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

import com.kingstargroup.conference.hibernate.form.TCifCustomer;
import com.kingstargroup.conference.hibernate.form.TDevConference;
import com.kingstargroup.conference.hibernate.form.TPifCard;
import com.kingstargroup.conference.hibernate.form.TTifMeslist;

/**
 * @author 人员分配通知相关
 *
 */
public class AttendeeDAO extends BasicDAO {
	private static AttendeeDAO _instance;
	private Logger errlog = Logger.getLogger("Errlog");
	//private Logger busslog = Logger.getLogger("Bussinesslog");
	
	public static AttendeeDAO getInstance() {
		if (_instance == null) {
			_instance = new AttendeeDAO();
		}
		return _instance;
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeDAO根据会议编号得到通知表里所有参与该会议的人员名单详细信息<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-12  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getAttendeeListByConfId(int confid)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
		.append(" cust.duty_Name as duty_Name,dept.dept_Name as deptName")
		.append(" from ykt_cur.T_Cif_Customer cust left join ykt_cur.T_Cif_Dept dept on cust.classdept_No=dept.dept_Code where ")
		.append(" cust.cut_Id in(select cust_Id from ykt_conf.T_Inform_List where con_Id="+confid+")");
		try {
			Query q = s.createSQLQuery(sqlStr.toString());
			return q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.error(he);
			throw he;
		}
	}
	
