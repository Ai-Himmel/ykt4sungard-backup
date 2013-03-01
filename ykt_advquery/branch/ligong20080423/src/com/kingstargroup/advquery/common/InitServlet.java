/**
 * 
 */
package com.kingstargroup.advquery.common;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;

import com.kingstargroup.advquery.hibernate.HibernateSessionFactory;
import com.kingstargroup.advquery.hibernate.util.FuncListUtil;
import com.kingstargroup.advquery.util.WebKeys;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: InitServlet.java<br>
 * Description: <br>
 * Modify History: <br>
 * ��������   ������   ����ʱ��     ��������<br>
 * ===================================<br>
 *  ����    Xiao Qi  2005-11-10  <br>
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
		System.out.println("====== Starting initialize hibernate session factory ======");
		HibernateSessionFactory.init();
		System.out.println("====== Initialize hibernate session factory successfully ======");
		System.out.println("====== Starting construct module JS tree ======");
		getServletContext().setAttribute(WebKeys.MODULE_JS_TREE, FuncListUtil.createJSTree());
		System.out.println("====== Construct module JS tree successfully ======");
	}

	
}
