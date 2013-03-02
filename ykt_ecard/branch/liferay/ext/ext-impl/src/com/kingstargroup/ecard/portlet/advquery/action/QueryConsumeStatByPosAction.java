/**
 * 
 */
package com.kingstargroup.ecard.portlet.advquery.action;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.portlet.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawBarConfTypeMap;
import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.ErrorInfo;
import com.kingstargroup.ecard.util.GetListResultStat;
import com.kingstargroup.ecard.util.GetProperty;
import com.kingstargroup.ecard.util.SortListByResult;
import com.liferay.util.servlet.SessionErrors;

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
		response.setCharacterEncoding("UTF-8");
		DynaActionForm consumebyposform = (DynaActionForm) form;
		String querytype = consumebyposform.getString("querytype");
		if(!"".equals(querytype)){
			consumebyposform.set("querytype", "");
			return mapping.findForward("errortest");	
		}
		// 查询条件要参数
		String posId = consumebyposform.getString("posid");
		// 开始日期
		String beginDate = consumebyposform
				.getString("consumestatbypos_begindate");
		// 结束日期
		String endDate = consumebyposform.getString("consumestatbypos_enddate");

		StringBuffer dateRange = new StringBuffer(200);
		String statTypeShow = "";
		// 返回查询结果
		List weekResult = null;
		// 选择的图形显示类型
		String showType = consumebyposform.getString("showType");
		String picType = "";
		// 金额单位
		int dataUnit = 0;
		// Ｙ轴提示信息
		String yLabel = "";
		// 查询类型参数（按日期范围查询或月份查询）
		String statType = consumebyposform.getString("statType");
		if (("".equals(beginDate)) || ("".equals(endDate))) {
			SessionErrors.add(request, EcardConstants.CONSUMEBYPOS_ERROR_EXIST, ErrorInfo
					.getErrorTip(statType, beginDate, endDate));
			return mapping.findForward("errortest");
		}
		if("".equals(posId)){
			SessionErrors.add(request, EcardConstants.CONSUMEBYPOS_ERROR_EXIST, "请填写消费机号后再查询");
			return mapping.findForward("errortest");
		}
		if ("bydate".equals(statType)) {
			beginDate = DateUtil
					.reFormatTime(beginDate);
			endDate = DateUtil.reFormatTime(endDate);
			statTypeShow = GetProperty.getProperties("title.date", this.servlet
					.getServletContext());
			dateRange.append(
					GetProperty.getProperties("query.show.date", this.servlet
							.getServletContext())).append(beginDate)
					.append("-").append(endDate);
		} else if ("bymonth".equals(statType)) {
			beginDate = DateUtil.getMonth(beginDate);
			endDate = DateUtil.getMonth(endDate);
			statTypeShow = GetProperty.getProperties("title.month",
					this.servlet.getServletContext());
			dateRange.append(
					GetProperty.getProperties("query.show.month", this.servlet
							.getServletContext())).append(beginDate)
					.append("-").append(endDate);
		} else if ("byweek".equals(statType)) {
			beginDate = DateUtil
					.reFormatTime(beginDate);
			endDate = DateUtil.reFormatTime(endDate);
			statTypeShow = GetProperty.getProperties("title.week", this.servlet
					.getServletContext());
			dateRange.append(
					GetProperty.getProperties("query.show.week", this.servlet
							.getServletContext())).append(beginDate)
					.append("-").append(endDate);

		}

		if (DateUtil.getIntervalTime(endDate, beginDate) > Long.valueOf(
				"7862400000").longValue()) {
			SessionErrors.add(request, EcardConstants.CONSUMEBYPOS_ERROR_EXIST,
					"查询日期间隔不能大于两个月，请重新指定查询条件！");
			return mapping.findForward("errortest");
		}
		// 绘制报表输入参数
		String accType[] = { "POS消费" };
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

		request.setAttribute("devname", getDevName(posId));
		List result = AdvqueryServiceUtil.getConsumeStatByPos(posId, beginDate,
				endDate, statType);
		if (result.isEmpty()) {
			SessionErrors.add(request, EcardConstants.CONSUMEBYPOS_ERROR_EXIST,
					getDevName(posId)
							+ ":"
							+ ErrorInfo.getErrorTip(statType, beginDate,
									endDate));
			return mapping.findForward("errortest");
		}

		if (("bydate".equals(statType)) || ("bymonth".equals(statType))) {
			request.setAttribute("result", result);
			yLabel = new GetListResultStat().getYLabelMoney(result, "tradefee",
					dataType);
			dataUnit = new GetListResultStat().getUnitValue(result, "tradefee",
					dataType);
			xData = "balance_date";
			request.setAttribute("ConsumeStatByPosChart",
					new DrawBarConfTypeMap(result, accType, xData, dataType,
							showColumn, dataUnit).getDataProducer());
			showTextAxis = ErrorInfo.showTextAxis(result);

		} else if ("byweek".equals(statType)) {
			weekResult = new GetListResultStat().getListByWeek(result,
					beginDate, endDate);
			Collections.sort(weekResult, new SortListByResult("balance_date"));
			yLabel = new GetListResultStat().getYLabelMoney(weekResult,
					"tradefee", dataType);
			dataUnit = new GetListResultStat().getUnitValue(weekResult,
					"tradefee", dataType);
			xData = "yearweek";
			request.setAttribute("result", weekResult);
			request.setAttribute("ConsumeStatByPosChart",
					new DrawBarConfTypeMap(weekResult, accType, xData,
							dataType, showColumn, dataUnit).getDataProducer());
			showTextAxis = ErrorInfo.showTextAxis(weekResult);

		}
		// 根据要显示的图形类别绘制图形
		if ("line".equals(showType)) {
			picType = GetProperty.getProperties("pic.line", this.servlet
					.getServletContext());
			showOutLine = false;
		} else if ("bar".equals(showType)) {
			picType = GetProperty.getProperties("pic.bar", this.servlet
					.getServletContext());
			showOutLine = true;
		} else if ("stack".equals(showType)) {
			picType = GetProperty.getProperties("pic.stack", this.servlet
					.getServletContext());
			showOutLine = true;
		}

		request.setAttribute("ylabel", yLabel);
		request.setAttribute("pictype", picType);

		request.setAttribute("daterange", dateRange.toString());
		request.setAttribute("stattypeshow", statTypeShow);

		// 自定义图形显示
		request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,
				showGrid).getChartPostProcessor());
		return mapping.findForward("consumestatbypos_queryresult");
	}

	private String getDevName(String posId) {
		String devName = "";
		List list = AdvqueryServiceUtil.getPosDeviceList(posId);
		if (list != null) {
			Iterator iter = list.iterator();
			while (iter.hasNext()) {
				Object row = (Object) iter.next();
				devName = row.toString();
			}
		}
		return devName;
	}

}
