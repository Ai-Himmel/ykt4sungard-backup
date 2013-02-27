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
import com.kingstargroup.business.util.ParaUtil;
import com.kingstargroup.commons.BaseAction;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapFathersetsTable;
import com.kingstargroup.form.MapLinesTable;
import com.kingstargroup.form.MapSetsTable;
import com.kingstargroup.form.MapFatherLine;
import com.kingstargroup.form.TDevice;
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
			logger
					.info("×××××××××××××××开始重新保存所有GIS信息！××××××××××××××××××××××××");
		}

		Transaction tx = null;
		String xmlOut = "";
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		request.setCharacterEncoding("GBK");
		String deviceCount = request.getParameter("DC");
		String deviceLineCount = request.getParameter("DLC");
		String fatherDeviceCount = request.getParameter("FDC");
		String fatherLineCount = request.getParameter("FLC");

		try {
			Session session = HibernateSessionFactory.currentSession();
			tx = session.beginTransaction();
			int i = 1;
			long tempId = 1;
			int count_D = Integer.parseInt(deviceCount);
			session.createQuery("delete MapSetsTable").executeUpdate();
			String devicedevID ="";
//			String deviceID = "";
//			String deviceName = "";
			String deviceFatherID = "";
//			String deviceType = "";
//			String deviceStatus = "";
			String deviceCoordX = "";
			String deviceCoordY = "";
			String deviceFeature = "";
			for (i = 1; i <= count_D; i++) {
				// 子节点设备信息
				if (!"".equals(request.getParameter("DID" + i))) {
					MapSetsTable mapSetsTable = new MapSetsTable();
					devicedevID = request.getParameter("DID" + i);
//					deviceID = request.getParameter("DeviceID" + i);
					//deviceName = request.getParameter("DeviceName" + i);
//					deviceFatherID = request.getParameter("DFID" + i);
					//deviceType = request.getParameter("DeviceType" + i);
					//deviceStatus = request.getParameter("DeviceStatus" + i);
					
					deviceCoordX = request.getParameter("DX" + i);
					deviceCoordY = request.getParameter("DY" + i);
					deviceFeature = request.getParameter("DF" + i);
					
					TDevice device = null;
					TDevice fdevice = null;
					try {
						device =  (TDevice)session.get(TDevice.class, Long.valueOf(devicedevID));;
						fdevice = (TDevice)session.get(TDevice.class, new Long(device.getFdeviceid()));;
					} catch (Exception e) {
						// TODO: handle exception
						e.printStackTrace();
					}
					if(device==null){
						System.out.println("null device found deviceid=["+devicedevID+"] DFID=["+deviceFatherID+"]");
						continue;
					}
					mapSetsTable.setId(tempId);
					mapSetsTable.setDevid(Long.parseLong(devicedevID));
					mapSetsTable.setSetsid(device.getDevphyid());
					mapSetsTable.setSetname(device.getDevicename());
					mapSetsTable.setFatherid(fdevice.getDevphyid());
					mapSetsTable.setSettype(device.getDevtypecode());
					mapSetsTable.setSetstatus(Long.parseLong("0"));
					mapSetsTable.setXcoor(Double.parseDouble(deviceCoordX));
					mapSetsTable.setYcoor(Double.parseDouble(deviceCoordY));
					mapSetsTable.setFeature(deviceFeature);
					System.out.println(devicedevID);
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
				startPoINTEGERID = request.getParameter("SP" + i);
				endPoINTEGERID = request.getParameter("EP" + i);
				if (!"".equals(startPoINTEGERID) && !"".equals(endPoINTEGERID)) {
					MapLinesTable mapLinesTable = new MapLinesTable();
					lineWidth = request.getParameter("LW" + 1);
					lineColor = request.getParameter("LC" + 1);
					lineStyle = request.getParameter("LS" + 1);
					mapLinesTable.setId(tempId);
					mapLinesTable.setPoint1(startPoINTEGERID);
					mapLinesTable.setPoint2(endPoINTEGERID);
					if (Short.parseShort(lineWidth) > 20) {
						mapLinesTable.setLinetype(Long.parseLong("7"));
					} else {
						mapLinesTable.setLinetype(Long.parseLong(lineWidth));
					}
					mapLinesTable.setLinecolor(Long.parseLong(lineColor));
					if (null != lineStyle && !"".equals(lineStyle)) {
						mapLinesTable.setLinestyle(Long.parseLong(lineStyle));
					} else {
						mapLinesTable.setLinestyle(Long.parseLong("1"));
					}
					mapLinesTable.setLinestatus(Long.parseLong("1"));
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
				fatherSetID = request.getParameter("FID" + i);
				if (null != fatherSetID && !"".equals(fatherSetID)) {
					MapFathersetsTable mapFathersetsTable = new MapFathersetsTable();
					fatherSetName = request.getParameter("FSN" + i);
					fatherOprSys = request.getParameter("FOS" + i);
					fatherSetStatus = request.getParameter("FSS"
							+ i);
					fatherSetIP = request.getParameter("FSIP" + i);
					fatherHostName = request.getParameter("FHN" + i);

					fatherArea = request.getParameter("FA" + i);
					fatherSetMAC = request.getParameter("FSMAC" + i);
					fatherSetCoordX = request.getParameter("FSX"
							+ i);
					fatherSetCoordY = request.getParameter("FSY"
							+ i);
					fatherSetFeature = request.getParameter("FSF"
							+ i);
					mapFathersetsTable.setId(tempId);
					mapFathersetsTable.setSystemid(fatherSetID);
					mapFathersetsTable.setOperationsystem(fatherOprSys);
					mapFathersetsTable.setSystemname(fatherSetName);
					mapFathersetsTable.setStatus(Long.parseLong("0"));
					mapFathersetsTable.setIp(fatherSetIP);
					mapFathersetsTable.setHostname(fatherHostName);
					if (null != fatherArea && !"".equals(fatherArea)) {
						mapFathersetsTable.setArea(fatherArea);
					} else {
						mapFathersetsTable.setArea("2");
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
				startSetID = request.getParameter("SSID" + i);
				endSetID = request.getParameter("ESID" + i);
				if (!"".equals(startSetID) && !"".equals(endSetID)) {
					MapFatherLine mapFatherLine = new MapFatherLine();
					startSetLayer = request.getParameter("SSL" + i);
					endSetLayer = request.getParameter("ESL" + i);
					setLineWidth = request.getParameter("SLW" + i);
					setLineColor = request.getParameter("SLC" + i);
					setLineStyle = request.getParameter("SLS" + i);
					mapFatherLine.setId(tempId);
					mapFatherLine.setSpoint(startSetID);
					mapFatherLine.setEpoint(endSetID);
					mapFatherLine.setSplayer(Long.parseLong(startSetLayer));
					mapFatherLine.setEplayer(Long.parseLong(endSetLayer));
					if (Short.parseShort(setLineWidth) > 20) {
						mapFatherLine.setLinetype(Long.parseLong("7"));
					} else {
						mapFatherLine.setLinetype(Long.parseLong(setLineWidth));
					}
					mapFatherLine.setLinecolor(Long.parseLong(setLineColor));
					if (null != setLineStyle && !"".equals(setLineStyle)) {
						mapFatherLine.setLinestyle(Long.parseLong(setLineStyle));
					} else {
						mapFatherLine.setLinestyle(Long.parseLong("1"));
					}

					mapFatherLine.setLinestatus(Long.parseLong("1"));
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
			logger.error("保存GIS信息时出现一下异常：", e); //$NON-NLS-1$
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

		if (logger.isInfoEnabled()) {
			logger
					.info("*********************保存所有GIS信息成功！*************************");
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

			Query query = session
					.createQuery("from MapSetsTable sets Order by sets.id");

			List list = query.list();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
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

	public ActionForward setLineList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		String xmlOut = "";
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		try {

			Session session = HibernateSessionFactory.currentSession();

			Query query = session
					.createQuery("from MapLinesTable lines Order by lines.id");

			List list = query.list();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {
			logger
					.error(
							"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

			// server is busy!
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
					msgResources.getMessage("server.state.SERVER_IS_BUSY"),
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {
			logger
					.error(
							"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

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
		String xmlOut = "";
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		try {

			Session session = HibernateSessionFactory.currentSession();

			Query query = session
					.createQuery("from MapFathersetsTable fathersets Order by fathersets.id");
			List list = query.list();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {
			logger
					.error(
							"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

			// server is busy!
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
					msgResources.getMessage("server.state.SERVER_IS_BUSY"),
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {
			logger
					.error(
							"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

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

		String xmlOut = "";
		MessageResources msgResources = (MessageResources) this.getServlet()
				.getServletContext().getAttribute(Globals.MESSAGES_KEY);
		try {

			Session session = HibernateSessionFactory.currentSession();

			Query query = session
					.createQuery("from MapFatherLine line order by line.id");

			List list = query.list();
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
					.valueOf(list.size()), list);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (HibernateException e) {
			logger
					.error(
							"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

			// server is busy!
			xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SERVER_IS_BUSY,
					msgResources.getMessage("server.state.SERVER_IS_BUSY"),
					null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

		} catch (Exception e) {
			logger
					.error(
							"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

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
