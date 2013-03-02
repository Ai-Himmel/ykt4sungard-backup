/**
 * 
 */
package com.kingstargroup.ecard.portlet.advquery.cewolf;

import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.jfree.data.category.DefaultCategoryDataset;

import de.laures.cewolf.DatasetProducer;

/**
 * 往数据集中添加绘制图表所需的数据,能指定要显示的Y轴值、图标等
 * 绘制折线图HashMap表
 * @author Administrator
 *
 */
public class DrawBarConfTypeMap {
	private List result;			// 数据集列表

	private String accType[]; 		// 图标显示内容

	private String xData; 			// 图表的X轴显示内容

	private String dataType; 		// Y轴要显示数据的数据类型
	
	private String showColumn;		// 要显示的列号
	
	private int dataUnit;

	public DrawBarConfTypeMap(List result, String accType[], String xData,
			String dataType,String showColumn,int dataUnit) {
		this.result = result;
		this.accType = accType;
		this.xData = xData;
		this.dataType = dataType;
		this.showColumn = showColumn;
		this.dataUnit = dataUnit;
	}

	private DatasetProducer producer = new DatasetProducer() {
		public Object produceDataset(Map params) {
			DefaultCategoryDataset dataset = new DefaultCategoryDataset();
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

			// 往数据集中添加绘制图表所需的数据
			//Iterator iter = result.iterator();
			//while (iter.hasNext()) {
				//Object[] val = (Object[]) iter.next();
				//HashMap row = (HashMap) iter.next();
				/**for (int i = 1; i < accType.length + 1; ++i) {
					if ("integer".equals(dataType)) {
						dataset.addValue((Integer) row.get(showColumn),
								(Comparable) accType[i - 1],
								(Comparable) row.get(xData));
					} else if ("float".equals(dataType)) {
						dataset.addValue((Float) row.get(showColumn),
								(Comparable) accType[i - 1],
								(Comparable) row.get(xData));
					}
				}**/
				if ("integer".equals(dataType)) {
					int yValue;
					for (int i = 1; i < accType.length + 1; ++i) {
						yValue = (Integer.parseInt(row.get(showColumn).toString()))/dataUnit;
						dataset.addValue(new Integer(yValue),
								(Comparable) accType[i - 1],
								(Comparable) row.get(xData));
					}
				}else if ("float".equals(dataType)) {
					double yValue;
					for (int i = 1; i < accType.length + 1; ++i) {
						yValue = (Double.parseDouble(row.get(showColumn).toString()))/dataUnit;
						dataset.addValue(new Float(yValue),
								(Comparable) accType[i - 1],
								(Comparable) row.get(xData));
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

	public void setXData(String xData) {
		this.xData = xData;
	}

	public void setDataType(String dataType) {
		this.dataType = dataType;
	}

	public DatasetProducer getDataProducer() {
		return producer;
	}

}
