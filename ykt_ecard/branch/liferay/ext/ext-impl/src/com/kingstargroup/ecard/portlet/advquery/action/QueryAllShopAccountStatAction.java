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
 * 商户整体账户变动情况，营业额，管理费金额
 * 
 * @author Administrator
 * 
 */
public class QueryAllShopAccountStatAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		QueryAllShopAccountStatActionExecution exec = new QueryAllShopAccountStatActionExecution();
		return exec.execute(mapping, form, request, response);
	}

	private class QueryAllShopAccountStatActionExecution {
		private String beginDate;
		private String endDate;
		private StringBuffer dateRange = new StringBuffer(200);
		private String statTypeShow = "";
		// 返回查询结果
		private List weekResult = null;
		private String showType;
		private String picType = "";
		// 金额单位
		private int dataUnit = 1;
		private int dateUnit = 1;
		private int dataUnit2 = 1;
		// Ｙ轴提示信息
		private String yLabel = "";
		private String yLabel2 = "";
		private String statType;

		// 绘制图形时要传入的参数
		private String accType[] = { "营业额", "管理费" };
		private String accType2[] = { "管理费(放大)" };
		private String xData = "";
		private String dataType = "float";
		private String columnTitle[] = { "tradeamt", "mngamt" };
		private String columnTitle2[] = { "mngamt" };

		// 自定义图表显示要传入的参数
		// 显示自定义颜色
		private boolean showCustColor = true;
		// 显示横坐标文字的旋转方向
		private boolean showTextAxis = true;
		// 显示Bar图标上的数字
		private boolean showLabel = false;
		// 显示自定义图表背景颜色
		private boolean showBackgroundColor = true;
		// 显示轮廓线
		private boolean showOutLine = false;
		// 显示网格线
		private boolean showGrid = true;

		ActionServlet servlet = QueryAllShopAccountStatAction.this.servlet;

		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
				throws Exception {
			response.setCharacterEncoding("UTF-8");
			DynaActionForm allshopaccountform = (DynaActionForm) form;
			String querytype = allshopaccountform.getString("querytype");
			if(!"".equals(querytype)){
				allshopaccountform.set("querytype", "");
				return mapping.findForward("errortest");	
			}
			// 开始日期
			beginDate = allshopaccountform.getString("allshopaccount_begindate");
			// 结束日期
			endDate = allshopaccountform.getString("allshopaccount_enddate");
			// 选择的图形显示类型
			showType = allshopaccountform.getString("showType");

			// 统计类型要传入的参数（按月统计或按日期统计）
			statType = allshopaccountform.getString("statType");
			if (("".equals(beginDate)) || ("".equals(endDate))) {
				SessionErrors.add(request, EcardConstants.ALLSHOPACCOUNT_ERROR_EXIST, ErrorInfo
						.getErrorTip(statType, beginDate, endDate));
				return mapping.findForward("errortest");
			}
			setInit(request);
			// 判断是否用曲线图显示
			String errtip = ErrorInfo.DateRangeJudeg(showType, statType,
					beginDate, endDate, request);
			if (!"".equals(errtip)) {
				SessionErrors.add(request, EcardConstants.ALLSHOPACCOUNT_ERROR_EXIST, errtip);
				return mapping.findForward("errortest");
			}
			List result = AdvqueryServiceUtil.getShopAccountChangeStat(
					beginDate, endDate, statType);
			if (result.isEmpty()) {
				SessionErrors.add(request, EcardConstants.ALLSHOPACCOUNT_ERROR_EXIST, ErrorInfo
						.getErrorTip(statType, beginDate, endDate));
				return mapping.findForward("errortest");
			}
			

			dateUnit = result.size() / 9;
			setTypeReturn(request, result);
			// 根据要显示的图形类别绘制图形
			showTypeResult();

			request.setAttribute("ylabel", yLabel);
			request.setAttribute("ylabel2", yLabel2);
			request.setAttribute("stattype", statType);
			request.setAttribute("pictype", picType);
			request.setAttribute("showtype", showType);
			request.setAttribute("daterange", dateRange.toString());
			request.setAttribute("stattypeshow", statTypeShow);

			drawPic(request);

			return mapping.findForward("allshopaccount_queryresult");

		}

		/**
		 * 初始化
		 * 
		 * @param request
		 */
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

		private void setTypeReturn(HttpServletRequest request, List result) {
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
					request.setAttribute("allShopAccountStatChart",
							new DrawTimeSeries(result, columnTitle, xData,
									dataType, accType, dataUnit)
									.getTimeSeriesProducer());

					request.setAttribute("allShopAccountStatChart2",
							new DrawTimeSeries(result, columnTitle2, xData,
									dataType, accType2, dataUnit2)
									.getTimeSeriesProducer());

				} else {
					request.setAttribute("allShopAccountStatChart",
							new DrawBarByTypeMap(result, accType, xData,
									dataType, columnTitle, dataUnit)
									.getDataProducer());
				}
			} else if ("bymonth".equals(statType)) {
				request.setAttribute("result", result);
				yLabel = new GetListResultStat().getYLabelMoney(result,
						"tradeamt", dataType);
				dataUnit = new GetListResultStat().getUnitValue(result,
						"tradeamt", dataType);
				xData = "balance_date";
				request.setAttribute("allShopAccountStatChart",
						new DrawBarByTypeMap(result, accType, xData, dataType,
								columnTitle, dataUnit).getDataProducer());
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
				request.setAttribute("allShopAccountStatChart",
						new DrawBarByTypeMap(weekResult, accType, xData,
								dataType, columnTitle, dataUnit)
								.getDataProducer());
				showTextAxis = ErrorInfo.showTextAxis(weekResult);
			}
		}

		/**
		 * 根据选择的图形类型设置图形属性
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
