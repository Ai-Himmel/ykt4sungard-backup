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
		StringBuffer custIds = new StringBuffer();
		StringBuffer custIds1 = new StringBuffer();
		StringBuffer custIds2 = new StringBuffer();
		StringBuffer custIds3 = new StringBuffer();
		StringBuffer custIds4 = new StringBuffer();
		if (null == custAllotList) {
			custIds.append("0");
			custIds1.append("0");
			custIds2.append("0");
			custIds3.append("0");
			custIds4.append("0");
		} else if (custAllotList.size() == 0) {
			custIds.append("0");
			custIds1.append("0");
			custIds2.append("0");
			custIds3.append("0");
			custIds4.append("0");
		} else {
			if(custAllotList.size()<1000){
				for (int i = 0; i < custAllotList.size(); i++) {
					Map custMap = (Map) custAllotList.get(i);
					if (i == custAllotList.size() - 1) {
						custIds.append(custMap.get("custId"));
					} else {
						custIds.append(custMap.get("custId") + ",");
					}
				}
				custIds1.append("0");
				custIds2.append("0");
				custIds3.append("0");
				custIds4.append("0");
			}else if(custAllotList.size()<2000){
				for (int i = 0; i < 1000; i++) {
					Map custMap = (Map) custAllotList.get(i);
					if (i == 1000 - 1) {
						custIds.append(custMap.get("custId"));
					} else {
						custIds.append(custMap.get("custId") + ",");
					}
				}
				for (int i = 1000; i < custAllotList.size(); i++) {
					Map custMap = (Map) custAllotList.get(i);
					if (i == custAllotList.size() - 1) {
						custIds1.append(custMap.get("custId"));
					} else {
						custIds1.append(custMap.get("custId") + ",");
					}
				}
				custIds2.append("0");
				custIds3.append("0");
				custIds4.append("0");
			}else if(custAllotList.size()<3000){
				for (int i = 0; i < 1000; i++) {
					Map custMap = (Map) custAllotList.get(i);
					if (i == 1000 - 1) {
						custIds.append(custMap.get("custId"));
					} else {
						custIds.append(custMap.get("custId") + ",");
					}
				}
				for (int i = 1000; i < 2000; i++) {
					Map custMap = (Map) custAllotList.get(i);
					if (i == 2000 - 1) {
						custIds1.append(custMap.get("custId"));
					} else {
						custIds1.append(custMap.get("custId") + ",");
					}
				}
				for (int i = 2000; i < custAllotList.size(); i++) {
					Map custMap = (Map) custAllotList.get(i);
					if (i == custAllotList.size() - 1) {
						custIds2.append(custMap.get("custId"));
					} else {
						custIds2.append(custMap.get("custId") + ",");
					}
				}
				custIds3.append("0");
				custIds4.append("0");
			}else if(custAllotList.size()<4000){
				for (int i = 0; i < 1000; i++) {
					Map custMap = (Map) custAllotList.get(i);
					if (i == 1000 - 1) {
						custIds.append(custMap.get("custId"));
					} else {
						custIds.append(custMap.get("custId") + ",");
					}
				}
				for (int i = 1000; i < 2000; i++) {
					Map custMap = (Map) custAllotList.get(i);
					if (i == 2000 - 1) {
						custIds1.append(custMap.get("custId"));
					} else {
						custIds1.append(custMap.get("custId") + ",");
					}
				}
				for (int i = 2000; i < 3000; i++) {
					Map custMap = (Map) custAllotList.get(i);
					if (i == 3000 - 1) {
						custIds2.append(custMap.get("custId"));
					} else {
						custIds2.append(custMap.get("custId") + ",");
					}
				}
				for (int i = 3000; i < custAllotList.size(); i++) {
					Map custMap = (Map) custAllotList.get(i);
					if (i == custAllotList.size() - 1) {
						custIds3.append(custMap.get("custId"));
					} else {
						custIds3.append(custMap.get("custId") + ",");
					}
				}
				custIds4.append("0");
			}else if(custAllotList.size()<5000){
				for (int i = 0; i < 1000; i++) {
					Map custMap = (Map) custAllotList.get(i);
					if (i == 1000 - 1) {
						custIds.append(custMap.get("custId"));
					} else {
						custIds.append(custMap.get("custId") + ",");
					}
				}
				for (int i = 1000; i < 2000; i++) {
					Map custMap = (Map) custAllotList.get(i);
					if (i == 2000 - 1) {
						custIds1.append(custMap.get("custId"));
					} else {
						custIds1.append(custMap.get("custId") + ",");
					}
				}
				for (int i = 2000; i < 3000; i++) {
					Map custMap = (Map) custAllotList.get(i);
					if (i == 3000 - 1) {
						custIds2.append(custMap.get("custId"));
					} else {
						custIds2.append(custMap.get("custId") + ",");
					}
				}
				for (int i = 3000; i < 4000; i++) {
					Map custMap = (Map) custAllotList.get(i);
					if (i == 4000 - 1) {
						custIds3.append(custMap.get("custId"));
					} else {
						custIds3.append(custMap.get("custId") + ",");
					}
				}
				for (int i = 4000; i < custAllotList.size(); i++) {
					Map custMap = (Map) custAllotList.get(i);
					if (i == custAllotList.size() - 1) {
						custIds4.append(custMap.get("custId"));
					} else {
						custIds4.append(custMap.get("custId") + ",");
					}
				}
			}
			
		
		}
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select cust.custid as cutId,cust.custname as cutName,cust.stuempno as stuempNo,")
				.append(
						" duty.duty as dutyName,dept.deptname as deptName,duty.duty as duty ")
				.append(
						" from ykt_cur.T_CUSTOMER cust left join YKT_CUR.T_Dept dept on ")
				.append(
						" cust.deptcode=dept.deptcode left join YKT_CONF.T_DUTY duty on")
				.append(" cust.stuempno=duty.stuemp_No")
				.append(" where cust.custid not in(" + custIds + ") " +
						"and cust.custid not in(" + custIds1 + ") " +
						"and cust.custid not in(" + custIds2 + ") " +
						"and cust.custid not in(" + custIds3+ ") " +
						"and cust.custid not in(" + custIds4 + ") ")
				.append(
						" and cust.custid not in(select cust_id from YKT_CONF.T_ATTENDEE_LIST where con_id="
								+ confid + ")");
		if (!"".equals(custno.trim())) {
			sqlStr.append(" and cust.stuempno = '" + custno + "'");
		}
		if (!"".equals(custname)) {
			sqlStr.append(" and cust.custname like '%" + custname + "%'");
		}
		if ((!"".equals(duty))) {
			sqlStr.append(" and duty.duty like '%" + duty + "%'");
		}
		if ((!"".equals(dept)) && (!"-".equals(dept))) {
			sqlStr.append(" and cust.deptcode='" + dept + "'");
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
	
	public List getCustInfo(String[] stuempNos, String[] custNames, String duty,String dept, int confid)throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select cust.custid as cutId,cust.custname as cutName,cust.stuempno as stuempNo,");
		sqlStr.append(" duty.duty as dutyName,dept.deptname as deptName,duty.duty as duty ");
		sqlStr.append(" from ykt_cur.T_CUSTOMER cust left join YKT_CUR.T_Dept dept on ");
		sqlStr.append(" cust.deptcode=dept.deptcode left join YKT_CONF.T_DUTY duty on");
		sqlStr.append(" cust.stuempno=duty.stuemp_No");
		sqlStr.append(" where cust.custid not in(select cust_id from YKT_CONF.T_ATTENDEE_LIST where con_id=").append(confid).append(")");
		if(stuempNos!=null && stuempNos.length>0){
			sqlStr.append(" and cust.stuempno in (");
			for(int i=0;i<stuempNos.length;i++){
				sqlStr.append("'").append(stuempNos[i]).append("',");
			}
			sqlStr = sqlStr.deleteCharAt(sqlStr.length()-1);
			sqlStr.append(")");
			
		}
		if(custNames!=null && custNames.length>0){
			sqlStr.append(" and cust.custname in (");
			for(int i=0;i<custNames.length;i++){
				sqlStr.append("'").append(custNames[i]).append("',");
			}
			sqlStr = sqlStr.deleteCharAt(sqlStr.length()-1);
			sqlStr.append(")");
		}
		
		if ((!"".equals(duty))) {
			sqlStr.append(" and duty.duty like '%" + duty + "%'");
		}
		if ((!"".equals(dept)) && (!"-".equals(dept))) {
			sqlStr.append(" and cust.deptcode='" + dept + "'");
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
						"select cust.custid as cutId,cust.custtype as cutType,cuttype.custtypename as typeName,")
				.append("cust.custname as cutName,cust.stuempno as stuempNo,")
				.append("cust.deptcode as deptNo,dept.deptname as deptName,")
				.append(
						"cust.specialtycode as sCode,special.specialtyname as sName,cust.sex,dict.dictcaption as dictCaption ")
				.append(
						"from ykt_cur.T_CUSTOMER cust left join YKT_CUR.T_CARD card on ")
				.append(
						"cust.custid=card.custid left join YKT_CUR.T_Dept dept on ")
				.append(
						"cust.deptcode=dept.deptcode left join YKT_CUR.T_CUTTYPE cuttype on ")
				.append(
						"cust.custtype=cuttype.custtype left join YKT_CUR.T_DICTIONARY dict on ")
				.append("cust.sex=dict.dictval and dict.dicttype=39 ").append(
						"left join YKT_CUR.T_SPECIALITY special on ").append(
						"cust.specialtycode=special.specialtycode ").append(
						" where card.cardphyid='" + physicalno + "'");

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
						"select cust.custid as cutId,cust.custname as cutName,cust.stuempno as stuempNo,")
				.append(
						" duty.duty as duty,dept.deptname as deptName ,att.attend_sign as attendSign")
				.append(
						" from ykt_cur.T_Customer cust left join ykt_cur.T_Dept dept")
				.append(
						" on cust.deptcode=dept.deptcode left join ykt_conf.T_Attendee_List att ")
				.append(
						" on cust.custid=att.cust_id left join YKT_CONF.T_DUTY duty on")
				.append(" cust.stuempno=duty.stuemp_No").append(
						" where att.ATTEND_SIGN='00' and att.con_Id=" + confid);
		if (!"".equals(custno)) {
			sqlStr.append(" and cust.stuempno like '%" + custno + "%'");
		}
		if (!"".equals(custname)) {
			sqlStr.append(" and cust.custname like '%" + custname + "%'");
		}
		if (!"".equals(duty)) {
			sqlStr.equals(" and cust.duty_Name like '%" + duty + "%'");
		}
		if (!"-".equals(dept)) {
			sqlStr.append(" and cust.deptcode='" + dept + "'");
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
						"select cust.custid as cutId,cust.custname as cutName,cust.stuempno as stuempNo,")
				.append(
						" duty.duty as duty,dept.deptname as deptName ,att.attend_Sign as attendSign")
				.append(
						" from ykt_cur.T_Customer cust left join ykt_cur.T_Dept dept")
				.append(
						" on cust.deptcode=dept.deptcode left join ykt_conf.T_Attendee_List att ")
				.append(
						" on cust.custid=att.cust_id left join YKT_CONF.T_DUTY duty on")
				.append(" cust.stuempno=duty.stuemp_No")
				.append(
						" where (att.ATTEND_SIGN='00' or att.ATTEND_SIGN='13' or att.ATTEND_SIGN='23') and att.con_Id="
								+ confid);
		if (!"".equals(custno)) {
			sqlStr.append(" and cust.stuempno like '%" + custno + "%'");
		}
		if (!"".equals(custname)) {
			sqlStr.append(" and cust.custname like '%" + custname + "%'");
		}
		if (!"".equals(duty)) {
			sqlStr.equals(" and duty.duty like '%" + duty + "%'");
		}
		if (!"-".equals(dept)) {
			sqlStr.append(" and cust.deptcode='" + dept + "'");
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
						"select cust.custid as cutId,cust.custname as cutName,cust.stuempno as stuempNo,")
				.append(
						" duty.duty as duty,dept.deptname as deptName ,att.attend_Sign as attendSign")
				.append(
						" from ykt_cur.T_Customer cust left join ykt_cur.T_Dept dept")
				.append(
						" on cust.deptcode=dept.deptcode left join ykt_conf.T_Attendee_List att ")
				.append(
						" on cust.custid=att.cust_id left join YKT_CONF.T_DUTY duty on")
				.append(" cust.stuempno=duty.stuemp_No").append(
						" where (att.ATTEND_SIGN='00' or att.ATTEND_SIGN='30') and att.con_Id="
								+ confid);
		if (!"".equals(custno)) {
			sqlStr.append(" and cust.stuempno like '%" + custno + "%'");
		}
		if (!"".equals(custname)) {
			sqlStr.append(" and cust.custname like '%" + custname + "%'");
		}
		if (!"".equals(duty)) {
			sqlStr.equals(" and duty.duty like '%" + duty + "%'");
		}
		if (!"-".equals(dept)) {
			sqlStr.append(" and cust.deptcode='" + dept + "'");
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
						"select cust.custid as cutId,cust.custname as cutName,cust.stuempno as stuempNo,")
				.append(
						" duty.duty as duty,dept.deptname as deptName ,att.attend_Sign as attendSign")
				.append(
						" from ykt_cur.T_Customer cust left join ykt_cur.T_Dept dept")
				.append(
						" on cust.deptcode=dept.deptcode left join ykt_conf.T_Attendee_List att ")
				.append(
						" on cust.custid=att.cust_id left join YKT_CONF.T_DUTY duty on")
				.append(" cust.stuempno=duty.stuemp_No")
				.append(
						" where (att.ATTEND_SIGN='00' or att.ATTEND_SIGN='12' or att.ATTEND_SIGN='22') and att.con_id="
								+ confid);
		if (!"".equals(custno)) {
			sqlStr.append(" and cust.stuempno like '%" + custno + "%'");
		}
		if (!"".equals(custname)) {
			sqlStr.append(" and cust.custname like '%" + custname + "%'");
		}
		if (!"".equals(duty)) {
			sqlStr.equals(" and duty.duty like '%" + duty + "%'");
		}
		if (!"-".equals(dept)) {
			sqlStr.append(" and cust.deptcode='" + dept + "'");
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
	
	//直接从一卡通取人员
	public List getEcardCustInfoSPE(int confid, String custno, String custname,
			String duty, String dept, String dlgt) throws HibernateException {
		Session s = getSession();
		// HashMap map = new HashMap();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select cust.custid as cutId,cust.custname as cutName,cust.stuempno as stuempNo,")
				.append(
						" duty.duty as duty,dept.deptname as deptName ,'00' as attendSign")
				.append(
						" from ykt_cur.T_Customer cust left join ykt_cur.T_Dept dept")
				.append(
						" on cust.deptcode=dept.deptcode left join YKT_CONF.T_DUTY duty on")
				.append(" cust.stuempno=duty.stuemp_No")
				.append(
						" where 1=1 ");
		if (!"".equals(custno)) {
			sqlStr.append(" and cust.stuempno like '%" + custno + "%'");
		}
		if (!"".equals(custname)) {
			sqlStr.append(" and cust.custname like '%" + custname + "%'");
		}
		if (!"".equals(duty)) {
			sqlStr.equals(" and duty.duty like '%" + duty + "%'");
		}
		if (!"-".equals(dept)) {
			sqlStr.append(" and cust.deptcode='" + dept + "'");
		}
//		if (!"-".equals(dlgt)) {
//			sqlStr.append(" and att.delegray=" + dlgt + "");
//		}
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
		// sqlStr
		// .append(
		// "select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No
		// as stuempNo,")
		// .append(
		// " duty.duty as duty,dept.dept_Name as deptName ,att.attend_Sign as
		// attendSign")
		// .append(
		// " from ykt_conf.T_Attendee_List att left join ykt_cur.T_Cif_Customer
		// cust ")
		// .append("on cust.cut_Id=att.cust_Id left join ykt_cur.T_Cif_Dept dept
		// ")
		// .append(
		// " on cust.classdept_No=dept.dept_Code ")
		// .append(
		// "left join YKT_CONF.T_DUTY duty on")
		// .append(" cust.stuemp_No=duty.stuemp_No").append(
		// " where att.con_Id=" + confid
		// + " and att.ATTEND_SIGN='00' ");
		sqlStr
				.append(
						"select cust.custid as cutId,cust.custname as cutName,cust.stuempno as stuempNo,")
				.append(
						" duty.duty as duty,dept.deptname as deptName ,att.attend_Sign as attendSign")
				.append(
						" from ykt_conf.T_Attendee_List att left join ykt_cur.T_Customer cust ")
				.append(
						"on cust.custid=att.cust_id left join ykt_cur.T_Dept dept ")
				.append(
						" on cust.deptcode=dept.deptcode left join YKT_CONF.T_DUTY duty on ")
				.append(" cust.stuempno=duty.stuemp_no ").append(
						" where att.con_id=" + confid
								+ " and att.ATTEND_SIGN='00' ");
		if (!"".equals(custno)) {
			sqlStr.append(" and cust.stuempno like '%" + custno + "%'");
		}
		if (!"".equals(custname)) {
			sqlStr.append(" and cust.custname like '%" + custname + "%'");
		}
		if (!"".equals(duty)) {
			sqlStr.equals(" and duty.duty like '%" + duty + "%'");
		}
		if (!"-".equals(dept)) {
			sqlStr.append(" and cust.deptcode='" + dept + "'");
		}
		sqlStr.append(" order by dept.deptname ");
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
		// sqlStr
		// .append(
		// "select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No
		// as stuempNo, ")
		// .append(
		// "duty.duty as duty,dept.dept_Name as deptName ,att.attend_Sign as
		// attendSign ")
		// .append(
		// "from (select a.COSUMER_ID,his.attend_sign,his.confid from
		// YKT_CUR.T_PIF_CARD a, ")
		// .append(
		// "ykt_conf.T_RECORDHIS his where a.physical_no=his.physical_no and
		// his.dealornot='0')att ")
		//				
		// .append(
		// "left join ykt_cur.T_Cif_Customer cust on cust.cut_Id=att.COSUMER_ID
		// left join ykt_cur.T_Cif_Dept dept ")
		// .append("on cust.classdept_No=dept.dept_Code ")
		//				
		// .append(" left join YKT_CONF.T_DUTY duty on ")
		// .append("cust.stuemp_No=duty.stuemp_No ").append(
		// "where att.confid=" + confid);
		sqlStr
				.append(
						"select cust.custid as cutId,cust.custname as cutName,cust.stuempno as stuempNo, ")
				.append(
						"duty.duty as duty,dept.deptname as deptName ,att.attend_Sign as attendSign ")
				.append(
						"from (select a.custid,his.attend_sign,his.confid from YKT_CUR.T_CARD a, ")
				.append(
						"ykt_conf.T_RECORDHIS his where a.cardphyid=his.physical_no and his.dealornot='0' and a.status||a.lossflag='10')att ")

				.append(
						"left join ykt_cur.T_Customer cust on cust.custid=att.custid left join ykt_cur.T_Dept dept ")
				.append(
						"on cust.deptcode=dept.deptcode  left join YKT_CONF.T_DUTY duty on ")
				.append(" cust.stuempno=duty.stuemp_no ").append(
						"where att.confid=" + confid);

		if (!"".equals(custno)) {
			sqlStr.append(" and cust.stuempno like '%" + custno + "%'");
		}
		if (!"".equals(custname)) {
			sqlStr.append(" and cust.custname like '%" + custname + "%'");
		}
		if (!"".equals(duty)) {
			sqlStr.equals(" and duty.duty like '%" + duty + "%'");
		}
		if (!"-".equals(dept)) {
			sqlStr.append(" and cust.deptcode='" + dept + "'");
		}
		sqlStr.append(" order by dept.deptname ");
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
						"select cust.custid as cutId,cust.custname as cutName,cust.stuempno as stuempNo, ")
				.append(
						"duty.duty as duty,dept.deptname as deptName ,att.attend_Sign as attendSign ")
				.append(
						"from ykt_cur.T_Customer cust left join ykt_cur.T_Dept dept ")
				.append("on cust.deptcode=dept.deptcode left join  ")
				.append(
						"(select a.custid,his.attend_sign,his.confid from YKT_CUR.T_CARD a, ")
				.append(
						"ykt_conf.T_RECORDHIS his where a.cardphyid=his.physical_no)att ")
				.append(
						"on cust.custid=att.custid left join YKT_CONF.T_DUTY duty on ")
				.append("cust.stuempno=duty.stuemp_No ").append(
						"where att.confid=" + confid);
		if (!"".equals(custid)) {
			sqlStr.append(" and cust.custid = " + custid + "");
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
						"select cust.custid as cutId,cust.custname as cutName,cust.stuempno as stuempNo,")
				.append(
						"duty.duty as duty,dept.deptname as deptName,cust.sex as sex ")
				.append(
						"from ykt_cur.T_Customer cust left join ykt_cur.T_Dept dept on ")
				.append(
						" cust.deptcode=dept.deptcode left join YKT_CONF.T_DUTY duty on")
				.append(" cust.stuempno=duty.stuemp_No")
				.append(
						" where cust.custid in(select cust_Id from ykt_conf.T_Attendee_Group where group_Id="
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
						"select cust.custid as cutId,cust.custname as cutName,cust.stuempno as stuempNo,")
				.append("dept.deptname as deptName ")
				.append(
						"from ykt_cur.T_Customer cust left join ykt_cur.T_Dept dept on ")
				.append(" cust.deptcode=dept.deptcode ")
				.append(
						" where cust.custid in(select cust_Id from ykt_conf.T_Attendee_Group where group_Id="
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
				.append("select cust.custid as cutId,cust.custname as cutName,")
				.append(
						"cust.stuempno as stuempNo,duty.duty as duty,dept.deptname as deptName ")
				.append(
						"from ykt_cur.T_Customer cust left join ykt_cur.T_Dept dept on ")
				.append(
						" cust.deptcode=dept.deptcode left join YKT_CONF.T_DUTY duty on")
				.append(" cust.stuempno=duty.stuemp_No where cust.custid in")
				.append(
						" (select cust_Id from ykt_conf.T_Attendee_Group where group_Id="
								+ groupid + ")")
				.append(" and cust.custid not in(" + custIds + ")")
				.append(
						" and cust.custid not in(select cust_id from YKT_CONF.T_ATTENDEE_LIST where con_id="
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
		StringBuffer custIdbuff = new StringBuffer();
		StringBuffer custIdbuff1 = new StringBuffer();
		StringBuffer custIdbuff2 = new StringBuffer();
		StringBuffer custIdbuff3 = new StringBuffer();
		StringBuffer custIdbuff4 = new StringBuffer();
		if (null == custIds) {
			custIdbuff.append("0");
			custIdbuff1.append("0");
			custIdbuff2.append("0");
			custIdbuff3.append("0");
			custIdbuff4.append("0");
		} else if ("".equals(custIds)) {
			custIdbuff.append("0");
			custIdbuff1.append("0");
			custIdbuff2.append("0");
			custIdbuff3.append("0");
			custIdbuff4.append("0");
		} else {
			String[] temp = custIds.split(",");
			if(temp.length<1000){
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
				custIdbuff1.append("0");
				custIdbuff2.append("0");
				custIdbuff3.append("0");
				custIdbuff4.append("0");
			}else if(temp.length<2000){
				for (int i = 0; i < 1000; i++) {
					if ("".equals(temp[i])) {
						continue;
					}
					if (i == 1000 - 1) {
						custIdbuff.append(temp[i]);
					} else {
						custIdbuff.append(temp[i] + ",");
					}
				}
				for (int i = 1000; i < temp.length; i++) {
					if ("".equals(temp[i])) {
						continue;
					}
					if (i == temp.length - 1) {
						custIdbuff1.append(temp[i]);
					} else {
						custIdbuff1.append(temp[i] + ",");
					}
				}
				custIdbuff2.append("0");
				custIdbuff3.append("0");
				custIdbuff4.append("0");
			}else if(temp.length<3000){
				for (int i = 0; i < 1000; i++) {
					if ("".equals(temp[i])) {
						continue;
					}
					if (i == 1000 - 1) {
						custIdbuff.append(temp[i]);
					} else {
						custIdbuff.append(temp[i] + ",");
					}
				}
				for (int i = 1000; i < 2000; i++) {
					if ("".equals(temp[i])) {
						continue;
					}
					if (i == 2000 - 1) {
						custIdbuff1.append(temp[i]);
					} else {
						custIdbuff1.append(temp[i] + ",");
					}
				}
				for (int i = 2000; i < temp.length; i++) {
					if ("".equals(temp[i])) {
						continue;
					}
					if (i == temp.length - 1) {
						custIdbuff2.append(temp[i]);
					} else {
						custIdbuff2.append(temp[i] + ",");
					}
				}
				custIdbuff3.append("0");
				custIdbuff4.append("0");
			}else if(temp.length<4000){
				for (int i = 0; i < 1000; i++) {
					if ("".equals(temp[i])) {
						continue;
					}
					if (i == 1000 - 1) {
						custIdbuff.append(temp[i]);
					} else {
						custIdbuff.append(temp[i] + ",");
					}
				}
				for (int i = 1000; i < 2000; i++) {
					if ("".equals(temp[i])) {
						continue;
					}
					if (i == 2000 - 1) {
						custIdbuff1.append(temp[i]);
					} else {
						custIdbuff1.append(temp[i] + ",");
					}
				}
				for (int i = 2000; i < 3000; i++) {
					if ("".equals(temp[i])) {
						continue;
					}
					if (i == 3000 - 1) {
						custIdbuff2.append(temp[i]);
					} else {
						custIdbuff2.append(temp[i] + ",");
					}
				}
				for (int i = 3000; i < temp.length; i++) {
					if ("".equals(temp[i])) {
						continue;
					}
					if (i == temp.length - 1) {
						custIdbuff3.append(temp[i]);
					} else {
						custIdbuff3.append(temp[i] + ",");
					}
				}
				custIdbuff4.append("0");
			}else if(temp.length<4000){
				for (int i = 0; i < 1000; i++) {
					if ("".equals(temp[i])) {
						continue;
					}
					if (i == 1000 - 1) {
						custIdbuff.append(temp[i]);
					} else {
						custIdbuff.append(temp[i] + ",");
					}
				}
				for (int i = 1000; i < 2000; i++) {
					if ("".equals(temp[i])) {
						continue;
					}
					if (i == 2000 - 1) {
						custIdbuff1.append(temp[i]);
					} else {
						custIdbuff1.append(temp[i] + ",");
					}
				}
				for (int i = 2000; i < 3000; i++) {
					if ("".equals(temp[i])) {
						continue;
					}
					if (i == 3000 - 1) {
						custIdbuff2.append(temp[i]);
					} else {
						custIdbuff2.append(temp[i] + ",");
					}
				}
				for (int i = 3000; i < 4000; i++) {
					if ("".equals(temp[i])) {
						continue;
					}
					if (i == temp.length - 1) {
						custIdbuff3.append(temp[i]);
					} else {
						custIdbuff3.append(temp[i] + ",");
					}
				}
				for (int i = 3000; i < temp.length; i++) {
					if ("".equals(temp[i])) {
						continue;
					}
					if (i == temp.length - 1) {
						custIdbuff4.append(temp[i]);
					} else {
						custIdbuff4.append(temp[i] + ",");
					}
				}
			}
			
		}
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append("select cust.custid as cutId,cust.custname as cutName,")
				.append(
						"cust.stuempno as stuempNo,duty.duty as duty,dept.deptname as deptName ")
				.append(
						"from ykt_cur.T_Customer cust left join ykt_cur.T_Dept dept on ")
				.append(
						" cust.deptcode=dept.deptcode left join YKT_CONF.T_DUTY duty on")
				.append(" cust.stuempno=duty.stuemp_No where cust.custid in")
				.append(
						" (select cust_Id from ykt_conf.T_Attendee_Group where group_Id="
								+ groupid + ")")
				.append(
						" and cust.custid not in(" + custIdbuff.toString()
								+ ")  and cust.custid not in(" + custIdbuff1.toString()
								+ ")  and cust.custid not in(" + custIdbuff2.toString()
								+ ")  and cust.custid not in(" + custIdbuff3.toString()
								+ ")  and cust.custid not in(" + custIdbuff4.toString()
								+ ") ")
				.append(
						" and cust.custid not in(select cust_id from YKT_CONF.T_ATTENDEE_LIST where con_id="
								+ confid + ") order by cust.custid");
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
						"select distinct cust.custid as cutId,cust.custname as cutName,")
				.append(
						"cust.stuempno as stuempNo,duty.duty as duty,dept.deptname as deptName ")
				.append(
						"from ykt_cur.T_Customer cust left join ykt_cur.T_Dept dept on ")
				.append(
						" cust.deptcode=dept.deptcode left join YKT_CONF.T_DUTY duty on")
				.append(" cust.stuempno=duty.stuemp_No")
				.append(" where cust.custid in(" + custIds + ")")
				.append(
						" or cust.custid in (select cust_id from YKT_CONF.T_ATTENDEE_LIST where con_id="
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
		StringBuffer custIds = new StringBuffer();
		StringBuffer custIds1 = new StringBuffer();
		StringBuffer custIds2 = new StringBuffer();
		StringBuffer custIds3 = new StringBuffer();
		StringBuffer custIds4 = new StringBuffer();

		if (null == attendedList) {
			custIds.append("0");
			custIds1.append("0");
			custIds2.append("0");
			custIds3.append("0");
			custIds4.append("0");
		} else if (attendedList.size() == 0) {
			custIds.append("0");
			custIds1.append("0");
			custIds2.append("0");
			custIds3.append("0");
			custIds4.append("0");
		} else {
			if (attendedList.size() < 1000) {

				for (int i = 0; i < attendedList.size(); i++) {
					Map custMap = (Map) attendedList.get(i);
					if (i == attendedList.size() - 1) {
						custIds.append(custMap.get("custId"));
					} else {
						custIds.append(custMap.get("custId") + ",");
					}
				}
				custIds1.append("0");
				custIds2.append("0");
				custIds3.append("0");
				custIds4.append("0");

			} else if (attendedList.size() < 2000) {
				for (int i = 0; i < 1000; i++) {
					Map custMap = (Map) attendedList.get(i);
					if (i == 999) {
						custIds.append(custMap.get("custId"));
					} else {
						custIds.append(custMap.get("custId") + ",");
					}
				}

				for (int i = 1000; i < attendedList.size(); i++) {
					Map custMap = (Map) attendedList.get(i);
					if (i == attendedList.size() - 1) {
						custIds1.append(custMap.get("custId"));
					} else {
						custIds1.append(custMap.get("custId") + ",");
					}
				}
				custIds2.append("0");
				custIds3.append("0");
				custIds4.append("0");

			} else if (attendedList.size() < 3000) {
				for (int i = 0; i < 1000; i++) {
					Map custMap = (Map) attendedList.get(i);
					if (i == 1000 - 1) {
						custIds.append(custMap.get("custId"));
					} else {
						custIds.append(custMap.get("custId") + ",");
					}
				}
				for (int i = 1000; i < 2000; i++) {
					Map custMap = (Map) attendedList.get(i);
					if (i == 2000 - 1) {
						custIds1.append(custMap.get("custId"));
					} else {
						custIds1.append(custMap.get("custId") + ",");
					}
				}
				for (int i = 2000; i < attendedList.size(); i++) {
					Map custMap = (Map) attendedList.get(i);
					if (i == attendedList.size() - 1) {
						custIds2.append(custMap.get("custId"));
					} else {
						custIds2.append(custMap.get("custId") + ",");
					}
				}
				custIds3.append("0");
				custIds4.append("0");

			} else if (attendedList.size() < 4000) {
				for (int i = 0; i < 1000; i++) {
					Map custMap = (Map) attendedList.get(i);
					if (i == 1000 - 1) {
						custIds.append(custMap.get("custId"));
					} else {
						custIds.append(custMap.get("custId") + ",");
					}
				}
				for (int i = 1000; i < 2000; i++) {
					Map custMap = (Map) attendedList.get(i);
					if (i == 2000 - 1) {
						custIds1.append(custMap.get("custId"));
					} else {
						custIds1.append(custMap.get("custId") + ",");
					}
				}
				for (int i = 2000; i < 3000; i++) {
					Map custMap = (Map) attendedList.get(i);
					if (i == 3000 - 1) {
						custIds2.append(custMap.get("custId"));
					} else {
						custIds2.append(custMap.get("custId") + ",");
					}
				}
				for (int i = 3000; i < attendedList.size(); i++) {
					Map custMap = (Map) attendedList.get(i);
					if (i == attendedList.size() - 1) {
						custIds3.append(custMap.get("custId"));
					} else {
						custIds3.append(custMap.get("custId") + ",");
					}
				}
				custIds4.append("0");

			} else if (attendedList.size() < 5000) {
				for (int i = 0; i < 1000; i++) {
					Map custMap = (Map) attendedList.get(i);
					if (i == 1000 - 1) {
						custIds.append(custMap.get("custId"));
					} else {
						custIds.append(custMap.get("custId") + ",");
					}
				}
				for (int i = 1000; i < 2000; i++) {
					Map custMap = (Map) attendedList.get(i);
					if (i == 2000 - 1) {
						custIds1.append(custMap.get("custId"));
					} else {
						custIds1.append(custMap.get("custId") + ",");
					}
				}
				for (int i = 2000; i < 3000; i++) {
					Map custMap = (Map) attendedList.get(i);
					if (i == 3000 - 1) {
						custIds2.append(custMap.get("custId"));
					} else {
						custIds2.append(custMap.get("custId") + ",");
					}
				}
				for (int i = 3000; i < 4000; i++) {
					Map custMap = (Map) attendedList.get(i);
					if (i == 4000 - 1) {
						custIds3.append(custMap.get("custId"));
					} else {
						custIds3.append(custMap.get("custId") + ",");
					}
				}
				for (int i = 4000; i < attendedList.size(); i++) {
					Map custMap = (Map) attendedList.get(i);
					if (i == attendedList.size() - 1) {
						custIds4.append(custMap.get("custId"));
					} else {
						custIds4.append(custMap.get("custId") + ",");
					}
				}
			}

		}

		sqlStr
				.append(
						"select distinct cust.custid as cutId,cust.custname as cutName,")
				.append(
						"cust.stuempno as stuempNo,duty.duty as duty,dept.deptname as deptName,")
				.append(
						"fullatt.delegray as delegray,fullatt.dlgt_name as dlgtName,")
				.append(
						"fullatt.attendee_type as attendeeType,fullatt.dictcaption as dictCaption ")
				.append(
						"from ykt_cur.T_Customer cust left join ykt_cur.T_Dept dept on ")
				.append(
						"cust.deptcode=dept.deptcode left join YKT_CONF.T_DUTY duty on ")
				.append("cust.stuempno=duty.stuemp_No left join ")
				.append(
						"(select att.con_id,att.cust_id,att.delegray,dele.dlgt_name,att.attendee_type,dic.dictcaption ")
				.append(
						"from YKT_CONF.T_ATTENDEE_LIST att left join YKT_CONF.T_DELEGATE dele ")
				.append(
						"on att.delegray=dele.DLGT_ID left join YKT_CUR.T_Dictionary dic ")
				.append(
						"on att.attendee_type=dic.dictval and dic.dicttype=78 where att.con_id="
								+ confId + " ")
				.append(
						"and (att.cust_id in(" + custIds
								+ ") or att.cust_id in(" + custIds1
								+ ") or att.cust_id in(" + custIds2
								+ ") or att.cust_id in(" + custIds3
								+ ") or att.cust_id in(" + custIds4
								+ ")))fullatt on cust.custid=fullatt.cust_id ")
				.append(
						"where (cust.custid in(" + custIds
								+ ") or cust.custid in(" + custIds1
								+ ") or cust.custid in(" + custIds2
								+ ") or cust.custid in(" + custIds3
								+ ") or cust.custid in(" + custIds4+ ") ) ")
				.append("order by fullatt.delegray,cust.custid");

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
						"select distinct cust.custid as cutId,cust.custname as cutName,")
				.append(
						"cust.stuempno as stuempNo,duty.duty as duty,dept.deptname as deptName,")
				.append(
						"fullatt.delegray as delegray,fullatt.dlgt_name as dlgtName,")
				.append(
						"fullatt.attendee_type as attendeeType,fullatt.dictcaption as dictCaption ")
				.append(
						"from ykt_cur.T_Customer cust left join ykt_cur.T_Dept dept on ")
				.append(
						"cust.deptcode=dept.deptcode left join YKT_CONF.T_DUTY duty on ")
				.append("cust.stuempno=duty.stuemp_No left join ")
				.append(
						"(select att.con_id,att.cust_id,att.delegray,dele.dlgt_name,att.attendee_type,dic.dictcaption ")
				.append(
						"from YKT_CONF.T_ATTENDEE_LIST att left join YKT_CONF.T_DELEGATE dele ")
				.append(
						"on att.delegray=dele.DLGT_ID left join YKT_CUR.T_Dictionary dic ")
				.append(
						"on att.attendee_type=dic.dictval where att.con_id="
								+ confId + " ")
				.append(
						"and dic.dicttype=78)fullatt on cust.custid=fullatt.cust_id ")
				.append("where fullatt.con_id=" + confId + " ").append(
						"order by fullatt.delegray,cust.custid");
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

			Query q = s.createQuery("select cardphyid from TCard where custid="
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

}
