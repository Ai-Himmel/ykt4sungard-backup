package org.king.common.chart;

import org.jfree.chart.labels.StandardXYToolTipGenerator;
import org.jfree.data.time.TimePeriodValue;
import org.jfree.data.time.TimePeriodValues;
import org.jfree.data.time.TimePeriodValuesCollection;
import org.jfree.data.xy.XYDataset;
import org.king.utils.DateUtil;

import java.text.DateFormat;
import java.text.NumberFormat;
import java.util.Date;

/**
 * .
 * User: Yiming.You
 * Date: 2010-8-17
 */
public class StateToolTipGenerator extends StandardXYToolTipGenerator {

    private String[] states;

    public StateToolTipGenerator() {
        super(DEFAULT_TOOL_TIP_FORMAT, DateFormat.getInstance(), NumberFormat.getInstance());
    }

    public StateToolTipGenerator(DateFormat xFormat) {
        super(DEFAULT_TOOL_TIP_FORMAT, xFormat, NumberFormat.getInstance());
    }

    @Override
    public String generateLabelString(XYDataset dataset, int series, int item) {
        String result = null;
        dataset.getSeriesKey(series).toString();
        if (dataset instanceof TimePeriodValuesCollection) {
            TimePeriodValues timePeriodValues = ((TimePeriodValuesCollection) dataset).getSeries(series);
            TimePeriodValue timePeriodValue = timePeriodValues.getDataItem(item);
            Date start = timePeriodValue.getPeriod().getStart();
            Date end = timePeriodValue.getPeriod().getEnd();
            Number value = timePeriodValue.getValue();
            String duration = DateUtil.convertTime(end.getTime() - start.getTime(), DateUtil.duration, DateUtil.alias, 4);
            result = states[value.intValue()] + "&#10;";
            result += "From:" + getXDateFormat().format(start) + "&#10;";
            result += "To:" + getXDateFormat().format(end) + "&#10;";
            result += "Duration:" + duration;
        }
        return result;
    }

    public String[] getStates() {
        return states;
    }

    public void setStates(String[] states) {
        this.states = states;
    }
}
