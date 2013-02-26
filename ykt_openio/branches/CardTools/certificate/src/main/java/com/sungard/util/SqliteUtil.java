package com.sungard.util;

import com.sungard.common.Configuration;
import com.sungard.common.Constant;
import org.apache.log4j.Logger;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

/**
 * .
 * User: Yiming.You
 * Date: 2011-9-22
 */
public class SqliteUtil {
    private static final Logger logger = Logger.getLogger(SqliteUtil.class);

    public static Connection getConnection() {
        Connection conn = null;
        try {
            String driverClass = Configuration.getProperty(Constant.SQLITE_DRIVER_CLASS);
            String jdbcUrl = Configuration.getProperty(Constant.SQLITE_JDBC_URL);
            Class.forName(driverClass);
            conn = DriverManager.getConnection(jdbcUrl);
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
