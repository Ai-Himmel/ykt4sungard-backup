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

import org.king.quarters.domain.TabSsDept;
import org.king.quarters.service.IDeptService;

import com.opensymphony.xwork.ActionSupport;


public class AddOrUpdateDeptAction extends ActionSupport {

	private IDeptService quartersDeptService;

	
	
	private TabSsDept dept;
	
	public TabSsDept getDept() {
		return dept;
	}

	public void setDept(TabSsDept dept) {
		this.dept = dept;
	}

	public String input(){
		
		if(dept != null && dept.getId() != null){
			dept = quartersDeptService.getDept(dept.getId());
		}
		return this.INPUT;
	}
	
	public String addOrUpdate(){
	
		quartersDeptService.addOrUpdateDept(dept);
		this.addActionMessage("添加或更新成功!");
		return this.INPUT;
	}

	public void setQuartersDeptService(IDeptService quartersDeptService) {
		this.quartersDeptService = quartersDeptService;
	}
}
