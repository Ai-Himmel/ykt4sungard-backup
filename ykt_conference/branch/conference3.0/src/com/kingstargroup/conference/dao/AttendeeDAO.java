/**
 * 
 */
package com.kingstargroup.conference.dao;

import java.util.Iterator;
import java.util.List;

import org.apache.log4j.Logger;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.conference.hibernate.form.TAttendeeList;
import com.kingstargroup.conference.hibernate.form.TAttendeeListId;
import com.kingstargroup.conference.hibernate.form.TCard;
import com.kingstargroup.conference.hibernate.form.TCustomer;
import com.kingstargroup.conference.hibernate.form.TDevConference;
import com.kingstargroup.conference.hibernate.form.TMsglist;

/**
 * @author ��Ա����֪ͨ���
 * 
 */
public class AttendeeDAO extends BasicDAO {
	private static AttendeeDAO _instance;
	private Logger errlog = Logger.getLogger("Errlog");

	// private Logger busslog = Logger.getLogger("Bussinesslog");

	public static AttendeeDAO getInstance() {
		if (_instance == null) {
			_instance = new AttendeeDAO();
		}
		return _instance;
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeDAO���ݻ����ŵõ�֪ͨ�������в���û������Ա������ϸ��Ϣ<br>
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
	public List getAttendeeListByConfId(int confid) throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select cust.custid as cutId,cust.custname as cutName,cust.stuempno as stuempNo,")
				.append(" duty.duty as duty_Name,dept.deptname as deptName")
				.append(
						" from ykt_cur.t_customer cust left join ykt_cur.t_dept dept on cust.deptcode=dept.deptcode left join ykt_conf.t_duty duty on")
				.append(" cust.stuempno = duty.stuemp_no")
				.append(
						" where cust.custid in(select cust_id from ykt_conf.t_inform_list where con_id="
								+ confid + ")");
		try {
			Query q = s.createSQLQuery(sqlStr.toString());
			return q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.error(he);
			throw he;
		}
	}

