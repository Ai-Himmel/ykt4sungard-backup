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
import com.kingstargroup.advquery.hibernate.util.ReportActiveUtil;

/**
 * 存款总体情况统计（金额和笔数）
 * @author Administrator
 *
 */
public class QueryTotleSavingStatAction extends Action{

	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		QueryTotleSavingStatActionExecution exec = new QueryTotleSavingStatActionExecution();
		return exec.execute(mapping,form,request,response);

	}
	private class QueryTotleSavingStatActionExecution {
		private String beginDate;
		private String endDate;
		private StringBuffer dateRange = new StringBuffer(200);
		private String statTypeShow = "";
		private String showType ;
		private String picType = "";
		//金额单位
		private int dataUnit = 1;
		private int dateUnit = 1;
		//Ｙ轴提示信息
		private String yLabel = "";
		private List weekResult = null;
		private String statType;
		//统计类别，money为金额，num为笔数
		private String moneyornum;
		private String mapforward = "";
		//显示图形所需参数
		private String accType[] = {"POS充值","圈存转账","经费本充值","支票充值","现金充值"};
		private String xData = "";
		private String columnTitle[] = {"pos","transfer","outlay","ticket","cash"};
		
		private String accTypeNum[] = {"POS充值","圈存转账","现金充值"};
		private String columnTitleNum[] = {"pos","transfer","cash"};
		
		// 自定义图表显示要传入的参数
		// 显示自定义颜色
		private boolean showCustColor = true;
		// 显示横坐标文字的旋转方向
		private boolean showTextAxis = true ;
		// 显示Bar图标上的数字
		private boolean showLabel = false;
		// 显示自定义图表背景颜色
		private boolean showBackgroundColor = true;
		// 显示轮廓线
		private boolean showOutLine = true;
		// 显示网格线
		private boolean showGrid = true;
		
		ActionServlet servlet = QueryTotleSavingStatAction.this.servlet;
		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
			throws Exception{
			//开始日期
			beginDate = request.getParameter("begindate");
			//结束日期
			endDate = request.getParameter("enddate");
			//选择的图形显示类型
			showType = request.getParameter("showType");		
			//查询类型
			statType = request.getParameter("statType");
			moneyornum = request.getParameter("moneyornum");
			if (("".equals(beginDate))||("".equals(endDate))){
				request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}
			setInit(request);
			//判断是否用曲线图显示
			if (new ErrorInfo().DateRangeJudeg(showType,statType,beginDate,endDate,request)){
				return mapping.findForward("errortest");
			}
			

			if ("money".equals(moneyornum)){
				String dataType = "float";
				String picAttribute = "TotleSavingMoneyBar";
				mapforward = "totlesavingmoney_queryresult";
				List result = ReportActiveUtil.getTotleSavingMoneyStat(beginDate,endDate,statType);
				if (result.isEmpty()){
					request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
					return mapping.findForward("errortest");			
				}
				dateUnit = result.size()/9;
				statTypeResult(request,result,dataType,picAttribute,accType,columnTitle);

				//根据要显示的图形类别绘制图形
				showTypeResult();
				request.setAttribute("pictype",picType);
				float[] resultPie = new GetListResultStat().getListResultStatFloat(result,
						columnTitle);

				showTextAxis = new ErrorInfo().showTextAxis(result);
				request.setAttribute("stattypeshow",statTypeShow);
				// 绘制饼图
				request
						.setAttribute("TotleSavingMoneyPieData", new DrawPieCust(
								resultPie, accType, dataType, columnTitle)
								.getDatasetProducerTotle());
				// 自定义饼图显示
				request.setAttribute("dataColorPie", new CustomerDrawChart(showBackgroundColor).getPiePostProcessor());
				
			}else if ("num".equals(moneyornum)){
				//显示图形所需参数
				String dataType = "integer";
				String picAttribute = "TotleSavingNumBar";
				mapforward = "totlesavingnum_queryresult";
				List result = ReportActiveUtil.getTotleSavingNumStat(beginDate,endDate,statType);
				if (result.isEmpty()){
					request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
					return mapping.findForward("errortest");			
				}
				dateUnit = result.size()/9;
				statTypeResult(request,result,dataType,picAttribute,accTypeNum,columnTitleNum);
				//根据要显示的图形类别绘制图形
				showTypeResult();
				
				request.setAttribute("pictype",picType);
		
				int[] resultPie = new GetListResultStat().getListResultStat(result,
						columnTitleNum);
				request.setAttribute("stattypeshow",statTypeShow);
				// 绘制饼图
				request
						.setAttribute("TotleSavingNumData", new DrawPieCust(
								resultPie, accTypeNum, dataType, columnTitleNum)
								.getDatasetProducerTotle());
				// 自定义饼图显示
				request.setAttribute("dataColorPie", new CustomerDrawChart(showBackgroundColor).getPiePostProcessor());
			}
			//自定义图形显示
			request.setAttribute("ylabel",yLabel);
			drawPic(request);
			request.setAttribute("daterange",dateRange.toString());
			return mapping.findForward(mapforward);
			
		}
		private void setInit(HttpServletRequest request){
			HttpSession session = request.getSession();
			if ("bydate".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));	
	 			session.setAttribute("begindate23d",request.getParameter("begindate"));
				session.setAttribute("enddate23d",request.getParameter("enddate"));
				session.setAttribute("querytype23","0");
				statTypeShow = GetProperty.getProperties("title.date",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.date",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("bymonth".equals(statType)){
				beginDate = DateUtil.getMonth(request.getParameter("begindate"));
				endDate = DateUtil.getMonth(request.getParameter("enddate"));	
	 			session.setAttribute("begindate23m",request.getParameter("begindate"));
				session.setAttribute("enddate23m",request.getParameter("enddate"));
				session.setAttribute("querytype22","1");
				statTypeShow = GetProperty.getProperties("title.month",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.month",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("byweek".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));	
	 			session.setAttribute("begindate23w",request.getParameter("begindate"));
				session.setAttribute("enddate23w",request.getParameter("enddate"));
				session.setAttribute("querytype22","2");
				//beginWeek = DateUtilExtend.getWeek(beginDate);
				//endWeek = DateUtilExtend.getWeek(endDate);	
				statTypeShow = GetProperty.getProperties("title.week",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.week",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}
		}
		private void statTypeResult(HttpServletRequest request,List result,String dataType,
				String picAttribute,String inAccType[],String inColumnTitle[]){
			if ("bydate".equals(statType)){
				request.setAttribute("result", result);
				if ("money".equals(moneyornum)){
					yLabel = new GetListResultStat().getYLabelMoney(result, "pos",dataType);
				}else if ("num".equals(moneyornum)){
					yLabel = new GetListResultStat().getYLabelNum(result,"pos",dataType);
				}
				dataUnit = new GetListResultStat().getUnitValue(result, "pos",dataType);
				xData = "balance_date";
				if ("line".equals(showType)){
					request.setAttribute(picAttribute,
					new DrawTimeSeries(result, inColumnTitle, xData,
							dataType, inAccType, dataUnit)
							.getTimeSeriesProducer());
				}else{
					request.setAttribute(picAttribute,
							new DrawBarByTypeMap(result,inAccType,xData,dataType,inColumnTitle,dataUnit)
							.getDataProducer());
				}
			}else if ("bymonth".equals(statType)){
				request.setAttribute("result",result);
				if ("money".equals(moneyornum)){
					yLabel = new GetListResultStat().getYLabelMoney(result, "pos",dataType);
				}else if ("num".equals(moneyornum)){
					yLabel = new GetListResultStat().getYLabelNum(result,"pos",dataType);
				}
				dataUnit = new GetListResultStat().getUnitValue(result, "pos",dataType);
				xData = "balance_date";
				request.setAttribute(picAttribute,
						new DrawBarByTypeMap(result,inAccType,xData,dataType,inColumnTitle,dataUnit).getDataProducer());
				showTextAxis = new ErrorInfo().showTextAxis(result);
			}else if ("byweek".equals(statType)){
				weekResult = new GetListResultStat().getListByWeek(result,beginDate,endDate);
				Collections.sort(weekResult,new SortListByResult("balance_date"));
				if ("money".equals(moneyornum)){
					yLabel = new GetListResultStat().getYLabelMoney(weekResult, "pos",dataType);
				}else if ("num".equals(moneyornum)){
					yLabel = new GetListResultStat().getYLabelNum(weekResult,"pos",dataType);
				}
				dataUnit = new GetListResultStat().getUnitValue(weekResult, "pos",dataType);
				xData = "yearweek";
				request.setAttribute("result",weekResult);
				request.setAttribute(picAttribute,
						new DrawBarByTypeMap(weekResult,inAccType,xData,dataType,inColumnTitle,dataUnit).getDataProducer());
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
