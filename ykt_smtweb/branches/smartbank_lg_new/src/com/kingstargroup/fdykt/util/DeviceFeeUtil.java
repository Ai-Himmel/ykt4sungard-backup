package com.kingstargroup.fdykt.util;

import java.sql.SQLException;

import org.apache.log4j.Logger;

import com.kingstargroup.fdykt.dao.DB2DeviceDAO;

public class DeviceFeeUtil {
	
	  private static final Logger logger = Logger.getLogger(DeviceFeeUtil.class);

	
	public static  String getGroupByDevice(String deviceId)throws  SQLException, Exception {
		try{
		DB2DeviceDAO  dao = new DB2DeviceDAO();
		return  dao.getGroupbyDeviceId(deviceId);
		}catch (Exception e) {
			logger.error("读取设备菜单组失败");
			throw (e);
    	}
		
	}

}
