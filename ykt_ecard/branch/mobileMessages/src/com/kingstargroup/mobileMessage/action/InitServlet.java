/**
 * 
 */
package com.kingstargroup.mobileMessage.action;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;

import com.kingstargroup.mobileMessage.hibernate.HibernateSessionFactory;
import com.kingstargroup.mobileMessage.util.ClientInitUtil;



/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: InitServlet.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-10  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class InitServlet extends HttpServlet {
	

	/* (non-Javadoc)
	 * @see javax.servlet.GenericServlet#init(javax.servlet.ServletConfig)
	 */
	public void init(ServletConfig sc) throws ServletException {
		super.init(sc);
		
		log.info("====== Starting initialize hibernate session factory ======");
		HibernateSessionFactory.init();
		log.info("====== Initialize hibernate session factory successfully ======");
		
	}
	
	private Logger log = Logger.getLogger(InitServlet.class);

	
}
