package com.kingstargroup.action.search;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name:CheckAbnormalDeviceHistoyAction.java
 * Description: 异常设备历史信息查询
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期     操作者    操作内容简述
 * 创建  				2005-10-09    何林青   在异常设备信息表里查询相关信息返回
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
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

public class CheckAbnormalDeviceHistoyAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CheckAbnormalDeviceHistoyAction.class);

	public ActionForward List(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		request.setCharacterEncoding("GBK");
		String deviceID = request.getParameter("DeviceID");
		String fatherDeviceID = request.getParameter("FatherDeviceID");
		String contactName = request.getParameter("ContactName");
		String startTime = request.getParameter("StartTime");
		String endTime = request.getParameter("EndTime");
		String errorReason = request.getParameter("ErrorReason");
		String deviceType = request.getParameter("DeviceType");
		String lastFlag = request.getParameter("lastanalysis");
		String startCount = request.getParameter("StartCount");

		StringBuffer sqlBuff = new StringBuffer();
		sqlBuff.append("from MapDeviceTable as device where 1=1 ");
		if (!"".equals(deviceID) && null != deviceID) {
			sqlBuff.append(" and device.devphy999Id = :deviceID ");
		}

		if (!"".equals(fatherDeviceID) && null != fatherDeviceID) {
			sqlBuff.append(" and device.fdevphyId = :fatherDeviceID ");

		}

		if (!"".equals(contactName) && null != contactName) {
			sqlBuff.append(" and device.contactName like :contactName ");
		}

		if (!"".equals(deviceType) && null != deviceType) {
			sqlBuff.append(" and device.deviceType = :deviceType ");
		}

		if (!"".equals(lastFlag) && null != lastFlag) {
			if ("1".equals(lastFlag)) {
				// ToDo:checked----to get the last version of result
				sqlBuff.append(" and device.id.analysisTime >= :startTime ");
				sqlBuff.append(" and device.id.analysisTime <= :endTime ");
			} else {
				// ToDo:unchecked
				if (!"".equals(startTime) && null != startTime) {
					sqlBuff
							.append(" and device.id.analysisTime >= :startTime ");
				}

				if (!"".equals(endTime) && null != endTime) {
					sqlBuff.append(" and device.id.analysisTime <= :endTime ");
				}
			}
		}

		if (!"".equals(errorReason) && null != errorReason
				&& !"-".equals(errorReason)) {
			sqlBuff.append(" and device.errorReason = :errorReason ");
		}

		sqlBuff
				.append("order by device.id.analysisTime desc, device.devphy999Id");

		try {
			// MessageResources msgResources = (MessageResources) this
			// .getServlet().getServletContext().getAttribute(
			// Globals.MESSAGES_KEY);
			Session session = HibernateSessionFactory.currentSession();
			Query queryTime = session
					.createQuery("select a.value from MapParamTable a,MapSysDictionary b where a.parameter=b.dictCode and b.id.dictNo=:dictNo and b.id.dictValue=:dictValue");
			if (!"".equals(errorReason) && null != errorReason
					&& !"-".equals(errorReason)) {
				queryTime.setInteger("dictNo", 2);
				queryTime.setString("dictValue", errorReason);
			} else {
				queryTime.setInteger("dictNo", 0);
				queryTime.setString("dictValue", "0");
			}
			List listTime = queryTime.list();
			String dateTime = DateUtil.getNow();
			int intevalTime = 0;
			if (listTime.size() > 0) {
				if (errorReason.startsWith("10")) {
					intevalTime = (int) (Float.parseFloat(listTime.get(0)
							.toString()) * 60 * -1);
				} else {
					intevalTime = (int) (Float.parseFloat(listTime.get(0)
							.toString()) * 60 * 60 * -1);
				}

			} else {
				intevalTime = -10 * 60;
			}

			String xmlOut = "";
			Query query = session.createQuery(sqlBuff.toString());
			if (!"".equals(deviceID) && null != deviceID) {
				query.setString("deviceID", deviceID);
			}

			if (!"".equals(fatherDeviceID) && null != fatherDeviceID) {
				query.setString("fatherDeviceID", fatherDeviceID);

			}

			if (!"".equals(contactName) && null != contactName) {
				contactName = "%" + contactName + "%";
				query.setString("contactName", contactName);
			}

			if (!"".equals(deviceType) && null != deviceType
					&& !"-".equals(deviceType)) {
				query.setString("deviceType", deviceType);

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

			if (!"".equals(errorReason) && null != errorReason
					&& !"-".equals(errorReason)) {
				query.setInteger("errorReason", Integer.parseInt(errorReason));
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
		} finally {
			HibernateSessionFactory.closeSession();
		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

	public ActionForward itemList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";

		try {
			xmlOut = XMLGenerateUtil.XMLGenerate("0000", "0", null);
			xmlOut = XMLGenerateUtil.deviceXMLGenerate(xmlOut);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {
			logger
					.error(
							"itemList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
			// server is busy!
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
					msgResources.getMessage("server.state.SERVER_IS_BUSY"),
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		}

		if (logger.isDebugEnabled()) {
			logger
					.debug("itemList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - end"); //$NON-NLS-1$
		}
		return null;
	}

	public ActionForward deviceList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		String xmlOut = "";

		try {
			Session session = HibernateSessionFactory.currentSession();
			Query query = session
					.createQuery("select new com.kingstargroup.form.DeviceResult(a.id.dictValue,a.dictCaption) from TPifDictionary a where a.id.dictNo=47");
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
