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
 * �Զ���ͼ��������ֵķ���ͼ����ʾ��ǩ��ͼ����ʾ��ɫ��
 * 
 * @author Administrator
 * 
 */
public class CustomerDrawChart {
	// ��ʾ�Զ�����ɫ
	private boolean showCustColor;

	// ��ʾ���������ֵ���ת����
	private boolean showTextAxis;

	// ��ʾBarͼ���ϵ�����
	private boolean showLabel;

	// ��ʾ�Զ���ͼ������ɫ
	private boolean showBackgroundColor;

	// ��ʾ������
	private boolean showOutLine;

	// ��ʾ������
	private boolean showGrid;
	
	//������Ŀ̶���ʾ
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
	 * �Զ����ͼ
	 * @return
	 */
	public ChartPostProcessor getPiePostProcessor() {
		return piePostProcessor;
	}

	/**
	 * �Զ����ߣ�����ͼ�Ļ���
	 * @return
	 */
	public ChartPostProcessor getChartPostProcessor() {
		return chartPostProcessor;
	}
	
	/**
	 * �Զ���ʱ��ͼ��ʾ��ʽ
	 * @return
	 */
	public ChartPostProcessor getTimeSeriesPostProcessor() {
		return timeSeriesPostProcessor;
	}

	private ChartPostProcessor chartPostProcessor = new ChartPostProcessor() {
		public void processChart(Object chart, Map params) {
			CategoryPlot plot = (CategoryPlot) ((JFreeChart) chart).getPlot();

			// �Զ�����ɫ��ʾ
			if (showCustColor) {
				for (int i = 0; i < params.size(); i++) {
					String colorStr = (String) params.get(String.valueOf(i));
					plot.getRenderer().setSeriesPaint(i,
							java.awt.Color.decode(colorStr));
				}
			}
			// ���ú���������ֵ���ת����
			if (showTextAxis) {
				CategoryAxis domainAxis = plot.getDomainAxis();
				domainAxis.setCategoryLabelPositions(CategoryLabelPositions
						.createUpRotationLabelPositions(Math.PI / 6.0));
			}

			// ������ʾ��ǩ
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

			// �����Ƿ����������
			if (showOutLine) {
				BarRenderer renderer = (BarRenderer) plot.getRenderer();
				renderer.setDrawBarOutline(true);
				renderer.setMinimumBarLength(0.05);
				renderer.setMaximumBarWidth(0.02);
			}

			// �����Զ��屳����ɫ
			if (showBackgroundColor) {
				plot.setBackgroundPaint(new Color(247, 247, 247));
			}
			
			// ��ʾ������
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
			// �����Զ��屳����ɫ
			if (showBackgroundColor) {
				((JFreeChart) chart).setBackgroundPaint(new Color(247, 247, 247));
			}
		}

	};
	private ChartPostProcessor timeSeriesPostProcessor = new ChartPostProcessor() {
		public void processChart(Object chart, Map params) {
			XYPlot plot = (XYPlot) ((JFreeChart) chart).getPlot();

			// �����Զ��屳����ɫ
			if (showBackgroundColor) {
				plot.setBackgroundPaint(new Color(247, 247, 247));
			}
			// �Զ�����ɫ��ʾ
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