	/**
	 * 根据选择的人员列表显示要出席会议人员名单
	 * 2006-6-12
	 * hjw
	 * @param
	 * @return
	 */
	public List getAttendeeAllotList(
			String custnolists)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
		.append(" duty.duty as dutyName,dept.dept_Name as deptName")
		.append(" from ykt_cur.T_Cif_Customer cust left join ykt_cur.T_Cif_Dept dept on")
		.append(" cust.classdept_No=dept.dept_Code left join ykt_conf.t_duty duty on")
		.append(" cust.stuemp_no = duty.stuemp_no")
		.append(" where cust.cut_Id in("+custnolists+")");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId",Hibernate.INTEGER);
			q.addScalar("cutName",Hibernate.STRING);
			q.addScalar("stuempNo",Hibernate.STRING);
			q.addScalar("dutyName",Hibernate.STRING);
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
	 * Description: AttendeeDAO根据人员编号得到该人员的卡号<br>
	 * Return: TPifCard<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-11  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public TPifCard getCardNoByCustId(int custid)throws HibernateException{
		TPifCard card = null;
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TPifCard where stateId='1000' and cosumerId="+custid);
			if (q.list().size()!=0){
				card = (TPifCard)q.list().get(0);
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
		 * Description: AttendeeDAO取得用户信息<br>
		 * Return: TCifCustomer<br>
		 * Modify History: <br>
		 * 操作类型    操作人     操作时间       操作内容<br>
		 * ======================================<br>
		 *  创建      韩纪伟     2006-5-26  <br>
		 * @author   韩纪伟
		 * @version 
		 * @since 1.0
		 */
	public TCifCustomer getCustomerCustId(int custid)throws HibernateException{
		TCifCustomer customer = null;
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TCifCustomer where cutId="+custid);
			if (q.list().size()!=0){
				customer = (TCifCustomer)q.list().get(0);
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
	 * Description: AttendeeDAO根据会议编号和人员编号判断是否存在该记录，存在则返回true<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-12  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public boolean existAttendee(int custid,int confid)throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TAttendeeList where id.conId="+confid+" and id.custId="+custid);
			if (q.list().size()!=0){
				return true;
			}else{
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
	 * Description: AttendeeDAO根据会议编号和设备编号判断是否存在该设备，存在返回true<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-12  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public boolean existDevice(int devid,int confid)throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TDevConference where id.conId="+confid+" and id.deviceId="+devid);
			if (q.list().size()!=0){
				return true;
			}else{
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
	 * Description: AttendeeDAO根据人员编号和会议编号判断是否存在有通知信息，存在这返回true<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-12  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public boolean existInform(int custid,int confid)throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TInformList where id.conId="+confid+" and id.custId="+custid);
			if (q.list().size()!=0){
				return true;
			}else{
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
	 * Description: AttendeeDAO根据会议编号取得该会议分配的设备<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-27  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getDevListByConfid(int confid)throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TDevConference where id.conId="+confid);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}		
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeDAO根据会议编号得到要通知的人员名单<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-13  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getAttendeeByConfId(int confid)throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TInformList where id.conId="+confid);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeDAO根据会议列表取得人员名单列表<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-19  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getAttListByConfId(int confid)throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TAttendeeList where id.conId="+confid);
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
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-21  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getAttendeeListBy(
			int confid,
			String custno,
			String custname,
			String dept,
			String duty)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
		.append(" cust.duty_Name as dutyName,dept.dept_Name as deptName")
		.append(" from ykt_cur.T_Cif_Customer cust left join ykt_cur.T_Cif_Dept dept")
		.append(" on cust.classdept_No=dept.dept_Code where ")
		.append(" cust.cut_Id in(select cust_Id from ykt_conf.T_Inform_List where con_Id="+confid+")");
		if (!"".equals(custno)){
			sqlStr.append(" and cust.stuemp_No like '%"+custno+"%'");
		}
		if (!"".equals(custname)){
			sqlStr.append(" and cust.cut_Name like '%"+custname+"%'");
		}
		if (!"".equals(duty)){
			sqlStr.append(" and cust.duty_Name like '%"+duty+"%'");
		}
		if (!"-".equals(dept)){
			sqlStr.append(" and cust.classdept_No='"+dept+"'");
		}
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId",Hibernate.INTEGER);
			q.addScalar("cutName",Hibernate.STRING);
			q.addScalar("stuempNo",Hibernate.STRING);
			q.addScalar("dutyName",Hibernate.STRING);
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
		 * Description: AttendeeDAO到消息队列表中查找是否存在记录，存在则删除<br>
		 * Return: void<br>
		 * Modify History: <br>
		 * 操作类型    操作人     操作时间       操作内容<br>
		 * ======================================<br>
		 *  创建      韩纪伟     2006-5-9  <br>
		 * @author   韩纪伟
		 * @version 
		 * @since 1.0
		 */
	public void deleteMesList(int devid,Integer dev999id,int cardno) throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append(" from TTifMeslist where deviceId="+devid+" and devid="+dev999id)
		.append(" and funid=930117 and cardNo="+cardno+" and ecode>0");
		try {
			Query q = s.createQuery(sqlStr.toString());
			Iterator iter = q.list().iterator();
			while (iter.hasNext()){
				s.delete((TTifMeslist)iter.next());
			}
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}		
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeDAO根据会议编号取得已经使用该会议设备的会议列表<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-5-9  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List usedDevIdList(String begindate) throws HibernateException{
		Session s = getSession();
		//String confdate = DateUtilExtend.getNowDate2();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select DEVICE_ID, CON_BEGINDATE, CON_BEGINTIME, CON_ENDTIME,CON_SIGNTIME")
		.append(" from YKT_CONF.T_DEV_CONFERENCE where CON_BEGINDATE='"+begindate+"'");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("DEVICE_ID",Hibernate.INTEGER);
			q.addScalar("CON_BEGINDATE",Hibernate.STRING);
			q.addScalar("CON_BEGINTIME",Hibernate.STRING);
			q.addScalar("CON_ENDTIME",Hibernate.STRING);
			q.addScalar("CON_SIGNTIME",Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
		/**
		 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
		 * File name: .java<br>
		 * Description: AttendeeDAO设备会议对应表中如果存在设备，则先删除再增加<br>
		 * Return: void<br>
		 * Modify History: <br>
		 * 操作类型    操作人     操作时间       操作内容<br>
		 * ======================================<br>
		 *  创建      韩纪伟     2006-5-9  <br>
		 * @author   韩纪伟
		 * @version 
		 * @since 1.0
		 */
	public void delDevConf(int confid)throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TDevConference where id.conId="+confid);
			Iterator iter = q.list().iterator();
			while (iter.hasNext()){
				s.delete((TDevConference)iter.next());
			}
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AttendeeDAO根据会议编号取得在该会议中的人员信息<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-5-29  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getCustListByConfId(int confid)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append(" from TCifCustomer where cutId in (")
		.append(" select id.custId from TInformList where id.conId="+confid+")");
		try {
			Query q = s.createQuery(sqlStr.toString());
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
		/**
		 * 消息队列中该会议是否都下发成功，如果都下发成功返回0,否则返回其它
		 * 2006-6-8
		 * hjw
		 * @param
		 * @return
		 */
	public String getMesListIfSucceed(int confid,String beginDate)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select count(*)as num from YKT_CUR.T_TIF_MESLIST where")
		.append(" DEVPHY999_ID in (select DEVPHY999_ID from YKT_CUR.T_PIF_DEVICE where DEVICE_ID in ")
		.append(" (select DEVICE_ID from YKT_CONF.T_DEV_CONFERENCE where con_id="+confid+"))")
		.append(" and ecode<>0 and indt like '"+beginDate+"%'");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("num",Hibernate.INTEGER);
			return q.list().get(0).toString();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
		/**
		 * 名单是否发送成功
		 * 2006-6-8
		 * hjw
		 * @param
		 * @return
		 */
	public String ifSendBySucceed(int confid)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select count(*) as num from YKT_CONF.T_ATTENDEE_LIST ")
		.append("where con_id="+confid+" and send_sign='0'");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("num",Hibernate.INTEGER);
			return q.list().get(0).toString();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
}
