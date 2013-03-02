package com.kingstargroup.fdykt.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.HashMap;

public class DB2TradeCodeDAO extends DB2ActionDAO {

    public HashMap RetriveTradeMsgs() throws
        ClassNotFoundException, SQLException, Exception {
        String sql = "";
        Connection conn = null;
        PreparedStatement stm = null;
        ResultSet result = null;

        try {
            conn = getConnection();
            sql = "select tradecode,trademsg from YKT_CUR.T_PIF_TRADECODE with ur";
            stm = conn.prepareStatement(sql);
            result = stm.executeQuery();
            HashMap trademsgs = new HashMap();
            while (result.next()) {
                trademsgs.put(result.getString("tradecode"),
                              result.getString("trademsg"));
            }
            return trademsgs;
        } catch (SQLException e1) {
            //Move to superClass
            //Log.write("Get a  EmpInfo failed with WORKER_NO = " + name + " failed : " + e.toString());
            throw (e1);
        } catch (Exception e) {
            e.printStackTrace();
            throw (e);
        } finally {
            if (stm != null) {
                stm.close();
            }

        }
    }
}
