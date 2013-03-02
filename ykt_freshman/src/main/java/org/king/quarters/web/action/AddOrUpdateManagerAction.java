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
					this.addActionMessage("��ӻ�����������Ա�ɹ�");
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
