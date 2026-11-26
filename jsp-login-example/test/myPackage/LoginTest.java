package myPackage;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.mockito.ArgumentMatchers.eq;
import static org.mockito.ArgumentMatchers.any;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.never;
import static org.mockito.Mockito.verify;
import static org.mockito.Mockito.when;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.mockito.ArgumentCaptor;

/** The DAO and the servlet against an in-memory H2 database (see pom.xml). */
class LoginTest {

  @BeforeAll
  static void createUsers() throws Exception {
    try (Connection c = DriverManager.getConnection(System.getenv("DB_URL"), "sa", "");
         Statement s = c.createStatement()) {
      s.execute("CREATE TABLE IF NOT EXISTS users (username VARCHAR(50) PRIMARY KEY,"
          + " password VARCHAR(50) NOT NULL, FirstName VARCHAR(50), LastName VARCHAR(50))");
      s.execute("MERGE INTO users VALUES ('demo', 'demo', 'Demo', 'User')");
      s.execute("MERGE INTO users VALUES ('o''brien', 'pa''ss', 'Pat', 'O''Brien')");
    }
  }

  private static UserBean login(String user, String password) {
    UserBean bean = new UserBean();
    bean.setUserName(user);
    bean.setPassword(password);
    return UserDAO.login(bean);
  }

  @Test
  void rightPasswordLogsIn() {
    UserBean u = login("demo", "demo");
    assertTrue(u.isValid());
    assertEquals("Demo", u.getFirstName());
    assertEquals("User", u.getLastName());
  }

  @Test
  void wrongPasswordOrUnknownUserIsRejected() {
    assertFalse(login("demo", "nope").isValid());
    assertFalse(login("nobody", "demo").isValid());
  }

  @Test
  void sqlInjectionInThePasswordDoesNotLogIn() {
    assertFalse(login("demo", "' or '1'='1").isValid());
    assertFalse(login("' or '1'='1' --", "x").isValid());
  }

  @Test
  void quotesInCredentialsAreDataNotSql() {
    UserBean u = login("o'brien", "pa'ss");
    assertTrue(u.isValid());
    assertEquals("O'Brien", u.getLastName());
  }

  private static HttpServletResponse get(String user, String password, HttpSession session)
      throws Exception {
    HttpServletRequest req = mock(HttpServletRequest.class);
    HttpServletResponse resp = mock(HttpServletResponse.class);
    when(req.getParameter("un")).thenReturn(user);
    when(req.getParameter("pw")).thenReturn(password);
    when(req.getSession(true)).thenReturn(session);
    new QueryServlet().doGet(req, resp);
    return resp;
  }

  @Test
  void servletRedirectsAValidUserAndKeepsItInTheSession() throws Exception {
    HttpSession session = mock(HttpSession.class);
    HttpServletResponse resp = get("demo", "demo", session);
    verify(resp).sendRedirect("userLogged.jsp");
    ArgumentCaptor<Object> stored = ArgumentCaptor.forClass(Object.class);
    verify(session).setAttribute(eq("currentSessionUser"), stored.capture());
    UserBean u = (UserBean) stored.getValue();
    assertTrue(u.isValid());
    assertEquals("Demo", u.getFirstName());
  }

  @Test
  void servletRedirectsAnInvalidUser() throws Exception {
    HttpSession session = mock(HttpSession.class);
    HttpServletResponse resp = get("demo", "' or '1'='1", session);
    verify(resp).sendRedirect("invalidLogin.jsp");
    verify(resp, never()).sendRedirect("userLogged.jsp");
    verify(session, never()).setAttribute(eq("currentSessionUser"), any());
  }
}
