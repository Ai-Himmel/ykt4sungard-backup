package com.sungard.util;

import com.sungard.common.Configuration;
import com.sungard.common.Constant;
import org.apache.log4j.Logger;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Locale;
import java.util.Properties;

/**
 * .
 * User: Yiming.You
 * Date: 2011-9-30
 */
public class DBUtil {
    private static final Logger logger = Logger.getLogger(DBUtil.class);

    public static Connection getConnection() {
        Connection conn = null;
        try {
            String driverClass = Configuration.getProperty(Constant.JDBC_DRIVER_CLASS);
            String jdbcUrl = Configuration.getProperty(Constant.JDBC_URL);
            String user = Configuration.getProperty(Constant.DB_USER);
            String password = Configuration.getProperty(Constant.DB_PASSWORD);
            logger.debug("locale = " + Locale.getDefault());
            Class.forName(driverClass);
            conn = DriverManager.getConnection(jdbcUrl, user, password);
        } catch (Exception e) {
            logger.error("fail to open connection", e);
        }
        return conn;
    }

    public static void closeConnection(Connection conn) {
        if (conn != null) {
            try {
                conn.close();
            } catch (SQLException e) {
            }
        }
    }

    public static void closeStatement(Statement stmt) {
        if (stmt != null) {
            try {
                stmt.close();
            } catch (SQLException e) {
            }
        }
    }

    public static void closeResultSet(ResultSet rs) {
        if (rs != null) {
            try {
                rs.close();
            } catch (SQLException e) {
            }
        }
    }

    public static void rollback(Connection conn) {
        if (conn != null) {
            try {
                conn.rollback();
            } catch (SQLException e) {
            }
        }
    }

    public static void main(String[] args) {
        Connection conn = DBUtil.getConnection();
        System.out.println("conn = " + conn);
        Locale aDefault = Locale.getDefault();
        System.out.println("aDefault = " + aDefault);
        Properties properties = System.getProperties();
        for (Object o : properties.keySet()) {
            System.out.println("o = " + o);
            System.out.println("properties = " + properties.get(o));
        }
    }
}
