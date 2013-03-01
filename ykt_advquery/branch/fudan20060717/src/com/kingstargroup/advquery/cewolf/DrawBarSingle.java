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
 * �����ݼ�����ӻ���ͼ�����������
 * ��һͼ����ʾ������X��ֻ����ʾĳһ������ѽ������
 * @author Administrator
 *
 */
public class DrawBarSingle {
	private List result;		//��̨���ݷ����б�
	private int	fillData;		//���ͼ�����ݵ��к�
	private int xData;			//���ͼ���X��
	private int yData;			//���ͼ���Y��
	private String dataType;	//Ҫ������ݵ�����
	
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
			// �����ݼ�����ӻ���ͼ�����������
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
