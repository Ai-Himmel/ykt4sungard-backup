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

import org.king.common.service.IDirectoryService;
import org.king.dormitorymanage.domain.Dormitorymodel;
import org.king.quarters.domain.TabSsDept;
import org.king.quarters.service.IQuartersService;

import com.opensymphony.xwork.ActionContext;
import com.opensymphony.xwork.ActionSupport;

public class AddOrUpdateQuartersAction extends ActionSupport {

	private IQuartersService quartersService;
	private IDirectoryService directoryService;
	
	private Dormitorymodel model ;
	private Map depts;
	private List locations;
	private List areas;
	private List dormitorys;
	private List sexs;
	private List levels;
	private List directions;
	public List getDirections() {
		return directions;
	}

	public void setDirections(List directions) {
		this.directions = directions;
	}

	public List getLevels() {
		return levels;
	}

	public void setLevels(List levels) {
		this.levels = levels;
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

	public List getLocations() {
		return locations;
	}

	public void setLocations(List locations) {
		this.locations = locations;
	}

	public List getSexs() {
		return sexs;
	}

	public void setSexs(List sexs) {
		this.sexs = sexs;
	}

	public Map getDepts() {
		return depts;
	}

	public void setDepts(Map depts) {
		this.depts = depts;
	}

	public Dormitorymodel getModel() {
		return model;
	}

	public void setModel(Dormitorymodel model) {
		this.model = model;
	}

	public String input(){
		
		if(model != null && model.getDormitoryId() != null){
			model = quartersService.getQuarters( model.getDormitoryId());
			
		}
		prepare();
		return this.INPUT;
	}
	
	public String addOrUpdate(){
	
		try{
		if (!this.hasErrors()){
		
			quartersService.addOrUpdateQuarters(model);
			this.addActionMessage("��ӻ���³ɹ�!");
		}
		}catch(Throwable e){
			this.addActionMessage(e.getMessage());
		}
		prepare();
		this.addActionMessage("�д�����!");
		return this.INPUT;
	}

	public void setQuartersService(IQuartersService quartersService) {
		this.quartersService = quartersService;
	}

	public void prepare() {
		ActionContext context = ActionContext.getContext();
		String userId = (String)context.getSession().get("account");
		TabSsDept dept = quartersService.getManageDept(userId);
		depts  = new HashMap();
		depts.put("","�޲���");
		if (dept != null){
			depts.put(dept.getId(),dept.getName());
		}
		areas = directoryService.getAreas();
		sexs = directoryService.getSexs();
		levels =directoryService.getLevels();
		directions = directoryService.getDirections();
		if (model != null && model.getArea() != null && ! model.getArea().trim().equals("")){
			locations = directoryService.getLocations(model.getArea());
		}
		if (model != null && model.getLocation() != null && !model.getLocation().trim().equals("")){
			dormitorys = directoryService.getDormitory(model.getLocation());
		}
		
	}

	public void setDirectoryService(IDirectoryService directoryService) {
		this.directoryService = directoryService;
	}

	
}
