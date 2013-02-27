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
		// �ж���Ϣ
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

			StringBuffer sqlDevOne = new StringBuffer();

			sqlAreaOne
					.append("select distinct(b.id.deviceId)  handan from MapDeviceTable  b where b.id.analysisTime>=:analysisTime and (1<>1 ");
			sqlDevOne
					.append(
							"select distinct(a.id.deviceId)  handan from MapSerialexceptTable  a,TPifDevice  b,MapSetsTable  c ")
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



		
			// 3001=�豸�쳣
			// 3002=��ˮͻ��
			// 3003=��������ˮ
			// 3004=�ڿ�����
			// 3005=�������汾����ȷ
			// 3006=���ڶ������
			// 3007=�豸ʱ�Ӵ���
			// 3008=��;�ο���ˮ
			// 3009=������ˮ
			// 30010=δ������ˮ
			// 30011=�����쳣��ˮ
			// 3011=�豸�ѻ�
			// 3012=CPUʹ����Ԥ��
			// 3013=�ڴ�ʹ����Ԥ��
			// 3014=Ӳ��ʹ����Ԥ��
			// 3015=����ʱ��ͻ��
			// 3016=���뿨���ͻ��
			// 3017=�豸�Ų�����
			// 3018=�ظ���ˮ
			// 3019=������ѣ��죩
			// 30110=������ѣ����ʣ�
			// 30111=�ڿ���������
			// 30112=�׿���������
			// 30113=�ڿ��������
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


						}

					} else if ("3012".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlAreaOne.append("or (b.errorReason = 102) ");


						}

					} else if ("3013".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlAreaOne.append("or (b.errorReason = 103) ");


						}

					} else if ("3014".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlAreaOne.append("or (b.errorReason = 104) ");


						}

					} else if ("3015".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or (a.abnormaltype =201) ");


						}

					} else if ("3016".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or (a.abnormaltype =203) ");


						}

					} else if ("3017".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or (a.abnormaltype = 204) ");


						}

					} else if ("3018".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or (a.abnormaltype = 205) ");
	

						}

					} else if ("3019".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 3 ");
	

						}
					} else if ("30110".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 15 ");
		

						}
					} else if ("30111".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 51 ");
	

						}
					} else if ("30112".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 52 ");
		

						}
					} else if ("30113".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 53 ");
	
						}
					} else if ("3005".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlAreaOne.append("or b.errorReason = 11 ");
		

						}
					} else if ("3006".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 14 ");
		

						}
					} else if ("3007".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlAreaOne.append("or b.errorReason = 12 ");
	

						}
					} else if ("3008".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 4 ");
			

						}
					} else if ("3009".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 10 ");



						}
					} else if ("30010".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 9 ");


						}
					} else if ("30011".equals(name.substring(5))) {
						if ("1".equals(value)) {
							sqlDevOne.append("or a.abnormaltype = 6 ");
		

						}
					}
				}

			}
			sqlAreaOne.append(") ");
			sqlDevOne.append(") ");

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
				.createQuery("from MapParamTable  param where param.parameter=:paramRefer");
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
				int ligong = listResAOne.size() + listResDOne.size();


				// user exist
				xmlOut = XMLGenerateUtil.SpecialXmlGenerate(ligong);

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
