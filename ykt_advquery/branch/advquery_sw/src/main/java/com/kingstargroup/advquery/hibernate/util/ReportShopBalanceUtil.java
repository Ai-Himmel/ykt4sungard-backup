/**
 * 
 */
package com.kingstargroup.advquery.hibernate.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import com.kingstargroup.advquery.common.DateUtilExtend;
import com.kingstargroup.advquery.hibernate.dao.ReportShopBalanceDAO;
import com.kingstargroup.advquery.util.WebKeys;

public class ReportShopBalanceUtil extends BasicUtil {

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AccountUtil个人消费明细<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-5-15  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public static List getAllConsumeStat(String beginDate,String endDate,String statType) {
		ReportShopBalanceDAO dao = ReportShopBalanceDAO.getInstance();
		List result = new ArrayList();
		try {
			List consume = dao.getAllConsumeStat(beginDate,endDate,statType);
			if ("bydate".equals(statType)){
				for (int i=0 ;i<consume.size();i++){
					Object[] objects = (Object[])consume.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("tradeamt",objects[1]);
					accMap.put("mngamt",objects[2]);
					accMap.put("tradenum",objects[3]);
					accMap.put("week",DateUtilExtend.getWeekByDate(objects[0].toString()));
					accMap.put("sysdate",new Integer((int)DateUtilExtend.diffDate(WebKeys.sysBeginDate,objects[0].toString())+1));
					result.add(accMap);
				}
			}else{
				for (int i=0 ;i<consume.size();i++){
					Object[] objects = (Object[])consume.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("tradeamt",objects[1]);
					accMap.put("mngamt",objects[2]);
					accMap.put("tradenum",objects[3]);
					result.add(accMap);
				}
			}
			return result;
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
			closeSession();
		}
	}
	
	public static List getAreaSalesNumCompare(String beginDate,String endDate,String statType){
		ReportShopBalanceDAO dao = ReportShopBalanceDAO.getInstance();
		List result = new ArrayList();
		try {
			List consume = dao.getAreaSalesNumCompare(beginDate,endDate,statType);
			if ("bydate".equals(statType)){
				for (int i=0 ;i<consume.size();i++){
					Object[] objects = (Object[])consume.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("hd",objects[1]);
					accMap.put("fl",objects[2]);
					accMap.put("zj",objects[3]);
					accMap.put("jw",objects[4]);
					accMap.put("week",DateUtilExtend.getWeekByDate(objects[0].toString()));
					accMap.put("sysdate",new Integer((int)DateUtilExtend.diffDate(WebKeys.sysBeginDate,objects[0].toString())+1));
					result.add(accMap);
				}
			}else{
				for (int i=0 ;i<consume.size();i++){
					Object[] objects = (Object[])consume.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("hd",objects[1]);
					accMap.put("fl",objects[2]);
					accMap.put("zj",objects[3]);
					accMap.put("jw",objects[4]);
					result.add(accMap);
				}
			}
			return result;
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
			closeSession();
		}		
	}
	public static List getAreaSalesMoneyCompare(String beginDate,String endDate,String statType){
		ReportShopBalanceDAO dao = ReportShopBalanceDAO.getInstance();
		List result = new ArrayList();
		try {
			List consume = dao.getAreaSalesMoneyCompare(beginDate,endDate,statType);
			if ("bydate".equals(statType)){
				for (int i=0 ;i<consume.size();i++){
					Object[] objects = (Object[])consume.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("hd",objects[1]);
					accMap.put("fl",objects[2]);
					accMap.put("zj",objects[3]);
					accMap.put("jw",objects[4]);
					accMap.put("week",DateUtilExtend.getWeekByDate(objects[0].toString()));
					accMap.put("sysdate",new Integer((int)DateUtilExtend.diffDate(WebKeys.sysBeginDate,objects[0].toString())+1));
					result.add(accMap);
				}
			}else{
				for (int i=0 ;i<consume.size();i++){
					Object[] objects = (Object[])consume.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("hd",objects[1]);
					accMap.put("fl",objects[2]);
					accMap.put("zj",objects[3]);
					accMap.put("jw",objects[4]);
					result.add(accMap);
				}
			}
			return result;
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
			closeSession();
		}		
	}
	
	/**
	 * 各校区消费金额和笔数对比
	 * 2006-6-2
	 * hjw
	 * @param
	 * @return
	 */
	public static List getAreaSalesCompare(String beginDate,String endDate,String statType){
		ReportShopBalanceDAO dao = ReportShopBalanceDAO.getInstance();
		List result = new ArrayList();
		try {
			List consume = dao.getAreaSalesCompare(beginDate,endDate,statType);
			if ("bydate".equals(statType)){
				for (int i=0 ;i<consume.size();i++){
					Object[] objects = (Object[])consume.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("hdamt",objects[1]);
					accMap.put("flamt",objects[2]);
					accMap.put("zjamt",objects[3]);
					accMap.put("jwamt",objects[4]);
					accMap.put("hdnum",objects[5]);
					accMap.put("flnum",objects[6]);
					accMap.put("zjnum",objects[7]);
					accMap.put("jwnum",objects[8]);
					accMap.put("week",DateUtilExtend.getWeekByDate(objects[0].toString()));
					accMap.put("sysdate",new Integer((int)DateUtilExtend.diffDate(WebKeys.sysBeginDate,objects[0].toString())+1));
					result.add(accMap);
				}
			}else{
				for (int i=0 ;i<consume.size();i++){
					Object[] objects = (Object[])consume.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("hdamt",objects[1]);
					accMap.put("flamt",objects[2]);
					accMap.put("zjamt",objects[3]);
					accMap.put("jwamt",objects[4]);
					accMap.put("hdnum",objects[5]);
					accMap.put("flnum",objects[6]);
					accMap.put("zjnum",objects[7]);
					accMap.put("jwnum",objects[8]);
					result.add(accMap);
				}
			}
			return result;
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
			closeSession();
		}		
	}
	
//	商户营业结算报表  gejinfeng 2008-09-23
	public static List getShopAccountQueryResult(String beginDate,String endDate,String shopid){
		ReportShopBalanceDAO dao = ReportShopBalanceDAO.getInstance();
		List result = new ArrayList();
		try {
			List consume = dao.getShopAccountQueryResult(beginDate,endDate,shopid);
			for(int i=0 ; i<consume.size() ; i++){
				Object[] objects = (Object[])consume.get(i);
				HashMap accMap = new HashMap();
				accMap.put("shopId", objects[0]);
				accMap.put("shopName", objects[1]);
				accMap.put("deptId", objects[2]);
				accMap.put("deviceId", objects[3]);
				accMap.put("deviceName", objects[4]);
				accMap.put("sumCount", objects[5]);
				accMap.put("sumTrade", objects[6]);
				accMap.put("sumMng", objects[7]);
				accMap.put("sumTotal", objects[8]);
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
