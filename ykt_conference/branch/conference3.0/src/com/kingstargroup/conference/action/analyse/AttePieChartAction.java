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
	     //用工厂类创建饼图  
	     JFreeChart pieChart = ChartFactory.createPieChart("",createDataset(concount),true,true,false);
	     
	     // RenderingHints做文字渲染参数的修改  
	     // VALUE_TEXT_ANTIALIAS_OFF表示将文字的抗锯齿关闭.  
	     pieChart.getRenderingHints().put(RenderingHints.KEY_TEXT_ANTIALIASING,RenderingHints.VALUE_TEXT_ANTIALIAS_OFF);  
	     //得到饼图的Plot对象  
	     PiePlot piePlot = (PiePlot) pieChart.getPlot();  
	     setSection(piePlot);  
	     setLabel(piePlot);  
	     setNoDataMessage(piePlot);  
	     setNullAndZeroValue(piePlot);  
	     pieChart.getLegend().setItemFont(new Font("宋体",Font.PLAIN,12));
	     return pieChart;
	 }  
		   
     public DefaultPieDataset createDataset(List concount) {  
         //设置数据  
         DefaultPieDataset pieDataset = new DefaultPieDataset();  
         if(concount!=null){
        	 pieDataset.setValue("实际出席", (Integer)concount.get(1));  
             pieDataset.setValue("请假", (Integer)concount.get(2));  
             pieDataset.setValue("缺席", (Integer)concount.get(3));  
         }
         return pieDataset;  
     }  
   
     public void setSection(PiePlot pieplot) {  
         //设置扇区颜色  
         pieplot.setSectionPaint("实际出席", new Color(160, 160, 255));  
         pieplot.setSectionPaint("请假", Color.YELLOW);  
         pieplot.setSectionPaint("缺席", new Color(96, 96, 191));  
         //设置扇区分离显示  
         pieplot.setExplodePercent("缺席", 0.2D);  
         //设置扇区边框不可见  
         pieplot.setSectionOutlinesVisible(false);  
     }  
		   
     public void setLabel(PiePlot pieplot) {  
         //设置扇区标签显示格式：关键字：值(百分比) 
         pieplot.setLabelGenerator(new StandardPieSectionLabelGenerator("{0}：{1}({2})",NumberFormat.getNumberInstance(),new DecimalFormat("0.00%")));  
         pieplot.setMaximumLabelWidth(0.2);
         //设置扇区标签颜色
         pieplot.setLabelBackgroundPaint(new Color(220, 220, 220));  
         pieplot.setLabelFont((new Font("宋体", Font.PLAIN, 12)));  
   
     }  
   
     public void setNoDataMessage(PiePlot pieplot) {  
         //设置没有数据时显示的信息  
         pieplot.setNoDataMessage("无数据");  
         //设置没有数据时显示的信息的字体  
         pieplot.setNoDataMessageFont(new Font("宋体", Font.BOLD, 14));  
         //设置没有数据时显示的信息的颜色  
         pieplot.setNoDataMessagePaint(Color.red);  
     }  
   
     public void setNullAndZeroValue(PiePlot piePlot) {  
         //设置是否忽略0和null值  
          piePlot.setIgnoreNullValues(true);  
          piePlot.setIgnoreZeroValues(true);  
     } 
}
