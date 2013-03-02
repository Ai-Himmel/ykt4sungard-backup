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
		 * Return: boolean�޿�ǩ����״̬Ϊ3<br>
		 * Modify History: <br>
		 * ��������    ������     ����ʱ��       ��������<br>
		 * ======================================<br>
		 *  ����      ����ΰ     2006-4-18  <br>
		 * @author   ����ΰ
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
	 * Description: SignUtil��٣�״̬Ϊ2<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-18  <br>
	 * @author   ����ΰ
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
	 * Description: SignUtilȡ�����<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-29  <br>
	 * @author   ����ΰ
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
	 * Description: SignUtil���ǩ����״̬Ϊ4<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-18  <br>
	 * @author   ����ΰ
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
		 * Description: SignUtil�Ƿ��Ѿ�ǩ��<br>
		 * Return: boolean<br>
		 * Modify History: <br>
		 * ��������    ������     ����ʱ��       ��������<br>
		 * ======================================<br>
		 *  ����      ����ΰ     2006-4-29  <br>
		 * @author   ����ΰ
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
	 * Description: SignUtil���ݻ�����ȡ�û�����Ϣ<br>
	 * Return: TConference<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-19  <br>
	 * @author   ����ΰ
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
	 * Description: SignUtil���ݻ�����ȡ�������Ա������<br>
	 * Return: int<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-19  <br>
	 * @author   ����ΰ
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
	 * Description: SignUtil���ݻ�����ȡ��ʵ��ǩ��������<br>
	 * Return: int<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-19  <br>
	 * @author   ����ΰ
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
	 * Description: SignUtil���ݻ�����ȡ������ǩ�������б�(1,3����ǩ��)<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-19  <br>
	 * @author   ����ΰ
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
	 * Description: SignUtil���ݻ�����ȡ��δ�������б�(0Ĭ��)<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-19  <br>
	 * @author   ����ΰ
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
	 * Description: SignUtil���ݻ�����ȡ����������б�(2���)<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-19  <br>
	 * @author   ����ΰ
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
	 * Description: SignUtil���ݻ�����ȡ�����ǩ�������б�(4���ǩ��)<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-19  <br>
	 * @author   ����ΰ
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
	 * ��������ͳ��Ӧ��������ʵ������
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
