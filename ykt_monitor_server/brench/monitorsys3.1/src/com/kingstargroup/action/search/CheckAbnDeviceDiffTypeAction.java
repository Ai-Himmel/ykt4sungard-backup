package com.kingstargroup.action.search;

import java.util.Enumeration;
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
import com.kingstargroup.form.MapParamTable;
import com.kingstargroup.form.MapStateDic;
import com.kingstargroup.form.UnusualDeviceResult;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.XMLGenerateUtil;

public class CheckAbnDeviceDiffTypeAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CheckAbnormalDeviceHistoyAction.class);

	/**
	 * Method name: deviceList<br>
	 * Description: 设备信息列表<br>
	 * Return: ActionForward<br>
	 * Args:
	 * 
	 * @param mapping
	 *            Args:
	 * @param form
	 *            Args:
	 * @param request
	 *            Args:
	 * @param response
	 *            Args:
	 * @return Args:
	 * @throws Exception
	 *             Modify History: <br>
	 *             操作类型 操作人 操作时间 操作内容<br>
	 *             ======================================<br>
	 *             创建 何林青 Aug 15, 2007 <br>
	 * @author 何林青
	 * @version
	 * @since 1.0
	 */
	public ActionForward deviceList(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		HttpSession httpSession = request.getSession();
		// 判断信息
		if (httpSession.getAttribute("userLogin") != null) {

			try {
				// MessageResources msgResources = (MessageResources) this
				// .getServlet().getServletContext().getAttribute(
				// Globals.MESSAGES_KEY);
				request.setCharacterEncoding("GBK");
				String deviceType = request.getParameter("DeviceType");
				String area = request.getParameter("Area");

				StringBuffer sqlBuff = new StringBuffer();
				StringBuffer sqlBuffServer = new StringBuffer();
				StringBuffer sqlBuffService = new StringBuffer();
				StringBuffer sqlBuffer = new StringBuffer();

				sqlBuff
						.append(
								"select new com.kingstargroup.form.UnusualDeviceResult")
						.append(
								"(sets.id, device.devphyid, device.devicename, device.devtypecode, ")
						.append("device.contactName, device.errorReason) ")
						.append(
								"from MapDeviceTable device, MapSetsTable sets ")
						.append(
								"where device.id.analysistime>=:analysistime and device.devphyid=sets.setsid and (1<>1 ");

				sqlBuffServer
						.append(
								"select new com.kingstargroup.form.UnusualDeviceResult")
						.append(
								"(sets.id, device.devphyid, device.devicename, device.devtypecode, ")
						.append("device.contactName, device.errorReason) ")
						.append(
								"from MapDeviceTable device, MapFathersetsTable sets ")
						.append(
								"where device.id.analysistime>=:analysistime and device.devphyid=sets.systemid and (1<>1 ");

				sqlBuffService
						.append(
								"select new com.kingstargroup.form.UnusualDeviceResult")
						.append(
								"(sets.id, sets.systemid, serial.serverName, serial.serviceType, ")
						.append("serial.contactname, serial.errorcode) ")
						.append(
								"from MapServiceException serial, MapFathersetsTable sets ")
						.append(
								"where serial.id.analysistime>=:analysistime and serial.serverId=sets.id ")
						.append("and (1<>1 ");

				sqlBuffer
						.append(
								"select new com.kingstargroup.form.UnusualDeviceResult")
						.append(
								"(sets.id, serial.id.devphyid, sets.setname, sets.settype, ")
						.append("serial.contactname, serial.abnormaltype) ")
						.append(
								"from MapSerialexceptTable serial, MapSetsTable sets, TDevice device ")
						.append(
								"where serial.id.analysistime>=:analysistime and serial.id.devphyid=sets.setsid and sets.setsid=device.devphyid ")
						.append("and device.status=1 and (1<>1 ");
				// , MapSerialTable serial, MapSeriallostTable seriallost
				// server--999set ---lanprot --pos
				// --multimidia--check---forbbiden
				// handan -- fenglin ---jiangwang---zhangjiang
				if (deviceType.length()>0&&"1".equals(deviceType.substring(0, 1))) {
					// don't know the server's device Type
					sqlBuff.append(" or device.devtypecode = '").append("0000")
							.append("'");
					sqlBuffServer.append(" or device.devtypecode = '").append(
							"0000").append("'");
					sqlBuffService.append(" or serial.serviceType <> '")
							.append("0000").append("'");
					sqlBuffer.append(" or sets.settype = '").append("0000")
							.append("'");
				}
				if (deviceType.length()>1&&"1".equals(deviceType.substring(1, 2))) {
					sqlBuff.append(" or device.devtypecode = '").append("12")
							.append("'");
					sqlBuffer.append(" or sets.settype = '").append("12")
							.append("'");
				}
				if (deviceType.length()>2&&"1".equals(deviceType.substring(2, 3))) {
					sqlBuff.append(" or device.devtypecode = '").append("5301")
							.append("'");
					sqlBuffer.append(" or sets.settype = '").append("5301")
							.append("'");
				}
				if (deviceType.length()>3&&"1".equals(deviceType.substring(3, 4))) {
					sqlBuff.append(" or device.devtypecode = '").append("0226")
							.append("' or device.devtypecode = '").append(
									"0201").append("'");
					sqlBuffer.append(" or sets.settype = '").append("0226")
							.append("' or sets.settype = '").append("0201")
							.append("'");
				}
				if (deviceType.length()>4&&"1".equals(deviceType.substring(4, 5))) {
					sqlBuff.append(" or device.devtypecode = '").append("0236")
							.append("'");
					sqlBuffer.append(" or sets.settype = '").append("0236")
							.append("'");
				}
				if (deviceType.length()>5&&"1".equals(deviceType.substring(5, 6))) {
					sqlBuff.append(" or device.devtypecode = '").append("0121")
							.append("'");
					sqlBuffer.append(" or sets.settype = '").append("0121")
							.append("'");
				}
				sqlBuff.append(") and (1<>1 ");
				sqlBuffService.append(") and (1<>1 ");
				sqlBuffServer.append(") and (1<>1 ");
				sqlBuffer.append(") and (1<>1 ");
				List listArea = null;
				String tmp = "";
				if (area.length()>0&&"1".equals(area.substring(0, 1))) {
					listArea = GetAreaCodeTimelyAction.getInstance()
							.returnListAfterCheckTime(1);
					for (int i = 0; i < listArea.size(); i++) {
						tmp = "'" + listArea.get(i).toString() + "'";
						sqlBuff.append(" or device.areacode = " + tmp);
						sqlBuffServer.append(" or sets.area = " + tmp);
						sqlBuffService.append(" or sets.area = " + tmp);
						sqlBuffer.append(" or device.areacode = " + tmp);
					}
				}
				if (area.length()>1&&"1".equals(area.substring(1, 2))) {
					listArea = GetAreaCodeTimelyAction.getInstance()
							.returnListAfterCheckTime(2);
					for (int i = 0; i < listArea.size(); i++) {
						tmp = "'" + listArea.get(i).toString() + "'";
						sqlBuff.append(" or device.areacode = " + tmp);
						sqlBuffServer.append(" or sets.area = " + tmp);
						sqlBuffService.append(" or sets.area = " + tmp);
						sqlBuffer.append(" or device.areacode = " + tmp);
					}
				}
				if (area.length()>2&&"1".equals(area.substring(2, 3))) {
					listArea = GetAreaCodeTimelyAction.getInstance()
							.returnListAfterCheckTime(3);
					for (int i = 0; i < listArea.size(); i++) {
						tmp = "'" + listArea.get(i).toString() + "'";
						sqlBuff.append(" or device.areacode = " + tmp);
						sqlBuffServer.append(" or sets.area = " + tmp);
						sqlBuffService.append(" or sets.area = " + tmp);
						sqlBuffer.append(" or device.areacode = " + tmp);
					}
				}
				if (area.length()>3&&"1".equals(area.substring(3, 4))) {
					listArea = GetAreaCodeTimelyAction.getInstance()
							.returnListAfterCheckTime(4);
					for (int i = 0; i < listArea.size(); i++) {
						tmp = "'" + listArea.get(i).toString() + "'";
						sqlBuff.append(" or device.areacode = " + tmp);
						sqlBuffServer.append(" or sets.area = " + tmp);
						sqlBuffService.append(" or sets.area = " + tmp);
						sqlBuffer.append(" or device.areacode = " + tmp);
					}
				}

				sqlBuff.append(") and (1<>1 ");
				sqlBuffServer.append(") and (1<>1 ");
				sqlBuffService.append(") and (1<>1 ");
				sqlBuffer.append(") and (1<>1 ");

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
								sqlBuffServer
										.append("or (device.errorReason =105) ");
								break;
							}
						}

						if ("3012".equals(name.substring(5))) {// cpu
							if ("1".equals(value)) {
								sqlBuff
										.append("or (device.errorReason  =102) ");
								sqlBuffServer
										.append("or (device.errorReason =102) ");
							}

						} else if ("3013".equals(name.substring(5))) {// mem
							if ("1".equals(value)) {
								sqlBuff
										.append("or (device.errorReason  =103) ");
								sqlBuffServer
										.append("or (device.errorReason =103) ");
							}

						} else if ("3014".equals(name.substring(5))) {// disk
							if ("1".equals(value)) {
								sqlBuff
										.append("or (device.errorReason  =104) ");
								sqlBuffServer
										.append("or (device.errorReason =104) ");
							}

						} else if ("3015".equals(name.substring(5))) {
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
						} else if ("3005".equals(name.substring(5))) {
							if ("1".equals(value)) {
								sqlBuff.append("or device.errorReason = 11 ");
							}
						} else if ("3006".equals(name.substring(5))) {
							if ("1".equals(value)) {
								sqlBuffer
										.append("or serial.abnormaltype = 14 ");
							}
						} else if ("3007".equals(name.substring(5))) {
							if ("1".equals(value)) {
								sqlBuff.append("or device.errorReason = 12 ");
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
						} else if ("30114".equals(name.substring(5))) {// web
							if ("1".equals(value)) {
								sqlBuffService
										.append("or serial.errorcode = 108 ");
							}
						} else if ("30115".equals(name.substring(5))) {// db
							if ("1".equals(value)) {
								sqlBuffService
										.append("or serial.errorcode = 109 ");
							}
						} else if ("30116".equals(name.substring(5))) {// drtp
							if ("1".equals(value)) {
								sqlBuffService
										.append("or serial.errorcode = 110 ");
							}
						}
					}

				}

				sqlBuff
						.append(") order by sets.fatherid,device.errorReason,sets.id");
				sqlBuffService
						.append(") order by sets.systemid,serial.errorcode,sets.id");
				sqlBuffServer
						.append(") order by sets.systemid,device.errorReason,sets.id");
				sqlBuffer
						.append(") order by sets.fatherid,serial.abnormaltype,sets.id");

				double cycle = 5.0;
				double serverCycle = 5.0;
				double serviceCycle = 5.0;
				Query queryCycle = session
						.createQuery("from MapParamTable param where param.parameter=:paramRefer "
								+ "or param.parameter=:paramRefer1 or param.parameter=:paramRefer2");
				queryCycle.setString("paramRefer", "HeartInterval");
				queryCycle.setString("paramRefer1", "ServerExceptionCycle");
				queryCycle.setString("paramRefer2", "ServiceExceptionCycle");
				List listParam = queryCycle.list();
				Iterator iterParam = listParam.iterator();
				while (iterParam.hasNext()) {
					MapParamTable mapParamTable = (MapParamTable) iterParam
							.next();
					if ("HeartInterval".equals(mapParamTable.getParameter())) {
						cycle = mapParamTable.getValue();
					} else if ("ServerExceptionCycle".equals(mapParamTable
							.getParameter())) {
						serverCycle = mapParamTable.getValue();
					} else if ("ServiceExceptionCycle".equals(mapParamTable
							.getParameter())) {
						serviceCycle = mapParamTable.getValue();
					}

				}
				String s = String.valueOf(cycle * 60);
				String t = String.valueOf(serverCycle * 60);
				String v = String.valueOf(serviceCycle * 60);
				int intCycle = Integer.parseInt(s.substring(0, s.indexOf('.')));
				int intServerCycle = Integer.parseInt(t.substring(0, t
						.indexOf('.')));
				int intServiceCylce = Integer.parseInt(v.substring(0, v
						.indexOf('.')));
				String checkTime = DateUtil
						.getNewTime(DateUtil.getNow(), -3600);
				String checkTime1 = DateUtil.getNewTime(DateUtil.getNow(),
						-intCycle);
				String checkTime2 = DateUtil.getNewTime(DateUtil.getNow(),
						-intServerCycle);
				String checkTime3 = DateUtil.getNewTime(DateUtil.getNow(),
						-intServiceCylce);

				String xmlOut = "";
				Query query = session.createQuery(sqlBuff.toString());
				query.setString("analysistime", checkTime1);
				List list = query.list();

				Query queryServer = session.createQuery(sqlBuffServer
						.toString());
				queryServer.setString("analysistime", checkTime2);
				List listServer = queryServer.list();

				Query queryService = session.createQuery(sqlBuffService
						.toString());
				queryService.setString("analysistime", checkTime3);
				List listService = queryService.list();

				Query queryer = session.createQuery(sqlBuffer.toString());
				queryer.setString("analysistime", checkTime);
				List lister = queryer.list();

				String predevphyid = "";
				for (int i = 0; i < list.size(); i++) {
					UnusualDeviceResult unusualDR = (UnusualDeviceResult) list
							.get(i);
					if (predevphyid.equals(unusualDR.getDevphy999Id())) {
						list.remove(i);
						i--;
					} else {
						predevphyid = unusualDR.getDevphy999Id();
					}
				}
				predevphyid = "";
				for (int i = 0; i < listServer.size(); i++) {
					UnusualDeviceResult unusualDR = (UnusualDeviceResult) listServer
							.get(i);
					if (predevphyid.equals(unusualDR.getDevphy999Id())) {
						listServer.remove(i);
						i--;
					} else {
						predevphyid = unusualDR.getDevphy999Id();
					}
				}

				predevphyid = "";
				for (int i = 0; i < listService.size(); i++) {
					UnusualDeviceResult unusualDR = (UnusualDeviceResult) listService
							.get(i);
					if (predevphyid.equals(unusualDR.getDevphy999Id())) {
						listService.remove(i);
						i--;
					} else {
						predevphyid = unusualDR.getDevphy999Id();
					}
				}

				predevphyid = "";
				for (int i = 0; i < lister.size(); i++) {
					UnusualDeviceResult unusualDR = (UnusualDeviceResult) lister
							.get(i);
					if (predevphyid.equals(unusualDR.getDevphy999Id())) {
						lister.remove(i);
						i--;
					} else {
						predevphyid = unusualDR.getDevphy999Id();
					}
				}
				// user exist
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(list.size()), list);
				xmlOut = XMLGenerateUtil.DeXMLGenerate(xmlOut, listServer);
				xmlOut = XMLGenerateUtil.DeXMLGenerate(xmlOut, listService);
				xmlOut = XMLGenerateUtil.DeXMLGenerate(xmlOut, lister);

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
