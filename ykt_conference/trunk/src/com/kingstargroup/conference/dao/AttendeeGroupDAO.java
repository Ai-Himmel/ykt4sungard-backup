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

import com.kingstargroup.conference.hibernate.form.TAttendeeGroup;

/**
 * @author ��Ա������ش���
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
	 * Description: AttendeeGroupDAO����������ѯĳ���˵���Ϣ<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-6  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public List getCustInfo(
			String custno,
			String custname,
			String duty,
			String dept) throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
		.append(" cust.duty_Name as dutyName,dept.dept_Name as deptName,duty.duty as duty ")
		.append(" from ykt_cur.T_CIF_CUSTOMER cust left join YKT_CUR.T_Cif_Dept dept on ")
		.append(" cust.classdept_No=dept.dept_Code left join YKT_CONF.T_DUTY duty on")
		.append(" cust.stuemp_No=duty.stuemp_No")
		.append("  where 1>0");
		if (!"".equals(custno)){
			sqlStr.append(" and cust.stuemp_No like '%"+custno+"%'");
		}
		if (!"".equals(custname)){
			sqlStr.append(" and cust.cut_Name like '%"+custname+"%'");
		}
		if ((!"".equals(duty))){
			sqlStr.append(" and duty.duty like '%"+duty+"%'");
		}
		if ((!"".equals(dept))&&(!"-".equals(dept))){
			sqlStr.append(" and cust.classdept_No='"+dept+"'");
		}
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());		
			q.addScalar("cutId",Hibernate.INTEGER);
			q.addScalar("cutName",Hibernate.STRING);
			q.addScalar("stuempNo",Hibernate.STRING);
			q.addScalar("dutyName",Hibernate.STRING);
			q.addScalar("deptName",Hibernate.STRING);
			q.addScalar("duty",Hibernate.STRING);
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
	 * Description: AttendeeGroupDAO�õ��ͻ���Ϣ���ŵ�Map����<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-17  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public List getCustInfo(
			int confid,
			String custno,
			String custname,
			String duty,
			String dept) throws HibernateException{
		Session s = getSession();
		//HashMap map = new HashMap();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
		.append(" duty.duty as duty,dept.dept_Name as deptName ,att.attend_Sign as attendSign")
		.append(" from ykt_cur.T_Cif_Customer cust left join ykt_cur.T_Cif_Dept dept")
		.append(" on cust.classdept_No=dept.dept_Code left join ykt_conf.T_Attendee_List att ")
		.append(" on cust.cut_Id=att.cust_Id left join YKT_CONF.T_DUTY duty on")
		.append(" cust.stuemp_No=duty.stuemp_No")
		.append(" where att.con_Id="+confid);
		if (!"".equals(custno)){
			sqlStr.append(" and cust.stuemp_No like '%"+custno+"%'");
		}
		if (!"".equals(custname)){
			sqlStr.append(" and cust.cut_Name like '%"+custname+"%'");
		}
		if (!"".equals(duty)){
			sqlStr.equals(" and cust.duty_Name like '%"+duty+"%'");
		}
		if (!"-".equals(dept)){
			sqlStr.append(" and cust.classdept_No='"+dept+"'");
		}
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());	
			q.addScalar("cutId",Hibernate.INTEGER);
			q.addScalar("cutName",Hibernate.STRING);
			q.addScalar("stuempNo",Hibernate.STRING);
			q.addScalar("duty",Hibernate.STRING);
			q.addScalar("deptName",Hibernate.STRING);
			q.addScalar("attendSign",Hibernate.STRING);
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
	 * Description: AttendeeGroupDAO����ѡ������ŵõ��������Ա����<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-7  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public List getCustGroupList(int groupid) throws HibernateException{
		Session s = getSession();
		//HashMap map = new HashMap();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
		.append("duty.duty as duty,dept.dept_Name as deptName ")
		.append("from ykt_cur.T_Cif_Customer cust left join ykt_cur.T_Cif_Dept dept on ")
		.append(" cust.classdept_No=dept.dept_Code left join YKT_CONF.T_DUTY duty on")
		.append(" cust.stuemp_No=duty.stuemp_No")
		.append(" where cust.cut_Id in(select cust_Id from ykt_conf.T_Attendee_Group where group_Id="+groupid+")");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId",Hibernate.INTEGER);
			q.addScalar("cutName",Hibernate.STRING);
			q.addScalar("stuempNo",Hibernate.STRING);
			q.addScalar("duty",Hibernate.STRING);
			q.addScalar("deptName",Hibernate.STRING);
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
	 * Description: AttendeeGroupDAO����Ա��������ɾ��<br>
	 * Return: void<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-7  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public void deleteCustGroup(int groupid,int custid) throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TAttendeeGroup where id.groupId="+groupid+" and id.custId="+custid);
			Iterator iter = q.list().iterator();
			while (iter.hasNext()){
				s.delete((TAttendeeGroup)iter.next());
			}
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}		
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeGroupDAO�������źͿͻ��Ų����Ƿ���ڸ÷�����Ա<br>
	 * Return: boolean���ڷ���true,���򷵻�false<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-24  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public boolean existsAttendeeGroup(int groupid,int custid) throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TAttendeeGroup where id.groupId="+groupid+" and id.custId="+custid);
			if (q.list().size()>0){
				return true;
			}else{
				return false;
			}
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}		
	}
	
}
