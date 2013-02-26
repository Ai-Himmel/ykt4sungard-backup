package org.king.util;

import org.apache.log4j.Logger;
import org.king.common.Configuration;
import org.king.common.Constant;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

/**
 * .
 * User: Yiming.You
 * Date: 2011-4-28
 */
public class DBUtil {
    private static final Logger logger = Logger.getLogger(DBUtil.class);

    public static Connection getConnection() {
        Connection conn = null;
        try {
            String driverClass = Configuration.getProperty(Constant.DRIVER_CLASS);
            String jdbcUrl = Configuration.getProperty(Constant.JDBC_URL);
            String user = Configuration.getProperty(Constant.USERNAME);
            String password = Configuration.getProperty(Constant.PASSWORD);
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
}
