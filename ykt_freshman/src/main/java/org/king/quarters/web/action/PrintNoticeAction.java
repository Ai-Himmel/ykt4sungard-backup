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
import java.util.Locale;

import org.king.quarters.domain.TabSsDept;
import org.king.quarters.service.IQuartersNoticeService;
import org.king.quarters.service.IQuartersService;

import com.opensymphony.xwork.ActionContext;
import com.opensymphony.xwork.ActionSupport;



public class PrintNoticeAction extends ActionSupport{

	private IQuartersNoticeService quartersNoticeService;

	public void setQuartersNoticeService(
			IQuartersNoticeService quartersNoticeService) {
		this.quartersNoticeService = quartersNoticeService;
	}
	
	private IQuartersService quartersService;
	public void setQuartersService(IQuartersService quartersService) {
		this.quartersService = quartersService;
	}
	
	private List deleteX;
	private int type = 0;
    private List dataSource;
    private String personName;
	public String getPersonName() {
		return personName;
	}

	public void setPersonName(String personName) {
		this.personName = personName;
	}

	public List getDataSource() {
		return dataSource;
	}

	public void setDataSource(List dataSource) {
		this.dataSource = dataSource;
	}

	public List getDeleteX() {
		return deleteX;
	}

	public void setDeleteX(List deleteX) {
		this.deleteX = deleteX;
	}
	
	public String printNotice(){
		ActionContext context = ActionContext.getContext();
		context.setLocale(Locale.ENGLISH);
		String userId = (String)context.getSession().get("account");
		TabSsDept dept= quartersService.getManageDept(userId);
		String curdept=dept.getId();
		personName = (String)(String)context.getSession().get("personName");
		dataSource = quartersNoticeService.getNoticeDataSource(userId,deleteX);
		if (type ==1) 
			return curdept+"ruzhuNotice";
		else if (type == 2)
			return curdept+"jiaofeiNotice";
		else 
			return curdept+"juzhuNotice";
	}

	public int getType() {
		return type;
	}

	public void setType(int type) {
		this.type = type;
	}

	
	
	
	
}
