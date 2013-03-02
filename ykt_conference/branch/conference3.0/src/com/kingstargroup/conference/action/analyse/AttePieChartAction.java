package com.kingstargroup.conference.action.analyse;

import java.awt.Color;
import java.awt.Font;
import java.awt.RenderingHints;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartUtilities;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.labels.StandardPieSectionLabelGenerator;
import org.jfree.chart.plot.PiePlot;
import org.jfree.data.general.DefaultPieDataset;

public class AttePieChartAction extends Action {
	public ActionForward execute(ActionMapping mapping,ActionForm form,HttpServletRequest request,HttpServletResponse response) {
		List concount = null;
		if(request.getSession().getAttribute("concount")!=null){
			concount = (ArrayList)request.getSession().getAttribute("concount");
		} 
		
		response.setContentType("image/jpeg");
		try {
			JFreeChart chart = createPieChart(concount);
			ChartUtilities.writeChartAsJPEG(response.getOutputStream(),1.0f,chart,400,300,null);
		} catch(Exception e) {
			e.printStackTrace();
		}
		return null;
	}
	
	 public JFreeChart createPieChart(List concount) {  
	     //�ù����ഴ����ͼ  
	     JFreeChart pieChart = ChartFactory.createPieChart("",createDataset(concount),true,true,false);
	     
	     // RenderingHints��������Ⱦ�������޸�  
	     // VALUE_TEXT_ANTIALIAS_OFF��ʾ�����ֵĿ���ݹر�.  
	     pieChart.getRenderingHints().put(RenderingHints.KEY_TEXT_ANTIALIASING,RenderingHints.VALUE_TEXT_ANTIALIAS_OFF);  
	     //�õ���ͼ��Plot����  
	     PiePlot piePlot = (PiePlot) pieChart.getPlot();  
	     setSection(piePlot);  
	     setLabel(piePlot);  
	     setNoDataMessage(piePlot);  
	     setNullAndZeroValue(piePlot);  
	     pieChart.getLegend().setItemFont(new Font("����",Font.PLAIN,12));
	     return pieChart;
	 }  
		   
     public DefaultPieDataset createDataset(List concount) {  
         //��������  
         DefaultPieDataset pieDataset = new DefaultPieDataset();  
         if(concount!=null){
        	 pieDataset.setValue("ʵ�ʳ�ϯ", (Integer)concount.get(1));  
             pieDataset.setValue("���", (Integer)concount.get(2));  
             pieDataset.setValue("ȱϯ", (Integer)concount.get(3));  
         }
         return pieDataset;  
     }  
   
     public void setSection(PiePlot pieplot) {  
         //����������ɫ  
         pieplot.setSectionPaint("ʵ�ʳ�ϯ", new Color(160, 160, 255));  
         pieplot.setSectionPaint("���", Color.YELLOW);  
         pieplot.setSectionPaint("ȱϯ", new Color(96, 96, 191));  
         //��������������ʾ  
         pieplot.setExplodePercent("ȱϯ", 0.2D);  
         //���������߿򲻿ɼ�  
         pieplot.setSectionOutlinesVisible(false);  
     }  
		   
     public void setLabel(PiePlot pieplot) {  
         //����������ǩ��ʾ��ʽ���ؼ��֣�ֵ(�ٷֱ�) 
         pieplot.setLabelGenerator(new StandardPieSectionLabelGenerator("{0}��{1}({2})",NumberFormat.getNumberInstance(),new DecimalFormat("0.00%")));  
         pieplot.setMaximumLabelWidth(0.2);
         //����������ǩ��ɫ
         pieplot.setLabelBackgroundPaint(new Color(220, 220, 220));  
         pieplot.setLabelFont((new Font("����", Font.PLAIN, 12)));  
   
     }  
   
     public void setNoDataMessage(PiePlot pieplot) {  
         //����û������ʱ��ʾ����Ϣ  
         pieplot.setNoDataMessage("������");  
         //����û������ʱ��ʾ����Ϣ������  
         pieplot.setNoDataMessageFont(new Font("����", Font.BOLD, 14));  
         //����û������ʱ��ʾ����Ϣ����ɫ  
         pieplot.setNoDataMessagePaint(Color.red);  
     }  
   
     public void setNullAndZeroValue(PiePlot piePlot) {  
         //�����Ƿ����0��nullֵ  
          piePlot.setIgnoreNullValues(true);  
          piePlot.setIgnoreZeroValues(true);  
     } 
}
