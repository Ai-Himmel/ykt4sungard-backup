package com.kingstargroup.conference.util;

import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.Transaction;

import com.kingstargroup.conference.dao.AssemblyRoomDAO;
import com.kingstargroup.conference.dao.AttGroupNameDAO;
import com.kingstargroup.conference.dao.ConferenceTypeDAO;
import com.kingstargroup.conference.dao.DelegateDAO;
import com.kingstargroup.conference.hibernate.form.TAssemblyRoom;
import com.kingstargroup.conference.hibernate.form.TConferenceType;
import com.kingstargroup.conference.hibernate.form.TDelegate;
import com.kingstargroup.conference.hibernate.form.TGroup;

public class ParameterUtil extends BasicUtil{
	
	/**
	 * (non-Javadoc)
	 * @see com.kingstargroup.conference.service.IParameterService#createAssemblyRoom(java.lang.String, java.lang.String, java.lang.Integer, java.lang.String)
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: ParameterImpl会议室增加<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-3-30  <br>
	 * @author   韩纪伟
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
	 * Description: ParameterImpl修改会议室<br>
	 * @author   王莹
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
	 * Description: ParameterImpl会议室查询，按主键查询<br>
	 * @author   王莹
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
	 * Description: ParameterImpl会议室查询，返回所有会议室<br>
	 * @author   王莹
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
	 * Description: ParameterImpl会议室查询，按条件查询<br>
	 * @author   王莹
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
	 * Description: ParameterImpl按会议室编号查询会议<br>
	 * @author   王莹
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
	 * Description: ParameterImpl删除会议室<br>
	 * @author   王莹
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
	 * Description: ParameterImpl增加会议类型<br>
	 * @author   王莹
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
	 * Description: ParameterImpl会议类型查询，按主键查询<br>
	 * @author   王莹
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
	 * Description: ParameterImpl会议类型查询，返回所有记录<br>
	 * @author   王莹
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
	 * Description: ParameterImpl会议类型查询，校验用<br>
	 * @author   王莹
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
	 * Description: ParameterImpl会议类型查询，按名称查询<br>
	 * @author   王莹
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
	 * Description: ParameterImpl修改会议类型<br>
	 * @author   王莹
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
	 * Description: ParameterImpl按会议类型编号查询会议<br>
	 * @author   王莹
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
	 * Description: ParameterImpl删除会议类型<br>
	 * @author   王莹
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
	 * Description: ParameterImpl人员组增加<br>
	 * @author   王莹
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
	 * Description: ParameterImpl人员组查询，按主键查询<br>
	 * @author   王莹
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
	 * Description: ParameterImpl人员组查询，返回所有记录<br>
	 * @author   王莹
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
	 * Description: ParameterImpl人员组查询，返回操作人名下的所有记录<br>
	 * @author   王莹
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
	 * Description: ParameterImpl人员组查询，按条件查询<br>
	 * @author   王莹
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
	
	/**
	 * 取得最大会议室编号
	 * @return
	 */
	public static String getMaxRoomId(){
		AssemblyRoomDAO dao = AssemblyRoomDAO.getInstance();
		try{
			return String.valueOf(Integer.parseInt(dao.getMaxRoomId())+1);
		}catch(HibernateException he){
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

	public static boolean createDelegate(
			String dlgtName, String open,String dept,String operId,
			String comment) {
		DelegateDAO dao = DelegateDAO.getInstance();
		Transaction t = beginTransaction();		
		try {			
			TDelegate delegate = new TDelegate();
			delegate.setDlgtName(dlgtName);
			delegate.setOpen("1");
			delegate.setOperId(operId);
			delegate.setComment(comment);
			delegate.setDeptId("");			
			dao.save(delegate);
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

	public static List getAllDelegates(String operId) {
		DelegateDAO dao = DelegateDAO.getInstance();
		try {
			return dao.getAllDelegates(operId);		
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}
	
	public static TDelegate getDelegate(String id) {
		DelegateDAO dao = DelegateDAO.getInstance();
		try {
			return dao.getDelegate(id);
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}
	
	public static List getDelegates(String operId,String dlgtName) {
		DelegateDAO dao = DelegateDAO.getInstance();
		try {
			return dao.getDelegates(operId,dlgtName);
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}
	
	public static List getConfDlgt(String id) {
		DelegateDAO dao = DelegateDAO.getInstance();
		try {
			List list = dao.getConfDlgt(id);
			return list;
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}
	
	public static boolean deleteDelegates(String[] ids) {
		DelegateDAO dao = DelegateDAO.getInstance();
		Transaction t = beginTransaction();
		try {
			dao.deleteDelegates(ids);
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

	public static boolean modifyDelegate(String id, String dlgtName, String open,String dept,String operId,
			String comment) {
		DelegateDAO dao = DelegateDAO.getInstance();
		Transaction t = beginTransaction();
		try {
			if (dao.getDelegate(id) == null) {
				return false;
			}
			TDelegate delegate = dao.getDelegate(id);
			delegate.setComment(comment);
			delegate.setDeptId(dept);
			delegate.setDlgtName(dlgtName);
			delegate.setOpen(open);
			delegate.setOperId(operId);
			dao.save(delegate);
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