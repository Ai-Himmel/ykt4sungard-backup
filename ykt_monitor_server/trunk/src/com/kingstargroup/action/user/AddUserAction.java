package com.kingstargroup.action.user;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name:AddUserAction.java
 * Description: 管理员添加用户
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期     操作者    操作内容简述
 * 创建  				2005-10-08    何林青    添加用户方法
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */

import org.apache.log4j.Logger;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.Globals;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.util.MessageResources;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.kingstargroup.commons.BaseAction;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapUserTable;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.MD5encoding;
import com.kingstargroup.utils.XMLGenerateUtil;

public class AddUserAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(AddUserAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		HttpSession httpSession = request.getSession();
		if (httpSession.getAttribute("userLogin") != null) {
			MapUserTable httpSessionUser = (MapUserTable) httpSession
					.getAttribute("userLogin");
			if (ErrorCode.MANAGER_USER_ROLE.equals(httpSessionUser
					.getUserrole())) {
				Transaction tx = null;
				request.setCharacterEncoding("GBK");
				String userName = request.getParameter("UserName");
				String name = request.getParameter("Name");
				// default password = "123456"
				String passWord = MD5encoding
						.MD5Encode(ErrorCode.DEFAULT_PASSWORD);
				String gender = request.getParameter("Gender");
				String company = request.getParameter("Company");
				String email = request.getParameter("Email");
				String phone = request.getParameter("Phone");
				String userRole = request.getParameter("UserRole");
				// String userStatus = request.getParameter("UserStatus");
				try {
					MessageResources msgResources = (MessageResources) this
							.getServlet().getServletContext().getAttribute(
									Globals.MESSAGES_KEY);
					Session session = HibernateSessionFactory.currentSession();
					String xmlOut = "";
					Query query = session
							.createQuery("from MapUserTable user where user.username=:userName");
					query.setString("userName", userName);
					if (query.iterate().hasNext()) {
						// user exist
						xmlOut = XMLGenerateUtil
								.XMLGenerate(
										ErrorCode.USER_EXIST,
										msgResources
												.getMessage("user.addUserAction.USER_EXIST"),
										null);
					} else {
						// add user
						tx = session.beginTransaction();
						String time = DateUtil.getNow();
						MapUserTable mapUserTable = new MapUserTable();
						mapUserTable.setUsername(userName);
						mapUserTable.setName(name);
						mapUserTable.setPassword(passWord);
						mapUserTable.setGender(gender);
						mapUserTable.setCompany(company);
						mapUserTable.setEmail(email);
						mapUserTable.setPhone(phone);
						mapUserTable.setUserrole(userRole);
						mapUserTable.setLogintime(time);
						mapUserTable.setUserstatus(Long.parseLong(ErrorCode.USER_STATUS_OK));
						mapUserTable.setAdduser(httpSessionUser.getUsername());
						mapUserTable.setCreatetime(time);
						session.save(mapUserTable);
						tx.commit();
						xmlOut = XMLGenerateUtil
								.XMLGenerate(
										ErrorCode.SUCCESS,
										msgResources
												.getMessage("user.addUserAction.ADD_SUCCESS"),
										null);
					}
					XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

				} catch (HibernateException e) {
					logger
							.error(
									"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
					if (tx != null) {
						try {
							tx.rollback();
						} catch (Exception e1) {
							// TODO: handle exception
							e1.printStackTrace();
						}
					}

				} catch (Exception e) {
					logger
							.error(
									"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
					if (tx != null) {
						try {
							tx.rollback();
						} catch (Exception e1) {
							// TODO: handle exception
							e1.printStackTrace();
						}
					}

				} finally {
					HibernateSessionFactory.closeSession();
				}
			}

			if (logger.isDebugEnabled()) {
				logger
						.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
			}
		}
		return null;
	}

}
