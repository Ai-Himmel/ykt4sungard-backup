package com.kingstargroup.action.user;

import org.apache.log4j.Logger;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: UserManager.java
 * Description: 用户管理
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期     操作者    操作内容简述
 * 创建  				2005-10-13   何林青    管理员对用户信息维护
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */

import java.util.Iterator;
import java.util.List;

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

import com.kingstargroup.Constants;
import com.kingstargroup.commons.BaseAction;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapUserTable;
import com.kingstargroup.utils.XMLGenerateUtil;

public class UserManageAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(UserManageAction.class);

	/**
	 * Description: 重置用户信息
	 * 
	 * @param
	 * @return XML Modify History: 2005-10-11 创建
	 */
	public ActionForward save(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("save(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		// HttpSession httpSession = request.getSession();
		// 判断信息
		Transaction tx = null;
		request.setCharacterEncoding("GBK");

		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";
		String userName = request.getParameter("UserName");
		String name = request.getParameter("Name");
		String password = request.getParameter("PassWord");
		String gender = request.getParameter("Gender");
		String company = request.getParameter("Company");
		String email = request.getParameter("Email");
		String phone = request.getParameter("Phone");
		String userRole = request.getParameter("UserRole");
		String userStatus = request.getParameter("UserStatus");

		try {
			HttpSession httpSession = request.getSession();
			MapUserTable mapUserTable = (MapUserTable) httpSession
					.getAttribute("userLogin");
			if (ErrorCode.SUPER_USER.equals(mapUserTable.getUsername())) {
				// reset
				Session session = HibernateSessionFactory.currentSession();
				tx = session.beginTransaction();
				Query query = session
						.createQuery("from MapUserTable  user where user.username= :username");
				query.setString("username", userName);
				Iterator iter = query.iterate();
				if (iter.hasNext()) {
					MapUserTable userTable = (MapUserTable) iter.next();
					userTable.setName(name);
					if (null != password && !"".equals(password)) {
						userTable.setPassword(password);
					}
					userTable.setGender(gender);
					userTable.setCompany(company);
					userTable.setEmail(email);
					userTable.setPhone(phone);
					userTable.setUserrole(userRole);
					userTable.setUserstatus(Long.parseLong(userStatus));
					session.update(userTable);
				}
				tx.commit();
				xmlOut = XMLGenerateUtil
						.XMLGenerate(
								ErrorCode.SUCCESS,
								msgResources
										.getMessage("user.UsermanageAction.RESET_SUCCESS"),
								null);
			} else {
				Session session = HibernateSessionFactory.currentSession();
				tx = session.beginTransaction();
				Query query = session
						.createQuery("from MapUserTable  user where user.username= :username");
				query.setString("username", userName);
				Iterator iter = query.iterate();
				if (iter.hasNext()) {
					MapUserTable userTable = (MapUserTable) iter.next();
					if ("9999".equals(userTable.getUserrole())) {
						// no reset
						xmlOut = XMLGenerateUtil
								.XMLGenerate(
										ErrorCode.CAN_NOT_RESET,
										msgResources
												.getMessage("user.UsermanageAction.CAN_NOT_RESET"),
										null);
					} else {
						// reset
						tx = session.beginTransaction();
						userTable.setName(name);
						if (null != password && !"".equals(password)) {
							userTable.setPassword(password);
						}
						userTable.setGender(gender);
						userTable.setCompany(company);
						userTable.setEmail(email);
						userTable.setPhone(phone);
						userTable.setUserrole(userRole);
						userTable.setUserstatus(Long.parseLong(userStatus));
						session.update(userTable);
						tx.commit();
						xmlOut = XMLGenerateUtil
								.XMLGenerate(
										ErrorCode.SUCCESS,
										msgResources
												.getMessage("user.UsermanageAction.RESET_SUCCESS"),
										null);
					}
				}
			}

			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {
			logger
					.error(
							"save(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
			e.printStackTrace();
			if (tx != null) {
				try {
					tx.rollback();
				} catch (Exception e1) {
					// TODO: handle exception
					e1.printStackTrace();
				}
			}
			// server is busy!
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
					msgResources.getMessage("server.state.SERVER_IS_BUSY"),
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {
			logger
					.error(
							"save(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
			e.printStackTrace();
			if (tx != null) {
				try {
					tx.rollback();
				} catch (Exception e1) {
					// TODO: handle exception
					e1.printStackTrace();
				}
			}
			// server is busy!
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
					msgResources.getMessage("server.state.SERVER_IS_BUSY"),
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} finally {
			HibernateSessionFactory.closeSession();
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("save(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

	/**
	 * Description: 查询用户信息列表
	 * 
	 * @param
	 * @return XML Modify History: 2005-10-11 创建
	 */
	public ActionForward userList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("userList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		Transaction tx = null;
		request.setCharacterEncoding("GBK");

		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";
		String userName = request.getParameter("UserName");
		String name = request.getParameter("Name");
		String userRole = request.getParameter("UserRole");
		String userStatus = request.getParameter("UserStatus");
		StringBuffer sqlBuff = new StringBuffer();
		sqlBuff.append("from MapUserTable  user where 1=1");

		if (!"".equals(userName) && null != userName) {
			sqlBuff.append(" and user.username like :userName");
		}
		if (!"".equals(name) && null != name) {
			sqlBuff.append(" and user.name like :name");
		}
		if (!"".equals(userRole) && null != userRole) {
			sqlBuff.append(" and user.userrole = '").append(userRole).append(
					"'");
		}
		if (!"".equals(userStatus) && null != userStatus) {
			sqlBuff.append(" and user.userstatus = ").append(userStatus);
		}
		try {
			HttpSession httpSession = request.getSession();
			MapUserTable mapUserTable = (MapUserTable) httpSession
					.getAttribute("userLogin");
			if ("admin".equals(mapUserTable.getUsername())) {
				Session session = HibernateSessionFactory.currentSession();
				tx = session.beginTransaction();
				Query query = session.createQuery(sqlBuff.toString());
				if (!"".equals(userName) && null != userName) {
					query.setString("userName", "%"+userName+"%");
				}
				if (!"".equals(name) && null != name) {
					query.setString("name", "%"+name+"%");
				}
				List list = query.list();
				tx.commit();
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(list.size()), list);
				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);
			} else {
				Session session = HibernateSessionFactory.currentSession();
				tx = session.beginTransaction();
				sqlBuff.append(" and not user.username=:adminRole");
				Query query = session.createQuery(sqlBuff.toString());
				query.setString("adminRole", Constants.ADMIN_ROLE);
				if (!"".equals(userName) && null != userName) {
					query.setString("userName", userName);
				}
				if (!"".equals(name) && null != name) {
					query.setString("name", name);
				}
				List list = query.list();
				tx.commit();
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(list.size()), list);
				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);
			}

		} catch (HibernateException e) {
			logger
					.error(
							"userList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
			e.printStackTrace();
			if (tx != null) {
				try {
					tx.rollback();
				} catch (Exception e1) {
					// TODO: handle exception
					e1.printStackTrace();
				}
			}
			// server is busy!
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
					msgResources.getMessage("server.state.SERVER_IS_BUSY"),
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {
			logger
					.error(
							"userList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
			e.printStackTrace();
			if (tx != null) {
				try {
					tx.rollback();
				} catch (Exception e1) {
					// TODO: handle exception
					e1.printStackTrace();
				}
			}
			// server is busy!
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
					msgResources.getMessage("server.state.SERVER_IS_BUSY"),
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} finally {
			HibernateSessionFactory.closeSession();
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("userList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

	/**
	 * Description: 管理员删除用户
	 * 
	 * @param
	 * @return XML Modify History: 2005-10-13 创建
	 */

	public ActionForward deleteUser(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("deleteUser(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		Transaction tx = null;
		request.setCharacterEncoding("GBK");

		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";
		String userName = request.getParameter("UserName");
		try {
			HttpSession httpSession = request.getSession();
			MapUserTable mapUserTable = (MapUserTable) httpSession
					.getAttribute("userLogin");
			if ("admin".equals(mapUserTable.getUsername())) {
				Session session = HibernateSessionFactory.currentSession();
				tx = session.beginTransaction();
				if ("admin".equals(userName)) {
					// no delete
					xmlOut = XMLGenerateUtil
							.XMLGenerate(
									ErrorCode.CAN_NOT_DELETE,
									msgResources
											.getMessage("user.UsermanageAction.CAN_NOT_DELETE"),
									null);
				} else {
					// delete
					session.createQuery(
							"delete MapUserTable where username=:username")
							.setString("username", userName).executeUpdate();
					tx.commit();
					xmlOut = XMLGenerateUtil
							.XMLGenerate(
									ErrorCode.SUCCESS,
									msgResources
											.getMessage("user.UsermanageAction.DELETE_SUCCESS"),
									null);
				}
			} else {
				Session session = HibernateSessionFactory.currentSession();
				tx = session.beginTransaction();
				Query query = session
						.createQuery("from MapUserTable where username=:username");
				query.setString("username", userName);
				Iterator iter = query.iterate();
				if (iter.hasNext()) {
					MapUserTable userTable = new MapUserTable();
					userTable = (MapUserTable) iter.next();
					if ("9999".equals(userTable.getUserrole())) {
						// no delete
						xmlOut = XMLGenerateUtil
								.XMLGenerate(
										ErrorCode.CAN_NOT_DELETE,
										msgResources
												.getMessage("user.UsermanageAction.CAN_NOT_DELETE"),
										null);
					} else {
						// delete
						session.createQuery(
								"delete MapUserTable where username=:username")
								.setString("username", userName)
								.executeUpdate();
						tx.commit();
						xmlOut = XMLGenerateUtil
								.XMLGenerate(
										ErrorCode.SUCCESS,
										msgResources
												.getMessage("user.UsermanageAction.DELETE_SUCCESS"),
										null);
					}
				}

			}
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {
			logger
					.error(
							"deleteUser(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
			e.printStackTrace();
			if (tx != null) {
				try {
					tx.rollback();
				} catch (Exception e1) {
					// TODO: handle exception
					e1.printStackTrace();
				}
			}
			// server is busy!
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
					msgResources.getMessage("server.state.SERVER_IS_BUSY"),
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {
			logger
					.error(
							"deleteUser(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
			e.printStackTrace();
			if (tx != null) {
				try {
					tx.rollback();
				} catch (Exception e1) {
					// TODO: handle exception
					e1.printStackTrace();
				}
			}
			// server is busy!
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
					msgResources.getMessage("server.state.SERVER_IS_BUSY"),
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} finally {
			HibernateSessionFactory.closeSession();
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("deleteUser(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}
}
