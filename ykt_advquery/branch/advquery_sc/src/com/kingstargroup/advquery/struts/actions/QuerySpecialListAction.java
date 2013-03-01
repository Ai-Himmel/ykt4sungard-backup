/**
 * 
 */
package com.kingstargroup.advquery.struts.actions;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.advquery.cewolf.CustomerDrawChart;
import com.kingstargroup.advquery.cewolf.DrawBarSingleMap;
import com.kingstargroup.advquery.common.DateUtil;
import com.kingstargroup.advquery.common.DateUtilExtend;
import com.kingstargroup.advquery.common.ErrorInfo;
import com.kingstargroup.advquery.tradeserial.TradeSerialDAO;

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
		
		// 开始日期
		String beginDate = request.getParameter("begindate").toString();
		// 结束日期
		String endDate = request.getParameter("enddate").toString();
		// 日期不能为空
		if (("".equals(beginDate)) || ("".equals(endDate))) {
			request.setAttribute("errorcont", new ErrorInfo().getErrorTip(
					"bydate", beginDate, endDate));
			return mapping.findForward("errortest");
		}
		
		int datenum = (int)DateUtilExtend.diffDate(DateUtil.reFormatTime(beginDate),DateUtil.reFormatTime(endDate));
		
		
		
		if ("".equals(request.getParameter("per"))
				||(Integer.parseInt(request.getParameter("per").toString()))>datenum) {
			request.setAttribute("errorcont", new String(
					"消费频度不能为空且不能大于日期差，请重新输入！"));
			return mapping.findForward("errortest");
		}
		
		String meal = nullToString(request.getParameter("meal"));
		//String bDate = beginDate;//nullToString(request.getParameter("begindate"));
		//String eDate = nullToString(request.getParameter("enddate"));
		String deptNo = nullToString(request.getParameter("deptNo"));
		String specNo = nullToString(request.getParameter("specNo"));
		String classNo = nullToString(request.getParameter("classNo"));
		int custType = Integer.parseInt(nullToString(request.getParameter("custType")));
		int feeType = Integer.parseInt(nullToString(request.getParameter("feeType")));
		String bStuempNo = nullToString(request.getParameter("bStuempNo"));
		String eStuempNo = nullToString(request.getParameter("eStuempNo"));
		int per = Integer.parseInt(nullToString(request.getParameter("per").toString()));
		String selPer = request.getParameter("selPer").toString();
		int perRange = 0;
		float bavgRange = 0;
		float eavgRange = 0;
		if (!"".equals(request.getParameter("bavgRange").toString())) {
			bavgRange = Float.parseFloat(request.getParameter("bavgRange").toString());
		}
		if (!"".equals(request.getParameter("eavgRange").toString())) {
			eavgRange = Float.parseFloat(request.getParameter("eavgRange").toString());
		}
		
		if (!"".equals(selPer)){
			if ("".equals(request.getParameter("perRange"))){
				request.setAttribute("errorcont", new String(
				"选择了平均值浮动，但输入的浮动范围值不正确，请重新输入！"));
				return mapping.findForward("errortest");
				
			}else{
				perRange = Integer.parseInt(request.getParameter("perRange").toString());
			}
		}
		//如果开始值大于零，并且开始值大于结束值，提示错误信息
		if (bavgRange>0){
			if (bavgRange>eavgRange){
				request.setAttribute("errorcont", new String(
				"平均值范围开始值不能大于结束值，为零则不使用平均值过滤查询结果，请重新输入！"));
				return mapping.findForward("errortest");
				
			}
		}
		
		HttpSession session = request.getSession();
		session.setAttribute("meal",String.valueOf(meal));
		session.setAttribute("begindate27d",String.valueOf(beginDate));
		session.setAttribute("enddate27d",String.valueOf(endDate));
		session.setAttribute("deptNo",String.valueOf(deptNo));
		session.setAttribute("specNo",String.valueOf(specNo));
		session.setAttribute("classNo",String.valueOf(classNo));
		session.setAttribute("custType",String.valueOf(custType));
		session.setAttribute("feeType",String.valueOf(feeType));
		session.setAttribute("bStuempNo",String.valueOf(bStuempNo));
		session.setAttribute("eStuempNo",String.valueOf(eStuempNo));
		session.setAttribute("per",String.valueOf(per));
		session.setAttribute("bavgRange",String.valueOf(bavgRange));
		session.setAttribute("eavgRange",String.valueOf(eavgRange));
		session.setAttribute("selPer",String.valueOf(selPer));
		session.setAttribute("perRange",String.valueOf(perRange));
		
		beginDate = DateUtil.reFormatTime(request.getParameter("begindate"));
		endDate = DateUtil.reFormatTime(request.getParameter("enddate"));
		List resultList = new TradeSerialDAO().getSpecialList(beginDate,endDate,deptNo,specNo,classNo,custType,
				feeType,bStuempNo,eStuempNo,per,meal,bavgRange,eavgRange,selPer,perRange);
		List resultAvg = new TradeSerialDAO().getSpecStat(meal);
		List result3 = new TradeSerialDAO().getConsemeAvg(meal,beginDate,endDate);
		if (null==resultList){
			request.setAttribute("errorcont", new ErrorInfo().getErrorTip(
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
}
