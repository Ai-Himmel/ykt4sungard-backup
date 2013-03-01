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
		 * Description: DeviceUtil�ն��豸ʹ����<br>
		 * Return: List<br>
		 * Modify History: <br>
		 * ��������    ������     ����ʱ��       ��������<br>
		 * ======================================<br>
		 *  ����      ����ΰ     2006-5-26  <br>
		 * @author   ����ΰ
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
				accMap.put("total",new Integer(devNum));
				accMap.put("rate",new Float(Integer.parseInt(objects[1].toString())*100/devNum));
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
