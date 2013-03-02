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
 * 往数据集中添加绘制图表所需的数据
 * 单一图表显示（例：X轴只能显示某一天的消费金额或存款金额）
 * @author Administrator
 *
 */
public class DrawBarSingleMap {
	private List result;			//后台数据返回列表
	private String	fillData;		//填充图表数据的列号
	private String xData;			//填充图表的X轴
	private String yData;			//填充图表的Y轴
	private String dataType;		//要填充数据的类型
	
	public DrawBarSingleMap(List result,String fillData,String xData,String yData,String dataType){
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
	
	public void setfillData(String fillData) {
		this.fillData = fillData;
	}
	
	public void setXData(String xData){
		this.xData = xData;
	}
	public void setYData(String yData){
		this.yData = yData;
	}
	
	
	private DatasetProducer producer = new DatasetProducer(){
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

			//Iterator iter = result.iterator();
			//while (iter.hasNext()) {
				//Object[] val = (Object[]) iter.next();
				//HashMap row = (HashMap) iter.next();
				if ("integer".equals(dataType)){
					dataset.addValue((Integer) row.get(yData),
							(Comparable) row.get(fillData), (Comparable) row.get(xData));					
				}else if ("float".equals(dataType)){
					dataset.addValue((Float) row.get(yData),
							(Comparable) row.get(fillData), (Comparable) row.get(xData));

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
