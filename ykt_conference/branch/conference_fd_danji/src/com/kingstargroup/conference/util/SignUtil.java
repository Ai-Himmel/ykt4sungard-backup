package com.kingstargroup.conference.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.Transaction;

import com.kingstargroup.conference.common.DateUtilExtend;
import com.kingstargroup.conference.dao.AttendeeGroupDAO;
import com.kingstargroup.conference.dao.ConferenceDAO;
import com.kingstargroup.conference.dao.SignDAO;
import com.kingstargroup.conference.hibernate.form.TAttendeeList;
import com.kingstargroup.conference.hibernate.form.TConference;
import com.kingstargroup.conference.hibernate.form.TRecordhis;

/**
 * @author hjw
 * 
 */
public class SignUtil extends BasicUtil {

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignUtil<br>
	 * Return: boolean�޿�ǩ����״̬Ϊ12�޿�ǩ��,22�޿�ǩ�����ٵ���<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-18 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static boolean attendeeNoCardSign(int confid, String[] custid,
			String signtime) {
		SignDAO dao = SignDAO.getInstance();
		ConferenceDAO confDao = ConferenceDAO.getInstance();
		Transaction t = beginTransaction();
		String getDate = DateUtilExtend.getNowDate2();

		try {
			String nowtime = DateUtilExtend.getNowDate2()
					+ DateUtilExtend.getNowTime2();
			String meetTime = "";
			TConference conf = confDao.getConference(confid);
			meetTime = conf.getConBegindate() + conf.getConBegintime();
			for (int i = 0; i < custid.length; i++) {
				Iterator iter = dao.getCustListBy(confid,
						Integer.parseInt(custid[i])).iterator();
				while (iter.hasNext()) {
					TAttendeeList att = (TAttendeeList) iter.next();
					if (nowtime.compareTo(meetTime) >= 0) {
						// �ٵ�
						att.setAttendSign("22");
					}
					if (nowtime.compareTo(meetTime) < 0) {
						// ����
						att.setAttendSign("12");
					}
					att.setAttendDate(getDate);
					att.setAttendTime(signtime);
					dao.saveOrUpdate(att);
				}
			}

			t.commit();
			return true;
		} catch (HibernateException he) {
			t.rollback();
			he.printStackTrace();
			return false;
		} finally {
			closeSession();
		}
	}
	
