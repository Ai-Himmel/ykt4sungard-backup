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

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.king.quarters.domain.TabSsManager;
import org.king.quarters.service.IDeptService;
import org.king.quarters.service.IManagerService;
import org.king.security.service.IPersonService;

import com.opensymphony.xwork.ActionSupport;

public class AddOrUpdateManagerAction extends ActionSupport{

	private IManagerService quartersManagerService;

	private IDeptService quartersDeptService;
	private IPersonService personService;
	
	private TabSsManager manager ;
	private Map depts ;
	
	public Map getDepts() {
		return depts;
	}
	public Map prepareDepts(){
		Map p = new HashMap();
		List l = quartersDeptService.getDepts();
		if (l != null && l.size() > 0){
			for (int i = 0 ; i < l.size() ; i++){
				Map t  = (Map)l.get(i);
				String id = (String)t.get("id");
				String name = (String)t.get("name");
				p.put(id, name);
			}
		}
		return p;
		
	}
	public String input(){
		
		if(manager != null && manager.getId() != null){
			manager = quartersManagerService.getManager(manager.getId());
		}
		depts = prepareDepts();
		return this.INPUT;
	}
	
	public String addOrUpdate(){
		
		if(!this.hasErrors()){
			try{
				boolean success = quartersManagerService.addOrUpdateDept(manager);
				if (success){
					this.addActionMessage("添加或更新宿舍管理员成功");
				}
			}catch(Throwable e){
				this.addActionMessage(e.getMessage());
			}
		}
		depts = prepareDepts();
		return this.INPUT;
	}

	

	public TabSsManager getManager() {
		return manager;
	}

	public void setManager(TabSsManager manager) {
		this.manager = manager;
	}

	

	public void setQuartersDeptService(IDeptService quartersDeptService) {
		this.quartersDeptService = quartersDeptService;
	}
	public void setQuartersManagerService(IManagerService quartersManagerService) {
		this.quartersManagerService = quartersManagerService;
	}
	public void setPersonService(IPersonService personService) {
		this.personService = personService;
	}

	
}
