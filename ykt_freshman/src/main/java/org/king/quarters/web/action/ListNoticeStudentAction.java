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

import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;

import org.king.common.service.IDirectoryService;
import org.king.quarters.domain.TabSsDept;
import org.king.quarters.service.IQuartersNoticeService;
import org.king.quarters.service.IQuartersService;
import org.king.quarters.service.NoticeInfo;

import com.opensymphony.webwork.interceptor.ServletRequestAware;
import com.opensymphony.xwork.ActionContext;
import com.opensymphony.xwork.ActionSupport;


public class ListNoticeStudentAction extends ActionSupport implements ServletRequestAware{

	private IQuartersService quartersService;
	private IDirectoryService directoryService;
	private IQuartersNoticeService quartersNoticeService;
	private HttpServletRequest request;
	
	private List students = new ArrayList();
	private List locations;
	private List areas;
	private List dormitorys;
	private List depts;
	private List majorList;
	//
	
	private TabSsDept dept;
	private int pageNo = 1;
	private int pageSize = 10;
	private int count = 0;
	
	
	private NoticeInfo model;
	
	
	public NoticeInfo getModel() {
		return model;
	}

	public void setModel(NoticeInfo model) {
		this.model = model;
	}

	
	
	public void prepare() {
		areas = directoryService.getAreas();
		depts = directoryService.getGraduateDepartments();
		
		if (model != null && model.getArea() != null && ! model.getArea().trim().equals("")){
			locations = directoryService.getLocations(model.getArea());
		}
		if (model != null && model.getLocation() != null && !model.getLocation().trim().equals("")){
			dormitorys = directoryService.getDormitory(model.getLocation());
		}
		
		majorList = directoryService.getGraduateMajors();
		
		
		ActionContext context = ActionContext.getContext();
		String userId = (String)context.getSession().get("account");
	    dept  = quartersService.getManageDept(userId);
	}
	public String input(){
		//managers = quartersManagerService.getManagers();
		prepare();
		if (dept == null){
			  return "noRight";
			}
		
		
		return this.INPUT;
	}
	
	public String search(){
		ActionContext context = ActionContext.getContext();
		String userId = (String)context.getSession().get("account");
		count = quartersNoticeService.searchStudents(students,userId,model, pageNo, pageSize);
		request.setAttribute("count",new Integer(count));
		request.setAttribute("pageSize",new Integer(pageSize));
		if(count <=0 ){
			this.addActionMessage("没有要入住的学生!");
		}
		prepare();
		return this.INPUT;
	}
	public void setQuartersService(IQuartersService quartersService) {
		this.quartersService = quartersService;
	}
	//分页
	public int getPageNo() {
		return pageNo;
	}
	public void setPageNo(int pageNo) {
		this.pageNo = pageNo;
	}
	public int getPageSize() {
		return pageSize;
	}
	public void setPageSize(int pageSize) {
		this.pageSize = pageSize;
	}
	public int getCount() {
		return count;
	}
	public void setCount(int count) {
		this.count = count;
	}
	public void setDirectoryService(IDirectoryService directoryService) {
		this.directoryService = directoryService;
	}
	public List getLocations() {
		return locations;
	}
	public void setLocations(List locations) {
		this.locations = locations;
	}
	
	public List getAreas() {
		return areas;
	}
	public void setAreas(List areas) {
		this.areas = areas;
	}
	public List getDormitorys() {
		return dormitorys;
	}
	public void setDormitorys(List dormitorys) {
		this.dormitorys = dormitorys;
	}
	
	public TabSsDept getDept() {
		return dept;
	}
	public void setDept(TabSsDept dept) {
		this.dept = dept;
	}
	public void setQuartersNoticeService(
			IQuartersNoticeService quartersNoticeService) {
		this.quartersNoticeService = quartersNoticeService;
	}

	public void setServletRequest(HttpServletRequest request) {
		
		this.request = request;
	}

	public List getStudents() {
		return students;
	}

	public void setStudents(List students) {
		this.students = students;
	}

	public List getDepts() {
		return depts;
	}

	public void setDepts(List depts) {
		this.depts = depts;
	}

	public List getMajorList() {
		return majorList;
	}

	public void setMajorList(List majorList) {
		this.majorList = majorList;
	}

	

	
	
	
}
