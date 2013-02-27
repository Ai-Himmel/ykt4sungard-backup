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
		// 判断信息
		if (httpSession.getAttribute("userLogin") != null) {
			request.setCharacterEncoding("GBK");
			// String DEVICE_EXCEPTION = request
			// .getParameter("Item_DEVICE_EXCEPTION");
			// String SERI_EXCEPTION =
			// request.getParameter("Item_SERI_EXCEPTION");
			// String LARGE_EXCEPTION = request
			// .getParameter("Item_LARGE_EXCEPTION");
			// String MID_EXCEPTION =
			// request.getParameter("Item_MID_EXCEPTION");
			// String BSHEETVER_EXCEPTION = request
			// .getParameter("Item_BSHEETVER_EXCEPTION");
			// String OTHER_EXCEPTION = request
			// .getParameter("Item_OTHER_EXCEPTION");
			// // String SERI_LOSS = request.getParameter("Item_SERI_LOSS");
			// // String SUPRESS_EXCEPTION =
			// // request.getParameter("Item_SUPRESS_EXCEPTION");
			// String UNCHECK_SERI = request.getParameter("Item_UNCHECK_SERI");
			// String REVERSE_SERI = request.getParameter("Item_REVERSE_SERI");
			// String BSHEETVER_ERROR = request
			// .getParameter("Item_BSHEETVER_ERROR");
			// String SETTIME_ERROR =
			// request.getParameter("Item_SETTIME_ERROR");
			// String SHORTTIME_MUTI_COMSUMPTION = request
			// .getParameter("Item_SHORTTIME_MUTI_COMSUMPTION");

			StringBuffer sqlAreaOne = new StringBuffer();
			StringBuffer sqlAreaTwo = new StringBuffer();
			StringBuffer sqlAreaThree = new StringBuffer();
//			StringBuffer sqlAreaFour = new StringBuffer();
			StringBuffer sqlDevOne = new StringBuffer();
			StringBuffer sqlDevTwo = new StringBuffer();
			StringBuffer sqlDevThree = new StringBuffer();
//			StringBuffer sqlDevFour = new StringBuffer();
			sqlAreaOne
					.append("select distinct(b.id.deviceId) as handan from MapDeviceTable as b where b.id.analysisTime>=:analysisTime and (1<>1 ");
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
			}
			sqlAreaOne.append(") and (1<>1 ");
			sqlDevOne.append(") and (1<>1 ");

			sqlAreaTwo
					.append("select distinct(b.id.deviceId) as fenglin from MapDeviceTable as b where b.id.analysisTime>=:analysisTime and (1<>1 ");
			sqlDevTwo
					.append(
							"select distinct(a.id.deviceId) as fenglin from MapSerialexceptTable as a,TPifDevice as b,MapSetsTable as c ")
					.append(
							"where a.id.analysisTime>=:analysisTime and  a.id.deviceId = b.devphy999Id and a.id.deviceId = c.setsid and (1<>1 ");
			List listAreaTwo = GetAreaCodeTimelyAction.getInstance()
					.returnListAfterCheckTime(2);

			for (int i = 0; i < listAreaTwo.size(); i++) {
				temp = listAreaTwo.get(i).toString();
				sqlAreaTwo.append(" or b.area=" + temp);
				sqlDevTwo.append(" or b.area=" + temp);
			}
			sqlAreaTwo.append(") and (1<>1 ");
			sqlDevTwo.append(") and (1<>1 ");

			sqlAreaThree
					.append("select distinct(b.id.deviceId) as jiangwan from MapDeviceTable as b where b.id.analysisTime>=:analysisTime and (1<>1 ");
			sqlDevThree
					.append(
							"select distinct(a.id.deviceId) as jiangwan from MapSerialexceptTable as a,TPifDevice as b,MapSetsTable as c ")
					.append(
							"where a.id.analysisTime>=:analysisTime and  a.id.deviceId = b.devphy999Id and a.id.deviceId = c.setsid and (1<>1 ");
			List listAreaThree = GetAreaCodeTimelyAction.getInstance()
					.returnListAfterCheckTime(3);

			for (int i = 0; i < listAreaThree.size(); i++) {
				temp = listAreaThree.get(i).toString();
				sqlAreaThree.append(" or b.area=" + temp);
				sqlDevThree.append(" or b.area=" + temp);
			}
			sqlAreaThree.append(") and (1<>1 ");
			sqlDevThree.append(") and (1<>1 ");

