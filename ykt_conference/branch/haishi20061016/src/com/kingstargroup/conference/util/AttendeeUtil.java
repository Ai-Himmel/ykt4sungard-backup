package com.kingstargroup.conference.util;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import org.apache.log4j.Logger;
import org.hibernate.HibernateException;
import org.hibernate.Transaction;

import com.kingstargroup.conference.common.DateUtilExtend;
import com.kingstargroup.conference.common.GetCh2Spell;
import com.kingstargroup.conference.common.SortListColl;
import com.kingstargroup.conference.common.StringUtil;
import com.kingstargroup.conference.dao.AttendeeDAO;
import com.kingstargroup.conference.dao.AttendeeGroupDAO;
import com.kingstargroup.conference.dao.ConferenceDAO;
import com.kingstargroup.conference.dao.DictionaryDAO;
import com.kingstargroup.conference.hibernate.form.TAttendeeGroup;
import com.kingstargroup.conference.hibernate.form.TAttendeeGroupKey;
import com.kingstargroup.conference.hibernate.form.TAttendeeList;
import com.kingstargroup.conference.hibernate.form.TAttendeeListKey;
import com.kingstargroup.conference.hibernate.form.TConference;
import com.kingstargroup.conference.hibernate.form.TDevConference;
import com.kingstargroup.conference.hibernate.form.TDevConferenceKey;
import com.kingstargroup.conference.hibernate.form.TInformList;
import com.kingstargroup.conference.hibernate.form.TInformListKey;
import com.kingstargroup.conference.hibernate.form.TPifCard;
import com.kingstargroup.conference.hibernate.form.TPifDevice;
import com.kingstargroup.conference.hibernate.form.TTifMeslist;

