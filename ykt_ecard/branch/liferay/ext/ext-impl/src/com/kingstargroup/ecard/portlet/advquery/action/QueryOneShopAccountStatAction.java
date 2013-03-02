/**
 * 
 */
package com.kingstargroup.ecard.portlet.advquery.action;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionServlet;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.hibernate.shop.TShop;
import com.kingstargroup.ecard.portlet.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawBarByTypeMap;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawTimeSeries;
import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.portlet.shop.service.ShopServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.ErrorInfo;
import com.kingstargroup.ecard.util.GetListResultStat;
import com.kingstargroup.ecard.util.GetProperty;
import com.kingstargroup.ecard.util.SortListByResult;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.servlet.SessionErrors;

/**
 * ���̻�Ӫҵ���ͳ��
 * 
 * @author Administrator
 * 
 */
public class QueryOneShopAccountStatAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		QueryOneShopAccountStatActionExecution exec = new QueryOneShopAccountStatActionExecution();
		return exec.execute(mapping, form, request, response);
	}

	private class QueryOneShopAccountStatActionExecution {
		private int shopId;
		private String beginDate;
		private String endDate;
		private StringBuffer dateRange = new StringBuffer(200);
		private String statTypeShow = "";
		// ���ز�ѯ���
		private List weekResult = null;
		private String showType;
		private String picType = "";
		// ��λ
		private int dataUnit = 1;
		private int dataUnit2 = 1;
		private int dateUnit = 1;
		// ������ʾ��Ϣ
		private String yLabel = "";
		private String yLabel2 = "";
		private String statType;
		// ����ͼ��Ҫ����Ĳ���
		private String accType[] = { "�������", "����ѽ��" };
		private String accType2[] = { "����ѽ��(�Ŵ�)" };
		private String xData = "";
		private String dataType = "float";
		private String columnTitle[] = { "tradeamt", "mngamt" };
		private String columnTitle2[] = { "mngamt" };

		// �Զ���ͼ����ʾҪ����Ĳ���
		// ��ʾ�Զ�����ɫ
		private boolean showCustColor = true;
		// ��ʾ���������ֵ���ת����
		private boolean showTextAxis = true;
		// ��ʾBarͼ���ϵ�����
		private boolean showLabel = false;
		// ��ʾ�Զ���ͼ������ɫ
		private boolean showBackgroundColor = true;
		// ��ʾ������
		private boolean showOutLine = true;
		// ��ʾ������
		private boolean showGrid = true;
		ActionServlet servlet = QueryOneShopAccountStatAction.this.servlet;

		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
				throws Exception {
			
			response.setCharacterEncoding("UTF-8");
			DynaActionForm oneshopaccountform = (DynaActionForm) form;
			Long realUserId = (Long) request.getSession().getAttribute(
					WebKeys.USER_ID);
			List shoplist = ShopServiceUtil.getShopList(realUserId);
			request.setAttribute("shopList", shoplist);
			String querytype = oneshopaccountform.getString("querytype");
			if(!"".equals(querytype)){
				oneshopaccountform.set("querytype", "");
				return mapping.findForward("errortest");	
			}
			
			if("".equals(oneshopaccountform.getString("shopid"))){
				SessionErrors.add(request, EcardConstants.ONESHOPACCOUNT_ERROR_EXIST,"��ѡ���̻����ٲ�ѯ");
				return mapping.findForward("errortest");
			}
			// ��ѯҪ����Ĳ���
			shopId = Integer.parseInt(oneshopaccountform.getString("shopid"));
			// ��ʼ����
			beginDate = oneshopaccountform.getString("oneshopaccount_begindate");
			// ��������
			endDate = oneshopaccountform.getString("oneshopaccount_enddate");
			// ѡ���ͼ����ʾ����
			showType = oneshopaccountform.getString("showType");

			// ͳ�Ʒ�ʽҪ����Ĳ���
			statType = oneshopaccountform.getString("statType");
			if (("".equals(beginDate)) || ("".equals(endDate))) {
				SessionErrors.add(request, EcardConstants.ONESHOPACCOUNT_ERROR_EXIST,
						ErrorInfo.getErrorTip(statType, beginDate, endDate));
				return mapping.findForward("errortest");
			}

			setInit(request);

			// �ж��Ƿ�������ͼ��ʾ
			String errtip = ErrorInfo.DateRangeJudeg(showType, statType,
					beginDate, endDate, request);
			if (!"".equals(errtip)) {
				SessionErrors.add(request, EcardConstants.ONESHOPACCOUNT_ERROR_EXIST, errtip);
				return mapping.findForward("errortest");
			}
			
			List result = AdvqueryServiceUtil.getOneAccountStat(shopId,
					beginDate, endDate, statType);
			if (result.isEmpty()) {
				SessionErrors.add(request, EcardConstants.ONESHOPACCOUNT_ERROR_EXIST,
						getShopName(shopId)
								+ ":"
								+ ErrorInfo.getErrorTip(statType, beginDate,
										endDate));
				return mapping.findForward("errortest");
			}


			dateUnit = result.size() / 9;
			statTypeResult(request, result);
			// ����Ҫ��ʾ��ͼ��������ͼ��
			showTypeResult();

			request.setAttribute("pictype", picType);
			request.setAttribute("ylabel2", yLabel2);
			request.setAttribute("stattype", statType);
			request.setAttribute("ylabel", yLabel);
			request.setAttribute("daterange", dateRange.toString());
			request.setAttribute("shopname", getShopName(shopId));
			request.setAttribute("stattypeshow", statTypeShow);
			drawPic(request);
			return mapping.findForward("oneshopaccount_queryresult");

		}

		private void setInit(HttpServletRequest request) {
			HttpSession session = request.getSession();
			session.setAttribute("shopid", Integer.valueOf(String
					.valueOf(shopId)));

			if ("bydate".equals(statType)) {
				beginDate = DateUtil.reFormatTime(beginDate);
				endDate = DateUtil.reFormatTime(endDate);
				statTypeShow = GetProperty.getProperties("title.date", servlet
						.getServletContext());
				dateRange.append(
						GetProperty.getProperties("query.show.date", servlet
								.getServletContext())).append(beginDate)
						.append("-").append(endDate);
			} else if ("bymonth".equals(statType)) {
				beginDate = DateUtil.getMonth(beginDate);
				endDate = DateUtil.getMonth(endDate);
				statTypeShow = GetProperty.getProperties("title.month", servlet
						.getServletContext());
				dateRange.append(
						GetProperty.getProperties("query.show.month", servlet
								.getServletContext())).append(beginDate)
						.append("-").append(endDate);
			} else if ("byweek".equals(statType)) {
				beginDate = DateUtil.reFormatTime(beginDate);
				endDate = DateUtil.reFormatTime(endDate);
				statTypeShow = GetProperty.getProperties("title.week", servlet
						.getServletContext());
				dateRange.append(
						GetProperty.getProperties("query.show.week", servlet
								.getServletContext())).append(beginDate)
						.append("-").append(endDate);
			}
		}

		private void statTypeResult(HttpServletRequest request, List result) {
			try {
				if ("bydate".equals(statType)) {
					yLabel = new GetListResultStat().getYLabelMoney(result,
							"tradeamt", dataType);
					dataUnit = new GetListResultStat().getUnitValue(result,
							"tradeamt", dataType);
					yLabel2 = new GetListResultStat().getYLabelMoney(result,
							"mngamt", dataType);
					dataUnit2 = new GetListResultStat().getUnitValue(result,
							"mngamt", dataType);
					Collections.sort(result, new SortListByResult(
							"balance_date"));
					request.setAttribute("result", result);
					xData = "balance_date";
					if ("line".equals(showType)) {
						request.setAttribute("OneShopAccountStatChart",
								new DrawTimeSeries(result, columnTitle, xData,
										dataType, accType, dataUnit)
										.getTimeSeriesProducer());

						request.setAttribute("OneShopAccountStatChart2",
								new DrawTimeSeries(result, columnTitle2, xData,
										dataType, accType2, dataUnit2)
										.getTimeSeriesProducer());

					} else {
						request.setAttribute("OneShopAccountStatChart",
								new DrawBarByTypeMap(result, accType, xData,
										dataType, columnTitle, dataUnit)
										.getDataProducer());
					}
				} else if ("bymonth".equals(statType)) {
					Collections.sort(result, new SortListByResult(
							"balance_date"));
					request.setAttribute("result", result);
					yLabel = new GetListResultStat().getYLabelMoney(result,
							"tradeamt", dataType);
					dataUnit = new GetListResultStat().getUnitValue(result,
							"tradeamt", dataType);
					xData = "balance_date";
					request.setAttribute("OneShopAccountStatChart",
							new DrawBarByTypeMap(result, accType, xData,
									dataType, columnTitle, dataUnit)
									.getDataProducer());
					showTextAxis = ErrorInfo.showTextAxis(result);
				} else if ("byweek".equals(statType)) {
					weekResult = new GetListResultStat().getListByWeek(result,
							beginDate, endDate);
					Collections.sort(weekResult, new SortListByResult(
							"balance_date"));
					yLabel = new GetListResultStat().getYLabelMoney(weekResult,
							"tradeamt", dataType);
					dataUnit = new GetListResultStat().getUnitValue(weekResult,
							"tradeamt", dataType);
					xData = "yearweek";
					request.setAttribute("result", weekResult);
					request.setAttribute("OneShopAccountStatChart",
							new DrawBarByTypeMap(weekResult, accType, xData,
									dataType, columnTitle, dataUnit)
									.getDataProducer());
					showTextAxis = ErrorInfo.showTextAxis(weekResult);
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		}

		private void showTypeResult() {
			if ("line".equals(showType)) {
				if ("bydate".equals(statType)) {
					picType = GetProperty.getProperties("pic.timeseries",
							servlet.getServletContext());
				} else {
					picType = GetProperty.getProperties("pic.line", servlet
							.getServletContext());
				}
				showOutLine = false;
			} else if ("bar".equals(showType)) {
				picType = GetProperty.getProperties("pic.bar", servlet
						.getServletContext());
				showOutLine = true;
			} else if ("stack".equals(showType)) {
				picType = GetProperty.getProperties("pic.stack", servlet
						.getServletContext());
				showOutLine = true;
			}

		}

		private void drawPic(HttpServletRequest request) {
			if ("line".equals(showType)) {
				if ("bydate".equals(statType)) {
					request.setAttribute("dataColor", new CustomerDrawChart(
							showBackgroundColor, showCustColor, dateUnit)
							.getTimeSeriesPostProcessor());
				} else {
					request.setAttribute("dataColor", new CustomerDrawChart(
							showCustColor, showTextAxis, showLabel,
							showBackgroundColor, showOutLine, showGrid)
							.getChartPostProcessor());
				}
			} else if ("bar".equals(showType)) {
				request.setAttribute("dataColor", new CustomerDrawChart(
						showCustColor, showTextAxis, showLabel,
						showBackgroundColor, showOutLine, showGrid)
						.getChartPostProcessor());
			} else if ("stack".equals(showType)) {
				request.setAttribute("dataColor", new CustomerDrawChart(
						showCustColor, showTextAxis, showLabel,
						showBackgroundColor, showOutLine, showGrid)
						.getChartPostProcessor());
			}
		}
	}

	private String getShopName(int shopId) {
		String devName = "";
		List list = AdvqueryServiceUtil.getShopName(shopId);
		if (list != null) {
			Iterator iter = list.iterator();
			while (iter.hasNext()) {
				TShop row = (TShop) iter.next();
				devName = row.getShopname();
			}
		}
		return devName;
	}

}
