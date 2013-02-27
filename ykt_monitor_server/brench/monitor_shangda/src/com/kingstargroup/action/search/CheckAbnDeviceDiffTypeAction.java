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
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.XMLGenerateUtil;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: CheckAbnDeviceDiffTypeAction.java
 * Description: xml返回异常设备及流水信息列表类
 * Modify History（或Change Log）: 
 * 操作类型（创建、修改等） 操作日期     操作者    操作内容简述
 * 创建              Nov 16, 2005   何林青   类
 * <p>
 * 
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */
public class CheckAbnDeviceDiffTypeAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CheckAbnormalDeviceHistoyAction.class);

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
			request.setCharacterEncoding("GBK");
			String deviceType = request.getParameter("DeviceType");
			String area = request.getParameter("Area");

			StringBuffer sqlBuff = new StringBuffer();
			StringBuffer sqlBuffer = new StringBuffer();
			sqlBuff
					.append(
							"select new com.kingstargroup.form.UnusualDeviceResult")
					.append(
							"(sets.id, device.devphy999Id, device.deviceName, device.deviceType, ")
					.append("device.contactName, device.errorReason) ")
					.append(
							"from MapDeviceTable as device, MapSetsTable as sets ")
					.append(
							"where device.id.analysisTime>=:analysisTime and device.devphy999Id=sets.setsid and (1<>1 ");
			sqlBuffer
					.append(
							"select new com.kingstargroup.form.UnusualDeviceResult")
					.append(
							"(sets.id, serial.id.deviceId, sets.setname, sets.settype, ")
					.append("serial.contactname, serial.abnormaltype) ")
					.append(
							"from MapSerialexceptTable as serial, MapSetsTable as sets, TPifDevice as device ")
					.append(
							"where serial.id.analysisTime>=:analysisTime and serial.id.deviceId=sets.setsid and sets.setsid=device.dev999Id ")
					.append("and not device.stateId=5 and (1<>1 ");
			// , MapSerialTable as serial, MapSeriallostTable as seriallost
			// server--999set ---lanprot --pos --multimidia--check---forbbiden
			// handan -- fenglin ---jiangwang---zhangjiang
			if ("1".equals(deviceType.substring(0, 1))) {
				// don't know the server's device Type
				sqlBuff.append(" or device.deviceType = '").append("0000")
						.append("'");
				sqlBuffer.append(" or sets.settype = '").append("0000").append(
						"'");
			}
			if ("1".equals(deviceType.substring(1, 2))) {
				sqlBuff.append(" or device.deviceType = '").append("12")
						.append("'");
				sqlBuffer.append(" or sets.settype = '").append("12").append(
						"'");
			}
			if ("1".equals(deviceType.substring(2, 3))) {
				sqlBuff.append(" or device.deviceType = '").append("5301")
						.append("'");
				sqlBuffer.append(" or sets.settype = '").append("5301").append(
						"'");
			}
			if ("1".equals(deviceType.substring(3, 4))) {
				sqlBuff.append(" or device.deviceType = '").append("0226")
						.append("'");
				sqlBuffer.append(" or sets.settype = '").append("0226").append(
						"'");
			}
			if ("1".equals(deviceType.substring(4, 5))) {
				sqlBuff.append(" or device.deviceType = '").append("0230")
						.append("'");
				sqlBuffer.append(" or sets.settype = '").append("0230").append(
						"'");
			}
			if ("1".equals(deviceType.substring(5, 6))) {
				sqlBuff.append(" or device.deviceType = '").append("0121")
						.append("'");
				sqlBuffer.append(" or sets.settype = '").append("0121").append(
						"'");
			}
			sqlBuff.append(") and (1<>1 ");
			sqlBuffer.append(") and (1<>1 ");
			List listArea = null;
			String tmp = "";
			if ("1".equals(area.substring(0, 1))) {
				listArea = GetAreaCodeTimelyAction.getInstance()
						.returnListAfterCheckTime(1);
				for (int i = 0; i < listArea.size(); i++) {
					tmp = listArea.get(i).toString();
					sqlBuff.append(" or device.area = " + tmp);
					sqlBuffer.append(" or device.area = " + tmp);
				}
			}
			if ("1".equals(area.substring(1, 2))) {
				listArea = GetAreaCodeTimelyAction.getInstance()
						.returnListAfterCheckTime(2);
				for (int i = 0; i < listArea.size(); i++) {
					tmp = listArea.get(i).toString();
					sqlBuff.append(" or device.area = " + tmp);
					sqlBuffer.append(" or device.area = " + tmp);
				}
			}
			if ("1".equals(area.substring(2, 3))) {
				listArea = GetAreaCodeTimelyAction.getInstance()
						.returnListAfterCheckTime(3);
				for (int i = 0; i < listArea.size(); i++) {
					tmp = listArea.get(i).toString();
					sqlBuff.append(" or device.area = " + tmp);
					sqlBuffer.append(" or device.area = " + tmp);
				}
			}

			sqlBuff.append(") and (1<>1 ");
			sqlBuffer.append(") and (1<>1 ");

			Enumeration enumration = request.getParameterNames();
			String name = "";
			String value = "";
			while (enumration.hasMoreElements()) {
				name = (String) enumration.nextElement();
				if (name.startsWith("Item_")) {
					value = request.getParameter(name);
					if ("3011".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlBuff.append("or (device.errorReason =101) ");
						}

					} else if ("3012".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlBuff.append("or (device.errorReason  =102) ");
						}

					} else if ("3013".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlBuff.append("or (device.errorReason  =103) ");
						}

					} else if ("3014".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlBuff.append("or (device.errorReason  =104) ");
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
							sqlBuffer.append("or serial.abnormaltype = 15 ");
						}
					} else if ("300111".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlBuffer.append("or (serial.abnormaltype = 51) ");
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
							sqlBuffer.append("or serial.abnormaltype = 14 ");
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
							sqlBuffer.append("or serial.abnormaltype = 10 ");
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

			sqlBuff.append(") order by sets.fatherid");
			sqlBuffer.append(") order by sets.fatherid");

			try {
				// MessageResources msgResources = (MessageResources) this
				// .getServlet().getServletContext().getAttribute(
				// Globals.MESSAGES_KEY);
				Session session = HibernateSessionFactory.currentSession();
				
				double cycle = 5.0;
				Query queryCycle = session
				.createQuery("from MapParamTable as param where param.parameter=:paramRefer");
				queryCycle.setString("paramRefer", "HeartInterval");
				Iterator iterParam = queryCycle.iterate();
				if (iterParam.hasNext()) {
					MapParamTable mapParamTable = (MapParamTable) iterParam.next();
					cycle = mapParamTable.getValue().doubleValue();
				}
				String s = String.valueOf(cycle * 60);
				int doubleCycle = Integer.parseInt(s.substring(0, s.indexOf('.')));
				String checkTime = DateUtil.getNewTime(DateUtil.getNow(), -3600);
				String checkTime1 = DateUtil.getNewTime(DateUtil.getNow(), -doubleCycle);
				String xmlOut = "";
				Query query = session.createQuery(sqlBuff.toString());
				query.setString("analysisTime", checkTime1);
				// query.setString("analysisTime", "20051013000000");
				List list = query.list();

				Query queryer = session.createQuery(sqlBuffer.toString());
				queryer.setString("analysisTime", checkTime);
				// queryer.setString("analysisTime", "20051013000000");
				List lister = queryer.list();
				// user exist
				xmlOut = XMLGenerateUtil.XMLGenerate(ErrorCode.SUCCESS, String
						.valueOf(list.size()), list);
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
