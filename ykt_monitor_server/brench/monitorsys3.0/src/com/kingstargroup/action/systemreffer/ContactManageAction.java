/**
 * 
 */
package com.kingstargroup.action.systemreffer;

import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.Globals;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.util.MessageResources;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import org.hibernate.Transaction;

import com.kingstargroup.action.user.ErrorCode;
import com.kingstargroup.commons.BaseAction;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapContactTable;
import com.kingstargroup.form.MapUserTable;
import com.kingstargroup.utils.XMLGenerateUtil;

/**
 * <br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: ContactManageAction.java<br>
 * Description: <br>
 * Modify History（或Change Log）: <br>
 * 操作类型（创建、修改等） 操作日期 操作者 操作内容简述<br>
 * 创建 2005-11-11 何林青 <br>
 * <p>
 * 
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */
public class ContactManageAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(ContactManageAction.class);

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
		String contactName = request.getParameter("ContactName");
		String contactGender = request.getParameter("ContactGender");
		String contactCompany = request.getParameter("ContactCompany");
		String weekdays = request.getParameter("Weekdays");
		String startTime = request.getParameter("StartTime");
		String endTime = request.getParameter("EndTime");
		String email = request.getParameter("Email");
		String cellphone = request.getParameter("Cellphone");
		try {
			HttpSession httpSession = request.getSession();
			MapUserTable mapUserTable = (MapUserTable) httpSession
					.getAttribute("userLogin");

			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();
			Query query = session
					.createQuery("from MapContactTable a where a.contactname=:contactName");
			query.setString("contactName", contactName);
			Iterator iter = query.iterate();
			if (iter.hasNext()) {
				MapContactTable contactTable = (MapContactTable) iter.next();
				contactTable.setCellphone(cellphone);
				contactTable.setContactcompany(contactCompany);
				contactTable.setContactgender(contactGender);
				contactTable.setEmail(email);
				contactTable.setEndtime(endTime);
				contactTable.setStarttime(startTime);
				contactTable.setWeekdays(weekdays);
				session.save(contactTable);
				xmlOut = XMLGenerateUtil
						.XMLGenerate(
								ErrorCode.SUCCESS,
								msgResources
										.getMessage("contact.ContactManageAction.RESET_SUCCESS"),
								null);
			} else {
				xmlOut = XMLGenerateUtil
						.XMLGenerate(
								ErrorCode.CAN_NOT_RESET,
								msgResources
										.getMessage("contact.ContactManageAction.CAN_NOT_UPDATE"),
								null);
			}
			tx.commit();

			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {
			logger
					.error(
							"save(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

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
	 * Description: 查询报警联系人信息列表
	 * 
	 * @param
	 * @return XML Modify History: 2005-11-11 创建
	 */
	public ActionForward contactList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		Transaction tx = null;
		request.setCharacterEncoding("GBK");

		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";
		String contactName = request.getParameter("ContactName");
		String exceptionType = request.getParameter("ExceptionType");
		String startTime = request.getParameter("StartTime");
		String endTime = request.getParameter("EndTime");
		StringBuffer sqlBuff = new StringBuffer();
		sqlBuff.append("from MapContactTable  a where 1=1 ");
		if (!"".equals(contactName) && null != contactName) {
			sqlBuff.append(" and a.contactname = :contactName");
		}
		if (!"".equals(exceptionType) && null != exceptionType
				&& !"-".equals(exceptionType)) {
			sqlBuff
					.append(" and a.contactname in(select b.contactname ")
					.append(
							"from MapContactMonitorTable b where b.monitorname=:exceptionType)");
		}
		if (!"".equals(startTime) && null != startTime) {
			sqlBuff.append(" and a.starttime <= :startTime");
		}
		if (!"".equals(endTime) && null != endTime) {
			sqlBuff.append(" and a.endtime >= :endTime");
		}

		try {
			HttpSession httpSession = request.getSession();
			MapUserTable mapUserTable = (MapUserTable) httpSession
					.getAttribute("userLogin");
			if ("9999".equals(mapUserTable.getUserrole())) {
				Session session = HibernateSessionFactory.currentSession();
				tx = session.beginTransaction();
				Query query = session.createQuery(sqlBuff.toString());
				if (!"".equals(contactName) && null != contactName) {
					query.setString("contactName", contactName);
				}
				if (!"".equals(exceptionType) && null != exceptionType
						&& !"-".equals(exceptionType)) {
					query.setString("exceptionType", exceptionType);
				}
				if (!"".equals(startTime) && null != startTime) {
					query.setString("startTime", startTime);
				}
				if (!"".equals(endTime) && null != endTime) {
					query.setString("endTime", endTime);
				}
				List list = query.list();
				tx.commit();
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(list.size()), list);
				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);
			}
		} catch (Exception e) {

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

		return null;
	}

	/**
	 * Description: 管理员删除报警联系人
	 * 
	 * @param
	 * @return XML Modify History: 2005-11-11 创建
	 */

	public ActionForward deleteContact(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		Transaction tx = null;
		request.setCharacterEncoding("GBK");

		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";
		String contactName = request.getParameter("ContactName");
		try {
			HttpSession httpSession = request.getSession();
			MapUserTable mapUserTable = (MapUserTable) httpSession
					.getAttribute("userLogin");
			if ("9999".equals(mapUserTable.getUserrole())) {
				Session session = HibernateSessionFactory.currentSession();
				tx = session.beginTransaction();
				Query query = session
						.createQuery("from MapContactTable a where a.contactname=:contactName");
				query.setString("contactName", contactName);
				Iterator iter = query.iterate();
				if (iter.hasNext()) {

					// delete
					session
							.createQuery(
									"delete MapContactTable where contactname=:contactName")
							.setString("contactName", contactName)
							.executeUpdate();
					session
							.createQuery(
									"delete MapContactMonitorTable where contactname=:contactName")
							.setString("contactName", contactName)
							.executeUpdate();
					tx.commit();
					xmlOut = XMLGenerateUtil
							.XMLGenerate(
									ErrorCode.SUCCESS,
									msgResources
											.getMessage("contact.ContactManageAction.DELETE_SUCCESS"),
									null);
				}
			} else {
				xmlOut = XMLGenerateUtil
						.XMLGenerate(
								ErrorCode.CAN_NOT_DELETE,
								msgResources
										.getMessage("contact.ContactManageAction.CAN_NOT_DELETE"),
								null);
			}

			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {

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

		return null;
	}

	/**
	 * Description: 分配选项列表项查询
	 * 
	 * @param
	 * @return XML Modify History: 2005-11-11 创建
	 */
	public ActionForward itemList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("itemList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		Transaction tx = null;
		request.setCharacterEncoding("GBK");

		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";

		try {
			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();
			Query query = session
					.createQuery("select new com.kingstargroup.form.DeviceResult(sets.setsid,sets.setname) from MapSetsTable  sets where sets.settype='5301' order by sets.setsid");
			List list = query.list();
			Query queryFather = session
					.createQuery("select new com.kingstargroup.form.DeviceResult(fatherSets.systemid,fatherSets.systemname) from MapFathersetsTable  fatherSets order by fatherSets.systemid");
			List listFather = queryFather.list();
			tx.commit();

			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			xmlOut = XMLGenerateUtil.DeXMLGenerate(xmlOut, listFather);
			xmlOut = XMLGenerateUtil.serialXMLGenerate(xmlOut, "", 0);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {
			logger
					.error(
							"itemList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

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
					.debug("itemList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

}
