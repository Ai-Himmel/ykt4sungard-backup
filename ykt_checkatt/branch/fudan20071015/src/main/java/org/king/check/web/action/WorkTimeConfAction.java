package org.king.check.web.action;

import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.check.domain.Tworktimeinfo;
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
		return mapping.findForward("addWorkTime");
	}
	public ActionForward addworkTime(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession();
		Map filterMap = WebUtils.getParametersStartingWith(request, "add_");
		
		Tworktimeinfo workTimeComf =new Tworktimeinfo();
		
		workTimeComf.setWorktimeName((String)filterMap.get("confName"));
		workTimeComf.setOfftime1((String)filterMap.get("offdutytime1_hour")+(String)filterMap.get("offdutytime1_min"));
		workTimeComf.setOfftime2((String)filterMap.get("offdutytime2_hour")+(String)filterMap.get("offdutytime2_min"));
		workTimeComf.setOfftime3((String)filterMap.get("offdutytime3_hour")+(String)filterMap.get("offdutytime3_min"));
		workTimeComf.setOfftime4((String)filterMap.get("offdutytime4_hour")+(String)filterMap.get("offdutytime4_min"));
		workTimeComf.setOntime1((String)filterMap.get("ondutytime1_hour")+(String)filterMap.get("ondutytime1_min"));
		workTimeComf.setOntime2((String)filterMap.get("ondutytime2_hour")+(String)filterMap.get("ondutytime2_min"));
		workTimeComf.setOntime3((String)filterMap.get("ondutytime3_hour")+(String)filterMap.get("ondutytime3_min"));
		workTimeComf.setOntime4((String)filterMap.get("ondutytime4_hour")+(String)filterMap.get("ondutytime4_min"));
		workTimeComf.setDeptId((String)session.getAttribute("personDeptId"));
		
		workTimeConfService.saveWorkTimeConf(workTimeComf);
		
		request.setAttribute("workTimeComf",workTimeComf);
		
		return mapping.findForward("addOk");
	}
	public ActionForward search(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		searchWorkTimeList(request);
		return mapping.findForward("searchRes");
	}
	public ActionForward delete(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String workIds[]=request.getParameterValues("itemlist");
		
		for(int i=0;i<workIds.length;i++)
		{
			workTimeConfService.deleteWorkTimeConf(workIds[i]);
		}
		
		searchWorkTimeList(request);
		return mapping.findForward("searchRes");
	}
	public ActionForward update_step1(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		String workTimeConfId=request.getParameter("workTimeConfId");
		
		Tworktimeinfo workTimeComf=workTimeConfService.getWorkTimeConf(workTimeConfId);
		
		String temp=workTimeComf.getOfftime1();
		if(StringUtils.isNotEmpty(temp))
		{
			request.setAttribute("add_offdutytime1_hour",temp.substring(0,2));
			request.setAttribute("add_offdutytime1_min",temp.substring(2));
		}
		temp=workTimeComf.getOfftime2();
		if(StringUtils.isNotEmpty(temp))
		{
			request.setAttribute("add_offdutytime2_hour",temp.substring(0,2));
			request.setAttribute("add_offdutytime2_min",temp.substring(2));
		}
		temp=workTimeComf.getOfftime3();
		if(StringUtils.isNotEmpty(temp))
		{
			request.setAttribute("add_offdutytime3_hour",temp.substring(0,2));
			request.setAttribute("add_offdutytime3_min",temp.substring(2));
		}
		temp=workTimeComf.getOfftime4();
		if(StringUtils.isNotEmpty(temp))
		{
			request.setAttribute("add_offdutytime4_hour",temp.substring(0,2));
			request.setAttribute("add_offdutytime4_min",temp.substring(2));
		}

		temp=workTimeComf.getOntime1();
		if(StringUtils.isNotEmpty(temp))
		{
			request.setAttribute("add_ondutytime1_hour",temp.substring(0,2));
			request.setAttribute("add_ondutytime1_min",temp.substring(2));
		}
		temp=workTimeComf.getOntime2();
		if(StringUtils.isNotEmpty(temp))
		{
			request.setAttribute("add_ondutytime2_hour",temp.substring(0,2));
			request.setAttribute("add_ondutytime2_min",temp.substring(2));
		}
		temp=workTimeComf.getOntime3();
		if(StringUtils.isNotEmpty(temp))
		{
			request.setAttribute("add_ondutytime3_hour",temp.substring(0,2));
			request.setAttribute("add_ondutytime3_min",temp.substring(2));
		}
		temp=workTimeComf.getOntime4();
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
		//log.debug("update");
		HttpSession session = request.getSession();
		Map filterMap = WebUtils.getParametersStartingWith(request, "add_");
		
		Tworktimeinfo workTimeComf =workTimeConfService.getWorkTimeConf((String)filterMap.get("worktimeconfid"));
		
		workTimeComf.setWorktimeName((String)filterMap.get("confName"));
		workTimeComf.setOfftime1((String)filterMap.get("offdutytime1_hour")+(String)filterMap.get("offdutytime1_min"));
		workTimeComf.setOfftime2((String)filterMap.get("offdutytime2_hour")+(String)filterMap.get("offdutytime2_min"));
		workTimeComf.setOfftime3((String)filterMap.get("offdutytime3_hour")+(String)filterMap.get("offdutytime3_min"));
		workTimeComf.setOfftime4((String)filterMap.get("offdutytime4_hour")+(String)filterMap.get("offdutytime4_min"));
		workTimeComf.setOntime1((String)filterMap.get("ondutytime1_hour")+(String)filterMap.get("ondutytime1_min"));
		workTimeComf.setOntime2((String)filterMap.get("ondutytime2_hour")+(String)filterMap.get("ondutytime2_min"));
		workTimeComf.setOntime3((String)filterMap.get("ondutytime3_hour")+(String)filterMap.get("ondutytime3_min"));
		workTimeComf.setOntime4((String)filterMap.get("ondutytime4_hour")+(String)filterMap.get("ondutytime4_min"));
		workTimeComf.setDeptId((String)session.getAttribute("personDeptId"));
		
		workTimeConfService.updateWorkTimeConf(workTimeComf);
		
		searchWorkTimeList(request);
		return mapping.findForward("searchRes");
	}
	
	private void searchWorkTimeList(HttpServletRequest request)throws Exception{
		
		Map filterMap = WebUtils.getParametersStartingWith(request, "search_");
		
		List workTimeList=workTimeConfService.search(filterMap);
		
		workTimeList=workTimeConfService.reForMatWorkTimeList(workTimeList);
		
		request.setAttribute("workTimeList",workTimeList);
	}
}
