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
package org.king.quarters.web.action;

import java.util.List;

import org.king.quarters.service.IDeptService;

import com.opensymphony.xwork.ActionSupport;

public class ListDeptAction extends ActionSupport {

	private IDeptService quartersDeptService;

	
	
	private List depts;
	private List deleteX ;
	public List getDepts() {
		return depts;
	}
	
	public void setDepts(List depts) {
		this.depts = depts;
	}
	
	public String input(){
		depts = quartersDeptService.getDepts();
		
		return this.INPUT;
	}
	public String delete(){
		
		quartersDeptService.deleteDept(deleteX);
		depts = quartersDeptService.getDepts();
		return this.INPUT;
	}

	public List getDeleteX() {
		return deleteX;
	}

	public void setDeleteX(List deleteX) {
		this.deleteX = deleteX;
	}

	public void setQuartersDeptService(IDeptService quartersDeptService) {
		this.quartersDeptService = quartersDeptService;
	}
}