	public static boolean attendeeNoCardUnSign(int confid, String[] custid,
			String signtime) {
		SignDAO dao = SignDAO.getInstance();
		Transaction t = beginTransaction();
		try {

			for (int i = 0; i < custid.length; i++) {
				Iterator iter = dao.getCustListBy(confid,
						Integer.parseInt(custid[i])).iterator();
				while (iter.hasNext()) {
					TAttendeeList att = (TAttendeeList) iter.next();					
					att.setAttendSign("00");
					att.setAttendDate(null);
					att.setAttendTime(null);
					dao.saveOrUpdate(att);
				}
			}

			t.commit();
			return true;
		} catch (HibernateException he) {
			t.rollback();
			he.printStackTrace();
			return false;
		} finally {
			closeSession();
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignUtil��٣�״̬Ϊ30<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-18 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static boolean attendeeLeave(int confid, int custid,
			String leavereason) {
		SignDAO dao = SignDAO.getInstance();
		Transaction t = beginTransaction();
		String getDate = DateUtilExtend.getNowDate2();
		String getTime = DateUtilExtend.getNowTime();
		try {
			Iterator iter = dao.getCustListBy(confid, custid).iterator();
			while (iter.hasNext()) {
				TAttendeeList att = (TAttendeeList) iter.next();
				att.setAttendSign("30");
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
		} finally {
			closeSession();
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignUtilȡ�����<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-29 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static boolean attendeeCancleLeave(int confid, int custid) {
		SignDAO dao = SignDAO.getInstance();
		Transaction t = beginTransaction();
		String getDate = DateUtilExtend.getNowDate2();
		String getTime = DateUtilExtend.getNowTime();
		try {
			Iterator iter = dao.getCustListBy(confid, custid).iterator();
			while (iter.hasNext()) {
				TAttendeeList att = (TAttendeeList) iter.next();
				att.setAttendSign("00");
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
		} finally {
			closeSession();
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignUtil���ǩ����״̬Ϊ4<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-18 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static boolean attendeeReplace(int confid, int custid, String repid,
			String repname, String repdept, String repduty, String comments,
			String signtime) {
		SignDAO dao = SignDAO.getInstance();
		ConferenceDAO confDao = ConferenceDAO.getInstance();
		Transaction t = beginTransaction();
		String getDate = DateUtilExtend.getNowDate2();
		try {

			String nowtime = DateUtilExtend.getNowDate2()
					+ DateUtilExtend.getNowTime2();
			String meetTime = "";
			TConference conf = confDao.getConference(confid);
			meetTime = conf.getConBegindate() + conf.getConBegintime();

			Iterator iter = dao.getCustListBy(confid, custid).iterator();
			while (iter.hasNext()) {
				TAttendeeList att = (TAttendeeList) iter.next();
				if (nowtime.compareTo(meetTime) >= 0) {
					// �ٵ�
					att.setAttendSign("23");
				}
				if (nowtime.compareTo(meetTime) < 0) {
					// ����
					att.setAttendSign("13");
				}
				att.setAttendDate(getDate);
				att.setAttendTime(signtime);
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
		} finally {
			closeSession();
		}
	}
	
	public static boolean attendeeUnReplace(int confid, int custid) {
		SignDAO dao = SignDAO.getInstance();
		Transaction t = beginTransaction();
		try {
			Iterator iter = dao.getCustListBy(confid, custid).iterator();
			while (iter.hasNext()) {
				TAttendeeList att = (TAttendeeList) iter.next();
				att.setAttendSign("00");
				att.setAttendDate(null);
				att.setAttendTime(null);
				att.setReplacerId(null);
				att.setReplacerName(null);
				att.setReplacerDept(null);
				att.setReplacerDuty(null);
				att.setReplacerComments(null);
				dao.saveOrUpdate(att);
			}
			t.commit();
			return true;
		} catch (HibernateException he) {
			t.rollback();
			he.printStackTrace();
			return false;
		} finally {
			closeSession();
		}
	}


	public static boolean attendeeReplacebyhand(int confid, String custidA,
			String custidB) {
		SignDAO dao = SignDAO.getInstance();
		ConferenceDAO confDao = ConferenceDAO.getInstance();
		AttendeeGroupDAO groupDao = AttendeeGroupDAO.getInstance();
		Transaction t = beginTransaction();
		try {
			String meetTime = "";
			List custlist = groupDao.getCustInfobyids(confid, custidB);
			TRecordhis his = groupDao.getRecordhis(confid, custidB);
			String tempid = "";
			String hisid = "";
			if (his != null) {
				TConference conf = confDao.getConference(confid);
				meetTime = conf.getConBegindate() + conf.getConBegintime();
				Iterator iter = dao.getCustListBy(confid,
						Integer.parseInt(custidA)).iterator();				
				hisid =  his.getConfid().toString();
				while (iter.hasNext()) {
					TAttendeeList att = (TAttendeeList) iter.next();
					tempid = att.getId().getConId().toString();
					if (tempid.equals(hisid)) {
						if (his.getChecktime().substring(9).compareTo(meetTime) >= 0) {
							// �ٵ�
							att.setAttendSign("23");
						}
						if (his.getChecktime().substring(9).compareTo(meetTime) < 0) {
							// ����
							att.setAttendSign("13");
						}
						att.setAttendDate(his.getChecktime().substring(0, 8));
						att.setAttendTime(his.getChecktime().substring(8));
						att.setReplacerId(custidB);
						if (custlist.size() > 0) {
							Object[] cust = (Object[]) custlist.get(0);
							att.setReplacerName(convent(cust[1]));
							att.setReplacerDept(convent(cust[4]));
							att.setReplacerDuty(convent(cust[3]));
						}
						dao.saveOrUpdate(att);
					}
				}
				if (tempid.equals(hisid)) {
					his.setDealornot("1");
					dao.saveOrUpdate(his);
				}
			}
			t.commit();
			if(tempid.equals(hisid)){
				return true;
			}else{
				return false;
			}
		} catch (HibernateException he) {
			t.rollback();
			he.printStackTrace();
			return false;
		} catch (Exception e) {
			t.rollback();
			e.printStackTrace();
			return false;
		} finally {
			closeSession();
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignUtil�Ƿ��Ѿ�ǩ��<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-29 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static boolean getSignedOrNot(int confid, int custid) {
		SignDAO dao = SignDAO.getInstance();
		try {
			return dao.getSignedOrNot(confid, custid);
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
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-19 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static TConference getConfInfoById(int confid) {
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
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-19 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static int getConfTotleAttendeeByCofid(int confid) {
		SignDAO dao = SignDAO.getInstance();
		int totlenum = 0;
		try {
			totlenum = dao.getConfTotleAttendeeByCofid(confid);
		} catch (HibernateException he) {

		} finally {
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
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-19 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static int getSignedNumByCofid(int confid) {
		SignDAO dao = SignDAO.getInstance();
		int factnum = 0;
		try {
			factnum = dao.getSignedNumByCofid(confid);
		} catch (HibernateException he) {

		} finally {
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
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-19 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static List getSignedNumByConfid(int confid) {
		SignDAO dao = SignDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getSignedNumByConfid(confid);
			for (int i = 0, l = list.size(); i < l; i++) {
				Object[] objects = (Object[]) list.get(i);
				String dutyName = convent(objects[3]);
				if(i+1<l){
					Object[] objects1 = (Object[]) list.get(i+1);
					if(convent(objects[0]).equals(convent(objects1[0]))){
						dutyName += ","+convent(objects1[3]);
						i++;
						for(int j=i+1;j<l;j++){
							objects1 = (Object[]) list.get(j);
							if(convent(objects[0]).equals(convent(objects1[0]))){
								dutyName += ","+convent(objects1[3]);
								i++;
								continue;
							}else{
								break;
							}
						}						
					}
				}
				
				HashMap map = new HashMap();
				map.put("cutId", convent(objects[0]));
				map.put("cutName", convent(objects[1]));
				map.put("stuempNo", convent(objects[2]));
				map.put("dutyName", dutyName);
				map.put("deptName", convent(objects[4]));
				map.put("attendDate", convent(objects[5]));
				map.put("attendTime", convent(objects[6]));
				result.add(map);
			}
			return result;
		} catch (HibernateException he) {
			return null;
		} finally {
			closeSession();
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignUtil���ݻ�����ȡ��δ�������б�(00Ĭ��)<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-19 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static List getUnSignNumByConfid(int confid) {
		SignDAO dao = SignDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getUnSignNumByConfid(confid);
			for (int i = 0, l = list.size(); i < l; i++) {
				
				Object[] objects = (Object[]) list.get(i);
				String dutyName = convent(objects[3]);
				if(i+1<l){
					Object[] objects1 = (Object[]) list.get(i+1);
					if(convent(objects[0]).equals(convent(objects1[0]))){
						dutyName += ","+convent(objects1[3]);
						i++;
						for(int j=i+1;j<l;j++){
							objects1 = (Object[]) list.get(j);
							if(convent(objects[0]).equals(convent(objects1[0]))){
								dutyName += ","+convent(objects1[3]);
								i++;
								continue;
							}else{
								break;
							}
						}						
					}
				}
				
				HashMap map = new HashMap();
				map.put("cutId", convent(objects[0]));
				map.put("cutName", convent(objects[1]));
				map.put("stuempNo", convent(objects[2]));
				map.put("dutyName", dutyName);
				map.put("deptName", convent(objects[4]));
				map.put("attendDate", convent(objects[5]));
				map.put("attendTime", convent(objects[6]));
				result.add(map);
			}
			return result;
		} catch (HibernateException he) {
			return null;
		} finally {
			closeSession();
		}
	}
	
	public static List getUnSignNumByConfidCount(int confid) {
		SignDAO dao = SignDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getUnSignNumByConfidCount(confid);
			for (int i = 0, l = list.size(); i < l; i++) {				
				Object[] objects = (Object[]) list.get(i);				
				HashMap map = new HashMap();
				map.put("cutId", convent(objects[0]));
				map.put("attendDate", convent(objects[1]));
				map.put("attendTime", convent(objects[2]));
				result.add(map);
			}
			return result;
		} catch (HibernateException he) {
			return null;
		} finally {
			closeSession();
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignUtil���ݻ�����ȡ����������б�(30���)<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-19 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static List getLeaveNumByConfid(int confid) {
		SignDAO dao = SignDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getLeaveNumByConfid(confid);
			for (int i = 0, l = list.size(); i < l; i++) {
				Object[] objects = (Object[]) list.get(i);
				String dutyName = convent(objects[3]);
				if(i+1<l){
					Object[] objects1 = (Object[]) list.get(i+1);
					if(convent(objects[0]).equals(convent(objects1[0]))){
						dutyName += ","+convent(objects1[3]);
						i++;
						for(int j=i+1;j<l;j++){
							objects1 = (Object[]) list.get(j);
							if(convent(objects[0]).equals(convent(objects1[0]))){
								dutyName += ","+convent(objects1[3]);
								i++;
								continue;
							}else{
								break;
							}
						}						
					}
				}
				
				HashMap map = new HashMap();
				map.put("cutId", convent(objects[0]));
				map.put("cutName", convent(objects[1]));
				map.put("stuempNo", convent(objects[2]));
				map.put("dutyName", dutyName);
				map.put("deptName", convent(objects[4]));
				map.put("attendDate", convent(objects[5]));
				map.put("attendTime", convent(objects[6]));
				result.add(map);
			}
			return result;
		} catch (HibernateException he) {
			return null;
		} finally {
			closeSession();
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignUtil���ݻ�����ȡ�����ǩ�������б�(13���ǩ��,23���ǩ��(�ٵ�))<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-19 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static List getReplaceNumByConfid(int confid) {
		SignDAO dao = SignDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getReplaceNumByConfid(confid);
			for (int i = 0, l = list.size(); i < l; i++) {
				Object[] objects = (Object[]) list.get(i);
				String dutyName = convent(objects[3]);
				if(i+1<l){
					Object[] objects1 = (Object[]) list.get(i+1);
					if(convent(objects[0]).equals(convent(objects1[0]))){
						dutyName += ","+convent(objects1[3]);
						i++;
						for(int j=i+1;j<l;j++){
							objects1 = (Object[]) list.get(j);
							if(convent(objects[0]).equals(convent(objects1[0]))){
								dutyName += ","+convent(objects1[3]);
								i++;
								continue;
							}else{
								break;
							}
						}						
					}
				}
				
				HashMap map = new HashMap();
				map.put("cutId", convent(objects[0]));
				map.put("cutName", convent(objects[1]));
				map.put("stuempNo", convent(objects[2]));
				map.put("dutyName", dutyName);
				map.put("deptName", convent(objects[4]));
				map.put("attendDate", convent(objects[5]));
				map.put("attendTime", convent(objects[6]));
				map.put("repName", convent(objects[7]));
				map.put("repDuty", convent(objects[8]));
				result.add(map);
			}
			return result;
		} catch (HibernateException he) {
			return null;
		} finally {
			closeSession();
		}
	}

	/**
	 * ��������ͳ��Ӧ��������ʵ������ 2006-6-13 hjw
	 * 
	 * @param
	 * @return
	 */
	public static List getDelegrayListByConfid(int confid) {
		SignDAO dao = SignDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getDelegrayListByConfid(confid);
			for (int i = 0, l = list.size(); i < l; i++) {
				Object[] objects = (Object[]) list.get(i);
				HashMap map = new HashMap();
				map.put("delegray", convent(objects[0]));
				map.put("dlgtName", "".equals(convent(objects[1]))?"����":convent(objects[1]));
				map.put("attendee", convent(objects[2]));
				map.put("fact", convent(objects[3])==""?"0":convent(objects[3]));
				int total = Integer.parseInt(convent(objects[2]));
				int checked = Integer.parseInt(convent(objects[3])==""?"0":convent(objects[3])) * 100;
				if (total > 0) {
					map.put("ratio", String.valueOf(checked / total));
				} else {
					map.put("ratio", "100");
				}				
				result.add(map);
			}
			

			int totlenum = 0;
				totlenum = dao.getConfTotleAttendeeByCofid(confid);
			int factnum = 0;
					factnum = dao.getSignedNumByCofid(confid);
			HashMap map = new HashMap();
			map.put("delegray", "-1");
			map.put("dlgtName", "�ܼ�");
			map.put("attendee", String.valueOf(totlenum));
			map.put("fact", String.valueOf(factnum));
			if (totlenum > 0) {
				map.put("ratio", String.valueOf(factnum *100 / totlenum));
			} else {
				map.put("ratio", "100");
			}	
			result.add(map);
			return result;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}
	
	public static List getDelegrayListByConfidspit(int confid,int flag) {
		SignDAO dao = SignDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getDelegrayListByConfid(confid);
			if(1==flag){
				for (int i = 0, l = list.size(); i < l; i++) {
					if(i%2!=0){
						continue;
					}
					Object[] objects = (Object[]) list.get(i);
					HashMap map = new HashMap();
					map.put("delegray", convent(objects[0]));
					map.put("dlgtName", "".equals(convent(objects[1]))?"����":convent(objects[1]));
					map.put("attendee", convent(objects[2]));
					map.put("fact", convent(objects[3])==""?"0":convent(objects[3]));
					int total = Integer.parseInt(convent(objects[2]));
					int checked = Integer.parseInt(convent(objects[3])==""?"0":convent(objects[3])) * 100;
					if (total > 0) {
						map.put("ratio", String.valueOf(checked / total));
					} else {
						map.put("ratio", "100");
					}				
					result.add(map);
				}
			}else{
				for (int i = 0, l = list.size(); i < l; i++) {
					if(i%2==0){
						continue;
					}
					Object[] objects = (Object[]) list.get(i);
					HashMap map = new HashMap();
					map.put("delegray", convent(objects[0]));
					map.put("dlgtName", "".equals(convent(objects[1]))?"����":convent(objects[1]));
					map.put("attendee", convent(objects[2]));
					map.put("fact", convent(objects[3])==""?"0":convent(objects[3]));
					int total = Integer.parseInt(convent(objects[2]));
					int checked = Integer.parseInt(convent(objects[3])==""?"0":convent(objects[3])) * 100;
					if (total > 0) {
						map.put("ratio", String.valueOf(checked / total));
					} else {
						map.put("ratio", "100");
					}				
					result.add(map);
				}
				
				int totlenum = 0;
				totlenum = dao.getConfTotleAttendeeByCofid(confid);
			int factnum = 0;
					factnum = dao.getSignedNumByCofid(confid);
			HashMap map = new HashMap();
			map.put("delegray", "-1");
			map.put("dlgtName", "�ܼ�");
			map.put("attendee", String.valueOf(totlenum));
			map.put("fact", String.valueOf(factnum));
			if (totlenum > 0) {
				map.put("ratio", String.valueOf(factnum *100 / totlenum));
			} else {
				map.put("ratio", "100");
			}	
			result.add(map);
			}			

			
			return result;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	/**
	 * ��ʾ��������ϸ 2006-6-13 hlq
	 * 
	 * @param
	 * @return
	 */
	public static List getCustListByConfidandDlgt(int confid, String delegray) {
		SignDAO dao = SignDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getDelegrayListByConfid(confid, delegray);
			for (int i = 0, l = list.size(); i < l; i++) {
				Object[] objects = (Object[]) list.get(i);
				HashMap map = new HashMap();
				map.put("cutId", new Integer(convent(objects[0])));
				map.put("cutName", convent(objects[1]));
				map.put("stuempNo", convent(objects[2]));
				map.put("dutyName", convent(objects[3]));
				map.put("deptName", convent(objects[4]));
				map.put("attendSign", GetDictionary
						.getAttendeeStatus(convent(objects[5])));
				map.put("attendDate", convent(objects[6]));
				map.put("attendTime", convent(objects[7]));
				result.add(map);
			}
			return result;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	private static String convent(Object ss) {
		if (null == ss) {
			return "";
		} else {
			return ss.toString();
		}
	}
	
//	ͨ��confid����ѯ�������ʱ��
	public static String getEndTimeByConid(int confid){
		SignDAO dao = SignDAO.getInstance();
		return dao.getEndTimeByConid(confid);
	}

}
