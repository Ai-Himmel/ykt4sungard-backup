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
            sql = "select device_id,device_name from YKT_CUR.T_PIF_DEVICE";
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
    
   public List DeviceList(int page) throws
    ClassNotFoundException, SQLException, Exception {
    String sql = "";
    Connection conn = null;
    PreparedStatement stm = null;
    ResultSet result = null;
    List  list = new ArrayList();
    
    try {
        conn = getConnection();
        sql = "select device_id,device_name,b.dict_caption as dict_caption from YKT_CUR.T_PIF_DEVICE  a, YKT_CUR.T_PIF_DICTIONARY  b where a.devtype =b.dict_value " +
              " and b.dict_value='0230'  order by device_id ";
       	 
        stm = conn.prepareStatement(sql);
        result = stm.executeQuery();
       
        int start = 0;
		while ((start++ < page - 1) && result.next()) {
			;
		}
		int count = 10;
		while (result.next() && (count-- > 0)) {
			HashMap devices = new HashMap();
            devices.put("devId",result.getString("device_id"));
            devices.put("devname",result.getString("device_name"));
            devices.put("dictcaption",result.getString("dict_caption"));
            list.add(devices);
        }
        return list;
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
   
   public int  DeviceCount() throws
   ClassNotFoundException, SQLException, Exception {
   String sql = "";
   Connection conn = null;
   PreparedStatement stm = null;
   ResultSet result = null;
   
   try {
       conn = getConnection();
       sql = "select  count(a.device_id)   from YKT_CUR.T_PIF_DEVICE  a, YKT_CUR.T_PIF_DICTIONARY  b where a.devtype =b.dict_value " +
             " and b.dict_value='0230' ";
      	 
       stm = conn.prepareStatement(sql);
       result = stm.executeQuery();
       result.next();
       int  total = result.getInt(1);
       return total;
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
   
   public String  getShopbyDeviceId(String deviceId)throws ClassNotFoundException,SQLException, Exception{
	   String sql = "";
	   Connection conn = null;
	   PreparedStatement stm = null;
	   ResultSet result = null;
	   String fee_acc="";
	   
       try{
    	   
	   conn= getConnection();
       sql =" select fee_acc  from ykt_cur.t_pif_device_fee_account  where deviceId="+deviceId;
       stm= conn.prepareStatement(sql);
       result=stm.executeQuery();
      
       while(result.next()){
    	   fee_acc = result.getString("fee_acc");
       }
       return fee_acc;
       } catch (SQLException e1) {
    	   e1.printStackTrace();
       } catch (Exception e) {
           e.printStackTrace();
       } finally {
    	   if (stm != null) {
               stm.close();
           }
       }
       return fee_acc;
   }
   
   public String  getGroupbyDeviceId(String deviceId)throws ClassNotFoundException,SQLException, Exception{
	  
	   String sql = "";
	   Connection conn = null;
	   PreparedStatement stm = null;
	   ResultSet result = null;
	   String group="";
       try{   
    	   
	   conn= getConnection();
       sql =" select group  from ykt_cur.t_pif_device_fee_account  where deviceId= "+deviceId;
       stm= conn.prepareStatement(sql);
       result=stm.executeQuery();
      
       while(result.next()){
    	   group = result.getString("group");
       }
       
       return group;
       } catch (SQLException e1) {
    	   e1.printStackTrace();
       } catch (Exception e) {
           e.printStackTrace();
       }
       finally {
    	   if (stm != null) {
               stm.close();
           }
       }
       return group;
   }
}
