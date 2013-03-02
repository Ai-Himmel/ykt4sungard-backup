package com.kingstargroup.conference.util;

import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.Transaction;

import com.kingstargroup.conference.dao.AssemblyRoomDAO;
import com.kingstargroup.conference.dao.AttGroupNameDAO;
import com.kingstargroup.conference.dao.ConferenceTypeDAO;
import com.kingstargroup.conference.hibernate.form.TAssemblyRoom;
import com.kingstargroup.conference.hibernate.form.TConferenceType;
import com.kingstargroup.conference.hibernate.form.TGroup;

public class ParameterUtil extends BasicUtil{
	
	/**
	 * (non-Javadoc)
	 * @see com.kingstargroup.conference.service.IParameterService#createAssemblyRoom(java.lang.String, java.lang.String, java.lang.Integer, java.lang.String)
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImpl����������<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-3-30  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static boolean createAssemblyRoom(
			String roomid,
			String roomname,
			Integer con,
			String address){
		AssemblyRoomDAO dao = AssemblyRoomDAO.getInstance();
		Transaction t = beginTransaction();
		try {			
			TAssemblyRoom room = new TAssemblyRoom();
			room.setAddress(address);
			room.setContain(con);
			room.setRoomId(roomid);
			room.setRoomName(roomname);
			dao.save(room);
			t.commit();
		} catch (HibernateException e) {
			e.printStackTrace();
			t.rollback();
			return false;
		}finally{
			closeSession();
		}
		return true;
	}	

	/**
	 * (non-Javadoc)
	 * 
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImpl�޸Ļ�����<br>
	 * @author   ��Ө
	 */
	public static boolean modifyAssemblyRoom(
			String id, 
			String name, 
			String address, 
			Integer contain, 
			String comments) {
		AssemblyRoomDAO dao = AssemblyRoomDAO.getInstance(); 
		Transaction t = beginTransaction();
		try {			
			TAssemblyRoom assemblyroom = (TAssemblyRoom) dao.findByPrimaryKey(TAssemblyRoom.class, id);
			assemblyroom.setRoomName(name);
			assemblyroom.setAddress(address);
			assemblyroom.setContain(contain);
			assemblyroom.setComments(comments);
			dao.save(assemblyroom);
			t.commit();
		} catch (HibernateException e) {
			e.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
		return true;
	}
	
	/**
	 * (non-Javadoc)
	 * 
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImpl�����Ҳ�ѯ����������ѯ<br>
	 * @author   ��Ө
	 */
	public static TAssemblyRoom getAssemblyRoom(String id) {
		AssemblyRoomDAO dao = AssemblyRoomDAO.getInstance();
		try {
			TAssemblyRoom assemblyroom = (TAssemblyRoom) dao.findByPrimaryKey(TAssemblyRoom.class, id);		
			return assemblyroom;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}
	
	/**
	 * (non-Javadoc)
	 * 
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImpl�����Ҳ�ѯ���������л�����<br>
	 * @author   ��Ө
	 */
	public static List getAllAssemblyRoom() {
		AssemblyRoomDAO dao = AssemblyRoomDAO.getInstance();
		try {
			return dao.getAssemblyRoom();
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}
	
	/**
	 * (non-Javadoc)
	 * 
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImpl�����Ҳ�ѯ����������ѯ<br>
	 * @author   ��Ө
	 */
	public static List getAssemblyRoom(
			String roomId, 
			String roomName, 
			String address, 
			Integer con) {
		AssemblyRoomDAO dao = AssemblyRoomDAO.getInstance();
		try {
			return dao.getAssemblyRoom(roomId, roomName, address, con);
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}
	
	/**
	 * (non-Javadoc)
	 * 
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImpl�������ұ�Ų�ѯ����<br>
	 * @author   ��Ө
	 */
	public static List getConferenceByRoomid(String id) {
		AssemblyRoomDAO dao = AssemblyRoomDAO.getInstance();
		try {			
			return dao.getConferenceByRoomid(id);
		}catch (HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}		
	}
	
	/**
	 * (non-Javadoc)
	 * 
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImplɾ��������<br>
	 * @author   ��Ө
	 */
	public static boolean deleteAssemblyRoom(String[] ids) {
		AssemblyRoomDAO dao = AssemblyRoomDAO.getInstance();
		Transaction t = beginTransaction();
		try {
			dao.deleteAssemblyRoom(ids);
			t.commit();
			return true;
		}catch (HibernateException he) {
			he.printStackTrace();
			t.rollback();
			return false;
		}finally{
			closeSession();
		}		
	}
	
	
	/**
	 * (non-Javadoc)
	 * 
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImpl���ӻ�������<br>
	 * @author   ��Ө
	 */
	public static boolean createConferenceType(
			String typename, 
			String comments) {
		ConferenceTypeDAO dao = ConferenceTypeDAO.getInstance();
		Transaction t = beginTransaction();		
		try {			
			TConferenceType conftype = new TConferenceType();
			conftype.setTypeName(typename);
			conftype.setComments(comments);			
			dao.save(conftype);
			t.commit();
		} catch (HibernateException e) {
			e.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
		return true;
	}	
	
	/**
	 * (non-Javadoc)
	 * 
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImpl�������Ͳ�ѯ����������ѯ<br>
	 * @author   ��Ө
	 */
	public static TConferenceType getConferenceType(Integer id) {
		ConferenceTypeDAO dao = ConferenceTypeDAO.getInstance();
		try {
			TConferenceType conftype = (TConferenceType) dao.findByPrimaryKey(TConferenceType.class, id);		
			return conftype;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}	
	
	/**
	 * (non-Javadoc)
	 * 
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImpl�������Ͳ�ѯ���������м�¼<br>
	 * @author   ��Ө
	 */
	public static List getAllConferenceType() {
		ConferenceTypeDAO dao = ConferenceTypeDAO.getInstance();
		try {
			return dao.getConfType();
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}	
	
	/**
	 * (non-Javadoc)
	 * 
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImpl�������Ͳ�ѯ��У����<br>
	 * @author   ��Ө
	 */
	public static List getConferenceType(String typename) {
		ConferenceTypeDAO dao = ConferenceTypeDAO.getInstance();
		try {
			return dao.getConfType(typename);
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}	
	
	/**
	 * (non-Javadoc)
	 * 
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImpl�������Ͳ�ѯ�������Ʋ�ѯ<br>
	 * @author   ��Ө
	 */
	public static List getConfTypeForQue(String typename) {
		ConferenceTypeDAO dao = ConferenceTypeDAO.getInstance();
		try {
			return dao.getConfTypeForQue(typename);
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}	
	
	/**
	 * (non-Javadoc)
	 * 
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImpl�޸Ļ�������<br>
	 * @author   ��Ө
	 */
	public static boolean modifyConferenceType(
			Integer id, 
			String name, 
			String comments) {
		ConferenceTypeDAO dao = ConferenceTypeDAO.getInstance(); 
		Transaction t = beginTransaction();
		try {
			if (dao.findByPrimaryKey(TConferenceType.class, id) == null) {
				return false;
			}
			TConferenceType conftype = (TConferenceType) dao.findByPrimaryKey(TConferenceType.class, id);
			conftype.setTypeName(name);
			conftype.setComments(comments);
			dao.save(conftype);
			t.commit();
		} catch(HibernateException e) {
			e.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
		return true;
	}
	
	/**
	 * (non-Javadoc)
	 * 
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImpl���������ͱ�Ų�ѯ����<br>
	 * @author   ��Ө
	 */
	public static List getConferenceByType(String typename) {
		ConferenceTypeDAO dao = ConferenceTypeDAO.getInstance();
		try {			
			return dao.getConferenceByType(typename);
		}catch (HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}		
	}
	
	/**
	 * (non-Javadoc)
	 * 
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImplɾ����������<br>
	 * @author   ��Ө
	 */
	public static boolean deleteConferenceType(String[] ids) {
		ConferenceTypeDAO dao = ConferenceTypeDAO.getInstance();
		Transaction t = beginTransaction();
		try {
			dao.deleteConferenceType(ids);
			t.commit();
			return true;
		}catch(HibernateException he) {
			he.printStackTrace();
			t.rollback();
			return false;
		}finally{
			closeSession();
		}		
	}	
	
	
	/**
	 * (non-Javadoc)
	 * 
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImpl��Ա������<br>
	 * @author   ��Ө
	 */
	public static boolean createAttGroupName(
			String operid, 
			String groupname, 
			String comments) {
		AttGroupNameDAO dao = AttGroupNameDAO.getInstance();
		Transaction t = beginTransaction();		
		try {			
			TGroup tgroup = new TGroup();
			tgroup.setOperId(operid);
			tgroup.setGroupName(groupname);
			tgroup.setComments(comments);
			
			dao.save(tgroup);
			t.commit();
		} catch(HibernateException e) {
			e.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
		return true;
	}

	/**
	 * (non-Javadoc)
	 * 
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImpl��Ա���ѯ����������ѯ<br>
	 * @author   ��Ө
	 */
	public static TGroup getAttGroupName(Integer groupId) {
		AttGroupNameDAO dao = AttGroupNameDAO.getInstance();
		try {
			TGroup group = (TGroup) dao.findByPrimaryKey(TGroup.class, groupId);		
			return group;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}
	
	/**
	 * (non-Javadoc)
	 * 
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImpl��Ա���ѯ���������м�¼<br>
	 * @author   ��Ө
	 */
	public static List getAllAttGroupNameByOperId(String username) {
		AttGroupNameDAO dao = AttGroupNameDAO.getInstance();
		try {
			return dao.getAttGroupNameByOperId(username);
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}

	/**
	 * (non-Javadoc)
	 * 
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImpl��Ա���ѯ�����ز��������µ����м�¼<br>
	 * @author   ��Ө
	 */
	public static List getAllAttGroupName(String operid) {
		AttGroupNameDAO dao = AttGroupNameDAO.getInstance();
		try {
			return dao.getAttGroupNameByOperId(operid);
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}
	
	/**
	 * (non-Javadoc)
	 * 
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImpl��Ա���ѯ����������ѯ<br>
	 * @author   ��Ө
	 */
	public static List getAttGroupName(String operid, String name) {
		AttGroupNameDAO dao = AttGroupNameDAO.getInstance();
		try {
			return dao.getAttGroupName(operid, name);
		} catch(HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}

	public static boolean deleteAttGroupName(String[] ids) {
		AttGroupNameDAO dao = AttGroupNameDAO.getInstance();
		Transaction t = beginTransaction();
		try {
			dao.deleteAttGroupName(ids);
			t.commit();
			return true;
		}catch(HibernateException he) {
			he.printStackTrace();
			t.rollback();
			return false;
		}finally{
			closeSession();
		}		
	}

	public static boolean modifyAttGroupName(Integer id, String operId, String groupName, String comments) {
		AttGroupNameDAO dao = AttGroupNameDAO.getInstance(); 
		Transaction t = beginTransaction();
		try {
			if (dao.findByPrimaryKey(TGroup.class, id) == null) {
				return false;
			}
			TGroup group = (TGroup) dao.findByPrimaryKey(TGroup.class, id);
			group.setOperId(operId);
			group.setGroupName(groupName);
			group.setComments(comments);
			dao.save(group);
			t.commit();
		} catch(HibernateException e) {
			e.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
		return true;
	}


	
	



}