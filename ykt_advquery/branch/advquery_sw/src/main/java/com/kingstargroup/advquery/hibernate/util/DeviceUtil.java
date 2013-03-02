/**
 * 
 */
package com.kingstargroup.advquery.hibernate.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import com.kingstargroup.advquery.hibernate.dao.DeviceDAO;

public class DeviceUtil extends BasicUtil {

		/**
		 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
		 * File name: .java<br>
		 * Description: DeviceUtil终端设备使用率<br>
		 * Return: List<br>
		 * Modify History: <br>
		 * 操作类型    操作人     操作时间       操作内容<br>
		 * ======================================<br>
		 *  创建      韩纪伟     2006-5-26  <br>
		 * @author   韩纪伟
		 * @version 
		 * @since 1.0
		 */
	public static List getDeviceRate(
			int serialtype,
			String beginDate,
			String endDate,
			String devType,
			String statType) {
		DeviceDAO dao = DeviceDAO.getInstance();
		int devNum = Integer.parseInt(dao.getDeviceNum(devType));
		List result = new ArrayList();
		try {
			List devused = dao.getDeviceUsed(serialtype,beginDate,endDate,statType);
			for (int i=0 ;i<devused.size();i++){
				Object[] objects = (Object[])devused.get(i);
				HashMap accMap = new HashMap();
				accMap.put("balance_date",objects[0]);
				accMap.put("devuse",objects[1]);
				if (devNum==0){
					accMap.put("rate",new Float(0));
				}else{
					accMap.put("rate",new Float(Integer.parseInt(objects[1].toString())*100/devNum));
				}
				accMap.put("total",new Integer(devNum));
				result.add(accMap);
			}
			return result;
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
			closeSession();
		}
	}
	
}
