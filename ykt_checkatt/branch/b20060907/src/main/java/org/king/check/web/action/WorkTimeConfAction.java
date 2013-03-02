package org.king.check.web.action;

import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.check.domain.Worktimeconf;
import org.king.check.service.WorkTimeConfService;
import org.king.framework.web.action.BaseAction;
import org.springframework.web.util.WebUtils;

public class WorkTimeConfAction extends BaseAction{
	private static final Log log = LogFactory.getLog(WorkTimeConfAction.class);
	
	private  WorkTimeConfService workTimeConfService;
	
	

	public void setWorkTimeConfService(WorkTimeConfService workTimeConfService) {
		this.workTimeConfService = workTimeConfService;
	}

	public ActionForward goWorkTime(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("goWorkTime");
		
		return mapping.findForward("goWorkTime");
	}
	
	public ActionForward addworkTime_step1(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("addWorkTimeStep1");
		
		return mapping.findForward("addWorkTime");
	}
	public ActionForward addworkTime(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("addworkTime");
		
		Map filterMap = WebUtils.getParametersStartingWith(request, "add_");
		
		Worktimeconf workTimeComf =new Worktimeconf();
		
		workTimeComf.setConfname((String)filterMap.get("confName"));
		workTimeComf.setOffdutytime1((String)filterMap.get("offdutytime1_hour")+(String)filterMap.get("offdutytime1_min"));
		workTimeComf.setOffdutytime2((String)filterMap.get("offdutytime2_hour")+(String)filterMap.get("offdutytime2_min"));
		workTimeComf.setOffdutytime3((String)filterMap.get("offdutytime3_hour")+(String)filterMap.get("offdutytime3_min"));
		workTimeComf.setOffdutytime4((String)filterMap.get("offdutytime4_hour")+(String)filterMap.get("offdutytime4_min"));
		workTimeComf.setOndutytime1((String)filterMap.get("ondutytime1_hour")+(String)filterMap.get("ondutytime1_min"));
		workTimeComf.setOndutytime2((String)filterMap.get("ondutytime2_hour")+(String)filterMap.get("ondutytime2_min"));
		workTimeComf.setOndutytime3((String)filterMap.get("ondutytime3_hour")+(String)filterMap.get("ondutytime3_min"));
		workTimeComf.setOndutytime4((String)filterMap.get("ondutytime4_hour")+(String)filterMap.get("ondutytime4_min"));
		
		log.debug((String)filterMap.get("offdutytime1_hour")+(String)filterMap.get("offdutytime1_min"));
		
		workTimeConfService.saveWorkTimeConf(workTimeComf);
		
		request.setAttribute("workTimeComf",workTimeComf);
		
		return mapping.findForward("addOk");
	}
	public ActionForward search(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("search");
		
		Map filterMap = WebUtils.getParametersStartingWith(request, "search_");
		
		List workTimeList=workTimeConfService.search(filterMap);
		
		workTimeList=workTimeConfService.reForMatWorkTimeList(workTimeList);
		
		request.setAttribute("workTimeList",workTimeList);
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
			workTimeConfService.deleteWorkTimeConf(workIds[i]);
		}
		request.setAttribute("msg","删除成功");
		return mapping.findForward("deleteOk");
	}
	public ActionForward update_step1(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("update_step1");
		
		String workTimeConfId=request.getParameter("workTimeConfId");
		
		Worktimeconf workTimeComf=workTimeConfService.getWorkTimeConf(workTimeConfId);
		
		String temp=workTimeComf.getOffdutytime1();
		if(StringUtils.isNotEmpty(temp))
		{
			request.setAttribute("add_offdutytime1_hour",temp.substring(0,2));
			request.setAttribute("add_offdutytime1_min",temp.substring(2));
		}
		temp=workTimeComf.getOffdutytime2();
		if(StringUtils.isNotEmpty(temp))
		{
			request.setAttribute("add_offdutytime2_hour",temp.substring(0,2));
			request.setAttribute("add_offdutytime2_min",temp.substring(2));
		}
		temp=workTimeComf.getOffdutytime3();
		if(StringUtils.isNotEmpty(temp))
		{
			request.setAttribute("add_offdutytime3_hour",temp.substring(0,2));
			request.setAttribute("add_offdutytime3_min",temp.substring(2));
		}
		temp=workTimeComf.getOffdutytime4();
		if(StringUtils.isNotEmpty(temp))
		{
			request.setAttribute("add_offdutytime4_hour",temp.substring(0,2));
			request.setAttribute("add_offdutytime4_min",temp.substring(2));
		}

		temp=workTimeComf.getOndutytime1();
		if(StringUtils.isNotEmpty(temp))
		{
			request.setAttribute("add_ondutytime1_hour",temp.substring(0,2));
			request.setAttribute("add_ondutytime1_min",temp.substring(2));
		}
		temp=workTimeComf.getOndutytime2();
		if(StringUtils.isNotEmpty(temp))
		{
			request.setAttribute("add_ondutytime2_hour",temp.substring(0,2));
			request.setAttribute("add_ondutytime2_min",temp.substring(2));
		}
		temp=workTimeComf.getOndutytime3();
		if(StringUtils.isNotEmpty(temp))
		{
			request.setAttribute("add_ondutytime3_hour",temp.substring(0,2));
			request.setAttribute("add_ondutytime3_min",temp.substring(2));
		}
		temp=workTimeComf.getOndutytime4();
		if(StringUtils.isNotEmpty(temp))
		{
			request.setAttribute("add_ondutytime4_hour",temp.substring(0,2));
			request.setAttribute("add_ondutytime4_min",temp.substring(2));
		}
		
		request.setAttribute("workTimeComf",workTimeComf);
		return mapping.findForward("update_step1");
	}
	public ActionForward update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("update");
		
		Map filterMap = WebUtils.getParametersStartingWith(request, "add_");
		
		Worktimeconf workTimeComf =workTimeConfService.getWorkTimeConf((String)filterMap.get("worktimeconfid"));
		
		workTimeComf.setConfname((String)filterMap.get("confName"));
		workTimeComf.setOffdutytime1((String)filterMap.get("offdutytime1_hour")+(String)filterMap.get("offdutytime1_min"));
		workTimeComf.setOffdutytime2((String)filterMap.get("offdutytime2_hour")+(String)filterMap.get("offdutytime2_min"));
		workTimeComf.setOffdutytime3((String)filterMap.get("offdutytime3_hour")+(String)filterMap.get("offdutytime3_min"));
		workTimeComf.setOffdutytime4((String)filterMap.get("offdutytime4_hour")+(String)filterMap.get("offdutytime4_min"));
		workTimeComf.setOndutytime1((String)filterMap.get("ondutytime1_hour")+(String)filterMap.get("ondutytime1_min"));
		workTimeComf.setOndutytime2((String)filterMap.get("ondutytime2_hour")+(String)filterMap.get("ondutytime2_min"));
		workTimeComf.setOndutytime3((String)filterMap.get("ondutytime3_hour")+(String)filterMap.get("ondutytime3_min"));
		workTimeComf.setOndutytime4((String)filterMap.get("ondutytime4_hour")+(String)filterMap.get("ondutytime4_min"));
		
		log.debug((String)filterMap.get("offdutytime1_hour")+(String)filterMap.get("offdutytime1_min"));
		
		workTimeConfService.updateWorkTimeConf(workTimeComf);
		
		request.setAttribute("msg","修改成功");
		return mapping.findForward("updateOk");
	}
}
