/**
 * 
 */
package com.kingstargroup.conference.util;

import org.hibernate.Transaction;
import com.kingstargroup.conference.hibernate.HibernateSessionFactory;;

public class BasicUtil {
	
	protected static void closeSession() {
		HibernateSessionFactory.closeSession();
	}
	
	protected static Transaction beginTransaction() {
		return HibernateSessionFactory.currentSession().beginTransaction();
	}
}
