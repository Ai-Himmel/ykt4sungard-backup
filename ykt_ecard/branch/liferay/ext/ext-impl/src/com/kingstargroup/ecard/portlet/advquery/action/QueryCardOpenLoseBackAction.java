/**
 * 
 */
package com.kingstargroup.ecard.portlet.advquery.action;

import java.util.Collections;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionServlet;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.portlet.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawBarByTypeMap;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawPieCust;
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
		private String accType[] = { "发行卡",  "收回卡","挂失卡", "冻结卡" };
		private String xData = "";
		private String dataType = "integer";
		private String columnTitle[] = {"open", "receive","lose", "cool" };

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
			
			response.setCharacterEncoding("UTF-8");
			DynaActionForm cardopenlosebackform = (DynaActionForm)form;
			//开始日期
			beginDate = cardopenlosebackform.getString("openloseback_begindate");
			//结束日期
			endDate = cardopenlosebackform.getString("openloseback_enddate");
			//选择的图形显示类型
			showType = request.getParameter("showType");		
			// 统计类型参数
			statType = request.getParameter("statType");
			
			
			String querytype = cardopenlosebackform.getString("querytype");
			if(!"".equals(querytype)){
				cardopenlosebackform.set("querytype", "");
				return mapping.findForward("errortest");	
			}
			
			if (("".equals(beginDate))||("".equals(endDate))){
				SessionErrors.add(request,EcardConstants.CARDOPENLOSEBACK_ERROR_EXIST,ErrorInfo.getErrorTip(statType,beginDate,endDate));	
				return mapping.findForward("errortest");			
			}
			
			
			setInit(request);
			List result = AdvqueryServiceUtil.getCardOpenLoseBack(beginDate,
					endDate, statType);
			if (result==null ||result.isEmpty()){
				SessionErrors.add(request, EcardConstants.CARDOPENLOSEBACK_ERROR_EXIST,ErrorInfo.getErrorTip(statType,beginDate,endDate));	
				return mapping.findForward("errortest");			
			}
			//判断是否用曲线图显示
			String errtip = ErrorInfo.DateRangeJudeg(showType,statType,beginDate,endDate,request);
			if (!"".equals(errtip)){
				SessionErrors.add(request, EcardConstants.CARDOPENLOSEBACK_ERROR_EXIST,errtip);		
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
			if ("bydate".equals(statType)){
				beginDate = DateUtil.reFormatTime(beginDate);
				endDate = DateUtil.reFormatTime(endDate);	
				statTypeShow = GetProperty.getProperties("title.date",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.date",this.servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("bymonth".equals(statType)){
				beginDate = DateUtil.getMonth(beginDate);
				endDate = DateUtil.getMonth(endDate);	
				statTypeShow = GetProperty.getProperties("title.month",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.month",this.servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}else if ("byweek".equals(statType)){
				beginDate = DateUtil.reFormatTime(beginDate);
				endDate = DateUtil.reFormatTime(endDate);	
				statTypeShow = GetProperty.getProperties("title.week",servlet.getServletContext());
				dateRange.append(GetProperty.getProperties("query.show.week",this.servlet.getServletContext()))
				.append(beginDate).append("-").append(endDate);
			}
		}
		private void statTypeResult(HttpServletRequest request,List result){
			if ("bydate".equals(statType)){
				yLabel = new GetListResultStat().getYLabelCard(result, "open",dataType);
				dataUnit = new GetListResultStat().getUnitValue(result, "open",dataType);
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
				yLabel = new GetListResultStat().getYLabelCard(result,"open",dataType);
				dataUnit = new GetListResultStat().getUnitValue(result,"open",dataType);
				xData = "balance_date";
				// 创建发卡，挂失，收回，补办卡数量图形数据集
				request.setAttribute("cardOpenLoseBackBarData", new DrawBarByTypeMap(
						result, accType, xData, dataType, columnTitle,dataUnit)
						.getDataProducer());
				showTextAxis = new ErrorInfo().showTextAxis(result);
			}else if ("byweek".equals(statType)){
				weekResult = new GetListResultStat().getListByWeek(result,beginDate,endDate);
				Collections.sort(weekResult,new SortListByResult("balance_date"));
				yLabel = new GetListResultStat().getYLabelCard(weekResult,"open",dataType);
				dataUnit = new GetListResultStat().getUnitValue(weekResult,"open",dataType);
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
