package org.king.common.chart;

import junit.framework.TestCase;
import org.jfree.chart.ChartUtilities;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.DateAxis;
import org.jfree.chart.axis.DateTickUnit;
import org.jfree.chart.axis.DateTickUnitType;
import org.jfree.chart.axis.SymbolAxis;
import org.jfree.chart.plot.XYPlot;
import org.jfree.data.time.Day;
import org.jfree.data.time.SimpleTimePeriod;
import org.jfree.data.time.TimePeriodValues;
import org.jfree.data.time.TimePeriodValuesCollection;
import org.jfree.data.xy.XYDataset;

import java.awt.*;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

/**
 * .
 * User: Yiming.You
 * Date: 2010-8-11
 */
public class ChartTest extends TestCase {

    private DateFormat dateFormat = new SimpleDateFormat("yyyyMMddHHmmss");

    private Object[][] getBarData() throws ParseException {
        Object[][] data = new Object[10][3];
        data[0][0] = dateFormat.parse("20100725092541");
        data[0][1] = dateFormat.parse("20100726103242");
        data[0][2] = Integer.valueOf(1);

        data[1][0] = dateFormat.parse("20100726103242");
        data[1][1] = dateFormat.parse("20100727113316");
        data[1][2] = Integer.valueOf(3);

        data[2][0] = dateFormat.parse("20100727113316");
        data[2][1] = dateFormat.parse("20100728234256");
        data[2][2] = Integer.valueOf(2);

        data[3][0] = dateFormat.parse("20100728234256");
        data[3][1] = dateFormat.parse("20100729085631");
        data[3][2] = Integer.valueOf(4);

        data[4][0] = dateFormat.parse("20100729085631");
        data[4][1] = dateFormat.parse("20100730042233");
        data[4][2] = Integer.valueOf(1);

        data[5][0] = dateFormat.parse("20100730042233");
        data[5][1] = dateFormat.parse("20100801164126");
        data[5][2] = Integer.valueOf(2);

        data[6][0] = dateFormat.parse("20100801164126");
        data[6][1] = dateFormat.parse("20100802153623");
        data[6][2] = Integer.valueOf(1);

        data[7][0] = dateFormat.parse("20100802153623");
        data[7][1] = dateFormat.parse("20100803111819");
        data[7][2] = Integer.valueOf(4);

        data[8][0] = dateFormat.parse("20100803111819");
        data[8][1] = dateFormat.parse("20100804222138");
        data[8][2] = Integer.valueOf(2);

        data[9][0] = dateFormat.parse("20100804222138");
        data[9][1] = dateFormat.parse("20100805222138");
        data[9][2] = Integer.valueOf(3);

        return data;
    }

    private Object[][] getPieData() throws ParseException {
        Object[][] data = new Object[4][2];
        data[0][0] = Integer.valueOf(1);
        data[0][1] = Long.valueOf(111111);
        data[1][0] = Integer.valueOf(2);
        data[1][1] = Long.valueOf(222222);
        data[2][0] = Integer.valueOf(3);
        data[2][1] = Long.valueOf(333333);
        data[3][0] = Integer.valueOf(4);
        data[3][1] = Long.valueOf(444444);

        return data;
    }

    public void testStateBarChart() {
        try {
            Object[][] data = getBarData();
            Chart chart = StateChartFactory.getStateBarChart("主机状态图", data, 800, 320, StateChartFactory.HOST_TYPE,3);
            OutputStream outputStream = new FileOutputStream("E:\\host_bar.jpg");
            chart.writeChartAsJPEG(outputStream);
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ParseException e) {
            e.printStackTrace();
        }
    }

    public void testStatePieChart() {
        try {
            Object[][] data = getPieData();
            Chart chart = StateChartFactory.getStatePieChart("主机状态图", data, 800, 600, StateChartFactory.HOST_TYPE);
            OutputStream outputStream = new FileOutputStream("E:\\host_pie.jpg");
            chart.writeChartAsJPEG(outputStream);
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ParseException e) {
            e.printStackTrace();
        }
    }

    public static XYDataset createDataset() {

        final TimePeriodValues s1 = new TimePeriodValues("");
        final Day d1 = new Day();
        final Day d2 = (Day) d1.next();
        final Day d3 = (Day) d2.next();
        final Day d4 = (Day) d3.next();
        final Day d5 = (Day) d4.next();
        final Day d6 = (Day) d5.next();
        final Day d7 = (Day) d6.next();

        s1.add(new SimpleTimePeriod(d6.getStart(), d6.getEnd()), 1);
        s1.add(new SimpleTimePeriod(d1.getStart(), d2.getEnd()), 2);
        s1.add(new SimpleTimePeriod(d7.getStart(), d7.getEnd()), 3);
        s1.add(new SimpleTimePeriod(d3.getStart(), d5.getEnd()), 4);

        final TimePeriodValuesCollection dataset = new TimePeriodValuesCollection();
        dataset.addSeries(s1);
        dataset.setDomainIsPointsInTime(false);

        return dataset;
    }

    public static void main(String[] args) throws IOException {
        final XYDataset data = createDataset();
        final StateBarRenderer renderer = new StateBarRenderer();
        renderer.setDataset(data);
        Paint[] paints = new Paint[]{Color.GRAY, Color.GREEN, Color.RED, Color.GRAY, Color.GRAY,};
        renderer.setPaints(paints);

        final DateAxis domainAxis = new DateAxis("Date");
        domainAxis.setVerticalTickLabels(true);
//        final NumberAxis rangeAxis = new NumberAxis("Value");
        String[] array = new String[]{"", "up", "down", "unreachable", "depending"};
        SymbolAxis rangeAxis = new SymbolAxis("Value", array);
        rangeAxis.setUpperBound(4);
        rangeAxis.setLowerBound(0);
//        rangeAxis.setNumberFormatOverride();
        domainAxis.setDateFormatOverride(new SimpleDateFormat("EEE MMM d HH:mm:ss yyyy", Locale.ENGLISH));
//        domainAxis.setAutoTickUnitSelection(false);
        domainAxis.setTickUnit(new DateTickUnit(DateTickUnitType.DAY, 1));

        final XYPlot plot = new XYPlot(data, domainAxis, rangeAxis, renderer);


        final JFreeChart chart = new JFreeChart("Time Period Values Demo", JFreeChart.DEFAULT_TITLE_FONT, plot, false);
        FileOutputStream fileOutputStream = new FileOutputStream("E:\\a.jpg");

        ChartUtilities.writeChartAsJPEG(fileOutputStream, 1, chart, 800, 600, null);
    }

    public void testFormatTime(){
        Date now = new Date();
        DateFormat dateFormat = new SimpleDateFormat("EEE yyyy-MM-dd",Locale.ENGLISH);
        System.out.println(dateFormat.format(now));
    }

}
