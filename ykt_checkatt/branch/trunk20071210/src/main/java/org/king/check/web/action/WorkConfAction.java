package org.king.check.web.action;

import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.check.domain.Tworkconfinfo;
import org.king.check.service.WorkConfService;
import org.king.framework.web.action.BaseAction;
import org.springframework.web.util.WebUtils;

public class WorkConfAction extends BaseAction {
	private static final Log log = LogFactory.getLog(WorkConfAction.class);

	private WorkConfService workConfService;

	public void setWorkConfService(WorkConfService workConfService) {
		this.workConfService = workConfService;
	}

	public ActionForward goWorkConf(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		//log.debug("goWorkConf");

		return mapping.findForward("goWorkConf");
	}

	public ActionForward addWorkConf_step1(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		//log.debug("addWorkConf_step1");

		return mapping.findForward("add_step1");
	}

	public ActionForward addWorkConf(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession();
		Map filterMap = WebUtils.getParametersStartingWith(request, "add_");

		Tworkconfinfo workConf = new Tworkconfinfo();

		workConf.setWorkconfName((String) filterMap.get("confName"));
		workConf.setDelayTime(new Integer((String) filterMap.get("offDutyLastTime")));
		workConf.setOverTime(new Integer((String) filterMap.get("ondutyAdvancedTime")));
		workConf.setLeaveearlyTime(new Integer(0));
		workConf.setOverdueTime(new Integer(0));
		workConf.setCheckTime(new Integer((String)filterMap.get("checkTime")));
		workConf.setDeptId((String)session.getAttribute("personDeptId"));
		workConfService.saveWorkConf(workConf);

		request.setAttribute("workConf", workConf);
		return mapping.findForward("saveOk");
	}

	public ActionForward search(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		searchWorkConfList(request);
		return mapping.findForward("searchRes");
	}

	public ActionForward delete(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String workIds[] = request.getParameterValues("itemlist");

		StringBuffer tempIds = new StringBuffer(128);
		for (int i=0;i<workIds.length;i++){
			if (i==workIds.length-1){
				tempIds.append("'").append(workIds[i]).append("'");
			}else{
				tempIds.append("'").append(workIds[i]).append("'").append(",");
			}
		}
		List usedWork = workConfService.getUsedWorkConf(tempIds.toString());
		if (usedWork.size()>0){
			request.setAttribute("msg","要删除的考勤制度中有已经被引用的项，不能删除！");
		}else{
			for (int i = 0; i < workIds.length; i++) {
				workConfService.deleteWorkConf(workIds[i]);
			}
			request.setAttribute("msg","删除考勤制度成功!");
		}		

		searchWorkConfList(request);
		return mapping.findForward("searchRes");
	}

	public ActionForward update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		//log.debug("update");
		HttpSession session = request.getSession();
		Map filterMap = WebUtils.getParametersStartingWith(request, "add_");

		Tworkconfinfo workConf = workConfService.getWorkConf((String) filterMap
				.get("workConfId"));

		workConf.setWorkconfName((String) filterMap.get("confName"));
		workConf.setDelayTime(new Integer((String) filterMap.get("offDutyLastTime")));
		workConf.setOverTime(new Integer((String) filterMap.get("ondutyAdvancedTime")));
		workConf.setLeaveearlyTime(new Integer(0));
		workConf.setOverdueTime(new Integer(0));
		workConf.setCheckTime(new Integer((String)filterMap.get("checkTime")));
		workConf.setDeptId((String)session.getAttribute("personDeptId"));

		workConfService.updateWorkConf(workConf);

		//request.setAttribute("msg", "修改成功");
		searchWorkConfList(request);
		return mapping.findForward("searchRes");
	}

	public ActionForward update_step1(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("update_step1");

		String workConfId = request.getParameter("workConfid");

		Tworkconfinfo workConf = workConfService.getWorkConf(workConfId);

		request.setAttribute("workConf", workConf);

		return mapping.findForward("update_step1");
	}
	
	private void searchWorkConfList(HttpServletRequest request)throws Exception{
		Map filterMap = WebUtils.getParametersStartingWith(request, "search_");

		List workConfList = workConfService.search(filterMap);
		request.setAttribute("workConfList", workConfList);

	}
}
