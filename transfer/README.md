# Transfer Application

This is an example of a simple application that does a transfer of money between accounts.

## Used resources

Stack is very lightweight and straightforward:

- [Kotlin](https://kotlinlang.org/)
- [Ktor](https://ktor.io/)
- [Exposed](https://github.com/JetBrains/Exposed)
- [H2](http://www.h2database.com/html/main.html)

## Reasoning

As we do not need anything else than transfer, we need to focus on transactions.
Transactions need to read/modify data and can be expressed through plain SQL procedures on the DBMS side or sync in-code transactions on the application side.
For purpose of the application, the focus is on the simplistic application-side approach.
To see a solution in plain SQL, refer to [hsqldb.sql](hsqldb.sql).

## Running the application

To run, use `gradlew run` in the root of the project. To build Fat Jar, use `gradlew shadowJar`.
