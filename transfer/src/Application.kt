package com.transfer

import com.fasterxml.jackson.core.JsonProcessingException
import com.fasterxml.jackson.databind.SerializationFeature
import io.ktor.application.Application
import io.ktor.application.call
import io.ktor.application.install
import io.ktor.features.CallLogging
import io.ktor.features.ContentNegotiation
import io.ktor.features.DefaultHeaders
import io.ktor.features.StatusPages
import io.ktor.http.ContentType
import io.ktor.http.HttpStatusCode
import io.ktor.jackson.jackson
import io.ktor.request.receive
import io.ktor.response.header
import io.ktor.response.respond
import io.ktor.response.respondText
import io.ktor.routing.get
import io.ktor.routing.post
import io.ktor.routing.routing
import org.jetbrains.exposed.sql.*
import org.jetbrains.exposed.sql.transactions.transaction
import org.joda.time.DateTime
import java.lang.Exception
import java.math.BigDecimal
import java.sql.Connection
import java.util.*

/**
 * Database is intended for in-memory DB only.
 * Recreated it on each startup, without validation, etc.
 * In real use, it is a good idea to use migration engines (think FlyWay).
 * Data type choices are debatable:
 *     - UUID will solve a problem of new accounts insertion and generation lock.
 *     - DECIMAL(14,2) allows to store anything up to trillion (max |999,999,999,999.99|).
 *     - DATETIME is especially good all around the globe with the use of time zone.
 * For advanced performance optimizations of DB:
 *     - Transfer table may be split by criteria like day, currency, regions, etc.
 *     - Each account may get separate history table to ensure less queries for transfer table.
 * For sake of simplicity, we are only interested in immutable (append-only) database.
 * As such, we do not need any cascades, especially in transfer table.
 */

object Account : Table() {
    val uid = uuid("uid").primaryKey()
    val balance = decimal("balance", 14, 2)
}

object Transfer : Table() {
    val uid = uuid("uid").primaryKey()
    val src = uuid("src").references(Account.uid)
    val dst = uuid("dst").references(Account.uid)
    val amount = decimal("amount", 14, 2)
    val time = datetime("time")
}

/**
 * Supporting exception subclass.
 * Useful when handling requests in async way.
 * Bound to response in StatusPages middleware.
 */

class BadRequestException(msg: String) : RuntimeException(msg)

/**
 * JSON from POST request on handles.
 * Simplifies deserialization of request body.
 */

data class TransferRequest(val src: UUID, val dst: UUID, val amount: BigDecimal)

/**
 * Main entry point for runtime.
 * Think `fun main(args : Array<String>)`.
 * Does:
 *   - Middleware installation.
 *   - Database initialization (in-mem).
 *   - Routing setup & inline execution.
 */

fun Application.module() {

    install(DefaultHeaders)
    install(CallLogging)

    install(StatusPages) {
        exception<JsonProcessingException> {
            call.respond(HttpStatusCode.BadRequest, mapOf("OK" to false, "msg" to it.localizedMessage))
        }

        exception<BadRequestException> {
            call.respond(HttpStatusCode.BadRequest, mapOf("OK" to false, "msg" to it.localizedMessage))
        }

        exception<Exception> {
            call.respond(HttpStatusCode.InternalServerError, mapOf("OK" to false, "msg" to it.localizedMessage))
        }
    }

    install(ContentNegotiation) {
        jackson {
            enable(SerializationFeature.INDENT_OUTPUT)
        }
    }

    Database.connect("jdbc:h2:mem:test;DB_CLOSE_DELAY=-1", "org.h2.Driver")

    transaction {
        SchemaUtils.create(Account, Transfer)
    }

    routing {

        /**
         * Simple health check route to keep server up or restart.
         * Mainly for containerized environment and tests.
         * Very useful for dependant services too.
         */

        get("/health") {
            call.respond(mapOf("status" to "alive"))
        }

        /**
         * Main handle to provide transfer between accounts.
         * Simplified because we need no authorization.
         * In real application, it is useful to combine with JWT auth, etc.
         * Data query, update and insertions are handled through transaction.
         * To ensure consistency, use maximum level of isolation, repeat once.
         */

        post("/transfer") {
            val request = call.receive<TransferRequest>()

            if (request.src == request.dst) {
                throw BadRequestException("Destination account is the same as source account uid='${request.src}'")
            }

            transaction(Connection.TRANSACTION_SERIALIZABLE, 1) {
                val srcQuery = Account.select { Account.uid eq request.src }.toSet()

                if (srcQuery.count() != 1) {
                    throw BadRequestException("Transfer source account uid='${request.src}' does not exist")
                }

                srcQuery.forEach {
                    if (it[Account.balance] < request.amount) {
                        throw BadRequestException("Transfer source account does not have required amount of currency")
                    }
                }

                if (Account.select { Account.uid eq request.dst }.count() != 1) {
                    throw BadRequestException("Transfer destination account uid='${request.dst}' does not exist")
                }

                Account.update({ Account.uid eq request.src }) { account ->
                    with(SqlExpressionBuilder) {
                        account.update(balance, balance - request.amount)
                    }
                }

                Account.update({ Account.uid eq request.dst }) { account ->
                    with(SqlExpressionBuilder) {
                        account.update(balance, balance + request.amount)
                    }
                }

                Transfer.insert {
                    it[uid] = UUID.randomUUID()
                    it[src] = request.src
                    it[dst] = request.dst
                    it[amount] = request.amount
                    it[time] = DateTime.now()
                }
            }

            call.respond(mapOf("OK" to true))
        }
    }
}
