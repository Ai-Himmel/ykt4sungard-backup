/**
 * 
 */
package com.kingstargroup.ecard.portlet.advquery.action;

import java.util.Collections;
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

import com.kingstargroup.ecard.portlet.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawBarByTypeMap;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawTimeSeries;
import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.ErrorInfo;
import com.kingstargroup.ecard.util.GetListResultStat;
import com.kingstargroup.ecard.util.GetProperty;
import com.kingstargroup.ecard.util.SortListByResult;
import com.liferay.util.servlet.SessionErrors;

/**
 * �����������ͳ��
 * 
 * @author Administrator
 * 
 */
public class QueryAllConsumeStatAction extends Action {
	/**
	 * Logger for this class
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		QueryAllConsumeStatActionExecution exec = new QueryAllConsumeStatActionExecution();
		ActionForward returnActionForward = exec.execute(mapping, form,
				request, response);
		return returnActionForward;
	}

	private class QueryAllConsumeStatActionExecution {

		// ��ʼ���ڣ��·ݣ��ܣ�
		private String beginDate;
		// �������ڣ��·ݣ��ܣ�
		private String endDate;

		// ����ͷ��ʾ�����ڣ��·ݣ����ڵȣ�
		private String statTypeShow = "";
		// ���ڷ�Χ��ʾ
		private StringBuffer dateRange = new StringBuffer("");
		// ͳ������
		private String statType;
		// ������ʾ��Ϣ
		private String yLabel = "";
		private String yLabel2 = "";
		// ��λ
		private int dataUnit = 1;
		private int dataUnit2 = 1;
		// X�����ڿ̶�
		private int dateUnit = 1;
		// ���ز�ѯ���
		private List weekResult = null;
		private String xData = "";
		// �Զ���ͼ����ʾҪ����Ĳ���
		// ��ʾ�Զ�����ɫ
		private boolean showCustColor = false;
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

		private String showType;// ѡ���ͼ����ʾ����
		private String picType = "";

		// ����ͼ��Ҫ����Ĳ���
		String accType[] = { "���ѽ��", "����ѽ��" };
		String accType2[] = { "����ѽ��(�Ŵ�)" };
		String dataType = "float";
		String columnTitle[] = { "tradeamt", "mngamt" };
		String columnTitle2[] = { "mngamt" };
		ActionServlet servlet = QueryAllConsumeStatAction.this.servlet;

		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
				throws Exception {
			response.setCharacterEncoding("UTF-8");
			DynaActionForm allconsumeform = (DynaActionForm) form;
			String querytype = allconsumeform.getString("querytype");
			if(!"".equals(querytype)){
				allconsumeform.set("querytype", "");
				return mapping.findForward("errortest");	
			}
			// ��ʼ����
			beginDate = allconsumeform.getString("allconsume_begindate");
			// ��������
			endDate = allconsumeform.getString("allconsume_enddate");
			// ͳ������Ҫ����Ĳ����������ڻ��·�ͳ�ƣ�
			statType = allconsumeform.getString("statType");
			// ѡ���ͼ����ʾ����
			showType = allconsumeform.getString("showType");

			if (("".equals(beginDate)) || ("".equals(endDate))) {
				SessionErrors.add(request, EcardConstants.ALLCONSUME_ERROR_EXIST, ErrorInfo
						.getErrorTip(statType, beginDate, endDate));
				return mapping.findForward("errortest");
			}

			setInit(request);
			// �ж��Ƿ�������ͼ��ʾ
			String errtip = ErrorInfo.DateRangeJudeg(showType, statType,
					beginDate, endDate, request);
			if (!"".equals(errtip)) {
				SessionErrors.add(request, EcardConstants.ALLCONSUME_ERROR_EXIST, errtip);
				return mapping.findForward("errortest");
			}

			List result = AdvqueryServiceUtil.getAllConsumeStat(beginDate,
					endDate, statType);
			if (result.isEmpty()) {
				SessionErrors.add(request, EcardConstants.ALLCONSUME_ERROR_EXIST, ErrorInfo
						.getErrorTip(statType, beginDate, endDate));
				return mapping.findForward("errortest");
			}
			Collections.sort(result, new SortListByResult("balance_date"));

			dateUnit = result.size() / 8;
			statTypeReturn(request, result);

			// ����Ҫ��ʾ��ͼ��������ͼ��
			showTypeResult();

			request.setAttribute("pictype", picType);
			request.setAttribute("ylabel", yLabel);
			request.setAttribute("ylabel2", yLabel2);
			request.setAttribute("stattype", statType);
			request.setAttribute("pictype", picType);
			request.setAttribute("daterange", dateRange.toString());
			request.setAttribute("stattypeshow", statTypeShow);
			drawPic(request);
			ActionForward returnActionForward = mapping
					.findForward("allconsume_queryresult");
			return returnActionForward;
		}

		private void setInit(HttpServletRequest request) {
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

				statTypeShow = GetProperty.getProperties("title.month",
						this.servlet.getServletContext());
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

		/**
		 * ����ѡ���ͳ�����ͻ���ͼ��
		 * 
		 * @param request
		 * @param result
		 */
		private void statTypeReturn(HttpServletRequest request, List result) {

			if ("bydate".equals(statType)) {
				yLabel = new GetListResultStat().getYLabelMoney(result,
						"tradeamt", dataType);
				dataUnit = new GetListResultStat().getUnitValue(result,
						"tradeamt", dataType);
				yLabel2 = new GetListResultStat().getYLabelMoney(result,
						"mngamt", dataType);
				dataUnit2 = new GetListResultStat().getUnitValue(result,
						"mngamt", dataType);
				request.setAttribute("result", result);
				xData = "balance_date";
				if ("line".equals(showType)) {
					request.setAttribute("allConsumeStatChart",
							new DrawTimeSeries(result, columnTitle, xData,
									dataType, accType, dataUnit)
									.getTimeSeriesProducer());

					request.setAttribute("allConsumeStatChart2",
							new DrawTimeSeries(result, columnTitle2, xData,
									dataType, accType2, dataUnit2)
									.getTimeSeriesProducer());

				} else {
					request.setAttribute("allConsumeStatChart",
							new DrawBarByTypeMap(result, accType, xData,
									dataType, columnTitle, dataUnit)
									.getDataProducer());
				}
			} else if ("bymonth".equals(statType)) {
				yLabel = new GetListResultStat().getYLabelMoney(result,
						"tradeamt", dataType);
				dataUnit = new GetListResultStat().getUnitValue(result,
						"tradeamt", dataType);
				request.setAttribute("result", result);
				xData = "balance_date";
				request.setAttribute("allConsumeStatChart",
						new DrawBarByTypeMap(result, accType, xData, dataType,
								columnTitle, dataUnit).getDataProducer());

				showTextAxis = ErrorInfo.showTextAxis(result);
			} else if ("byweek".equals(statType)) {
				weekResult = new GetListResultStat().getListByWeek(result,
						beginDate, endDate);
				Collections.sort(weekResult, new SortListByResult(
						"balance_date"));
				xData = "yearweek";
				yLabel = new GetListResultStat().getYLabelMoney(weekResult,
						"tradeamt", dataType);
				dataUnit = new GetListResultStat().getUnitValue(weekResult,
						"tradeamt", dataType);
				request.setAttribute("result", weekResult);
				request.setAttribute("allConsumeStatChart",
						new DrawBarByTypeMap(weekResult, accType, xData,
								dataType, columnTitle, dataUnit)
								.getDataProducer());

				showTextAxis = ErrorInfo.showTextAxis(weekResult);
			}

		}

		/**
		 * ����ѡ���ͼ����������ͼ������
		 * 
		 */
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
}
