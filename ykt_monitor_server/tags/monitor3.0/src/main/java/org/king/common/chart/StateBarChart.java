package org.king.common.chart;

import org.jfree.chart.ChartUtilities;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.*;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.StandardXYBarPainter;
import org.jfree.data.time.SimpleTimePeriod;
import org.jfree.data.time.TimePeriodValues;
import org.jfree.data.time.TimePeriodValuesCollection;
import org.jfree.data.xy.XYDataset;

import java.awt.*;
import java.io.IOException;
import java.io.OutputStream;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

/**
 * 状态图.
 * User: Yiming.You
 * Date: 2010-8-11
 */
public class StateBarChart extends Chart {
    private String seriesName = "";

    /**
     * 要显示的数据，该数据的每一条记录为一个一维数组，其中，array[0]为startDate，array[1]为endDate，array[2]为value
     */
    private Object[][] data;

    //纵坐标的状态值对应的显示值
    private String[] states;

    //格式化提示日期
    private DateFormat toolTipDateFormat = new SimpleDateFormat("EEE yyyy-MM-dd HH:mm:ss", Locale.ENGLISH);

    //格式化横轴的日期
    private DateFormat dateFormat = new SimpleDateFormat("EEE yyyy-MM-dd", Locale.ENGLISH);

    private StateBarRenderer renderer = new StateBarRenderer();

    //是否显示series
    private boolean legend = false;

    //横轴时间间隔
    private DateTickUnit dateTickUnit = new DateTickUnit(DateTickUnitType.DAY, 1);

    private StateToolTipGenerator stateToolTipGenerator = new StateToolTipGenerator(toolTipDateFormat);

    public StateBarChart() {
    }

    public StateBarChart(String chartName) {
        super(chartName);
    }

    public StateBarChart(String chartName, int width, int height) {
        super(chartName, width, height);
    }

    public XYDataset getDataset() {
        TimePeriodValues timePeriodValues = new TimePeriodValues(getSeriesName());

        Date startDate;
        Date endDate;
        Number value;
        for (int i = 0; i < data.length; i++) {
            startDate = (Date) data[i][0];
            endDate = (Date) data[i][1];
            value = (Number) data[i][2];
            timePeriodValues.add(new SimpleTimePeriod(startDate, endDate), value);
        }
        TimePeriodValuesCollection dataset = new TimePeriodValuesCollection();
        dataset.addSeries(timePeriodValues);
        //dataset.setDomainIsPointsInTime(false);
        return dataset;
    }

    public void setPaints(Paint[] paints) {
        renderer.setPaints(paints);
    }

    public DateAxis getDomainAxis() {
        DateAxis domainAxis = new DateAxis(getAxisX());
        domainAxis.setVerticalTickLabels(true);
        domainAxis.setDateFormatOverride(dateFormat);
        domainAxis.setTickUnit(getDateTickUnit());
        domainAxis.setTickLabelFont(new Font("SansSerif", Font.PLAIN, 12));
        domainAxis.setLabelFont(new Font("SansSerif", Font.PLAIN, 14));
//        domainAxis.setAutoTickUnitSelection(false);
        return domainAxis;
    }

    public void setDomainTickUnit(DateTickUnitType type, int multiple) {
        setDateTickUnit(new DateTickUnit(type, multiple));
    }

    public void setDateTickUnit(DateTickUnit dateTickUnit) {
        this.dateTickUnit = dateTickUnit;
    }

    public DateTickUnit getDateTickUnit() {
        return dateTickUnit;
    }

    public ValueAxis getValueAxis() {
        SymbolAxis rangeAxis = new SymbolAxis(getAxisY(), states);
        rangeAxis.setUpperBound(getUpperBound());
        rangeAxis.setLowerBound(getLowerBound());
        rangeAxis.setTickLabelFont(new Font("SansSerif", Font.PLAIN, 12));
        rangeAxis.setLabelFont(new Font("SansSerif", Font.PLAIN, 14));
        return rangeAxis;
    }

    public XYPlot getXYPlot() {
        XYDataset dataset = getDataset();
        renderer.setDataset(dataset);
        renderer.setShadowVisible(false);
        renderer.setDrawBarOutline(false);
        //the default bar painter is GradientXYBarPainter
        renderer.setBarPainter(new StandardXYBarPainter());
        if (stateToolTipGenerator != null) {
            stateToolTipGenerator.setStates(states);
            renderer.setBaseToolTipGenerator(stateToolTipGenerator);
        }
        XYPlot plot = new XYPlot(dataset, getDomainAxis(), getValueAxis(), getRenderer());
        plot.setNoDataMessage("No data available");
        plot.setNoDataMessageFont(new Font("SansSerif", Font.BOLD, 16));
        return plot;
    }

    public JFreeChart getChart() {
        return new JFreeChart(getChartName(), JFreeChart.DEFAULT_TITLE_FONT, getXYPlot(), isLegend());
    }

    public void writeChartAsJPEG(OutputStream outputStream) throws IOException {
        ChartUtilities.writeChartAsJPEG(outputStream, 1, getChart(), getWidth(), getHeight(), null);
    }

    public StateBarRenderer getRenderer() {
        return renderer;
    }

    public void setRenderer(StateBarRenderer renderer) {
        this.renderer = renderer;
    }

    public StateToolTipGenerator getStateToolTipGenerator() {
        return stateToolTipGenerator;
    }

    public void setStateToolTipGenerator(StateToolTipGenerator stateToolTipGenerator) {
        this.stateToolTipGenerator = stateToolTipGenerator;
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

    public DateFormat getDateFormat() {
        return dateFormat;
    }

    public void setDateFormat(DateFormat dateFormat) {
        this.dateFormat = dateFormat;
    }

    public String getSeriesName() {
        return seriesName;
    }

    public void setSeriesName(String seriesName) {
        this.seriesName = seriesName;
    }

    public boolean isLegend() {
        return legend;
    }

    public void setLegend(boolean legend) {
        this.legend = legend;
    }

    public void setDayTickUnit(int day){
        dateTickUnit = new DateTickUnit(DateTickUnitType.DAY, day);
    }

    public void setMonthTickUnit(int month){
        dateTickUnit = new DateTickUnit(DateTickUnitType.MONTH, month);
    }

    public void setHourTickUnit(int hour){
        dateTickUnit = new DateTickUnit(DateTickUnitType.HOUR, hour);
    }
}
