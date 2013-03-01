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
 * 各校区消费情况对比（金额）
 * @author Administrator
 *
 */
public class QueryAllConsumeCompareAction extends Action{

	public ActionForward execute(ActionMapping mapping, 
				ActionForm form, 
				HttpServletRequest request, 
				HttpServletResponse response) throws Exception {
		QueryAllConsumeCompareActionExecution exec = new QueryAllConsumeCompareActionExecution();
		return exec.execute(mapping,form,request,response);
	}
	private class QueryAllConsumeCompareActionExecution {
		private String beginDate;
		private String endDate;
		private StringBuffer dateRange = new StringBuffer(200);
		private String statTypeShow = "";
		//金额单位
		private int dataUnit = 1;
		private int dateUnit = 1;
		//Ｙ轴提示信息
		private String yLabel = "";
		//返回查询结果
		private List weekResult = null;
		private String showType;
		private String picType = "";
		private String compareType;
		private String statType;
		
		//生成图表输入参数
		private String accType[] = {"邯郸校区","枫林校区","张江校区","江湾校区"};
		private String xData = "";
		private String columnTitle[] = {"hd","fl","zj","jw"};
		
		// 自定义图表显示要传入的参数
		// 显示自定义颜色
		private boolean showCustColor = true;
		// 显示横坐标文字的旋转方向
		private boolean showTextAxis =true;
		// 显示Bar图标上的数字
		private boolean showLabel = false;
		// 显示自定义图表背景颜色
		private boolean showBackgroundColor = true;
		// 显示轮廓线
		private boolean showOutLine = true;
		//显示网格线
		private boolean showGrid = true;
		private String mapForward = "";
		ActionServlet servlet = QueryAllConsumeCompareAction.this.servlet;
		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
			throws Exception{
			//开始日期
			beginDate = request.getParameter("begindate");
			//结束日期
			endDate = request.getParameter("enddate");
			//选择的图形显示类型
			showType = request.getParameter("showType");		
			//统计类别参数（按日期或月份）
			compareType = request.getParameter("moneyornum");
			//查询类型（按日查询或按月查询）
			statType = request.getParameter("statType");
			if (("".equals(beginDate))||("".equals(endDate))){
				request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}
			
			setInit(request);
			//判断是否用曲线图显示
			if (new ErrorInfo().DateRangeJudeg(showType,statType,beginDate,endDate,request)){
				return mapping.findForward("errortest");
			}
			
			if ("num".equals(compareType)){
				String dataType = "integer";
				String rAttribute = "AllConsumeCompareNumChart";
				List result = ReportShopBalanceUtil.getAreaSalesNumCompare(beginDate,endDate,statType);
				if (result.isEmpty()){
					request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
					return mapping.findForward("errortest");			
				}
				dateUnit = result.size()/9;
				setTypeReturn(request,result,dataType,rAttribute);
				//根据要显示的图形类别绘制图形
				showTypeResult();
				
				request.setAttribute("pictype",picType);
				
				request.setAttribute("stattypeshow",statTypeShow);
				mapForward = "allconsumecomparenum_queryresult";			
			}else if ("money".equals(compareType)){
				String dataType = "float";
				String rAttribute = "AllConsumeCompareMoneyChart";
				List result = ReportShopBalanceUtil.getAreaSalesMoneyCompare(beginDate,endDate,statType);
				if (result.isEmpty()){
					request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
					return mapping.findForward("errortest");			
				}
				dateUnit = result.size()/9;
				setTypeReturn(request,result,dataType,rAttribute);
				//根据要显示的图形类别绘制图形
				showTypeResult();

				request.setAttribute("pictype",picType);

				request.setAttribute("stattypeshow",statTypeShow);
				mapForward = "allconsumecomparemoney_queryresult";			
			}
			
			request.setAttribute("ylabel",yLabel);
			request.setAttribute("daterange",dateRange.toString());
			drawPic(request);
			return mapping.findForward(mapForward);	
		}
		
