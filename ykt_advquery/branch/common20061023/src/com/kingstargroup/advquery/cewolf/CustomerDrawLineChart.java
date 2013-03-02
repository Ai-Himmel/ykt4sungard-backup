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
 * �Զ�������ͼ����ʾ��ʽ
 * 
 * @author Administrator
 * 
 */
public class CustomerDrawLineChart {
	// �������ߵ�͸����
	private boolean showAlpha;

	// ��ʾͼ�α���ɫ
	private boolean showBackGround;

	// ����������ַ���
	private boolean showTextAxis;

	// ��ʾ������
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
			// ����ͼ�ε�͸����
			if (showAlpha) {
				plot.setForegroundAlpha(1.0f);
				
				// �Զ���ͼ������ʾ���
				StandardLegend legend = (StandardLegend) ((JFreeChart) chart).getLegend();
		        legend.setDisplaySeriesShapes(true);
		        legend.setShapeScaleX(0.8);
		        legend.setShapeScaleY(0.8);
		        legend.setDisplaySeriesLines(true);
		        
			}
			// ���ñ���ɫ
			if (showBackGround) {
				plot.setBackgroundPaint(new Color(247, 247, 247));
			}
			//��ʾͼ������
			if (showGrid) {
				plot.setDomainGridlinesVisible(true);
				plot.setDomainGridlinePaint(new Color(185,185,185));
				plot.setRangeGridlinesVisible(true);
				plot.setRangeGridlinePaint(new Color(185,185,185));
			}
			// ���ú���������ֵ���ת����
			if (showTextAxis) {
				CategoryAxis domainAxis = plot.getDomainAxis();
				domainAxis.setCategoryLabelPositions(CategoryLabelPositions
						.createUpRotationLabelPositions(Math.PI / 6.0));
			}
		}
	};

}
