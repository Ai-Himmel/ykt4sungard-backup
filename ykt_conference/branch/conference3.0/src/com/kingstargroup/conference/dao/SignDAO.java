package com.kingstargroup.conference.dao;

import java.util.Iterator;
import java.util.List;

import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.CONSTANT;
import com.kingstargroup.conference.common.DateUtilExtend;
import com.kingstargroup.conference.hibernate.form.TAttendeeList;
import com.kingstargroup.conference.hibernate.form.TAttendeeListId;
import com.kingstargroup.conference.hibernate.form.TCard;
import com.kingstargroup.conference.hibernate.form.TConference;
import com.kingstargroup.conference.hibernate.form.TCustomer;
import com.kingstargroup.conference.hibernate.form.TRecordhis;

public class SignDAO extends BasicDAO {
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
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-18 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public List getCustListBy(long confid, long custid)
			throws HibernateException {
		Session s = getSession();
		try {
			Query q = s
					.createQuery(" from TAttendeeList att where att.id.conId="
							+ confid + " and att.id.custId=" + custid);
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
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-19 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public TConference getConfInfoById(int confid) throws HibernateException {
		Session s = getSession();
		TConference conf = null;
		try {
			Query q = s.createQuery(" from TConference where conId=" + confid);
			if (q.list().size() != 0) {
				conf = (TConference) q.list().get(0);
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
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-19 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public int getConfTotleAttendeeByCofid(int confid)
			throws HibernateException {
		Session s = getSession();
		try {
			SQLQuery q = s
					.createSQLQuery("select count(*) as totleattendee from ykt_conf.T_ATTENDEE_LIST where CON_ID="
							+ confid);
			q.addScalar("totleattendee", Hibernate.INTEGER);
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
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-19 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public int getSignedNumByCofid(int confid) throws HibernateException {
		Session s = getSession();
		try {
			SQLQuery q = s
					.createSQLQuery("select count(*) as signednum from ykt_conf.T_ATTENDEE_LIST where attend_sign in ('11','12','13','21','22','23') and CON_ID="
							+ confid);
			q.addScalar("signednum", Hibernate.INTEGER);
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
	 * Return: boolean true已经签到，false未签到<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-29 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public boolean getSignedOrNot(int confid, int custid)
			throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select count(*) as signed from ykt_conf.T_ATTENDEE_LIST  where attend_sign not in ('00','30')")
				.append(" and CON_ID=" + confid + " and cust_id=" + custid);
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("signed", Hibernate.INTEGER);
			if (Integer.parseInt(q.list().get(0).toString()) != 0) {
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
	 * Description: SignDAO根据会议编号取得正常签到人数列表<br>
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
	public List getSignedNumByConfid(int confid) throws HibernateException {
		return getSignedNumByConfid(confid,"");
	}
	
	public List getSignedNumByConfid(int confid,String deptName) throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		if ("db2".equals(CONSTANT.DB_CONFIG)) {
			sqlStr
					.append(
							"select distinct att.cust_id as cutId,att.cut_name as cutName,att.stuemp_no as stuempNo,")
					.append(
							" '' as dutyName,att.dept_name as deptName,att.ATTEND_DATE as attendDate,")
					.append("att.ATTEND_TIME as attendTime")
					.append(
							" from ykt_conf.T_ATTENDEE_LIST att where con_Id="
									+ confid)
					.append(
							" and (attend_Sign='11' or attend_Sign='12' or attend_Sign='13' or attend_Sign='21' or attend_Sign='22' or attend_Sign='23') ");
			if(StringUtils.isNotBlank(deptName)){
				sqlStr.append(" and att.dept_name='").append(deptName).append("'");
			}
			sqlStr.append(" order by att.ATTEND_TIME desc with ur");
		} else if ("oracle".equals(CONSTANT.DB_CONFIG)) {
			sqlStr
					.append(
							"select distinct att.cust_id as cutId,att.cut_name as cutName,att.stuemp_no as stuempNo,")
					.append(
							" '' as dutyName,att.dept_name as deptName,att.ATTEND_DATE as attendDate,")
					.append("att.ATTEND_TIME as attendTime")
					.append(
							" from ykt_conf.T_ATTENDEE_LIST att where con_Id="
									+ confid)
					.append(
							" and (attend_Sign='11' or attend_Sign='12' or attend_Sign='13' or attend_Sign='21' or attend_Sign='22' or attend_Sign='23') ");
			if(StringUtils.isNotBlank(deptName)){
				sqlStr.append(" and att.dept_name='").append(deptName).append("'");
			}
			sqlStr.append(" order by att.ATTEND_TIME desc");
		} else {
			sqlStr
					.append(
							"select distinct att.cust_id as cutId,att.cut_name as cutName,att.stuemp_no as stuempNo,")
					.append(
							" '' as dutyName,att.dept_name as deptName,att.ATTEND_DATE as attendDate,")
					.append("att.ATTEND_TIME as attendTime")
					.append(
							" from ykt_conf.T_ATTENDEE_LIST att where con_Id="
									+ confid)
					.append(
							" and (attend_Sign='11' or attend_Sign='12' or attend_Sign='13' or attend_Sign='21' or attend_Sign='22' or attend_Sign='23')");
			if(StringUtils.isNotBlank(deptName)){
				sqlStr.append(" and att.dept_name='").append(deptName).append("'");
			}
			sqlStr.append(" order by att.ATTEND_TIME desc");
		}
		

		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("dutyName", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("attendDate", Hibernate.STRING);
			q.addScalar("attendTime", Hibernate.STRING);
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
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-19 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public List getUnSignNumByConfid(int confid) throws HibernateException {
		return getUnSignNumByConfid(confid,"");
	}
	
	public List getUnSignNumByConfid(int confid,String deptName) throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		if ("db2".equals(CONSTANT.DB_CONFIG)) {
			sqlStr
					.append(
							"select distinct att.cust_id as cutId,att.cut_name as cutName,att.stuemp_no as stuempNo,")
					.append(
							" '' as dutyName,att.dept_name as deptName,att.ATTEND_DATE as attendDate,")
					.append("att.ATTEND_TIME as attendTime").append(
							" from ykt_conf.T_ATTENDEE_LIST att where con_Id="
									+ confid).append(
							" and attend_Sign='00' with ur");
			if(StringUtils.isNotBlank(deptName)){
				sqlStr.append(" and att.dept_name='").append(deptName).append("'");
			}
		} else if ("oracle".equals(CONSTANT.DB_CONFIG)) {
			sqlStr
					.append(
							"select distinct att.cust_id as cutId,att.cut_name as cutName,att.stuemp_no as stuempNo,")
					.append(
							" '' as dutyName,d.deptname as deptName,att.ATTEND_DATE as attendDate,")
					.append("att.ATTEND_TIME as attendTime,d.deptcode").append(
							" from ykt_conf.T_ATTENDEE_LIST att,ykt_cur.T_Dept d where att.DEPT_NAME=d.DEPTNAME and att.con_Id="
									+ confid).append(" and att.attend_Sign='00'");
			if(StringUtils.isNotBlank(deptName)){
				sqlStr.append(" and d.deptname='").append(deptName).append("'");
			}
			sqlStr.append(" order by d.deptcode asc,att.cut_name");
		} else {
			sqlStr
					.append(
							"select distinct att.cust_id as cutId,att.cut_name as cutName,att.stuemp_no as stuempNo,")
					.append(
							" '' as dutyName,att.dept_name as deptName,att.ATTEND_DATE as attendDate,")
					.append("att.ATTEND_TIME as attendTime,d.deptcode").append(
							" from ykt_conf.T_ATTENDEE_LIST att ,ykt_cur.T_Dept d where d.deptname=att.dept_name and att.con_Id="
									+ confid).append(" and att.attend_Sign='00'");
			if(StringUtils.isNotBlank(deptName)){
				sqlStr.append(" and att.dept_name='").append(deptName).append("'");
			}
			sqlStr.append(" order by d.deptcode asc,att.cut_name");
		}
		
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("dutyName", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("attendDate", Hibernate.STRING);
			q.addScalar("attendTime", Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	public List getUnSignNumByConfidCount(int confid) throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append(
				"select att.cust_Id as cutId,att.ATTEND_DATE as attendDate,")
				.append("att.ATTEND_TIME as attendTime ").append(
						"from ykt_conf.T_ATTENDEE_LIST att ").append(
						" where att.attend_Sign='00' and att.con_id=" + confid);
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("attendDate", Hibernate.STRING);
			q.addScalar("attendTime", Hibernate.STRING);
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
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-19 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public List getLeaveNumByConfid(int confid) throws HibernateException {
		return getLeaveNumByConfid(confid,"");
	}
	
	public List getLeaveNumByConfid(int confid,String deptName) throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		if ("db2".equals(CONSTANT.DB_CONFIG)) {
			sqlStr
					.append(
							"select distinct att.cust_id as cutId,att.cut_name as cutName,att.stuemp_no as stuempNo,")
					.append(
							" '' as dutyName,att.dept_name as deptName,att.ATTEND_DATE as attendDate,")
					.append("att.ATTEND_TIME as attendTime").append(
							" from ykt_conf.T_ATTENDEE_LIST att where con_Id="
									+ confid).append(
							" and attend_Sign='30' with ur");
		} else if ("oracle".equals(CONSTANT.DB_CONFIG)) {
			sqlStr
					.append(
							"select distinct att.cust_id as cutId,att.cut_name as cutName,att.stuemp_no as stuempNo,")
					.append(
							" '' as dutyName,d.deptname as deptName,att.ATTEND_DATE as attendDate,")
					.append("att.ATTEND_TIME as attendTime,d.deptcode").append(
							" from ykt_conf.T_ATTENDEE_LIST att,ykt_cur.T_Dept d where att.DEPT_NAME=d.DEPTNAME and att.con_Id="
									+ confid).append(" and att.attend_Sign='30'");
			if(StringUtils.isNotBlank(deptName)){
				sqlStr.append(" and d.deptname='").append(deptName).append("'");
			}
			sqlStr.append(" order by d.deptcode asc,att.cut_name");
		} else {
			sqlStr
					.append(
							"select distinct att.cust_id as cutId,att.cut_name as cutName,att.stuemp_no as stuempNo,")
					.append(
							" '' as dutyName,att.dept_name as deptName,att.ATTEND_DATE as attendDate,")
					.append("att.ATTEND_TIME as attendTime,d.deptcode").append(
							" from ykt_conf.T_ATTENDEE_LIST att,ykt_cur.T_Dept d where att.dept_name=d.deptname and att.con_Id="
									+ confid).append(" and attend_Sign='30'");
			if(StringUtils.isNotBlank(deptName)){
				sqlStr.append(" and att.dept_name='").append(deptName).append("'");
			}
			sqlStr.append(" order by d.deptcode asc,att.cut_name");
		}
		

		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("dutyName", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("attendDate", Hibernate.STRING);
			q.addScalar("attendTime", Hibernate.STRING);
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
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-19 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public List getReplaceNumByConfid(int confid) throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		if ("db2".equals(CONSTANT.DB_CONFIG)) {
			sqlStr
					.append(
							"select distinct att.cust_id as cutId,att.cut_name as cutName,att.stuemp_no as stuempNo,")
					.append(
							" '' as dutyName,att.dept_name as deptName,att.ATTEND_DATE as attendDate,")
					.append(
							"att.ATTEND_TIME as attendTime,att.REPLACER_NAME as repName,att.REPLACER_DUTY as repDuty")
					.append(
							" from ykt_conf.T_ATTENDEE_LIST att where con_Id="
									+ confid)
					.append(
							" and (attend_Sign='13' or attend_Sign='23') order by attendTime desc with ur");
		} else if ("oracle".equals(CONSTANT.DB_CONFIG)) {
			sqlStr
					.append(
							"select distinct att.cust_id as cutId,att.cut_name as cutName,att.stuemp_no as stuempNo,")
					.append(
							" '' as dutyName,att.dept_name as deptName,att.ATTEND_DATE as attendDate,")
					.append(
							"att.ATTEND_TIME as attendTime,att.REPLACER_NAME as repName,att.REPLACER_DUTY as repDuty")
					.append(
							" from ykt_conf.T_ATTENDEE_LIST att where con_Id="
									+ confid)
					.append(
							" and (attend_Sign='13' or attend_Sign='23') order by attendTime desc");
		} else {
			sqlStr
					.append(
							"select distinct att.cust_id as cutId,att.cut_name as cutName,att.stuemp_no as stuempNo,")
					.append(
							" '' as dutyName,att.dept_name as deptName,att.ATTEND_DATE as attendDate,")
					.append(
							"att.ATTEND_TIME as attendTime,att.REPLACER_NAME as repName,att.REPLACER_DUTY as repDuty")
					.append(
							" from ykt_conf.T_ATTENDEE_LIST att where con_Id="
									+ confid)
					.append(
							" and (attend_Sign='13' or attend_Sign='23') order by attendTime desc");
		}

		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("dutyName", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("attendDate", Hibernate.STRING);
			q.addScalar("attendTime", Hibernate.STRING);
			q.addScalar("repName", Hibernate.STRING);
			q.addScalar("repDuty", Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * 按代表团统计应到人数和实到人数 2006-6-13 hjw
	 * 
	 * @param
	 * @return
	 */
	public List getDelegrayListByConfid(int confid) throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select delegray,dlgt_name as dlgtName,sum(attendee) attendee,sum(fact)fact from")
				.append(" (select delegray,dlgt_name,")
				.append(
						" (case when attend_sign in('00','11','12','13','21','22','23','30') then 1 else 0 end)as attendee,")
				.append(
						" (case when attend_sign in('11','12','13','21','22','23') then 1 else 0 end)as fact")
				.append(
						" from YKT_CONF.T_ATTENDEE_LIST left join YKT_CONF.T_DELEGATE on delegray=dlgt_id where con_id="
								+ confid + " )t group by delegray,dlgt_name");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("delegray", Hibernate.STRING);
			q.addScalar("dlgtName", Hibernate.STRING);
			q.addScalar("attendee", Hibernate.INTEGER);
			q.addScalar("fact", Hibernate.INTEGER);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	/**
	 * 
	 * 2007-03-20 hlq
	 * 
	 * @param
	 * @return
	 */
	public List getDelegrayListByConfid(int confid, String delegary)
			throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();

		sqlStr
				.append(
						"select cust.custid as cutId,cust.custname as cutName,cust.stuempno as stuempNo,")
				.append(
						" duty.duty as duty,dept.deptname as deptName ,att.attend_Sign as attendSign,att.ATTEND_DATE as attendDate,att.ATTEND_TIME as attendTime")
				.append(
						" from ykt_cur.T_Customer cust left join ykt_cur.T_Dept dept")
				.append(
						" on cust.deptcode=dept.deptcode left join ykt_conf.T_Attendee_List att ")
				.append(
						" on cust.custid=att.cust_Id left join YKT_CONF.T_DUTY duty on")
				.append(" cust.stuempno=duty.stuemp_No").append(
						" where att.con_id=").append(confid);
		if (!"-1".equals(delegary)) {
			sqlStr.append(" and delegray=").append(delegary);
		}
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("duty", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("attendSign", Hibernate.STRING);
			q.addScalar("attendDate", Hibernate.STRING);
			q.addScalar("attendTime", Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	public boolean getCustbyidandPhyNo(long conId, String physicalNo)
			throws HibernateException, Exception {
		Session s = getSession();
		try {

			Query q = s
					.createQuery(" from TAttendeeList att,TCard card where att.cardNo=card.cardno and att.id.conId="
							+ conId
							+ " and card.cardphyid ='"
							+ physicalNo
							+ "' and card.status||card.lossflag='10'");
			List list = q.list();
			if (null == list || list.size() == 0) {
				return false;
			}
			return true;
		} catch (HibernateException he) {
			errlog.error(he);
			he.printStackTrace();
		} catch (Exception e) {
			errlog.error(e);
			e.printStackTrace();
		}
		return false;
	}

	public boolean getEcardCustbyidandPhyNo(long conId, String physicalNo)
			throws HibernateException, Exception {
		Session s = getSession();
		try {

			Query q = s
					.createQuery(" from TAttendeeList att,TCard card where att.cardNo=card.cardno and att.id.conId="
							+ conId
							+ " and card.cardphyid ='"
							+ physicalNo
							+ "' and card.status||card.lossflag='10'");
			List list = q.list();
			if (null == list || list.size() == 0) {
				return false;
			}
			return true;
		} catch (HibernateException he) {
			errlog.error(he);
			he.printStackTrace();
		} catch (Exception e) {
			errlog.error(e);
			e.printStackTrace();
		}
		return false;
	}

	public void updatecheckFlag(long conId, String physicalNo)
			throws HibernateException, Exception {
		Session s = getSession();
		try {
			String nowtime = DateUtilExtend.getNowDate2()
					+ DateUtilExtend.getNowTime2();
			String meetTime = "";
			Query time = s
					.createQuery("from TConference a where a.conId=:conId");
			time.setLong("conId", conId);
			List timeList = time.list();
			Iterator timeIter = timeList.iterator();
			while (timeIter.hasNext()) {
				TConference conf = (TConference) timeIter.next();
				meetTime = conf.getConBegindate() + conf.getConBegintime();
			}
			Query card = s.createQuery("from TCard where cardphyid='"
					+ physicalNo + "' and status='1' and lossflag='0'");

			List cardlist = card.list();
			Iterator carditer = cardlist.iterator();
			if (carditer.hasNext()) {
				TCard tpifcard = (TCard) carditer.next();
				long cardId = tpifcard.getCardno();
				Query q = s
						.createQuery("from TAttendeeList att where att.id.conId="
								+ conId + " and att.cardNo =" + cardId + "");
				List list = q.list();
				Iterator iter = list.iterator();
				if (iter.hasNext()) {
					TAttendeeList attendee = (TAttendeeList) iter.next();
					if (null == attendee.getAttendDate()
							|| "".equals(attendee.getAttendDate())) {
						if (nowtime.compareTo(meetTime) >= 0) {
							// 迟到
							attendee.setAttendSign("21");
						}
						if (nowtime.compareTo(meetTime) < 0) {
							// 正常
							attendee.setAttendSign("11");
						}

						attendee.setAttendDate(DateUtilExtend.getNowDate2());
						attendee.setAttendTime(DateUtilExtend.getNowTime());
						s.save(attendee);
					}
				}
			}

		} catch (HibernateException he) {
			errlog.error(he);
			he.printStackTrace();
		} catch (Exception e) {
			errlog.error(e);
			e.printStackTrace();
		}
	}

	public void getandUpdatecheckFlag(long conId, String physicalNo)
			throws HibernateException, Exception {
		Session s = getSession();
		try {

			String nowtime = DateUtilExtend.getNowDate2()
					+ DateUtilExtend.getNowTime2();
			String meetTime = "";
			TConference tconference = (TConference) s.get(TConference.class,
					new Long(conId));
			if (tconference != null) {
				meetTime = tconference.getConBegindate()
						+ tconference.getConBegintime();
			}
			String getDate = DateUtilExtend.getNowDate2();
			String getTime = DateUtilExtend.getNowTime2();

			Query card = s.createQuery("from TCard where cardphyid='"
					+ physicalNo + "' and status='1' and lossflag='0'");

			List cardlist = card.list();
			Iterator carditer = cardlist.iterator();
			if (carditer.hasNext()) {
				TCard tcard = (TCard) carditer.next();
				long custid = tcard.getCustid();
				TCustomer tcustomer = (TCustomer) s.get(TCustomer.class,
						new Long(custid));

				TAttendeeListId key = new TAttendeeListId();
				key.setConId(conId);
				key.setCustId(custid);
				TAttendeeList attendee = new TAttendeeList(key);
				attendee.setCardNo(tcard.getCardno());
				attendee.setSendSign("0");// 是否下发，0未下发，1下发
				attendee.setDelSign("0");
				attendee.setAllotDate(getDate);
				attendee.setAllotTime(getTime);
				attendee.setDelegray(0);
				attendee.setAttendeeType("1");
				attendee.setCutName(tcustomer.getCustname());
				attendee.setStuempNo(tcustomer.getStuempno());
				attendee.setSex(tcustomer.getSex() == null ? "" : tcustomer
						.getSex());
				attendee.setDeptName(DictionaryDAO.getInstance().getDeptName(
						tcustomer.getDeptcode()));
				if (nowtime.compareTo(meetTime) >= 0) {
					// 迟到
					attendee.setAttendSign("21");
				}
				if (nowtime.compareTo(meetTime) < 0) {
					// 正常
					attendee.setAttendSign("11");
				}
				attendee.setAttendDate(DateUtilExtend.getNowDate2());
				attendee.setAttendTime(DateUtilExtend.getNowTime());
				s.save(attendee);
			}

		} catch (HibernateException he) {
			errlog.error(he);
			he.printStackTrace();
		} catch (Exception e) {
			errlog.error(e);
			e.printStackTrace();
		}
	}

	public void getandUpdatecheckFlagbyCustid(long conId, String custid,
			String flag) throws HibernateException, Exception {
		Session s = getSession();
		try {
			String getDate = DateUtilExtend.getNowDate2();
			String getTime = DateUtilExtend.getNowTime2();
			TCustomer tcustomer = (TCustomer) s.get(TCustomer.class, new Long(
					custid));
			if (tcustomer != null) {
				TAttendeeListId key = new TAttendeeListId();
				key.setConId(conId);
				key.setCustId(tcustomer.getCustid());
				TAttendeeList attendee = new TAttendeeList(key);

				Query card = s.createQuery("from TCard where custid='" + custid
						+ "' and status='1' and lossflag='0'");
				List cardlist = card.list();
				Iterator carditer = cardlist.iterator();
				if (carditer.hasNext()) {
					TCard tcard = (TCard) carditer.next();
					attendee.setCardNo(tcard.getCardno());
				} else {
					attendee.setCardNo(0);
				}
				attendee.setSendSign("0");// 是否下发，0未下发，1下发
				attendee.setDelSign("0");
				attendee.setAttendSign(flag);
				attendee.setAllotDate(getDate);
				attendee.setAllotTime(getTime);
				attendee.setDelegray(0);
				attendee.setAttendeeType("1");
				attendee.setCutName(tcustomer.getCustname());
				attendee.setStuempNo(tcustomer.getStuempno());
				attendee.setSex(tcustomer.getSex() == null ? "" : tcustomer
						.getSex());
				attendee.setDeptName(DictionaryDAO.getInstance().getDeptName(
						tcustomer.getDeptcode()));
				attendee.setAttendSign("12");
				attendee.setAttendDate(DateUtilExtend.getNowDate2());
				attendee.setAttendTime(DateUtilExtend.getNowTime());
				s.save(attendee);

			}

		} catch (HibernateException he) {
			errlog.error(he);
			he.printStackTrace();
		} catch (Exception e) {
			errlog.error(e);
			e.printStackTrace();
		}
	}

	public void recordHis(long confid, String physicalNo)
			throws HibernateException, Exception {
		Session s = getSession();
		try {
			String nowtime = DateUtilExtend.getNowDate2()
					+ DateUtilExtend.getNowTime();
			String meetTime = "";
			Query time = s
					.createQuery("from TConference a where a.conId=:conId");
			time.setLong("conId", confid);
			List timeList = time.list();
			Iterator timeIter = timeList.iterator();
			if (timeIter.hasNext()) {
				TConference conf = (TConference) timeIter.next();
				meetTime = conf.getConBegindate() + conf.getConBegintime();
			}
			Query chec = s.createQuery("from TRecordhis a where a.confid="
					+ confid + " and physicalNo='" + physicalNo + "'");
			List checList = chec.list();
			if (checList == null || checList.size() == 0) {
				TRecordhis rh = new TRecordhis();
				long id = getMaxidfromRecordHis() + 1;
				rh.setId(id);
				rh.setConfid(confid);
				rh.setPhysicalNo(physicalNo);
				rh.setChecktime(nowtime);
				if (nowtime.compareTo(meetTime) >= 0) {
					// 迟到
					rh.setAttendSign("21");
				}
				if (nowtime.compareTo(meetTime) < 0) {
					// 正常
					rh.setAttendSign("11");
				}
				rh.setDealornot("0");
				s.save(rh);
			}
		} catch (HibernateException he) {
			errlog.error(he);
			he.printStackTrace();
		} catch (Exception e) {
			errlog.error(e);
			e.printStackTrace();
		}
	}

	public long getMaxidfromRecordHis() {
		Session s = getSession();
		long id = 0;
		try {
			Query q = s.createQuery("select max(id) from TRecordhis");
			List list = q.list();
			Iterator iter = list.iterator();
			if (iter.hasNext()) {
				id = Long.parseLong(iter.next().toString());
			}
		} catch (HibernateException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return id;
	}
	
	/**
	 * 按部门统计应到人数，实到人数，未到人数，请假人数
	 * 
	 * @param
	 * @return
	 */
	public List getDeptListByConfid(int confid) throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select dept_name as deptName,sum(attendee) attendee,sum(signed) signednum,sum(unsign) unsignnum,sum(leave) leavenum from ");
		sqlStr.append("(select attr.dept_name,d.deptcode as deptcode,(case when attr.attend_sign in ('00', '11', '12', '13', '21', '22', '23', '30') then 1 else 0 end) as attendee,");
		sqlStr.append("(case when attr.attend_sign in ('11', '12', '13', '21', '22', '23') then 1 else 0 end) as signed,");
		sqlStr.append("(case when attr.attend_sign = '00' then 1 else 0 end) as unsign,");
		sqlStr.append("(case when attr.attend_sign = '30' then 1 else 0 end) as leave ");
		sqlStr.append("from YKT_CONF.T_ATTENDEE_LIST attr, ykt_cur.T_Dept d where attr.DEPT_NAME=d.DEPTNAME and attr.con_id =").append(confid).append(") t group by dept_name,deptcode");
		sqlStr.append(" order by deptcode asc");
		
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("attendee", Hibernate.INTEGER);
			q.addScalar("signednum", Hibernate.INTEGER);
			q.addScalar("unsignnum", Hibernate.INTEGER);
			q.addScalar("leavenum", Hibernate.INTEGER);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}
	
	/**
	 * 获得应到人员列表
	 * @param confid
	 * @param deptName
	 * @return
	 * @throws HibernateException
	 */
	public List getAttendeeByConfid(int confid,String deptName) throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		
		sqlStr.append("select distinct att.cust_id as cutId,att.cut_name as cutName,att.stuemp_no as stuempNo,")
				.append(" '' as dutyName,d.deptname as deptName,att.ATTEND_DATE as attendDate,")
				.append("att.ATTEND_TIME as attendTime,d.deptcode")
				.append(" from ykt_conf.T_ATTENDEE_LIST att,ykt_cur.T_Dept d where att.DEPT_NAME=d.DEPTNAME and att.con_Id="+ confid);
		if(StringUtils.isNotBlank(deptName)){
			sqlStr.append(" and d.deptname='").append(deptName).append("'");
		}
		sqlStr.append(" order by d.deptcode asc,att.cut_name");
		
		
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("cutId", Hibernate.INTEGER);
			q.addScalar("cutName", Hibernate.STRING);
			q.addScalar("stuempNo", Hibernate.STRING);
			q.addScalar("dutyName", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("attendDate", Hibernate.STRING);
			q.addScalar("attendTime", Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			errlog.error(he);
			throw he;
		}
	}

	private Logger errlog = Logger.getLogger("Errlog");

	private static SignDAO _instance;

}
