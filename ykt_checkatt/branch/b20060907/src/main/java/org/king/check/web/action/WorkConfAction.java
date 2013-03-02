package org.king.check.web.action;


import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.check.domain.Workconf;
import org.king.check.service.WorkConfService;
import org.king.framework.web.action.BaseAction;
import org.springframework.web.util.WebUtils;

public class WorkConfAction extends BaseAction{
	private static final Log log = LogFactory.getLog(WorkConfAction.class);
	
	private WorkConfService workConfService;
	

	public void setWorkConfService(WorkConfService workConfService) {
		this.workConfService = workConfService;
	}
	public ActionForward goWorkConf(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("goWorkConf");
		
		return mapping.findForward("goWorkConf");
	}
	public ActionForward addWorkConf_step1(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("addWorkConf_step1");
		
		return mapping.findForward("add_step1");
	}
	public ActionForward addWorkConf(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("addWorkConf");
		Map filterMap = WebUtils.getParametersStartingWith(request, "add_");
		
		Workconf workConf=new Workconf();
		
		workConf.setConfname((String)filterMap.get("confName"));
		workConf.setOffdutyovertime(new Integer((String)filterMap.get("offDutyLastTime")));
		workConf.setOndutyad(new Integer((String)filterMap.get("ondutyAdvancedTime")));
		workConf.setPermitlatetime(new Integer((String)filterMap.get("permitLateTime")));
		workConf.setPreearly(new Integer((String)filterMap.get("permitEarly")));
		
		workConfService.saveWorkConf(workConf);
		
		request.setAttribute("workConf",workConf);
		return mapping.findForward("saveOk");
	}
	public ActionForward search(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("search");
		Map filterMap = WebUtils.getParametersStartingWith(request, "search_");
		
		List workConfList=workConfService.search(filterMap);
		request.setAttribute("workConfList",workConfList);
		request.setAttribute("show","block");
		return mapping.findForward("searchRes");
	}
	public ActionForward delete(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("delete");
		String workIds[]=request.getParameterValues("itemlist");
		
		for(int i=0;i<workIds.length;i++)
		{
			workConfService.deleteWorkConf(workIds[i]);
		}
		request.setAttribute("msg","删除成功");
		return mapping.findForward("deleteOk");
	}
	public ActionForward update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("update");
		Map filterMap = WebUtils.getParametersStartingWith(request, "add_");
		
		Workconf workConf=workConfService.getWorkConf((String)filterMap.get("workConfId"));
		
		workConf.setConfname((String)filterMap.get("confName"));
		workConf.setOffdutyovertime(new Integer((String)filterMap.get("offDutyLastTime")));
		workConf.setOndutyad(new Integer((String)filterMap.get("ondutyAdvancedTime")));
		workConf.setPermitlatetime(new Integer((String)filterMap.get("permitLateTime")));
		workConf.setPreearly(new Integer((String)filterMap.get("permitEarly")));
		
		workConfService.updateWorkConf(workConf);
		
		request.setAttribute("msg","修改成功");
		return mapping.findForward("updateOk");
	}
	public ActionForward update_step1(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("update_step1");
		
		String workConfId=request.getParameter("workConfid");
		
		Workconf workConf=workConfService.getWorkConf(workConfId);
		
		request.setAttribute("workConf",workConf);
		
		return mapping.findForward("update_step1");
	}
}
