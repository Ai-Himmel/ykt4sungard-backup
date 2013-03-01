/**
 * 
 */
package com.kingstargroup.advquery.cewolf;

import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.jfree.data.time.Day;
import org.jfree.data.time.MovingAverage;
import org.jfree.data.time.TimeSeries;
import org.jfree.data.time.TimeSeriesCollection;
import org.jfree.data.xy.XYDataset;

import com.kingstargroup.advquery.common.DateUtilExtend;

import de.laures.cewolf.DatasetProducer;

/**
 * @author Administrator
 * 
 */
public class DrawTimeSeries {
	private List result; // 结果列表

	private String statTitle[];// 要统计的内容

	private String dateValue;// X轴的日期字段名称

	private String dataType;// ｙ轴要显示的数据类型

	private String accTitle[];// ｘ轴显示的中午提示

	private int dataUnit;// ｙ轴的数据标尺大小
	
	private int dateUnit;//	日期刻度值
	
	private DatasetProducer xyProducer = new DatasetProducer() {
		public Object produceDataset(Map params) {
			TimeSeriesCollection dataset = new TimeSeriesCollection();
			TimeSeries ts[] = new TimeSeries[statTitle.length];
			for (int i = 0; i < statTitle.length; i++) {
				ts[i] = new TimeSeries(accTitle[i], Day.class);
				Iterator iter = result.iterator();
				if ("integer".equals(dataType)) {
					int yValue;
					while (iter.hasNext()) {
						HashMap row = (HashMap) iter.next();
						yValue = Integer.parseInt(row.get(statTitle[i])
								.toString()) / dataUnit;
						ts[i].add(new Day(DateUtilExtend.getStrToDate(row.get(
								dateValue).toString())), new Integer(yValue));
					}
				} else if ("float".equals(dataType)) {
					float yValue;
					while (iter.hasNext()) {
						HashMap row = (HashMap) iter.next();
						yValue = Float.parseFloat(row.get(statTitle[i])
								.toString())/ dataUnit;
						ts[i].add(new Day(DateUtilExtend.getStrToDate(row.get(
								dateValue).toString())), new Float(yValue));
					}
				}
				dataset.addSeries(ts[i]);
			}
			return dataset;
		}

		public String getProducerId() {
			return "TimeDataProducer";
		}

		public boolean hasExpired(Map params, Date since) {
			return false;
		}
	};
	
	/**
	 * 绘制时序图的移动平均图形
	 */
	private DatasetProducer avgProducer = new DatasetProducer() {
		public Object produceDataset(Map params) {
			TimeSeriesCollection dataset = new TimeSeriesCollection();
			TimeSeries avg[] = new TimeSeries[statTitle.length];;
			TimeSeries ts[] = new TimeSeries[statTitle.length];
			for (int i = 0; i < statTitle.length; i++) {
				ts[i] = new TimeSeries(accTitle[i], Day.class);
				Iterator iter = result.iterator();
				if ("integer".equals(dataType)) {
					int yValue;
					while (iter.hasNext()) {
						HashMap row = (HashMap) iter.next();
						yValue = Integer.parseInt(row.get(statTitle[i])
								.toString()) / dataUnit;
						ts[i].add(new Day(DateUtilExtend.getStrToDate(row.get(
								dateValue).toString())), new Integer(yValue));
					}
				} else if ("float".equals(dataType)) {
					float yValue;
					while (iter.hasNext()) {
						HashMap row = (HashMap) iter.next();
						yValue = Float.parseFloat(row.get(statTitle[i])
								.toString())/ dataUnit;
						ts[i].add(new Day(DateUtilExtend.getStrToDate(row.get(
								dateValue).toString())), new Float(yValue));
					}
				}
				avg[i] = MovingAverage.createMovingAverage(ts[i], dateUnit+"天平均值", dateUnit, dateUnit);
				dataset.addSeries(ts[i]);
				dataset.addSeries(avg[i]);
			}
			return dataset;
		}
		public String getProducerId() {
			return "TimeDataProducer";
		}

		public boolean hasExpired(Map params, Date since) {
			return false;
		}
	};
	
	/**
	 * 绘制时序图
	 * @param result
	 * @param statTitle
	 * @param dateValue
	 * @param dataType
	 * @param accTitle
	 * @param dataUnit
	 */
	public DrawTimeSeries(List result, String statTitle[], String dateValue,
			String dataType, String accTitle[], int dataUnit) {
		this.result = result;
		this.statTitle = statTitle;
		this.dateValue = dateValue;
		this.dataType = dataType;
		this.accTitle = accTitle;
		this.dataUnit = dataUnit;
	}
	
	/**
	 * 时序图的平均移动曲线
	 * @param result
	 * @param statTitle
	 * @param dateValue
	 * @param dataType
	 * @param accTitle
	 * @param dataUnit
	 * @param dateUnit
	 */
	public DrawTimeSeries(List result, String statTitle[], String dateValue,
			String dataType, String accTitle[], int dataUnit,int dateUnit) {
		this.result = result;
		this.statTitle = statTitle;
		this.dateValue = dateValue;
		this.dataType = dataType;
		this.accTitle = accTitle;
		this.dataUnit = dataUnit;
		this.dateUnit = dateUnit;
	}

		/**
		 * 绘制图形数据集
		 * 2006-6-14
		 * hjw
		 * @param
		 * @return
		 */
	private XYDataset chartDataSet() {
		TimeSeriesCollection dataset = new TimeSeriesCollection();
		TimeSeries ts[] = new TimeSeries[statTitle.length];
		for (int i = 0; i < statTitle.length; i++) {
			ts[i] = new TimeSeries(accTitle[i], Day.class);
			Iterator iter = result.iterator();
			if ("integer".equals(dataType)) {
				int yValue;
				while (iter.hasNext()) {
					HashMap row = (HashMap) iter.next();
					yValue = Integer.parseInt(row.get(statTitle[i])
							.toString()) / dataUnit;
					ts[i].add(new Day(DateUtilExtend.getStrToDate(row.get(
							dateValue).toString())), new Integer(yValue));
				}
			} else if ("float".equals(dataType)) {
				float yValue;
				while (iter.hasNext()) {
					HashMap row = (HashMap) iter.next();
					yValue = Float.parseFloat(row.get(statTitle[i])
							.toString())/ dataUnit;
					ts[i].add(new Day(DateUtilExtend.getStrToDate(row.get(
							dateValue).toString())), new Float(yValue));
				}
			}
			dataset.addSeries(ts[i]);
		}
		return dataset;
	}
	
	public XYDataset getChartDataSet(){
		return chartDataSet();
	}

	public DatasetProducer getTimeSeriesProducer() {
		return xyProducer;
	}
	
	public DatasetProducer getTimeSeriesProducerAvg() {
		return avgProducer;
	}
}
