package com.kingstargroup.conference.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.Transaction;

import com.kingstargroup.conference.common.DateUtilExtend;
import com.kingstargroup.conference.dao.AttendeeDAO;
import com.kingstargroup.conference.dao.AttendeeGroupDAO;
import com.kingstargroup.conference.dao.ConferenceDAO;
import com.kingstargroup.conference.dao.DictionaryDAO;
import com.kingstargroup.conference.dao.SignDAO;
import com.kingstargroup.conference.hibernate.form.TAttendeeList;
import com.kingstargroup.conference.hibernate.form.TAttendeeListKey;
import com.kingstargroup.conference.hibernate.form.TCifCustomer;
import com.kingstargroup.conference.hibernate.form.TConference;
import com.kingstargroup.conference.hibernate.form.TPifCard;
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
	 * Return: boolean无卡签到，状态为12无卡签到,22无卡签到（迟到）<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-18 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static int attendeeNoCardSign(int confid, String[] custid,
			String signtime) {
		SignDAO dao = SignDAO.getInstance();
		ConferenceDAO confDao = ConferenceDAO.getInstance();
		Transaction t = beginTransaction();
		String getDate = DateUtilExtend.getNowDate2();
		int cout1 =0;
		int cout2=custid.length;
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
					if("00".equals(att.getAttendSign())){						
						if (nowtime.compareTo(meetTime) >= 0) {
							// 迟到
							att.setAttendSign("22");
						}
						if (nowtime.compareTo(meetTime) < 0) {
							// 正常
							att.setAttendSign("12");
						}
						att.setAttendDate(getDate);
						att.setAttendTime(signtime);
						dao.saveOrUpdate(att);
					}else{
						cout1++;
					}
				}
			}

			t.commit();
			if(cout1<cout2){
				return 1;
			}else{
				return 2;
			}
		} catch (HibernateException he) {
			t.rollback();
			he.printStackTrace();
			return 3;
		} finally {
			closeSession();
		}
	}
	//把需要上传的传到数据库
	public static boolean uploadSign(int confid,String[] custid, HashMap timemap){
		SignDAO dao = SignDAO.getInstance();
		AttendeeDAO attDao = AttendeeDAO.getInstance();
		ConferenceDAO confDao = ConferenceDAO.getInstance();
		Transaction t = beginTransaction();
		try {
			
			String meetTime = "";
			TConference conf = confDao.getConference(confid);
			meetTime = conf.getConBegindate() + conf.getConBegintime();
			for (int i = 0; i < custid.length; i++) {
				String signtime = String.valueOf(timemap.get(custid[i]));
				String getDate = DateUtilExtend.getNowDate2();
				String getTime =  DateUtilExtend.getNowTime();
				if (signtime.length() == 14) {
					getDate = signtime.substring(0, 8);
					getTime = signtime.substring(8);
				}
				
					TAttendeeListKey key = new TAttendeeListKey();
					key.setConId(new Integer(confid));
					key.setCustId(Integer.valueOf(custid[i]));
					//根据客户号取得该客户的卡号
					TPifCard card = attDao.getCardNoByCustId(Integer.parseInt(custid[i]
							.toString()));
					TCifCustomer customer = attDao.getCustomer(new Integer(custid[i]));
					TAttendeeList att = new  TAttendeeList(key);
					if (null != card) {
						att.setCardNo(card.getCardId());
					} else {
						att.setCardNo(new Integer(0));
					}
					if (signtime.compareTo(meetTime) >= 0) {
						// 迟到
						att.setAttendSign("21");
					}
					if (signtime.compareTo(meetTime) < 0) {
						// 正常
						att.setAttendSign("11");
					}
					att.setSendSign("0");// 是否下发，0未下发，1下发
					att.setDelSign("0");
					
					att.setAllotDate(getDate);
					att.setAllotTime(getTime);
					att.setAttendDate(getDate);
					att.setAttendTime(getTime);
					att.setCutName(customer.getCutName());
					att.setStuempNo(customer.getStuempNo());
					att.setSex(customer.getSex());
					att.setDeptName(DictionaryDAO.getInstance().getDeptName(
							customer.getClassdeptNo()));
					attDao.save(att);
				
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

	public static String attendeeOffLineSign(int confid, String[] custid,
			HashMap timemap) {
		SignDAO dao = SignDAO.getInstance();
		ConferenceDAO confDao = ConferenceDAO.getInstance();
		String  succPerson ="";
		Transaction t = beginTransaction();
		// String getDate = DateUtilExtend.getNowDate2();
        
		try {
			// String nowtime = DateUtilExtend.getNowDate2()
			// + DateUtilExtend.getNowTime2();
			String meetTime = "";
			TConference conf = confDao.getConference(confid);
			meetTime = conf.getConBegindate() + conf.getConBegintime();
			for (int i = 0; i < custid.length; i++) {
				String signtime = String.valueOf(timemap.get(custid[i]));
				String getDate = DateUtilExtend.getNowDate2();
				String getTime =  DateUtilExtend.getNowTime();
				if (signtime.length() == 14) {
					getDate = signtime.substring(0, 8);
					getTime = signtime.substring(8);
				}
				Iterator iter = dao.getCustListBy(confid,
						Integer.parseInt(custid[i])).iterator();
				while (iter.hasNext()) {
					TAttendeeList att = (TAttendeeList) iter.next();
					if (signtime.compareTo(meetTime) >= 0) {
						// 迟到
						att.setAttendSign("21");
					}
					if (signtime.compareTo(meetTime) < 0) {
						// 正常
						att.setAttendSign("11");
					}
					att.setAttendDate(getDate);
					att.setAttendTime(getTime);
					dao.saveOrUpdate(att);
					succPerson = succPerson + custid[i]+",";
				}
			}

			t.commit();
			return succPerson;
		} catch (HibernateException he) {
			t.rollback();
			he.printStackTrace();
			return succPerson;
		} finally {
			closeSession();
		}
	}

	public static int attendeeNoCardUnSign(int confid, String[] custid,
			String signtime) {
		SignDAO dao = SignDAO.getInstance();
		Transaction t = beginTransaction();
		int cout1 =0;
		int cout2=custid.length;
		try {

			for (int i = 0; i < custid.length; i++) {
				Iterator iter = dao.getCustListBy(confid,
						Integer.parseInt(custid[i])).iterator();
				while (iter.hasNext()) {
					TAttendeeList att = (TAttendeeList) iter.next();
					if("12".equals(att.getAttendSign())||"22".equals(att.getAttendSign())){
					att.setAttendSign("00");
					att.setAttendDate(null);
					att.setAttendTime(null);
					dao.saveOrUpdate(att);
					}else{
						cout1++;
					}
				}
			}

			t.commit();
			if(cout1<cout2){
				return 1;
			}else{
				return 2;
			}
		} catch (HibernateException he) {
			t.rollback();
			he.printStackTrace();
			return 3;
		} finally {
			closeSession();
		}
	}

	public static boolean attendeeOffLineUnSign(int confid, String[] custid) {
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
	 * Description: SignUtil请假，状态为30<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-18 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static int attendeeLeave(int confid, String[] custid ,
			String leavereason) {
		SignDAO dao = SignDAO.getInstance();
		Transaction t = beginTransaction();
		String getDate = DateUtilExtend.getNowDate2();
		String getTime = DateUtilExtend.getNowTime();
		int cout1 =0;
		int cout2=custid.length;
		try {
			for (int i = 0; i < custid.length; i++) {
				Iterator iter = dao.getCustListBy(confid, Integer.parseInt(custid[i])).iterator();
				while (iter.hasNext()) {
					TAttendeeList att = (TAttendeeList) iter.next();
					if(!"30".equals(att.getAttendSign())){
						att.setAttendSign("30");
						att.setLeaveReason(leavereason);
						att.setAttendDate(getDate);
						att.setAttendTime(getTime);
						dao.saveOrUpdate(att);
					}else{
						cout1++;
					}
				}
			}			
			t.commit();
			if(cout1<cout2){
				return 1;
			}else{
				return 2;
			}
		} catch (HibernateException he) {
			t.rollback();
			he.printStackTrace();
			return 3;
		} finally {
			closeSession();
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignUtil取消请假<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-29 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public static int attendeeCancleLeave(int confid, String[] custid) {
		SignDAO dao = SignDAO.getInstance();
		Transaction t = beginTransaction();
		String getDate = DateUtilExtend.getNowDate2();
		String getTime = DateUtilExtend.getNowTime();
		int cout1 =0;
		int cout2=custid.length;
		try {
			for (int i = 0; i < custid.length; i++) {
				Iterator iter = dao.getCustListBy(confid, Integer.parseInt(custid[i])).iterator();
				while (iter.hasNext()) {
					TAttendeeList att = (TAttendeeList) iter.next();
					if("30".equals(att.getAttendSign())){
						att.setAttendSign("00");
						att.setLeaveReason("");
						att.setAttendDate(getDate);
						att.setAttendTime(getTime);
						dao.saveOrUpdate(att);
					}else{
						cout2++;
					}
				}				
			}
			
			t.commit();
			if(cout1<cout2){
				return 1;
			}else{
				return 2;
			}
		} catch (HibernateException he) {
			t.rollback();
			he.printStackTrace();
			return 3;
		} finally {
			closeSession();
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignUtil替代签到，状态为4<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-18 <br>
	 * 
	 * @author 韩纪伟
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
					// 迟到
					att.setAttendSign("23");
				}
				if (nowtime.compareTo(meetTime) < 0) {
					// 正常
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
	
	public static boolean  attHasCardNoInfo(int confid,String custidB){
		SignDAO dao = SignDAO.getInstance();
		ConferenceDAO confDao = ConferenceDAO.getInstance();
		AttendeeGroupDAO groupDao = AttendeeGroupDAO.getInstance();
		Transaction t = beginTransaction();
		
		try {
			String meetTime = "";
			//客户信息
			List custlist = groupDao.getCustInfobyids(confid, custidB);
			//会议
			TConference conf = confDao.getConference(confid);
			//开会时间
			meetTime = conf.getConBegindate() + conf.getConBegintime();
			//打卡记录
			TRecordhis his = groupDao.getRecordhis(confid, custidB);
			
			TAttendeeList att = new TAttendeeList(); 
			TAttendeeListKey key = new TAttendeeListKey();
			key.setConId(new Integer(confid));
			key.setCustId(new Integer(custidB));
			att.setId(key);
			if (his.getChecktime().substring(9).compareTo(meetTime) >= 0) {
				// 迟到
				att.setAttendSign("21");
			}
			if (his.getChecktime().substring(9).compareTo(meetTime) < 0) {
				// 正常
				att.setAttendSign("11");
			}
			if (custlist.size() > 0) {
				Object[] cust = (Object[]) custlist.get(0);
				att.setCutName(convent(cust[1]));
				att.setStuempNo(convent(cust[2]));
				att.setDeptName(convent(cust[4]));
				
				att.setAllotDate(conf.getConBegindate());
				att.setAllotTime(conf.getConBegintime());
				
			}
			att.setAttendDate(his.getChecktime().substring(0, 8));
			att.setAttendTime(his.getChecktime().substring(8));
			att.setSendSign("0");
			att.setDelSign("0");
			dao.saveOrUpdate(att);
			his.setDealornot("1");
			dao.saveOrUpdate(his);
			t.commit();
			return true;
			
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
				hisid = his.getConfid().toString();
				while (iter.hasNext()) {
					TAttendeeList att = (TAttendeeList) iter.next();
					tempid = att.getId().getConId().toString();
					if (tempid.equals(hisid)) {
						if (his.getChecktime().substring(9).compareTo(meetTime) >= 0) {
							// 迟到
							att.setAttendSign("23");
						}
						if (his.getChecktime().substring(9).compareTo(meetTime) < 0) {
							// 正常
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
			if (tempid.equals(hisid)) {
				return true;
			} else {
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
	 * Description: SignUtil是否已经签到<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-29 <br>
	 * 
	 * @author 韩纪伟
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
	 * Description: SignUtil根据会议编号取得会议信息<br>
	 * Return: TConference<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-19 <br>
	 * 
	 * @author 韩纪伟
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
	 * Description: SignUtil根据会议编号取得与会人员总人数<br>
	 * Return: int<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-19 <br>
	 * 
	 * @author 韩纪伟
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
	 * Description: SignUtil根据会议编号取得实际签到总人数<br>
	 * Return: int<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-19 <br>
	 * 
	 * @author 韩纪伟
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
	 * Description: SignUtil根据会议编号取得正常签到人数列表(1,3正常签到)<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-19 <br>
	 * 
	 * @author 韩纪伟
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
				if (i + 1 < l) {
					Object[] objects1 = (Object[]) list.get(i + 1);
					if (convent(objects[0]).equals(convent(objects1[0]))) {
						dutyName += "," + convent(objects1[3]);
						i++;
						for (int j = i + 1; j < l; j++) {
							objects1 = (Object[]) list.get(j);
							if (convent(objects[0])
									.equals(convent(objects1[0]))) {
								dutyName += "," + convent(objects1[3]);
								i++;
								continue;
							} else {
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
	 * Description: SignUtil根据会议编号取得未到人数列表(00默认)<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-19 <br>
	 * 
	 * @author 韩纪伟
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
				if (i + 1 < l) {
					Object[] objects1 = (Object[]) list.get(i + 1);
					if (convent(objects[0]).equals(convent(objects1[0]))) {
						dutyName += "," + convent(objects1[3]);
						i++;
						for (int j = i + 1; j < l; j++) {
							objects1 = (Object[]) list.get(j);
							if (convent(objects[0])
									.equals(convent(objects1[0]))) {
								dutyName += "," + convent(objects1[3]);
								i++;
								continue;
							} else {
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
	 * Description: SignUtil根据会议编号取得请假人数列表(30请假)<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-19 <br>
	 * 
	 * @author 韩纪伟
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
				if (i + 1 < l) {
					Object[] objects1 = (Object[]) list.get(i + 1);
					if (convent(objects[0]).equals(convent(objects1[0]))) {
						dutyName += "," + convent(objects1[3]);
						i++;
						for (int j = i + 1; j < l; j++) {
							objects1 = (Object[]) list.get(j);
							if (convent(objects[0])
									.equals(convent(objects1[0]))) {
								dutyName += "," + convent(objects1[3]);
								i++;
								continue;
							} else {
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
	 * Description: SignUtil根据会议编号取得替代签到人数列表(13替代签到,23替代签到(迟到))<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-19 <br>
	 * 
	 * @author 韩纪伟
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
				if (i + 1 < l) {
					Object[] objects1 = (Object[]) list.get(i + 1);
					if (convent(objects[0]).equals(convent(objects1[0]))) {
						dutyName += "," + convent(objects1[3]);
						i++;
						for (int j = i + 1; j < l; j++) {
							objects1 = (Object[]) list.get(j);
							if (convent(objects[0])
									.equals(convent(objects1[0]))) {
								dutyName += "," + convent(objects1[3]);
								i++;
								continue;
							} else {
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
	 * 按代表团统计应到人数和实到人数 2006-6-13 hjw
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
				map.put("dlgtName", "".equals(convent(objects[1])) ? "其他"
						: convent(objects[1]));
				map.put("attendee", convent(objects[2]));
				map.put("fact", convent(objects[3]) == "" ? "0"
						: convent(objects[3]));
				int total = Integer.parseInt(convent(objects[2]));
				int checked = Integer.parseInt(convent(objects[3]) == "" ? "0"
						: convent(objects[3])) * 100;
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
			map.put("dlgtName", "总计");
			map.put("attendee", String.valueOf(totlenum));
			map.put("fact", String.valueOf(factnum));
			if (totlenum > 0) {
				map.put("ratio", String.valueOf(factnum * 100 / totlenum));
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

	public static List getDelegrayListByConfidspit(int confid, int flag) {
		SignDAO dao = SignDAO.getInstance();
		List result = new ArrayList();
		List list = null;
		try {
			list = dao.getDelegrayListByConfid(confid);
			if (1 == flag) {
				for (int i = 0, l = list.size(); i < l; i++) {
					if (i % 2 != 0) {
						continue;
					}
					Object[] objects = (Object[]) list.get(i);
					HashMap map = new HashMap();
					map.put("delegray", convent(objects[0]));
					map.put("dlgtName", "".equals(convent(objects[1])) ? "其他"
							: convent(objects[1]));
					map.put("attendee", convent(objects[2]));
					map.put("fact", convent(objects[3]) == "" ? "0"
							: convent(objects[3]));
					int total = Integer.parseInt(convent(objects[2]));
					int checked = Integer
							.parseInt(convent(objects[3]) == "" ? "0"
									: convent(objects[3])) * 100;
					if (total > 0) {
						map.put("ratio", String.valueOf(checked / total));
					} else {
						map.put("ratio", "100");
					}
					result.add(map);
				}
			} else {
				for (int i = 0, l = list.size(); i < l; i++) {
					if (i % 2 == 0) {
						continue;
					}
					Object[] objects = (Object[]) list.get(i);
					HashMap map = new HashMap();
					map.put("delegray", convent(objects[0]));
					map.put("dlgtName", "".equals(convent(objects[1])) ? "其他"
							: convent(objects[1]));
					map.put("attendee", convent(objects[2]));
					map.put("fact", convent(objects[3]) == "" ? "0"
							: convent(objects[3]));
					int total = Integer.parseInt(convent(objects[2]));
					int checked = Integer
							.parseInt(convent(objects[3]) == "" ? "0"
									: convent(objects[3])) * 100;
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
				map.put("dlgtName", "总计");
				map.put("attendee", String.valueOf(totlenum));
				map.put("fact", String.valueOf(factnum));
				if (totlenum > 0) {
					map.put("ratio", String.valueOf(factnum * 100 / totlenum));
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
	 * 显示代表团明细 2006-6-13 hlq
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

}
