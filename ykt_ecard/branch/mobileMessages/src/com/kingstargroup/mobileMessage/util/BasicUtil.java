/**
 * 
 */
package com.kingstargroup.mobileMessage.util;

import java.util.TimerTask;

import org.hibernate.Transaction;

import com.kingstargroup.mobileMessage.hibernate.HibernateSessionFactory;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: BasicUtil.java
 * Description: 
 * Modify History: 
 * ��������   ������   ����ʱ��     ��������
 * ===================================
 *  ����    Xiao Qi  2005-10-2  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public abstract class BasicUtil {
	
	protected static void closeSession() {
		HibernateSessionFactory.closeSession();
	}
	
	protected static Transaction beginTransaction() {
		return HibernateSessionFactory.currentSession().beginTransaction();
	}

}
