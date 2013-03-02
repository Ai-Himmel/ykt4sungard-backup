package com.kingstargroup.conference.dao;

import java.util.Iterator;
import java.util.List;

import org.apache.log4j.Logger;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.conference.common.DateUtilExtend;
import com.kingstargroup.conference.hibernate.form.TPifDictionary;

public class DictionaryDAO extends BasicDAO{
	static Logger log = Logger.getLogger("Errlog");
	public static DictionaryDAO getInstance() {
		if (_instance == null) {
			_instance = new DictionaryDAO();
		}
		return _instance;
	}
		/**
		 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
		 * File name: .java<br>
		 * Description: DictionaryDAOȡ�û������б�<br>
		 * Return: List<br>
		 * Modify History: <br>
		 * ��������    ������     ����ʱ��       ��������<br>
		 * ======================================<br>
		 *  ����      ����ΰ     2006-4-3  <br>
		 * @author   ����ΰ
		 * @version 
		 * @since 1.0
		 */
	public List getAssimblyRoom() throws HibernateException{
		Session s = getSession();
		List getList = null;
		try {
			Query q = s.createQuery(" from TAssemblyRoom");
			getList = q.list();
		} catch (HibernateException ex) {
			ex.printStackTrace();
			log.error(ex);
			throw ex;
		}	
		return getList;
	}
		/**
		 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
		 * File name: .java<br>
		 * Description: DictionaryDAOȡ�û��������б�<br>
		 * Return: List<br>
		 * Modify History: <br>
		 * ��������    ������     ����ʱ��       ��������<br>
		 * ======================================<br>
		 *  ����      ����ΰ     2006-4-3  <br>
		 * @author   ����ΰ
		 * @version 
		 * @since 1.0
		 */
	public List getConfType() throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TConferenceType");
			List getlist = q.list();
			return getlist;
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
		
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DictionaryDAO���һ����λ�б�<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-4  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public List getDeptList() throws HibernateException{
		Session s = getSession();
		try {
			SQLQuery q = s.createSQLQuery("select DEPT_CODE,DEPT_NAME from ykt_cur.T_Cif_Dept where dept_Level=1");
			q.addScalar("DEPT_CODE",Hibernate.STRING);
			q.addScalar("DEPT_NAME",Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.equals(he);
			throw he;
		}
	}
	
	public String getDeptName(String dept_code) throws HibernateException{
		Session s = getSession();
		String deptName = "";
		try {
			
			Query q = s.createQuery("select deptName from TCifDept where deptCode='"+dept_code+"'");
			List list = q.list();
			if(list!=null&&list.size()>0){
				deptName = list.get(0).toString();
			}
			return deptName;
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.equals(he);
			throw he;
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DictionaryDAO���ݲ���Աȡ�øò���Ա����Ȩ�޵Ļ����б�<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-5  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public List getConfList(String username)throws HibernateException{
		Session s= getSession();
		StringBuffer sqlStr = new StringBuffer();
		String beginDate = DateUtilExtend.getNowDate2();
		//sqlStr.append(" from TConference where organigerId")
		//.append(" in(select deptId from TDeptLimit where operCode=:opercode) and beginDate>=:begindate");
		sqlStr.append(" from TConference where organigerId")
		.append(" in(select id.deptId from TDeptLimit where id.operCode='"+username+"')")
		.append(" and status!='9' and conBegindate>='"+beginDate+"'");
		try {
			Query q = s.createQuery(sqlStr.toString());
			///q.setString("begindate",beginDate);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
	/**
		* File name: DictionaryDAO.java<br>
		* Description: <br> ��������ǰ�Ļ���
		* Return: @param username
		* Return: @return
		* Return: @throws HibernateException<br>
		* Modify History: <br>
		* ��������    ������     ����ʱ��       ��������<br>
		* ======================================<br>
		*  ����      ������    2007-3-29  <br>
		* @author   ������
		* @version 
		* @since 1.0
		*/
	public List getConfListBeforeMeeting(String username)throws HibernateException{
		Session s= getSession();
		StringBuffer sqlStr = new StringBuffer();
		String beginDate = DateUtilExtend.getNowDate2();
		//sqlStr.append(" from TConference where organigerId")
		//.append(" in(select deptId from TDeptLimit where operCode=:opercode) and beginDate>=:begindate");
		sqlStr.append(" from TConference where organigerId")
		.append(" in(select id.deptId from TDeptLimit where id.operCode='"+username+"')")
		.append(" and status!='9' and conBegindate<='"+beginDate+"' order by conBegindate desc,conBegintime desc");
		try {
			Query q = s.createQuery(sqlStr.toString());
			///q.setString("begindate",beginDate);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DictionaryDAO�ӿͻ�����ȡ��ְ���б�<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-6  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public List getDutyList()throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery("select distinct dutyName from TCifCustomer");
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DictionaryDAO���ݵ�¼����Ա��ȡ�øò���Ա���������<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-6  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public List getGroupListByOper(String username)throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TGroup where operId='"+username+"' order by groupId");
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DictionaryDAO���ݲ���Ա��ŵõ������б��е�������Ա<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-11  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public List getAttendeeGroupListByOper(String username)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
		.append(" cust.duty_Name as dutyName,dept.dept_Name as deptName,group.GROUP_ID as groupId ")
		.append(" from ykt_cur.T_CIF_CUSTOMER cust left join YKT_CUR.T_Cif_Dept dept")
		.append(" on cust.classdept_No=dept.dept_Code left join ykt_conf.T_ATTENDEE_GROUP group ")
		.append(" on group.CUST_ID=cust.cut_Id where ")
		.append(" group.group_Id in(select group_Id from ykt_conf.T_Group where oper_Id='"+username+"')");
		try {
			//where id.groupId in(select groupId from TGroup where operId='"+Constants.USER_KEY+"')");
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId",Hibernate.INTEGER);
			q.addScalar("cutName",Hibernate.STRING);
			q.addScalar("stuempNo",Hibernate.STRING);
			q.addScalar("dutyName",Hibernate.STRING);
			q.addScalar("deptName",Hibernate.STRING);
			q.addScalar("groupId",Hibernate.INTEGER);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DictionaryDAO����״̬<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-11  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public String getConfStatus(String typeid)throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TPifDictionary where id.dictNo=80 and id.dictValue='"+typeid+"'");
			return ((TPifDictionary)q.list().get(0)).getDictCaption();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DictionaryDAO�����Ա״̬<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-11  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public String getAttendeeStatus(String statusid)throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TPifDictionary where id.dictNo=79 and id.dictValue='"+statusid+"'");
			return ((TPifDictionary)q.list().get(0)).getDictCaption();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DictionaryDAO��Ա���<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-11  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public List getCustTypeList()throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TPifDictionary where id.dictNo=78");
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
	public TPifDictionary getCustType(String dictValue)throws HibernateException{
		Session s = getSession();
		TPifDictionary dic = null;
		try {
			Query q = s.createQuery(" from TPifDictionary where id.dictNo=78 and id.dictValue='"+dictValue+"'");
			List list = q.list();
			Iterator iter = list.iterator();
			if (iter.hasNext()) {
				dic = (TPifDictionary) iter.next();
			}
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
		return dic;
	}
	
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DictionaryDAOȡ�ü�ʱ���豸���б�<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-11  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public List getDeviceList()throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append(" from TPifDevice where devtype='0121' and devUsage=1003");
		try {
			Query q = s.createQuery(sqlStr.toString());
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
	 * Description: DictionaryDAO���ݻ�����ȡ�øû�����������豸�б�<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-19  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public List getDeviceListByConfid(int confid)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append(" from TPifDevice where devtype='0121' and deviceId in ")
		.append("(select id.deviceId from TDevConference where id.conId="+confid+")");
		try {
			Query q = s.createQuery(sqlStr.toString());
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
		
	}
	
	private Logger errlog = Logger.getLogger("Errlog");

	private static DictionaryDAO _instance;
}
