/**
 * 
 */
package com.kingstargroup.advquery.hibernate.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import com.kingstargroup.advquery.hibernate.dao.AccountDAO;

public class AccountUtil extends BasicUtil {
	
public static List  getHandTrade(String custNo, String beginDate,String endDate) {
		
		//todo
		AccountDAO dao = AccountDAO.getInstance();
		List result = new ArrayList();
		try {
			List account = dao.getHandTrade(custNo, beginDate, endDate);
			
			/*for (int i=0 ;i<account.size();i++){
				Object[] objects = (Object[])account.get(i);
				HashMap accMap = new HashMap();
				accMap.put("operdate",objects[0]);
				accMap.put("opertime",objects[1]);
				accMap.put("devid",dao.getDevNameByDevId(Integer.parseInt(objects[2].toString())));
				accMap.put("operator",objects[3]);
				accMap.put("comments",objects[4]);
				accMap.put("opfee",objects[5]);
				result.add(accMap);
			}*/
			return result;
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
			closeSession();
		}
	}

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
	public static List getOneAccountDetail(String custNo, String beginDate,String endDate) {
		AccountDAO dao = AccountDAO.getInstance();
		List result = new ArrayList();
		try {
			List account = dao.getOneAccountDetail(custNo,beginDate,endDate);
			for (int i=0 ;i<account.size();i++){
				Object[] objects = (Object[])account.get(i);
				HashMap accMap = new HashMap();
				accMap.put("operdate",objects[0]);
				accMap.put("opertime",objects[1]);
				accMap.put("devid",dao.getDevNameByDevId(Integer.parseInt(objects[2].toString())));
				accMap.put("operator",objects[3]);
				accMap.put("comments",objects[4]);
				accMap.put("opfee",objects[5]);
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
	
	public static  String getCustIdBystuempNo(String  stuempNo){
		try{
		AccountDAO dao = AccountDAO.getInstance();
		return dao.getCustIdBystuempNo(stuempNo);
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
			closeSession();
		}
	}
	
}
