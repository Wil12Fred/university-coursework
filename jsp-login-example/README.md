# LoginPageJsp

A minimal Java web application from a university course (2018): a JSP login form
that sends the username and password to a servlet, which looks the user up in a
MySQL table and shows a welcome page or an "invalid user" page. The UI text is in
Spanish.

It is a teaching example of the classic JSP + Servlet + DAO + JavaBean pattern,
not production code — see **Known issues**.

## How it works

| File | Role |
|---|---|
| `queryUser.jsp` | login form (`un`, `pw`), submits `GET query` |
| `WEB-INF/web.xml` | maps `/query` to `myPackage.QueryServlet` |
| `WEB-INF/classes/QueryServlet.java` | calls the DAO, stores the user in the session, redirects |
| `WEB-INF/classes/UserDAO.java` | `SELECT * FROM users WHERE username=... AND password=...` |
| `WEB-INF/classes/ConnectionManager.java` | JDBC connection, settings from env vars |
| `WEB-INF/classes/UserBean.java` | the user JavaBean |
| `userLogged.jsp` / `invalidLogin.jsp` | result pages |

## Requirements

- JDK 8 or newer
- a `javax.servlet-api` 3.x jar to compile against (e.g. from Maven Central,
  `javax.servlet:javax.servlet-api:3.1.0`)
- a Servlet 3.0 container that still uses the `javax.*` namespace, e.g. **Tomcat 8.5 or 9**
  (Tomcat 10+ uses `jakarta.*` and will not load these classes)
- MySQL, plus the MySQL JDBC driver (Connector/J) copied into Tomcat's `lib/`

## Build

```sh
SERVLET_API_JAR=/path/to/javax.servlet-api-3.1.0.jar ./build.sh
# -> build/LoginPageJsp.war
```

## Database

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

## Run (Tomcat)

1. Copy `.env.example` values into Tomcat's environment, for example in
   `$CATALINA_HOME/bin/setenv.sh`:
   ```sh
   export DB_URL='jdbc:mysql://localhost/jsplogin?useSSL=false'
   export DB_USER=root
   export DB_PASSWORD=...
   ```
2. Copy the MySQL Connector/J jar into `$CATALINA_HOME/lib/`.
3. Copy `build/LoginPageJsp.war` into `$CATALINA_HOME/webapps/` and start Tomcat.
4. Open `http://localhost:8080/LoginPageJsp/queryUser.jsp`, log in as `demo` / `demo`
   and you get `Bienvenido Demo User`; a wrong password shows `Disculpe, datos no validos.`

Only the compile/package step has been verified; the app has not been run
against a live Tomcat + MySQL as part of this cleanup.

## Known issues (kept as-is, it is coursework)

- **SQL injection**: `UserDAO` concatenates the username and password into the
  query. A `PreparedStatement` would fix it.
- Passwords are stored and compared in plain text, and the form uses `GET`, so
  the password appears in the URL.
- The query is printed to stdout, including the password.
