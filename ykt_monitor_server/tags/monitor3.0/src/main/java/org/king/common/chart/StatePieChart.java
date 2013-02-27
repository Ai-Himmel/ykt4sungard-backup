package org.king.common.chart;

import org.jfree.chart.ChartUtilities;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.labels.StandardPieSectionLabelGenerator;
import org.jfree.chart.plot.PiePlot;
import org.jfree.data.general.DefaultPieDataset;

import java.awt.*;
import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;

/**
 * .
 * User: Yiming.You
 * Date: 2010-8-11
 */
public class StatePieChart extends Chart {
    /**
     * 要显示的数据，该数据的每一条记录为一个一维数组，其中，array[0]为状态值，array[1]为状态对应的值,该值为状态持续的毫秒数
     */
    private Object[][] data;

    //状态对应的显示值
    private String[] states;

    //设置每个扇区的颜色
    private Paint[] paints;

    //是否显示series
    private boolean legend = false;

    //爆炸模式，即设置饼图中的哪一块将分离出去
    private String explodeKey;

    public StatePieChart() {
    }

    public StatePieChart(String chartName) {
        super(chartName);
    }

    public StatePieChart(String chartName, int width, int height) {
        super(chartName, width, height);
    }

    public DefaultPieDataset getDataset() {
        DefaultPieDataset dataset = new DefaultPieDataset();
        for (int i = 0; i < data.length; i++) {
            int value = ((Integer) data[i][0]).intValue();
            dataset.setValue(states[value], (Number) data[i][1]);
        }
        return dataset;
    }

    public PiePlot getPiePlot() {
        PiePlot piePlot = new PiePlot(getDataset());
        piePlot.setNoDataMessage("No data available");
        if (paints != null && paints.length > 0) {
            for (int i = 0; i < paints.length; i++) {
                piePlot.setSectionPaint(states[i], paints[i]);
            }
        }
        piePlot.setNoDataMessage("No data available");
        piePlot.setLabelBackgroundPaint(new Color(220, 220, 220));
        piePlot.setBackgroundPaint(new Color(220, 220, 220));
//        piePlot.setNoDataMessagePaint(new Color(220, 220, 220));
        piePlot.setNoDataMessageFont(new Font("SansSerif", Font.BOLD, 16));
        piePlot.setLabelFont(new Font("SansSerif", Font.PLAIN, 14));
        piePlot.setLabelGenerator(new StandardPieSectionLabelGenerator("{0} ({2})"));
        if(getExplodeKey()!=null){
            piePlot.setExplodePercent(getExplodeKey(),0.10);
        }
        return piePlot;
    }

    public JFreeChart getChart() {
        return new JFreeChart(getChartName(), JFreeChart.DEFAULT_TITLE_FONT, getPiePlot(), isLegend());
    }

    @Override
    public void writeChartAsJPEG(OutputStream outputStream) throws IOException {
        ChartUtilities.writeChartAsJPEG(outputStream, 1, getChart(), getWidth(), getHeight(), null);
    }

    public boolean isLegend() {
        return legend;
    }

    public void setLegend(boolean legend) {
        this.legend = legend;
    }

    public Object[][] getData() {
        return data;
    }

    public void setData(Object[][] data) {
        this.data = data;
    }

    public String[] getStates() {
        return states;
    }

    public void setStates(String[] states) {
        this.states = states;
    }

    public Paint[] getPaints() {
        return paints;
    }

    public void setPaints(Paint[] paints) {
        this.paints = paints;
    }

    public String getExplodeKey() {
        return explodeKey;
    }

    public void setExplodeKey(String explodeKey) {
        this.explodeKey = explodeKey;
    }
}
