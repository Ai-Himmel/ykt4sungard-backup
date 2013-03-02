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
			this.addActionMessage("����ɹ���");
		}
		else if (code == 1) {
			this.addActionMessage("�û�û�й�������Ȩ�ޣ�");
		}
		else if(code == 2){
			this.addActionMessage("���ݸ�ʽ���ԣ�");
		}
		else if (code == 3){
			this.addActionMessage("���ݲ��Ի򲻴��ڵ�У��СУ��¥�ŵȣ�");
		}
		else {
			this.addActionMessage("û�����ݣ�");
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
