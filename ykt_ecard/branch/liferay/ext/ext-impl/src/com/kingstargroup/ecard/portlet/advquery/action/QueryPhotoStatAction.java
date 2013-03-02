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
import com.kingstargroup.ecard.portlet.advquery.cewolf.DrawBarConfTypeMap;
import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.ErrorInfo;
import com.kingstargroup.ecard.util.GetListResultStat;
import com.kingstargroup.ecard.util.GetProperty;
import com.liferay.util.servlet.SessionErrors;
/**
 * 拍照情况统计
 * @author Administrator
 *
 */
public class QueryPhotoStatAction extends Action{

	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest request, 
			HttpServletResponse response) throws Exception {
		response.setCharacterEncoding("UTF-8");
		DynaActionForm pohotform = (DynaActionForm) form;
		List typeList = AdvqueryServiceUtil.getEmpType();
		request.setAttribute("typeList", typeList);
		String querytype = pohotform.getString("querytype");
		if(!"".equals(querytype)){
			pohotform.set("querytype", "");
			return mapping.findForward("errortest");	
		}		
		String cutType = pohotform.getString("emptype");
		//金额单位
		int dataUnit = 0;
		//Ｙ轴提示信息
		String yLabel = "";
		//开始日期
		String beginDate = pohotform.getString("photo_begindate");
		//结束日期
		String endDate = pohotform.getString("photo_enddate");
		String dateRange = "";
		String statTypeShow = "";
		List result = null;
		String statType = pohotform.getString("statType");
		if (("".equals(beginDate)) || ("".equals(endDate))) {
			SessionErrors.add(request, EcardConstants.PHOTO_ERROR_EXIST, ErrorInfo
					.getErrorTip(statType, beginDate, endDate));
			return mapping.findForward("errortest");
		}
		HttpSession session = request.getSession();
		session.setAttribute("cuttype",cutType);
		if ("bydate".equals(statType)){
			beginDate = DateUtil.reFormatTime(pohotform.getString("photo_begindate"));
			endDate = DateUtil.reFormatTime(pohotform.getString("photo_enddate"));	
			statTypeShow = GetProperty.getProperties("title.date",this.servlet.getServletContext());
		}else if ("bymonth".equals(statType)){
			beginDate = DateUtil.getMonth(pohotform.getString("photo_begindate"));
			endDate = DateUtil.getMonth(pohotform.getString("photo_enddate"));	
			statTypeShow = GetProperty.getProperties("title.month",this.servlet.getServletContext());
		}
		dateRange = ':'+beginDate+'-'+endDate;
		
		//生成图表要传入的参数
		String accType[] = {"拍照情况统计"};
		String xData = "photo_date";
		String showColumn = "photonum";
		String dataType = "integer";
		
		// 自定义图表显示要传入的参数
		// 显示自定义颜色
		boolean showCustColor = true;
		// 显示横坐标文字的旋转方向
		boolean showTextAxis ;
		// 显示Bar图标上的数字
		boolean showLabel = false;
		// 显示自定义图表背景颜色
		boolean showBackgroundColor = true;
		// 显示轮廓线
		boolean showOutLine = true;
		// 显示网格线
		boolean showGrid = true;
		if ("all".equals(cutType)){
			result = AdvqueryServiceUtil.getphotoNumAll(beginDate,endDate,statType);
			request.setAttribute("cuttype","所有人");
		}else{
			result = AdvqueryServiceUtil.getphotoNumByType(cutType,beginDate,endDate,statType);
			request.setAttribute("cuttype",cutType);
		}
		
		if (result.isEmpty()) {
			SessionErrors.add(request, EcardConstants.PHOTO_ERROR_EXIST, ErrorInfo
					.getErrorTip(statType, beginDate, endDate));
			return mapping.findForward("errortest");
		}
		showTextAxis = ErrorInfo.showTextAxis(result);
		request.setAttribute("daterange",dateRange);
		
		yLabel = new GetListResultStat().getYLabelManNum(result,"photonum",dataType);
		dataUnit = new GetListResultStat().getUnitValue(result,"photonum",dataType);
		request.setAttribute("result",result);
		request.setAttribute("ylabel",yLabel);
		request.setAttribute("stattypeshow",statTypeShow);
		request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid)
				.getChartPostProcessor());
		
		request.setAttribute("photoChart",
				new DrawBarConfTypeMap(result,accType,xData,dataType,showColumn,dataUnit).getDataProducer());
		return mapping.findForward("photo_queryresult");
	}

}
