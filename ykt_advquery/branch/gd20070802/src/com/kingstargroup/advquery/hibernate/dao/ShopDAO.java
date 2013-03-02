/**
 * 
 */
package com.kingstargroup.advquery.hibernate.dao;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ShopDAO.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-13  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class ShopDAO extends BasicDAO {

	/**
	 * Description:singleton pattern
	 * @return
	 * Modify History:
	 */
	public static ShopDAO getInstance() {
		if (_instance == null) {
			_instance = new ShopDAO();
		}
		return _instance;
	}
	
	public List getChildList(String parentId) throws HibernateException {
		Session s = getSession();
		try {
			Query q = s.createQuery(" from TCifShop where deptId = :parentId and shop_state!=2 order by shopId asc");
			q.setInteger("parentId", Integer.parseInt(parentId));
			q.setCacheable(true);
			return q.list();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw ex;
		}
	}
	
	private static ShopDAO _instance;
	private Log _log = LogFactory.getLog(ShopDAO.class.getClass());

}
