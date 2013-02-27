package com.kingstargroup.action.user;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: LoginServlet.java
 * Description: 用户登入类
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期     操作者    操作内容简述
 * 创建  				2005-9-28    何林青    处理用户登入 用户session管理
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */

import org.apache.log4j.Logger;
import org.apache.struts.Globals;
import org.apache.struts.util.MessageResources;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Session;
import org.hibernate.Transaction;

import java.io.IOException;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.kingstargroup.action.user.LoginCheck;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapUserTable;
import com.kingstargroup.form.TSubsysLog;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.LoginUserManager;
import com.kingstargroup.utils.XMLGenerateUtil;

public class LoginServlet extends HttpServlet {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(LoginServlet.class);

	/**
	 * Constructor of the object.
	 */
	public LoginServlet() {
		super();
	}

	/**
	 * Destruction of the servlet. <br>
	 */
	public void destroy() {
		super.destroy(); // Just puts "destroy" string in log
		// Put your code here
	}

	/**
	 * The doGet method of the servlet. <br>
	 * 
	 * This method is called when a form has its tag value method equals to get.
	 * 
	 * @param request
	 *            the request send by the client to the server
	 * @param response
	 *            the response send by the server to the client
	 * @throws ServletException
	 *             if an error occurred
	 * @throws IOException
	 *             if an error occurred
	 */
	public void doGet(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		if (logger.isDebugEnabled()) {
			logger
					.debug("doGet(HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("doGet(HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
	}

	/**
	 * The doPost method of the servlet. <br>
	 * 
	 * This method is called when a form has its tag value method equals to
	 * post.
	 * 
	 * @param request
	 *            the request send by the client to the server
	 * @param response
	 *            the response send by the server to the client
	 * @throws ServletException
	 *             if an error occurred
	 * @throws IOException
	 *             if an error occurred
	 */
	public void doPost(HttpServletRequest request, HttpServletResponse response)
			throws ServletException, IOException {
		if (logger.isDebugEnabled()) {
			logger
					.debug("doPost(HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}
		MessageResources msgResources = (MessageResources) getServletContext()
				.getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";
		try {

			String userName = request.getParameter("UserName");
			String password = request.getParameter("PassWord");
			String retCode = LoginCheck.logindbCheck(userName, password);

			if (ErrorCode.NO_USER.equals(retCode)) {
				xmlOut = XMLGenerateUtil.XMLGenerate(retCode, msgResources
						.getMessage("user.loginServlet.NO_USER"), null);
			} else if (ErrorCode.PWD_ERROR.equals(retCode)) {
				xmlOut = XMLGenerateUtil.XMLGenerate(retCode, msgResources
						.getMessage("user.loginServlet.PWD_ERROR"), null);
			} else if (ErrorCode.USER_STOPED.equals(retCode)) {
				xmlOut = XMLGenerateUtil.XMLGenerate(retCode, msgResources
						.getMessage("user.loginServlet.USER_STOPED"), null);
			} else {
				xmlOut = XMLGenerateUtil.XMLGenerate("0000", retCode, null);
				MapUserTable mapUserTable = LoginUserManager.getForm(userName);
				request.getSession().invalidate();
				request.getSession(true)
						.setAttribute("userLogin", mapUserTable);
				Transaction tx = null;
				try {
					Session session = HibernateSessionFactory.currentSession();
					tx = session.beginTransaction();
					mapUserTable.setLogintime(DateUtil.getNow());
					session.update(mapUserTable);
					TSubsysLog syslog = new TSubsysLog();
					syslog.setCustId(Integer.valueOf("0"));
					syslog.setLoginName(mapUserTable.getUsername());
					syslog.setLogDate(DateUtil.getNow().substring(0, 8));
					syslog.setLogTime(DateUtil.getNow().substring(8));
					syslog.setFlag(Integer.valueOf("0"));
					syslog.setSussysId(Integer.valueOf("2003"));
					syslog.setComments(mapUserTable.getUsername() + "["
							+ DateUtil.getNow() + "]:成功登陆监控系统");
					session.save(syslog);
					tx.commit();
				} catch (Exception e) {
					if (logger.isInfoEnabled()) {
						logger
								.info(
										"doPost(HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
					}
					if (tx != null) {
						tx.rollback();
					}
					xmlOut = XMLGenerateUtil.XMLGenerate(
							ErrorCode.SERVER_IS_BUSY, msgResources
									.getMessage("server.state.SERVER_IS_BUSY"),
							null);
					XMLGenerateUtil.XMLSendOut(request, response, xmlOut);
				} finally {
					HibernateSessionFactory.closeSession();
				}
			}
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {
			logger.error("doPost(HttpServletRequest, HttpServletResponse)", e);
			// server is busy!
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
					msgResources.getMessage("server.state.SERVER_IS_BUSY"),
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("doPost(HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
	}

	/**
	 * Initialization of the servlet. <br>
	 * 
	 * @throws ServletException
	 *             if an error occure
	 */
	public void init() throws ServletException {
		// Put your code here

	}

}
