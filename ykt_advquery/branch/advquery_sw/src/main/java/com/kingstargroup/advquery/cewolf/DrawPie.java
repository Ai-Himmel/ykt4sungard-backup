/**
 * 
 */
package com.kingstargroup.advquery.cewolf;

import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.jfree.data.general.DefaultPieDataset;

import de.laures.cewolf.DatasetProducer;

/**
 * 往数据集中添加绘制图表所需的数据--绘制饼图
 * @author Administrator
 * 
 */
public class DrawPie {
	private List result; 		// 饼图显示所需要的数据列表

	private String textPie; 		// 饼图要显示的内容

	private String dataPie; 		// 饼图要显示的数据
	
	private String dataType;	//饼图显示数据的数据类型

	private DatasetProducer producer = new DatasetProducer() {
		public Object produceDataset(Map params) {
			DefaultPieDataset dataset = new DefaultPieDataset();
			Iterator iter = result.iterator();
			while (iter.hasNext()) {
				//Object[] pieval = (Object[]) iter.next();
				HashMap row = (HashMap)iter.next();
				if ("float".equals(dataType)){
					dataset.setValue((Comparable) row.get(textPie),
							((Float) row.get(dataPie)));					
				}else if ("integer".equals(dataType)){
					dataset.setValue((Comparable) row.get(textPie),
							((Integer) row.get(dataPie)));

				}
			}
			return dataset;
		}

		public String getProducerId() {
			return "PieDataProducer";
		}

		public boolean hasExpired(Map params, Date since) {
			return false;
		}

	};
	
	public void setDatasetResult(List result) {
		this.result = result;
	}
	
	//设置绘制饼图要传送的参数
	public DrawPie(List result,String textPie,String dataPie,String dataType){
		this.result = result;
		this.textPie = textPie;
		this.dataPie = dataPie;
		this.dataType = dataType;
	}
	
	//返回图形填充值
	public DatasetProducer getDatasetProducer(){
		return producer;
	}
	
}
