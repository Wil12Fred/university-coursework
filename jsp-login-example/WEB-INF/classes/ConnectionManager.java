package myPackage;
import java.sql.*;
import java.util.*;
import myPackage.*;

public class ConnectionManager {

  static Connection con;
  static String url;
        
  public static Connection getConnection() {
    
    // Connection settings come from the environment (see .env.example).
    String url = env("DB_URL", "jdbc:mysql://localhost/jsplogin?useSSL=false");
    try {             
      con = DriverManager.getConnection(url, env("DB_USER", "root"), env("DB_PASSWORD", "")); 
    } catch (SQLException ex) {
      ex.printStackTrace();
    }
    return con;
  }

  private static String env(String name, String fallback) {
    String value = System.getenv(name);
    return value != null ? value : fallback;
  }
}
