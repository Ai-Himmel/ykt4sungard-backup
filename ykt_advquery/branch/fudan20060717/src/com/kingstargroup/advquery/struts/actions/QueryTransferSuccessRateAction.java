package com.kingstargroup.advquery.struts.actions;

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

import com.kingstargroup.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.advquery.cewolf.DrawBarConfTypeMap;
import com.kingstargroup.advquery.cewolf.CustomerDrawLineChart;
import com.kingstargroup.advquery.cewolf.DrawTimeSeries;
import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.common.GetListResultStat;
import com.kingstargroup.advquery.common.GetProperty;
import com.kingstargroup.advquery.common.SortListByResult;
import com.kingstargroup.advquery.hibernate.util.ReportActiveUtil;

public class QueryTransferSuccessRateAction extends Action {

	/**
	 * 圈存成功率
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		QueryTransferSuccessRateActionExecution exec = new QueryTransferSuccessRateActionExecution();
		return exec.execute(mapping, form, request, response);
	}

	private class QueryTransferSuccessRateActionExecution {
		private String beginDate;

		private String endDate;

		private StringBuffer dateRange = new StringBuffer(200);

		private String statTypeShow = "";
		private String picType = "";
		// 返回查询结果
		private List weekResult = null;

		// 金额单位
		private int dataUnit = 1;

		private int dateUnit = 1;

		// Ｙ轴提示信息
		private String yLabel = "";

		private String statType;

		// 生成图片要传入的参数
		private String accType[] = { "圈存成功率" };

		private String xData = "";

		private String dataType = "float";

		private String showColumn = "rate";
		private String columnTitle[] = {"rate"};

		// 自定义图表显示要传入的参数
		// 设置曲线的透明度
		private boolean showAlpha = true;

		// 显示图形背景色
		private boolean showBackGround = true;
		
		private boolean showCustColor = true;

		// 横坐标的文字方向
		private boolean showTextAxis = true;

		// 显示坐标线
		private boolean showGrid = true;

		ActionServlet servlet = QueryTransferSuccessRateAction.this.servlet;

		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
				throws Exception {
			// 开始日期
			beginDate = request.getParameter("begindate");
			// 结束日期
			endDate = request.getParameter("enddate");
			statType = request.getParameter("statType");
			if (("".equals(beginDate)) || ("".equals(endDate))) {
				request.setAttribute("errorcont", new ErrorInfo().getErrorTip(
						statType, beginDate, endDate));
				return mapping.findForward("errortest");
			}

			setInit(request);

			List result = ReportActiveUtil.getTransferSuccessRate(
					beginDate, endDate, statType);
			if ((result.isEmpty()) || (result == null)) {
				request.setAttribute("errorcont", new ErrorInfo().getErrorTip(
						statType, beginDate, endDate));
				return mapping.findForward("errortest");
			}

			dateUnit = result.size()/9;
			statTypeResult(request, result);
			showTypeResult();
			request.setAttribute("ylabel", yLabel);
			request.setAttribute("pictype",picType);
			
			request.setAttribute("daterange", dateRange.toString());
			request.setAttribute("stattypeshow", statTypeShow);

			drawPic(request);
			return mapping.findForward("transfer_queryresult");

		}

		private void setInit(HttpServletRequest request) {
			HttpSession session = request.getSession();
			if ("bydate".equals(statType)) {
				beginDate = DateUtil.reFormatTime(request
						.getParameter("begindate"));
				endDate = DateUtil
						.reFormatTime(request.getParameter("enddate"));
				session.setAttribute("begindate53d", request
						.getParameter("begindate"));
				session.setAttribute("enddate53d", request
						.getParameter("enddate"));
				session.setAttribute("querytype53", "0");
				statTypeShow = GetProperty.getProperties("title.date", servlet
						.getServletContext());
				dateRange.append(
						GetProperty.getProperties("query.show.date", servlet
								.getServletContext())).append(beginDate)
						.append("-").append(endDate);
			} else if ("bymonth".equals(statType)) {
				beginDate = DateUtil
						.getMonth(request.getParameter("begindate"));
				endDate = DateUtil.getMonth(request.getParameter("enddate"));
				session.setAttribute("begindate53m", request
						.getParameter("begindate"));
				session.setAttribute("enddate53m", request
						.getParameter("enddate"));
				session.setAttribute("querytype53", "1");
				statTypeShow = GetProperty.getProperties("title.month", servlet
						.getServletContext());
				dateRange.append(
						GetProperty.getProperties("query.show.month", servlet
								.getServletContext())).append(beginDate)
						.append("-").append(endDate);
			} else if ("byweek".equals(statType)) {
				beginDate = DateUtil.reFormatTime(request
						.getParameter("begindate"));
				endDate = DateUtil
						.reFormatTime(request.getParameter("enddate"));
				session.setAttribute("begindate53w", request
						.getParameter("begindate"));
				session.setAttribute("enddate53w", request
						.getParameter("enddate"));
				// beginWeek = DateUtilExtend.getWeek(beginDate);
				// endWeek = DateUtilExtend.getWeek(endDate);
				statTypeShow = GetProperty.getProperties("title.week", servlet
						.getServletContext());
				dateRange.append(
						GetProperty.getProperties("query.show.week", servlet
								.getServletContext())).append(beginDate)
						.append("-").append(endDate);
			}
		}

		private void statTypeResult(HttpServletRequest request, List result) {
			if ("bydate".equals(statType)) {
				request.setAttribute("result", result);
				xData = "balance_date";
				yLabel = new GetListResultStat().getYLabelRate(result, "rate",
						dataType);
				dataUnit = new GetListResultStat().getUnitValue(result, "rate",
						dataType);
				request.setAttribute("transferChart",
						new DrawTimeSeries(result, columnTitle, xData,
								dataType, accType, dataUnit)
								.getTimeSeriesProducer());

				showTextAxis = new ErrorInfo().showTextAxis(result);
			} else if ("bymonth".equals(statType)) {
				request.setAttribute("result", result);
				xData = "balance_date";
				yLabel = new GetListResultStat().getYLabelRate(result, "rate",
						dataType);
				dataUnit = new GetListResultStat().getUnitValue(result, "rate",
						dataType);
				request.setAttribute("transferChart", new DrawBarConfTypeMap(
						result, accType, xData, dataType, showColumn, dataUnit)
						.getDataProducer());

				showTextAxis = new ErrorInfo().showTextAxis(result);
			} else if ("byweek".equals(statType)) {
				weekResult = new GetListResultStat().getListByWeek(result,
						beginDate, endDate);
				Collections.sort(weekResult, new SortListByResult(
						"balance_date"));
				yLabel = new GetListResultStat().getYLabelRate(weekResult,
						"rate", dataType);
				dataUnit = new GetListResultStat().getUnitValue(weekResult,
						"rate", dataType);
				xData = "yearweek";
				request.setAttribute("result", weekResult);
				request.setAttribute("transferChart", new DrawBarConfTypeMap(
						weekResult, accType, xData, dataType, showColumn,
						dataUnit).getDataProducer());

				showTextAxis = new ErrorInfo().showTextAxis(weekResult);
			}
		}
		private void showTypeResult(){
			if ("bydate".equals(statType)){
				picType = GetProperty.getProperties("pic.timeseries",servlet.getServletContext());
			}else{
				picType = GetProperty.getProperties("pic.line",servlet.getServletContext());
			}
		}
		private void drawPic(HttpServletRequest request){
			if ("bydate".equals(statType)){
				request.setAttribute("dataColor", new CustomerDrawChart(showBackGround,showCustColor,dateUnit)
						.getTimeSeriesPostProcessor());
			}else{
				request.setAttribute("dataColor", new CustomerDrawLineChart(
						showAlpha, showBackGround, showGrid, showTextAxis)
						.getChartPostProcessor());
			}
		}

	}
}
