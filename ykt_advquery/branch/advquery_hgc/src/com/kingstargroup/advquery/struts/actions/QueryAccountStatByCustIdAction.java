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
import com.kingstargroup.advquery.customer.TCifCustomer;
import com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO;
import com.kingstargroup.advquery.hibernate.util.AccountUtil;
import com.kingstargroup.advquery.tradeserial.TradeSerialDAO;

/**
 * 个人帐务变动情况：存款，消费，押金
 * 
 * @author Administrator
 * 
 */
public class QueryAccountStatByCustIdAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) throws Exception {
		QueryAccountStatByCustIdActionExecution exec = new QueryAccountStatByCustIdActionExecution();
		return exec.execute(mapping,form,request,response);

	}
	private class QueryAccountStatByCustIdActionExecution {
		private String stuempno;
		//学工号
		private String custId;
		//开始日期
		private String beginDate;
		//结束日期
		private String endDate ;
		//显示日期范围
		private StringBuffer dateRange = new StringBuffer(200);
		//查询类型
		private String statType;
		//显示统计时是按月份统计，还是日期，周统计
		private String statTypeShow = "";
		//错误提示信息
		private String errorTip = "";
		
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
		
		//生成图表输入参数
		private String accType[] = {"存款","消费","押金"};
		private String xData = "";
		private String dataType = "float";
		private String columnTitle[] = {"saving","consume","ensure"};
		
		//返回查询结果
		private List weekResult = null;
		//金额单位
		private int dataUnit = 1;
		private int dateUnit11 = 9;
		//Ｙ轴提示信息
		private String yLabel = "";
		//选择的图形显示类型
		private String showType;
		//图形要显示的类型
		private String picType = "";

		ActionServlet servlet = QueryAccountStatByCustIdAction.this.servlet;
		public ActionForward execute(ActionMapping mapping, ActionForm form,
				HttpServletRequest request, HttpServletResponse response)
			throws Exception{
			//学工号
			custId = request.getParameter("empno");
			stuempno = request.getParameter("stuempno");
			//开始日期
			beginDate = request.getParameter("begindate");
			//结束日期
			endDate = request.getParameter("enddate");
			//选择的图形显示类型
			showType = request.getParameter("showType");
			//查询类型
			statType = request.getParameter("statType");
			
			setInit(request);
			
		
			if ("".equals(custId)&& "".equals(stuempno)){
				request.setAttribute("errorcont",new String("请输入要查询的客户号或学工号！"));
				return mapping.findForward("errortest");
			}
			if(!"".equals(stuempno)){
	          String 	temp_custId =   getCustId(stuempno);
	          if((!"".equals(custId))&&!temp_custId.equals(custId)){
	        	  request.setAttribute("errorcont",new String("客户不存在，请重新输入！"));
					return mapping.findForward("errortest");
	          }else{
	        	  custId = temp_custId;
	          }
			}
			/*if (("".equals(getCustName(custId))) || null==(getCustName(custId))) {
				request.setAttribute("errorcont",new String("客户号："+custId+"不存在，请重新输入！"));
				return mapping.findForward("errortest");			
			}*/
			request.setAttribute("custname",getCustName(custId));
			
			List result = new TradeSerialDAO().getAllAccountChangeStatByCustId(
					custId, beginDate, endDate,statType);
			if (result.isEmpty()){
				request.setAttribute("errorcont",errorTip);
				return mapping.findForward("errortest");			
			}
			//判断是否用曲线图显示
			if (new ErrorInfo().DateRangeJudeg(showType,statType,beginDate,endDate,request)){
				return mapping.findForward("errortest");
			}
			
			dateUnit11 = result.size()/8;
			//根据统计类型判断要组合
			statTypeReturn(request,result);
			
			//根据要显示的图形类别绘制图形
			showTypeResult();
			
			request.setAttribute("ylabel",yLabel);
			request.setAttribute("pictype",picType);
			request.setAttribute("daterange",dateRange.toString());
			request.setAttribute("stattypeshow",statTypeShow);
			
			drawPic(request);
			
			return mapping.findForward("oneaccountstat_queryresult");

		}
		
		/**
		 * 初始化系列参数
		 * @param request
		 */
		private void setInit(HttpServletRequest request){
			HttpSession session = request.getSession();
			session.setAttribute("custid",custId);
			session.setAttribute("stuempno",stuempno);
			if ("bydate".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));	
	 			session.setAttribute("begindate42d",request.getParameter("begindate"));
				session.setAttribute("enddate42d",request.getParameter("enddate"));
				session.setAttribute("querytype42","0");
				statTypeShow = GetProperty.getProperties("title.date",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.date",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("bymonth".equals(statType)){
				beginDate = DateUtil.getMonth(request.getParameter("begindate"));
				endDate = DateUtil.getMonth(request.getParameter("enddate"));
	 			session.setAttribute("begindate42m",request.getParameter("begindate"));
				session.setAttribute("enddate42m",request.getParameter("enddate"));
				session.setAttribute("querytype42","1");
				statTypeShow = GetProperty.getProperties("title.month",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.month",servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("byweek".equals(statType)){
				beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
				endDate = DateUtil.reFormatTime(request.getParameter("enddate"));	
	 			session.setAttribute("begindate42w",request.getParameter("begindate"));
				session.setAttribute("enddate42w",request.getParameter("enddate"));
				session.setAttribute("querytype42","2");
				//beginWeek = DateUtilExtend.getWeek(beginDate);
				//endWeek = DateUtilExtend.getWeek(endDate);	
				statTypeShow = GetProperty.getProperties("title.week",this.servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.week",this.servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}
			
			if ("bydate".equals(statType)){
				errorTip = "日期范围为："+dateRange+"--没有你要查询的数据，请重新指定查询条件！";		
			}else if ("bymonth".equals(statType)){
				errorTip = "月份范围为："+dateRange+"--没有你要查询的数据，请重新指定查询条件！";			
			}
			
		}
		
		/**
		 * 根据选择的统计类型绘制图形
		 * @param request
		 * @param result
		 */
		private void statTypeReturn(HttpServletRequest request,List result){
			if ("bydate".equals(statType)){
				request.setAttribute("result",result);
				yLabel = new GetListResultStat().getYLabelMoney(result,"consume",dataType);
				dataUnit = new GetListResultStat().getUnitValue(result,"consume",dataType);
				xData = "balance_date";
				if ("line".equals(showType)){
					request.setAttribute("OneAccountStatChart",
					new DrawTimeSeries(result, columnTitle, xData,
							dataType, accType, dataUnit)
							.getTimeSeriesProducer());
				}else{
					request.setAttribute("OneAccountStatChart",
							new DrawBarByTypeMap(result,accType,xData,dataType,columnTitle,dataUnit).getDataProducer());
				}
			}else if ("bymonth".equals(statType)){
				request.setAttribute("result",result);
				yLabel = new GetListResultStat().getYLabelMoney(result,"consume",dataType);
				dataUnit = new GetListResultStat().getUnitValue(result,"consume",dataType);
				xData = "balance_date";
				request.setAttribute("OneAccountStatChart",
						new DrawBarByTypeMap(result,accType,xData,dataType,columnTitle,dataUnit).getDataProducer());
				showTextAxis = new ErrorInfo().showTextAxis(result);
			}else if ("byweek".equals(statType)){
				weekResult = new GetListResultStat().getListByWeek(result,beginDate,endDate);
				Collections.sort(weekResult,new SortListByResult("balance_date"));
				yLabel = new GetListResultStat().getYLabelMoney(weekResult,"consume",dataType);
				dataUnit = new GetListResultStat().getUnitValue(weekResult,"consume",dataType);
				xData = "yearweek";
				request.setAttribute("result",weekResult);
				request.setAttribute("OneAccountStatChart",
						new DrawBarByTypeMap(weekResult,accType,xData,dataType,columnTitle,dataUnit).getDataProducer());
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
					request.setAttribute("dataColor", new CustomerDrawChart(showBackgroundColor,
							showCustColor,dateUnit11)
							.getTimeSeriesPostProcessor());
				}else{
					request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
							showTextAxis, showLabel, showBackgroundColor, showOutLine,
							showGrid).getChartPostProcessor());
				}
			}else if ("bar".equals(showType)) {
				request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid).getChartPostProcessor());
			}else if ("stack".equals(showType)) {
				request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
						showTextAxis, showLabel, showBackgroundColor, showOutLine,
						showGrid).getChartPostProcessor());
			}
		}

	}
	/**
	 * 根据学工号得到姓名
	 * @param custId
	 * @return
	 */
	private String getCustName(String custId){
		String custName = "";
		List list = new GetQueryConListDAO().getCustNameByID(custId);
		Iterator iter = list.iterator();
		while (iter.hasNext()){
			TCifCustomer row = (TCifCustomer)iter.next();
			custName = row.getCutName().toString();
		}
		return custName;
	}
	
	private String getCustId(String stuempNo){
		String custId ="";
		custId =  AccountUtil.getCustIdBystuempNo(stuempNo);
	    return custId;
	}

}
