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

import org.king.quarters.service.IManagerService;

import com.opensymphony.xwork.ActionSupport;


public class ListManagerAction extends ActionSupport {

	private IManagerService quartersManagerService;

	
	private List managers;
	
	
	public List getManagers() {
		return managers;
	}
	public void setManagers(List managers) {
		this.managers = managers;
	}
	public String input(){
		managers = quartersManagerService.getManagers();
		
		return this.INPUT;
	}
	public void setQuartersManagerService(IManagerService quartersManagerService) {
		this.quartersManagerService = quartersManagerService;
	}
	
	
}
