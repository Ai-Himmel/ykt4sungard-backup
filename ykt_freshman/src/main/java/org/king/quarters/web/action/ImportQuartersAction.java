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
import org.king.quarters.service.IQuartersService;

import com.opensymphony.xwork.ActionContext;
import com.opensymphony.xwork.ActionSupport;


public class ImportQuartersAction extends ActionSupport {

	private IQuartersService quartersService;
	java.io.File excelFile;
	public java.io.File getExcelFile() {
		return excelFile;
	}

	public void setExcelFile(java.io.File excelFile) {
		this.excelFile = excelFile;
	}

	private TabSsDept dept;
	public TabSsDept getDept() {
		return dept;
	}

	public void setDept(TabSsDept dept) {
		this.dept = dept;
	}

	public String input(){	
		ActionContext context = ActionContext.getContext();
		String userId = (String)context.getSession().get("account");
		 dept  = quartersService.getManageDept(userId);
		if (dept == null){
		  return "noRight";
		}
		return this.INPUT;
	}
	
	public String importFile(){	
		
		//account.
		try{
		ActionContext context = ActionContext.getContext();
		String userId = (String)context.getSession().get("account");
		dept = quartersService.getManageDept(userId);
		if (dept == null){
			  return "noRight";
			}
		int code = quartersService.importQuarters(userId, excelFile);
		if (code == 0) {
			this.addActionMessage("导入成功！");
		}
		else if (code == 1) {
			this.addActionMessage("用户没有管理宿舍权限！");
		}
		else if(code == 2){
			this.addActionMessage("数据格式不对！");
		}
		else if (code == 3){
			this.addActionMessage("数据不对或不存在的校区小校区楼号等！");
		}
		else {
			this.addActionMessage("没有数据！");
		}
		}catch(Throwable e){
			String message = e.getMessage();
			this.addActionMessage(message);
		}
		return this.INPUT;
	}

	public void setQuartersService(IQuartersService quartersService) {
		this.quartersService = quartersService;
	}
	
	
}
