/**
 * 
 */
package com.kingstargroup.ecard.portlet.advquery.cewolf;

import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.jfree.data.general.DefaultPieDataset;

import de.laures.cewolf.DatasetProducer;

/**
 * �����ݼ�����ӻ���ͼ�����������--���Ʊ�ͼ
 * @author Administrator
 * 
 */
public class DrawPie {
	private List result; 		// ��ͼ��ʾ����Ҫ�������б�

	private String textPie; 		// ��ͼҪ��ʾ������

	private String dataPie; 		// ��ͼҪ��ʾ������
	
	private String dataType;	//��ͼ��ʾ���ݵ���������

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
	
	//���û��Ʊ�ͼҪ���͵Ĳ���
	public DrawPie(List result,String textPie,String dataPie,String dataType){
		this.result = result;
		this.textPie = textPie;
		this.dataPie = dataPie;
		this.dataType = dataType;
	}
	
	//����ͼ�����ֵ
	public DatasetProducer getDatasetProducer(){
		return producer;
	}
	
}
