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
    	
    

   	 
        // ����ͼ��
		// ��������ͼ��ʾʱ�������
		String fillData = "avgFee";
		String xData = "opeDate";
		String yData = "avgFee";
		String barDataType = "float";
	   
        //�Զ���ͼ����ʾҪ����Ĳ���
		// ��ʾ�Զ�����ɫ
		boolean showCustColor = true;
		// ��ʾ���������ֵ���ת����
		boolean showTextAxis = false;
		// ��ʾBarͼ���ϵ�����
		boolean showLabel = true;
		// ��ʾ�Զ���ͼ������ɫ
		boolean showBackgroundColor = true;
		// ��ʾ������
		boolean showOutLine = true;
		// ��ʾ������
		boolean showGrid = true;
		
	
		req.setAttribute("dataColor", new CustomerDrawChart(showCustColor,
				showTextAxis, showLabel, showBackgroundColor, showOutLine,showGrid).getChartPostProcessor());
		
		
		
       //�������������ռ����ͼ�����ݼ�
		req.setAttribute(
				"consAvgData",new DrawBarSingleMap(list, fillData, xData, yData,barDataType).getDatasetProducer());		
		
		//����ͼ����ʾ����
		String dateRange = ":"+begindate+"-"+enddate;
    	String specStatTip = deptname+dateRange+"�˾������ѽ��(Ԫ)";
    	 
    	req.setAttribute("specStatTip",specStatTip);
    	req.setAttribute("dateRange",dateRange);
   	    req.setAttribute("result",list);
   	    req.setAttribute("ylabel","��λ:Ԫ");
    
	
         return  mapping.findForward("avgtraderesult");
	 }catch(Exception e){
    	 req.setAttribute("errorcont","��ѯ�����쳣Exception��");
    	 return mapping.findForward("error");
	 }
	
	}*/
    return null;
	}
}
