package com.kingstargroup.action.search;

import java.util.Enumeration;
import java.util.Iterator;
import java.util.List;

import org.apache.log4j.Logger;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;
import com.kingstargroup.commons.BaseAction;
import com.kingstargroup.commons.HibernateSessionFactory;
import com.kingstargroup.form.MapParamTable;
import com.kingstargroup.utils.DateUtil;
import com.kingstargroup.utils.XMLGenerateUtil;

public class CheckStatisticalAction extends BaseAction {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CheckStatisticalAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (logger.isDebugEnabled()) {
			logger
					.debug("execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse) - start"); //$NON-NLS-1$
		}

		HttpSession httpSession = request.getSession();
		// еп╤опео╒
		if (httpSession.getAttribute("userLogin") != null) {
			request.setCharacterEncoding("GBK");
			StringBuffer sqlAreaOne = new StringBuffer();
			StringBuffer sqlAreaTwo = new StringBuffer();
			StringBuffer sqlAreaThree = new StringBuffer();
			StringBuffer sqlAreaFour = new StringBuffer();
			StringBuffer sqlDevOne = new StringBuffer();
			StringBuffer sqlDevTwo = new StringBuffer();
			StringBuffer sqlDevThree = new StringBuffer();
			StringBuffer sqlDevFour = new StringBuffer();
			StringBuffer sqlServerOne = new StringBuffer();
			StringBuffer sqlServerTwo = new StringBuffer();
			StringBuffer sqlServerThree = new StringBuffer();
			StringBuffer sqlServerFour = new StringBuffer();
			StringBuffer sqlServiceOne = new StringBuffer();
			StringBuffer sqlServiceTwo = new StringBuffer();
			StringBuffer sqlServiceThree = new StringBuffer();
			StringBuffer sqlServiceFour = new StringBuffer();
			sqlAreaOne
					.append("select distinct(b.devphy999Id) as handan from MapDeviceTable as b,MapSetsTable as c where b.devphy999Id=c.setsid and b.id.analysisTime>=:analysisTime and (1<>1 ");
			sqlServerOne
			.append("select distinct(b.devphy999Id) as handan from MapDeviceTable as b,MapFathersetsTable as c where b.devphy999Id=c.systemid and b.id.analysisTime>=:analysisTime and (1<>1 ");
			sqlServiceOne
			.append("select distinct(b.id.serviceId) as handan from MapServiceException as b,MapFathersetsTable as c where b.serverId=c.id and b.id.analysistime>=:analysisTime and (1<>1 ");
			
			sqlDevOne
					.append(
							"select distinct(a.id.deviceId) as handan from MapSerialexceptTable as a,TPifDevice as b,MapSetsTable as c ")
					.append(
							"where a.id.analysisTime>=:analysisTime and a.id.deviceId = b.devphy999Id and a.id.deviceId = c.setsid and (1<>1 ");
			List listAreaOne = GetAreaCodeTimelyAction.getInstance()
					.returnListAfterCheckTime(1);
			String temp = "";
			for (int i = 0; i < listAreaOne.size(); i++) {
				temp = listAreaOne.get(i).toString();
				sqlAreaOne.append(" or b.area=" + temp);
				sqlDevOne.append(" or b.area=" + temp);
				sqlServerOne.append(" or c.area=" + temp);
				sqlServiceOne.append(" or c.area=" + temp);
			}
			sqlAreaOne.append(") and (1<>1 ");
			sqlDevOne.append(") and (1<>1 ");
			sqlServerOne.append(") and (1<>1 ");
			sqlServiceOne.append(") and (1<>1 ");

			sqlAreaTwo
					.append("select distinct(b.devphy999Id) as fenglin from MapDeviceTable as b,MapSetsTable as c where b.devphy999Id=c.setsid and b.id.analysisTime>=:analysisTime and (1<>1 ");
			sqlDevTwo
					.append(
							"select distinct(a.id.deviceId) as fenglin from MapSerialexceptTable as a,TPifDevice as b,MapSetsTable as c ")
					.append(
							"where a.id.analysisTime>=:analysisTime and  a.id.deviceId = b.devphy999Id and a.id.deviceId = c.setsid and (1<>1 ");
			sqlServerTwo
			.append("select distinct(b.devphy999Id) as handan from MapDeviceTable as b,MapFathersetsTable as c where b.devphy999Id=c.systemid and b.id.analysisTime>=:analysisTime and (1<>1 ");
			sqlServiceTwo
			.append("select distinct(b.id.serviceId) as handan from MapServiceException as b,MapFathersetsTable as c where b.serverId=c.id and b.id.analysistime>=:analysisTime and (1<>1 ");
			
			List listAreaTwo = GetAreaCodeTimelyAction.getInstance()
					.returnListAfterCheckTime(2);

			for (int i = 0; i < listAreaTwo.size(); i++) {
				temp = listAreaTwo.get(i).toString();
				sqlAreaTwo.append(" or b.area=" + temp);
				sqlDevTwo.append(" or b.area=" + temp);
				sqlServerTwo.append(" or c.area=" + temp);
				sqlServiceTwo.append(" or c.area=" + temp);
				
			}
			sqlAreaTwo.append(") and (1<>1 ");
			sqlDevTwo.append(") and (1<>1 ");
			sqlServerTwo.append(") and (1<>1 ");
			sqlServiceTwo.append(") and (1<>1 ");

			sqlAreaThree
					.append("select distinct(b.devphy999Id) as jiangwan from MapDeviceTable as b,MapSetsTable as c where b.devphy999Id=c.setsid and b.id.analysisTime>=:analysisTime and (1<>1 ");
			sqlDevThree
					.append(
							"select distinct(a.id.deviceId) as jiangwan from MapSerialexceptTable as a,TPifDevice as b,MapSetsTable as c ")
					.append(
							"where a.id.analysisTime>=:analysisTime and  a.id.deviceId = b.devphy999Id and a.id.deviceId = c.setsid and (1<>1 ");
			sqlServerThree
			.append("select distinct(b.devphy999Id) as handan from MapDeviceTable as b,MapFathersetsTable as c where b.devphy999Id=c.systemid and b.id.analysisTime>=:analysisTime and (1<>1 ");
			sqlServiceThree
			.append("select distinct(b.id.serviceId) as handan from MapServiceException as b,MapFathersetsTable as c where b.serverId=c.id and b.id.analysistime>=:analysisTime and (1<>1 ");
			
			List listAreaThree = GetAreaCodeTimelyAction.getInstance()
					.returnListAfterCheckTime(4);

			for (int i = 0; i < listAreaThree.size(); i++) {
				temp = listAreaThree.get(i).toString();
				sqlAreaThree.append(" or b.area=" + temp);
				sqlDevThree.append(" or b.area=" + temp);
				sqlServerThree.append(" or c.area=" + temp);
				sqlServiceThree.append(" or c.area=" + temp);
			}
			sqlAreaThree.append(") and (1<>1 ");
			sqlDevThree.append(") and (1<>1 ");
			sqlServerThree.append(") and (1<>1 ");
			sqlServiceThree.append(") and (1<>1 ");

			sqlAreaFour
					.append("select distinct(b.devphy999Id) as zhangjiang from MapDeviceTable as b,MapSetsTable as c where b.devphy999Id=c.setsid and b.id.analysisTime>=:analysisTime and (1<>1 ");
			sqlDevFour
					.append(
							"select distinct(a.id.deviceId) as zhangjiang from MapSerialexceptTable as a,TPifDevice as b,MapSetsTable as c ")
					.append(
							"where a.id.analysisTime>=:analysisTime and a.id.deviceId = b.devphy999Id and a.id.deviceId = c.setsid and (1<>1 ");
			sqlServerFour
			.append("select distinct(b.devphy999Id) as handan from MapDeviceTable as b,MapFathersetsTable as c where b.devphy999Id=c.systemid and b.id.analysisTime>=:analysisTime and (1<>1 ");
			sqlServiceFour
			.append("select distinct(b.id.serviceId) as handan from MapServiceException as b,MapFathersetsTable as c where b.serverId=c.id and b.id.analysistime>=:analysisTime and (1<>1 ");
			
			List listAreaFour = GetAreaCodeTimelyAction.getInstance()
					.returnListAfterCheckTime(3);

			for (int i = 0; i < listAreaFour.size(); i++) {
				temp = listAreaFour.get(i).toString();
				sqlAreaFour.append(" or b.area=" + temp);
				sqlDevFour.append(" or b.area=" + temp);
				sqlServerFour.append(" or c.area=" + temp);
				sqlServiceFour.append(" or c.area=" + temp);
			}
			sqlAreaFour.append(") and (1<>1 ");
			sqlDevFour.append(") and (1<>1 ");
			sqlServerFour.append(") and (1<>1 ");
			sqlServiceFour.append(") and (1<>1 ");

			Enumeration enumration = request.getParameterNames();
			String name = "";
			String value = "";
			while (enumration.hasMoreElements()) {
				name = (String) enumration.nextElement();
				if (name.startsWith("Item_")) {
					value = request.getParameter(name);
					if ("3011".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlAreaOne.append("or (b.errorReason = 101) ");
							sqlAreaTwo.append("or (b.errorReason = 101) ");
							sqlAreaThree.append("or (b.errorReason = 101) ");
							sqlAreaFour.append("or (b.errorReason = 101) ");
							sqlServerOne.append("or (b.errorReason = 105) ");
							sqlServerTwo.append("or (b.errorReason = 105) ");
							sqlServerThree.append("or (b.errorReason = 105) ");
							sqlServerFour.append("or (b.errorReason = 105) ");
						}

					} else if ("3012".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlAreaOne.append("or (b.errorReason = 102) ");
							sqlAreaTwo.append("or (b.errorReason = 102) ");
							sqlAreaThree.append("or (b.errorReason = 102) ");
							sqlAreaFour.append("or (b.errorReason = 102) ");
							sqlServerOne.append("or (b.errorReason = 102) ");
							sqlServerTwo.append("or (b.errorReason = 102) ");
							sqlServerThree.append("or (b.errorReason = 102) ");
							sqlServerFour.append("or (b.errorReason = 102) ");
						}

					} else if ("3013".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlAreaOne.append("or (b.errorReason = 103) ");
							sqlAreaTwo.append("or (b.errorReason = 103) ");
							sqlAreaThree.append("or (b.errorReason = 103) ");
							sqlAreaFour.append("or (b.errorReason = 103) ");
							sqlServerOne.append("or (b.errorReason = 103) ");
							sqlServerTwo.append("or (b.errorReason = 103) ");
							sqlServerThree.append("or (b.errorReason = 103) ");
							sqlServerFour.append("or (b.errorReason = 103) ");
						}

					} else if ("3014".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlAreaOne.append("or (b.errorReason = 104) ");
							sqlAreaTwo.append("or (b.errorReason = 104) ");
							sqlAreaThree.append("or (b.errorReason = 104) ");
							sqlAreaFour.append("or (b.errorReason = 104) ");
							sqlServerOne.append("or (b.errorReason = 104) ");
							sqlServerTwo.append("or (b.errorReason = 104) ");
							sqlServerThree.append("or (b.errorReason = 104) ");
							sqlServerFour.append("or (b.errorReason = 104) ");
						}

					} else if ("3015".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or (a.abnormaltype =201) ");
							sqlDevTwo.append("or (a.abnormaltype  =201) ");
							sqlDevThree.append("or (a.abnormaltype  =201) ");
							sqlDevFour.append("or (a.abnormaltype  =201) ");
						}

					} else if ("3016".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or (a.abnormaltype =203) ");
							sqlDevTwo.append("or (a.abnormaltype =203) ");
							sqlDevThree.append("or (a.abnormaltype =203) ");
							sqlDevFour.append("or (a.abnormaltype =203) ");
						}

					} else if ("3017".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or (a.abnormaltype = 204) ");
							sqlDevTwo.append("or (a.abnormaltype = 204) ");
							sqlDevThree.append("or (a.abnormaltype = 204) ");
							sqlDevFour.append("or (a.abnormaltype = 204) ");
						}

					} else if ("3018".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or (a.abnormaltype = 205) ");
							sqlDevTwo.append("or (a.abnormaltype = 205) ");
							sqlDevThree.append("or (a.abnormaltype = 205) ");
							sqlDevFour.append("or (a.abnormaltype = 205) ");
						}

					} else if ("3019".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 3 ");
							sqlDevTwo.append("or a.abnormaltype = 3 ");
							sqlDevThree.append("or a.abnormaltype = 3 ");
							sqlDevFour.append("or a.abnormaltype = 3 ");
						}
					} else if ("30110".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 15 ");
							sqlDevTwo.append("or a.abnormaltype = 15 ");
							sqlDevThree.append("or a.abnormaltype = 15 ");
							sqlDevFour.append("or a.abnormaltype = 15 ");
						}
					} else if ("30111".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 51 ");
							sqlDevTwo.append("or a.abnormaltype = 51 ");
							sqlDevThree.append("or a.abnormaltype =51 ");
							sqlDevFour.append("or a.abnormaltype = 51 ");
						}
					} else if ("30112".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 52 ");
							sqlDevTwo.append("or a.abnormaltype = 52 ");
							sqlDevThree.append("or a.abnormaltype =52 ");
							sqlDevFour.append("or a.abnormaltype = 52 ");
						}
					} else if ("30113".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 53 ");
							sqlDevTwo.append("or a.abnormaltype = 53 ");
							sqlDevThree.append("or a.abnormaltype =53 ");
							sqlDevFour.append("or a.abnormaltype = 53 ");
						}
					} else if ("3005".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlAreaOne.append("or b.errorReason = 11 ");
							sqlAreaTwo.append("or b.errorReason = 11 ");
							sqlAreaThree.append("or b.errorReason = 11 ");
							sqlAreaFour.append("or b.errorReason = 11 ");
						}
					} else if ("3006".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 14 ");
							sqlDevTwo.append("or a.abnormaltype = 14 ");
							sqlDevThree.append("or a.abnormaltype = 14 ");
							sqlDevFour.append("or a.abnormaltype = 14 ");
						}
					} else if ("3007".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlAreaOne.append("or b.errorReason = 12 ");
							sqlAreaTwo.append("or b.errorReason = 12 ");
							sqlAreaThree.append("or b.errorReason = 12 ");
							sqlAreaFour.append("or b.errorReason = 12 ");
						}
					} else if ("3008".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 4 ");
							sqlDevTwo.append("or a.abnormaltype = 4 ");
							sqlDevThree.append("or a.abnormaltype = 4 ");
							sqlDevFour.append("or a.abnormaltype = 4 ");
						}
					} else if ("3009".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 10 ");
							sqlDevTwo.append("or a.abnormaltype = 10 ");
							sqlDevThree.append("or a.abnormaltype = 10 ");
							sqlDevFour.append("or a.abnormaltype = 10 ");

						}
					} else if ("30010".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 9 ");
							sqlDevTwo.append("or a.abnormaltype = 9 ");
							sqlDevThree.append("or a.abnormaltype = 9 ");
							sqlDevFour.append("or a.abnormaltype = 9 ");
						}
					} else if ("30011".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 6 ");
							sqlDevTwo.append("or a.abnormaltype = 6 ");
							sqlDevThree.append("or a.abnormaltype = 6 ");
							sqlDevFour.append("or a.abnormaltype = 6 ");
						}
					}else if ("30114".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlServiceOne.append("or b.errorcode = 108 ");
							sqlServiceTwo.append("or b.errorcode = 108 ");
							sqlServiceThree.append("or b.errorcode = 108 ");
							sqlServiceFour.append("or b.errorcode = 108 ");
						}
					}else if ("30115".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlServiceOne.append("or b.errorcode = 109 ");
							sqlServiceTwo.append("or b.errorcode = 109 ");
							sqlServiceThree.append("or b.errorcode = 109 ");
							sqlServiceFour.append("or b.errorcode = 109 ");
						}
					}else if ("30116".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlServiceOne.append("or b.errorcode = 110 ");
							sqlServiceTwo.append("or b.errorcode = 110 ");
							sqlServiceThree.append("or b.errorcode = 110 ");
							sqlServiceFour.append("or b.errorcode = 110 ");
						}
					}
					
				}

			}
			
			sqlAreaOne.append(") ");
			sqlDevOne.append(") ");
			sqlAreaTwo.append(") ");
			sqlDevTwo.append(") ");
			sqlAreaThree.append(") ");
			sqlDevThree.append(") ");
			sqlAreaFour.append(") ");
			sqlDevFour.append(") ");
			sqlServerOne.append(") ");
			sqlServiceOne.append(") ");
			sqlServerTwo.append(") ");
			sqlServiceTwo.append(") ");
			sqlServerThree.append(") ");
			sqlServiceThree.append(") ");
			sqlServerFour.append(") ");
			sqlServiceFour.append(") ");

			// , MapSerialTable as serial, MapSeriallostTable as seriallost
			// server--999set ---lanprot --pos --multimidia--check---forbbiden
			// handan -- fenglin ---jiangwang---zhangjiang

			try {
				// MessageResources msgResources = (MessageResources) this
				// .getServlet().getServletContext().getAttribute(
				// Globals.MESSAGES_KEY);
				Session session = HibernateSessionFactory.currentSession();
				
				double cycle = 5.0;
				double serverCycle = 5.0;
				double serviceCycle = 5.0;
				Query queryCycle = session
				.createQuery("from MapParamTable as param where param.parameter=:paramRefer " +
						"or param.parameter=:paramRefer1 or param.parameter=:paramRefer2");
				queryCycle.setString("paramRefer", "HeartInterval");
				queryCycle.setString("paramRefer1", "ServerExceptionCycle");
				queryCycle.setString("paramRefer2", "ServiceExceptionCycle");
				List listParam = queryCycle.list();
				Iterator iterParam = listParam.iterator();
				while (iterParam.hasNext()) {
					MapParamTable mapParamTable = (MapParamTable) iterParam.next();
					if("HeartInterval".equals(mapParamTable.getParameter())){
						cycle = mapParamTable.getValue().doubleValue();
					}else if("ServerExceptionCycle".equals(mapParamTable.getParameter())){
						serverCycle = mapParamTable.getValue().doubleValue();
					}else if("ServiceExceptionCycle".equals(mapParamTable.getParameter())){
						serviceCycle = mapParamTable.getValue().doubleValue();
					}
					
				}
				String s = String.valueOf(cycle * 60);
				String t = String.valueOf(serverCycle * 60);
				String v  = String.valueOf(serviceCycle * 60);
				int intCycle = Integer.parseInt(s.substring(0, s.indexOf('.')));
				int intServerCycle = Integer.parseInt(t.substring(0, t.indexOf('.')));
				int intServiceCylce = Integer.parseInt(v.substring(0, v.indexOf('.')));
				String checkTime = DateUtil.getNewTime(DateUtil.getNow(), -3600);
				String checkTime1 = DateUtil.getNewTime(DateUtil.getNow(),-intCycle);
				String checkTime2 = DateUtil.getNewTime(DateUtil.getNow(),-intServerCycle);
				String checkTime3 = DateUtil.getNewTime(DateUtil.getNow(), -intServiceCylce);
				
				
				String xmlOut = "";
				Query queryAreaOne = session.createQuery(sqlAreaOne.toString());
				queryAreaOne.setString("analysisTime", checkTime1);
				List listResAOne = queryAreaOne.list();
				Query queryDevOne = session.createQuery(sqlDevOne.toString());
				queryDevOne.setString("analysisTime", checkTime);
				List listResDOne = queryDevOne.list();
				Query queryServerOne = session.createQuery(sqlServerOne.toString());
				queryServerOne.setString("analysisTime", checkTime2);
				List listServerOne = queryServerOne.list();
				Query queryServiceOne = session.createQuery(sqlServiceOne.toString());
				queryServiceOne.setString("analysisTime", checkTime3);
				List listServiceOne = queryServiceOne.list();
				int handan = listResAOne.size() + listResDOne.size()+listServerOne.size() + listServiceOne.size();

				Query queryAreaTwo = session.createQuery(sqlAreaTwo.toString());
				queryAreaTwo.setString("analysisTime", checkTime1);
				List listResATwo = queryAreaTwo.list();
				Query queryDevTwo = session.createQuery(sqlDevTwo.toString());
				queryDevTwo.setString("analysisTime", checkTime);
				List listResDTwo = queryDevTwo.list();
				Query queryServerTwo = session.createQuery(sqlServerTwo.toString());
				queryServerTwo.setString("analysisTime", checkTime2);
				List listServerTwo = queryServerTwo.list();
				Query queryServiceTwo = session.createQuery(sqlServiceTwo.toString());
				queryServiceTwo.setString("analysisTime", checkTime3);
				List listServiceTwo = queryServiceTwo.list();
				int fenglin = listResATwo.size() + listResDTwo.size()+listServerTwo.size() + listServiceTwo.size();

				Query queryAreaThree = session.createQuery(sqlAreaThree
						.toString());
				queryAreaThree.setString("analysisTime", checkTime1);
				List listResAThree = queryAreaThree.list();
				Query queryDevThree = session.createQuery(sqlDevThree
						.toString());
				queryDevThree.setString("analysisTime", checkTime);
				List listResDThree = queryDevThree.list();
				Query queryServerThree= session.createQuery(sqlServerThree.toString());
				queryServerThree.setString("analysisTime", checkTime2);
				List listServerThree = queryServerThree.list();
				Query queryServiceThree = session.createQuery(sqlServiceThree.toString());
				queryServiceThree.setString("analysisTime", checkTime3);
				List listServiceThree = queryServiceThree.list();
				int jiangwan = listResAThree.size() + listResDThree.size()+listServerThree.size() + listServiceThree.size();

				Query queryAreaFour = session.createQuery(sqlAreaFour
						.toString());
				queryAreaFour.setString("analysisTime", checkTime1);
				List listResAFour = queryAreaFour.list();
				Query queryDevFour = session.createQuery(sqlDevFour.toString());
				queryDevFour.setString("analysisTime", checkTime);
				List listResDFour = queryDevFour.list();
				Query queryServerFour = session.createQuery(sqlServerFour.toString());
				queryServerFour.setString("analysisTime", checkTime2);
				List listServerFour = queryServerFour.list();
				Query queryServiceFour = session.createQuery(sqlServiceFour.toString());
				queryServiceFour.setString("analysisTime", checkTime3);
				List listServiceFour = queryServiceFour.list();
				int zhangjiang = listResAFour.size() + listResDFour.size()+listServerFour.size() + listServiceFour.size();

				// user exist
				xmlOut = XMLGenerateUtil.SpecialXmlGenerate(handan, fenglin,
						zhangjiang, jiangwan);

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
