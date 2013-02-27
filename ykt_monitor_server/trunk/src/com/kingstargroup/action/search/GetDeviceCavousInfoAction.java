package com.kingstargroup.action.search;

import java.util.ArrayList;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.action.user.ErrorCode;
import com.kingstargroup.commons.BaseAction;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapDeviceTable;
import com.kingstargroup.form.MapParamTable;
import com.kingstargroup.form.MapStateDic;
import com.kingstargroup.form.PositioResult;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.XMLGenerateUtil;

public class GetDeviceCavousInfoAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(GetDeviceCavousInfoAction.class);

//	public ActionForward getDeviceCavousInfo(ActionMapping mapping,
//			ActionForm form, HttpServletRequest request,
//			HttpServletResponse response) {
//		HttpSession httpSession = request.getSession();
//		// 判断信息
//		if (httpSession.getAttribute("userLogin") != null) {
//			try {
//				request.setCharacterEncoding("GBK");
//				String deviceID = request.getParameter("DeviceID");
//				String startTime = request.getParameter("StartTime");
//				String endTime = request.getParameter("EndTime");
//				String errorReason = request.getParameter("ErrorReason");
//
//				StringBuffer sqlBuffer = new StringBuffer();
//				Session session = HibernateSessionFactory.currentSession();
//
//				sqlBuffer.append("from MapDeviceTable where devphy999Id='")
//				.append(deviceID)
//				.append("' and errorReason=")
//				.append(errorReason)
//				.append(" and id.analysistime>='")
//				.append(startTime)
//				.append("' and id.analysistime<='")
//				.append(endTime)
//				.append("' order by id.analysistime");
//				String xmlOut = "";
//				Query query = session.createQuery(sqlBuffer.toString());
//				List list = query.list();
//
//				// user exist
//				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
//						.valueOf(list.size()), list);
//
//				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);
//
//			} catch (Exception e) {
//				logger
//						.error(
//								"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$
//
//				e.printStackTrace();
//			} finally {
//				HibernateSessionFactory.closeSession();
//			}
//		}
//		return null;
//	}
	
	public ActionForward getDeviceCavousInfo(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) {
		HttpSession httpSession = request.getSession();
		// 判断信息
		if (httpSession.getAttribute("userLogin") != null) {
			try {
				request.setCharacterEncoding("GBK");
				String deviceID = request.getParameter("DeviceID");
				String startTime = request.getParameter("StartTime");
				String endTime = request.getParameter("EndTime");
				String errorReason = request.getParameter("ErrorReason");
				Session session = HibernateSessionFactory.currentSession();
				Query queryInterval = session.createQuery("from MapParamTable where parameter='HeartInterval'");
				double heartInterval = 0;
				List listInterval = queryInterval.list();
				Iterator iterInterval = listInterval.iterator();
				if(iterInterval.hasNext()){
					MapParamTable mapParamTable = (MapParamTable)iterInterval.next();					
					heartInterval = mapParamTable.getValue();
				}
				
				double dbInterval =  heartInterval*60;
				int intInterval = (int)dbInterval;
				endTime = DateUtil.getMinDateTime(endTime, DateUtil.getNow());
				long interval = DateUtil.getIntervalTime(startTime, endTime);
				double dbvlaue = -interval/heartInterval/60000;
				int maxposition = (int)dbvlaue;
				HashMap posMap = new HashMap();
				for(int i=0;i<=maxposition;i++){
					posMap.put(String.valueOf(i), new PositioResult(DateUtil.getNewTime(startTime, intInterval*i),new Integer(1),new Integer(i),new Integer(0)));					
				}
				
				StringBuffer sqlBuffer = new StringBuffer();
				sqlBuffer.append("from MapDeviceTable where DEVPHYID='")
				.append(deviceID)
				.append("' and errorReason=")
				.append(errorReason)
				.append(" and id.analysistime>='")
				.append(startTime)
				.append("' and id.analysistime<='")
				.append(endTime)
				.append("' order by id.analysistime");
				String xmlOut = "";
				Query query = session.createQuery(sqlBuffer.toString());
				List list = query.list();
				Iterator iter = list.iterator();
				while(iter.hasNext()){
					MapDeviceTable mapDeviceTable = (MapDeviceTable)iter.next();
					String time=mapDeviceTable.getId().getAnalysistime();
					System.out.println(time);
					interval = DateUtil.getIntervalTime(startTime, time);
					dbvlaue = -interval/dbInterval/1000;
					int position = (int)dbvlaue;
//					mapDeviceTable.setSubsystemId(new Integer(position));
					PositioResult positionResult = (PositioResult)posMap.get(String.valueOf(position));
					if(positionResult!=null){
						positionResult.setX(time);
						positionResult.setY(Integer.valueOf("3"));
						positionResult.setPos(new Integer(position));
						positionResult.setFlag(new Integer("0"));
					}
					
					System.out.println(interval+":"+dbvlaue+":"+position);
				}
				// user exist
				List listResult = new ArrayList();
				
				for(int i=0;i<=maxposition;i++){
					listResult.add(posMap.get(String.valueOf(i)));
				}
				
				
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(listResult.size()), listResult);

				XMLGenerateUtil.XMLSendOut(request, response, xmlOut);

			} catch (Exception e) {
				logger
						.error(
								"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

				e.printStackTrace();
			} finally {
				HibernateSessionFactory.closeSession();
			}
		}
		return null;
	}
	
	

	public ActionForward mapDeviceTableErrInfoList(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("errInfoList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		HttpSession httpSession = request.getSession();
		// 判断信息
		if (httpSession.getAttribute("userLogin") != null) {

			try {

				request.setCharacterEncoding("GBK");
				String deviceType = request.getParameter("DeviceType");
				String area = request.getParameter("Area");
				String analysistime = request.getParameter("analysistime");

				StringBuffer sqlBuff = new StringBuffer();
				StringBuffer sqlBuffServer = new StringBuffer();

				sqlBuff
						.append(
								"select new com.kingstargroup.form.ErrInfoDevices")
						.append(
								"(device.id.analysistime,sets.id, device.devphyid, device.devicename, device.devtypecode, ")
						.append("device.contactName, device.errorReason) ")
						.append(
								"from MapDeviceTable device, MapSetsTable sets ")
						.append(
								"where device.id.analysistime>:analysistime and device.devphyid=sets.setsid and (1<>1 ");

				sqlBuffServer
						.append(
								"select new com.kingstargroup.form.ErrInfoDevices")
						.append(
								"(device.id.analysistime,sets.id, device.devphyid, device.devicename, device.devtypecode, ")
						.append("device.contactName, device.errorReason) ")
						.append(
								"from MapDeviceTable device, MapFathersetsTable sets ")
						.append(
								"where device.id.analysistime>:analysistime and device.devphyid=sets.systemid and (1<>1 ");

				// , MapSerialTable serial, MapSeriallostTable seriallost
				// server--999set ---lanprot --pos
				// --multimidia--check---forbbiden
				// handan -- fenglin ---jiangwang---zhangjiang
				if ("1".equals(deviceType.substring(0, 1))) {
					// don't know the server's device Type
					sqlBuff.append(" or device.devtypecode = '").append("0000")
							.append("'");
					sqlBuffServer.append(" or device.devtypecode = '").append(
							"0000").append("'");

				}
				if ("1".equals(deviceType.substring(1, 2))) {
					sqlBuff.append(" or device.devtypecode = '").append("12")
							.append("'");

				}
				if ("1".equals(deviceType.substring(2, 3))) {
					sqlBuff.append(" or device.devtypecode = '").append("5301")
							.append("'");

				}
				if ("1".equals(deviceType.substring(3, 4))) {
					sqlBuff.append(" or device.devtypecode = '").append("0226")
							.append("'");

				}
				if ("1".equals(deviceType.substring(4, 5))) {
					sqlBuff.append(" or device.devtypecode = '").append("0230")
							.append("'");

				}
				if ("1".equals(deviceType.substring(5, 6))) {
					sqlBuff.append(" or device.devtypecode = '").append("0121")
							.append("'");

				}
				sqlBuff.append(") and (1<>1 ");
				sqlBuffServer.append(") and (1<>1 ");
				List listArea = null;
				String tmp = "";
				if ("1".equals(area.substring(0, 1))) {
					listArea = GetAreaCodeTimelyAction.getInstance()
							.returnListAfterCheckTime(1);
					for (int i = 0; i < listArea.size(); i++) {
						tmp = listArea.get(i).toString();
						sqlBuff.append(" or device.area = " + tmp);
						sqlBuffServer.append(" or sets.area = " + tmp);
					}
				}
				if ("1".equals(area.substring(1, 2))) {
					listArea = GetAreaCodeTimelyAction.getInstance()
							.returnListAfterCheckTime(2);
					for (int i = 0; i < listArea.size(); i++) {
						tmp = listArea.get(i).toString();
						sqlBuff.append(" or device.area = " + tmp);
						sqlBuffServer.append(" or sets.area = " + tmp);
					}
				}
				if ("1".equals(area.substring(2, 3))) {
					listArea = GetAreaCodeTimelyAction.getInstance()
							.returnListAfterCheckTime(3);
					for (int i = 0; i < listArea.size(); i++) {
						tmp = listArea.get(i).toString();
						sqlBuff.append(" or device.area = " + tmp);
						sqlBuffServer.append(" or sets.area = " + tmp);
					}
				}
				if ("1".equals(area.substring(3, 4))) {
					listArea = GetAreaCodeTimelyAction.getInstance()
							.returnListAfterCheckTime(4);
					for (int i = 0; i < listArea.size(); i++) {
						tmp = listArea.get(i).toString();
						sqlBuff.append(" or device.area = " + tmp);
						sqlBuffServer.append(" or sets.area = " + tmp);
					}
				}

				sqlBuff.append(") and (1<>1 ");
				sqlBuffServer.append(") and (1<>1 ");

				Session session = HibernateSessionFactory.currentSession();
				Query errCodeQuery = session
						.createQuery("from MapStateDic a where a.errornot=1");
				List errCodeList = errCodeQuery.list();

				Enumeration enumration = request.getParameterNames();
				String name = "";
				String value = "";
				while (enumration.hasMoreElements()) {
					name = (String) enumration.nextElement();
					if (name.startsWith("Item_")) {
						value = request.getParameter(name);
						for (int i = 0; i < errCodeList.size(); i++) {
							MapStateDic mapStateDic = (MapStateDic) errCodeList
									.get(i);
							if (mapStateDic.getTagcode() != null
									&& mapStateDic.getTagcode().equals(
											name.substring(5))) {
								sqlBuff.append("or (device.errorReason ="
										+ "101" + mapStateDic.getErrorcode()
										+ ") ");
								sqlBuff.append("or (device.errorReason ="
										+ "151" + mapStateDic.getErrorcode()
										+ ") ");
								sqlBuffServer
										.append("or (device.errorReason =105) ");
								sqlBuffServer
										.append("or (device.errorReason =155) ");
								break;
							}
						}

						if ("3012".equals(name.substring(5))) {// cpu
							if ("1".equals(value)) {
								sqlBuff
										.append("or (device.errorReason  =102) ");
								sqlBuffServer
										.append("or (device.errorReason =102) ");
								sqlBuff
										.append("or (device.errorReason  =152) ");
								sqlBuffServer
										.append("or (device.errorReason =152) ");
							}

						} else if ("3013".equals(name.substring(5))) {// mem
							if ("1".equals(value)) {
								sqlBuff
										.append("or (device.errorReason  =103) ");
								sqlBuffServer
										.append("or (device.errorReason =103) ");
								sqlBuff
										.append("or (device.errorReason  =153) ");
								sqlBuffServer
										.append("or (device.errorReason =153) ");
							}

						} else if ("3014".equals(name.substring(5))) {// disk
							if ("1".equals(value)) {
								sqlBuff
										.append("or (device.errorReason  =104) ");
								sqlBuffServer
										.append("or (device.errorReason =104) ");
								sqlBuff
										.append("or (device.errorReason  =154) ");
								sqlBuffServer
										.append("or (device.errorReason =154) ");
							}

						} else if ("3005".equals(name.substring(5))) {
							if ("1".equals(value)) {
								sqlBuff.append("or device.errorReason = 11 ");
							}
						} else if ("3007".equals(name.substring(5))) {
							if ("1".equals(value)) {
								sqlBuff.append("or device.errorReason = 12 ");
							}
						}
					}

				}

				sqlBuff.append(") order by sets.fatherid");
				sqlBuffServer.append(") order by sets.systemid");

				String xmlOut = "";
				Query query = session.createQuery(sqlBuff.toString());
				query.setString("analysistime", analysistime);
				List list = query.list();

				Query queryServer = session.createQuery(sqlBuffServer
						.toString());
				queryServer.setString("analysistime", analysistime);
				List listServer = queryServer.list();

				// user exist
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(list.size()), list);
				xmlOut = XMLGenerateUtil.DeXMLGenerate(xmlOut, listServer);

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
		}
		return null;
	}

	public ActionForward mapServiceExceptionErrInfoList(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("errInfoList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		HttpSession httpSession = request.getSession();
		// 判断信息
		if (httpSession.getAttribute("userLogin") != null) {

			try {

				request.setCharacterEncoding("GBK");
				String deviceType = request.getParameter("DeviceType");
				String area = request.getParameter("Area");
				String analysistime = request.getParameter("analysistime");

				StringBuffer sqlBuffService = new StringBuffer();

				sqlBuffService
						.append(
								"select new com.kingstargroup.form.ErrInfoDevices")
						.append(
								"(serial.id.analysistime,sets.id, sets.systemid, serial.serverName, serial.serviceType, ")
						.append("serial.contactname, serial.errorcode) ")
						.append(
								"from MapServiceException serial, MapFathersetsTable sets ")
						.append(
								"where serial.id.analysistime>:analysistime and serial.serverId=sets.id ")
						.append("and (1<>1 ");

				// , MapSerialTable serial, MapSeriallostTable seriallost
				// server--999set ---lanprot --pos
				// --multimidia--check---forbbiden
				// handan -- fenglin ---jiangwang---zhangjiang
				if ("1".equals(deviceType.substring(0, 1))) {
					// don't know the server's device Type
					sqlBuffService.append(" or serial.serviceType <> '")
							.append("0000").append("'");

				}

				sqlBuffService.append(") and (1<>1 ");

				List listArea = null;
				String tmp = "";
				if ("1".equals(area.substring(0, 1))) {
					listArea = GetAreaCodeTimelyAction.getInstance()
							.returnListAfterCheckTime(1);
					for (int i = 0; i < listArea.size(); i++) {
						tmp = listArea.get(i).toString();
						sqlBuffService.append(" or sets.area = " + tmp);
					}
				}
				if ("1".equals(area.substring(1, 2))) {
					listArea = GetAreaCodeTimelyAction.getInstance()
							.returnListAfterCheckTime(2);
					for (int i = 0; i < listArea.size(); i++) {
						tmp = listArea.get(i).toString();
						sqlBuffService.append(" or sets.area = " + tmp);
					}
				}
				if ("1".equals(area.substring(2, 3))) {
					listArea = GetAreaCodeTimelyAction.getInstance()
							.returnListAfterCheckTime(3);
					for (int i = 0; i < listArea.size(); i++) {
						tmp = listArea.get(i).toString();
						sqlBuffService.append(" or sets.area = " + tmp);
					}
				}
				if ("1".equals(area.substring(3, 4))) {
					listArea = GetAreaCodeTimelyAction.getInstance()
							.returnListAfterCheckTime(4);
					for (int i = 0; i < listArea.size(); i++) {
						tmp = listArea.get(i).toString();
						sqlBuffService.append(" or sets.area = " + tmp);
					}
				}

				sqlBuffService.append(") and (1<>1 ");

				Session session = HibernateSessionFactory.currentSession();

				Enumeration enumration = request.getParameterNames();
				String name = "";
				String value = "";
				while (enumration.hasMoreElements()) {
					name = (String) enumration.nextElement();
					if (name.startsWith("Item_")) {
						value = request.getParameter(name);

						if ("30114".equals(name.substring(5))) {// web
							if ("1".equals(value)) {
								sqlBuffService
										.append("or serial.errorcode = 108 ");
								sqlBuffService
										.append("or serial.errorcode = 158 ");
							}
						} else if ("30115".equals(name.substring(5))) {// db
							if ("1".equals(value)) {
								sqlBuffService
										.append("or serial.errorcode = 109 ");
								sqlBuffService
										.append("or serial.errorcode = 159 ");
							}
						} else if ("30116".equals(name.substring(5))) {// drtp
							if ("1".equals(value)) {
								sqlBuffService
										.append("or serial.errorcode = 110 ");
								sqlBuffService
										.append("or serial.errorcode = 160 ");
							}
						}
					}

				}

				sqlBuffService.append(") order by sets.systemid");

				String xmlOut = "";

				Query queryService = session.createQuery(sqlBuffService
						.toString());
				queryService.setString("analysistime", analysistime);
				List listService = queryService.list();

				// user exist
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(listService.size()), listService);

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
		}
		return null;
	}

	public ActionForward mapSerialexceptTableErrInfoList(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("errInfoList(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		HttpSession httpSession = request.getSession();
		// 判断信息
		if (httpSession.getAttribute("userLogin") != null) {

			try {

				request.setCharacterEncoding("GBK");
				String deviceType = request.getParameter("DeviceType");
				String area = request.getParameter("Area");
				String analysistime = request.getParameter("analysistime");

				StringBuffer sqlBuffer = new StringBuffer();

				sqlBuffer
						.append(
								"select new com.kingstargroup.form.ErrInfoDevices")
						.append(
								"(serial.id.analysistime,sets.id, serial.id.devphyid, sets.setname, sets.settype, ")
						.append("serial.contactname, serial.abnormaltype) ")
						.append(
								"from MapSerialexceptTable serial, MapSetsTable sets, TDevice device ")
						.append(
								"where serial.id.analysistime>:analysistime and serial.id.devphyid=sets.setsid and sets.setsid=device.devphyid ")
						.append("and not device.stateId=5 and (1<>1 ");
				// , MapSerialTable serial, MapSeriallostTable seriallost
				// server--999set ---lanprot --pos
				// --multimidia--check---forbbiden
				// handan -- fenglin ---jiangwang---zhangjiang
				if ("1".equals(deviceType.substring(0, 1))) {
					// don't know the server's device Type
					sqlBuffer.append(" or sets.settype = '").append("0000")
							.append("'");
				}
				if ("1".equals(deviceType.substring(1, 2))) {
					sqlBuffer.append(" or sets.settype = '").append("12")
							.append("'");
				}
				if ("1".equals(deviceType.substring(2, 3))) {
					sqlBuffer.append(" or sets.settype = '").append("5301")
							.append("'");
				}
				if ("1".equals(deviceType.substring(3, 4))) {
					sqlBuffer.append(" or sets.settype = '").append("0226")
							.append("'");
				}
				if ("1".equals(deviceType.substring(4, 5))) {
					sqlBuffer.append(" or sets.settype = '").append("0230")
							.append("'");
				}
				if ("1".equals(deviceType.substring(5, 6))) {
					sqlBuffer.append(" or sets.settype = '").append("0121")
							.append("'");
				}
				sqlBuffer.append(") and (1<>1 ");
				List listArea = null;
				String tmp = "";
				if ("1".equals(area.substring(0, 1))) {
					listArea = GetAreaCodeTimelyAction.getInstance()
							.returnListAfterCheckTime(1);
					for (int i = 0; i < listArea.size(); i++) {
						tmp = listArea.get(i).toString();
						sqlBuffer.append(" or device.area = " + tmp);
					}
				}
				if ("1".equals(area.substring(1, 2))) {
					listArea = GetAreaCodeTimelyAction.getInstance()
							.returnListAfterCheckTime(2);
					for (int i = 0; i < listArea.size(); i++) {
						tmp = listArea.get(i).toString();
						sqlBuffer.append(" or device.area = " + tmp);
					}
				}
				if ("1".equals(area.substring(2, 3))) {
					listArea = GetAreaCodeTimelyAction.getInstance()
							.returnListAfterCheckTime(3);
					for (int i = 0; i < listArea.size(); i++) {
						tmp = listArea.get(i).toString();
						sqlBuffer.append(" or device.area = " + tmp);
					}
				}
				if ("1".equals(area.substring(3, 4))) {
					listArea = GetAreaCodeTimelyAction.getInstance()
							.returnListAfterCheckTime(4);
					for (int i = 0; i < listArea.size(); i++) {
						tmp = listArea.get(i).toString();
						sqlBuffer.append(" or device.area = " + tmp);
					}
				}

				sqlBuffer.append(") and (1<>1 ");

				Session session = HibernateSessionFactory.currentSession();

				Enumeration enumration = request.getParameterNames();
				String name = "";
				String value = "";
				while (enumration.hasMoreElements()) {
					name = (String) enumration.nextElement();
					if (name.startsWith("Item_")) {
						value = request.getParameter(name);

						if ("3015".equals(name.substring(5))) {
							if ("1".equals(value)) {
								sqlBuffer
										.append("or (serial.abnormaltype = 201) ");
							}

						} else if ("3016".equals(name.substring(5))) {
							if ("1".equals(value)) {
								sqlBuffer
										.append("or (serial.abnormaltype = 203) ");
							}

						} else if ("3017".equals(name.substring(5))) {
							if ("1".equals(value)) {
								sqlBuffer
										.append("or (serial.abnormaltype  = 204) ");
							}

						} else if ("3018".equals(name.substring(5))) {
							if ("1".equals(value)) {
								sqlBuffer
										.append("or (serial.abnormaltype  = 205) ");
							}

						} else if ("3019".equals(name.substring(5))) {
							if ("1".equals(value)) {
								sqlBuffer.append("or serial.abnormaltype = 3 ");
							}

						} else if ("30110".equals(name.substring(5))) {
							if ("1".equals(value)) {
								sqlBuffer
										.append("or serial.abnormaltype = 15 ");
							}
						} else if ("300111".equals(name.substring(5))) {
							if ("1".equals(value)) {
								sqlBuffer
										.append("or (serial.abnormaltype = 51) ");
							}
						} else if ("30112".equals(name.substring(5))) {
							if ("1".equals(value)) {
								sqlBuffer
										.append("or (serial.abnormaltype  = 52) ");
							}
						} else if ("30113".equals(name.substring(5))) {
							if ("1".equals(value)) {
								sqlBuffer
										.append("or (serial.abnormaltype  = 53) ");
							}
						} else if ("3006".equals(name.substring(5))) {
							if ("1".equals(value)) {
								sqlBuffer
										.append("or serial.abnormaltype = 14 ");
							}
						} else if ("3008".equals(name.substring(5))) {
							if ("1".equals(value)) {
								sqlBuffer.append("or serial.abnormaltype = 4 ");
							}
						} else if ("3009".equals(name.substring(5))) {
							if ("1".equals(value)) {
								sqlBuffer
										.append("or serial.abnormaltype = 10 ");
							}
						} else if ("30010".equals(name.substring(5))) {
							if ("1".equals(value)) {
								sqlBuffer.append("or serial.abnormaltype = 9 ");
							}
						} else if ("30011".equals(name.substring(5))) {
							if ("1".equals(value)) {
								sqlBuffer.append("or serial.abnormaltype = 6 ");
							}
						}
					}

				}

				sqlBuffer.append(") order by sets.fatherid");

				String xmlOut = "";

				Query queryer = session.createQuery(sqlBuffer.toString());
				queryer.setString("analysistime", analysistime);
				List lister = queryer.list();
				// user exist
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(lister.size()), lister);

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
		}
		return null;
	}
}