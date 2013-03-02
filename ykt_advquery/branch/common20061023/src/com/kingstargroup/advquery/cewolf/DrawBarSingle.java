/**
 * 
 */
package com.kingstargroup.advquery.cewolf;

import java.util.Date;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.jfree.data.category.DefaultCategoryDataset;

import de.laures.cewolf.DatasetProducer;

/**
 * 往数据集中添加绘制图表所需的数据
 * 单一图表显示（例：X轴只能显示某一天的消费金额或存款金额）
 * @author Administrator
 *
 */
public class DrawBarSingle {
	private List result;		//后台数据返回列表
	private int	fillData;		//填充图表数据的列号
	private int xData;			//填充图表的X轴
	private int yData;			//填充图表的Y轴
	private String dataType;	//要填充数据的类型
	
	public DrawBarSingle(List result,int fillData,int xData,int yData,String dataType){
		this.result = result;
		this.fillData = fillData;
		this.xData = xData;
		this.yData = yData;
		this.dataType = dataType;
	}
	
	public DatasetProducer getDatasetProducer(){
		return producer;
	}
	public void setDatasetResult(List result) {
		this.result = result;
	}
	
	public void setfillData(int fillData) {
		this.fillData = fillData;
	}
	
	public void setXData(int xData){
		this.xData = xData;
	}
	public void setYData(int yData){
		this.yData = yData;
	}
	
	
	private DatasetProducer producer = new DatasetProducer(){
		public Object produceDataset(Map params) {
			DefaultCategoryDataset dataset = new DefaultCategoryDataset();
			// 往数据集中添加绘制图表所需的数据
			Iterator iter = result.iterator();
			while (iter.hasNext()) {
				Object[] val = (Object[]) iter.next();
				if ("integer".equals(dataType)){
					dataset.addValue((Integer) val[yData],
							(Comparable) val[fillData], (Comparable) val[xData]);					
				}else if ("float".equals(dataType)){
					dataset.addValue((Float) val[yData],
							(Comparable) val[fillData], (Comparable) val[xData]);

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
}
