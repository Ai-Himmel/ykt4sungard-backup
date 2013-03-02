/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2007
 * �ļ���    ListDeptAction.java
 * �������ڣ� 2007-6-5 ����02:58:15
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 *  2007-6-5 ����02:58:15     ��ʤ        �����ļ���ʵ�ֻ�������
 * ============================================================
 */
package org.king.summary.web.action;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import net.sf.jasperreports.engine.export.JRHtmlExporterParameter;

import org.king.summary.service.IQuartersSummaryService;

import com.opensymphony.xwork.ActionSupport;

public class QuartersSummaryAction extends ActionSupport{

	private IQuartersSummaryService quartersSummaryService;

	
	
	
    private List dataSource;
    private Map parameters;
   
	
	public Map getParameters() {
		return parameters;
	}



	public List getDataSource() {
		return dataSource;
	}



	public void setDataSource(List dataSource) {
		this.dataSource = dataSource;
	}



	public String summary(){
		parameters = new HashMap();
		parameters.put(JRHtmlExporterParameter.IS_USING_IMAGES_TO_ALIGN,Boolean.FALSE);
		parameters.put(JRHtmlExporterParameter.SIZE_UNIT,JRHtmlExporterParameter.SIZE_UNIT_POINT);
		dataSource = quartersSummaryService.getSummaryInfo();
		return this.INPUT;
		
	}

	

	public void setQuartersSummaryService(
			IQuartersSummaryService quartersSummaryService) {
		this.quartersSummaryService = quartersSummaryService;
	}

	
	
	
	
}