		/**
		 * 初始化
		 * @param request
		 */
		private void setInit(HttpServletRequest request){
			HttpSession session = request.getSession();
			if ("bydate".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
	 			session.setAttribute("begindate46d",request.getParameter("begindate"));
				session.setAttribute("enddate46d",request.getParameter("enddate"));
				session.setAttribute("querytype46","0");
				statTypeShow = GetProperty.getProperties("title.date",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.date",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("bymonth".equals(statType)){
				beginDate = DateUtil.getMonth(request.getParameter("begindate"));
				endDate = DateUtil.getMonth(request.getParameter("enddate"));
	 			session.setAttribute("begindate46m",request.getParameter("begindate"));
				session.setAttribute("enddate46m",request.getParameter("enddate"));
				session.setAttribute("querytype46","1");
				statTypeShow = GetProperty.getProperties("title.month",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.month",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("byweek".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));	
	 			session.setAttribute("begindate46w",request.getParameter("begindate"));
				session.setAttribute("enddate46w",request.getParameter("enddate"));
				session.setAttribute("querytype46","2");
				//beginWeek = DateUtilExtend.getWeek(beginDate);
				//endWeek = DateUtilExtend.getWeek(endDate);	
				statTypeShow = GetProperty.getProperties("title.week",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.week",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}
		}
		
		/**
		 * 根据结果绘制图形
		 * @param request
		 * @param result
		 * @param dataType
		 */
		private void setTypeReturn(HttpServletRequest request,List result,String dataType,String rAttribute){
			if ("bydate".equals(statType)){
				if ("num".equals(compareType)){
					yLabel = new GetListResultStat().getYLabelNum(result, "hd",dataType);
				}else if ("money".equals(compareType)){
					yLabel = new GetListResultStat().getYLabelMoney(result,"hd",dataType);
				}
				
				dataUnit = new GetListResultStat().getUnitValue(result, "hd",dataType);
				request.setAttribute("result", result);
				xData = "balance_date";
				if ("line".equals(showType)){
					request.setAttribute(rAttribute,
					new DrawTimeSeries(result, columnTitle, xData,
							dataType, accType, dataUnit)
							.getTimeSeriesProducer());
				}else{
					request.setAttribute(rAttribute,
							new DrawBarByTypeMap(result,accType,xData,dataType,columnTitle,dataUnit)
							.getDataProducer());
				}				
			}else if ("bymonth".equals(statType)){
				request.setAttribute("result",result);
				if ("money".equals(compareType)){
					yLabel = new GetListResultStat().getYLabelMoney(result, "hd",dataType);
				}else if ("num".equals(compareType)){
					yLabel = new GetListResultStat().getYLabelNum(result,"hd",dataType);
				}
				dataUnit = new GetListResultStat().getUnitValue(result,"hd",dataType);
				xData = "balance_date";
				request.setAttribute(rAttribute,
						new DrawBarByTypeMap(result,accType,xData,dataType,columnTitle,dataUnit).getDataProducer());
				showTextAxis = new ErrorInfo().showTextAxis(result);
			}else if ("byweek".equals(statType)){
				weekResult = new GetListResultStat().getListByWeek(result,beginDate,endDate);
				Collections.sort(weekResult,new SortListByResult("balance_date"));
				if ("money".equals(compareType)){
					yLabel = new GetListResultStat().getYLabelMoney(weekResult, "hd",dataType);
				}else if ("num".equals(compareType)){
					yLabel = new GetListResultStat().getYLabelNum(weekResult,"hd",dataType);
				}
				dataUnit = new GetListResultStat().getUnitValue(weekResult,"hd",dataType);
				xData = "yearweek";
				request.setAttribute("result",weekResult);
				request.setAttribute(rAttribute,
						new DrawBarByTypeMap(weekResult,accType,xData,dataType,columnTitle,dataUnit).getDataProducer());
				showTextAxis = new ErrorInfo().showTextAxis(weekResult);
			}

		}
		
		/**
		 * 图形显示样式
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