//			sqlAreaFour
//					.append("select distinct(b.id.deviceId) as zhangjiang from MapDeviceTable as b where b.id.analysisTime>=:analysisTime and (1<>1 ");
//			sqlDevFour
//					.append(
//							"select distinct(a.id.deviceId) as zhangjiang from MapSerialexceptTable as a,TPifDevice as b,MapSetsTable as c ")
//					.append(
//							"where a.id.analysisTime>=:analysisTime and a.id.deviceId = b.devphy999Id and a.id.deviceId = c.setsid and (1<>1 ");
//			List listAreaFour = GetAreaCodeTimelyAction.getInstance()
//					.returnListAfterCheckTime(3);
//
//			for (int i = 0; i < listAreaFour.size(); i++) {
//				temp = listAreaFour.get(i).toString();
//				sqlAreaFour.append(" or b.area=" + temp);
//				sqlDevFour.append(" or b.area=" + temp);
//			}
//			sqlAreaFour.append(")");
//			sqlDevFour.append(")");
			// 3001=设备异常
			// 3002=流水突变
			// 3003=大额不正常流水
			// 3004=黑卡消费
			// 3005=黑名单版本不正确
			// 3006=短期多笔消费
			// 3007=设备时钟错误
			// 3008=中途拔卡流水
			// 3009=冲正流水
			// 30010=未入账流水
			// 30011=其他异常流水
			// 3011=设备脱机
			// 3012=CPU使用率预警
			// 3013=内存使用率预警
			// 3014=硬盘使用率预警
			// 3015=发生时间突变
			// 3016=出入卡金额突变
			// 3017=设备号不存在
			// 3018=重复流水
			// 3019=大额消费（天）
			// 30110=大额消费（单笔）
			// 30111=黑卡继续消费
			// 30112=白卡不能消费
			// 30113=黑卡标记消费
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
						}

					} else if ("3012".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlAreaOne.append("or (b.errorReason = 102) ");
							sqlAreaTwo.append("or (b.errorReason = 102) ");
							sqlAreaThree.append("or (b.errorReason = 102) ");
						}

					} else if ("3013".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlAreaOne.append("or (b.errorReason = 103) ");
							sqlAreaTwo.append("or (b.errorReason = 103) ");
							sqlAreaThree.append("or (b.errorReason = 103) ");
						}

					} else if ("3014".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlAreaOne.append("or (b.errorReason = 104) ");
							sqlAreaTwo.append("or (b.errorReason = 104) ");
							sqlAreaThree.append("or (b.errorReason = 104) ");
						}

					} else if ("3015".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or (a.abnormaltype =201) ");
							sqlDevTwo.append("or (a.abnormaltype  =201) ");
							sqlDevThree.append("or (a.abnormaltype  =201) ");
//							sqlDevFour.append("or (a.abnormaltype  =201) ");
						}

					} else if ("3016".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or (a.abnormaltype =203) ");
							sqlDevTwo.append("or (a.abnormaltype =203) ");
							sqlDevThree.append("or (a.abnormaltype =203) ");
//							sqlDevFour.append("or (a.abnormaltype =203) ");
						}

					} else if ("3017".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or (a.abnormaltype = 204) ");
							sqlDevTwo.append("or (a.abnormaltype = 204) ");
							sqlDevThree.append("or (a.abnormaltype = 204) ");
//							sqlDevFour.append("or (a.abnormaltype = 204) ");
						}

					} else if ("3018".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or (a.abnormaltype = 205) ");
							sqlDevTwo.append("or (a.abnormaltype = 205) ");
							sqlDevThree.append("or (a.abnormaltype = 205) ");
//							sqlDevFour.append("or (a.abnormaltype = 205) ");
						}

					} else if ("3019".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 3 ");
							sqlDevTwo.append("or a.abnormaltype = 3 ");
							sqlDevThree.append("or a.abnormaltype = 3 ");
//							sqlDevFour.append("or a.abnormaltype = 3 ");
						}
					} else if ("30110".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 15 ");
							sqlDevTwo.append("or a.abnormaltype = 15 ");
							sqlDevThree.append("or a.abnormaltype = 15 ");
//							sqlDevFour.append("or a.abnormaltype = 15 ");
						}
					} else if ("30111".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 51 ");
							sqlDevTwo.append("or a.abnormaltype = 51 ");
							sqlDevThree.append("or a.abnormaltype =51 ");
//							sqlDevFour.append("or a.abnormaltype = 51 ");
						}
					} else if ("30112".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 52 ");
							sqlDevTwo.append("or a.abnormaltype = 52 ");
							sqlDevThree.append("or a.abnormaltype =52 ");
//							sqlDevFour.append("or a.abnormaltype = 52 ");
						}
					} else if ("30113".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 53 ");
							sqlDevTwo.append("or a.abnormaltype = 53 ");
							sqlDevThree.append("or a.abnormaltype =53 ");
//							sqlDevFour.append("or a.abnormaltype = 53 ");
						}
					} else if ("3005".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlAreaOne.append("or b.errorReason = 11 ");
							sqlAreaTwo.append("or b.errorReason = 11 ");
							sqlAreaThree.append("or b.errorReason = 11 ");
//							sqlAreaFour.append("or b.errorReason = 11 ");
						}
					} else if ("3006".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 14 ");
							sqlDevTwo.append("or a.abnormaltype = 14 ");
							sqlDevThree.append("or a.abnormaltype = 14 ");
//							sqlDevFour.append("or a.abnormaltype = 14 ");
						}
					} else if ("3007".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlAreaOne.append("or b.errorReason = 12 ");
							sqlAreaTwo.append("or b.errorReason = 12 ");
							sqlAreaThree.append("or b.errorReason = 12 ");
//							sqlAreaFour.append("or b.errorReason = 12 ");
						}
					} else if ("3008".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 4 ");
							sqlDevTwo.append("or a.abnormaltype = 4 ");
							sqlDevThree.append("or a.abnormaltype = 4 ");
//							sqlDevFour.append("or a.abnormaltype = 4 ");
						}
					} else if ("3009".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 10 ");
							sqlDevTwo.append("or a.abnormaltype = 10 ");
							sqlDevThree.append("or a.abnormaltype = 10 ");
//							sqlDevFour.append("or a.abnormaltype = 10 ");

						}
					} else if ("30010".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 9 ");
							sqlDevTwo.append("or a.abnormaltype = 9 ");
							sqlDevThree.append("or a.abnormaltype = 9 ");
//							sqlDevFour.append("or a.abnormaltype = 9 ");
						}
					} else if ("30011".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 6 ");
							sqlDevTwo.append("or a.abnormaltype = 6 ");
							sqlDevThree.append("or a.abnormaltype = 6 ");
//							sqlDevFour.append("or a.abnormaltype = 6 ");
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

			// , MapSerialTable as serial, MapSeriallostTable as seriallost
			// server--999set ---lanprot --pos --multimidia--check---forbbiden
			// handan -- fenglin ---jiangwang---zhangjiang

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
				Query queryAreaOne = session.createQuery(sqlAreaOne.toString());
				queryAreaOne.setString("analysisTime", checkTime1);
				// queryAreaOne.setString("analysisTime", "20051113000000");
				List listResAOne = queryAreaOne.list();
				Query queryDevOne = session.createQuery(sqlDevOne.toString());
				queryDevOne.setString("analysisTime", checkTime);
				// queryDevOne.setString("analysisTime", "20051113000000");
				List listResDOne = queryDevOne.list();
				int baoshan = listResAOne.size() + listResDOne.size();

				Query queryAreaTwo = session.createQuery(sqlAreaTwo.toString());
				queryAreaTwo.setString("analysisTime", checkTime1);
				List listResATwo = queryAreaTwo.list();
				Query queryDevTwo = session.createQuery(sqlDevTwo.toString());
				queryDevTwo.setString("analysisTime", checkTime);
				List listResDTwo = queryDevTwo.list();
				int yanchang = listResATwo.size() + listResDTwo.size();

				Query queryAreaThree = session.createQuery(sqlAreaThree
						.toString());
				queryAreaThree.setString("analysisTime", checkTime1);
				List listResAThree = queryAreaThree.list();
				Query queryDevThree = session.createQuery(sqlDevThree
						.toString());
				queryDevThree.setString("analysisTime", checkTime);
				List listResDThree = queryDevThree.list();
				int jiading = listResAThree.size() + listResDThree.size();

//				Query queryAreaFour = session.createQuery(sqlAreaFour
//						.toString());
//				queryAreaFour.setString("analysisTime", checkTime1);
//				List listResAFour = queryAreaFour.list();
//				Query queryDevFour = session.createQuery(sqlDevFour.toString());
//				queryDevFour.setString("analysisTime", checkTime);
//				List listResDFour = queryDevFour.list();
//				int zhangjiang = listResAFour.size() + listResDFour.size();

				// user exist
				xmlOut = XMLGenerateUtil.SpecialXmlGenerate(baoshan, yanchang,
						jiading);

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
