/**
 * 
 */
package com.kingstargroup.ecard.common;

import org.hibernate.Transaction;

import com.liferay.portal.util.HibernateUtil;
import com.liferay.util.InstancePool;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: BasicUtil.java
 * Description: 
 * Modify History: 
 * 操作类型   操作人   操作时间     操作内容
 * ===================================
 *  创建    Xiao Qi  2005-10-2  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class BasicUtil {
	
	/**
	 * Description:得到事务管理类
	 * @return
	 * Modify History:
	 */
	protected static EcardTransactionManager getTxManager() {		
		return new EcardTransactionManager();
		
	}
	
	protected static Object getPersistence(String className) {		
		return InstancePool.get(className);
	}
	
	protected static void closeSession() {
		HibernateUtil.closeSession();
	}
	
	protected static Transaction beginTransaction() {
		return HibernateUtil.openLocalSession().beginTransaction();
	}
}
