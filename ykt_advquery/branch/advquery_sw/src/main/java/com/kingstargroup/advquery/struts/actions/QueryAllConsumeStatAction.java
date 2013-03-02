/**
 * 
 */
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
import com.kingstargroup.advquery.cewolf.DrawBarByTypeMap;
import com.kingstargroup.advquery.cewolf.DrawTimeSeries;
import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.common.GetListResultStat;
import com.kingstargroup.advquery.common.GetProperty;
import com.kingstargroup.advquery.common.SortListByResult;
import com.kingstargroup.advquery.hibernate.util.ReportShopBalanceUtil;

/**
 * 消费情况总体统计
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

		//开始日期（月份，周）
		private String beginDate;
		//结束日期（月份，周）
		private String endDate;
		
		//报表头显示（周期，月份，日期等）
		private String statTypeShow = "";
		//日期范围提示
		private StringBuffer dateRange = new StringBuffer("");
		//统计类型
		private String statType;
		// Ｙ轴提示信息
		private String yLabel = "";
		private String yLabel2 = "";
		//金额单位
		private int dataUnit = 1;
		private int dataUnit2 = 1;
		//X轴日期刻度
		private int dateUnit = 1;
		//返回查询结果
		private List weekResult = null;
		private String xData = "";
		// 自定义图表显示要传入的参数
		// 显示自定义颜色
		private boolean showCustColor = false;
		// 显示横坐标文字的旋转方向
		private boolean showTextAxis = true;
		// 显示Bar图标上的数字
		private boolean showLabel = false;
		// 显示自定义图表背景颜色
		private boolean showBackgroundColor = true;
		// 显示轮廓线
		private boolean showOutLine = true;
		// 显示网格线
		private boolean showGrid = true;
		
		private String showType;//选择的图形显示类型
		private String picType = "";
		
		// 绘制图表要传入的参数
		String accType[] = { "消费金额", "管理费金额" };			
		String accType2[] = { "管理费金额(放大)" };			
		String dataType = "float";
		String columnTitle[] = { "tradeamt", "mngamt" };
		String columnTitle2[] = { "mngamt" };
		ActionServlet servlet = QueryAllConsumeStatAction.this.servlet;
		
		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
			throws Exception{
			
			// 开始日期
			beginDate = request.getParameter("begindate");
			// 结束日期
			endDate = request.getParameter("enddate");		
			// 统计类型要传入的参数（按日期或月份统计）
			statType = request.getParameter("statType");			
			// 选择的图形显示类型
			showType = request.getParameter("showType");

			if (("".equals(beginDate)) || ("".equals(endDate))) {
				request.setAttribute("errorcont", new ErrorInfo().getErrorTip(
						statType, beginDate, endDate));
				ActionForward returnActionForward = mapping
						.findForward("errortest");
				return returnActionForward;
			}

			setInit(request);
			
			List result = ReportShopBalanceUtil.getAllConsumeStat(beginDate,
					endDate, statType);
			if (result.isEmpty()) {
				request.setAttribute("errorcont", new ErrorInfo().getErrorTip(
						statType, beginDate, endDate));
				ActionForward returnActionForward = mapping
						.findForward("errortest");
				return returnActionForward;
			}
			Collections.sort(result, new SortListByResult("balance_date"));
			//判断是否用曲线图显示
			if (new ErrorInfo().DateRangeJudeg(showType,statType,beginDate,endDate,request)){
				return mapping.findForward("errortest");
			}
			
			dateUnit = result.size()/8;
			statTypeReturn(request,result);
			
			// 根据要显示的图形类别绘制图形
			showTypeResult();
			
			request.setAttribute("pictype", picType);
			request.setAttribute("ylabel", yLabel);
			request.setAttribute("ylabel2",yLabel2);
			request.setAttribute("stattype",statType);
			request.setAttribute("pictype",picType);
			request.setAttribute("daterange", dateRange.toString());
			request.setAttribute("stattypeshow", statTypeShow);
			drawPic(request);
			ActionForward returnActionForward = mapping
					.findForward("allconsumestat_queryresult");
			return returnActionForward;
		}
		
		private void setInit(HttpServletRequest request){

			HttpSession session = request.getSession();
			if ("bydate".equals(statType)) {
				beginDate = DateUtil
						.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
				session.setAttribute("begindate45d", request
						.getParameter("begindate"));
				session.setAttribute("enddate45d", request.getParameter("enddate"));
				session.setAttribute("querytype45", "0");
				statTypeShow = GetProperty.getProperties("title.date", servlet
						.getServletContext());
				dateRange.append(
						GetProperty.getProperties("query.show.date", servlet.getServletContext())).append(beginDate)
						.append("-").append(endDate);
			} else if ("bymonth".equals(statType)) {
				beginDate = DateUtil.getMonth(request.getParameter("begindate"));
				endDate = DateUtil.getMonth(request.getParameter("enddate"));
				session.setAttribute("begindate45m", request
						.getParameter("begindate"));
				session.setAttribute("enddate45m", request.getParameter("enddate"));
				session.setAttribute("querytype45", "1");
				statTypeShow = GetProperty.getProperties("title.month",
						this.servlet.getServletContext());
				dateRange.append(
						GetProperty.getProperties("query.show.month", servlet
								.getServletContext())).append(beginDate)
						.append("-").append(endDate);
			} else if ("byweek".equals(statType)) {
				beginDate = DateUtil
						.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
				session.setAttribute("begindate45w", request
						.getParameter("begindate"));
				session.setAttribute("enddate45w", request.getParameter("enddate"));
				session.setAttribute("querytype45", "2");
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
		
		/**
		 * 根据选择的统计类型绘制图形
		 * @param request
		 * @param result
		 */
		private void statTypeReturn(HttpServletRequest request,List result){

			if ("bydate".equals(statType)){
				yLabel = new GetListResultStat().getYLabelMoney(result, "tradeamt",dataType);
				dataUnit = new GetListResultStat().getUnitValue(result, "tradeamt",dataType);
				yLabel2 = new GetListResultStat().getYLabelMoney(result, "mngamt",dataType);
				dataUnit2 = new GetListResultStat().getUnitValue(result, "mngamt",dataType);
				request.setAttribute("result", result);
				xData = "balance_date";
				if ("line".equals(showType)){
					request.setAttribute("allConsumeStatChart",
					new DrawTimeSeries(result, columnTitle, xData,
							dataType, accType, dataUnit)
							.getTimeSeriesProducer());
					
					request.setAttribute("allConsumeStatChart2",
							new DrawTimeSeries(result, columnTitle2, xData,
									dataType, accType2, dataUnit2)
									.getTimeSeriesProducer());
					
				}else{
					request.setAttribute("allConsumeStatChart",
							new DrawBarByTypeMap(result,accType,xData,dataType,columnTitle,dataUnit)
							.getDataProducer());
				}
			}else if ("bymonth".equals(statType)) {
				yLabel = new GetListResultStat().getYLabelMoney(result, "tradeamt",dataType);
				dataUnit = new GetListResultStat().getUnitValue(result, "tradeamt",dataType);
				request.setAttribute("result", result);
				xData = "balance_date";
				request.setAttribute("allConsumeStatChart",
						new DrawBarByTypeMap(result,accType,xData,dataType,columnTitle,dataUnit).getDataProducer());

				showTextAxis = new ErrorInfo().showTextAxis(result);
			} else if ("byweek".equals(statType)) {
				weekResult = new GetListResultStat().getListByWeek(result,
						beginDate, endDate);
				Collections.sort(weekResult, new SortListByResult("balance_date"));
				xData = "yearweek";
				yLabel = new GetListResultStat().getYLabelMoney(weekResult,
						"tradeamt", dataType);
				dataUnit = new GetListResultStat().getUnitValue(weekResult,
						"tradeamt", dataType);
				request.setAttribute("result", weekResult);
				request.setAttribute("allConsumeStatChart",
						new DrawBarByTypeMap(weekResult, accType, xData, dataType,
								columnTitle, dataUnit).getDataProducer());

				showTextAxis = new ErrorInfo().showTextAxis(weekResult);
			}
	

		}
		
		/**
		 * 根据选择的图形类型设置图形属性
		 *
		 */
		private void showTypeResult(){
			if ("line".equals(showType)) {
				if ("bydate".equals(statType)){
					picType = GetProperty.getProperties("pic.timeseries",servlet.getServletContext());
				}else{
					picType = GetProperty.getProperties("pic.line",servlet.getServletContext());
				}
				showOutLine = false;
			} else if ("bar".equals(showType)) {
				picType = GetProperty.getProperties("pic.bar", servlet
						.getServletContext());
				showOutLine = true;
			} else if ("stack".equals(showType)) {
				picType = GetProperty.getProperties("pic.stack",servlet
						.getServletContext());
				showOutLine = true;
			}

		}
		
		private void drawPic(HttpServletRequest request){
			if ("line".equals(showType)) {
				if ("bydate".equals(statType)){
					request.setAttribute("dataColor", new CustomerDrawChart(showBackgroundColor,showCustColor,dateUnit)
							.getTimeSeriesPostProcessor());
				}else{
					request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
							showTextAxis, showLabel, showBackgroundColor, showOutLine,
							showGrid).getChartPostProcessor());
				}
			}else if ("bar".equals(showType)) {
				request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
						showTextAxis, showLabel, showBackgroundColor, showOutLine,
						showGrid).getChartPostProcessor());
			}else if ("stack".equals(showType)) {
				request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
						showTextAxis, showLabel, showBackgroundColor, showOutLine,
						showGrid).getChartPostProcessor());
			}

		}
		
	}
}
