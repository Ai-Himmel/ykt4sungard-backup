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
package org.king.summary.web.action;

import java.util.ArrayList;
import java.util.List;

import javax.servlet.http.HttpServletRequest;

import org.king.common.service.IDirectoryService;
import org.king.summary.service.IQueryService;

import com.opensymphony.webwork.interceptor.ServletRequestAware;
import com.opensymphony.xwork.ActionSupport;

public class QueryGraduateAction extends ActionSupport implements ServletRequestAware{

	private IQueryService queryService;

	private IDirectoryService directoryService;
	private HttpServletRequest request;
	
	
    private List students = new ArrayList();;
    private List minZus;
    private List guoJis;
    private List yuanXis;
    private List zhuanYes;
    private List leiBies;
    private List areas;
    private List locations;
    private List louHaos;
    
    private int pageNo = 1;
    private int count;
    private QueryInfo model;
	

	public int getCount() {
		return count;
	}

	public void setCount(int count) {
		this.count = count;
	}

	public int getPageNo() {
		return pageNo;
	}

	public void setPageNo(int pageNo) {
		this.pageNo = pageNo;
	}


	private void prepare(){
		minZus = directoryService.getNations();
		guoJis = directoryService.getNationalitys();
		yuanXis = directoryService.getGraduateDepartments();
		zhuanYes = directoryService.getGraduateMajors();
		leiBies = directoryService.getStudentTypes();
		areas = directoryService.getAreas();
		if (model != null && model.getArea() != null && !model.getArea().trim().equals("")){
			locations = directoryService.getLocations(model.getArea().trim());
		}
		if (model != null && model.getLocation() != null && !model.getLocation().trim().equals("")){
			louHaos = directoryService.getDormitory(model.getLocation().trim());
		}
	}
	public String input(){
		prepare();
		return this.INPUT;
		
	}

	public String query(){
		
		count = queryService.queryGraduateInfos(students,model,this.getPageNo(),100);
		request.setAttribute("count",new Integer(count));
		prepare();
		return this.INPUT;
		
	}

	

	public void setServletRequest(HttpServletRequest request) {
		// TODO Auto-generated method stub
		this.request = request;
	}





	public void setQueryService(IQueryService queryService) {
		this.queryService = queryService;
	}





	public QueryInfo getModel() {
		return model;
	}





	public void setModel(QueryInfo model) {
		this.model = model;
	}





	public List getStudents() {
		return students;
	}





	public void setStudents(List students) {
		this.students = students;
	}

	public List getAreas() {
		return areas;
	}

	public void setAreas(List areas) {
		this.areas = areas;
	}

	public List getGuoJis() {
		return guoJis;
	}

	public void setGuoJis(List guoJis) {
		this.guoJis = guoJis;
	}

	public List getLeiBies() {
		return leiBies;
	}

	public void setLeiBies(List leiBies) {
		this.leiBies = leiBies;
	}

	public List getLocations() {
		return locations;
	}

	public void setLocations(List locations) {
		this.locations = locations;
	}

	public List getLouHaos() {
		return louHaos;
	}

	public void setLouHaos(List louHaos) {
		this.louHaos = louHaos;
	}

	public List getMinZus() {
		return minZus;
	}

	public void setMinZus(List minZus) {
		this.minZus = minZus;
	}

	public List getYuanXis() {
		return yuanXis;
	}

	public void setYuanXis(List yuanXis) {
		this.yuanXis = yuanXis;
	}

	public List getZhuanYes() {
		return zhuanYes;
	}

	public void setZhuanYes(List zhuanYes) {
		this.zhuanYes = zhuanYes;
	}

	public void setDirectoryService(IDirectoryService directoryService) {
		this.directoryService = directoryService;
	}

	
	
	
	
}
