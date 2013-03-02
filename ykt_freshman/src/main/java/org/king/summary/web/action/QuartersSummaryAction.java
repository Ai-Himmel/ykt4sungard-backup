/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    ListDeptAction.java
 * 创建日期： 2007-6-5 下午02:58:15
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-6-5 下午02:58:15     王胜        创建文件，实现基本功能
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
