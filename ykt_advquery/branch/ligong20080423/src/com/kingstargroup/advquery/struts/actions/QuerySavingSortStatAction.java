/**
 * 
 */
package com.kingstargroup.advquery.struts.actions;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.advquery.cewolf.DrawBarSingleMap;
import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.common.GetListResultStat;
import com.kingstargroup.advquery.common.GetProperty;
import com.kingstargroup.advquery.reportoper.ReportOperDAO;

/**
 * 存款情况分类统计
 * 
 * @author Administrator
 * 
 */
public class QuerySavingSortStatAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		// 查询时要传入的参数
		String seriType = request.getParameter("seritype");
		//开始日期
		String beginDate = request.getParameter("begindate");
		//结束日期
		String endDate = request.getParameter("enddate");
		StringBuffer dateRange = new StringBuffer(200);
		String statTypeShow = "";
		//返回查询结果
		List weekResult = null;
		//开始周
		//String beginWeek = "";
		//结束周
		//String endWeek = "";
		String statType = request.getParameter("statType");
		if (("".equals(beginDate))||("".equals(endDate))){
			request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
			return mapping.findForward("errortest");			
		}
		HttpSession session = request.getSession();
		if ("bydate".equals(statType)){
			beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
			endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
 			session.setAttribute("begindate24d",request.getParameter("begindate"));
			session.setAttribute("enddate24d",request.getParameter("enddate"));
			session.setAttribute("querytype24","0");
			statTypeShow = GetProperty.getProperties("title.date",this.servlet.getServletContext());
			dateRange.append(GetProperty.getProperties("query.show.date",this.servlet.getServletContext()))
			.append(beginDate).append("-").append(endDate);
		}else if ("bymonth".equals(statType)){
			beginDate = DateUtil.getMonth(request.getParameter("begindate"));
			endDate = DateUtil.getMonth(request.getParameter("enddate"));	
 			session.setAttribute("begindate24m",request.getParameter("begindate"));
			session.setAttribute("enddate24m",request.getParameter("enddate"));
			session.setAttribute("querytype24","1");
			statTypeShow = GetProperty.getProperties("title.date",this.servlet.getServletContext());
			dateRange.append(GetProperty.getProperties("query.show.month",this.servlet.getServletContext()))
			.append(beginDate).append("-").append(endDate);
		}else if ("byweek".equals(statType)){
			beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
			endDate = DateUtil.reFormatTime(request.getParameter("enddate"));	
 			session.setAttribute("begindate24w",request.getParameter("begindate"));
			session.setAttribute("enddate24w",request.getParameter("enddate"));
			session.setAttribute("querytype24","2");
			//beginWeek = DateUtilExtend.getWeek(beginDate);
			//endWeek = DateUtilExtend.getWeek(endDate);	
			statTypeShow = GetProperty.getProperties("title.week",this.servlet.getServletContext());
			dateRange.append(GetProperty.getProperties("query.show.week",this.servlet.getServletContext()))
			.append(beginDate).append("-").append(endDate);
		}
		// 定义柱形图显示时传入参数
		String fillData = "devid";
		String xData = "devid";
		String yNumData = "num";
		String yNumDataType="integer";
		String yMoneyDataType="float";
		String yMoneyData = "money";

		// 自定义图表显示要传入的参数
		// 显示自定义颜色
		boolean showCustColor = true;
		// 显示横坐标文字的旋转方向
		boolean showTextAxis = true;
		// 显示Bar图标上的数字
		boolean showLabel = false;
		// 显示自定义图表背景颜色
		boolean showBackgroundColor = true;
		// 显示轮廓线
		boolean showOutLine = true;
		// 显示网格线
		boolean showGrid = false;

		request.setAttribute("devname",getDevName(Integer.parseInt(seriType)));
		List result = new ReportOperDAO().getSavingSortStat(seriType,beginDate, endDate,statType);
		if (result.isEmpty()){
			request.setAttribute("errorcont",getDevName(Integer.parseInt(seriType))+"："+new ErrorInfo().getErrorTip(statType,beginDate,endDate));
			return mapping.findForward("errortest");			
		}
		
		if (("bydate".equals(statType))||("bymonth".equals(statType))){
			request.setAttribute("result",result);
			// 显示存款笔数柱形图
			try {
				
				request.setAttribute(
						"savingSortNumChart",
						new DrawBarSingleMap(result, fillData, xData, yNumData,yNumDataType)
								.getDatasetProducer());
							
			} catch (NullPointerException e) {
				_log.error(e);
				return null;
			}

			// 显示存款金额柱形图
			
			try {			
				request.setAttribute(
						"savingSortMoneyChart",
						new DrawBarSingleMap(result, fillData, xData, yMoneyData,yMoneyDataType)
								.getDatasetProducer());
				
			} catch (NullPointerException e) {
				_log.error(e);
				return null;
			}
			showTextAxis = new ErrorInfo().showTextAxis(result);

		}else if ("byweek".equals(statType)){
			weekResult = new GetListResultStat().getListByWeek(result,beginDate,endDate);
			//Collections.sort(weekResult,new SortListByResult("balance_date"));
			request.setAttribute("result",weekResult);
			// 显示存款笔数柱形图
			try {
				
				request.setAttribute(
						"savingSortNumChart",
						new DrawBarSingleMap(weekResult, fillData, xData, yNumData,yNumDataType)
								.getDatasetProducer());
							
			} catch (NullPointerException e) {
				_log.error(e);
				return null;
			}

			// 显示存款金额柱形图
			
			try {			
				request.setAttribute(
						"savingSortMoneyChart",
						new DrawBarSingleMap(weekResult, fillData, xData, yMoneyData,yMoneyDataType)
								.getDatasetProducer());
				
			} catch (NullPointerException e) {
				_log.error(e);
				return null;
			}
			showTextAxis = new ErrorInfo().showTextAxis(weekResult);
			
		}

		request.setAttribute("daterange",dateRange);
		request.setAttribute("stattypeshow",statTypeShow);

		request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid)
				.getChartPostProcessor());
		
		return mapping.findForward("savingsort_result");
	}
	private String getDevName(int seriType){
		String devName = "";
		switch (seriType){
		case 240001 :devName = "圈存转账";break;
		case 240155 :devName = "内部转账";break;
		case 847105 :devName = "现金充值";break;
		case 930034 :devName = "POS充值";break;
		case 8471062 :devName = "支票充值";break;
		case 8471063 :devName = "经费本充值";break;
		case 8471064 :devName = "其它充值";break;
		default :;
		}
		return devName;
	}
	
	private Log _log = LogFactory.getLog(QuerySavingSortStatAction.class);

}
