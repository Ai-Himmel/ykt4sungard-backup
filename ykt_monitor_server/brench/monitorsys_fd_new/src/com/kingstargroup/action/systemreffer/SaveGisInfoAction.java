package com.kingstargroup.action.systemreffer;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: SaveGisInfoAction.java
 * Description: 2.1.10 GIS数据保存功能
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期     操作者    操作内容简述
 * 创建  				2005-10-11   何林青    GIS数据保存
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

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
import com.kingstargroup.form.MapFatherLine;
import com.kingstargroup.form.MapFathersetsTable;
import com.kingstargroup.form.MapLinesTable;
import com.kingstargroup.form.MapSetsTable;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.XMLGenerateUtil;

public class SaveGisInfoAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(SaveGisInfoAction.class);

	public ActionForward save(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isInfoEnabled()) {
			logger.info("×××××××××××××××开始重新保存所有GIS信息！××××××××××××××××××××××××");
		}

		Transaction tx = null;
		String xmlOut = "";
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		request.setCharacterEncoding("GBK");
		String deviceCount = request.getParameter("DeviceCount");
		String deviceLineCount = request.getParameter("DeviceLineCount");
		String fatherDeviceCount = request.getParameter("FatherDeviceCount");
		String fatherLineCount = request.getParameter("FatherLineCount");

		try {
			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();
			int i = 1;
			int tempId = 1;
			int count_D = Integer.parseInt(deviceCount);
			session.createQuery("delete MapSetsTable").executeUpdate();
			String deviceID = "";
			String deviceName = "";
			String deviceFatherID = "";
			String deviceType = "";
			String deviceStatus = "";
			String deviceCoordX = "";
			String deviceCoordY = "";
			String deviceFeature = "";
			for (i = 1; i <= count_D; i++) {
				// 子节点设备信息
				if (!"".equals(request.getParameter("DeviceID" + i))) {
					MapSetsTable mapSetsTable = new MapSetsTable();
					deviceID = request.getParameter("DeviceID" + i);
					deviceName = request.getParameter("DeviceName" + i);
					deviceFatherID = request.getParameter("DeviceFatherID" + i);
					deviceType = request.getParameter("DeviceType" + i);
					deviceStatus = request.getParameter("DeviceStatus" + i);
					deviceCoordX = request.getParameter("DeviceCoordX" + i);
					deviceCoordY = request.getParameter("DeviceCoordY" + i);
					deviceFeature = request.getParameter("DeviceFeature" + i);
					mapSetsTable.setId(new Integer(tempId));
					mapSetsTable.setSetsid(deviceID);
					mapSetsTable.setSetname(deviceName);
					mapSetsTable.setFatherid(deviceFatherID);
					mapSetsTable.setSettype(deviceType);
					mapSetsTable.setSetstatus(Short.valueOf("0"));
					mapSetsTable.setXcoor(Double.valueOf(deviceCoordX));
					mapSetsTable.setYcoor(Double.valueOf(deviceCoordY));
					mapSetsTable.setFeature(deviceFeature);
					session.save(mapSetsTable);
					tempId++;
				}
			}

			int count_DL = Integer.parseInt(deviceLineCount);
			session.createQuery("delete MapLinesTable").executeUpdate();
			String startPoINTEGERID = "";
			String endPoINTEGERID = "";
			String lineWidth = "";
			String lineColor = "";
			String lineStyle = "";
			tempId = 1;
			for (i = 1; i <= count_DL; i++) {
				// 子节点设备线信息
				startPoINTEGERID = request.getParameter("StartPoINTEGERID" + i);
				endPoINTEGERID = request.getParameter("EndPoINTEGERID" + i);
				if (!"".equals(startPoINTEGERID) && !"".equals(endPoINTEGERID)) {
					MapLinesTable mapLinesTable = new MapLinesTable();
					lineWidth = request.getParameter("LineWidth" + i);
					lineColor = request.getParameter("LineColor" + i);
					lineStyle = request.getParameter("LineStyle" + i);
					mapLinesTable.setId(new Integer(tempId));
					mapLinesTable.setPoint1(startPoINTEGERID);
					mapLinesTable.setPoint2(endPoINTEGERID);
					if (Short.parseShort(lineWidth) > 20) {
						mapLinesTable.setLinetype(Short.valueOf("7"));
					} else {
						mapLinesTable.setLinetype(Short.valueOf(lineWidth));
					}
					mapLinesTable.setLinecolor(Long.valueOf(lineColor));
					if (null != lineStyle && !"".equals(lineStyle)) {
						mapLinesTable.setLinestyle(Integer.valueOf(lineStyle));
					} else {
						mapLinesTable.setLinestyle(Integer.valueOf("1"));
					}
					mapLinesTable.setLinestatus(Short.valueOf("1"));
					session.save(mapLinesTable);
					tempId++;
				}
			}

			int count_F = Integer.parseInt(fatherDeviceCount);
			session.createQuery("delete MapFathersetsTable").executeUpdate();
			String fatherSetID = "";
			String fatherSetName = "";
			String fatherOprSys = "";
			String fatherSetStatus = "";
			String fatherSetIP = "";
			String fatherHostName = "";
			String fatherArea = "";
			String fatherSetMAC = "";
			String fatherSetCoordX = "";
			String fatherSetCoordY = "";
			String fatherSetFeature = "";
			tempId = 1;
			for (i = 1; i <= count_F; i++) {
				// 父节点设备信息
				fatherSetID = request.getParameter("FatherSetID" + i);
				if (null != fatherSetID && !"".equals(fatherSetID)) {
					MapFathersetsTable mapFathersetsTable = new MapFathersetsTable();
					fatherSetName = request.getParameter("FatherSetName" + i);
					fatherOprSys = request.getParameter("FatherOprSys" + i);
					fatherSetStatus = request.getParameter("FatherSetStatus"
							+ i);
					fatherSetIP = request.getParameter("FatherSetIP" + i);
					fatherHostName = request.getParameter("FatherHostName" + i);

					fatherArea = request.getParameter("FatherArea" + i);
					fatherSetMAC = request.getParameter("FatherSetMAC" + i);
					fatherSetCoordX = request.getParameter("FatherSetCoordX"
							+ i);
					fatherSetCoordY = request.getParameter("FatherSetCoordY"
							+ i);
					fatherSetFeature = request.getParameter("FatherSetFeature"
							+ i);
					mapFathersetsTable.setId(new Integer(tempId));
					mapFathersetsTable.setSystemid(fatherSetID);
					mapFathersetsTable.setOperationsystem(fatherOprSys);
					mapFathersetsTable.setSystemname(fatherSetName);
					mapFathersetsTable.setStatus(Short.parseShort("0"));
					mapFathersetsTable.setIp(fatherSetIP);
					mapFathersetsTable.setHostname(fatherHostName);
					if (null != fatherArea && !"".equals(fatherArea)) {
						mapFathersetsTable.setArea(Integer.valueOf(fatherArea));
					} else {
						mapFathersetsTable.setArea(Integer.valueOf("2"));
					}
					mapFathersetsTable.setMacaddress(fatherSetMAC);
					mapFathersetsTable.setCoordx(Double
							.parseDouble(fatherSetCoordX));
					mapFathersetsTable.setCoordy(Double
							.parseDouble(fatherSetCoordY));
					mapFathersetsTable.setFeature(fatherSetFeature);
					session.save(mapFathersetsTable);
					tempId++;
				}
			}

			int count_FL = Integer.parseInt(fatherLineCount);
			session.createQuery("delete MapFatherLine").executeUpdate();
			String startSetID = "";
			String endSetID = "";
			String startSetLayer = "";
			String endSetLayer = "";
			String setLineWidth = "";
			String setLineColor = "";
			String setLineStyle = "";
			tempId = 1;
			for (i = 1; i <= count_FL; i++) {
				// 父节点设备线信息
				startSetID = request.getParameter("StartSetID" + i);
				endSetID = request.getParameter("EndSetID" + i);
				if (!"".equals(startSetID) && !"".equals(endSetID)) {
					MapFatherLine mapFatherLine = new MapFatherLine();
					startSetLayer = request.getParameter("StartSetLayer" + i);
					endSetLayer = request.getParameter("EndSetLayer" + i);
					setLineWidth = request.getParameter("SetLineWidth" + i);
					setLineColor = request.getParameter("SetLineColor" + i);
					setLineStyle = request.getParameter("SetLineStyle" + i);
					mapFatherLine.setId(new Integer(tempId));
					mapFatherLine.setSpoint(startSetID);
					mapFatherLine.setEpoint(endSetID);
					mapFatherLine.setSplayer(Integer.valueOf(startSetLayer));
					mapFatherLine.setEplayer(Integer.valueOf(endSetLayer));
					if (Short.parseShort(setLineWidth) > 20) {
						mapFatherLine.setLinetype(Short.valueOf("7"));
					} else {
						mapFatherLine.setLinetype(Short.valueOf(setLineWidth));
					}
					mapFatherLine.setLinecolor(Long.valueOf(setLineColor));
					if (null != setLineStyle && !"".equals(setLineStyle)) {
						mapFatherLine.setLinestyle(Integer
								.valueOf(setLineStyle));
					} else {
						mapFatherLine.setLinestyle(Integer.valueOf("1"));
					}

					mapFatherLine.setLinestatus(Short.valueOf("1"));
					session.save(mapFatherLine);
					tempId++;
				}
			}

			tx.commit();
			xmlOut = XMLGenerateUtil
					.XMLGenerate(
							ErrorCode.SUCCESS,
							msgResources
									.getMessage("com.kingstargroup.acton.systemreffer.GIS_INFO_SAVE_SUCCESS"),
							null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {			
			logger.error("保存GIS信息时出现一下异常：", e); //$NON-NLS-1$
			if (tx != null) {
				tx.rollback();
			}
			// server is busy!
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
					msgResources.getMessage("server.state.SERVER_IS_BUSY"),
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		}catch (Exception e) {
			logger.error("保存GIS信息时出现一下异常：", e); //$NON-NLS-1$
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

		if (logger.isInfoEnabled()) {
			logger.info("*********************保存所有GIS信息成功！*************************");
		}

		return null;
	}

	public ActionForward setList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		Transaction tx = null;
		String xmlOut = "";
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		try {

			Session session = HibernateSessionFactory.currentSession();

			tx = session.beginTransaction();
			Query query = session
					.createQuery("from MapSetsTable as sets Order by sets.id");
			tx.commit();
			List list = query.list();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {
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

		return null;
	}

	public ActionForward setLineList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		Transaction tx = null;
		String xmlOut = "";
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		try {

			Session session = HibernateSessionFactory.currentSession();

			tx = session.beginTransaction();
			Query query = session
					.createQuery("from MapLinesTable as lines Order by lines.id");
			tx.commit();
			List list = query.list();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {
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

		return null;
	}

	public ActionForward fatherSetList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		Transaction tx = null;
		String xmlOut = "";
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		try {

			Session session = HibernateSessionFactory.currentSession();

			tx = session.beginTransaction();
			Query query = session
					.createQuery("from MapFathersetsTable as fathersets Order by fathersets.id");
			tx.commit();
			List list = query.list();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {
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

		return null;
	}

	public ActionForward fatherLineList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		Transaction tx = null;
		String xmlOut = "";
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		try {

			Session session = HibernateSessionFactory.currentSession();

			tx = session.beginTransaction();
			Query query = session
					.createQuery("from MapFatherLine as line order by line.id");
			tx.commit();
			List list = query.list();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {
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

		return null;
	}

}
