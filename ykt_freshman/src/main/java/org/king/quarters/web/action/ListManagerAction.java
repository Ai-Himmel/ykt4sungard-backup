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
