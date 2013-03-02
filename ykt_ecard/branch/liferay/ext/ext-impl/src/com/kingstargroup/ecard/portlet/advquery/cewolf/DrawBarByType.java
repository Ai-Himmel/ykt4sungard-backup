/**
 * 
 */
package com.kingstargroup.ecard.portlet.advquery.cewolf;

import java.util.Date;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.jfree.data.category.DefaultCategoryDataset;

import de.laures.cewolf.DatasetProducer;

/**
 * 往数据集中添加绘制图表所需的数据 多类别图表显示（例：X轴能同时显示某一天的存款，消费，押金）
 * @author Administrator
 * 
 */
public class DrawBarByType {
	private List result; 		// 数据集列表

	private String accType[]; 	// 图标显示内容

	private int xData; 			// 图表的X轴显示内容

	private String dataType; 	// Y轴要显示数据的数据类型

	public DrawBarByType(List result, String accType[], int xData,
			String dataType) {
		this.result = result;
		this.accType = accType;
		this.xData = xData;
		this.dataType = dataType;
	}

	private DatasetProducer producer = new DatasetProducer() {
		public Object produceDataset(Map params) {
			DefaultCategoryDataset dataset = new DefaultCategoryDataset();
			// 往数据集中添加绘制图表所需的数据
			Iterator iter = result.iterator();
			while (iter.hasNext()) {
				Object[] val = (Object[]) iter.next();
				for (int i = 1; i < accType.length + 1; ++i) {
					if ("integer".equals(dataType)) {
						dataset.addValue((Integer) val[i],
								(Comparable) accType[i - 1],
								(Comparable) val[xData]);
					} else if ("float".equals(dataType)) {
						dataset.addValue((Float) val[i],
								(Comparable) accType[i - 1],
								(Comparable) val[xData]);
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

	public void setDatasetResult(List result) {
		this.result = result;
	}

	public void setAccType(String accType[]) {
		this.accType = accType;
	}

	public void setXData(int xData) {
		this.xData = xData;
	}

	public void setDataType(String dataType) {
		this.dataType = dataType;
	}

	public DatasetProducer getDataProducer() {
		return producer;
	}
}
