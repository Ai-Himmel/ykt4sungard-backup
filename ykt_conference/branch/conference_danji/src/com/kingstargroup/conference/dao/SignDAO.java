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
import com.kingstargroup.conference.hibernate.form.TAttendeeList;
import com.kingstargroup.conference.hibernate.form.TConference;
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
	public List getCustListBy(int confid, int custid) throws HibernateException {
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
					.createSQLQuery("select count(*) as totleattendee from T_ATTENDEE_LIST where CON_ID="
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
					.createSQLQuery("select count(*) as signednum from T_ATTENDEE_LIST where attend_sign in ('11','12','13','21','22','23') and CON_ID="
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
						"select count(*) as signed from T_ATTENDEE_LIST where attend_sign not in ('00','30')")
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
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select distinct cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
				.append(
						" duty.duty as dutyName,dept.dept_Name as deptName,att.ATTEND_DATE as attendDate,")
				.append(" att.ATTEND_TIME as attendTime")
				.append(
						" from ((t_cif_customer cust left join t_cif_dept dept on ")
				.append(
						" cust.classdept_No=dept.dept_Code) left join T_DUTY duty on")
				.append(" cust.stuemp_No=duty.stuemp_No)")
				.append(
						" left join T_ATTENDEE_LIST att on cust.cut_id=att.CUST_ID where")
				.append(
						" cust.cut_Id in(select cust_Id from T_Attendee_List where con_Id="
								+ confid).append(
						" and attend_Sign in('11','12','13','21','22','23')) and att.con_id="
								+ confid + " order by attend_Time desc");

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
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select distinct cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
				.append(
						" duty.duty as dutyName,dept.dept_Name as deptName,att.ATTEND_DATE as attendDate,")
				.append("att.ATTEND_TIME as attendTime")
				.append(
						" from ((t_cif_customer cust left join t_cif_dept dept on")
				.append(
						" cust.classdept_No=dept.dept_Code) left join T_ATTENDEE_LIST att on ")
				.append(" cust.cut_id=att.CUST_ID) left join T_DUTY duty on")
				.append(" cust.stuemp_No=duty.stuemp_No").append(
						" where cust.cut_Id in(select cust_Id from T_Attendee_List where con_Id="
								+ confid).append(
						" and attend_Sign='00')and att.con_id=" + confid);
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
						"from T_ATTENDEE_LIST att ").append(
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
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr
				.append(
						"select distinct cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
				.append(
						" duty.duty as dutyName,dept.dept_Name as deptName,att.ATTEND_DATE as attendDate,")
				.append("att.ATTEND_TIME as attendTime")
				.append(
						" from ((t_cif_customer cust left join t_cif_dept dept on ")
				.append(
						" cust.classdept_No=dept.dept_Code) left join T_DUTY duty on")
				.append(" cust.stuemp_No=duty.stuemp_No)")
				.append(
						" left join T_ATTENDEE_LIST att  on cust.cut_id=att.CUST_ID where ")
				.append(
						" cust.cut_Id in(select cust_Id from T_Attendee_List where con_Id="
								+ confid).append(
						" and attend_Sign='30')and att.con_id=" + confid);
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
		sqlStr
				.append(
						"select distinct cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
				.append(
						" duty.duty as dutyName,dept.dept_Name as deptName,att.ATTEND_DATE as attendDate,")
				.append(
						"att.ATTEND_TIME as attendTime,att.REPLACER_NAME as repName,att.REPLACER_DUTY as repDuty")
				.append(
						" from ((t_cif_customer cust left join t_cif_dept dept on")
				.append(
						" cust.classdept_No=dept.dept_Code) left join T_ATTENDEE_LIST att on ")
				.append(" cust.cut_id=att.CUST_ID) left join T_DUTY duty on")
				.append(" cust.stuemp_No=duty.stuemp_No").append(
						" where cust.cut_Id in(select cust_Id from T_Attendee_List where con_Id="
								+ confid).append(
						" and (attend_Sign='13' or attend_Sign='23'))and att.con_id="
								+ confid + " order by attend_Time desc");
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
						"select p.delegray,dlgt_name as dlgtName,p.attendee,p.fact from ")
				.append(
						"(select tt.delegray,tt.custId as attendee,qq.custId as fact from ")
				.append(
						"(select count(cust_id) as custId,delegray from T_ATTENDEE_LIST ")
				.append(
						"where con_id="
								+ confid
								+ " and attend_sign in('00','11','12','13','21','22','23','30') group by delegray) as tt ")
				.append(
						"left join (select count(cust_id) as custId,delegray from T_ATTENDEE_LIST ")
				.append(
						"where con_id="
								+ confid
								+ " and attend_sign in('11','12','13','21','22','23') ")
				.append(
						"group by delegray) as qq on tt.delegray=qq.delegray) as p,T_DELEGATE ")
				.append("where p.delegray=dlgt_id");
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
						"select cust.cut_Id as cutId,cust.cut_Name as cutName,cust.stuemp_No as stuempNo,")
				.append(
						" duty.duty as duty,dept.dept_Name as deptName ,att.attend_Sign as attendSign,att.ATTEND_DATE as attendDate,att.ATTEND_TIME as attendTime")
				.append(
						" from ((T_Cif_Customer as cust left join T_Cif_Dept as dept")
				.append(
						" on cust.classdept_No=dept.dept_Code) left join T_Attendee_List as att ")
				.append(
						" on cust.cut_Id=att.cust_Id) left join T_DUTY as duty on")
				.append(" cust.stuemp_No=duty.stuemp_No").append(
						" where att.con_Id=" + confid + " and delegray="
								+ delegary);
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

	public boolean getCustbyidandPhyNo(int conId, String physicalNo)
			throws HibernateException, Exception {
		Session s = getSession();
		try {
			Query q = s
					.createQuery(" from TAttendeeList att where att.id.conId="
							+ conId + " and att.physicalNo ='" + physicalNo
							+ "'");
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

	public void updatecheckFlag(int conId, String physicalNo)
			throws HibernateException, Exception {
		Session s = getSession();
		try {
			String nowtime = DateUtilExtend.getNowDate2()
					+ DateUtilExtend.getNowTime2();
			String meetTime = "";
			Query time = s
					.createQuery("from TConference a where a.conId=:conId");
			time.setInteger("conId", conId);
			List timeList = time.list();
			Iterator timeIter = timeList.iterator();
			while (timeIter.hasNext()) {
				TConference conf = (TConference) timeIter.next();
				meetTime = conf.getConBegindate() + conf.getConBegintime();
			}
			Query q = s
					.createQuery("from TAttendeeList att where att.id.conId="
							+ conId + " and att.physicalNo ='" + physicalNo
							+ "'");
			List list = q.list();
			Iterator iter = list.iterator();
			if (iter.hasNext()) {
				TAttendeeList attendee = (TAttendeeList) iter.next();
				if (null==attendee.getAttendDate()||"".equals(attendee.getAttendDate())) {
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
		} catch (HibernateException he) {
			errlog.error(he);
			he.printStackTrace();
		} catch (Exception e) {
			errlog.error(e);
			e.printStackTrace();
		}
	}

	public void recordHis(Integer confid, String physicalNo)
			throws HibernateException, Exception {
		Session s = getSession();
		try {
			String nowtime = DateUtilExtend.getNowDate2()
					+ DateUtilExtend.getNowTime2();
			String meetTime = "";
			Query time = s
					.createQuery("from TConference a where a.conId=:conId");
			time.setInteger("conId", confid.intValue());
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
				int id = getMaxidfromRecordHis() + 1;
				rh.setId((Integer.valueOf(String.valueOf(id))));
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

	public int getMaxidfromRecordHis() {
		Session s = getSession();
		int id = 0;
		try {
			Query q = s.createQuery("select max(id) from TRecordhis");
			List list = q.list();
			Iterator iter = list.iterator();
			if (iter.hasNext()) {
				id = Integer.parseInt(iter.next().toString());
			}
		} catch (HibernateException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return id;
	}
	public String getEndTimeByConid(int conid){
		Session s = getSession();
		try{
			Query q = s.createQuery(" select c.conEndtime  from  TConference   c where c.conId=:conId");
			q.setInteger("conId", conid);
			List time = q.list();
			Iterator it = time.iterator();
			while(it.hasNext()){
				String  endTime = (String)it.next();
				return endTime;
			}
			
		} catch (HibernateException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}
	private Logger errlog = Logger.getLogger("Errlog");

	private static SignDAO _instance;

}