	public void deleteAllAttendeeList() throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery("delete from TAttendeeList");
			q.executeUpdate();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	public void deleteAllAttendeeList(long confId, String attendees)
			throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TAttendeeList where id.conId="
					+ confId);
			List list = q.list();
			for (int i = 0; i < list.size(); i++) {
				TAttendeeList tattendeelist = (TAttendeeList) list.get(i);
				String tmp1 = ","
						+ String.valueOf(tattendeelist.getId().getCustId())
						+ ",";
				if (attendees.indexOf(tmp1) == -1) {
					Query dq = s
							.createQuery("delete from TAttendeeList where id.conId="
									+ confId
									+ " and id.custId="
									+ tattendeelist.getId().getCustId());
					q.executeUpdate();
				}
			}
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * ����ѡ�����Ա�б���ʾҪ��ϯ������Ա���� 2006-6-12 hjw
	 * 
	 * @param
	 * @return
	 */
	public List getAttendeeAllotList(String custnolists)
			throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
				.append(" duty.duty as dutyName,dept.dept_Name as deptName")
				.append(
						" from ykt_cur.t_customer cust left join ykt_cur.t_dept dept on")
				.append(
						" cust.deptcode=dept.deptcode left join ykt_conf.t_duty duty on")
				.append(" cust.stuempno = duty.stuemp_no").append(
						" where cust.custid in(" + custnolists + ")");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("dutyName", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeDAO������Ա��ŵõ�����Ա�Ŀ���<br>
	 * Return: TPifCard<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-11 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public TCard getCardNoByCustId(long custid) throws HibernateException {
		TCard card = null;
		Session s = getSession();
		try {
			Query q = s
					.createQuery(" from TCard where status||lossflag='10' and custid="
							+ custid);
			if (q.list().size() != 0) {
				card = (TCard) q.list().get(0);
			}
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
		return card;
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeDAOȡ���û���Ϣ<br>
	 * Return: TCifCustomer<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-5-26 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public TCustomer getCustomerCustId(int custid) throws HibernateException {
		TCustomer customer = null;
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TCustomer where custid=" + custid);
			if (q.list().size() != 0) {
				customer = (TCustomer) q.list().get(0);
			}
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
		return customer;
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeDAO���ݻ����ź���Ա����ж��Ƿ���ڸü�¼�������򷵻�true<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-12 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public boolean existAttendee(long custid, long confid)
			throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TAttendeeList where id.conId="
					+ confid + " and id.custId=" + custid);
			if (q.list().size() != 0) {
				return true;
			} else {
				return false;
			}
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeDAO���ݻ����ź��豸����ж��Ƿ���ڸ��豸�����ڷ���true<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-12 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public boolean existDevice(long devid, long confid)
			throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TDevConference where id.conId="
					+ confid + " and id.deviceId=" + devid);
			if (q.list().size() != 0) {
				return true;
			} else {
				return false;
			}
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeDAO������Ա��źͻ������ж��Ƿ������֪ͨ��Ϣ�������ⷵ��true<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-12 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public boolean existInform(long custid, long confid)
			throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TInformList where id.conId="
					+ confid + " and id.custId=" + custid);
			if (q.list().size() != 0) {
				return true;
			} else {
				return false;
			}
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeDAO���ݻ�����ȡ�øû��������豸<br>
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
	public List getDevListByConfid(int confid) throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TDevConference where id.conId="
					+ confid);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeDAO���ݻ����ŵõ�Ҫ֪ͨ����Ա����<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-13 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public List getAttendeeByConfId(long confid) throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TInformList where id.conId="
					+ confid);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeDAO���ݻ����б�ȡ����Ա�����б�<br>
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
	public List getAttListByConfId(int confid) throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TAttendeeList where id.conId="
					+ confid);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeDAO<br>
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
	public List getAttendeeListBy(int confid, String custno, String custname,
			String dept, String duty) throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select cust.custid as cutId,cust.custname as cutName,cust.stuempno as stuempNo,")
				.append(
						" duty.duty as dutyName,dept.deptname as deptName from ykt_cur.t_customer cust ")
				.append(
						" left join ykt_cur.t_dept dept on cust.deptcode=dept.deptcode ")
				.append(
						" left join YKT_CONF.T_DUTY duty on cust.stuempno=duty.stuemp_no where ")
				.append(
						" cust.custid in(select cust_id from ykt_conf.t_inform_List where con_id="
								+ confid + ")");
		if (!"".equals(custno)) {
			sqlStr.append(" and cust.stuempno like '%" + custno + "%'");
		}
		if (!"".equals(custname)) {
			sqlStr.append(" and cust.custname like '%" + custname + "%'");
		}
		if (!"".equals(duty)) {
			sqlStr.append(" and duty.duty like '%" + duty + "%'");
		}
		if (!"-".equals(dept)) {
			sqlStr.append(" and cust.deptcode='" + dept + "'");
		}
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("dutyName", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeDAO����Ϣ���б��в����Ƿ���ڼ�¼��������ɾ��<br>
	 * Return: void<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-5-9 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public void deleteMesList(int devid, Integer dev999id, int cardno)
			throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append(
				" from TMsglist where sysid=" + devid + " and deviceid="
						+ dev999id).append(
				" and funid=930117 and cardno=" + cardno + " and ecode>0");
		try {
			Query q = s.createQuery(sqlStr.toString());
			Iterator iter = q.list().iterator();
			while (iter.hasNext()) {
				s.delete((TMsglist) iter.next());
			}
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeDAO���ݻ�����ȡ���Ѿ�ʹ�øû����豸�Ļ����б�<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-5-9 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public List usedDevIdList(String begindate) throws HibernateException {
		Session s = getSession();
		// String confdate = DateUtilExtend.getNowDate2();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select DEVICE_ID, CON_BEGINDATE, CON_BEGINTIME, CON_ENDTIME,CON_SIGNTIME")
				.append(
						" from YKT_CONF.T_DEV_CONFERENCE where CON_BEGINDATE='"
								+ begindate + "'");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("DEVICE_ID", Hibernate.INTEGER);
			q.addScalar("CON_BEGINDATE", Hibernate.STRING);
			q.addScalar("CON_BEGINTIME", Hibernate.STRING);
			q.addScalar("CON_ENDTIME", Hibernate.STRING);
			q.addScalar("CON_SIGNTIME", Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeDAO�豸�����Ӧ������������豸������ɾ��������<br>
	 * Return: void<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-5-9 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public void delDevConf(long confid) throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TDevConference where id.conId="
					+ confid);
			Iterator iter = q.list().iterator();
			while (iter.hasNext()) {
				s.delete((TDevConference) iter.next());
			}
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeDAO���ݻ�����ȡ���ڸû����е���Ա��Ϣ<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-5-29 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public List getCustListByConfId(int confid) throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append(" from TCustomer where custid in (").append(
				" select id.custId from TInformList where id.conId=" + confid
						+ ")");
		try {
			Query q = s.createQuery(sqlStr.toString());
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * ��Ϣ�����иû����Ƿ��·��ɹ���������·��ɹ�����0,���򷵻����� 2006-6-8 hjw
	 * 
	 * @param
	 * @return
	 */
	public String getMesListIfSucceed(long confid, String beginDate)
			throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append("select count(*)as num from YKT_CUR.T_MSGLIST where")
				.append(
						" deviceid in (select deviceid from YKT_CUR.T_DEVICE where DEVICEID in ")
				.append(
						" (select DEVICE_ID from YKT_CONF.T_DEV_CONFERENCE where con_id="
								+ confid + "))").append(
						" and ecode<>0 and indt like '" + beginDate + "%'");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("num", Hibernate.INTEGER);
			return q.list().get(0).toString();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * �����Ƿ��ͳɹ� 2006-6-8 hjw
	 * 
	 * @param
	 * @return
	 */
	public String ifSendBySucceed(int confid) throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select count(*) as num from YKT_CONF.T_ATTENDEE_LIST ")
				.append("where con_id=" + confid + " and send_sign='0'");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("num", Hibernate.INTEGER);
			return q.list().get(0).toString();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	public TCustomer getCustomer(Long cutId) throws HibernateException {
		Session s = getSession();
		TCustomer cifcustomer = null;
		try {
			cifcustomer = (TCustomer) s.get(TCustomer.class, cutId);
		} catch (Exception e) {
			// TODO: handle exception
			e.printStackTrace();
		}
		return cifcustomer;

	}

}
