/**
 * 
 */
package com.kingstargroup.ecard.portlet.advquery.cewolf;

import java.awt.Color;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Map;

import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.CategoryAxis;
import org.jfree.chart.axis.CategoryLabelPositions;
import org.jfree.chart.axis.DateAxis;
import org.jfree.chart.axis.DateTickUnit;
import org.jfree.chart.labels.ItemLabelAnchor;
import org.jfree.chart.labels.ItemLabelPosition;
import org.jfree.chart.labels.StandardCategoryItemLabelGenerator;
import org.jfree.chart.plot.CategoryPlot;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.category.BarRenderer;
import org.jfree.ui.TextAnchor;

import de.laures.cewolf.ChartPostProcessor;
/**
 * 自定义图表横轴文字的方向，图表显示标签，图形显示颜色等
 * 
 * @author Administrator
 * 
 */
public class CustomerDrawChart {
	// 显示自定义颜色
	private boolean showCustColor;

	// 显示横坐标文字的旋转方向
	private boolean showTextAxis;

	// 显示Bar图标上的数字
	private boolean showLabel;

	// 显示自定义图表背景颜色
	private boolean showBackgroundColor;

	// 显示轮廓线
	private boolean showOutLine;

	// 显示网格线
	private boolean showGrid;
	
	//横坐标的刻度显示
	private int dateUnit;
	
	public CustomerDrawChart(boolean showCustColor, boolean showTextAxis,
			boolean showLabel, boolean showBackgroundColor,
			boolean showOutLine, boolean showGrid) {
		this.showCustColor = showCustColor;
		this.showTextAxis = showTextAxis;
		this.showLabel = showLabel;
		this.showBackgroundColor = showBackgroundColor;
		this.showOutLine = showOutLine;
		this.showGrid = showGrid;
	}
	
	public CustomerDrawChart(boolean showBackgroundColor){
		this.showBackgroundColor = showBackgroundColor;		
	}
	
	public CustomerDrawChart(boolean showBackgroundColor,boolean showCustColor,int dateUnit){
		this.showBackgroundColor = showBackgroundColor;		
		this.dateUnit = dateUnit;
		this.showCustColor = showCustColor;
	}
	
	/**
	 * 自定义饼图
	 * @return
	 */
	public ChartPostProcessor getPiePostProcessor() {
		return piePostProcessor;
	}

	/**
	 * 自定义线，柱形图的绘制
	 * @return
	 */
	public ChartPostProcessor getChartPostProcessor() {
		return chartPostProcessor;
	}
	
	/**
	 * 自定义时序图显示格式
	 * @return
	 */
	public ChartPostProcessor getTimeSeriesPostProcessor() {
		return timeSeriesPostProcessor;
	}

	private ChartPostProcessor chartPostProcessor = new ChartPostProcessor() {
		public void processChart(Object chart, Map params) {
			CategoryPlot plot = (CategoryPlot) ((JFreeChart) chart).getPlot();

			// 自定义颜色显示
			if (showCustColor) {
				for (int i = 0; i < params.size(); i++) {
					String colorStr = (String) params.get(String.valueOf(i));
					plot.getRenderer().setSeriesPaint(i,
							java.awt.Color.decode(colorStr));
				}
			}
			// 设置横轴标题文字的旋转方向
			if (showTextAxis) {
				CategoryAxis domainAxis = plot.getDomainAxis();
				domainAxis.setCategoryLabelPositions(CategoryLabelPositions
						.createUpRotationLabelPositions(Math.PI / 6.0));
			}

			// 定义显示标签
			if (showLabel) {
				BarRenderer renderer = (BarRenderer) plot.getRenderer();
				renderer
						.setBaseItemLabelGenerator(new StandardCategoryItemLabelGenerator());
				renderer.setBaseItemLabelsVisible(true);
				ItemLabelPosition p = new ItemLabelPosition(
						ItemLabelAnchor.OUTSIDE1, TextAnchor.CENTER_LEFT,
						TextAnchor.CENTER_LEFT, -Math.PI/2.0);
				renderer.setPositiveItemLabelPositionFallback(p);

			}

			// 定义是否绘制轮廓线
			if (showOutLine) {
				BarRenderer renderer = (BarRenderer) plot.getRenderer();
				renderer.setDrawBarOutline(true);
				renderer.setMinimumBarLength(0.05);
				renderer.setMaximumBarWidth(0.02);
			}

			// 设置自定义背景颜色
			if (showBackgroundColor) {
				plot.setBackgroundPaint(new Color(247, 247, 247));
			}
			
			// 显示网格线
			if (showGrid) {
				plot.setDomainGridlinesVisible(true);
				plot.setDomainGridlinePaint(new Color(185,185,185));
				plot.setRangeGridlinesVisible(true);
				plot.setRangeGridlinePaint(new Color(185,185,185));
			}
		}

	};
	private ChartPostProcessor piePostProcessor = new ChartPostProcessor() {
		public void processChart(Object chart, Map params) {
			// 设置自定义背景颜色
			if (showBackgroundColor) {
				((JFreeChart) chart).setBackgroundPaint(new Color(247, 247, 247));
			}
		}

	};
	private ChartPostProcessor timeSeriesPostProcessor = new ChartPostProcessor() {
		public void processChart(Object chart, Map params) {
			XYPlot plot = (XYPlot) ((JFreeChart) chart).getPlot();

			// 设置自定义背景颜色
			if (showBackgroundColor) {
				plot.setBackgroundPaint(new Color(247, 247, 247));
			}
			// 自定义颜色显示
			/*if (showCustColor) {
				for (int i = 0; i < params.size(); i++) {
					String colorStr = (String) params.get(String.valueOf(i));
					plot.getRenderer().setSeriesPaint(i,
							java.awt.Color.decode(colorStr));
				}
			}*/
			
			DateAxis domainAxis = new DateAxis();
			DateFormat df = new SimpleDateFormat("yyyyMMdd");
			DateTickUnit unit;
			if (0==dateUnit){
				unit = new DateTickUnit(DateTickUnit.DAY, 1, df);
			}else{
				unit = new DateTickUnit(DateTickUnit.DAY, dateUnit, df);
			}	        
			domainAxis.setTickUnit(unit);
			domainAxis.setVerticalTickLabels(false);
			plot.setDomainAxis(domainAxis);

		    //StandardXYItemRenderer renderer = 
				//(StandardXYItemRenderer) plot.getRenderer();
	        //renderer.setPlotShapes(true);
	        //renderer.setSeriesShapesFilled(0, Boolean.TRUE);
	        //renderer.setSeriesShapesFilled(1, Boolean.FALSE);

		}
	};

}
