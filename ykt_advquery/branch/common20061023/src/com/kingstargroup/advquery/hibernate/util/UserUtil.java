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
 * ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½   ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½   ï¿½ï¿½ï¿½ï¿½Ê±ï¿½ï¿½     ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½<br>
 * ===================================<br>
 *  ï¿½ï¿½ï¿½ï¿½    Xiao Qi  2005-11-10  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class UserUtil extends BasicUtil {

	/**
	 * Description:ï¿½ï¿½Â¼
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
		 * Description: UserUtil¼ÇÂ¼µÇÂ¼ÐÅÏ¢<br>
		 * Return: void<br>
		 * Modify History: <br>
		 * ²Ù×÷ÀàÐÍ    ²Ù×÷ÈË     ²Ù×÷Ê±¼ä       ²Ù×÷ÄÚÈÝ<br>
		 * ======================================<br>
		 *  ´´½¨      º«¼ÍÎ°     2006-5-16  <br>
		 * @author   º«¼ÍÎ°
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
			syslog.setComments(loginName+"["+sysDate+sysTime+"]"+":³É¹¦µÇÂ¼Áìµ¼²éÑ¯ÏµÍ³");
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
			 * ï¿½ï¿½ï¿½ï¿½Ã»ï¿?
			 */
			TLeadqueryOperator user = new TLeadqueryOperator();
			user.setOperCode(userid);
			user.setOperName(username);
			user.setOperPwd(Encryptor.digest(password));
			user.setIsShopOwner(isShopOwner);
			dao.saveOrUpdate(user);
			/*
			 * ï¿½ï¿½ï¿½ï¿½ï¿½Í¨ï¿½Ã»ï¿½È¨ï¿½ï¿?
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
			 * ï¿½ï¿½ï¿½ï¿½Ì»ï¿½È¨ï¿½ï¿?
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
			* ï¿½ï¿½ï¿½ï¿½ï¿½Ã»ï¿½ï¿½ï¿½Ï¢
			*/
			TLeadqueryOperator user = (TLeadqueryOperator) dao.findByPrimaryKey(TLeadqueryOperator.class, userid);
			user.setOperCode(userid);
			user.setOperName(username);
			user.setIsShopOwner(isShopOwner);
			dao.saveOrUpdate(user);
			/*
			* ï¿½ï¿½ï¿½ï¿½ï¿½Í¨ï¿½Ã»ï¿½È¨ï¿½ï¿?
			*/
			limitDAO.deleteFuncList(userid);//ï¿½ï¿½ï¿½ï¿½ï¿½È¨ï¿½Þ±ï¿½ï¿½ï¿½È¨ï¿½ï¿?
			String userLimits[] = StringUtil.split(userLimitString, ",");
			for (int i = 0; i < userLimits.length; i++) {
				TLeadqueryOperlimitKey key = new TLeadqueryOperlimitKey();
				key.setFuncCode(userLimits[i]);
				key.setOperCode(userid);
				TLeadqueryOperlimit limit = new TLeadqueryOperlimit(key);
				dao.save(limit);
			}
			/*
			* ï¿½ï¿½ï¿½ï¿½Ì»ï¿½È¨ï¿½ï¿?
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
	 * Description:ï¿½Þ¸ï¿½ï¿½ï¿½ï¿½ï¿½
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
	 * Description:ï¿½Ãµï¿½Ö¸ï¿½ï¿½ï¿½Ã»ï¿½ï¿½Ä¸ï¿½8Ä¿ï¿½Ð±ï¿½
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
