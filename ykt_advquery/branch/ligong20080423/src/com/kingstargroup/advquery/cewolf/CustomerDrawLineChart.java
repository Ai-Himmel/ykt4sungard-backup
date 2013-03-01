/**
 * 
 */
package com.kingstargroup.advquery.cewolf;

import java.awt.Color;
import java.util.Map;

import org.jfree.chart.JFreeChart;
import org.jfree.chart.StandardLegend;
import org.jfree.chart.axis.CategoryAxis;
import org.jfree.chart.axis.CategoryLabelPositions;
import org.jfree.chart.plot.CategoryPlot;

import de.laures.cewolf.ChartPostProcessor;

/**
 * 自定义曲线图的显示格式
 * 
 * @author Administrator
 * 
 */
public class CustomerDrawLineChart {
	// 设置曲线的透明度
	private boolean showAlpha;

	// 显示图形背景色
	private boolean showBackGround;

	// 横坐标的文字方向
	private boolean showTextAxis;

	// 显示坐标线
	private boolean showGrid;

	public CustomerDrawLineChart(boolean showAlpha, boolean showBackGround,boolean showGrid,
			boolean showTextAxis) {
		this.showAlpha = showAlpha;
		this.showBackGround = showBackGround;
		this.showTextAxis = showTextAxis;
		this.showGrid = showGrid;
	}
	
	public ChartPostProcessor getChartPostProcessor(){
		return chartPostProcessor;
	}

	private ChartPostProcessor chartPostProcessor = new ChartPostProcessor() {
		public void processChart(Object chart, Map params) {
			CategoryPlot plot = ((JFreeChart) chart).getCategoryPlot();
			// 设置图形的透明度
			if (showAlpha) {
				plot.setForegroundAlpha(1.0f);
				
				// 自定义图例的显示风格
				StandardLegend legend = (StandardLegend) ((JFreeChart) chart).getLegend();
		        legend.setDisplaySeriesShapes(true);
		        legend.setShapeScaleX(0.8);
		        legend.setShapeScaleY(0.8);
		        legend.setDisplaySeriesLines(true);
		        
			}
			// 设置背景色
			if (showBackGround) {
				plot.setBackgroundPaint(new Color(247, 247, 247));
			}
			//显示图形网格
			if (showGrid) {
				plot.setDomainGridlinesVisible(true);
				plot.setDomainGridlinePaint(new Color(185,185,185));
				plot.setRangeGridlinesVisible(true);
				plot.setRangeGridlinePaint(new Color(185,185,185));
			}
			// 设置横轴标题文字的旋转方向
			if (showTextAxis) {
				CategoryAxis domainAxis = plot.getDomainAxis();
				domainAxis.setCategoryLabelPositions(CategoryLabelPositions
						.createUpRotationLabelPositions(Math.PI / 6.0));
			}
		}
	};

}
