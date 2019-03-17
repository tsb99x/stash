import com.transfer.Account
import com.transfer.Transfer
import com.transfer.module
import io.ktor.application.Application
import io.ktor.http.ContentType
import io.ktor.http.HttpHeaders
import io.ktor.http.HttpMethod
import io.ktor.http.HttpStatusCode
import io.ktor.server.testing.*
import org.jetbrains.exposed.sql.*
import org.jetbrains.exposed.sql.transactions.transaction
import java.math.BigDecimal
import java.util.*
import kotlin.test.*

/**
 * (Almost) integration testing of application.
 * Operates on set of 3 accounts.
 * Ensures invariants of balances and transfer logs after any manipulation.
 */

class ApplicationTest {

    private val aUid = UUID.fromString("bc371998-9c3d-4eec-bd32-376f0e2f3d84")
    private val bUid = UUID.fromString("718bdc31-f057-4430-a0d1-f374b3f5b7b8")
    private val cUid = UUID.fromString("6be9a3fe-4f34-4917-a3f0-392b44507353")
    private val eUid = UUID.fromString("ffffffff-ffff-ffff-ffff-ffffffffffff")

    private fun setupTestData() {
        transaction {
            SchemaUtils.drop(Account, Transfer)
            SchemaUtils.create(Account, Transfer)

            com.transfer.Account.insert {
                it[uid] = aUid
                it[balance] = BigDecimal(1000.50)
            }

            com.transfer.Account.insert {
                it[uid] = bUid
                it[balance] = BigDecimal(999.99)
            }

            com.transfer.Account.insert {
                it[uid] = cUid
                it[balance] = BigDecimal(999_999_999_999.99)
            }
        }
    }

    @Test
    fun `test health check`() = withTestApplication(Application::module) {
        setupTestData()

        val call = handleRequest(HttpMethod.Get, "/health")

        assertEquals(HttpStatusCode.OK, call.response.status())
        assertEquals("application/json; charset=UTF-8", call.response.headers["Content-Type"])
        assertEquals(
            """{
            |  "status" : "alive"
            |}""".trimMargin(), call.response.content
        )

        assertBalances(BigDecimal("1000.50"), BigDecimal("999.99"), BigDecimal("999999999999.99"))
        assertTranferLogSize(0)
    }

    @Test
    fun `test non-existent route`() = withTestApplication(Application::module) {
        setupTestData()

        val call = handleRequest(HttpMethod.Get, "/non-existing")

        assertFalse(call.requestHandled)

        assertBalances(BigDecimal("1000.50"), BigDecimal("999.99"), BigDecimal("999999999999.99"))
        assertTranferLogSize(0)
    }

    @Test
    fun `test transfer empty body`() = withTestApplication(Application::module) {
        setupTestData()

        val call = handleRequest(HttpMethod.Post, "/transfer") {
            addHeader(HttpHeaders.ContentType, ContentType.Application.Json.toString())
        }

        assertEquals(HttpStatusCode.BadRequest, call.response.status())
        assertEquals("application/json; charset=UTF-8", call.response.headers["Content-Type"])
        assertTrue(call.response.content!!.isNotEmpty())

        assertBalances(BigDecimal("1000.50"), BigDecimal("999.99"), BigDecimal("999999999999.99"))
        assertTranferLogSize(0)
    }

    @Test
    fun `test transfer empty obj`() = withTestApplication(Application::module) {
        setupTestData()

        val call = handleRequest(HttpMethod.Post, "/transfer") {
            addHeader(HttpHeaders.ContentType, ContentType.Application.Json.toString())
            setBody("""{}""")
        }

        assertEquals(HttpStatusCode.BadRequest, call.response.status())
        assertEquals("application/json; charset=UTF-8", call.response.headers["Content-Type"])
        assertTrue(call.response.content!!.isNotEmpty())

        assertBalances(BigDecimal("1000.50"), BigDecimal("999.99"), BigDecimal("999999999999.99"))
        assertTranferLogSize(0)
    }

    @Test
    fun `test transfer with non-existent source`() = withTestApplication(Application::module) {
        setupTestData()

        assertFailedResult(
            callTransfer(eUid, bUid, 1000.toBigDecimal()), HttpStatusCode.BadRequest,
            "Transfer source account uid='ffffffff-ffff-ffff-ffff-ffffffffffff' does not exist"
        )

        assertBalances(BigDecimal("1000.50"), BigDecimal("999.99"), BigDecimal("999999999999.99"))
        assertTranferLogSize(0)
    }

    @Test
    fun `test transfer with non-existent destination`() = withTestApplication(Application::module) {
        setupTestData()

        assertFailedResult(
            callTransfer(aUid, eUid, 1000.toBigDecimal()), HttpStatusCode.BadRequest,
            "Transfer destination account uid='ffffffff-ffff-ffff-ffff-ffffffffffff' does not exist"
        )

        assertBalances(BigDecimal("1000.50"), BigDecimal("999.99"), BigDecimal("999999999999.99"))
        assertTranferLogSize(0)
    }

