package com.kingstargroup.conference.dao;

import java.util.List;

import org.apache.log4j.Logger;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.conference.hibernate.form.TConference;

public class SignDAO extends BasicDAO{
	public static SignDAO getInstance() {
		if (_instance == null) {
			_instance = new SignDAO();
		}
		return _instance;
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignDAO根据会议编号和客户编号取得要更新会议出席记录的人员<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-18  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getCustListBy(
			int confid,
			int custid)throws HibernateException{
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TAttendeeList att where att.id.conId="+confid+" and att.id.custId="+custid);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
		/**
		 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
		 * File name: .java<br>
		 * Description: SignDAO根据会议编号取得会议内容<br>
		 * Return: TConference<br>
		 * Modify History: <br>
		 * 操作类型    操作人     操作时间       操作内容<br>
		 * ======================================<br>
		 *  创建      韩纪伟     2006-4-19  <br>
		 * @author   韩纪伟
		 * @version 
		 * @since 1.0
		 */
	public TConference getConfInfoById(int confid)throws HibernateException{
		Session s = getSession();
		TConference conf = null;
		try {
			Query q = s.createQuery(" from TConference where conId="+confid);
			if (q.list().size()!=0){
				conf = (TConference)q.list().get(0);
			}
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
		return conf;
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignDAO根据会议编号取得出席总人数<br>
	 * Return: int<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-19  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public int getConfTotleAttendeeByCofid(int confid)throws HibernateException{
		Session s = getSession();
		try {
			SQLQuery q = s.createSQLQuery("select count(*) as totleattendee from ykt_conf.T_ATTENDEE_LIST where CON_ID="+confid);
			q.addScalar("totleattendee",Hibernate.INTEGER);
			return Integer.parseInt(q.list().get(0).toString());
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignDAO实际签到人数（1正常签到，3无卡签到，4替代签到）<br>
	 * Return: int<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-19  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public int getSignedNumByCofid(int confid)throws HibernateException{
		Session s = getSession();
		try {
			SQLQuery q = s.createSQLQuery("select count(*) as signednum from ykt_conf.T_ATTENDEE_LIST where attend_sign in ('1','3','4','5') and CON_ID="+confid);
			q.addScalar("signednum",Hibernate.INTEGER);
			return Integer.parseInt(q.list().get(0).toString());
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignDAO判断是否已经签到<br>
	 * Return: boolean	true已经签到，false未签到<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-29  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public boolean getSignedOrNot(int confid,int custid)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select count(*) as signed from ykt_conf.T_ATTENDEE_LIST where attend_sign in ('1','3','4','5')")
		.append(" and CON_ID="+confid+" and cust_id="+custid);
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("signed",Hibernate.INTEGER);
			if (Integer.parseInt(q.list().get(0).toString())!=0){
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
	 * Description: SignDAO根据会议编号取得正常签到人数列表<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-19  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getSignedNumByConfid(int confid)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select distinct cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
		.append(" duty.duty as dutyName,dept.dept_Name as deptName,att.ATTEND_DATE as attendDate,")
		.append(" att.ATTEND_TIME as attendTime")
		.append(" from ykt_cur.t_cif_customer cust left join ykt_cur.t_cif_dept dept on ")
		.append(" cust.classdept_No=dept.dept_Code left join YKT_CONF.T_DUTY duty on")
		.append(" cust.stuemp_No=duty.stuemp_No")
		.append(" left join ykt_conf.T_ATTENDEE_LIST att on cust.cut_id=att.CUST_ID where")
		.append(" cust.cut_Id in(select cust_Id from ykt_conf.T_Attendee_List where con_Id="+confid)
		.append(" and attend_Sign in('1','3','5'))and att.con_id="+confid +" order by attendTime desc");

		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId",Hibernate.INTEGER);
			q.addScalar("cutName",Hibernate.STRING);
			q.addScalar("stuempNo",Hibernate.STRING);
			q.addScalar("dutyName",Hibernate.STRING);
			q.addScalar("deptName",Hibernate.STRING);
			q.addScalar("attendDate",Hibernate.STRING);
			q.addScalar("attendTime",Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignDAO根据会议编号取得未到人数列表<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-19  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getUnSignNumByConfid(int confid)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select distinct cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
		.append(" duty.duty as dutyName,dept.dept_Name as deptName,att.ATTEND_DATE as attendDate,")
		.append("att.ATTEND_TIME as attendTime")
		.append(" from ykt_cur.t_cif_customer cust left join ykt_cur.t_cif_dept dept on")
		.append(" cust.classdept_No=dept.dept_Code left join ykt_conf.T_ATTENDEE_LIST att on ")
		.append(" cust.cut_id=att.CUST_ID left join YKT_CONF.T_DUTY duty on")
		.append(" cust.stuemp_No=duty.stuemp_No")
		.append(" where cust.cut_Id in(select cust_Id from ykt_conf.T_Attendee_List where con_Id="+confid)
		.append(" and attend_Sign='0')and att.con_id="+confid);
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId",Hibernate.INTEGER);
			q.addScalar("cutName",Hibernate.STRING);
			q.addScalar("stuempNo",Hibernate.STRING);
			q.addScalar("dutyName",Hibernate.STRING);
			q.addScalar("deptName",Hibernate.STRING);
			q.addScalar("attendDate",Hibernate.STRING);
			q.addScalar("attendTime",Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: SignDAO根据会议编号取得请假人数列表<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-19  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getLeaveNumByConfid(int confid)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select distinct cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
		.append(" duty.duty as dutyName,dept.dept_Name as deptName,att.ATTEND_DATE as attendDate,")
		.append("att.ATTEND_TIME as attendTime")
		.append(" from ykt_cur.t_cif_customer cust left join ykt_cur.t_cif_dept dept on ")
		.append(" cust.classdept_No=dept.dept_Code left join YKT_CONF.T_DUTY duty on")
		.append(" cust.stuemp_No=duty.stuemp_No")
		.append(" left join ykt_conf.T_ATTENDEE_LIST att  on cust.cut_id=att.CUST_ID where ")
		.append(" cust.cut_Id in(select cust_Id from ykt_conf.T_Attendee_List where con_Id="+confid)
		.append(" and attend_Sign='2')and att.con_id="+confid);
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId",Hibernate.INTEGER);
			q.addScalar("cutName",Hibernate.STRING);
			q.addScalar("stuempNo",Hibernate.STRING);
			q.addScalar("dutyName",Hibernate.STRING);
			q.addScalar("deptName",Hibernate.STRING);
			q.addScalar("attendDate",Hibernate.STRING);
			q.addScalar("attendTime",Hibernate.STRING);
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
	 * Description: SignDAO根据会议编号取得替代签到人数列表<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-4-19  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getReplaceNumByConfid(int confid)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select distinct cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
		.append(" duty.duty as dutyName,dept.dept_Name as deptName,att.ATTEND_DATE as attendDate,")
		.append("att.ATTEND_TIME as attendTime,att.REPLACER_NAME as repName,att.REPLACER_DUTY as repDuty")
		.append(" from ykt_cur.t_cif_customer cust left join ykt_cur.t_cif_dept dept on")
		.append(" cust.classdept_No=dept.dept_Code left join ykt_conf.T_ATTENDEE_LIST att on ")
		.append(" cust.cut_id=att.CUST_ID left join  YKT_CONF.T_DUTY duty on")
		.append(" cust.stuemp_No=duty.stuemp_No")
		.append(" where cust.cut_Id in(select cust_Id from ykt_conf.T_Attendee_List where con_Id="+confid)
		.append(" and attend_Sign='4')and att.con_id="+confid + " order by attendTime desc");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId",Hibernate.INTEGER);
			q.addScalar("cutName",Hibernate.STRING);
			q.addScalar("stuempNo",Hibernate.STRING);
			q.addScalar("dutyName",Hibernate.STRING);
			q.addScalar("deptName",Hibernate.STRING);
			q.addScalar("attendDate",Hibernate.STRING);
			q.addScalar("attendTime",Hibernate.STRING);
			q.addScalar("repName",Hibernate.STRING);
			q.addScalar("repDuty",Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
	/**
	 * 按代表团统计应到人数和实到人数
	 * 2006-6-13
	 * hjw
	 * @param
	 * @return
	 */
	public List getDelegrayListByConfid(int confid)throws HibernateException{
		Session s= getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select delegray,sum(attendee) attendee,sum(fact)fact from")
		.append(" (select DELEGRAY,")
		.append(" (case when attend_sign in('0','1','2','3','4','5','9') then 1 else 0 end)as attendee,")
		.append(" (case when attend_sign in('1','3','4','5') then 1 else 0 end)as fact")
		.append(" from YKT_CONF.T_ATTENDEE_LIST where con_id="+confid+")t group by delegray");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("delegray",Hibernate.STRING);
			q.addScalar("attendee",Hibernate.INTEGER);
			q.addScalar("fact",Hibernate.INTEGER);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	private Logger errlog = Logger.getLogger("Errlog");

	private static SignDAO _instance;
}