public class AttendeeUtil extends BasicUtil {
	static Logger log = Logger.getLogger("Businesslog");

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: GetDictionary����������ѯ��Ա������Ϣ<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-6 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static List getCustList(String custno, String custname, String duty,
			String dept) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getCustInfo(custno, custname, duty, dept);
			for (int i = 0; i < custList.size(); i++) {
				Object[] objects = (Object[]) custList.get(i);
				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("dutyName", convent(objects[3]));
				confMap.put("deptName", convent(objects[4]));
				confMap.put("duty", convent(objects[5]));
				//confMap.put("pym",GetCh2Spell.getBeginCharacter(convent(objects[4])));
				confMap.put("pym",new GetCh2Spell().String2Alpha(convent(objects[4])));
				result.add(confMap);
			}
		} catch (HibernateException he) {
			he.printStackTrace();
		} finally {
			closeSession();
		}
		Collections.sort(result,new SortListColl());
		return result;
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeUtilȡ�ÿͻ���Ϣ����map<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-17 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static List getCustListMap(int confid, String custno,
			String custname, String duty, String dept) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getCustInfo(confid, custno, custname, duty, dept);
			for (int i = 0; i < custList.size(); i++) {
				Object[] objects = (Object[]) custList.get(i);
				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("dutyName", convent(objects[3]));
				confMap.put("deptName", convent(objects[4]));
				confMap.put("attendSign", GetDictionary
						.getAttendeeStatus(convent(objects[5])));
				result.add(confMap);
			}
			return result;
		} catch (Exception he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	/**
	 * ����ѡ�����Ա�б���ʾҪ��ϯ������Ա����
	 * 2006-6-12
	 * hjw
	 * @param
	 * @return
	 */
	public static List getAttendeeAllotList(String groupids,String queryids){
		AttendeeDAO dao = AttendeeDAO.getInstance();
		String[] totcustids = StringUtil.split(groupids + queryids, ",");
		StringBuffer testids = new StringBuffer();
		for (int i=0 ;i<totcustids.length;i++){
			if (i==totcustids.length-1){
				testids.append(totcustids[i]);
			}else{
				testids.append(totcustids[i]+",");
			}
		}
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getAttendeeAllotList(testids.toString());
			for (int i = 0; i < custList.size(); i++) {
				Object[] objects = (Object[]) custList.get(i);
				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("dutyName", convent(objects[3]));
				confMap.put("deptName", convent(objects[4]));
				result.add(confMap);
			}
			return result;
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeUtil��ָ������Ա����<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-7 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static boolean attendeeGroup(String groupname, String ids) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		Transaction t = beginTransaction();
		String[] custids = StringUtil.split(ids, ",");
		try {
			for (int i = 0; i < custids.length; i++) {
				if (dao.existsAttendeeGroup(Integer.parseInt(groupname),
						Integer.parseInt(custids[i]))) {
					continue;
				}
				TAttendeeGroupKey key = new TAttendeeGroupKey();
				key.setCustId(new Integer(custids[i]));
				key.setGroupId(new Integer(groupname));
				TAttendeeGroup group = new TAttendeeGroup(key);
				dao.save(group);
			}
			t.commit();
			return true;
		} catch (HibernateException he) {
			he.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeUtil�������ŵõ��������Ա�б�<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-7 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static List getCustListByGroupId(int groupid) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getCustGroupList(groupid);
			for (int i = 0; i < custList.size(); i++) {
				Object[] objects = (Object[]) custList.get(i);
				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("duty", convent(objects[3]));
				confMap.put("deptName", convent(objects[4]));
				result.add(confMap);
			}
			return result;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeUtil������ɾ����Ա����<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-7 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static boolean deleteCustGroup(int groupid, String custids) {
		AttendeeGroupDAO dao = AttendeeGroupDAO.getInstance();
		Transaction t = beginTransaction();
		String[] custs = StringUtil.split(custids, ",");
		try {
			for (int i = 0; i < custs.length; i++) {
				dao.deleteCustGroup(groupid, Integer.parseInt(custs[i]));
			}
			t.commit();
			return true;
		} catch (HibernateException he) {
			he.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeUtil����Ա���豸�󶨵������У�����֪ͨ����д����Ա����<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-11 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static boolean attendeeAllot(int confid, String idsgroup,
			String idsquery, String deviceids, String custtype,
			String delegray, String custtype2, String delegray2) {
		AttendeeDAO dao = AttendeeDAO.getInstance();
		ConferenceDAO confdao = ConferenceDAO.getInstance();
		// ����Աѡ��ı���б�
		String[] custids = StringUtil.split(idsgroup, ",");
		String[] queryids = StringUtil.split(idsquery, ",");
		String[] totcustids = StringUtil.split(idsgroup + idsquery, ",");
		// ��ѯ������Ա����б�
		String[] devids = StringUtil.split(deviceids, ",");
		// ������
		Integer conid = new Integer(confid);
		String getDate = DateUtilExtend.getNowDate2();
		String getTime = DateUtilExtend.getNowTime2();
		Transaction t = beginTransaction();
		try {
			TConference conf = (TConference) confdao.findByPrimaryKey(
					TConference.class, new Integer(confid));
			// ���������Ա������Ϣ
			for (int i = 0; i < custids.length; i++) {
				Integer custid = new Integer(custids[i]);
				if (dao.existAttendee(Integer.parseInt(custid.toString()),
						confid)) {
					continue;
				}
				// ���ݿͻ���ȡ�øÿͻ��Ŀ���
				TPifCard card = dao.getCardNoByCustId(Integer.parseInt(custid
						.toString()));
				TAttendeeListKey key = new TAttendeeListKey();
				key.setConId(conid);
				key.setCustId(custid);
				TAttendeeList attendee = new TAttendeeList(key);
				if (null != card) {
					attendee.setCardNo(card.getCardId());
				} else {
					attendee.setCardNo(new Integer(0));
				}
				attendee.setSendSign("0");// �Ƿ��·���0δ�·���1�·�
				attendee.setDelSign("0");
				attendee.setAttendSign("0");
				attendee.setAllotDate(getDate);
				attendee.setAllotTime(getTime);
				attendee.setDelegray(delegray);
				attendee.setAttendeeType(custtype);
				dao.save(attendee);
			}
			// �����ѯ��Ա������Ϣ
			for (int i = 0; i < queryids.length; i++) {
				Integer qcustid = new Integer(queryids[i]);
				if (dao.existAttendee(Integer.parseInt(qcustid.toString()),
						confid)) {
					continue;
				}
				// ���ݿͻ���ȡ�øÿͻ��Ŀ���
				TPifCard card = dao.getCardNoByCustId(Integer.parseInt(qcustid
						.toString()));
				TAttendeeListKey qkey = new TAttendeeListKey();
				qkey.setConId(conid);
				qkey.setCustId(qcustid);
				TAttendeeList qattendee = new TAttendeeList(qkey);
				if (null != card) {
					qattendee.setCardNo(card.getCardId());
				} else {
					qattendee.setCardNo(new Integer(0));
				}
				qattendee.setSendSign("0");// �Ƿ��·���0δ�·���1�·�
				qattendee.setDelSign("0");
				qattendee.setAttendSign("0");
				qattendee.setAllotDate(getDate);
				qattendee.setAllotTime(getTime);
				qattendee.setDelegray(delegray2);
				qattendee.setAttendeeType(custtype2);
				dao.save(qattendee);
			}
			for (int i = 0; i < totcustids.length; i++) {
				Integer custid = new Integer(totcustids[i]);
				if (dao
						.existInform(Integer.parseInt(custid.toString()),
								confid)) {
					continue;
				}
				TInformListKey informkey = new TInformListKey();
				informkey.setConId(conid);
				informkey.setCustId(custid);
				TInformList inform = new TInformList(informkey);
				inform.setInformDate(getDate);
				inform.setInformTime(getTime);
				inform.setInformSign("0");// �Ƿ�֪ͨ��0δ֪ͨ��1֪ͨ
				dao.save(inform);

			}
			dao.delDevConf(confid);
			for (int j = 0; j < devids.length; j++) {
				if (dao.existDevice(Integer.parseInt(devids[j].toString()),
						confid)) {
					continue;
				}
				TDevConferenceKey key = new TDevConferenceKey();
				key.setConId(conid);
				key.setDeviceId(new Integer(devids[j]));
				TDevConference devconf = new TDevConference(key);
				devconf.setConBegindate(conf.getConBegindate());
				devconf.setConSigntime(conf.getConSigntime());
				devconf.setConBegintime(conf.getConBegintime());
				devconf.setConEndtime(conf.getConEndtime());
				dao.save(devconf);
			}
			t.commit();
			return true;
		} catch (HibernateException he) {
			he.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeUtil���ݻ����ŵõ�֪ͨ�������в���û������Ա����<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-12 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static List getAttendeeListByConfId(int confid) {
		AttendeeDAO dao = AttendeeDAO.getInstance();
		//List custList = new ArrayList();
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getAttendeeListByConfId(confid);
			//custList = dao.getCustGroupList(groupid);
			for (int i = 0; i < custList.size(); i++) {
				Object[] objects = (Object[]) custList.get(i);
				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("duty_Name", convent(objects[3]));
				confMap.put("deptName", convent(objects[4]));
				result.add(confMap);
			}
			return result;
		} catch (HibernateException he) {
			he.printStackTrace();
		} finally {
			closeSession();
		}
		return custList;
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeUtil���ݻ�����ȡ�øû��������豸<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-27 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static List getDevListByConfId(int confid) {
		AttendeeDAO dao = AttendeeDAO.getInstance();
		List devList = new ArrayList();
		try {
			devList = dao.getDevListByConfid(confid);
		} catch (HibernateException he) {
			he.printStackTrace();
		} finally {
			closeSession();
		}
		return devList;
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeUtil<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-13 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static boolean attendeeInform(int confid, String idsgroup,
			String idsquery, String informcotents) {
		AttendeeDAO dao = AttendeeDAO.getInstance();
		// ����Աѡ��ı���б�
		String[] custids = StringUtil.split(idsgroup + idsquery, ",");
		// ������
		Integer conid = new Integer(confid);
		String getDate = DateUtilExtend.getNowDate2();
		String getTime = DateUtilExtend.getNowTime();
		Transaction t = beginTransaction();
		try {
			// ��Ҫ֪ͨ����Ա�����·�����Ա�����б���ȥ
			for (int i = 0; i < custids.length; i++) {
				Integer custid = new Integer(custids[i]);
				if (dao
						.existInform(Integer.parseInt(custid.toString()),
								confid)) {
					continue;
				}
				TInformListKey informkey = new TInformListKey();
				informkey.setConId(conid);
				informkey.setCustId(custid);
				TInformList inform = new TInformList(informkey);
				inform.setInformDate(getDate);
				inform.setInformTime(getTime);
				inform.setInformSign("0");// �Ƿ�֪ͨ��0δ֪ͨ��1֪ͨ
				dao.save(inform);
			}
			// �ڴ˴����ú�OA֪ͨ�Ľӿڣ���֪ͨ�����·���OA�˺���ȥ
			// {֪ͨ�ӿ�}
			Iterator iter = dao.getAttendeeByConfId(confid).iterator();
			while (iter.hasNext()) {
				TInformList row = (TInformList) iter.next();
				row.setInformSign("1");
				dao.saveOrUpdate(row);
			}

			TConference conf = (TConference) dao.findByPrimaryKey(
					TConference.class, conid);
			conf.setContent(informcotents);
			dao.saveOrUpdate(conf);
			t.commit();
			//new MailSender().run(dao.getAttendeeByConfId(confid));

			return true;
		} catch (HibernateException he) {
			he.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeUtil����Ϣ���б������Ϣ<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-20 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static boolean addMesListByConfId(int confid) {
		AttendeeDAO dao = AttendeeDAO.getInstance();
		DictionaryDAO dictdao = DictionaryDAO.getInstance();
		StringBuffer datetime = new StringBuffer();
		datetime.append(DateUtilExtend.getNowDate2())
				.append(DateUtilExtend.getNowTime());
		Transaction t = beginTransaction();
		try {
			//ɾ���Ѿ����ڵ������б�
			for (int i = 0 ;i < 3 ;i++){
				deleteMesList(dictdao,dao,confid,datetime.toString());
			}
			
			// ��ȡ�豸�б�
			Iterator devIter = dictdao.getDeviceListByConfid(confid).iterator();
			while (devIter.hasNext()) {
				TPifDevice dev = (TPifDevice) devIter.next();
				Integer devId = dev.getDeviceId();

				//ѭ��5���·�ʱ���
				//for (int i=0 ;i<5;i++){
					//sendTime(dao,confid,datetime.toString(),dev,devId);
				//}
				// ����·�������Ϣ����
				for (int i = 0 ; i<3;i++){
					addMesList(dao,confid,dev,devId,datetime.toString());
				}
			}
			Iterator attIter1 = dao.getAttListByConfId(confid).iterator();
			while (attIter1.hasNext()) {
				TAttendeeList attendee = (TAttendeeList) attIter1.next();
				attendee.setSendSign("1");
				dao.save(attendee);
			}
			t.commit();
			return true;
		} catch (Exception e) {
			e.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
	}

	private static void deleteMesList(
			DictionaryDAO dictdao,
			AttendeeDAO dao,
			int confid,
			String datetime)throws Exception{
		StringBuffer delMesContent = new StringBuffer();
		// ����ɾ���Ѿ����ڵİ���������
		delMesContent.append("<CARDID>").append(0).append("</CARDID>")
				.append("<FTFLAG>").append(2).append("</FTFLAG>");
		// ��ȡ�豸�б�
		Iterator devIter = dictdao.getDeviceListByConfid(confid).iterator();
		while (devIter.hasNext()) {
			TTifMeslist delMesList = new TTifMeslist();
			TPifDevice dev = (TPifDevice) devIter.next();
			Integer devId = dev.getDeviceId();
			//BeanUtils.copyProperties(delMesList, mesList);
			delMesList.setFunid(new Integer(930117));
			delMesList.setLevel(new Integer(1));
			delMesList.setSendcount(new Integer(0));
			delMesList.setMaxSendCnt(new Integer(1));
			delMesList.setDelFlag("0");
			delMesList.setEcode(new Integer(9999));
			delMesList.setStateid(new Integer(1));
			delMesList.setIndt(datetime.toString());
			delMesList.setStartdt("");
			delMesList.setEnddt("");
			delMesList.setEmsg("");
			delMesList.setOutcontent("");
			delMesList.setCardNo(new Integer(0));
			delMesList.setIncontent(delMesContent.toString());
			delMesList.setDeviceId(dev.getSubsystemId());
			delMesList.setDevid(devId);
			dao.save(delMesList);
		}
		
	}
	private static void addMesList(AttendeeDAO dao,
				int confid,
				TPifDevice dev,
				Integer devId,
				String datetime)throws Exception{
		// ��ȡ�����б�
		Iterator attIter1 = dao.getAttListByConfId(confid).iterator();
		while (attIter1.hasNext()) {
			TAttendeeList attendee = (TAttendeeList) attIter1.next();
			TTifMeslist addMesList = new TTifMeslist();
			StringBuffer addMesContent = new StringBuffer();
			if ("0".equals(attendee.getCardNo().toString())){
				continue;
			}
			addMesContent.append("<CARDID>")
				.append(attendee.getCardNo())
				.append("</CARDID>")
				.append("<FTFLAG>")
				.append(0)
				.append("</FTFLAG>");
			addMesList.setFunid(new Integer(930117));
			addMesList.setLevel(new Integer(2));
			addMesList.setSendcount(new Integer(0));
			addMesList.setMaxSendCnt(new Integer(20));
			addMesList.setDelFlag("0");
			addMesList.setEcode(new Integer(9999));
			addMesList.setStateid(new Integer(1));
			addMesList.setIndt(datetime);
			addMesList.setStartdt("");
			addMesList.setEnddt("");
			addMesList.setEmsg("");
			addMesList.setOutcontent("");
			//BeanUtils.copyProperties(addMesList, mesList);
			addMesList.setIncontent(addMesContent.toString());
			addMesList.setDeviceId(dev.getSubsystemId());
			addMesList.setCardNo(attendee.getCardNo());
			addMesList.setDevid(devId);
			dao.save(addMesList);
		}
		
	}
	
	private static void sendTime(AttendeeDAO dao,int confid,String datetime,TPifDevice dev,Integer dev999id){
		// Ϊ�豸�·�ʱ���
		ConferenceDAO confdao = ConferenceDAO.getInstance();
		TConference conf = (TConference) confdao.findByPrimaryKey(
				TConference.class, new Integer(confid));
		String week = DateUtilExtend.getWeekByDate(conf.getConBegindate()
				.toString());
		String begintime = conf.getConSigntime();
		String endtime = conf.getConEndtime().substring(0, 4);
		TTifMeslist weekMesList = new TTifMeslist();
		StringBuffer weekCont = new StringBuffer();
		weekCont
				.append("<WEEKNO>")
				.append(week)
				.append("</WEEKNO><OUTNUM>1</OUTNUM><T1>")
				.append(begintime)
				.append(endtime)
				.append("FFFFFFFF")
				.append(
						"</T1><T2></T2><T3></T3><T4></T4><T5></T5><T6></T6><T7></T7><T8></T8>");
		weekMesList.setFunid(new Integer(930105));
		weekMesList.setLevel(new Integer(2));
		weekMesList.setSendcount(new Integer(0));
		weekMesList.setMaxSendCnt(new Integer(20));
		weekMesList.setDelFlag("0");
		weekMesList.setEcode(new Integer(9999));
		weekMesList.setStateid(new Integer(1));
		weekMesList.setIndt(datetime.toString());
		weekMesList.setStartdt("");
		weekMesList.setEnddt("");
		weekMesList.setEmsg("");
		weekMesList.setOutcontent("");
		weekMesList.setCardNo(new Integer(0));
		weekMesList.setIncontent(weekCont.toString());
		weekMesList.setDeviceId(dev.getSubsystemId());
		weekMesList.setDevid(dev999id);
		dao.save(weekMesList);
		
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeUtil<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-21 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static List getAttendeeListBy(int confid, String custno,
			String custname, String dept, String duty) {
		AttendeeDAO dao = AttendeeDAO.getInstance();
		List custList = null;
		List result = new ArrayList();
		try {
			custList = dao.getAttendeeListBy(confid,custno,custname,dept,duty);
			for (int i = 0; i < custList.size(); i++) {
				Object[] objects = (Object[]) custList.get(i);
				HashMap confMap = new HashMap();
				confMap.put("cutId", new Integer(convent(objects[0])));
				confMap.put("cutName", convent(objects[1]));
				confMap.put("stuempNo", convent(objects[2]));
				confMap.put("dutyName", convent(objects[3]));
				confMap.put("deptName", convent(objects[4]));
				result.add(confMap);
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
	 * Description: AttendeeUtil<br>
	 * Return: String<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-5-9 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static String getUsedDevList(int confid) {
		AttendeeDAO dao = AttendeeDAO.getInstance();
		ConferenceDAO confdao = ConferenceDAO.getInstance();
		StringBuffer devstr = new StringBuffer();
		try {
			TConference conf = (TConference) confdao.findByPrimaryKey(TConference.class, new Integer(confid));
			String beginDate = conf.getConBegindate();
			String signTime = conf.getConSigntime();
			String endTime = conf.getConEndtime();
			List devlist = dao.usedDevIdList(beginDate);
			Iterator iter = devlist.iterator();
			while (iter.hasNext()) {
				Object[] dev = (Object[]) iter.next();
				String devsignTime = dev[4].toString();
				String devendTime = dev[3].toString();
				//�ж�˫˫ʱ���Ƿ��ڶԷ�֮��
				if (((DateUtilExtend.timeDiff2(signTime,devsignTime)<0)&&
						(DateUtilExtend.timeDiff2(signTime,devendTime)>0))||
						((DateUtilExtend.timeDiff2(endTime,devsignTime)<0)&&
								(DateUtilExtend.timeDiff2(endTime,devendTime)>0))){
					devstr.append(GetDictionary.getDev999IdByDevId(Integer.parseInt(dev[0].toString()))+ ",");
					continue;
				}
				if (((DateUtilExtend.timeDiff2(devsignTime,signTime)<0)&&
						(DateUtilExtend.timeDiff2(devendTime,signTime)>0))||
						((DateUtilExtend.timeDiff2(devsignTime,endTime)<0)&&
								(DateUtilExtend.timeDiff2(devendTime,endTime)>0))){
					devstr.append(GetDictionary.getDev999IdByDevId(Integer.parseInt(dev[0].toString()))+ ",");
					continue;
				}
			}
			return devstr.toString();
		} catch (Exception he) {
			he.printStackTrace();
			return null;
		} finally {
			closeSession();
		}
	}

	/**
	 * �ж��Ƿ������δ�·��ɹ�����ˮ��trueΪ������δ�·��ɹ�����ˮ��falseΪû��
	 * 2006-6-7
	 * hjw
	 * @param
	 * @return
	 */
	public static boolean getMesListIfSucceed(int confid){
		AttendeeDAO attdao = AttendeeDAO.getInstance();
		ConferenceDAO confdao = ConferenceDAO.getInstance();
		String beginDate = "";
		try {
			TConference conf = (TConference)confdao.findByPrimaryKey(TConference.class,new Integer(confid));
			beginDate = conf.getConBegindate();
			if ("0".equals(attdao.getMesListIfSucceed(confid,beginDate))){
				return false;
			}else{
				return true;
			}
		} catch (HibernateException he) {
			he.printStackTrace();
			return false;
		}finally{
			closeSession();
		}
	}
	
	public static boolean ifSendBySucceed(int confid){
		AttendeeDAO dao = AttendeeDAO.getInstance();
		try {
			if ("0".equals(dao.ifSendBySucceed(confid))){
				return false;
			}else{
				return true;
			}
		} catch (Exception e) {
			return false;
		}finally{
			closeSession();
		}
	}
	public static List getCustListByConfId(int confid){
		AttendeeDAO dao = AttendeeDAO.getInstance();
		try {
			return dao.getCustListByConfId(confid);
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
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
