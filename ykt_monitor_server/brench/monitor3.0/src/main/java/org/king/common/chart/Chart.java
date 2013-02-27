package org.king.common.chart;

import org.jfree.chart.JFreeChart;

import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;

/**
 * .
 * User: Yiming.You
 * Date: 2010-8-11
 */
public abstract class Chart {
    private String chartName = "Time Period State";

    private String axisX = "Date";

    private String axisY = "State";

    private int width = 800;

    private int height = 600;

    private int upperBound;

    private int lowerBound = 0;

    public Chart() {
    }

    public Chart(String chartName) {
        this.chartName = chartName;
    }

    public Chart(String chartName, int width, int height) {
        this.chartName = chartName;
        this.width = width;
        this.height = height;
    }

    public abstract JFreeChart getChart();

    public abstract void writeChartAsJPEG(OutputStream outputStream) throws IOException;

    public String getChartName() {
        return chartName;
    }

    public void setChartName(String chartName) {
        this.chartName = chartName;
    }

    public String getAxisX() {
        return axisX;
    }

    public void setAxisX(String axisX) {
        this.axisX = axisX;
    }

    public String getAxisY() {
        return axisY;
    }

    public void setAxisY(String axisY) {
        this.axisY = axisY;
    }

    public int getWidth() {
        return width;
    }

    public void setWidth(int width) {
        this.width = width;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public int getUpperBound() {
        return upperBound;
    }

    public void setUpperBound(int upperBound) {
        this.upperBound = upperBound;
    }

    public int getLowerBound() {
        return lowerBound;
    }

    public void setLowerBound(int lowerBound) {
        this.lowerBound = lowerBound;
    }
}
