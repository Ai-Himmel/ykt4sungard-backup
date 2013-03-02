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

import com.kingstargroup.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.advquery.cewolf.DrawBarConfTypeMap;
import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.common.GetListResultStat;
import com.kingstargroup.advquery.common.GetProperty;
import com.kingstargroup.advquery.common.SortListByResult;
import com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO;
import com.kingstargroup.advquery.tradeserial.TradeSerialDAO;

/**
 * 某一台POS机的消费情况统计
 * 
 * @author Administrator
 * 
 */
public class QueryConsumeStatByPosAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		//查询条件要参数
		String posId = request.getParameter("posid");
		//开始日期
		String beginDate = request.getParameter("begindate");
		//结束日期
		String endDate = request.getParameter("enddate");
		StringBuffer dateRange = new StringBuffer(200);
		String statTypeShow = "";
		//返回查询结果
		List weekResult = null;
		//选择的图形显示类型
		String showType = request.getParameter("showType");		
		String picType = "";
		//金额单位
		int dataUnit = 0;
		//Ｙ轴提示信息
		String yLabel = "";
		//查询类型参数（按日期范围查询或月份查询）
		String statType = request.getParameter("statType");
		if (("".equals(beginDate))||("".equals(endDate))){
			request.setAttribute("errorcont",new ErrorInfo().getErrorTip(statType,beginDate,endDate));
			return mapping.findForward("errortest");			
		}
		HttpSession session = request.getSession();
		session.setAttribute("posid",posId);
		if ("bydate".equals(statType)){
			beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
			endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
 			session.setAttribute("begindate32d",request.getParameter("begindate"));
			session.setAttribute("enddate32d",request.getParameter("enddate"));
			session.setAttribute("querytype32","0");
			statTypeShow = GetProperty.getProperties("title.date",this.servlet.getServletContext());
			dateRange.append(GetProperty.getProperties("query.show.date",this.servlet.getServletContext()))
			.append(beginDate).append("-").append(endDate);
		}else if ("bymonth".equals(statType)){
			beginDate = DateUtil.getMonth(request.getParameter("begindate"));
			endDate = DateUtil.getMonth(request.getParameter("enddate"));
 			session.setAttribute("begindate32m",request.getParameter("begindate"));
			session.setAttribute("enddate32m",request.getParameter("enddate"));
			session.setAttribute("querytype32","1");
			statTypeShow = GetProperty.getProperties("title.month",this.servlet.getServletContext());
			dateRange.append(GetProperty.getProperties("query.show.month",this.servlet.getServletContext()))
			.append(beginDate).append("-").append(endDate);
		}else if ("byweek".equals(statType)){
			beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
			endDate = DateUtil.reFormatTime(request.getParameter("enddate"));	
 			session.setAttribute("begindate32w",request.getParameter("begindate"));
			session.setAttribute("enddate32w",request.getParameter("enddate"));
			session.setAttribute("querytype32","2");
			//beginWeek = DateUtilExtend.getWeek(beginDate);
			//endWeek = DateUtilExtend.getWeek(endDate);	
			statTypeShow = GetProperty.getProperties("title.week",this.servlet.getServletContext());
			dateRange.append(GetProperty.getProperties("query.show.week",this.servlet.getServletContext()))
			.append(beginDate).append("-").append(endDate);
			
		}
		
		if (DateUtil.getIntervalTime(endDate,beginDate)>Long.valueOf("7862400000").longValue()){
			request.setAttribute("errorcont",new String("查询日期间隔不能大于两个月，请重新指定查询条件！"));
			return mapping.findForward("errortest");			
		}
		//绘制报表输入参数
		String accType[] = {"POS消费"};
		String xData = "";
		String showColumn = "tradefee";
		String dataType = "float";
		
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
		boolean showGrid = true;

		request.setAttribute("devname",getDevName(posId));
		List result = new TradeSerialDAO().getConsumeStatByPos(posId,
				beginDate, endDate,statType);
		if (result.isEmpty()){
			request.setAttribute("errorcont",getDevName(posId)+":"+new ErrorInfo().getErrorTip(statType,beginDate,endDate));
			return mapping.findForward("errortest");			
		}
		
		if (("bydate".equals(statType))||("bymonth".equals(statType))){
			request.setAttribute("result",result);
			yLabel = new GetListResultStat().getYLabelMoney(result,"tradefee",dataType);
			dataUnit = new GetListResultStat().getUnitValue(result,"tradefee",dataType);
			xData = "balance_date";
			request.setAttribute("ConsumeStatByPosChart",
					new DrawBarConfTypeMap(result,accType,xData,dataType,showColumn,dataUnit).getDataProducer());
			showTextAxis = new ErrorInfo().showTextAxis(result);
			
		}else if ("byweek".equals(statType)){
			weekResult = new GetListResultStat().getListByWeek(result,beginDate,endDate);
			Collections.sort(weekResult,new SortListByResult("balance_date"));
			yLabel = new GetListResultStat().getYLabelMoney(weekResult,"tradefee",dataType);
			dataUnit = new GetListResultStat().getUnitValue(weekResult,"tradefee",dataType);
			xData = "yearweek";
			request.setAttribute("result",weekResult);
			request.setAttribute("ConsumeStatByPosChart",
					new DrawBarConfTypeMap(weekResult,accType,xData,dataType,showColumn,dataUnit).getDataProducer());
			showTextAxis = new ErrorInfo().showTextAxis(weekResult);
			
		}
		//根据要显示的图形类别绘制图形
		if ("line".equals(showType)){
			picType = GetProperty.getProperties("pic.line",this.servlet.getServletContext());
			showOutLine = false;
		}else if ("bar".equals(showType)){
			picType = GetProperty.getProperties("pic.bar",this.servlet.getServletContext());
			showOutLine = true;
		}else if ("stack".equals(showType)){
			picType = GetProperty.getProperties("pic.stack",this.servlet.getServletContext());
			showOutLine = true;
		}
		
		request.setAttribute("ylabel",yLabel);
		request.setAttribute("pictype",picType);
		
		request.setAttribute("daterange",dateRange.toString());
		request.setAttribute("stattypeshow",statTypeShow);
		
		// 自定义图形显示
		request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid)
				.getChartPostProcessor());
		return mapping.findForward("consumestatbypos_queryresult");
	}
	
	private String getDevName(String posId){
		String devName = "";
		List list = new GetQueryConListDAO().getPosDeviceList(posId);
		Iterator iter = list.iterator();
		while (iter.hasNext()){
			Object row = (Object)iter.next();
			devName = row.toString();
		}
		return devName;
	}

	

}
