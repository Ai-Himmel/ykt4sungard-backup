package org.king.dao.impl;

import org.apache.log4j.Logger;
import org.king.bean.Transdtl;
import org.king.dao.JdbcDao;
import org.king.util.DBUtil;
import org.king.util.Transformer;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-4-28
 */
public class OracleDaoImpl implements JdbcDao {
    private static final Logger logger = Logger.getLogger(OracleDaoImpl.class);

    private Transformer transformer = new Transformer();

    public List<Transdtl> findCheckRecord(Connection conn, String sql) {
        Statement stmt = null;
        ResultSet rs = null;
        List<Transdtl> result = new ArrayList<Transdtl>();
        try {
            stmt = conn.createStatement();
            logger.debug(sql);
            rs = stmt.executeQuery(sql);
            result = transformer.transformToBean(rs, Transdtl.class);
        } catch (Exception e) {
            logger.error(e);
        } finally {
            DBUtil.closeStatement(stmt);
            DBUtil.closeResultSet(rs);
        }
        return result;
    }

    /**
     * according to the response of check request,update third pay record
     *
     * @param conn .
     * @param args {ecard_id,status}
     * @throws SQLException
     */
    public void updateThirdPayRecord(Connection conn, String[][] args) throws SQLException {
        if (args == null || args.length == 0) {
            return;
        }
        String sql = "UPDATE T_THIRDPAY_JJLINK SET STATUS=?,UPDATE_TIME=to_char(sysdate,'YYYY-MM-DD HH24:mi:ss'),CHECK_NUM=nvl(CHECK_NUM,0)+1 WHERE ECARD_ID=? ";
        PreparedStatement pstmt = null;
        try {
            pstmt = conn.prepareStatement(sql);
            for (int i = 0; i < args.length; i++) {
                pstmt.setString(1, args[i][1]);
                pstmt.setLong(2, Long.parseLong(args[i][0]));
                pstmt.addBatch();
                logger.debug("[ecard_id:"+args[i][0]+",status:"+args[i][1]+"]");
            }
            pstmt.executeBatch();
        } catch (SQLException e) {
            throw e;
        } finally {
            DBUtil.closeStatement(pstmt);
        }
    }
}
