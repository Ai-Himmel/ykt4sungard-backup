/**
 * 
 */
package com.kingstargroup.advquery.cewolf;

import java.util.Date;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

import de.laures.cewolf.DatasetProducer;

/**
 * @author Administrator
 * 
 */
public class DrawXYChart {
	//图标显示内容
	private String accType;
	//数据结果集
	private List result;
	//要显示数据的数据类型
	private String dataType;
	//Y轴要显示的数据内容
	private int yData;
	//X轴要显示的数据内容
	private int xData;
	
	public DrawXYChart(List result,String accType,int xData,int yData,String dataType){
		this.result = result;
		this.accType = accType;
		this.xData = xData;
		this.yData = yData;
		this.dataType = dataType;
	}
	
	public DatasetProducer getDataProducer() {
		return producer;
	}
	
	private DatasetProducer producer = new DatasetProducer() {
		public Object produceDataset(Map params) {
		    /*XYSeries xys = new XYSeries(accType);
		    int bookSales = 0;
		    for (int day = 0; day <= 30; day++)
		    {
		      bookSales = 10+(int)(Math.random() * 30);
		      xys.add(day, bookSales);
		    }
		    XYSeriesCollection xysc = new XYSeriesCollection(xys);
		    return xysc;*/

			XYSeries xySeries = new XYSeries(accType);
			Iterator iter = result.iterator();
			while (iter.hasNext()) {
				Object[] xyVal = (Object[]) iter.next();
				if ("float".equals(dataType)){
					xySeries.add(Integer.parseInt((String)xyVal[xData]), (Float) xyVal[yData]);
				}else if ("integer".equals(dataType)){
					xySeries.add(Integer.parseInt((String)xyVal[xData]), (Integer) xyVal[yData]);
				}
				
			}
			XYSeriesCollection xySeriesCollection = new XYSeriesCollection();
			xySeriesCollection.addSeries(xySeries);
			return xySeriesCollection;
		}

		public String getProducerId() {
			return "CategoryDataProducer";
		}

		public boolean hasExpired(Map params, Date since) {
			return false;
		}

	};
}
