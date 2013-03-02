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
import com.kingstargroup.advquery.cewolf.DrawPieCust;
import com.kingstargroup.advquery.cewolf.DrawTimeSeries;
import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.common.GetListResultStat;
import com.kingstargroup.advquery.common.GetProperty;
import com.kingstargroup.advquery.common.SortListByResult;
import com.kingstargroup.advquery.reportactive.ReportActiveDAO;
/**
 * @author Administrator
 * 
 */
public class QueryCardOpenLoseBackAction extends Action {

	/**
	 * 某段时间内开卡，挂失，回收，补办卡总数统计
	 */
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		QueryCardOpenLoseBackActionExecution exec = new QueryCardOpenLoseBackActionExecution();
		return exec.execute(mapping,form,request,response);
	}
	private class QueryCardOpenLoseBackActionExecution {
		private String beginDate;
		private String endDate;
		//查询的日期范围
		private StringBuffer dateRange = new StringBuffer(200);
		//查询结果的显示标题
		private String statTypeShow = "";
		//金额单位
		private int dataUnit = 1;
		private int dateUnit = 1;
		//Ｙ轴提示信息
		private String yLabel = "";
		private String showType;
		private String picType = "";
		private List weekResult = null;
		private String statType;
		// 绘制图形时传入的参数
		private String accType[] = { "发行卡", "挂失卡", "收回卡", "补办卡" };
		private String xData = "";
		private String dataType = "integer";
		private String columnTitle[] = {"opencard", "lose", "receive","repair" };

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
		private boolean showOutLine = true;
		// 显示网格线
		private boolean showGrid = true;
		ActionServlet servlet = QueryCardOpenLoseBackAction.this.servlet;
		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
			throws Exception{
			//开始日期
			beginDate = request.getParameter("begindate");
			//结束日期
			endDate = request.getParameter("enddate");
			//选择的图形显示类型
			showType = request.getParameter("showType");		
			// 统计类型参数
			statType = request.getParameter("statType");
			if (("".equals(beginDate))||("".equals(endDate))){
				request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}
			
			setInit(request);
			List result = new ReportActiveDAO().getCardOpenLoseBackStat(beginDate,
					endDate, statType);
			if (result.isEmpty()){
				request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}
			//判断是否用曲线图显示
			if (new ErrorInfo().DateRangeJudeg(showType,statType,beginDate,endDate,request)){
				return mapping.findForward("errortest");
			}
			

			dateUnit = result.size()/9;
			//判断是按周查询，月，还是日查询
			statTypeResult(request,result);
			//根据要显示的图形类别绘制图形
			showTypeResult();
			request.setAttribute("pictype",picType);

			int[] resultPie = new GetListResultStat().getListResultStat(result,
					columnTitle);

			request.setAttribute("ylabel",yLabel);
			request.setAttribute("daterange",dateRange.toString());
			//request.setAttribute("result", result);
			request.setAttribute("stattypeshow",statTypeShow);
			// 自定义图形显示
			drawPic(request);

			// 绘制饼图
			request
					.setAttribute("cardOpenLoseBackPieData", new DrawPieCust(
							resultPie, accType, dataType, columnTitle)
							.getDatasetProducerTotle());

			// 自定义饼图显示
			request.setAttribute("dataColorPie", new CustomerDrawChart(showBackgroundColor).getPiePostProcessor());

			return mapping.findForward("cardopenloseback_queryresult");
			
		}
		private void setInit(HttpServletRequest request){
			HttpSession session = request.getSession();
			if ("bydate".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
	 			session.setAttribute("begindate22d",request.getParameter("begindate"));
				session.setAttribute("enddate22d",request.getParameter("enddate"));
				session.setAttribute("querytype22","0");
				statTypeShow = GetProperty.getProperties("title.date",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.date",servlet.getServletContext()))
					.append(beginDate).append("-").append(endDate);
			}else if ("bymonth".equals(statType)){
				beginDate = DateUtil.getMonth(request.getParameter("begindate"));
				endDate = DateUtil.getMonth(request.getParameter("enddate"));	
	 			session.setAttribute("begindate22m",request.getParameter("begindate"));
				session.setAttribute("enddate22m",request.getParameter("enddate"));
				session.setAttribute("querytype22","1");
				statTypeShow = GetProperty.getProperties("title.month",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.month",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("byweek".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));	
	 			session.setAttribute("begindate22w",request.getParameter("begindate"));
				session.setAttribute("enddate22w",request.getParameter("enddate"));
				session.setAttribute("querytype22","2");
				//beginWeek = DateUtilExtend.getWeek(beginDate);
				//endWeek = DateUtilExtend.getWeek(endDate);	
				statTypeShow = GetProperty.getProperties("title.week",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.week",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
				
			}
		}
		private void statTypeResult(HttpServletRequest request,List result){
			if ("bydate".equals(statType)){
				yLabel = new GetListResultStat().getYLabelCard(result, "opencard",dataType);
				dataUnit = new GetListResultStat().getUnitValue(result, "opencard",dataType);
				request.setAttribute("result", result);
				xData = "balance_date";
				if ("line".equals(showType)){
					request.setAttribute("cardOpenLoseBackBarData",
					new DrawTimeSeries(result, columnTitle, xData,
							dataType, accType, dataUnit)
							.getTimeSeriesProducer());
				}else{
					request.setAttribute("cardOpenLoseBackBarData",
							new DrawBarByTypeMap(result,accType,xData,dataType,columnTitle,dataUnit)
							.getDataProducer());
				}
			}else if ("bymonth".equals(statType)){
				request.setAttribute("result",result);
				yLabel = new GetListResultStat().getYLabelCard(result,"opencard",dataType);
				dataUnit = new GetListResultStat().getUnitValue(result,"opencard",dataType);
				xData = "balance_date";
				// 创建发卡，挂失，收回，补办卡数量图形数据集
				request.setAttribute("cardOpenLoseBackBarData", new DrawBarByTypeMap(
						result, accType, xData, dataType, columnTitle,dataUnit)
						.getDataProducer());
				showTextAxis = new ErrorInfo().showTextAxis(result);
			}else if ("byweek".equals(statType)){
				weekResult = new GetListResultStat().getListByWeek(result,beginDate,endDate);
				Collections.sort(weekResult,new SortListByResult("balance_date"));
				yLabel = new GetListResultStat().getYLabelCard(weekResult,"opencard",dataType);
				dataUnit = new GetListResultStat().getUnitValue(weekResult,"opencard",dataType);
				xData = "yearweek";
				request.setAttribute("result",weekResult);
				// 创建发卡，挂失，收回，补办卡数量图形数据集
				request.setAttribute("cardOpenLoseBackBarData", new DrawBarByTypeMap(
						weekResult, accType, xData, dataType, columnTitle,dataUnit)
						.getDataProducer());
				showTextAxis = new ErrorInfo().showTextAxis(weekResult);
			}
		}
		private void showTypeResult(){
			if ("line".equals(showType)) {
				if ("bydate".equals(statType)){
					picType = GetProperty.getProperties("pic.timeseries",servlet.getServletContext());
				}else{
					picType = GetProperty.getProperties("pic.line",servlet.getServletContext());
				}
				showOutLine = false;
			}else if ("bar".equals(showType)){
				picType = GetProperty.getProperties("pic.bar",servlet.getServletContext());
				showOutLine = true;
			}else if ("stack".equals(showType)){
				picType = GetProperty.getProperties("pic.stack",servlet.getServletContext());
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
