/**
 * 
 */
package com.kingstargroup.ecard.portlet.advquery.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.portlet.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawBarSingleMap;
import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.ErrorInfo;
import com.kingstargroup.ecard.util.GetListResultStat;
import com.kingstargroup.ecard.util.GetProperty;
import com.liferay.util.servlet.SessionErrors;


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
		response.setCharacterEncoding("UTF-8");
		DynaActionForm savingsortform = (DynaActionForm)form;
		
		String querytype = savingsortform.getString("querytype");
		if(!"".equals(querytype)){
			savingsortform.set("querytype", "");
			return mapping.findForward("errortest");	
		}
		// 查询时要传入的参数
		String seriType = savingsortform.getString("seritype");
		//开始日期
		String beginDate = savingsortform.getString("savingsort_begindate");
		//结束日期
		String endDate = savingsortform.getString("savingsort_enddate");
		StringBuffer dateRange = new StringBuffer(200);
		String statTypeShow = "";
		//返回查询结果
		List weekResult = null;
		//开始周
		//String beginWeek = "";
		//结束周
		//String endWeek = "";
		String statType = savingsortform.getString("statType");
		if (("".equals(beginDate))||("".equals(endDate))){
			SessionErrors.add(request, EcardConstants.SAVINGSORT_ERROR_EXIST,ErrorInfo.getErrorTip(statType,beginDate,endDate));	
			return mapping.findForward("errortest");			
		}
		if ("bydate".equals(statType)){
			beginDate = DateUtil.reFormatTime(savingsortform.getString("savingsort_begindate"));
			endDate = DateUtil.reFormatTime(savingsortform.getString("savingsort_enddate"));
			statTypeShow = GetProperty.getProperties("title.date",this.servlet.getServletContext());
			dateRange.append(GetProperty.getProperties("query.show.date",this.servlet.getServletContext()))
			.append(beginDate).append("-").append(endDate);
		}else if ("bymonth".equals(statType)){
			beginDate = DateUtil.getMonth(savingsortform.getString("savingsort_begindate"));
			endDate = DateUtil.getMonth(savingsortform.getString("savingsort_enddate"));	
			statTypeShow = GetProperty.getProperties("title.date",this.servlet.getServletContext());
			dateRange.append(GetProperty.getProperties("query.show.month",this.servlet.getServletContext()))
			.append(beginDate).append("-").append(endDate);
		}else if ("byweek".equals(statType)){
			beginDate = DateUtil.reFormatTime(savingsortform.getString("savingsort_begindate"));
			endDate = DateUtil.reFormatTime(savingsortform.getString("savingsort_enddate"));	
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
		List result = AdvqueryServiceUtil.getSavingSortStat(seriType,beginDate, endDate,statType);
		if (result.isEmpty()){
			SessionErrors.add(request, EcardConstants.SAVINGSORT_ERROR_EXIST,
					getDevName(Integer.parseInt(seriType))+"："+ErrorInfo.getErrorTip(statType,beginDate,endDate));
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
			showTextAxis = ErrorInfo.showTextAxis(result);

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
			showTextAxis = ErrorInfo.showTextAxis(weekResult);
			
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
		case 204 :devName = "圈存转账";break;
		case 202 :devName = "POS充值";break;
		case 201 :devName = "现金充值";break;
		default :;
		}
		return devName;
	}
	
	private Log _log = LogFactory.getLog(QuerySavingSortStatAction.class);

}
