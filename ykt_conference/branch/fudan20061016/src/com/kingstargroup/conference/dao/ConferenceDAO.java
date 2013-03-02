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
import com.kingstargroup.conference.hibernate.form.TConference;

public class ConferenceDAO extends BasicDAO {
	private Logger errlog = Logger.getLogger("Errlog");

	Logger info = Logger.getLogger("Businesslog");

	private static ConferenceDAO _instance;

	public static ConferenceDAO getInstance() {
		if (_instance == null) {
			_instance = new ConferenceDAO();
		}
		return _instance;
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ConferenceDAO会议删除<br>
	 * Return: void<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-4 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public void deleteConference(String conferenceIds[])
			throws HibernateException {
		Session s = getSession();
		int conId = -1;
		try {
			for (int i = 0; i < conferenceIds.length; i++) {
				// s.delete(s.get(TAssemblyRoom.class, conferenceIds[i]));
				// 删除会议时设置其状态为9
				// conId = Integer.parseInt(conferenceIds[i]);

				Query q = s.createQuery(" TConference set status=9");
				q.setInteger("conid", conId);
			}
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}

	public void deleteAllConference() throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery("delete from TConference");
			q.executeUpdate();

		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}

	public void deleteAllDeptLimit() throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery("delete from TDeptLimit");
			q.executeUpdate();

		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}

