/**
 * 
 */
package com.kingstargroup.advquery.hibernate.util;

import java.util.ArrayList;
import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.Transaction;

import com.kingstargroup.advquery.common.DateUtilExtend;
import com.kingstargroup.advquery.common.Encryptor;
import com.kingstargroup.advquery.hibernate.dao.UserDAO;
import com.kingstargroup.advquery.hibernate.dao.UserLimitDAO;
import com.kingstargroup.advquery.hibernate.dao.UserStoreLimitDAO;
import com.kingstargroup.advquery.hibernate.user.TLeadqueryOperator;
import com.kingstargroup.advquery.hibernate.user.TLeadqueryOperlimit;
import com.kingstargroup.advquery.hibernate.user.TLeadqueryOperlimitKey;
import com.kingstargroup.advquery.hibernate.user.TLeadqueryStorelimit;
import com.kingstargroup.advquery.hibernate.user.TLeadqueryStorelimitKey;
import com.kingstargroup.advquery.subsyslog.TSubsysLog;
import com.kingstargroup.advquery.util.StringUtil;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: UserUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 锟斤拷锟斤拷锟斤拷锟斤拷   锟斤拷锟斤拷锟斤拷   锟斤拷锟斤拷时锟斤拷     锟斤拷锟斤拷锟斤拷锟斤拷<br>
 * ===================================<br>
 *  锟斤拷锟斤拷    Xiao Qi  2005-11-10  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class UserUtil extends BasicUtil {

	/**
	 * Description:锟斤拷录
	 * @param username
	 * @param password
	 * @return
	 * Modify History:
	 */
	public static boolean login(String username, String password) {
		UserDAO dao = UserDAO.getInstance();
		try {
			TLeadqueryOperator user = (TLeadqueryOperator) dao.findByPrimaryKey(TLeadqueryOperator.class, username);
			if (user == null) {
				return false;
			}
			String pwd = user.getOperPwd();
			if (!Encryptor.digest(password).equals(pwd)) {
				return false;
			}
		} catch(HibernateException he) {
			return false;		
		} finally {
			closeSession();
		}
		return true;
	}
		/**
		 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
		 * File name: .java<br>
		 * Description: UserUtil记录登录信息<br>
		 * Return: void<br>
		 * Modify History: <br>
		 * 操作类型    操作人     操作时间       操作内容<br>
		 * ======================================<br>
		 *  创建      韩纪伟     2006-5-16  <br>
		 * @author   韩纪伟
		 * @version 
		 * @since 1.0
		 */
	public static void createLoginInfo(String loginName){
		String sysDate = DateUtilExtend.getNowDate2();
		String sysTime = DateUtilExtend.getNowTime();
		UserDAO dao = UserDAO.getInstance();
		Transaction t = beginTransaction();
		try {
			TSubsysLog syslog = new TSubsysLog();
			syslog.setCustId(new Integer(0));
			syslog.setSussysId(new Integer(2002));
			syslog.setLoginName(loginName);
			syslog.setLogDate(sysDate);
			syslog.setLogTime(sysTime);
			syslog.setComments(loginName+"["+sysDate+sysTime+"]"+":成功登录领导查询系统");
			dao.save(syslog);
			t.commit();
		} catch (Exception he) {
			he.printStackTrace();
			t.rollback();
		}
	}

	
	public static boolean createUser(String userid, 
									String username, 
									String password,
									String storeLimitString, 
									String userLimitString, 
									String isShopOwner) {
		UserDAO dao = UserDAO.getInstance();
		Transaction t = beginTransaction();
		try {
			if (dao.findByPrimaryKey(TLeadqueryOperator.class, userid) != null) {
				return false;
			}
			/*
			 * 锟斤拷锟斤拷没锟?
			 */
			TLeadqueryOperator user = new TLeadqueryOperator();
			user.setOperCode(userid);
			user.setOperName(username);
			user.setOperPwd(Encryptor.digest(password));
			user.setIsShopOwner(isShopOwner);
			dao.saveOrUpdate(user);
			/*
			 * 锟斤拷锟斤拷锟酵拷没锟饺拷锟?
			 */
			String userLimits[] = StringUtil.split(userLimitString, ",");
			for (int i = 0; i < userLimits.length; i++) {				
				TLeadqueryOperlimitKey key = new TLeadqueryOperlimitKey();
				key.setFuncCode(userLimits[i]);
				key.setOperCode(userid);
				TLeadqueryOperlimit limit = new TLeadqueryOperlimit(key);
				dao.save(limit);
			}
			/*
			 * 锟斤拷锟斤拷袒锟饺拷锟?
			 */
			String storeLimits[] = StringUtil.split(storeLimitString, ",");
			for (int i = 0; i < storeLimits.length; i++) {
				TLeadqueryStorelimitKey key = new TLeadqueryStorelimitKey();
				key.setStoreCode(storeLimits[i]);
				key.setOperCode(userid);
				TLeadqueryStorelimit limit = new TLeadqueryStorelimit(key);
				dao.save(limit);
			}
			t.commit();
		} catch(HibernateException he) {
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
		return true;
	}
	
	public static boolean updateUser(String userid, 
									String username, 
									String storeLimitString, 
									String userLimitString, 
									String isShopOwner) {
		UserDAO dao = UserDAO.getInstance();
		UserLimitDAO limitDAO = UserLimitDAO.getInstance();
		UserStoreLimitDAO storeLimitDAO = UserStoreLimitDAO.getInstance();
		Transaction t = beginTransaction();
		try {
			/*
			* 锟斤拷锟斤拷锟矫伙拷锟斤拷息
			*/
			TLeadqueryOperator user = (TLeadqueryOperator) dao.findByPrimaryKey(TLeadqueryOperator.class, userid);
			user.setOperCode(userid);
			user.setOperName(username);
			user.setIsShopOwner(isShopOwner);
			dao.saveOrUpdate(user);
			/*
			* 锟斤拷锟斤拷锟酵拷没锟饺拷锟?
			*/
			limitDAO.deleteFuncList(userid);//锟斤拷锟斤拷锟饺拷薇锟斤拷锟饺拷锟?
			String userLimits[] = StringUtil.split(userLimitString, ",");
			for (int i = 0; i < userLimits.length; i++) {
				TLeadqueryOperlimitKey key = new TLeadqueryOperlimitKey();
				key.setFuncCode(userLimits[i]);
				key.setOperCode(userid);
				TLeadqueryOperlimit limit = new TLeadqueryOperlimit(key);
				dao.save(limit);
			}
			/*
			* 锟斤拷锟斤拷袒锟饺拷锟?
			*/
			storeLimitDAO.deleteStoreList(userid);
			String storeLimits[] = StringUtil.split(storeLimitString, ",");
			for (int i = 0; i < storeLimits.length; i++) {
				TLeadqueryStorelimitKey key = new TLeadqueryStorelimitKey();
				key.setStoreCode(storeLimits[i]);
				key.setOperCode(userid);
				TLeadqueryStorelimit limit = new TLeadqueryStorelimit(key);
				dao.save(limit);
			}
			t.commit();
		} catch(HibernateException he) {
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
		return true;
	}	
	
	/**
	 * Description:锟睫革拷锟斤拷锟斤拷
	 * @param username
	 * @param oldPwd
	 * @param newPwd
	 * @return
	 * Modify History:
	 */
	public static boolean changePwd(String username, String oldPwd, String newPwd) {
		Transaction t = beginTransaction();
		UserDAO dao = UserDAO.getInstance();
		try {
			TLeadqueryOperator user = (TLeadqueryOperator) 
											dao.findByPrimaryKey(TLeadqueryOperator.class, username);
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
	
	public static List listUsers() {
		UserDAO dao = UserDAO.getInstance();
		try {
			return dao.getUsers();
		} catch (HibernateException he) {
			return null;
		} finally {
			closeSession();
		}
	}
	
	public static boolean deleteUsers(String ids[]) {
		Transaction t = beginTransaction();
		UserDAO dao = UserDAO.getInstance();
		UserLimitDAO limitDAO = UserLimitDAO.getInstance();
		UserStoreLimitDAO storeDAO = UserStoreLimitDAO.getInstance();
		try {
			limitDAO.deleteFuncList(ids);
			storeDAO.deleteStoreList(ids);
			dao.deleteUsers(ids);
			t.commit();
			return true;
		} catch(HibernateException he) {
			t.rollback();
			return false;
		} finally {
			closeSession();
		}
	}
	
	public static TLeadqueryOperator getUser(String userid) {
		UserDAO dao = UserDAO.getInstance();
		try {
			return (TLeadqueryOperator) dao.findByPrimaryKey(TLeadqueryOperator.class, userid);
		} catch(HibernateException he) {
			return null;
		} finally {
			closeSession();
		}
	}
	
	public static String getUserLimitString(String userid) {
		UserLimitDAO dao = UserLimitDAO.getInstance();
		try {			
			return StringUtil.merge(dao.getFuncList(userid), ",");
		} catch (HibernateException he) {
			return "";
		} finally {
			closeSession();
		}
	}
	
	public static String getStoreLimitString(String userid) {
		UserStoreLimitDAO dao = UserStoreLimitDAO.getInstance();
		try {			
			return StringUtil.merge(dao.getStoreList(userid), ",");
		} catch (HibernateException he) {
			return "";
		} finally {
			closeSession();
		}
	}
	
	public static boolean resetPassword(String ids[]) {
		Transaction t = beginTransaction();
		UserDAO dao = UserDAO.getInstance();		
		try {
			for (int i = 0; i < ids.length; i++) {
				TLeadqueryOperator user = (TLeadqueryOperator) dao.findByPrimaryKey(TLeadqueryOperator.class, ids[i]);
				user.setOperPwd(Encryptor.digest("111111"));
				dao.saveOrUpdate(user);
			}
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
	 * Description:锟矫碉拷指锟斤拷锟矫伙拷锟侥革拷8目锟叫憋拷
	 * @param userId
	 * @return
	 * Modify History:
	 */
	public static List getUserParentFuncList(String userId) {
		UserDAO dao = UserDAO.getInstance();
		List funcList = new ArrayList();
		try {
			funcList = dao.getUserParentFuncList(userId);
		} catch (HibernateException he) {
			
		} finally {
			closeSession();
		}
		return funcList;
	}
	
	public static List getUserChildFuncList(String userId, String parentId) {		
		UserDAO dao = UserDAO.getInstance();
		List funcList = new ArrayList();
		try {
			funcList = dao.getUserChildFuncList(userId, parentId);
		} catch (HibernateException he) {
			
		} finally {
			closeSession();
		}
		return funcList;
	}
	
	public static boolean checkUserRight(String userId, String funcURL) {
		UserDAO dao = UserDAO.getInstance();		
		try {
			return dao.checkUserRight(userId, funcURL);			
		} catch (HibernateException he) {
			return false;
		} finally {
			closeSession();
		}
	}

}
