package com.kingstargroup.utils;

import java.util.Iterator;

import org.apache.log4j.Logger;

import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapUserTable;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: LoginUserManager.java
 * Description: ���ص����û��������Ϣ�ࡣ 
 * Modify History����Change Log��: 
 * �������ͣ��������޸ĵȣ� 		�������� 		������ 		�������ݼ��� 
 * ���� 						2005-10-09 	������ 		����getFrom����
 * <p>
 * 
 * @author ������
 * @version 1.0
 * @since 1.0
 */

public class LoginUserManager {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(LoginUserManager.class);

	public static MapUserTable getForm(String userName) {
		if (logger.isDebugEnabled()) {
			logger.debug("getForm(String) - start"); //$NON-NLS-1$
		}

		MapUserTable mapUserTable = null;
		try {
			Session session = HibernateSessionFactory.currentSession();
			Query query = session
					.createQuery("from MapUserTable as user where user.username=?");
			if (userName == null) {
				query.setString(0, "");
			} else {
				query.setString(0, userName);
			}
			if (query.iterate().hasNext()) {
				mapUserTable = (MapUserTable) query.iterate().next();
				mapUserTable.getUsername();
			}
			HibernateSessionFactory.closeSession();
		} catch (Exception e) {
			logger.warn("getForm(String) - exception ignored", e); //$NON-NLS-1$

		}

		if (logger.isDebugEnabled()) {
			logger.debug("getForm(String) - end"); //$NON-NLS-1$
		}
		return mapUserTable;
	}

}
