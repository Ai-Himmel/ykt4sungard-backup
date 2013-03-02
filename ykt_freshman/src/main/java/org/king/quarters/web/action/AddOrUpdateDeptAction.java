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
		this.addActionMessage("��ӻ���³ɹ�!");
		return this.INPUT;
	}

	public void setQuartersDeptService(IDeptService quartersDeptService) {
		this.quartersDeptService = quartersDeptService;
	}
}
