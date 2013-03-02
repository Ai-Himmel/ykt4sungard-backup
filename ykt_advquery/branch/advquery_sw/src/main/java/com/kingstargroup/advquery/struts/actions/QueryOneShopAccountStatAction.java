/**
 * 
 */
package com.kingstargroup.advquery.struts.actions;

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

import com.kingstargroup.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.advquery.cewolf.DrawBarByTypeMap;
import com.kingstargroup.advquery.cewolf.DrawTimeSeries;
import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.common.GetListResultStat;
import com.kingstargroup.advquery.common.GetProperty;
import com.kingstargroup.advquery.common.SortListByResult;
import com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO;
import com.kingstargroup.advquery.reportshopbalance.ReportShopBalanceDAO;
import com.kingstargroup.advquery.shop.TCifShop;

/**
 * 各商户营业情况统计
 * 
 * @author Administrator
 * 
 */
public class QueryOneShopAccountStatAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) throws Exception {
		QueryOneShopAccountStatActionExecution exec = new QueryOneShopAccountStatActionExecution();
		return exec.execute(mapping,form,request,response);
	}
	private class QueryOneShopAccountStatActionExecution {
		private int shopId;
		private String beginDate;
		private String endDate;
		private StringBuffer dateRange = new StringBuffer(200);
		private String statTypeShow = "";
		//返回查询结果
		private List weekResult = null;
		private String showType;
		private String picType = "";
		//金额单位
		private int dataUnit = 1;
		private int dataUnit2 = 1;
		private int dateUnit = 1;
		//Ｙ轴提示信息
		private String yLabel = "";
		private String yLabel2 = "";
		private String statType;
		//绘制图形要传入的参数
		private String accType[] = {"发生金额","管理费金额"};
		private String accType2[] = {"管理费金额(放大)"};
		private String xData = "";
		private String dataType = "float";
		private String columnTitle[] = {"tradeamt","mngamt"};
		private String columnTitle2[] = {"mngamt"};
		
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
		ActionServlet servlet = QueryOneShopAccountStatAction.this.servlet;
		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
			throws Exception{
			//查询要传入的参数
			shopId = Integer.parseInt(request.getParameter("shopid"));
			//开始日期
			beginDate = request.getParameter("begindate");
			//结束日期
			endDate = request.getParameter("enddate");
			//选择的图形显示类型
			showType = request.getParameter("showType");		
			
			//统计方式要传入的参数
			statType = request.getParameter("statType");
			if (("".equals(beginDate))||("".equals(endDate))){
				request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}
			
			setInit(request);

			List result = new ReportShopBalanceDAO().getOneAccountStat(shopId,
					beginDate, endDate,statType);
			if (result.isEmpty()){
				request.setAttribute("errorcont",getShopName(shopId)+":"+new ErrorInfo().getErrorTip(statType,beginDate,endDate));
				return mapping.findForward("errortest");			
			}
			//判断是否用曲线图显示
			if (new ErrorInfo().DateRangeJudeg(showType,statType,beginDate,endDate,request)){
				return mapping.findForward("errortest");
			}
			

			dateUnit = result.size()/9;
			statTypeResult(request,result);
			//根据要显示的图形类别绘制图形
			showTypeResult();
			
			request.setAttribute("pictype",picType);
			request.setAttribute("ylabel2",yLabel2);
			request.setAttribute("stattype",statType);
			request.setAttribute("ylabel",yLabel);
			request.setAttribute("daterange",dateRange.toString());
			request.setAttribute("shopname",getShopName(shopId));
			request.setAttribute("stattypeshow",statTypeShow);
			drawPic(request);
			return mapping.findForward("oneshopaccountstat_queryresult");
			
		}
		private void setInit(HttpServletRequest request){
			HttpSession session = request.getSession();
			session.setAttribute("shopid",Integer.valueOf(String.valueOf(shopId)));
			
			if ("bydate".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
	 			session.setAttribute("begindate34d",request.getParameter("begindate"));
				session.setAttribute("enddate34d",request.getParameter("enddate"));
				session.setAttribute("querytype34","0");
				statTypeShow = GetProperty.getProperties("title.date",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.date",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("bymonth".equals(statType)){
				beginDate = DateUtil.getMonth(request.getParameter("begindate"));
				endDate = DateUtil.getMonth(request.getParameter("enddate"));
	 			session.setAttribute("begindate34m",request.getParameter("begindate"));
				session.setAttribute("enddate34m",request.getParameter("enddate"));
				session.setAttribute("querytype34","1");
				statTypeShow = GetProperty.getProperties("title.month",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.month",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("byweek".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));	
	 			session.setAttribute("begindate34w",request.getParameter("begindate"));
				session.setAttribute("enddate34w",request.getParameter("enddate"));
				session.setAttribute("querytype34","2");
				//beginWeek = DateUtilExtend.getWeek(beginDate);
				//endWeek = DateUtilExtend.getWeek(endDate);	
				statTypeShow = GetProperty.getProperties("title.week",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.week",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
				}	
			}
		private void statTypeResult(HttpServletRequest request,List result){
			try {
				if ("bydate".equals(statType)){
					yLabel = new GetListResultStat().getYLabelMoney(result, "tradeamt",dataType);
					dataUnit = new GetListResultStat().getUnitValue(result, "tradeamt",dataType);
					yLabel2 = new GetListResultStat().getYLabelMoney(result, "mngamt",dataType);
					dataUnit2 = new GetListResultStat().getUnitValue(result, "mngamt",dataType);
					Collections.sort(result,new SortListByResult("balance_date"));
					request.setAttribute("result", result);
					xData = "balance_date";
					if ("line".equals(showType)){
						request.setAttribute("OneShopAccountStatChart",new DrawTimeSeries(result, columnTitle, xData,dataType, accType, dataUnit).getTimeSeriesProducer());
						
						request.setAttribute("OneShopAccountStatChart2",
								new DrawTimeSeries(result, columnTitle2, xData,
										dataType, accType2, dataUnit2)
										.getTimeSeriesProducer());

					}else{
						request.setAttribute("OneShopAccountStatChart",
								new DrawBarByTypeMap(result,accType,xData,dataType,columnTitle,dataUnit)
								.getDataProducer());
					}
				}else if ("bymonth".equals(statType)){
					Collections.sort(result,new SortListByResult("balance_date"));
					request.setAttribute("result",result);
					yLabel = new GetListResultStat().getYLabelMoney(result,"tradeamt",dataType);
					dataUnit = new GetListResultStat().getUnitValue(result,"tradeamt",dataType);
					xData = "balance_date";
					request.setAttribute("OneShopAccountStatChart",
							new DrawBarByTypeMap(result,accType,xData,dataType,columnTitle,dataUnit).getDataProducer());
					showTextAxis = new ErrorInfo().showTextAxis(result);
				}else if ("byweek".equals(statType)){
					weekResult = new GetListResultStat().getListByWeek(result,beginDate,endDate);
					Collections.sort(weekResult,new SortListByResult("balance_date"));
					yLabel = new GetListResultStat().getYLabelMoney(weekResult,"tradeamt",dataType);
					dataUnit = new GetListResultStat().getUnitValue(weekResult,"tradeamt",dataType);
					xData = "yearweek";
					request.setAttribute("result",weekResult);
					request.setAttribute("OneShopAccountStatChart",
							new DrawBarByTypeMap(weekResult,accType,xData,dataType,columnTitle,dataUnit).getDataProducer());
					showTextAxis = new ErrorInfo().showTextAxis(weekResult);
				}
			} catch (Exception e) {
				e.printStackTrace();
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
	private String getShopName(int shopId){
		String devName = "";
		List list = new GetQueryConListDAO().getShopName(shopId);
		Iterator iter = list.iterator();
		while (iter.hasNext()){
			TCifShop row = (TCifShop)iter.next();
			devName = row.getShopName().toString();
		}
		return devName;
	}

}
