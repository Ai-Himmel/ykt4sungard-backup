/**
 * 
 */
package com.kingstargroup.conference.util;

import java.util.ArrayList;
import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.Transaction;

import com.kingstargroup.conference.common.DateUtilExtend;
import com.kingstargroup.conference.common.Encryptor;
import com.kingstargroup.conference.common.StringUtil;
import com.kingstargroup.conference.dao.OperatorDAO;
import com.kingstargroup.conference.hibernate.form.TCifDeptfull;
import com.kingstargroup.conference.hibernate.form.TDeptLimit;
import com.kingstargroup.conference.hibernate.form.TDeptLimitKey;
import com.kingstargroup.conference.hibernate.form.TOperLimit;
import com.kingstargroup.conference.hibernate.form.TOperLimitKey;
import com.kingstargroup.conference.hibernate.form.TOperator;
import com.kingstargroup.conference.hibernate.form.TSubsysLog;

public class OperatorUtil extends BasicUtil {
	private static int nodeId = 1;
	
	public static boolean ifUserExist(String opercode){
		OperatorDAO dao = OperatorDAO.getInstance();
		try {
			if (dao.findByPrimaryKey(TOperator.class, opercode) != null) {
				return true;
			}else{
				return false;
			}
		} catch (HibernateException he) {
			return true;
		}
	}
	
