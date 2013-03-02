package com.kingstargroup.conference.dao;

import java.util.Iterator;
import java.util.List;

import org.apache.log4j.Logger;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

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
					.createSQLQuery("select max(ROOM_ID)as roomId from YKT_CONF.T_ASSEMBLY_ROOM");
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
			sqlStr.append(" and a.roomName like '%" + roomName + "%' ");
		}
		if (!"".equals(address)) {
			sqlStr.append(" and a.address like '%" + address + "%' ");
		}
		if (null != contain) {
			sqlStr.append(" and a.contain>=" + contain);
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
	 * Description: AssemblyRoomDAO���ݻ����ұ�Ų�ѯ����<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ��Ө 2006-4-5 <br>
	 * 
	 * @author ��Ө
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
}
