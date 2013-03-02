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
 * �����ݼ�����ӻ���ͼ�����������
 * ��һͼ����ʾ������X��ֻ����ʾĳһ������ѽ������
 * @author Administrator
 *
 */
public class DrawBarSingleMap {
	private List result;			//��̨���ݷ����б�
	private String	fillData;		//���ͼ�����ݵ��к�
	private String xData;			//���ͼ���X��
	private String yData;			//���ͼ���Y��
	private String dataType;		//Ҫ������ݵ�����
	
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
			// �����ݼ�����ӻ���ͼ�����������
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
