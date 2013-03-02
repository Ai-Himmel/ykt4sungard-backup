package com.kingstargroup.conference.util;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;

import org.hibernate.HibernateException;

import com.kingstargroup.conference.common.GetCh2Spell;
import com.kingstargroup.conference.common.SortListColl;
import com.kingstargroup.conference.dao.DelegateDAO;
import com.kingstargroup.conference.dao.DictionaryDAO;
import com.kingstargroup.conference.hibernate.form.TAssemblyRoom;
import com.kingstargroup.conference.hibernate.form.TCifCustomer;
import com.kingstargroup.conference.hibernate.form.TCifDept;
import com.kingstargroup.conference.hibernate.form.TConference;
import com.kingstargroup.conference.hibernate.form.TDelegate;
import com.kingstargroup.conference.hibernate.form.TFuncList;
import com.kingstargroup.conference.hibernate.form.TOperator;
import com.kingstargroup.conference.hibernate.form.TPifDevice;
import com.kingstargroup.conference.hibernate.form.TPifDictionary;

public class GetDictionary extends BasicUtil{

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: GetDictionaryȡ�û������б�<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-3  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static List getAssimblyRoom(){
		DictionaryDAO dao = DictionaryDAO.getInstance();
		List dictList = new ArrayList();
		try {
			dictList = dao.getAssimblyRoom();
		} catch (HibernateException he) {
			he.printStackTrace();
			
		}finally{
			closeSession();
		}
		return dictList;
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: GetDictionaryȡ���������б�<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-3  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static List getConfType(){
		DictionaryDAO dao = DictionaryDAO.getInstance();
		List typeList = new ArrayList();
		try {
			typeList = dao.getConfType();
		} catch (HibernateException he) {
			he.printStackTrace();
		}finally{
			closeSession();
		}
		return typeList;
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: GetDictionaryȡ��һ����λ�б�<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-4  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static List getDeptList(){
		DictionaryDAO dao = DictionaryDAO.getInstance();
		List custList = null;
		List deptList = new ArrayList();
		try {
			custList = dao.getDeptList();
			int custsize = custList.size();
			for (int i = 0; i < custsize; i++) {
				Object[] objects = (Object[]) custList.get(i);
				HashMap confMap = new HashMap();
				confMap.put("deptCode", convent(objects[0]));
				confMap.put("deptName", convent(objects[1]));
				//confMap.put("pym",GetCh2Spell.getBeginCharacter(convent(objects[1])));
				confMap.put("pym",new GetCh2Spell().String2Alpha(convent(objects[1])));
				deptList.add(confMap);
			}
		} catch (HibernateException he) {
			he.printStackTrace();
		}finally{
			closeSession();
			
		}
		Collections.sort(deptList,new SortListColl());
		//Arrays.sort(deptList);
		//System.out.println("++++++++++++++++++++++++++++++++++++++++++++++++++"+deptList);
		return deptList;

	}
	
	
	public static List getDlgtList(String username){
		DelegateDAO dao = new DelegateDAO();
		List dlgtList = new ArrayList();
		try {
			dlgtList = dao.getAllDelegates(username);
		} catch (HibernateException he) {
			he.printStackTrace();
		}finally{
			closeSession();
			
		}
		return dlgtList;
	}
	
	public static TDelegate getDlgt(String id){
		DelegateDAO dao = new DelegateDAO();
		TDelegate dlgt = dao.getDelegate(id);
		return dlgt;		
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: GetDictionary���ݲ���Ա��ȡ�øò���Ա���в���Ȩ�޻����б�<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-5  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static List getConfList(String username){
		DictionaryDAO dao = DictionaryDAO.getInstance();
		List confList = new ArrayList();
		try {
			confList = dao.getConfList(username);
		} catch (HibernateException he) {
			he.printStackTrace();
		}finally{
			closeSession();
		}
		return confList;
	}
	
	public static List getConfListBeforeMeeting(String username){
		DictionaryDAO dao = DictionaryDAO.getInstance();
		List confList = new ArrayList();
		try {
			confList = dao.getConfListBeforeMeeting(username);
		} catch (HibernateException he) {
			he.printStackTrace();
		}finally{
			closeSession();
		}
		return confList;
	}
	
		/**
		 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
		 * File name: .java<br>
		 * Description: GetDictionaryȡ��ְ���б�<br>
		 * Return: List<br>
		 * Modify History: <br>
		 * ��������    ������     ����ʱ��       ��������<br>
		 * ======================================<br>
		 *  ����      ����ΰ     2006-4-7  <br>
		 * @author   ����ΰ
		 * @version 
		 * @since 1.0
		 */
	public static List getDutyList(){
		DictionaryDAO dao = DictionaryDAO.getInstance();
		List dutyList = new ArrayList();
		try {
			dutyList = dao.getDutyList();
		} catch (HibernateException he) {
			he.printStackTrace();
		}finally{
			closeSession();
		}
		return dutyList;
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: GetDictionary���ݵ�¼�Ĳ���Ա�õ������б�<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-7  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static List getGroupNameList(String username){
		DictionaryDAO dao = DictionaryDAO.getInstance();
		List groupList = new ArrayList();
		try {
			groupList = dao.getGroupListByOper(username);
		} catch (HibernateException he) {
			he.printStackTrace();
		}finally{
			closeSession();
		}
		return groupList;
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: GetDictionary���ݲ���Ա��ŵõ������б��е�������Ա<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-11  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static List getAttendeeGroupListByOper(String username){
		DictionaryDAO dao = DictionaryDAO.getInstance();
		List groupList = new ArrayList();
		try {
			groupList = dao.getAttendeeGroupListByOper(username);
		} catch (HibernateException he) {
			he.printStackTrace();
		}finally{
			closeSession();
		}
		return groupList;
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: GetDictionaryȡ�ü�ʱ����������ֵ�<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-11  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static List getDeviceList(){
		DictionaryDAO dao = DictionaryDAO.getInstance();
		List deviceList = new ArrayList();
		try {
			deviceList = dao.getDeviceList();
		} catch (HibernateException he) {
			he.printStackTrace();
		}finally{
			closeSession();
		}
		return deviceList;
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: GetDictionary���ݻ����ұ��ȡ�û���������<br>
	 * Return: String<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-19  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static String getAssemblyNameById(String assid){
		DictionaryDAO dao = DictionaryDAO.getInstance();
		TAssemblyRoom assembly = null;
		try {
			assembly = (TAssemblyRoom)dao.findByPrimaryKey(TAssemblyRoom.class,assid);
		} catch (HibernateException he) {
			he.printStackTrace();
		}finally{
			closeSession();
		}
		return assembly.getRoomName().toString();
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: GetDictionary���ݲ��ű��ȡ�ò�������<br>
	 * Return: String<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-19  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static String getDeptNameByDeptCode(String deptcode){
		DictionaryDAO dao = DictionaryDAO.getInstance();
		TCifDept dept = null;
		try {
			dept = (TCifDept)dao.findByPrimaryKey(TCifDept.class,deptcode);
		} catch (HibernateException he) {
			he.printStackTrace();
		}finally{
			closeSession();
		}
		return dept.getDeptName().toString();
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: GetDictionary�����豸���ȡ�������豸������<br>
	 * Return: String<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-20  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static String getDev999IdByDevId(int devId){
		DictionaryDAO dao = DictionaryDAO.getInstance();
		TPifDevice dev = null;
		try {
			dev = (TPifDevice)dao.findByPrimaryKey(TPifDevice.class,new Integer(devId));
		} catch (HibernateException he) {
			return null;
		}finally{
			//closeSession();
		}
		return dev.getDev999Id().toString();
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorUtil���ݹ��ܺ�ȡ�ù�������<br>
	 * Return: String<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-20  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static String getFuncName(String funcCode) {
		DictionaryDAO dao = DictionaryDAO.getInstance();
		String funcName = "";
		try {
			funcName = ((TFuncList)dao.findByPrimaryKey(TFuncList.class, funcCode)).getFuncName();
		} catch(HibernateException he) {
			
		} finally {
			closeSession();
		}
		return funcName;
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: GetDictionary����Ա�����ȡ������<br>
	 * Return: String<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-21  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static String getCustNameById(int custid){
		DictionaryDAO dao = DictionaryDAO.getInstance();
		try {
			return ((TCifCustomer)dao.findByPrimaryKey(TCifCustomer.class,new Integer(custid))).getCutName();
		} catch (HibernateException he) {
			return null;
		}finally{
			closeSession();
		}
	}
		/**
		 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
		 * File name: .java<br>
		 * Description: GetDictionary���ݻ�����ȡ�û�������<br>
		 * Return: String<br>
		 * Modify History: <br>
		 * ��������    ������     ����ʱ��       ��������<br>
		 * ======================================<br>
		 *  ����      ����ΰ     2006-4-25  <br>
		 * @author   ����ΰ
		 * @version 
		 * @since 1.0
		 */
	public static String getConfNameById(int confid){
		DictionaryDAO dao = DictionaryDAO.getInstance();
		try {
			return ((TConference)dao.findByPrimaryKey(TConference.class,new Integer(confid))).getConName();
		} catch (HibernateException he) {
			return null;
		}finally{
			closeSession();
		}
	}
	
		/**
		 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
		 * File name: .java<br>
		 * Description: GetDictionary���ݲ���Ա��¼��ȡ���䲿�ű��<br>
		 * Return: String<br>
		 * Modify History: <br>
		 * ��������    ������     ����ʱ��       ��������<br>
		 * ======================================<br>
		 *  ����      ����ΰ     2006-4-26  <br>
		 * @author   ����ΰ
		 * @version 
		 * @since 1.0
		 */
	public static String getDeptByOperCode(String opercode){
		DictionaryDAO dao = DictionaryDAO.getInstance();
		try {
			return ((TOperator)dao.findByPrimaryKey(TOperator.class,opercode)).getDeptId();
		} catch (HibernateException he) {
			return null;
		}finally{
			closeSession();
		}
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorUtil��Ա�б�<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-24  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static List getCustTypeList() {
		DictionaryDAO dao = DictionaryDAO.getInstance();	
		List custType = null;
		try {
			custType = dao.getCustTypeList();			
		} catch (HibernateException he) {
			
		} finally {
			closeSession();
		}
		return custType;
	}
	
	public static TPifDictionary getCustType(String dictValue) {
		DictionaryDAO dao = DictionaryDAO.getInstance();	
		TPifDictionary custType = null;
		try {
			custType = dao.getCustType(dictValue);			
		} catch (HibernateException he) {
			
		} finally {
			closeSession();
		}
		return custType;
	}

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorUtil����״̬<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-24  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static String getConfStatus(String typeid) {
		DictionaryDAO dao = DictionaryDAO.getInstance();	
		String confStatus = "";
		try {
			confStatus = dao.getConfStatus(typeid);			
		} catch (HibernateException he) {
			
		} finally {
			closeSession();
		}
		return confStatus;
	}
		/**
		 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
		 * File name: .java<br>
		 * Description: GetDictionary�����Ա״̬<br>
		 * Return: String<br>
		 * Modify History: <br>
		 * ��������    ������     ����ʱ��       ��������<br>
		 * ======================================<br>
		 *  ����      ����ΰ     2006-4-30  <br>
		 * @author   ����ΰ
		 * @version 
		 * @since 1.0
		 */
	public static String getAttendeeStatus(String statusid) {
		DictionaryDAO dao = DictionaryDAO.getInstance();	
		String attStatus = "";
		try {
			attStatus = dao.getAttendeeStatus(statusid);			
		} catch (HibernateException he) {
			
		} finally {
			closeSession();
		}
		return attStatus;
	}
	private static String convent(Object ss) {
		if (null == ss) {
			return "";
		} else {
			return ss.toString();
		}
	}

}