	public void deleteAllDevConference() throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery("delete from TDevConference");
			q.executeUpdate();

		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}

	public void deleteAllDelegate() throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery("delete from TDelegate");
			q.executeUpdate();

		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}

	public void deleteAllGroup() throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery("delete from TGroup");
			q.executeUpdate();

		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ConferenceDAO根据操作员权限取得还没有开过的会议列表<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-3 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public List getConference(String username) throws HibernateException {
		Session s = getSession();
		// String enddate = DateUtilExtend.getNowDate2();
		// StringBuffer sqlStr = new StringBuffer();
		try {
			Query q = s.getNamedQuery("getConferenceSQL");
			q.setString("opercode", username);
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
	 * Description: ConferenceDAO根据当前日期取得要下发名单的会议<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-5-29 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public List getAllotAttendeeConfByDate() throws HibernateException {
		Session s = getSession();
		String beginDate = DateUtilExtend.getNowDate2();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append(" from TConference where status<>'9' and conBegindate='"
				+ beginDate + "'");
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
	 * Description: ConferenceDAO根据条件查询会议<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 韩纪伟 2006-4-5 <br>
	 * 
	 * @author 韩纪伟
	 * @version
	 * @since 1.0
	 */
	public List getConferenceByQuery(String confName, String confType,
			String confRoom, String confDept, String beginDate, String endDate,
			String compere, String username) throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		// HashMap map = new HashMap();
		sqlStr
				.append(
						"select conf.con_Id as conId, conf.con_Name as conName, conf.room_Id as roomId,")
				.append(
						"room.room_Name as roomName,room.address as address,conf.type_Name as typeName, ")
				.append(
						"conf.con_Begindate as beginDate, conf.con_Begintime as beginTime, conf.con_Enddate as endDate,")
				.append(
						"conf.con_Endtime as endTime,dept.dept_Name as deptName,conf.organiger_Id as orgId, ")
				.append(
						"conf.compere as compere,conf.con_Explain as explain, conf.if_Serecy as serecy, conf.status as status,")
				.append("conf.content as content, conf.comments as comments ")
				.append(
						"from ykt_conf.T_Conference conf,ykt_cur.T_Cif_Dept dept,ykt_conf.T_Assembly_Room room ")
				.append(
						"where conf.room_Id = room.room_Id and conf.organiger_Id=dept.dept_Code and conf.status<>'9' ")
				.append(
						"and conf.organiger_Id in (select dept_Id from ykt_conf.T_Dept_Limit where oper_Code='"
								+ username + "')");
		if (null!=confName&&!"".equals(confName)) {
			sqlStr.append(" and conf.con_Name like '%" + confName + "%'");
		}
		if (null!=confType&&(!"".equals(confType)) && (!"-".equals(confType))) {
			sqlStr.append(" and conf.type_Name ='" + confType + "'");
		}
		if (null!=confRoom&&(!"-".equals(confRoom)) && (!"".equals(confRoom))) {
			sqlStr.append(" and conf.room_Id='" + confRoom + "'");
		}
		if (null!=confDept&&(!"-".equals(confDept)) && (!"".equals(confDept))) {
			sqlStr.append(" and conf.organiger_Id='" + confDept + "'");
		}
		if (null!=beginDate&&(!"".equals(beginDate))) {
			sqlStr.append(" and conf.con_Begindate='" + beginDate + "'");
		}
		if (null!=endDate&&!"".equals(endDate)) {
			sqlStr.append(" and conf.con_Enddate>='" + endDate + "'");
		}
		if (null!=compere&&!"".equals(compere)) {
			sqlStr.append(" and conf.compere like '%" + compere + "%'");
		}
		sqlStr.append(" order by conf.con_Begindate desc,conf.con_Begintime desc");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			info.info(sqlStr.toString());
			q.addScalar("conId", Hibernate.INTEGER);
			q.addScalar("conName", Hibernate.STRING);
			q.addScalar("roomId", Hibernate.STRING);
			q.addScalar("roomName", Hibernate.STRING);
			q.addScalar("address", Hibernate.STRING);
			q.addScalar("typeName", Hibernate.STRING);
			q.addScalar("beginDate", Hibernate.STRING);
			q.addScalar("beginTime", Hibernate.STRING);
			q.addScalar("endDate", Hibernate.STRING);
			q.addScalar("endTime", Hibernate.STRING);
			q.addScalar("deptName", Hibernate.STRING);
			q.addScalar("orgId", Hibernate.STRING);
			q.addScalar("compere", Hibernate.STRING);
			q.addScalar("explain", Hibernate.STRING);
			q.addScalar("serecy", Hibernate.STRING);
			q.addScalar("status", Hibernate.STRING);
			q.addScalar("content", Hibernate.STRING);
			q.addScalar("comments", Hibernate.STRING);
			return q.list();
		} catch (HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}

	public TConference getConIdByTime(String username) {
		TConference conf = null;
		Session s = getSession();
		String beginDate = DateUtilExtend.getNowDate2();
		String signTime = DateUtilExtend.getNowTime2();
		StringBuffer sqlStr = new StringBuffer();
		if("".equals(username)){
		sqlStr.append(" from TConference where status<>'9' and conBegindate='"
				+ beginDate + "' and conSigntime<='" + signTime
				+ "' and conEndtime>='" + signTime + "'");
		}else{
			sqlStr.append(" from TConference where status<>'9' and conBegindate='"
					+ beginDate + "' and conSigntime<='" + signTime
					+ "' and conEndtime>='" + signTime + "' and preplan2='"+username+"'");
		}
		try {
			Query q = s.createQuery(sqlStr.toString());
			List list = q.list();
			Iterator iter = list.iterator();
			if (iter.hasNext()) {
				conf = (TConference) iter.next();
			}
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.error(he);
			throw he;
		}
		return conf;
	}

	public List getConfList() {
		List list = null;
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append(" from TConference where status<>'9'");
		try {
			Query q = s.createQuery(sqlStr.toString());
			list = q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.error(he);
		} catch (Exception e) {
			e.printStackTrace();
			errlog.error(e);
		}
		return list;
	}

	public TConference getConference(int ConfId) {
		TConference conf = null;
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append(" from TConference where conId=" + ConfId);
		try {
			Query q = s.createQuery(sqlStr.toString());
			List list = q.list();
			Iterator iter = list.iterator();
			if (iter.hasNext()) {
				conf = (TConference) iter.next();
			}
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.error(he);
		} catch (Exception e) {
			e.printStackTrace();
			errlog.error(e);
		}

		return conf;
	}
	
	public List getAvailableConfByUser(String username){
		Session s = getSession();
		String beginDate = DateUtilExtend.getNowDate2();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append(" from TConference where status<>'9' and conBegindate='"
				+ beginDate + "' and preplan2='"+username+"'");
		try {
			Query q = s.createQuery(sqlStr.toString());
			return q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.error(he);
			throw he;
		}
		
	}
	
	public List checkMeetingRoom(String roomId, String signTime, String beginDate,
			String beginTime, String endDate, String endTime){
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append(" from TConference where status<>'9' and roomId='"+roomId+"' and conBegindate='"
				+ beginDate + "' and conBegintime<='"+beginTime+"' and conEndtime>='"+beginTime+"'");
		try {
			Query q = s.createQuery(sqlStr.toString());
			return q.list();
		} catch (HibernateException he) {
			he.printStackTrace();
			errlog.error(he);
			throw he;
		}
	}

}
