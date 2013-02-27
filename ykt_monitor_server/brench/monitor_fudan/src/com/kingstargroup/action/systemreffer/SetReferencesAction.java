package com.kingstargroup.action.systemreffer;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name:SetReferencesAction.java
 * Description: 设置系统参数
 * Modify History（或Change Log）: 
 * 操作类型（创建、修改等） 操作日期     操作者    操作内容简述
 * 创建                2005-10-10   何林青   系统参数保存方法
 * <p>
 * 
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */

import java.util.Enumeration;
import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

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
import com.kingstargroup.form.MapParamTable;
import com.kingstargroup.utils.XMLGenerateUtil;

public class SetReferencesAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(SetReferencesAction.class);

	public ActionForward save(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest,HttpServletResponse) - start"); //$NON-NLS-1$
		}

		Transaction tx = null;
		String xmlOut = "";
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		request.setCharacterEncoding("GBK");
		try {
			Session session = HibernateSessionFactory.currentSession();
			Enumeration enumration = request.getParameterNames();
			tx = session.beginTransaction();
			session.createQuery("delete MapParamTable").executeUpdate();
			while (enumration.hasMoreElements()) {
				String name = (String) enumration.nextElement();
				String value = null;
				if (name.startsWith("param_")) {
					value = request.getParameter(name);
					MapParamTable record = new MapParamTable();
					record.setParameter(name.substring(6));
					record.setValue(Double.valueOf(value));
					record.setFlag(Short.valueOf("0"));
					session.save(record);
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

	public ActionForward listView(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		Transaction tx = null;
		String xmlOut = "";
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		try {

			Session session = HibernateSessionFactory.currentSession();

			tx = session.beginTransaction();
			Query query = session.createQuery("from MapParamTable");
			List list = query.list();
			tx.commit();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {
			logger
					.error(
							"execute(ActionMapping, ActionForm,HttpServletRequest,HttpServletResponse)", e); //$NON-NLS-1$

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

	public ActionForward referenceList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("referenceList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		Transaction tx = null;
		String xmlOut = "";
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		try {

			Session session = HibernateSessionFactory.currentSession();

			tx = session.beginTransaction();
			String name = request.getParameter("name");
			String type = request.getParameter("type");
			String flag = request.getParameter("flag");
			StringBuffer queryStr = new StringBuffer();
			queryStr.append("from MapParamTable a where 1=1 ");
			if (!"".equals(name) && null != name) {
				queryStr.append("and a.name like :name ");
			}
			if (!"".equals(type) && null != type && !"-".equals(type)) {
				if("1".equals(type)){
					queryStr.append("and (a.parameter = 'HeartInterval' or a.parameter = 'MeMopercentage' or a.parameter = 'CPUpercentage' or a.parameter = 'HWpercentage') ");
				}else if("2".equals(type)){
					queryStr.append("and (a.parameter = 'MutationCycle') ");
				}else if("3".equals(type)){
					queryStr.append("and (a.parameter = 'LargeAmountCycle' or a.parameter = 'LargeAmountLimit' or a.parameter = 'SingleAmountLimit') ");
				}else if("4".equals(type)){
					queryStr.append("and (a.parameter = 'MidDrawCycle') ");
				}else if("5".equals(type)){					
					queryStr.append("and (a.parameter = 'BlackCardCycle') ");
				}else if("6".equals(type)){
					queryStr.append("and (a.parameter = 'OtherCycle') ");					
				}else if("7".equals(type)){
					queryStr.append("and (a.parameter = 'TradeLackCycle') ");
				}else if("8".equals(type)){
					queryStr.append("and (a.parameter = 'SuppressCycle' or a.parameter = 'SuppressTime') ");					
				}else if("9".equals(type)){					
					queryStr.append("and (a.parameter = 'UncheckedCycle') ");
				}else if("10".equals(type)){					
					queryStr.append("and (a.parameter = 'RollbackCycle') ");
				}else if("11".equals(type)){					
					queryStr.append("and (a.parameter = 'BlackListDistrCycle' or a.parameter = 'BlackListDistrTime') ");
				}else if("12".equals(type)){
					queryStr.append("and (a.parameter = 'ClockErrorCycle' or a.parameter = 'ClockErrorLimit') ");
				}else if("13".equals(type)){					
					queryStr.append("and (a.parameter = 'CAUnbalanceCycle') ");
				}else if("14".equals(type)){
					queryStr.append("and (a.parameter = 'ShortTimeMCCycle' or a.parameter = 'CountLimit' or a.parameter = 'ShortTimeLimit') ");
				}else if("15".equals(type)){
					queryStr.append("and (a.parameter = 'DeviceFlushTime') ");
				}
				
			}
			if (!"".equals(flag) && null != flag && !"-".equals(flag)) {
				queryStr.append("and a.flag =:flag ");
			}
			Query query = session.createQuery(queryStr.toString());
			if (!"".equals(name) && null != name) {
				name = "%" + name + "%";
				query.setString("name", name);
			}
			if (!"".equals(flag) && null != flag && !"-".equals(flag)) {
				query.setInteger("flag", Integer.parseInt(flag));
			}
			List list = query.list();
			tx.commit();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {
			logger
					.error(
							"referenceList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

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
					.debug("referenceList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

	// public ActionForward delete(ActionMapping mapping, ActionForm form,
	// HttpServletRequest request, HttpServletResponse response)
	// throws Exception {
	// if (logger.isDebugEnabled()) {
	// logger
	// .debug("delete(ActionMapping, ActionForm, HttpServletRequest,
	// HttpServletResponse) - start"); //$NON-NLS-1$
	// }
	//
	// Transaction tx = null;
	// String xmlOut = "";
	// MessageResources msgResources = (MessageResources) this.getServlet()
	// .getServletContext().getAttribute(Globals.MESSAGES_KEY);
	// request.setCharacterEncoding("GBK");
	// try {
	// Session session = HibernateSessionFactory.currentSession();
	// String parameter = request.getParameter("parameter");
	// tx = session.beginTransaction();
	// session.createQuery(
	// "delete MapParamTable a where a.parameter=:parameter")
	// .setString("parameter", parameter).executeUpdate();
	// tx.commit();
	// xmlOut = XMLGenerateUtil
	// .XMLGenerate(
	// ErrorCode.SUCCESS,
	// msgResources
	// .getMessage("com.kingstargroup.acton.systemreffer.REFFER_DELETE_SUCCESS"),
	// null);
	// XMLGenerateUtil.XMLSendOut(request, response, xmlOut);
	//
	// } catch (Exception e) {
	// logger
	// .error(
	// "delete(ActionMapping, ActionForm, HttpServletRequest,
	// HttpServletResponse)", e); //$NON-NLS-1$
	//
	// if (tx != null) {
	// tx.rollback();
	// }
	// // server is busy!
	// xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
	// msgResources.getMessage("server.state.SERVER_IS_BUSY"),
	// null);
	// XMLGenerateUtil.XMLSendOut(request, response, xmlOut);
	//
	// } finally {
	// HibernateSessionFactory.closeSession();
	// }
	//
	// if (logger.isDebugEnabled()) {
	// logger
	// .debug("delete(ActionMapping, ActionForm, HttpServletRequest,
	// HttpServletResponse) - end"); //$NON-NLS-1$
	// }
	// return null;
	// }

	// public ActionForward save(ActionMapping mapping, ActionForm form,
	// HttpServletRequest request, HttpServletResponse response)
	// throws Exception {
	// if (logger.isDebugEnabled()) {
	// logger
	// .debug("save(ActionMapping, ActionForm, HttpServletRequest,
	// HttpServletResponse) - start"); //$NON-NLS-1$
	// }
	//
	// Transaction tx = null;
	// String xmlOut = "";
	// MessageResources msgResources = (MessageResources) this.getServlet()
	// .getServletContext().getAttribute(Globals.MESSAGES_KEY);
	// request.setCharacterEncoding("GBK");
	// try {
	// Session session = HibernateSessionFactory.currentSession();
	// tx = session.beginTransaction();
	// String parameter = request.getParameter("parameter");
	// String name = request.getParameter("name");
	// String value = request.getParameter("value");
	// String unit = request.getParameter("unit");
	// String flag = request.getParameter("flag");
	// Query query = session
	// .createQuery("from MapParamTable as a where a.parameter=:parameter");
	// query.setString("parameter", parameter);
	// if (query.iterate().hasNext()) {
	// // user exist
	// xmlOut = XMLGenerateUtil
	// .XMLGenerate(
	// ErrorCode.REFERENCE_EXIST,
	// msgResources
	// .getMessage("com.kingstargroup.acton.systemreffer.REFFER_EXIST"),
	// null);
	// } else {
	// // add reference
	// tx = session.beginTransaction();
	//
	// MapParamTable mapParamTable = new MapParamTable();
	// mapParamTable.setParameter(parameter);
	// mapParamTable.setName(name);
	// mapParamTable.setValue(Double.valueOf(value));
	// mapParamTable.setUnit(unit);
	// mapParamTable.setFlag(Short.valueOf(flag));
	// session.save(mapParamTable);
	// tx.commit();
	// xmlOut = XMLGenerateUtil
	// .XMLGenerate(
	// ErrorCode.SUCCESS,
	// msgResources
	// .getMessage("com.kingstargroup.acton.systemreffer.REFFER_ADD_SUCCESS"),
	// null);
	// }
	//
	// XMLGenerateUtil.XMLSendOut(request, response, xmlOut);
	//
	// } catch (Exception e) {
	// logger
	// .error(
	// "save(ActionMapping, ActionForm, HttpServletRequest,
	// HttpServletResponse)", e); //$NON-NLS-1$
	//
	// if (tx != null) {
	// tx.rollback();
	// }
	// // server is busy!
	// xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
	// msgResources.getMessage("server.state.SERVER_IS_BUSY"),
	// null);
	// XMLGenerateUtil.XMLSendOut(request, response, xmlOut);
	//
	// } finally {
	// HibernateSessionFactory.closeSession();
	// }
	//
	// if (logger.isDebugEnabled()) {
	// logger
	// .debug("save(ActionMapping, ActionForm, HttpServletRequest,
	// HttpServletResponse) - end"); //$NON-NLS-1$
	// }
	// return null;
	// }

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
			String value = request.getParameter("value");
			String unit = request.getParameter("unit");
			String flag = request.getParameter("flag");
			Query query = session
					.createQuery("from MapParamTable as a where a.parameter=:parameter");
			query.setString("parameter", parameter);
			List list = query.list();
			Iterator iter = list.iterator();
			if (iter.hasNext()) {
				MapParamTable mapParamTable = (MapParamTable) iter.next();
				mapParamTable.setName(name);
				mapParamTable.setValue(Double.valueOf(value));
				mapParamTable.setUnit(unit);
				mapParamTable.setFlag(Short.valueOf(flag));
				session.update(mapParamTable);
			}
			tx.commit();
			xmlOut = XMLGenerateUtil
					.XMLGenerate(
							ErrorCode.SUCCESS,
							msgResources
									.getMessage("com.kingstargroup.acton.systemreffer.REFFER_RESET_SUCCESS"),
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

}
