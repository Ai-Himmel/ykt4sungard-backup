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
 * �����ݼ�����ӻ���ͼ�����������,��ָ��Ҫ��ʾ��Y��ֵ��ͼ���
 * ��������ͼ
 * @author Administrator
 *
 */
public class DrawBarConfType {
	private List result;		// ���ݼ��б�

	private String accType[]; 	// ͼ����ʾ����

	private int xData; 			// ͼ���X����ʾ����

	private String dataType; 	// Y��Ҫ��ʾ���ݵ���������
	
	private int showColumn;		// Ҫ��ʾ���к�

	public DrawBarConfType(List result, String accType[], int xData,
			String dataType,int showColumn) {
		this.result = result;
		this.accType = accType;
		this.xData = xData;
		this.dataType = dataType;
		this.showColumn = showColumn;
	}

	private DatasetProducer producer = new DatasetProducer() {
		public Object produceDataset(Map params) {
			DefaultCategoryDataset dataset = new DefaultCategoryDataset();
			// �����ݼ�����ӻ���ͼ�����������
			Iterator iter = result.iterator();
			while (iter.hasNext()) {
				Object[] val = (Object[]) iter.next();
				for (int i = 1; i < accType.length + 1; ++i) {
					if ("integer".equals(dataType)) {
						dataset.addValue((Integer) val[showColumn],
								(Comparable) accType[i - 1],
								(Comparable) val[xData]);
					} else if ("float".equals(dataType)) {
						dataset.addValue((Float) val[showColumn],
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