    @Test
    fun `test transfer success and reverse`() = withTestApplication(Application::module) {
        setupTestData()

        assertOkResult(
            callTransfer(aUid, bUid, 1000.toBigDecimal())
        )

        assertBalances(BigDecimal("0.50"), BigDecimal("1999.99"), BigDecimal("999999999999.99"))
        assertTranferLogRecord(aUid, bUid, 1000.toBigDecimal())
        assertTranferLogSize(1)

        assertOkResult(
            callTransfer(bUid, aUid, 1000.toBigDecimal())
        )

        assertBalances(BigDecimal("1000.50"), BigDecimal("999.99"), BigDecimal("999999999999.99"))
        assertTranferLogRecord(bUid, aUid, 1000.toBigDecimal())
        assertTranferLogSize(2)
    }

    @Test
    fun `test transfer to same account`() = withTestApplication(Application::module) {
        setupTestData()

        assertFailedResult(
            callTransfer(aUid, aUid, 1000.toBigDecimal()), HttpStatusCode.BadRequest,
            "Destination account is the same as source account uid='bc371998-9c3d-4eec-bd32-376f0e2f3d84'"
        )

        assertBalances(BigDecimal("1000.50"), BigDecimal("999.99"), BigDecimal("999999999999.99"))
        assertTranferLogSize(0)
    }

    @Test
    fun `test transfer with underflow`() = withTestApplication(Application::module) {
        setupTestData()

        assertOkResult(
            callTransfer(aUid, bUid, 1000.toBigDecimal())
        )

        assertBalances(BigDecimal("0.50"), BigDecimal("1999.99"), BigDecimal("999999999999.99"))
        assertTranferLogRecord(aUid, bUid, 1000.toBigDecimal())
        assertTranferLogSize(1)

        assertFailedResult(
            callTransfer(aUid, bUid, 1000.toBigDecimal()), HttpStatusCode.BadRequest,
            "Transfer source account does not have required amount of currency"
        )

        assertBalances(BigDecimal("0.50"), BigDecimal("1999.99"), BigDecimal("999999999999.99"))
        assertTranferLogSize(1)
    }

    @Test
    fun `test transfer with overflow`() = withTestApplication(Application::module) {
        setupTestData()

        assertFailedResult(
            callTransfer(aUid, cUid, 1000.toBigDecimal()), HttpStatusCode.InternalServerError,
            "org.h2.jdbc.JdbcSQLException: Value too long for column BALANCE [90005-60]"
        )

        assertBalances(BigDecimal("1000.50"), BigDecimal("999.99"), BigDecimal("999999999999.99"))
        assertTranferLogSize(0)
    }

    /**
     * Utility part of test suite.
     * Mainly for assertion simplification.
     */

    private fun TestApplicationEngine.callTransfer(src: UUID, dst: UUID, amount: BigDecimal): TestApplicationCall {
        return handleRequest(HttpMethod.Post, "/transfer") {
            addHeader(HttpHeaders.ContentType, ContentType.Application.Json.toString())
            setBody(
                """{
                |"src":"$src",
                |"dst":"$dst",
                |"amount":$amount
                |}""".trimMargin()
            )
        }
    }

    private fun assertBalances(aBalance: BigDecimal, bBalance: BigDecimal, cBalance: BigDecimal) {
        transaction {
            assertIndividualBalance(aUid, aBalance)
            assertIndividualBalance(bUid, bBalance)
            assertIndividualBalance(cUid, cBalance)
        }
    }

    private fun assertIndividualBalance(uid: UUID, balance: BigDecimal) {
        val query = Account.select { Account.uid eq uid }
        assertEquals(query.count(), 1)
        query.forEach {
            assertEquals(balance, it[Account.balance])
        }
    }

    private fun assertTranferLogRecord(src: UUID, dst: UUID, amount: BigDecimal) {
        transaction {
            val query = Transfer.select {
                (Transfer.src eq src) and (Transfer.dst eq dst) and (Transfer.amount eq amount)
            }
            assertEquals(1, query.count())
        }
    }

    private fun assertTranferLogSize(size: Int) {
        transaction {
            assertEquals(size, Transfer.selectAll().count())
        }
    }

    private fun assertOkResult(call: TestApplicationCall) {
        assertResult(
            call, HttpStatusCode.OK,
            """{
            |  "OK" : true
            |}""".trimMargin()
        )
    }

    private fun assertFailedResult(call: TestApplicationCall, statusCode: HttpStatusCode, msg: String) {
        assertResult(
            call, statusCode,
            """{
            |  "OK" : false,
            |  "msg" : "$msg"
            |}""".trimMargin()
        )
    }

    private fun assertResult(call: TestApplicationCall, statusCode: HttpStatusCode, content: String) {
        assertEquals(statusCode, call.response.status())
        assertEquals("application/json; charset=UTF-8", call.response.headers["Content-Type"])
        assertEquals(content, call.response.content)
    }
}
