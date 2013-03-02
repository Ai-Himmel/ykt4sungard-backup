/**
 * 
 */
package com.kingstargroup.ecard.portlet.advquery.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;

import com.kingstargroup.ecard.portlet.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawBarSingleMap;
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawPie;
import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.util.servlet.SessionErrors;


/**
 * 卡片使用情况
 * 
 * @author Administrator
 * 
 */
public class QueryCardUseAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		response.setCharacterEncoding("UTF-8");
		// 查询时传入日期参数
		DynaActionForm   carduseform = (DynaActionForm)form;
		
		String enddate = carduseform.getString("carduse_enddate");
		
		enddate = DateUtil.reFormatTime(enddate);
		
		// 定义柱形图显示时传入参数
		String fillData = "typename";
		String xData = "typename";
		String yData = "cardnum";
		String barDataType = "integer";
		
		String dataPie = "rate";
		String dataType = "float";

		// 自定义图表显示要传入的参数
		// 显示自定义颜色
		boolean showCustColor = true;
		// 显示横坐标文字的旋转方向
		boolean showTextAxis = false;
		// 显示Bar图标上的数字
		boolean showLabel = false;
		// 显示自定义图表背景颜色
		boolean showBackgroundColor = true;
		// 显示轮廓线
		boolean showOutLine = true;
		// 显示网格线
		boolean showGrid = true;
		HttpSession session = request.getSession();
		
		List result = AdvqueryServiceUtil.getCardUse(enddate);
		if (result.isEmpty()){
			SessionErrors.add(request, EcardConstants.CARDUSE_ERROR_EXIST,"没有你要查询的数据，请重新指定查询条件！");
			return mapping.findForward("errortest");			
		}
		request.setAttribute("result", result);

		request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid)
				.getChartPostProcessor());

		// 创建各卡类别所占数量图形数据集
		request.setAttribute(
				"cardUseVBarData",
				new DrawBarSingleMap(result, fillData, xData, yData,barDataType)
						.getDatasetProducer());
		// 创建各卡类别所占百分比图形数据集
		request.setAttribute(
				"cardUsePieData",
				new DrawPie(result, xData, dataPie, dataType)
						.getDatasetProducer());
		// 自定义饼图显示
		request.setAttribute("dataColorPie", new CustomerDrawChart(showBackgroundColor).getPiePostProcessor());

		return mapping.findForward("carduse_queryresult");
	}

}
