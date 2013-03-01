/**
 * 
 */
package com.kingstargroup.advquery.hibernate.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import com.kingstargroup.advquery.common.DateUtilExtend;
import com.kingstargroup.advquery.hibernate.dao.ReportActiveDAO;
import com.kingstargroup.advquery.hibernate.dao.TicketDAO;
import com.kingstargroup.advquery.util.WebKeys;

public class ReportActiveUtil extends BasicUtil {

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
	public static List getTotleSavingMoneyStat(String beginDate,String endDate,String statType) {
		ReportActiveDAO dao = ReportActiveDAO.getInstance();
		List result = new ArrayList();
		try {
			List saving = dao.getTotleSavingMoneyStat(beginDate,endDate,statType);
			if ("bydate".equals(statType)){
				for (int i=0 ;i<saving.size();i++){
					Object[] objects = (Object[])saving.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("transfer",objects[1]);
					accMap.put("cash",objects[2]);
					accMap.put("pos",objects[3]);
					accMap.put("outlay",objects[5]);
					accMap.put("ticket",objects[4]);
					accMap.put("week",DateUtilExtend.getWeekByDate(objects[0].toString()));
					accMap.put("sysdate",new Integer((int)DateUtilExtend.diffDate(WebKeys.sysBeginDate,objects[0].toString())+1));
					result.add(accMap);
				}
			}else{
				for (int i=0 ;i<saving.size();i++){
					Object[] objects = (Object[])saving.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("transfer",objects[1]);
					accMap.put("cash",objects[2]);
					accMap.put("pos",objects[3]);
					accMap.put("outlay",objects[5]);
					accMap.put("ticket",objects[4]);
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
	 * 存款总体情况笔数统计
	 * 2006-5-31
	 * hjw
	 * @param
	 * @return
	 */
	public static List getTotleSavingNumStat(String beginDate,String endDate,String statType) {
		ReportActiveDAO dao = ReportActiveDAO.getInstance();
		List result = new ArrayList();
		try {
			List saving = dao.getTotleSavingNumStat(beginDate,endDate,statType);
			if ("bydate".equals(statType)){
				for (int i=0 ;i<saving.size();i++){
					Object[] objects = (Object[])saving.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("transfer",objects[1]);
					accMap.put("cash",objects[2]);
					accMap.put("pos",objects[3]);
					accMap.put("week",DateUtilExtend.getWeekByDate(objects[0].toString()));
					accMap.put("sysdate",new Integer((int)DateUtilExtend.diffDate(WebKeys.sysBeginDate,objects[0].toString())+1));
					result.add(accMap);
				}
			}else{
				for (int i=0 ;i<saving.size();i++){
					Object[] objects = (Object[])saving.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("transfer",objects[1]);
					accMap.put("cash",objects[2]);
					accMap.put("pos",objects[3]);
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
	 * 各类存款对比（笔数和金额）
	 * 2006-6-2
	 * hjw
	 * @param
	 * @return
	 */
	public static List getTotleSavingStat(String beginDate,String endDate,String statType) {
		ReportActiveDAO dao = ReportActiveDAO.getInstance();
		List result = new ArrayList();
		try {
			List saving = dao.getTotleSavingStat(beginDate,endDate,statType);
			if ("bydate".equals(statType)){
				for (int i=0 ;i<saving.size();i++){
					Object[] objects = (Object[])saving.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("transferamt",objects[1]);
					accMap.put("cashamt",objects[2]);
					accMap.put("posamt",objects[3]);
					accMap.put("outlayamt",objects[5]);
					accMap.put("ticketamt",objects[4]);
					accMap.put("transfernum",objects[6]);
					accMap.put("cashnum",objects[7]);
					accMap.put("posnum",objects[8]);
					//accMap.put("ticketnum",getTicketFillNumByDate(convert(objects[0]),2));//支票
					//accMap.put("outlaynum",getTicketFillNumByDate(convert(objects[0]),3));//经费本
					accMap.put("week",DateUtilExtend.getWeekByDate(convert(objects[0])));
					accMap.put("sysdate",new Integer((int)DateUtilExtend.diffDate(WebKeys.sysBeginDate,convert(objects[0]))+1));
					result.add(accMap);
				}
			}else if ("byweek".equals(statType)){
				for (int i=0 ;i<saving.size();i++){
					Object[] objects = (Object[])saving.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("transferamt",objects[1]);
					accMap.put("cashamt",objects[2]);
					accMap.put("posamt",objects[3]);
					accMap.put("outlayamt",objects[5]);
					accMap.put("ticketamt",objects[4]);
					accMap.put("transfernum",objects[6]);
					accMap.put("cashnum",objects[7]);
					accMap.put("posnum",objects[8]);
					//accMap.put("ticketnum",getTicketFillNumByDate(convert(objects[0]),2));//支票
					//accMap.put("outlaynum",getTicketFillNumByDate(convert(objects[0]),3));//经费本
					result.add(accMap);
				}
			}else{
				for (int i=0 ;i<saving.size();i++){
					Object[] objects = (Object[])saving.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("transferamt",objects[1]);
					accMap.put("cashamt",objects[2]);
					accMap.put("posamt",objects[3]);
					accMap.put("outlayamt",getTicketFillMoneyByMonth(convert(objects[0]),3));
					accMap.put("ticketamt",getTicketFillMoneyByMonth(convert(objects[0]),2));
					accMap.put("transfernum",objects[6]);
					accMap.put("cashnum",objects[7]);
					accMap.put("posnum",objects[8]);
					//accMap.put("ticketnum",getTicketFillNumByMonth(convert(objects[0]),2));//支票
					//accMap.put("outlaynum",getTicketFillNumByMonth(convert(objects[0]),3));//经费本
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
	 * 经费本和支票充值情况对比
	 * 2006-6-5
	 * hjw
	 * @param
	 * @return
	 */
	public static List getBillTotleSavingStat(String beginDate,String endDate,String statType) {
		ReportActiveDAO dao = ReportActiveDAO.getInstance();
		List result = new ArrayList();
		try {
			List saving = dao.getBillTotleSavingStat(beginDate,endDate,statType);
			if ("bydate".equals(statType)){
				for (int i=0 ;i<saving.size();i++){
					Object[] objects = (Object[])saving.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("ticketnum",objects[1]);
					accMap.put("outlaynum",objects[2]);
					accMap.put("ticketmoney",objects[3]);
					accMap.put("outlaymoney",objects[4]);
					accMap.put("week",DateUtilExtend.getWeekByDate(objects[0].toString()));
					accMap.put("sysdate",new Integer((int)DateUtilExtend.diffDate(WebKeys.sysBeginDate,objects[0].toString())+1));
					result.add(accMap);
				}
			}else{
				for (int i=0 ;i<saving.size();i++){
					Object[] objects = (Object[])saving.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("ticketnum",objects[1]);
					accMap.put("outlaynum",objects[2]);
					accMap.put("ticketmoney",objects[3]);
					accMap.put("outlaymoney",objects[4]);
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
	 * 圈存成功率统计
	 * 2006-6-6
	 * hjw
	 * @param
	 * @return
	 */
	public static List getTransferSuccessRate(String beginDate,String endDate, String statType){
		ReportActiveDAO dao = ReportActiveDAO.getInstance();
		List result = new ArrayList();
		try {
			List saving = dao.getTransferSuccessRate(beginDate,endDate,statType);
			if ("bydate".equals(statType)){
				for (int i=0 ;i<saving.size();i++){
					Object[] objects = (Object[])saving.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("account",objects[1]);
					accMap.put("inaccount",objects[2]);
					accMap.put("rate",objects[3]);
					accMap.put("week",DateUtilExtend.getWeekByDate(objects[0].toString()));
					accMap.put("sysdate",new Integer((int)DateUtilExtend.diffDate(WebKeys.sysBeginDate,objects[0].toString())+1));
					result.add(accMap);
				}
			}else{
				for (int i=0 ;i<saving.size();i++){
					Object[] objects = (Object[])saving.get(i);
					HashMap accMap = new HashMap();
					accMap.put("balance_date",objects[0]);
					accMap.put("account",objects[1]);
					accMap.put("inaccount",objects[2]);
					accMap.put("rate",objects[3]);
					result.add(accMap);
				}
			}
			return result;
		} catch (Exception he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}
	public static String getTicketFillNumByDate(String date,int type){
		TicketDAO ticketdao = TicketDAO.getInstance();
		try {
			return ticketdao.getTicketFillNumByDate(date,type);
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
			closeSession();
		}
	}
	public static String getTicketFillNumByMonth(String date,int type){
		TicketDAO ticketdao = TicketDAO.getInstance();
		try {
			return ticketdao.getTicketFillNumByMonth(date,type);
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
			closeSession();
		}
	}
	public static String getTicketFillMoneyByDate(String date,int type){
		TicketDAO ticketdao = TicketDAO.getInstance();
		try {
			return ticketdao.getTicketFillMoneyByDate(date,type);
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
			closeSession();
		}
	}
	public static String getTicketFillMoneyByMonth(String date,int type){
		TicketDAO ticketdao = TicketDAO.getInstance();
		try {
			return ticketdao.getTicketFillMoneyByMonth(date,type);
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
			closeSession();
		}
	}
	
	private static String convert(Object obj){
		if (obj==null){
			return "";
		}else{
			return obj.toString();
		}
	}

}
