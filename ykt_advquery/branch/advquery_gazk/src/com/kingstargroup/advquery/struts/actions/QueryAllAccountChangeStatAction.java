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
import com.kingstargroup.advquery.reportactive.ReportActiveDAO;

/**
 * @author Administrator
 *
 */
public class QueryAllAccountChangeStatAction extends Action{

	/**
	 * 整体帐务情况变化统计：充值，消费，押金
	 */
	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		QueryAllAccountChangeStatActionExecution exec = new QueryAllAccountChangeStatActionExecution();
		return exec.execute(mapping,form,request,response);
	}
	private class QueryAllAccountChangeStatActionExecution {
		//统计类别传入的参数
		private String statType ;
		//开始日期
		private String beginDate;
		//结束日期
		private String endDate;
		//返回查询结果
		private List weekResult = null;
		//日期范围
		private StringBuffer dateRange = new StringBuffer(200);
		//选择的图形显示类型
		private String showType;		
		private String picType = "";
		private String statTypeShow = "";
		//金额单位
		private int dataUnit = 1;
		private int dataUnit2 = 1;
		private int dateUnit = 1;
		//Ｙ轴提示信息
		private String yLabel = "";
		private String yLabel2 = "";
		private String accType[] = {"存款", "消费", "押金"};
		private String accType2[] = {"押金(放大)"};
		private String xData = "";
		private String dataType = "float";
		private String columnTitle[] = {"saving","consume","ensure"};
		private String columnTitle2[] = {"ensure"};
		
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
		//显示网格线
		private boolean showGrid = true;
		
		ActionServlet servlet = QueryAllAccountChangeStatAction.this.servlet;
		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
			throws Exception{
			//统计类别传入的参数
			statType = request.getParameter("statType");
			//开始日期
			beginDate = request.getParameter("begindate");
			//结束日期
			endDate = request.getParameter("enddate");
			//选择的图形显示类型
			showType = request.getParameter("showType");	
			if (("".equals(beginDate))||("".equals(endDate))){
				request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}
			
			setInit(request);
			
			List result = new ReportActiveDAO().getAllAccountChangeStat(beginDate,endDate,statType);
			if (result.isEmpty()){
				request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}
			//判断是否用曲线图显示
			if (new ErrorInfo().DateRangeJudeg(showType,statType,beginDate,endDate,request)){
				return mapping.findForward("errortest");
			}
			

			dateUnit = result.size()/10;
			setTypeReturn(request,result);
			
			//根据要显示的图形类别绘制图形
			showTypeResult();
			request.setAttribute("pictype",picType);
			request.setAttribute("ylabel",yLabel);
			request.setAttribute("ylabel2",yLabel2);
			request.setAttribute("stattype",statType);
			request.setAttribute("showtype",showType);
			request.setAttribute("rangedate",dateRange.toString());
			request.setAttribute("stattypeshow",statTypeShow);
			drawPic(request);
			return mapping.findForward("allaccountstat_queryresult");
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
	 			session.setAttribute("begindate41d",request.getParameter("begindate"));
				session.setAttribute("enddate41d",request.getParameter("enddate"));
				session.setAttribute("querytype41","0");
				statTypeShow = GetProperty.getProperties("title.date",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.date",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("bymonth".equals(statType)){
				beginDate = DateUtil.getMonth(request.getParameter("begindate"));
				endDate = DateUtil.getMonth(request.getParameter("enddate"));	
	 			session.setAttribute("begindate41m",request.getParameter("begindate"));
				session.setAttribute("enddate41m",request.getParameter("enddate"));
				session.setAttribute("querytype41","1");
				statTypeShow = GetProperty.getProperties("title.month",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.date",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("byweek".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));	
	 			session.setAttribute("begindate41w",request.getParameter("begindate"));
				session.setAttribute("enddate41w",request.getParameter("enddate"));
				session.setAttribute("querytype41","2");
				//beginWeek = DateUtilExtend.getWeek(beginDate);
				//endWeek = DateUtilExtend.getWeek(endDate);	
				statTypeShow = GetProperty.getProperties("title.week",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.week",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}
			
		}
		
		/**
		 * 根据选择的统计类型绘制图形
		 * @param request
		 * @param result
		 */
		private void setTypeReturn(HttpServletRequest request,List result){
			if ("bydate".equals(statType)){
				if ("bydate".equals(statType)){
					yLabel = new GetListResultStat().getYLabelMoney(result, "saving",dataType);
					dataUnit = new GetListResultStat().getUnitValue(result, "saving",dataType);
					yLabel2 = new GetListResultStat().getYLabelMoney(result, "ensure",dataType);
					dataUnit2 = new GetListResultStat().getUnitValue(result, "ensure",dataType);
					request.setAttribute("result", result);
					xData = "balance_date";
					if ("line".equals(showType)){
						request.setAttribute("allaccountstatChart",
						new DrawTimeSeries(result, columnTitle, xData,
								dataType, accType, dataUnit)
								.getTimeSeriesProducer());
						request.setAttribute("allaccountstatChart2",
								new DrawTimeSeries(result, columnTitle2, xData,
										dataType, accType2, dataUnit2)
										.getTimeSeriesProducer());

					}else{
						request.setAttribute("allaccountstatChart",
								new DrawBarByTypeMap(result,accType,xData,dataType,columnTitle,dataUnit)
								.getDataProducer());
					}
				}
			}else if ("bymonth".equals(statType)){
				request.setAttribute("result",result);
				yLabel = new GetListResultStat().getYLabelMoney(result,"saving",dataType);
				dataUnit = new GetListResultStat().getUnitValue(result,"saving",dataType);
				xData = "balance_date";
				request.setAttribute("allaccountstatChart" ,
						new DrawBarByTypeMap(result,accType,xData,dataType,columnTitle,dataUnit).getDataProducer());
				
				showTextAxis = new ErrorInfo().showTextAxis(result);
			}else if ("byweek".equals(statType)){
				weekResult = new GetListResultStat().getListByWeek(result,beginDate,endDate);
				Collections.sort(weekResult,new SortListByResult("balance_date"));
				yLabel = new GetListResultStat().getYLabelMoney(weekResult,"saving",dataType);
				dataUnit = new GetListResultStat().getUnitValue(weekResult,"saving",dataType);
				xData = "yearweek";
				request.setAttribute("result",weekResult);
				request.setAttribute("allaccountstatChart" ,
						new DrawBarByTypeMap(weekResult,accType,xData,dataType,columnTitle,dataUnit).getDataProducer());
				
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
					request.setAttribute("dataColor", new CustomerDrawChart(showBackgroundColor,
							showCustColor,dateUnit)
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
