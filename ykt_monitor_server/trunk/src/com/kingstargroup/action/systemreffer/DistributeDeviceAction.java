package com.kingstargroup.action.systemreffer;

import org.apache.log4j.Logger;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: DistributeDeviceAction.java
 * Description: 2.1.6 分配监控设备给联系人
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期     操作者    操作内容简述
 * 创建  				2005-10-11   何林青    保存给报警联系人分配的设备
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

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
import com.kingstargroup.form.MapContactMonitorTable;
import com.kingstargroup.utils.SplitUtil;
import com.kingstargroup.utils.XMLGenerateUtil;

public class DistributeDeviceAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(DistributeDeviceAction.class);

	/**
	 * Description: 保存分配给信息
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

		Transaction tx = null;
		request.setCharacterEncoding("GBK");
		String contactName = request.getParameter("ContactName");
		String count = request.getParameter("count");
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";
		try {

			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();			
			session.createQuery(
					"delete MapContactMonitorTable where contactname = :contact")
					.setString("contact", contactName).executeUpdate();
			String monitorName ="";
			String monitorNO = "";
			for(int i=0; i<Integer.parseInt(count); i++){
				monitorName = request.getParameter("MonitorName"+i);
				monitorNO = request.getParameter("MonitorNo"+i);
				MapContactMonitorTable mapContactMonitorTable = new MapContactMonitorTable();
				mapContactMonitorTable.setContactname(contactName);
				mapContactMonitorTable.setMonitorno(monitorNO);
				mapContactMonitorTable.setMonitorname(monitorName);
				session.save(mapContactMonitorTable);
			}
			tx.commit();
			xmlOut = XMLGenerateUtil
					.XMLGenerate(
							ErrorCode.SUCCESS,
							msgResources
									.getMessage("com.kingstargroup.acton.systemreffer.DEVICE_DISTRI_SUCCESS"),
							null);
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
	 * Description: 返回报警联系人列表给客户端
	 * 
	 * @param
	 * @return XML Modify History: 2005-10-11 创建
	 */
	public ActionForward contactList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("contactList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		request.setCharacterEncoding("GBK");
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";

		try {

			Session session = HibernateSessionFactory.currentSession();
			Query query = session.createQuery("from MapContactTable");			
			List list = query.list();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {
			logger
					.error(
							"contactList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

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
					.debug("contactList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

	/**
	 * Description: 返回报警联系人监控选项给客户端
	 * 
	 * @param
	 * @return XML Modify History: 2005-10-11 创建
	 */

	public ActionForward monitorItemList(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("monitorItemList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		Transaction tx = null;
		request.setCharacterEncoding("GBK");

		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";

		try {
			String contactName = request.getParameter("ContactName");
			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();
			Query query = session
					.createQuery("from MapContactMonitorTable  monitor where monitor.contactname=:contactName");
			query.setString("contactName", contactName);
			tx.commit();
			List list = query.list();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {
			logger
					.error(
							"monitorItemList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

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
					.debug("monitorItemList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

	/**
	 * Description: 返回lanport以上的设备列表给客户端
	 * 
	 * @param
	 * @return XML Modify History: 2005-10-11 创建
	 */
	public ActionForward fatherSetList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("fatherSetList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		Transaction tx = null;
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";

		try {
			String contactName = request.getParameter("ContactName");
			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();
			Query query = session
					.createQuery("select new com.kingstargroup.form.FatherSetsResult(fatherSets.systemid,fatherSets.systemname) from MapFathersetsTable  fatherSets where fatherSets.systemid not in (select monitor.monitorno from MapContactMonitorTable  monitor where monitor.contactname=:name)");
			query.setString("name", contactName);			
			List list = query.list();
			tx.commit();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {
			logger
					.error(
							"fatherSetList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

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
					.debug("fatherSetList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

	/**
	 * Description: 返回lanprot给客户端
	 * 
	 * @param
	 * @return XML Modify History: 2005-10-11 创建
	 */
	public ActionForward deviceList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("deviceList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		Transaction tx = null;
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";

		try {
			String contactName = request.getParameter("ContactName");
			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();
			Query query = session
					.createQuery("select new com.kingstargroup.form.DeviceResult(sets.setsid,sets.setname) from MapSetsTable  sets where sets.settype='5301' and sets.setsid not in (select monitor.monitorno from MapContactMonitorTable monitor where monitor.contactname=:name)");
			query.setString("name", contactName);
			List list = query.list();
			Query queryFather = session
			.createQuery("select new com.kingstargroup.form.DeviceResult(fatherSets.systemid,fatherSets.systemname) from MapFathersetsTable  fatherSets where fatherSets.systemid not in (select monitor.monitorno from MapContactMonitorTable  monitor where monitor.contactname=:name)");
			queryFather.setString("name", contactName);			
			List listFather = queryFather.list();
			
			Query queryMonitor = session
			.createQuery("from MapContactMonitorTable  monitor where monitor.contactname=:contactName");
			queryMonitor.setString("contactName", contactName);
			List listMonitor = queryMonitor.list();
			String xmlOutMonitor = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
			.valueOf(listMonitor.size()), listMonitor);
	
			
			tx.commit();

			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			xmlOut = XMLGenerateUtil.DeXMLGenerate(xmlOut,listFather);
			xmlOut = XMLGenerateUtil.serialXMLGenerate(xmlOut,xmlOutMonitor,0);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {
			logger
					.error(
							"deviceList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

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
					.debug("deviceList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}
}
