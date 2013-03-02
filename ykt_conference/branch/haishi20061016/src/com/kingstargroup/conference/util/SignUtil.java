package com.kingstargroup.conference.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.Transaction;

import com.kingstargroup.conference.common.DateUtilExtend;
import com.kingstargroup.conference.dao.SignDAO;
import com.kingstargroup.conference.hibernate.form.TAttendeeList;
import com.kingstargroup.conference.hibernate.form.TConference;

/**
 * @author hjw
 *
 */
public class SignUtil extends BasicUtil{
		
		/**
		 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
		 * File name: .java<br>
		 * Description: SignUtil<br>
		 * Return: boolean无卡签到，状态为3<br>
		 * Modify History: <br>
		 * 操作类型    操作人     操作时间       操作内容<br>
		 * ======================================<br>
		 *  创建      韩纪伟     2006-4-18  <br>
		 * @author   韩纪伟
		 * @version 
		 * @since 1.0
		 */
	public static boolean attendeeNoCardSign(
			int confid,
			int custid,
			String signtime){
		SignDAO dao = SignDAO.getInstance();
		Transaction t = beginTransaction();
		String getDate = DateUtilExtend.getNowDate2();
		
		try {
			Iterator iter = dao.getCustListBy(confid,custid).iterator();
			while (iter.hasNext()){
				TAttendeeList att = (TAttendeeList)iter.next();
				att.setAttendSign("3");
				att.setAttendDate(getDate);
				att.setAttendTime(signtime+"00");
				dao.saveOrUpdate(att);
			}			
			t.commit();
			return true;
		} catch (HibernateException he) {
			t.rollback();
			he.printStackTrace();
			return false;
		}finally{
			closeSession();
		}
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignUtil请假，状态为2<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-18  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public static boolean attendeeLeave(
			int confid,
			int custid,
			String leavereason){
		SignDAO dao = SignDAO.getInstance();
		Transaction t = beginTransaction();
		String getDate = DateUtilExtend.getNowDate2();
		String getTime = DateUtilExtend.getNowTime();
		try {
			Iterator iter = dao.getCustListBy(confid,custid).iterator();
			while (iter.hasNext()){
				TAttendeeList att = (TAttendeeList)iter.next();
				att.setAttendSign("2");
				att.setLeaveReason(leavereason);
				att.setAttendDate(getDate);
				att.setAttendTime(getTime);
				dao.saveOrUpdate(att);
			}			
			t.commit();
			return true;
		} catch (HibernateException he) {
			t.rollback();
			he.printStackTrace();
			return false;
		}finally{
			closeSession();
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignUtil取消请假<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-29  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public static boolean attendeeCancleLeave(
			int confid,
			int custid){
		SignDAO dao = SignDAO.getInstance();
		Transaction t = beginTransaction();
		String getDate = DateUtilExtend.getNowDate2();
		String getTime = DateUtilExtend.getNowTime();
		try {
			Iterator iter = dao.getCustListBy(confid,custid).iterator();
			while (iter.hasNext()){
				TAttendeeList att = (TAttendeeList)iter.next();
				att.setAttendSign("0");
				att.setLeaveReason("");
				att.setAttendDate(getDate);
				att.setAttendTime(getTime);
				dao.saveOrUpdate(att);
			}			
			t.commit();
			return true;
		} catch (HibernateException he) {
			t.rollback();
			he.printStackTrace();
			return false;
		}finally{
			closeSession();
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignUtil替代签到，状态为4<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-18  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public static boolean attendeeReplace(
			int confid,
			int custid,
			String repid,
			String repname,
			String repdept,
			String repduty,
			String comments,
			String signtime){
		SignDAO dao = SignDAO.getInstance();
		Transaction t = beginTransaction();
		String getDate = DateUtilExtend.getNowDate2();
		try {
			Iterator iter = dao.getCustListBy(confid,custid).iterator();
			while (iter.hasNext()){
				TAttendeeList att = (TAttendeeList)iter.next();
				att.setAttendSign("4");
				att.setAttendDate(getDate);
				att.setAttendTime(signtime+"00");
				att.setReplacerId(repid);
				att.setReplacerName(repname);
				att.setReplacerDept(repdept);
				att.setReplacerDuty(repduty);
				att.setReplacerComments(comments);
				dao.saveOrUpdate(att);
			}			
			t.commit();
			return true;
		} catch (HibernateException he) {
			t.rollback();
			he.printStackTrace();
			return false;
		}finally{
			closeSession();
		}
	}
	
		/**
		 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
		 * File name: .java<br>
		 * Description: SignUtil是否已经签到<br>
		 * Return: boolean<br>
		 * Modify History: <br>
		 * 操作类型    操作人     操作时间       操作内容<br>
		 * ======================================<br>
		 *  创建      韩纪伟     2006-4-29  <br>
		 * @author   韩纪伟
		 * @version 
		 * @since 1.0
		 */
	public static boolean getSignedOrNot(int confid,int custid){
		SignDAO dao = SignDAO.getInstance();
		try {
			return dao.getSignedOrNot(confid,custid);
		} catch (HibernateException he) {
			return true;
		}

	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignUtil根据会议编号取得会议信息<br>
	 * Return: TConference<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-19  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public static TConference getConfInfoById(int confid){
		SignDAO dao = SignDAO.getInstance();
		try {
			return dao.getConfInfoById(confid);
		} catch (HibernateException he) {
			return null;
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignUtil根据会议编号取得与会人员总人数<br>
	 * Return: int<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-19  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public static int getConfTotleAttendeeByCofid(int confid){
		SignDAO dao = SignDAO.getInstance();
		int totlenum=0;
		try {
			totlenum = dao.getConfTotleAttendeeByCofid(confid);
		} catch (HibernateException he) {
			
		}finally{
			closeSession();
		}
		return totlenum;
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignUtil根据会议编号取得实际签到总人数<br>
	 * Return: int<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-19  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public static int getSignedNumByCofid(int confid){
		SignDAO dao = SignDAO.getInstance();
		int factnum=0;
		try {
			factnum = dao.getSignedNumByCofid(confid);
		} catch (HibernateException he) {
			
		}finally{
			closeSession();
		}
		return factnum;
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignUtil根据会议编号取得正常签到人数列表(1,3正常签到)<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-19  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public static List getSignedNumByConfid(int confid){
		SignDAO dao = SignDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getSignedNumByConfid(confid);
			for (int i=0, l=list.size();i<l;i++){
				Object[] objects = (Object[]) list.get(i);
				HashMap map = new HashMap();
				map.put("cutId",convent(objects[0]));
				map.put("cutName", convent(objects[1]));
				map.put("stuempNo", convent(objects[2]));
				map.put("dutyName", convent(objects[3]));				
				map.put("deptName",convent(objects[4]));
				map.put("attendDate",convent(objects[5]));
				map.put("attendTime",convent(objects[6]));
				result.add(map);
			}
			return result;
		} catch (HibernateException he) {
			return null;
		}finally{
			closeSession();
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignUtil根据会议编号取得未到人数列表(0默认)<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-19  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public static List getUnSignNumByConfid(int confid){
		SignDAO dao = SignDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getUnSignNumByConfid(confid);
			for (int i=0, l=list.size();i<l;i++){
				Object[] objects = (Object[]) list.get(i);
				HashMap map = new HashMap();
				map.put("cutId",convent(objects[0]));
				map.put("cutName", convent(objects[1]));
				map.put("stuempNo", convent(objects[2]));
				map.put("dutyName", convent(objects[3]));				
				map.put("deptName",convent(objects[4]));
				map.put("attendDate",convent(objects[5]));
				map.put("attendTime",convent(objects[6]));
				result.add(map);
			}
			return result;
		} catch (HibernateException he) {
			return null;
		}finally{
			closeSession();
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignUtil根据会议编号取得请假人数列表(2请假)<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-19  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public static List getLeaveNumByConfid(int confid){
		SignDAO dao = SignDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getLeaveNumByConfid(confid);
			for (int i=0, l=list.size();i<l;i++){
				Object[] objects = (Object[]) list.get(i);
				HashMap map = new HashMap();
				map.put("cutId",convent(objects[0]));
				map.put("cutName", convent(objects[1]));
				map.put("stuempNo", convent(objects[2]));
				map.put("dutyName", convent(objects[3]));				
				map.put("deptName",convent(objects[4]));
				map.put("attendDate",convent(objects[5]));
				map.put("attendTime",convent(objects[6]));
				result.add(map);
			}
			return result;
		} catch (HibernateException he) {
			return null;
		}finally{
			closeSession();
		}
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignUtil根据会议编号取得替代签到人数列表(4替代签到)<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-19  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public static List getReplaceNumByConfid(int confid){
		SignDAO dao = SignDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getReplaceNumByConfid(confid);
			for (int i=0, l=list.size();i<l;i++){
				Object[] objects = (Object[]) list.get(i);
				HashMap map = new HashMap();
				map.put("cutId",convent(objects[0]));
				map.put("cutName", convent(objects[1]));
				map.put("stuempNo", convent(objects[2]));
				map.put("dutyName", convent(objects[3]));				
				map.put("deptName",convent(objects[4]));
				map.put("attendDate",convent(objects[5]));
				map.put("attendTime",convent(objects[6]));
				map.put("repName",convent(objects[7]));
				map.put("repDuty",convent(objects[8]));
				result.add(map);
			}
			return result;
		} catch (HibernateException he) {
			return null;
		}finally{
			closeSession();
		}
	}
	
	/**
	 * 按代表团统计应到人数和实到人数
	 * 2006-6-13
	 * hjw
	 * @param
	 * @return
	 */
	public static List getDelegrayListByConfid(int confid){
		SignDAO dao = SignDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getDelegrayListByConfid(confid);
			for (int i=0, l=list.size();i<l;i++){
				Object[] objects = (Object[]) list.get(i);
				HashMap map = new HashMap();
				map.put("delegray",convent(objects[0]));
				map.put("attendee", convent(objects[1]));
				map.put("fact", convent(objects[2]));
				result.add(map);
			}
			return result;
		} catch (HibernateException he) {
			return null;
		}finally{
			closeSession();
		}
	}

	private static String convent (Object ss){
		if (null==ss){
			return "";
		}else{
			return ss.toString();
		}
	}

}
