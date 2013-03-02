/**
 * 
 */
package com.kingstargroup.ecard.portlet.advquery.cewolf;

import java.util.Date;
import java.util.Map;

import org.jfree.data.general.DefaultPieDataset;

import de.laures.cewolf.DatasetProducer;

/**
 * 往数据集中添加绘制图表所需的数据--从各Map中合计值生成饼图 2005-11-08日加入
 * 
 * @author Administrator
 * 
 */
public class DrawPieCust {
	private int[] result; 		// 饼图显示所需要的数据列表
	
	private float[] resultfloat;

	private String textPie[]; 	// 饼图要显示的内容

	private String dataType; 	// 饼图显示数据的数据类型

	private String columnTitle[];// 要显示的标题

	private DatasetProducer producer = new DatasetProducer() {
		public Object produceDataset(Map params) {
			DefaultPieDataset dataset = new DefaultPieDataset();
			//Iterator iter = result.iterator();
			for (int i = 0; i < columnTitle.length; i++) {
				if ("float".equals(dataType)) {
					
					dataset.setValue((Comparable) textPie[i],(float)(resultfloat[i]));
				} else if ("integer".equals(dataType)) {
					dataset.setValue((Comparable) textPie[i],
							(new Integer(result[i])));

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

	private DatasetProducer producerTotle = new DatasetProducer() {
		public Object produceDataset(Map params) {
			DefaultPieDataset dataset = new DefaultPieDataset();
			if ("float".equals(dataType)){
				float totleValue = 0;
				float[] pieData = new float[columnTitle.length];
				for (int j = 0 ; j<columnTitle.length;j++){
					pieData[j] = 0;
				}
				for (int i = 0; i<columnTitle.length; i++){
					totleValue += (float)(resultfloat[i]);
				}
				for (int i = 0; i<columnTitle.length; i++){
					pieData[i] = resultfloat[i]*100/totleValue;
					dataset.setValue((Comparable) textPie[i],(float)(pieData[i]));
				}
				
			}else if ("integer".equals(dataType)){
				int totleValue = 0;
				float[] pieData = new float[columnTitle.length];
				for (int j = 0 ; j<columnTitle.length;j++){
					pieData[j] = 0;
				}
				for (int i = 0; i<columnTitle.length; i++){
					totleValue += (int)(result[i]);
				}
				for (int i = 0; i<columnTitle.length; i++){
					pieData[i] = ((float)(result[i]))*100/totleValue;
					dataset.setValue((Comparable) textPie[i],(float)(pieData[i]));
				}
				
			}
			
			/**Iterator iter = result.iterator();
			for (int i = 1; i < columnTitle.length; i++) {
				
				if ("float".equals(dataType)) {
					dataset.setValue((Comparable) textPie[i-1],(float)(resultfloat[i]));
				} else if ("integer".equals(dataType)) {
					dataset.setValue((Comparable) textPie[i-1],
							(new Integer(result[i])));

				}
			}**/
			return dataset;
		}

		public String getProducerId() {
			return "PieDataProducer";
		}

		public boolean hasExpired(Map params, Date since) {
			return false;
		}

	};

	// 设置绘制饼图要传送的参数
	public DrawPieCust(int[] result, String textPie[], String dataType,
			String columnTitle[]) {
		this.result = result;
		this.textPie = textPie;
		this.columnTitle = columnTitle;
		this.dataType = dataType;
	}

	// 设置绘制饼图要传送的参数
	public DrawPieCust(float[] result, String textPie[], String dataType,
			String columnTitle[]) {
		this.resultfloat = result;
		this.textPie = textPie;
		this.columnTitle = columnTitle;
		this.dataType = dataType;
	}

	// 返回图形填充值
	public DatasetProducer getDatasetProducer() {
		return producer;
	}
	
	// 返回合计图形填充值
	public DatasetProducer getDatasetProducerTotle() {
		return producerTotle;
	}
	
	

}
