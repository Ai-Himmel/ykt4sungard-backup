package org.king.dao;

import org.king.bean.Transdtl;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-4-28
 */
public interface JdbcDao {
    public List<Transdtl> findCheckRecord(Connection conn,String sql);

    public void updateThirdPayRecord(Connection conn, String[][] args) throws SQLException;
}
