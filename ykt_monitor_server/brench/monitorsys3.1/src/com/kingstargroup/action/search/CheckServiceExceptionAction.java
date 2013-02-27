package com.kingstargroup.action.search;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name:CheckAbnormalDeviceHistoyAction.java
 * Description: 异常服务历史信息查询
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期     操作者    操作内容简述
 * 创建  				2006-12-13    何林青   在异常服务信息表里查询相关信息返回
 * <p>
 *
 * @author      何林青
 * @version     2.0
 * @since       2.0
 */

import java.util.List;

import org.apache.log4j.Logger;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.Globals;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.util.MessageResources;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.action.user.ErrorCode;
import com.kingstargroup.commons.BaseAction;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.XMLGenerateUtil;

public class CheckServiceExceptionAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CheckServiceExceptionAction.class);

	public ActionForward List(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		request.setCharacterEncoding("GBK");
		String serverId = request.getParameter("ServerId");
		String serviceType = request.getParameter("ServiceType");
		String contactName = request.getParameter("ContactName");
		String startTime = request.getParameter("StartTime");
		String endTime = request.getParameter("EndTime");
		String errorCode = request.getParameter("ErrorCode");
		String lastFlag = request.getParameter("lastanalysis");
		String startCount = request.getParameter("StartCount");

		StringBuffer sqlBuff = new StringBuffer();
		sqlBuff
				.append("select new com.kingstargroup.form.ServiceExceptionResult(a.id.analysistime,a.serverName,a.serviceType,b.serviceName,a.contactname,a.status,a.errorcode) from MapServiceException a,MapServiceTable b,MapFathersetsTable c "
						+ " where a.id.serviceId=b.serviceId and a.serverId=c.id ");
		if (!"".equals(serverId) && null != serverId && !"-".equals(serverId)) {
			sqlBuff.append(" and c.systemid = :serverId ");
		}

		if (!"".equals(serviceType) && null != serviceType && !"-".equals(serviceType)) {
			sqlBuff.append(" and a.serviceType = :serviceType ");

		}

		if (!"".equals(contactName) && null != contactName) {
			sqlBuff.append(" and a.contactname like :contactName ");
		}

		if (!"".equals(lastFlag) && null != lastFlag) {
			if ("1".equals(lastFlag)) {
				// ToDo:checked----to get the last version of result
				sqlBuff.append(" and a.id.analysistime >= :startTime ");
				sqlBuff.append(" and a.id.analysistime <= :endTime ");
			} else {
				// ToDo:unchecked
				if (!"".equals(startTime) && null != startTime) {
					sqlBuff
							.append(" and a.id.analysistime >= :startTime ");
				}

				if (!"".equals(endTime) && null != endTime) {
					sqlBuff.append(" and a.id.analysistime <= :endTime ");
				}
			}
		}

		if (!"".equals(errorCode) && null != errorCode
				&& !"-".equals(errorCode)) {
			sqlBuff.append(" and a.errorcode = :errorCode ");
		}

		sqlBuff.append("order by a.id.analysistime desc, a.serverId");

		try {
			// MessageResources msgResources = (MessageResources) this
			// .getServlet().getServletContext().getAttribute(
			// Globals.MESSAGES_KEY);
			Session session = HibernateSessionFactory.currentSession();
			Query queryTime = session
					.createQuery("select a.value,a.unit from MapParamTable a,MapSysDictionary b where a.parameter=b.dictCode and b.id.dictNo=:dictNo and b.id.dictValue=:dictValue");
			if (!"".equals(errorCode) && null != errorCode
					&& !"-".equals(errorCode)) {
				queryTime.setInteger("dictNo", 2);
				queryTime.setString("dictValue", errorCode);
			} else {
				queryTime.setInteger("dictNo", 0);
				queryTime.setString("dictValue", "0");
			}
			List listTime = queryTime.list();
			String dateTime = DateUtil.getNow();
			int intevalTime = 0;
			if (listTime.size() > 0) {
				Object a[] = (Object[])listTime.get(0);
				String unit = (String) a[1];
				Double time = (Double) a[0];
				if (unit.equals("分钟")) {
					intevalTime = (int) (time.doubleValue() * 60 * -1);
				} else if (unit.equals("小时")) {
					intevalTime = (int) (time.doubleValue() * 60 * 60 * -1);
				}

			} else {
				intevalTime = -10 * 60;
			}

			String xmlOut = "";
			Query query = session.createQuery(sqlBuff.toString());
			if (!"".equals(serverId) && null != serverId && !"-".equals(serverId)) {
				query.setString("serverId", serverId);
			}

			if (!"".equals(serviceType) && null != serviceType && !"-".equals(serviceType)) {
				query.setString("serviceType", serviceType);

			}

			if (!"".equals(contactName) && null != contactName) {
				contactName = "%" + contactName + "%";
				query.setString("contactName", contactName);
			}

			if (!"".equals(lastFlag) && null != lastFlag) {
				if ("1".equals(lastFlag)) {
					// ToDo:checked----to get the last version of result
					query.setString("startTime", DateUtil.getNewTime(dateTime,
							intevalTime));
					query.setString("endTime", dateTime);
				} else {
					// ToDo:unchecked
					if (!"".equals(startTime) && null != startTime) {
						query.setString("startTime", startTime);
					}
					if (!"".equals(endTime) && null != endTime) {
						query.setString("endTime", dateTime);
					}
				}
			}

			if (!"".equals(errorCode) && null != errorCode
					&& !"-".equals(errorCode)) {
				query.setInteger("errorCode", Integer.parseInt(errorCode));
			}

			if ("".equals(startCount) || null == startCount) {
				query.setFirstResult(0);
				query.setMaxResults(200);
			} else {
				query.setFirstResult(Integer.parseInt(startCount));
				query.setMaxResults(200);
			}
			List list = query.list();
			// user exist
			if (200 == list.size()) {
				xmlOut = XMLGenerateUtil.XMLGenerateWithFlag(ErrorCode.SUCCESS,
						String.valueOf(list.size()), list, "1");
			} else {
				xmlOut = XMLGenerateUtil.XMLGenerateWithFlag(ErrorCode.SUCCESS,
						String.valueOf(list.size()), list, "0");
			}

			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {
			logger
					.error(
							"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

			e.printStackTrace();
		}catch(Exception e1){
			logger
			.error(
					"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e1); //$NON-NLS-1$

			e1.printStackTrace();
			
		} finally {
			HibernateSessionFactory.closeSession();
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

	/**
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return 服务类型列表
	 * @throws Exception
	 */
	public ActionForward ServiceTypeList(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";

		try {
			Session session = HibernateSessionFactory.currentSession();
			Query query = session
					.createQuery("select new com.kingstargroup.form.DeviceResult(a.dictCode,a.dictCaption) from MapSysDictionary a where a.id.dictNo=3 ");
			List list = query.list();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {
			logger
					.error(
							"deviceList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
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

	/**
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return 服务器列表
	 * @throws Exception
	 */
	public ActionForward ServerList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";

		try {
			Session session = HibernateSessionFactory.currentSession();
			Query query = session
					.createQuery("select new com.kingstargroup.form.DeviceResult(a.systemid,a.systemname) from MapFathersetsTable a  ");
			List list = query.list();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {
			logger
					.error(
							"deviceList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
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

	/**
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return 异常原因
	 * @throws Exception
	 */
	public ActionForward ErrorList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";

		try {
			Session session = HibernateSessionFactory.currentSession();
			Query query = session
					.createQuery("select new com.kingstargroup.form.DeviceResult(a.id.dictValue,a.dictCaption) from MapSysDictionary a where a.id.dictNo=2 and a.dictCode='ServiceExceptionCycle'");
			List list = query.list();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {
			logger
					.error(
							"deviceList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
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
