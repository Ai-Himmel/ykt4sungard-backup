package com.kingstargroup.fdykt.dao;

import java.sql.*;
import java.util.*;

public class DB2DeviceDAO extends DB2ActionDAO{

    public HashMap RetriveDevice() throws
        ClassNotFoundException, SQLException, Exception {
        String sql = "";
        Connection conn = null;
        PreparedStatement stm = null;
        ResultSet result = null;

        try {
            conn = getConnection();
            sql = "select device_id,device_name from YKT_CUR.T_PIF_DEVICE with ur";
            stm = conn.prepareStatement(sql);
            result = stm.executeQuery();
            HashMap devices = new HashMap();
            while (result.next()) {
                devices.put(result.getString("device_id"),
                            result.getString("device_name"));
            }
            return devices;
        } catch (SQLException e1) {
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
