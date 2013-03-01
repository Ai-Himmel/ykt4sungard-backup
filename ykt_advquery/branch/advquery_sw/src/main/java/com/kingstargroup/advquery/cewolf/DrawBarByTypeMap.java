/**
 * 
 */
package com.kingstargroup.advquery.cewolf;

import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.jfree.data.category.CategoryDataset;
import org.jfree.data.category.DefaultCategoryDataset;

import de.laures.cewolf.DatasetProducer;

/**
 * 往数据集中添加绘制图表所需的数据 多类别图表显示（例：X轴能同时显示某一天的存款，消费，押金) HashMap表达
 * 
 * @author Administrator
 * 
 */
public class DrawBarByTypeMap {
	private List result; // 数据集列表

	private String accType[]; // 提示图标显示内容

	private String xData; // 图表的X轴要显示的列

	private String dataType; // Y轴要显示数据的数据类型
	
	private String columnTitle[];//列名称
	
	private int dataUnit;//金额单位

	public DrawBarByTypeMap(List result, String accType[], String xData,
			String dataType,String columnTitle[],int dataUnit) {
		this.result = result;
		this.accType = accType;
		this.xData = xData;
		this.dataType = dataType;
		this.columnTitle = columnTitle;
		this.dataUnit = dataUnit;
	}

	private DatasetProducer producer = new DatasetProducer() {
		public Object produceDataset(Map params) {
			DefaultCategoryDataset dataset = new DefaultCategoryDataset();
			// 往数据集中添加绘制图表所需的数据
			int step = (int)(result.size()/18);
			step = (step == 0) ? 1 : step;
			Iterator iter = result.iterator();
			int k = step - 1;
			HashMap row = null;
			while (iter.hasNext()) {
				row = null;
				while(iter.hasNext() && k++ < step) 
					row = (HashMap) iter.next();
				if(null == row)
					break;
				k = 0;
				//Object[] val = (Object[]) iter.next();
				//HashMap row = (HashMap) iter.next();
				/**for (int i = 1; i < accType.length + 1; ++i) {
					if ("integer".equals(dataType)) {
						dataset.addValue((Integer) row.get(columnTitle[i]),
								(Comparable) accType[i - 1],
								(Comparable) row.get(xData));
					} else if ("float".equals(dataType)) {
						dataset.addValue((Float) row.get(columnTitle[i]),
								(Comparable) accType[i - 1],
								(Comparable)(row.get(xData)));
					}
				}**/
				if ("integer".equals(dataType)) {
					int yValue;
					for (int i = 0; i < accType.length ; ++i) {
						yValue = (Integer.parseInt(row.get(columnTitle[i]).toString()))/dataUnit;
						dataset.addValue(new Integer(yValue),
								(Comparable) accType[i],
								(Comparable) row.get(xData));
					}
				}else if ("float".equals(dataType)) {
					float yValue;
					for (int i = 0; i < accType.length ; ++i) {
						yValue = (Float.parseFloat(row.get(columnTitle[i]).toString()))/dataUnit;
						dataset.addValue(new Float(yValue),
								(Comparable) accType[i],
								(Comparable)(row.get(xData)));						
					}
				}
			}
			return dataset;
		}

		public String getProducerId() {
			return "CategoryDataProducer";
		}

		public boolean hasExpired(Map params, Date since) {
			return false;
		}
	};
	private DatasetProducer producerDouble = new DatasetProducer() {
		public Object produceDataset(Map params) {
			DefaultCategoryDataset dataset = new DefaultCategoryDataset();
			// 往数据集中添加绘制图表所需的数据
			int step = (int)(result.size()/18);
			step = (step == 0) ? 1 : step;
			Iterator iter = result.iterator();
			int k = step - 1;
			HashMap row = null;
			while (iter.hasNext()) {
				row = null;
				while(iter.hasNext() && k++ < step) 
					row = (HashMap) iter.next();
				if(null == row)
					break;
				k = 0;
				//Object[] val = (Object[]) iter.next();
				//HashMap row = (HashMap) iter.next();
				/**for (int i = 1; i < accType.length + 1; ++i) {
					if ("integer".equals(dataType)) {
						dataset.addValue((Integer) row.get(columnTitle[i]),
								(Comparable) accType[i - 1],
								(Comparable) row.get(xData));
					} else if ("float".equals(dataType)) {
						dataset.addValue((Double) row.get(columnTitle[i]),
								(Comparable) accType[i - 1],
								(Comparable)(row.get(xData)));
					}
				}**/
				if ("integer".equals(dataType)) {
					int yValue;
					for (int i = 0; i < accType.length ; ++i) {
						yValue = (Integer.parseInt(row.get(columnTitle[i]).toString()))/dataUnit;
						dataset.addValue(new Integer(yValue),
								(Comparable) accType[i],
								(Comparable) row.get(xData));
					}
				}else if ("float".equals(dataType)) {
					double yValue;
					for (int i = 0; i < accType.length ; ++i) {
						yValue = (Double.parseDouble(row.get(columnTitle[i]).toString()))/dataUnit;
						dataset.addValue(new Double(yValue),
								(Comparable) accType[i],
								(Comparable)(row.get(xData)));						
					}
				}
			}
			return dataset;
		}

		public String getProducerId() {
			return "CategoryDataProducer";
		}

		public boolean hasExpired(Map params, Date since) {
			return false;
		}
	};

	/**
	 * 绘制图形数据集
	 * 2006-6-14
	 * hjw
	 * @param
	 * @return
	 */
	private CategoryDataset chartDataset() {
		DefaultCategoryDataset dataset = new DefaultCategoryDataset();
		// 往数据集中添加绘制图表所需的数据
		int step = (int)(result.size()/18);
		step = (step == 0) ? 1 : step;
		Iterator iter = result.iterator();
		int k = step - 1;
		HashMap row = null;
		while (iter.hasNext()) {
			row = null;
			while(iter.hasNext() && k++ < step) 
				row = (HashMap) iter.next();
			if(null == row)
				break;
			k = 0;
			if ("integer".equals(dataType)) {
				int yValue;
				for (int i = 0; i < accType.length ; ++i) {
					yValue = (Integer.parseInt(row.get(columnTitle[i]).toString()))/dataUnit;
					dataset.addValue(new Integer(yValue),
							(Comparable) accType[i],
							(Comparable) row.get(xData));
				}
			}else if ("float".equals(dataType)) {
				float yValue;
				for (int i = 0; i < accType.length ; ++i) {
					yValue = (Float.parseFloat(row.get(columnTitle[i]).toString()))/dataUnit;
					dataset.addValue(new Float(yValue),
							(Comparable) accType[i],
							(Comparable)(row.get(xData)));						
				}
			}
		}
		return dataset;
	}
	public CategoryDataset getchartDataset(){
		return chartDataset();
	}
	
	public void setDatasetResult(List result) {
		this.result = result;
	}

	public void setAccType(String accType[]) {
		this.accType = accType;
	}

	public void setXData(String xData) {
		this.xData = xData;
	}

	public void setDataType(String dataType) {
		this.dataType = dataType;
	}

	public DatasetProducer getDataProducer() {
		return producer;
	}
	public DatasetProducer getDataProducerDouble() {
		return producerDouble;
	}

}
