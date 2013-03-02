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
import com.kingstargroup.ecard.portlet.advquery.service.AdvqueryServiceUtil;
import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.DateUtilExtend;
import com.kingstargroup.ecard.util.EcardConstants;
import com.kingstargroup.ecard.util.ErrorInfo;
import com.liferay.util.servlet.SessionErrors;

/**
 * 贫困生分析
 * 
 * @author Administrator
 * 
 */
public class QuerySpecialListAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		response.setCharacterEncoding("UTF-8");
		DynaActionForm speciallistform = (DynaActionForm) form;
		
		List detpList = AdvqueryServiceUtil.getDeptList();
		request.setAttribute("deptList", detpList);
		List specList = AdvqueryServiceUtil.getSpecialityList();
		request.setAttribute("specList", specList);
		List custtypeList = AdvqueryServiceUtil.getCusttypeList();
		request.setAttribute("custtypeList", custtypeList);
		List feetypeList = AdvqueryServiceUtil.getFeeTypeList();
		request.setAttribute("feetypeList", feetypeList);
		
		// 开始日期
		String beginDate = speciallistform.getString("speciallist_begindate");
		// 结束日期
		String endDate = speciallistform.getString("speciallist_enddate");
		// 日期不能为空
		if (("".equals(beginDate)) || ("".equals(endDate))) {
			SessionErrors.add(request, EcardConstants.SPECIALLIST_ERROR_EXIST, ErrorInfo
					.getErrorTip("bydate", beginDate, endDate));
			return mapping.findForward("errortest");
		}

		int datenum = (int)DateUtilExtend.diffDate(DateUtil.reFormatTime(beginDate),DateUtil.reFormatTime(endDate));
		
		
		
		if ("".equals(speciallistform.getString("per"))
				||(Integer.parseInt(speciallistform.getString("per").toString()))>datenum) {
			SessionErrors.add(request, EcardConstants.SPECIALLIST_ERROR_EXIST, "消费频度不能为空且不能大于日期差，请重新输入！");
			return mapping.findForward("errortest");
		}
		
		String meal = nullToString(speciallistform.getString("meal"));
		String deptNo = nullToString(speciallistform.getString("deptNo"));
		String specNo = nullToString(speciallistform.getString("specNo"));
		String classNo = nullToString(speciallistform.getString("classNo"));
		int custType = Integer.parseInt(nullToInt(speciallistform.getString("custType")));
		int feeType = Integer.parseInt(nullToInt(speciallistform.getString("feeType")));
		String bStuempNo = nullToString(speciallistform.getString("bStuempNo"));
		String eStuempNo = nullToString(speciallistform.getString("eStuempNo"));
		int per = Integer.parseInt(nullToInt(speciallistform.getString("per")));
		String selPer = speciallistform.getString("selPer");
		int perRange = 0;
		float bavgRange = 0;
		float eavgRange = 0;
		if (!"".equals(speciallistform.getString("bavgRange"))) {
			bavgRange = Float.parseFloat(speciallistform.getString("bavgRange"));
		}
		if (!"".equals(speciallistform.getString("eavgRange"))) {
			eavgRange = Float.parseFloat(speciallistform.getString("eavgRange"));
		}
		
		if (!"".equals(selPer)){
			if ("".equals(speciallistform.getString("perRange"))){
				SessionErrors.add(request, EcardConstants.SPECIALLIST_ERROR_EXIST, "选择了平均值浮动，但输入的浮动范围值不正确，请重新输入！");
				return mapping.findForward("errortest");
				
			}else{
				perRange = Integer.parseInt(speciallistform.getString("perRange"));
			}
		}
		
		if(bavgRange<0 || eavgRange<0){
			SessionErrors.add(request, EcardConstants.SPECIALLIST_ERROR_EXIST, "平均值范围不能为负值，请重新输入！");
			return mapping.findForward("errortest");
			
		}
		
		//如果开始值大于零，并且开始值大于结束值，提示错误信息
		if (bavgRange>=0){
			if (bavgRange>eavgRange){
				SessionErrors.add(request, EcardConstants.SPECIALLIST_ERROR_EXIST, "平均值范围开始值不能大于结束值，为零则不使用平均值过滤查询结果，请重新输入！");
				return mapping.findForward("errortest");
				
			}
		}
		
		
		beginDate = DateUtil.reFormatTime(beginDate);
		endDate = DateUtil.reFormatTime(endDate);
//		List resultList = null;
		List resultList = AdvqueryServiceUtil.getSpecialList(beginDate,endDate,deptNo,specNo,classNo,custType,
				feeType,bStuempNo,eStuempNo,per,meal,bavgRange,eavgRange,selPer,perRange);
		List resultAvg = AdvqueryServiceUtil.getSpecStat(beginDate,endDate,deptNo,specNo,classNo,custType,
				feeType,bStuempNo,eStuempNo,per,meal,bavgRange,eavgRange,selPer,perRange);
		List result3 = AdvqueryServiceUtil.getConsemeAvg(beginDate,endDate,deptNo,specNo,classNo,custType,
				feeType,bStuempNo,eStuempNo,per,meal,bavgRange,eavgRange,selPer,perRange);
		if (resultList.isEmpty()||resultList.size()==0) {
			SessionErrors.add(request, EcardConstants.SPECIALLIST_ERROR_EXIST,ErrorInfo.getErrorTip(
					"bydate", beginDate, endDate));
			return mapping.findForward("errortest");
		}
		String specStatTip = "年度"+mealTrans(meal)+"均消费金额(元)";
		String dateRange = ":"+beginDate+"-"+endDate+"(共"+datenum+"天)";
		request.setAttribute("daterange",dateRange);
		request.setAttribute("resultAvg",resultAvg);
		request.setAttribute("result3",result3);
		request.setAttribute("resultList",resultList);
		request.setAttribute("specStatTip",specStatTip);
		request.setAttribute("ylabel","单位:人");
		request.setAttribute("mealStr",mealTrans(meal));
		
		//绘制图形
		// 定义柱形图显示时传入参数
		String fillData = "amavg";
		String xData = "amavg";
		String yData = "num";
		String barDataType = "integer";
		// 自定义图表显示要传入的参数
		// 显示自定义颜色
		boolean showCustColor = true;
		// 显示横坐标文字的旋转方向
		boolean showTextAxis = false;
		// 显示Bar图标上的数字
		boolean showLabel = true;
		// 显示自定义图表背景颜色
		boolean showBackgroundColor = true;
		// 显示轮廓线
		boolean showOutLine = false;
		// 显示网格线
		boolean showGrid = true;
		
		request.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid)
				.getChartPostProcessor());

		// 创建各卡类别所占数量图形数据集
		request.setAttribute(
				"consAvgData",
				new DrawBarSingleMap(result3, fillData, xData, yData,barDataType)
						.getDatasetProducer());				
		//绘制图形显示结束		
		return mapping.findForward("speciallist_queryresult");
	}
	
	private String mealTrans(String in){
		if ("bk".equals(in.trim())){
			return "早餐";
		}else if ("lun".equals(in.trim())){
			return "午餐";
		}else if ("sup".equals(in.trim())){
			return "晚餐";
		}else{
			return "全天";
		}
	}

	private String nullToString(Object o){
		if (o==null){
			return "";
		}else{
			return o.toString();
		}
	}
	private String nullToInt(Object o){		
		if (o==null||"".equals(o)){
			return "0";
		}else{
			return o.toString();
		}
	}
}
