package com.kingstargroup.action.systemreffer;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: SetAlertlevelAction.java
 * Description: 2.1.11 系统警戒级别设置
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期     操作者    操作内容简述
 * 创建  				2005-10-11   何林青    保存系统的报警级别
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */

import java.util.Enumeration;
import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
//import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.Globals;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.util.MessageResources;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.kingstargroup.action.user.ErrorCode;
import com.kingstargroup.commons.BaseAction;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapAlertTable;
import com.kingstargroup.form.MapParamTable;
import com.kingstargroup.utils.XMLGenerateUtil;

public class SetAlertlevelAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(SetAlertlevelAction.class);

	public ActionForward save(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		Transaction tx = null;
		String xmlOut = "";
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		request.setCharacterEncoding("GBK");

		try {
			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();
			session.createQuery("delete MapAlertTable").executeUpdate();
			Enumeration enumeration = request.getParameterNames();
			while (enumeration.hasMoreElements()) {
				String name = (String) enumeration.nextElement();
				String value = null;
				if (name.startsWith("param_")) {
					value = request.getParameter(name);
					MapAlertTable mapAlertTable = new MapAlertTable();
					mapAlertTable.setParameter(name.substring(6));
					mapAlertTable
							.setNote(Short.valueOf(value.substring(0, 1)));
					mapAlertTable.setMailalert(Short.valueOf(value.substring(1, 2)));
					mapAlertTable.setPhonealert(Short.valueOf(value.substring(2, 3)));
					session.save(mapAlertTable);
				}
			}
			tx.commit();
			xmlOut = XMLGenerateUtil
					.XMLGenerate(
							ErrorCode.SUCCESS,
							msgResources
									.getMessage("com.kingstargroup.acton.systemreffer.REFFER_SET_SUCCESS"),
							null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {
			logger
					.error(
							"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

			if (tx != null) {
				tx.rollback();
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
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}
	
	
	public ActionForward update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		Transaction tx = null;
		String xmlOut = "";
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		request.setCharacterEncoding("GBK");

		try {
			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();
			String parameter = request.getParameter("parameter");
			String name = request.getParameter("name");
			String note = request.getParameter("note");
			String mailalert = request.getParameter("mailalert");
			String phonealert = request.getParameter("phonealert");
			Query query = session.createQuery("from MapAlertTable  a where a.parameter=:parameter");
			query.setString("parameter", parameter);
			List list = query.list();
			Iterator iter = list.iterator();
			if (iter.hasNext()) {
				MapAlertTable mapAlertTable = (MapAlertTable) iter.next();
				mapAlertTable.setName(name);
				mapAlertTable.setMailalert(Short.valueOf(mailalert));
				mapAlertTable.setNote(Short.valueOf(note));
				mapAlertTable.setPhonealert(Short.valueOf(phonealert));
				session.update(mapAlertTable);
			}
			
			tx.commit();
			xmlOut = XMLGenerateUtil
					.XMLGenerate(
							ErrorCode.SUCCESS,
							msgResources
									.getMessage("com.kingstargroup.acton.systemreffer.ALERT_RESET_SUCCESS"),
							null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {

			if (tx != null) {
				tx.rollback();
			}
			// server is busy!
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
					msgResources.getMessage("server.state.SERVER_IS_BUSY"),
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} finally {
			HibernateSessionFactory.closeSession();
		}

		return null;
	}

	public ActionForward listView(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("listView(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		Transaction tx = null;
		String xmlOut = "";
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		try {

			Session session = HibernateSessionFactory.currentSession();

			tx = session.beginTransaction();
			Query query = session.createQuery("from MapAlertTable");
			tx.commit();
			List list = query.list();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {
			logger
					.error(
							"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

			if (tx != null) {
				tx.rollback();
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
					.debug("listView(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}
	
	public ActionForward alertList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("alertList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}


		Transaction tx = null;
		String xmlOut = "";
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		try {

			Session session = HibernateSessionFactory.currentSession();

			tx = session.beginTransaction();
			String name = request.getParameter("name");
			StringBuffer queryStr = new StringBuffer();
			queryStr.append("from MapAlertTable a where 1=1 ");
			if (!"".equals(name) && null != name) {
				queryStr.append("and a.name like :name ");
			}

			Query query = session.createQuery(queryStr.toString());
			if (!"".equals(name) && null != name) {
				name = "%" + name + "%";
				query.setString("name", name);
			}
			List list = query.list();
			tx.commit();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {
			logger
					.error(
							"alertList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

			if (tx != null) {
				tx.rollback();
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
					.debug("alertList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}
	

}
