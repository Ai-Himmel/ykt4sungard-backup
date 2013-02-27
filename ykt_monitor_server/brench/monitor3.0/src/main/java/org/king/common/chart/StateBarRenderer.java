package org.king.common.chart;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.jfree.chart.renderer.xy.XYBarRenderer;
import org.jfree.data.xy.XYDataset;

import java.awt.*;

/**
 * .��״̬ͼ�Ĳ�ͬ״̬��������Ⱦ�ɲ�ͬ��ɫ
 * User: yiming.you
 * Date: 2010-8-10
 */
public class StateBarRenderer extends XYBarRenderer {
    private static final Log log = LogFactory.getLog(StateBarRenderer.class);

    private XYDataset dataset;

    private Paint[] paints;

    public Paint getItemPaint(int row, int column) {
        double yValue = dataset.getYValue(row, column);
        try {
            int value = Double.valueOf(yValue).intValue();
            if (paints != null) {
                return paints[value];
            }
        } catch (Exception e) {
            log.error("can't find the special paint");
        }
        return super.getItemPaint(row, column);
    }

    public void setDataset(XYDataset dataset) {
        this.dataset = dataset;
    }

    public void setPaints(Paint[] paints) {
        this.paints = paints;
    }
}
