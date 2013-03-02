/**
 * 
 */
package org.king.check.web.action;

import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.check.config.CommonConfig;
import org.king.check.domain.Department;
import org.king.check.domain.Vacation;
import org.king.check.service.DepartmentService;
import org.king.check.service.VacationService;
import org.king.framework.web.action.BaseAction;
import org.springframework.web.util.WebUtils;

/**
 * @author a
 *
 */
public class VacationAction extends BaseAction{
	private static final Log log = LogFactory.getLog(VacationAction.class);
	
	private DepartmentService departmentService;
	
	private VacationService vacationService;
	
	
	public void setVacationService(VacationService vacationService) {
		this.vacationService = vacationService;
	}
	public void setDepartmentService(DepartmentService departmentService) {
		this.departmentService = departmentService;
	}
	public ActionForward goVacation(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("goVacation");
		
		return mapping.findForward("goVacation");
	}
	public ActionForward addVacation_step1(ActionMapping mapping, ActionForm form,//��д����
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("addVacation_step1");
		
		List departmentTree=departmentService.getDepartmentTree(0,null);
		request.setAttribute("departmentTree",departmentTree);
		
		return mapping.findForward("addVacation_step1");
	}
	public ActionForward addVacation(ActionMapping mapping, ActionForm form,//���ӽڼ���
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("addVacation");
		
		Map filterMap = WebUtils.getParametersStartingWith(request, "new_");
		String startDate=(String)filterMap.get("startMonth")+(String)filterMap.get("startDay");
		String endDate=(String)filterMap.get("endMonth")+(String)filterMap.get("endDay");
		
		Department department=departmentService.getDepartment((String)filterMap.get("departId"));
		
		
		Vacation vacation=new Vacation();
		vacation.setDepartid((String)filterMap.get("departId"));
		vacation.setVactionalname((String)filterMap.get("confName"));
		vacation.setStartdate(startDate);
		vacation.setEnddate(endDate);
		if(department.getParent()==null)
		{
			vacation.setIsglobe(CommonConfig.isGlobe);//����Ϊ�������ţ�����������Ϊȫ��
		}
		
		vacationService.save(vacation);
		
		request.setAttribute("confname",vacation.getVactionalname());
		request.setAttribute("startMonth",(String)filterMap.get("startMonth"));
		request.setAttribute("startDay",(String)filterMap.get("startDay"));
		
		request.setAttribute("endMonth",(String)filterMap.get("endMonth"));
		request.setAttribute("endDay",(String)filterMap.get("endDay"));
		
		request.setAttribute("dptName",department.getName());
		
		
		return mapping.findForward("showDetail");
	}
	public ActionForward addConfirm(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("addConfirm");
		Map filterMap = WebUtils.getParametersStartingWith(request, "new_");

		Department department=departmentService.getDepartment((String)filterMap.get("departId"));
		/*
		 * �õ���ǰ���ŵĹ��ݼ���
		 */
		List vacationList=vacationService.getVacationsByDeptId((String)filterMap.get("departId"));
		String va="";
		if(!vacationList.isEmpty())
		{
			Iterator vaIte=vacationList.iterator();
			while(vaIte.hasNext())
			{
				Vacation vacation=(Vacation)vaIte.next();
				va+=vacation.getStartdate()+"---"+vacation.getEnddate()+"&nbsp;";
			}
		}
		/*
		 * �õ���һ�����Ź��ݼ���
		 */
		String parantVa="";
		Department parantDept=department.getParent();
		if(parantDept!=null)
		{
			vacationList=vacationService.getVacationsByDeptId(parantDept.getId());
			if(!vacationList.isEmpty())
			{
				Iterator vaIte=vacationList.iterator();
				while(vaIte.hasNext())
				{
					Vacation vacation=(Vacation)vaIte.next();
					parantVa+=vacation.getStartdate()+"---"+vacation.getEnddate()+"&nbsp;";
				}
			}
		}
		/*
		 * �õ�ȫ�ֹ��ݼ���
		 */		
		vacationList=vacationService.getGlobeVacation();
		String globeVa="";
		if(vacationList!=null&&!vacationList.isEmpty())
		{
			Iterator vaIte=vacationList.iterator();
			while(vaIte.hasNext())
			{
				Vacation vacation=(Vacation)vaIte.next();
				globeVa+=vacation.getStartdate()+"---"+vacation.getEnddate()+"&nbsp;";
			}
		}
		request.setAttribute("new_startMonth",(String)filterMap.get("startMonth"));
		request.setAttribute("new_startDay",(String)filterMap.get("startDay"));
		request.setAttribute("new_confname",(String)filterMap.get("confName"));
		request.setAttribute("new_endMonth",(String)filterMap.get("endMonth"));
		request.setAttribute("new_endDay",(String)filterMap.get("endDay"));
		request.setAttribute("parantVa",parantVa);
		request.setAttribute("va",va);
		request.setAttribute("globeVa",globeVa);
		request.setAttribute("dptName",department.getName());
		request.setAttribute("new_departId",(String)filterMap.get("departId"));
		
		return mapping.findForward("addConfirm");
	}
	public ActionForward search(ActionMapping mapping, ActionForm form,//����
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("search");
		
		Map filterMap = WebUtils.getParametersStartingWith(request, "search_");
		List vacationList=vacationService.searchByFilter(filterMap);
		
		request.setAttribute("vacationList",vacationList);
		request.setAttribute("show","block");
		return mapping.findForward("goVacation");
	}
	public ActionForward update(ActionMapping mapping, ActionForm form,//�޸�
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("update");
		Map filterMap = WebUtils.getParametersStartingWith(request, "new_");
		String startDate=(String)filterMap.get("startMonth")+(String)filterMap.get("startDay");
		String endDate=(String)filterMap.get("endMonth")+(String)filterMap.get("endDay");
		
		Vacation vacation=vacationService.get((String)filterMap.get("vid"));
		vacation.setEnddate(endDate);
		vacation.setStartdate(startDate);
		vacation.setVactionalname((String)filterMap.get("confName"));
		vacationService.update(vacation);
		
		request.setAttribute("msg","�޸ĳɹ�");
		return mapping.findForward("goVacation");
	}
	public ActionForward update_step1(ActionMapping mapping, ActionForm form,//�޸Ĳ���һ
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("update_step1");
		String vacationId=request.getParameter("vacationid");
		Vacation vacation=vacationService.get(vacationId);
		String startDate=vacation.getStartdate();
		String endDate=vacation.getEnddate();
		
		Department department=departmentService.getDepartment(vacation.getDepartid());
		
		
		request.setAttribute("vacation",vacation);
		request.setAttribute("start_month",startDate.substring(0,2));
		request.setAttribute("end_month",endDate.substring(0,2));
		request.setAttribute("start_day",endDate.substring(0,2));
		request.setAttribute("end_day",endDate.substring(2));
		request.setAttribute("depart_name",department.getName());
		
		return mapping.findForward("update");
	}
	public ActionForward delete(ActionMapping mapping, ActionForm form,//ɾ��
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("delete");
       String vacationIds[]=request.getParameterValues("itemlist");
		
		for(int i=0;i<vacationIds.length;i++)
		{
			vacationService.delete(vacationService.get(vacationIds[i]));
		}
		
		request.setAttribute("msg","ɾ���ɹ�");
		return mapping.findForward("goVacation");
	}
	
}
