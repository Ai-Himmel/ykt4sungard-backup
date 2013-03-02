package com.kingstargroup.conference.dao;

import java.util.Iterator;
import java.util.List;

import org.apache.log4j.Logger;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.CONSTANT;

public class AssemblyRoomDAO extends BasicDAO {
	private static AssemblyRoomDAO _instance;

	private Logger errlog = Logger.getLogger("Errlog");

	public static AssemblyRoomDAO getInstance() {
		if (_instance == null) {
			_instance = new AssemblyRoomDAO();
		}
		return _instance;
	}

	public void deleteAssemblyRoom(String ids[]) throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append(" from TAssemblyRoom where roomId in ('" + ids[0] + "' ");
		for (int i = 1, l = ids.length; i < l; i++) {
			sqlStr.append(", '" + ids[i] + "' ");
		}
		sqlStr.append(")");
		try {
			Query q = s.createQuery(sqlStr.toString());
			Iterator iter = q.iterate();
			while (iter.hasNext()) {
				s.delete(iter.next());
			}
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}

	public void deleteAllAssemblyRoom() throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("delete from TAssemblyRoom");
		try {
			Query q = s.createQuery(sqlStr.toString());
			q.executeUpdate();
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}

	public String getMaxRoomId() throws HibernateException {
		Session s = getSession();
		try {
			SQLQuery q = s
					.createSQLQuery("select max(ROOM_ID)as roomId from T_ASSEMBLY_ROOM");
			List list = q.list();
			if(list.get(0)!=null){
				return list.get(0).toString();
			}
			return "0";			
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}

	public List getAssemblyRoom() throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TAssemblyRoom ");
			return q.list();
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}

	public List getAssemblyRoom(String roomId, String roomName, String address,
			Integer contain) throws HibernateException {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append(" from TAssemblyRoom a where 1=1 ");
		if (!"".equals(roomId)) {
			sqlStr.append(" and a.roomId='" + roomId + "' ");
		}
		if (!"".equals(roomName)) {
			sqlStr.append(" and a.roomName='" + roomName + "' ");
		}
		if (!"".equals(address)) {
			sqlStr.append(" and a.address like '%" + address + "%' ");
		}
		if (null != contain) {
			sqlStr.append(" and a.contain=" + contain);
		}
		try {
			Query q = s.createQuery(sqlStr.toString());
			return q.list();
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: AssemblyRoomDAO根据会议室编号查询会议<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型 操作人 操作时间 操作内容<br>
	 * ======================================<br>
	 * 创建 王莹 2006-4-5 <br>
	 * 
	 * @author 王莹
	 * @version
	 * @since 1.0
	 */
	public List getConferenceByRoomid(String roomId) throws HibernateException {
		Session s = getSession();
		String sql = " from TConference a where a.roomId='" + roomId + "' ";
		try {
			Query q = s.createQuery(sql);
			return q.list();
		} catch (HibernateException ex) {
			errlog.error(ex);
			throw ex;
		}
	}
	
	public List getPicAttendeeList(String conId,String attendeetime, String flag) {
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select ")
			.append(" a.cust_id as custId,")
			.append(" a.cut_name as cutName,")
			.append(" a.dept_name as deptName,")
			.append(" '' as dutyName, a.stuemp_no as stuempNo,")
			.append(" a.attend_Time as attendTime")			
			.append(" from ykt_conf.t_attendee_list a")
			.append(" where a.con_Id=" + conId);
			sqlStr.append(" and a.attend_Sign in ('11','12','13','21','22','23') ");
			if("0".equals(flag)){
				//第一个人
				if(!"".equals(attendeetime)){
					sqlStr.append(" and a.attend_time>'");
					sqlStr.append(attendeetime);
					sqlStr.append("' order by a.attend_Time");
				}else{
					sqlStr.append(" order by a.attend_Time desc");
				}
				
			}else{
				if(!"".equals(attendeetime)){
					sqlStr.append(" and a.attend_time<='");
					sqlStr.append(attendeetime);
					sqlStr.append("' order by a.attend_Time desc");
				}else{
					sqlStr.append(" order by a.attend_Time desc");
				}
			}
			if ("db2".equals(CONSTANT.DB_CONFIG)) {
				sqlStr.append(" with ur");
			}
			
			
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("custId",Hibernate.INTEGER);
			q.addScalar("cutName",Hibernate.STRING);
			q.addScalar("deptName",Hibernate.STRING);
			q.addScalar("dutyName",Hibernate.STRING);
			q.addScalar("stuempNo",Hibernate.STRING);
			q.addScalar("attendTime",Hibernate.STRING);
			return q.list();			
		} catch(HibernateException ex) {
			ex.printStackTrace();
			errlog.error(ex);
			throw ex;
		}
	}
}
