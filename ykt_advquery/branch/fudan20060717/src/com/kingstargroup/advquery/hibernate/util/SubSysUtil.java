/**
 * 
 */
package com.kingstargroup.advquery.hibernate.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import com.kingstargroup.advquery.dictionary.TPifDictionary;
import com.kingstargroup.advquery.hibernate.dao.SubSysDAO;

public class SubSysUtil extends BasicUtil {

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AccountUtil����������ϸ<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-5-15  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static List getSubSysName() {
		SubSysDAO dao = SubSysDAO.getInstance();
		try {
			List subSysName = dao.getSubSysName();
			return subSysName;
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
			closeSession();
		}
	}
	public static String getSubSysName(String subsysId) {
		SubSysDAO dao = SubSysDAO.getInstance();
		try {
			String subSysName = ((TPifDictionary)dao.getSubSysName(subsysId)).getDictCaption();
			return subSysName;
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
			closeSession();
		}
	}

	public static List getgetSubSysVisitList(int sysid ,String beginDate,String endDate,String statType) {
		SubSysDAO dao = SubSysDAO.getInstance();
		List result = new ArrayList();
		try {
			List subsyslist = dao.getSubSysVisitList(sysid,beginDate,endDate,statType);
			for (int i=0 ;i<subsyslist.size();i++){
				Object[] objects = (Object[])subsyslist.get(i);
				HashMap accMap = new HashMap();
				accMap.put("log_date",objects[0]);
				accMap.put("numb",objects[1]);
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
