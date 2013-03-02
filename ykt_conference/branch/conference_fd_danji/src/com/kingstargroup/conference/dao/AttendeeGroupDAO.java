/**
 * 
 */
package com.kingstargroup.conference.dao;

import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.log4j.Logger;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.conference.hibernate.form.TAttendeeGroup;
import com.kingstargroup.conference.hibernate.form.TRecordhis;

/**
 * @author 人员分组相关代码
 * 
 */
public class AttendeeGroupDAO extends BasicDAO {
	private static AttendeeGroupDAO _instance;

	private Logger errlog = Logger.getLogger("Errlog");

	public static AttendeeGroupDAO getInstance() {
		if (_instance == null) {
			_instance = new AttendeeGroupDAO();
		}
		return _instance;
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeGroupDAO根据条件查询某个人的信息<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-6 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public List getCustInfo(String custno, String custname, String duty,
			String dept, int confid, List custAllotList)
			throws HibernateException {
		Session s = getSession();
		StringBuffer custIds = new StringBuffer(1024);
		if (null == custAllotList) {
			custIds.append("0");
		} else if (custAllotList.size() == 0) {
			custIds.append("0");
		} else {
			for (int i = 0; i < custAllotList.size(); i++) {
				Map custMap = (Map) custAllotList.get(i);
				if (i == custAllotList.size() - 1) {
					custIds.append(custMap.get("custId"));
				} else {
					custIds.append(custMap.get("custId") + ",");
				}
			}
		}
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
				.append(
						" cust.duty_Name as dutyName,dept.dept_Name as deptName,duty.duty as duty ")
				.append(
						" from (T_CIF_CUSTOMER cust left join T_Cif_Dept dept on ")
				.append(
						" cust.classdept_No=dept.dept_Code) left join T_DUTY duty on")
				.append(" cust.stuemp_No=duty.stuemp_No").append(
						" where cust.cut_Id not in(" + custIds + ")").append(
						" and cust.cut_id not in(select cust_id from T_ATTENDEE_LIST where con_id="
								+ confid + ")");
		if (!"".equals(custno)) {
			sqlStr.append(" and cust.stuemp_No like '%" + custno + "%'");
		}
		if (!"".equals(custname)) {
			sqlStr.append(" and cust.cut_Name like '%" + custname + "%'");
		}
		if ((!"".equals(duty))) {
			sqlStr.append(" and duty.duty like '%" + duty + "%'");
		}
		if ((!"".equals(dept)) && (!"-".equals(dept))) {
			sqlStr.append(" and cust.classdept_No='" + dept + "'");
		}
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("dutyName", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("duty", Hibernate.STRING);
			return q.list();
		} catch (HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeGroupDAO得到客户信息并放到Map里面<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-17 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public List getCustInfo(int confid, String custno, String custname,
			String duty, String dept) throws HibernateException {
		Session s = getSession();
		// HashMap map = new HashMap();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
				.append(
						" duty.duty as duty,dept.dept_Name as deptName ,att.attend_Sign as attendSign")
				.append(" from ((T_Cif_Customer cust left join T_Cif_Dept dept")
				.append(
						" on cust.classdept_No=dept.dept_Code) left join T_Attendee_List att ")
				.append(" on cust.cut_Id=att.cust_Id) left join T_DUTY duty on")
				.append(" cust.stuemp_No=duty.stuemp_No").append(
						" where att.con_Id=" + confid);
		if (!"".equals(custno)) {
			sqlStr.append(" and cust.stuemp_No like '%" + custno + "%'");
		}
		if (!"".equals(custname)) {
			sqlStr.append(" and cust.cut_Name like '%" + custname + "%'");
		}
		if (!"".equals(duty)) {
			sqlStr.append(" and cust.duty_Name like '%" + duty + "%'");
		}
		if (!"-".equals(dept)) {
			sqlStr.append(" and cust.classdept_No='" + dept + "'");
		}
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("duty", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("attendSign", Hibernate.STRING);
			return q.list();
		} catch (HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}
	
	public List getLeaveCustInfo(int confid, String custno, String custname,
			String duty, String dept) throws HibernateException {
		Session s = getSession();
		// HashMap map = new HashMap();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
				.append(
						" duty.duty as duty,dept.dept_Name as deptName ,att.attend_Sign as attendSign")
				.append(" from ((T_Cif_Customer cust left join T_Cif_Dept dept")
				.append(
						" on cust.classdept_No=dept.dept_Code) left join T_Attendee_List att ")
				.append(" on cust.cut_Id=att.cust_Id) left join T_DUTY duty on")
				.append(" cust.stuemp_No=duty.stuemp_No")
				.append("  where (att.ATTEND_SIGN='00' or att.ATTEND_SIGN='30') ")
				.append(" and att.con_Id=" + confid);
		if (!"".equals(custno)) {
			sqlStr.append(" and cust.stuemp_No like '%" + custno + "%'");
		}
		if (!"".equals(custname)) {
			sqlStr.append(" and cust.cut_Name like '%" + custname + "%'");
		}
		if (!"".equals(duty)) {
			sqlStr.append(" and cust.duty_Name like '%" + duty + "%'");
		}
		if (!"-".equals(dept)) {
			sqlStr.append(" and cust.classdept_No='" + dept + "'");
		}
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("duty", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("attendSign", Hibernate.STRING);
			return q.list();
		} catch (HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}
	
	public List getReplaceCustInfo(int confid, String custno, String custname,
			String duty, String dept) throws HibernateException {
		Session s = getSession();
		// HashMap map = new HashMap();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
				.append(
						" duty.duty as duty,dept.dept_Name as deptName ,att.attend_Sign as attendSign")
				.append(" from ((T_Cif_Customer cust left join T_Cif_Dept dept")
				.append(
						" on cust.classdept_No=dept.dept_Code) left join T_Attendee_List att ")
				.append(" on cust.cut_Id=att.cust_Id) left join T_DUTY duty on")
				.append(" cust.stuemp_No=duty.stuemp_No")
				.append(" where (att.ATTEND_SIGN='00' or att.ATTEND_SIGN='13' or att.ATTEND_SIGN='23') ")
				.append(" and att.con_Id=" + confid);
		if (!"".equals(custno)) {
			sqlStr.append(" and cust.stuemp_No like '%" + custno + "%'");
		}
		if (!"".equals(custname)) {
			sqlStr.append(" and cust.cut_Name like '%" + custname + "%'");
		}
		if (!"".equals(duty)) {
			sqlStr.append(" and cust.duty_Name like '%" + duty + "%'");
		}
		if (!"-".equals(dept)) {
			sqlStr.append(" and cust.classdept_No='" + dept + "'");
		}
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("duty", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("attendSign", Hibernate.STRING);
			return q.list();
		} catch (HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}

	public List getCustInfoSPE(int confid, String custno, String custname,
			String duty, String dept, String dlgt) throws HibernateException {
		Session s = getSession();
		// HashMap map = new HashMap();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
				.append(
						" duty.duty as duty,dept.dept_Name as deptName ,att.attend_Sign as attendSign")
				.append(" from ((T_Cif_Customer cust left join T_Cif_Dept dept")
				.append(
						" on cust.classdept_No=dept.dept_Code) left join T_Attendee_List att ")
				.append(" on cust.cut_Id=att.cust_Id) left join T_DUTY duty on")
				.append(" cust.stuemp_No=duty.stuemp_No").append(
						" where  (att.ATTEND_SIGN='00' or att.ATTEND_SIGN='12' or att.ATTEND_SIGN='22') and att.con_Id=" + confid);
		if (!"".equals(custno)) {
			sqlStr.append(" and cust.stuemp_No like '%" + custno + "%'");
		}
		if (!"".equals(custname)) {
			sqlStr.append(" and cust.cut_Name like '%" + custname + "%'");
		}
		if (!"".equals(duty)) {
			sqlStr.append(" and cust.duty_Name like '%" + duty + "%'");
		}
		if (!"-".equals(dept)) {
			sqlStr.append(" and cust.classdept_No='" + dept + "'");
		}
		if (!"-".equals(dlgt)) {
			sqlStr.append(" and att.delegray=" + dlgt + "");
		}
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("duty", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("attendSign", Hibernate.STRING);
			return q.list();
		} catch (HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}

	public List getCustInfohandA(int confid, String custno, String custname,
			String duty, String dept) throws HibernateException {
		Session s = getSession();
		// HashMap map = new HashMap();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
				.append(
						" duty.duty as duty,dept.dept_Name as deptName ,att.attend_Sign as attendSign")
				.append(" from ((T_Cif_Customer cust left join T_Cif_Dept dept")
				.append(
						" on cust.classdept_No=dept.dept_Code) left join T_Attendee_List att ")
				.append(" on cust.cut_Id=att.cust_Id) left join T_DUTY duty on")
				.append(" cust.stuemp_No=duty.stuemp_No").append(
						" where att.con_Id=" + confid
								+ " and att.ATTEND_SIGN='00' ");
		if (!"".equals(custno)) {
			sqlStr.append(" and cust.stuemp_No like '%" + custno + "%'");
		}
		if (!"".equals(custname)) {
			sqlStr.append(" and cust.cut_Name like '%" + custname + "%'");
		}
		if (!"".equals(duty)) {
			sqlStr.equals(" and cust.duty_Name like '%" + duty + "%'");
		}
		if (!"-".equals(dept)) {
			sqlStr.append(" and cust.classdept_No='" + dept + "'");
		}
		sqlStr.append(" order by dept.dept_Name ");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("duty", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("attendSign", Hibernate.STRING);
			return q.list();
		} catch (HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}

	public List getCustInfohandB(int confid, String custno, String custname,
			String duty, String dept) throws HibernateException {
		Session s = getSession();
		// HashMap map = new HashMap();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo, ")
				.append(
						"duty.duty as duty,dept.dept_Name as deptName ,att.attend_Sign as attendSign ")
				.append("from T_Cif_Customer cust left join T_Cif_Dept dept ")
				.append("on cust.classdept_No=dept.dept_Code left join  ")
				.append(
						"(select a.COSUMER_ID,his.attend_sign,his.confid from T_PIF_CARD a, ")
				.append(
						"T_RECORDHIS his where a.physical_no=his.physical_no and his.dealornot='0')att ")
				.append(
						"on cust.cut_Id=att.COSUMER_ID left join T_DUTY duty on ")
				.append("cust.stuemp_No=duty.stuemp_No ").append(
						"where att.confid=" + confid);
		if (!"".equals(custno)) {
			sqlStr.append(" and cust.stuemp_No like '%" + custno + "%'");
		}
		if (!"".equals(custname)) {
			sqlStr.append(" and cust.cut_Name like '%" + custname + "%'");
		}
		if (!"".equals(duty)) {
			sqlStr.equals(" and cust.duty_Name like '%" + duty + "%'");
		}
		if (!"-".equals(dept)) {
			sqlStr.append(" and cust.classdept_No='" + dept + "'");
		}
		sqlStr.append(" order by dept.dept_Name ");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("duty", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("attendSign", Hibernate.STRING);
			return q.list();
		} catch (HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}

	public List getCustInfobyids(int confid, String custid)
			throws HibernateException {
		Session s = getSession();
		// HashMap map = new HashMap();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo, ")
				.append(
						"duty.duty as duty,dept.dept_Name as deptName ,att.attend_Sign as attendSign ")
				.append("from ((T_Cif_Customer cust left join T_Cif_Dept dept ")
				.append("on cust.classdept_No=dept.dept_Code )left join  ")
				.append(
						"(select a.COSUMER_ID,his.attend_sign,his.confid from T_PIF_CARD a, ")
				.append(
						"T_RECORDHIS his where a.physical_no=his.physical_no)att ")
				.append(
						"on cust.cut_Id=att.COSUMER_ID) left join T_DUTY duty on ")
				.append("cust.stuemp_No=duty.stuemp_No ").append(
						"where att.confid=" + confid);
		if (!"".equals(custid)) {
			sqlStr.append(" and cust.cut_id = " + custid + "");
		}
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("duty", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("attendSign", Hibernate.STRING);
			return q.list();
		} catch (HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeGroupDAO根据选择的组编号得到该组的人员名单<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-7 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public List getCustGroupList(int groupid) throws HibernateException {
		Session s = getSession();
		// HashMap map = new HashMap();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
				.append("duty.duty as duty,dept.dept_Name as deptName ")
				.append(
						"from (T_Cif_Customer cust left join T_Cif_Dept dept on ")
				.append(
						" cust.classdept_No=dept.dept_Code) left join T_DUTY duty on")
				.append(" cust.stuemp_No=duty.stuemp_No").append(
						" where cust.cut_Id in(select cust_Id from T_Attendee_Group where group_Id="
								+ groupid + ")");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("duty", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("sex", Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.error(he);
			throw he;
		}
	}
	
	public List getCustGroupListOnlyOne(int groupid) throws HibernateException {
		Session s = getSession();
		// HashMap map = new HashMap();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
				.append("dept.dept_Name as deptName ")
				.append(
						"from T_Cif_Customer cust left join T_Cif_Dept dept on ")
				.append(
						" cust.classdept_No=dept.dept_Code ")
				.append(
						" where cust.cut_Id in(select cust_Id from T_Attendee_Group where group_Id="
								+ groupid + ")");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * 根据组编号取得在该组中的人员名单，但不显示已经分配过的人员名单
	 * 
	 * @param groupid
	 * @param attendedList
	 * @return
	 * @throws HibernateException
	 */
	public List getCustGroupList(int confid, int groupid, List attendedList)
			throws HibernateException {
		Session s = getSession();
		StringBuffer custIds = new StringBuffer(1024);
		if (null == attendedList) {
			custIds.append("0");
		} else if (attendedList.size() == 0) {
			custIds.append("0");
		} else {
			for (int i = 0; i < attendedList.size(); i++) {
				Map custMap = (Map) attendedList.get(i);
				if (i == attendedList.size() - 1) {
					custIds.append(custMap.get("custId"));
				} else {
					custIds.append(custMap.get("custId") + ",");
				}
			}
		}
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append("select cust.cut_Id as cutId,cust.cut_Name as cutName,")
				.append(
						"cust.stuemp_No as stuempNo,duty.duty as duty,dept.dept_Name as deptName ")
				.append(
						"from (T_Cif_Customer cust left join T_Cif_Dept dept on ")
				.append(
						" cust.classdept_No=dept.dept_Code) left join T_DUTY duty on")
				.append(" cust.stuemp_No=duty.stuemp_No where cust.cut_Id in")
				.append(
						" (select cust_Id from T_Attendee_Group where group_Id="
								+ groupid + ")").append(
						" and cust.cut_Id not in(" + custIds + ")").append(
						" and cust.cut_id not in(select cust_id from T_ATTENDEE_LIST where con_id="
								+ confid + ")");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("duty", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.error(he);
			throw he;
		}
	}

	public List getCustGroupListExcept(int confid, int groupid, String custIds)
			throws HibernateException {
		Session s = getSession();
		StringBuffer custIdbuff = new StringBuffer(1024);
		if (null == custIds) {
			custIdbuff.append("0");
		} else if ("".equals(custIds)) {
			custIdbuff.append("0");
		} else {
			String[] temp = custIds.split(",");

			for (int i = 0; i < temp.length; i++) {
				if ("".equals(temp[i])) {
					continue;
				}
				if (i == temp.length - 1) {
					custIdbuff.append(temp[i]);
				} else {
					custIdbuff.append(temp[i] + ",");
				}
			}
		}
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append("select cust.cut_Id as cutId,cust.cut_Name as cutName,")
				.append(
						"cust.stuemp_No as stuempNo,duty.duty as duty,dept.dept_Name as deptName ")
				.append(
						"from T_Cif_Customer cust left join T_Cif_Dept dept on ")
				.append(
						" cust.classdept_No=dept.dept_Code left join T_DUTY duty on")
				.append(" cust.stuemp_No=duty.stuemp_No where cust.cut_Id in")
				.append(
						" (select cust_Id from T_Attendee_Group where group_Id="
								+ groupid + ")").append(
						" and cust.cut_Id not in(" + custIdbuff.toString()
								+ ")").append(
						" and cust.cut_id not in(select cust_id from T_ATTENDEE_LIST where con_id="
								+ confid + ")");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("duty", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * 取得已经分配过的人员名单列表 hanjiwei add it 20061122
	 * 
	 * @param confId
	 * @param attendedList
	 * @return
	 * @throws HibernateException
	 */
	public List getAttendedList(int confId, List attendedList)
			throws HibernateException {
		Session s = getSession();
		StringBuffer custIds = new StringBuffer(1024);
		if (null == attendedList) {
			custIds.append("0");
		} else if (attendedList.size() == 0) {
			custIds.append("0");
		} else {
			for (int i = 0; i < attendedList.size(); i++) {
				Map custMap = (Map) attendedList.get(i);
				if (i == attendedList.size() - 1) {
					custIds.append(custMap.get("custId"));
				} else {
					custIds.append(custMap.get("custId") + ",");
				}
			}
		}
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select distinct cust.cut_Id as cutId,cust.cut_Name as cutName,")
				.append(
						"cust.stuemp_No as stuempNo,duty.duty as duty,dept.dept_Name as deptName ")
				.append(
						"from (T_Cif_Customer cust left join T_Cif_Dept dept on ")
				.append(
						" cust.classdept_No=dept.dept_Code) left join T_DUTY duty on")
				.append(" cust.stuemp_No=duty.stuemp_No").append(
						" where cust.cut_Id in(" + custIds + ")").append(
						" or cust.cut_id in (select cust_id from T_ATTENDEE_LIST where con_id="
								+ confId + ")");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("duty", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			System.out.println(sqlStr);
			return q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * File name: AttendeeGroupDAO.java<br>
	 * Description: 获得所有会议名单<br>
	 * Return:
	 * 
	 * @param confId
	 *            Return:
	 * @param attendedList
	 *            Return:
	 * @return Return:
	 * @throws HibernateException
	 *             <br>
	 *             Modify History: <br>
	 *             操作类型 操作人 操作时间 操作内容<br>
	 *             ======================================<br>
	 *             创建 何林青 2007-3-29 <br>
	 * @author 何林青
	 * @version
	 * @since 1.0
	 */
	public List getAllAttendedList(int confId, List attendedList)
			throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		StringBuffer custIds = new StringBuffer(1024);
		if (null == attendedList) {
			custIds.append("0");
		} else if (attendedList.size() == 0) {
			custIds.append("0");
		} else {
			for (int i = 0; i < attendedList.size(); i++) {
				Map custMap = (Map) attendedList.get(i);
				if (i == attendedList.size() - 1) {
					custIds.append(custMap.get("custId"));
				} else {
					custIds.append(custMap.get("custId") + ",");
				}
			}
		}
		sqlStr
				.append(
						"select distinct cust.cut_Id as cutId,cust.cut_Name as cutName,")
				.append(
						"cust.stuemp_No as stuempNo,duty.duty as duty,dept.dept_Name as deptName,")
				.append(
						"fullatt.delegray as delegray,fullatt.dlgt_name as dlgtName,")
				.append(
						"fullatt.attendee_type as attendeeType,fullatt.dict_caption as dictCaption ")
				.append(
						"from ((T_Cif_Customer cust left join T_Cif_Dept dept on ")
				.append(
						"cust.classdept_No=dept.dept_Code) left join T_DUTY duty on ")
				.append("cust.stuemp_No=duty.stuemp_No) left join ")
				.append(
						"(select att.con_id,att.cust_id,att.delegray,dele.dlgt_name,att.attendee_type,dic.dict_caption ")
				.append("from (T_ATTENDEE_LIST att left join T_DELEGATE dele ")
				.append(
						"on att.delegray=dele.DLGT_ID) left join T_Pif_Dictionary dic ")
				.append(
						"on att.attendee_type=dic.dict_value and dic.dict_no=78 where att.con_id="
								+ confId + " ").append(
						"and att.cust_id in(" + custIds
								+ "))fullatt on cust.cut_id=fullatt.cust_id ")
				.append("where cust.cut_Id in(" + custIds + ") ").append(
						"order by fullatt.delegray");

		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("duty", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("delegray", Hibernate.INTEGER);
			q.addScalar("dlgtName", Hibernate.STRING);
			q.addScalar("attendeeType", Hibernate.STRING);
			q.addScalar("dictCaption", Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.error(he);
			throw he;
		}
	}

	public List getFirstAttendedList(int confId) throws HibernateException {
		Session s = getSession();

		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select distinct cust.cut_Id as cutId,cust.cut_Name as cutName,")
				.append(
						"cust.stuemp_No as stuempNo,duty.duty as duty,dept.dept_Name as deptName,")
				.append(
						"fullatt.delegray as delegray,fullatt.dlgt_name as dlgtName,")
				.append(
						"fullatt.attendee_type as attendeeType,fullatt.dict_caption as dictCaption ")
				.append(
						"from ((T_Cif_Customer cust left join T_Cif_Dept dept on ")
				.append(
						"cust.classdept_No=dept.dept_Code) left join T_DUTY duty on ")
				.append("cust.stuemp_No=duty.stuemp_No) left join ")
				.append(
						"(select att.con_id,att.cust_id,att.delegray,dele.dlgt_name,att.attendee_type,dic.dict_caption ")
				.append("from (T_ATTENDEE_LIST att left join T_DELEGATE dele ")
				.append(
						"on att.delegray=dele.DLGT_ID) left join T_Pif_Dictionary dic ")
				.append(
						"on att.attendee_type=dic.dict_value where att.con_id="
								+ confId + " ")
				.append(
						"and dic.dict_no=78)fullatt on cust.cut_id=fullatt.cust_id ")
				.append("where fullatt.con_id=" + confId + " ").append(
						"order by fullatt.delegray");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("duty", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("delegray", Hibernate.INTEGER);
			q.addScalar("dlgtName", Hibernate.STRING);
			q.addScalar("attendeeType", Hibernate.STRING);
			q.addScalar("dictCaption", Hibernate.STRING);
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
	 * Description: AttendeeGroupDAO把人员从组里面删除<br>
	 * Return: void<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-7 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public void deleteCustGroup(int groupid, int custid)
			throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TAttendeeGroup where id.groupId="
					+ groupid + " and id.custId=" + custid);
			Iterator iter = q.list().iterator();
			while (iter.hasNext()) {
				s.delete((TAttendeeGroup) iter.next());
			}
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * File name: AttendeeGroupDAO.java<br>
	 * Description: 删除所有的group<br>
	 * Return:
	 * 
	 * @throws HibernateException
	 *             <br>
	 *             Modify History: <br>
	 *             操作类型 操作人 操作时间 操作内容<br>
	 *             ======================================<br>
	 *             创建 何林青 2007-1-15 <br>
	 * @author 何林青
	 * @version
	 * @since 1.0
	 */
	public void deleteAllCustGroup() throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery("delete from TAttendeeGroup");
			q.executeUpdate();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeGroupDAO根据组编号和客户号查找是否存在该分组人员<br>
	 * Return: boolean存在返回true,否则返回false<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-24 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public boolean existsAttendeeGroup(int groupid, int custid)
			throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TAttendeeGroup where id.groupId="
					+ groupid + " and id.custId=" + custid);
			if (q.list().size() > 0) {
				return true;
			} else {
				return false;
			}
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	public TRecordhis getRecordhis(int confId, String custId) {

		TRecordhis his = null;
		List list = null;
		Session s = getSession();
		try {

			Query q = s
					.createQuery("select physicalNo from TPifCard where cosumerId="
							+ custId);
			list = q.list();
			Iterator iter = list.iterator();
			if (iter.hasNext()) {
				Query q1 = s.createQuery("from TRecordhis where physicalNo='"
						+ iter.next().toString() + "'");
				List list1 = q1.list();
				Iterator iter1 = list1.iterator();
				if (iter1.hasNext()) {
					his = (TRecordhis) iter1.next();
				}
			}

			return his;
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.error(he);
		} catch (Exception e) {
			e.printStackTrace();
			errlog.error(e);
		}
		System.out.print("aaaaaaaaaaaaa");
		return null;
	}

	/**
	 * Method name: getCustInfo<br>
	 * Description: 通过物理卡号查询客户信息<br>
	 * Return: List<br>
	 * Args:
	 * 
	 * @param physicalno
	 *            Args:
	 * @return Args:
	 * @throws HibernateException
	 *             Modify History: <br>
	 *             操作类型 操作人 操作时间 操作内容<br>
	 *             ======================================<br>
	 *             创建 何林青 Oct 18, 2007 <br>
	 * @author 何林青
	 * @version
	 * @since 1.0
	 */
	public List getCustInfo(String physicalno) throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select cust.cut_id as cutId,cust.cut_type as cutType,cuttype.type_name as typeName,")
				.append("cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
				.append(
						"cust.classdept_No as deptNo,dept.dept_Name as deptName,")
				.append(
						"cust.s_code as sCode,special.s_name as sName,cust.sex,dict.dict_caption as dictCaption ")
				.append(
						"from ykt_cur.T_CIF_CUSTOMER cust left join YKT_CUR.T_PIF_CARD card on ")
				.append(
						"cust.cut_id=card.COSUMER_ID left join YKT_CUR.T_Cif_Dept dept on ")
				.append(
						"cust.classdept_No=dept.dept_Code left join YKT_CUR.T_CIF_CUTTYPEFEE cuttype on ")
				.append(
						"cust.CUT_TYPE=cuttype.CUT_TYPE left join YKT_CUR.T_PIF_DICTIONARY dict on ")
				.append("cust.sex=dict.dict_value and dict.dict_no=39 ")
				.append("left join YKT_CUR.T_CIF_SPECIALITY special on ")
				.append("cust.s_code=special.s_code ").append(
						" where card.PHYSICAL_NO='" + physicalno + "'");

		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutType", Hibernate.INTEGER);
			q.addScalar("typeName", Hibernate.STRING);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("deptNo", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("sCode", Hibernate.STRING);
			q.addScalar("sName", Hibernate.STRING);
			q.addScalar("sex", Hibernate.STRING);
			q.addScalar("dictCaption", Hibernate.STRING);
			return q.list();
		} catch (HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}

}
