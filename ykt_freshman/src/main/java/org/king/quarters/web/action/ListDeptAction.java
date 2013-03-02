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
