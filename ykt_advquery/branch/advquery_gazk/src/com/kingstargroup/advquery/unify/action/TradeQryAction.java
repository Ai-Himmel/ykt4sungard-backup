package com.kingstargroup.advquery.unify.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;


import com.kingstargroup.advquery.cewolf.CustomerDrawChart;

import com.kingstargroup.advquery.cewolf.DrawBarSingleMap;

import com.kingstargroup.advquery.hibernate.util.TradeUtil;

public class TradeQryAction extends Action{
	
	public ActionForward execute(ActionMapping mapping, 
			ActionForm form, 
			HttpServletRequest req, 
			HttpServletResponse res) throws Exception {
		
		/*try{
		String manIds = req.getSession().getAttribute("manIds").toString();
    	String count = req.getSession().getAttribute("count").toString();
    	String begindate = req.getSession().getAttribute("begindate").toString();
    	String enddate = req.getSession().getAttribute("enddate").toString();
    	String deptname = req.getSession().getAttribute("deptname").toString();
    	
    	List list  = TradeUtil.getavgTrade(manIds, begindate, enddate, deptname); 
    	
    

   	 
        // 绘制图形
		// 定义柱形图显示时传入参数
		String fillData = "avgFee";
		String xData = "opeDate";
		String yData = "avgFee";
		String barDataType = "float";
	   
        //自定义图表显示要传入的参数
		// 显示自定义颜色
		boolean showCustColor = true;
		// 显示横坐标文字的旋转方向
		boolean showTextAxis = false;
		// 显示Bar图标上的数字
		boolean showLabel = true;
		// 显示自定义图表背景颜色
		boolean showBackgroundColor = true;
		// 显示轮廓线
		boolean showOutLine = true;
		// 显示网格线
		boolean showGrid = true;
		
	
		req.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid).getChartPostProcessor());
		
		
		
       //创建各卡类别所占数量图形数据集
		req.setAttribute(
				"consAvgData",new DrawBarSingleMap(list, fillData, xData, yData,barDataType).getDatasetProducer());		
		
		//绘制图形显示结束
		String dateRange = ":"+begindate+"-"+enddate;
    	String specStatTip = deptname+dateRange+"人均月消费金额(元)";
    	 
    	req.setAttribute("specStatTip",specStatTip);
    	req.setAttribute("dateRange",dateRange);
   	    req.setAttribute("result",list);
   	    req.setAttribute("ylabel","单位:元");
    
	
         return  mapping.findForward("avgtraderesult");
	 }catch(Exception e){
    	 req.setAttribute("errorcont","查询数据异常Exception！");
    	 return mapping.findForward("error");
	 }
	
	}*/
    return null;
	}
}
