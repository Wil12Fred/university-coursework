# jsp-login-example

[![CI](https://github.com/Wil12Fred/university-coursework/actions/workflows/jsp-login-example.yml/badge.svg)](https://github.com/Wil12Fred/university-coursework/actions/workflows/jsp-login-example.yml) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](../LICENSE)

A minimal Java web application showing the classic JSP + Servlet + DAO +
JavaBean pattern: a JSP login form sends the username and password to a
servlet, which looks the user up in a MySQL table and shows a welcome page or
an "invalid user" page. UI text is in Spanish. It is a teaching example, not
production code — see **Known limitations**.

## Features

| File | Role |
|---|---|
| `queryUser.jsp` | login form (`un`, `pw`), submits `GET query` |
| `WEB-INF/web.xml` | maps `/query` to `myPackage.QueryServlet` |
| `WEB-INF/classes/QueryServlet.java` | calls the DAO, stores the user in the session, redirects |
| `WEB-INF/classes/UserDAO.java` | `SELECT * FROM users WHERE username=? AND password=?` (prepared statement) |
| `WEB-INF/classes/ConnectionManager.java` | JDBC connection, settings from env vars (`.env.example`) |
| `WEB-INF/classes/UserBean.java` | the user JavaBean |
| `userLogged.jsp` / `invalidLogin.jsp` | result pages |

## Requirements

- JDK 8 or newer to build (the Maven wrapper downloads Maven itself).
  Debian/Ubuntu: `sudo apt install openjdk-17-jdk`; Arch: `sudo pacman -S jdk17-openjdk`.
- To run it: a Servlet 3.0 container that still uses the `javax.*` namespace,
  e.g. **Tomcat 8.5 or 9** (Tomcat 10+ uses `jakarta.*` and will not load
  these classes), MySQL, and the MySQL JDBC driver (Connector/J) in Tomcat's `lib/`.

## Build

```sh
./mvnw package          # runs the tests, then builds target/LoginPageJsp.war
```

## Run

Database:

```sql
CREATE DATABASE jsplogin;
USE jsplogin;
CREATE TABLE users (
  username  VARCHAR(50) PRIMARY KEY,
  password  VARCHAR(50) NOT NULL,
  FirstName VARCHAR(50),
  LastName  VARCHAR(50)
);
INSERT INTO users VALUES ('demo', 'demo', 'Demo', 'User');
```

Tomcat:

1. Put the `.env.example` settings in Tomcat's environment, for example in
   `$CATALINA_HOME/bin/setenv.sh`:
   ```sh
   export DB_URL='jdbc:mysql://localhost/jsplogin?useSSL=false'
   export DB_USER=root
   export DB_PASSWORD=...
   ```
2. Copy the MySQL Connector/J jar into `$CATALINA_HOME/lib/`.
3. Copy `target/LoginPageJsp.war` into `$CATALINA_HOME/webapps/` and start Tomcat.
4. Open `http://localhost:8080/LoginPageJsp/queryUser.jsp`, log in as `demo` / `demo`
   and you get `Bienvenido Demo User`; a wrong password shows `Disculpe, datos no validos.`

The app has not been run against a live Tomcat + MySQL; what is verified is
the build and the tests below (DAO and servlet against H2).

## Tests

```sh
./mvnw test
```

`test/myPackage/LoginTest.java` (JUnit 5) runs the real DAO and servlet
against an in-memory H2 database (Surefire sets `DB_URL` to it):

- the right password logs in and fills the first and last name; a wrong
  password or an unknown user does not;
- **SQL injection**: `' or '1'='1` as the password, or `' or '1'='1' --` as
  the username, does not log in;
- a username and password containing apostrophes (`o'brien` / `pa'ss`) work;
- `QueryServlet.doGet` redirects a valid user to `userLogged.jsp` and stores
  them in the session, and redirects an injection attempt to
  `invalidLogin.jsp` without touching the session (request, response and
  session are Mockito mocks).

## Project layout

```
*.jsp                    form and result pages
WEB-INF/web.xml          servlet mapping
WEB-INF/classes/*.java   servlet, DAO, bean, connection manager
test/myPackage/          JUnit tests
pom.xml, mvnw            Maven build (WAR packaging)
.env.example             database settings read from the environment
```

## Known limitations

- **SQL injection** — fixed: the DAO concatenated the credentials into the
  query (and printed it, password included, to stdout). It now uses a
  `PreparedStatement`; the tests above fail without the fix.
- Passwords are still stored and compared **in plain text**. A real
  application would store a slow salted hash (bcrypt, scrypt, Argon2) and
  compare hashes. Changing that means changing the table and every stored
  password, so it is left as-is in this teaching sample.
- The form uses `GET`, so the password ends up in the URL, browser history
  and server logs.
- The JSP pages declare `windows-1256` (Arabic) as their encoding, a leftover
  from the tutorial this was based on.
- `userLogged.jsp` fails with a `NullPointerException` if opened without
  logging in.

## Background

Written for a web programming course at university, 2016.

## License

MIT — see [LICENSE](../LICENSE).
