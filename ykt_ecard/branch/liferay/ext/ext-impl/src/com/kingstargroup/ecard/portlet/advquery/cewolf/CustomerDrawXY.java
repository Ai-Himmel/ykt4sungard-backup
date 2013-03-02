package com.kingstargroup.ecard.portlet.advquery.cewolf;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Font;
import java.util.Map;

import org.jfree.chart.JFreeChart;
import org.jfree.chart.plot.CategoryPlot;
import org.jfree.chart.renderer.category.LineAndShapeRenderer;
import org.jfree.chart.title.LegendTitle;

import de.laures.cewolf.ChartPostProcessor;

public class CustomerDrawXY implements ChartPostProcessor {
	public void processChart(Object chart, Map params) {
		/*XYPlot plot = (XYPlot) ((JFreeChart) chart).getPlot();
		StandardXYItemRenderer rendererXY = (StandardXYItemRenderer) plot.getRenderer();
		rendererXY.setPlotShapes(true);
		rendererXY.setShapesFilled(true);
		
        // 设置纵轴标题文字的字体及其旋转方向
		ValueAxis rangeAxis = plot.getRangeAxis();
		rangeAxis.setLabelAngle(Math.PI/6);*/
		
        CategoryPlot plot = (CategoryPlot) ((JFreeChart) chart).getPlot();
		// 自定义图例的显示风格
        LegendTitle legend = ((JFreeChart) chart).getLegend();
        Font labelFont = new Font("Arial", Font.BOLD, 12); 
        legend.setItemFont(labelFont);
        
//		StandardLegend legend = (StandardLegend) ((JFreeChart) chart).getLegend();
//        legend.setDisplaySeriesShapes(true);
//        legend.setShapeScaleX(1.5);
//        legend.setShapeScaleY(1.5);
//        legend.setDisplaySeriesLines(true);

        // 获取渲染对象
        LineAndShapeRenderer renderer = (LineAndShapeRenderer) plot.getRenderer();
		// 自定义线段的绘制颜色
		Color color[] = new Color[1];
		color[0] = new Color(99,99,0);
		color[1] = new Color(255,169,66);
		color[2] = new Color(33,255, 66);
		color[3] = new Color(33,0,255);
		color[4] = new Color(255,0,66);
		for (int i = 0; i < color.length; i++)
		{
			renderer.setSeriesPaint(i, color[i]);
		}

		// 自定义线段的绘制风格
		BasicStroke bs ;
		for (int i = 0; i <1; i++)
		{
			float dashes[] = {10.0f};
			bs = new BasicStroke(2.0f, BasicStroke.CAP_ROUND, 
						BasicStroke.JOIN_ROUND, 10.f, dashes, 0.0f);
			if (i % 2 != 0)
				renderer.setSeriesStroke(i, bs);
			else
				renderer.setSeriesStroke(i, new BasicStroke(2.0f));
		}

        

	}
}