		/**
		 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
		 * File name: .java<br>
		 * Description: OperatorUtil��¼��¼��Ϣ<br>
		 * Return: void<br>
		 * Modify History: <br>
		 * ��������    ������     ����ʱ��       ��������<br>
		 * ======================================<br>
		 *  ����      ����ΰ     2006-5-16  <br>
		 * @author   ����ΰ
		 * @version 
		 * @since 1.0
		 */
	public static void createLoginInfo(String loginName){
		String sysDate = DateUtilExtend.getNowDate2();
		String sysTime = DateUtilExtend.getNowTime();
		OperatorDAO dao = OperatorDAO.getInstance();
		Transaction t = beginTransaction();
		try {
			TSubsysLog syslog = new TSubsysLog();
			syslog.setCustId(new Integer(0));
			syslog.setSussysId(new Integer(2004));
			syslog.setLoginName(loginName);
			syslog.setLogDate(sysDate);
			syslog.setLogTime(sysTime);
			syslog.setComments(loginName+"["+sysDate+sysTime+"]"+":�ɹ���¼����ǩ��ϵͳ");
			dao.save(syslog);
			t.commit();
		} catch (Exception he) {
			he.printStackTrace();
			t.rollback();
		}
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorUtil��������Ա<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-14  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static boolean createOperator(
			String opercode ,
			String opername ,
			String deptcode ,
			String deptLimitString,
			String userLimitString,
			String password ){
		OperatorDAO dao = OperatorDAO.getInstance();
		Transaction t = beginTransaction();
		try {
			if (dao.findByPrimaryKey(TOperator.class, opercode) != null) {
				return false;
			}
			/**
			 * �������Ա��Ϣ
			 */
			TOperator user = new TOperator();
			user.setOperCode(opercode);
			user.setOperName(opername);
			user.setOperPwd(Encryptor.digest(password));
			user.setDeptId(deptcode);
			dao.saveOrUpdate(user);
			/**
			 * �������Ա����Ȩ����Ϣ
			 */
			String userLimits[] = StringUtil.split(userLimitString, ",");
			for (int i = 0; i < userLimits.length; i++) {				
				TOperLimitKey key = new TOperLimitKey();
				key.setFuncCode(userLimits[i]);
				key.setOperCode(opercode);
				TOperLimit limit = new TOperLimit(key);
				dao.save(limit);
			}
			/**
			 * �������Ա����Ȩ����Ϣ
			 */
			String storeLimits[] = StringUtil.split(deptLimitString, ",");
			for (int i = 0; i < storeLimits.length; i++) {
				TDeptLimitKey key = new TDeptLimitKey();
				key.setDeptId(storeLimits[i]);
				key.setOperCode(opercode);
				TDeptLimit limit = new TDeptLimit(key);
				dao.save(limit);
			}
			t.commit();
		} catch(HibernateException he) {
			he.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
		return true;
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorUtilɾ������Ա����֮������ı�<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-17  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static boolean deleteUsers(String opercode){
		Transaction t = beginTransaction();
		OperatorDAO dao = OperatorDAO.getInstance();
		try {
			dao.deleteDeptList(opercode);
			dao.deleteFuncList(opercode);
			dao.deleteUser(opercode);
			t.commit();
			return true;
		} catch(HibernateException he) {
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorUtil�޸Ĳ���Ա����<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-17  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static boolean editPassword(
			String opercode,
			String password){
		OperatorDAO dao = OperatorDAO.getInstance();
		Transaction t = beginTransaction();
		try {
			TOperator user = (TOperator)dao.findByPrimaryKey(TOperator.class,opercode);
			user.setOperPwd(Encryptor.digest(password));
			dao.saveOrUpdate(user);
			t.commit();
			return true;
		} catch (HibernateException he) {
			t.rollback();
			return false;
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorUtil���²���Ա��Ϣ<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-17  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static boolean updateUser(
			String opercode ,
			String opername ,
			String deptcode ,
			String deptLimitString,
			String userLimitString){
		OperatorDAO dao = OperatorDAO.getInstance();
		Transaction t = beginTransaction();
		try {
			/*
			* �޸Ĳ���Ա������Ϣ
			*/
			TOperator user = (TOperator) dao.findByPrimaryKey(TOperator.class, opercode);
			user.setOperCode(opercode);
			user.setOperName(opername);
			user.setDeptId(deptcode);
			dao.saveOrUpdate(user);
			/*
			* �޸�Ȩ���б�
			*/
			dao.deleteFuncList(opercode);
			String userLimits[] = StringUtil.split(userLimitString, ",");
			for (int i = 0; i < userLimits.length; i++) {
				TOperLimitKey key = new TOperLimitKey();
				key.setFuncCode(userLimits[i]);
				key.setOperCode(opercode);
				TOperLimit limit = new TOperLimit(key);
				dao.save(limit);
			}
			/*
			* �޸Ĳ���Ȩ����Ϣ
			*/
			dao.deleteDeptList(opercode);
			String deptLimits[] = StringUtil.split(deptLimitString, ",");
			for (int i = 0; i < deptLimits.length; i++) {
				TDeptLimitKey key = new TDeptLimitKey();
				key.setDeptId(deptLimits[i]);
				key.setOperCode(opercode);
				TDeptLimit limit = new TDeptLimit(key);
				dao.save(limit);
			}
			t.commit();
			return true;
		} catch(HibernateException he) {
			he.printStackTrace();
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorUtil���ݲ���Ա��ȡ�ò���Ա��Ϣ<br>
	 * Return: TOperator<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-17  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static TOperator getOperByOperCode(String opercode){
		OperatorDAO dao = OperatorDAO.getInstance();
		try {
			return (TOperator)dao.findByPrimaryKey(TOperator.class,opercode);
		} catch (HibernateException he) {
			he.printStackTrace();
			return null;
		}finally{
			closeSession();
		}
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorUtilȡ�ø�Ȩ���б�<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-14 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static List getUserParentFuncList(String userId) {
		OperatorDAO dao = OperatorDAO.getInstance();
		List funcList = new ArrayList();
		try {
			funcList = dao.getUserParentFuncList(userId);
		} catch (HibernateException he) {
			he.printStackTrace();
		} finally {
			closeSession();
		}
		return funcList;
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorUtilȡ�����еĲ���Ա�б�<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-14  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static List getAllOperatorList() {
		OperatorDAO dao = OperatorDAO.getInstance();
		List operList = new ArrayList();
		try {
			operList = dao.getAllOperatorList();
		} catch (HibernateException he) {
			he.printStackTrace();
		} finally {
			closeSession();
		}
		return operList;
	}

	/**
	 * (non-Javadoc)
	 * 
	 * @see com.kingstargroup.conference.service.IParameterService#login(java.lang.String,
	 *      java.lang.String) Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 *      File name: .java<br>
	 *      Description: ParameterImplϵͳ��¼<br>
	 *      Modify History: <br>
	 *      �������� ������ ����ʱ�� ��������<br>
	 *      ======================================<br>
	 *      ���� ����ΰ 2006-3-31 <br>
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static boolean login(String username, String password) {
		OperatorDAO dao = OperatorDAO.getInstance();
		try {
			TOperator user = (TOperator) dao.findByPrimaryKey(TOperator.class, username);
			if (user == null) {
				return false;
			}
			String pwd = user.getOperPwd();
			if (!Encryptor.digest(password).equals(pwd)) {
				return false;
			}
		} catch(HibernateException he) {
			he.printStackTrace();
			return false;		
		} finally {
			closeSession();
		}
		return true;
	}
	
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: UserImplȡ�ò���ԱȨ���б�<br>
	 * Return: String<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-3 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public static String getUserLimitString(String userid) {
		OperatorDAO dao = OperatorDAO.getInstance();
		try {			
			return StringUtil.merge(dao.getFuncList(userid), ",");
		} catch (HibernateException he) {
			he.printStackTrace();
			return "";
		} finally {
			closeSession();
		}
	}
	
		/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorUtil���ݲ���Ա���ȡ�����еĲ���Ȩ�ޱ��<br>
	 * Return: String<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-17  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static String getDeptLimitString(String userid) {
		OperatorDAO dao = OperatorDAO.getInstance();
		try {			
			return StringUtil.merge(dao.getDeptList(userid), ",");
		} catch (HibernateException he) {
			he.printStackTrace();
			return "";
		} finally {
			closeSession();
		}
	}
	

	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorUtil����������<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-13 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	private static List createDeptJSList(String parentId, String nodeParentId){
		OperatorDAO dao = OperatorDAO.getInstance();
		List deptList = new ArrayList();
		try {
			List childList = dao.getDeptChildList(parentId);
			for (int i = 0; i < childList.size(); i++) {
				TCifDeptfull dept = (TCifDeptfull) childList.get(i);
				StringBuffer nodeBuff = new StringBuffer();
				nodeBuff.append(nodeId)// nodeId
						.append("|")
						.append(nodeParentId)
						.append("|");// parentId
				if (i == childList.size() - 1){// ls
					nodeBuff.append("1|");
				} else {
					nodeBuff.append("0|");
				}
				nodeBuff.append("|");// path
				nodeBuff.append(dept.getDeptName())
						.append("|");// name
				nodeBuff.append("|");// image
				nodeBuff.append(dept.getDeptCode());// href
				deptList.add(nodeBuff.toString());// add to list
				int parentNode = nodeId;
				nodeId ++;				
				/*
				 * process child list
				 */
				deptList.addAll(createDeptJSList(dept.getDeptCode().toString(), String.valueOf(parentNode)));
			}
		} catch (HibernateException he) {
			throw he;
		}
		return deptList;
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorUtil����������<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * �������� ������ ����ʱ�� ��������<br>
	 * ======================================<br>
	 * ���� ����ΰ 2006-4-13 <br>
	 * 
	 * @author ����ΰ
	 * @version
	 * @since 1.0
	 */
	public synchronized static List createDeptJSList(String rootId) {
		
		List deptList = new ArrayList();
		try {
			nodeId = 1;
			deptList = createDeptJSList(rootId, "");
		} catch (HibernateException he) {
			
		} finally {
			closeSession();
		}
		return deptList;
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorUtil�����û��ź͸��˵���ȡ���Ӳ˵���<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-20  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static List getUserChildFuncList(String userId, String parentId) {		
		OperatorDAO dao = OperatorDAO.getInstance();
		List funcList = new ArrayList();
		try {
			funcList = dao.getUserChildFuncList(userId, parentId);
		} catch (HibernateException he) {
			
		} finally {
			closeSession();
		}
		return funcList;
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorUtil�û������޸�<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-21  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static boolean changePwd(String username, String oldPwd, String newPwd) {
		Transaction t = beginTransaction();
		OperatorDAO dao = OperatorDAO.getInstance();
		try {
			TOperator user = (TOperator) 
											dao.findByPrimaryKey(TOperator.class, username);
			String pwd = user.getOperPwd();
			if (!Encryptor.digest(oldPwd).equals(pwd)) {
				return false;
			}
			user.setOperPwd(Encryptor.digest(newPwd));
			dao.saveOrUpdate(user);
			t.commit();
		} catch (HibernateException he) {
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
		return true;
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: OperatorUtil����û��ĵ�¼Ȩ��<br>
	 * Return: boolean<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ����ΰ     2006-4-24  <br>
	 * @author   ����ΰ
	 * @version 
	 * @since 1.0
	 */
	public static boolean checkUserRight(String userId, String funcURL) {
		OperatorDAO dao = OperatorDAO.getInstance();		
		try {
			return dao.checkUserRight(userId, funcURL);			
		} catch (HibernateException he) {
			return false;
		} finally {
			closeSession();
		}
	}

}
