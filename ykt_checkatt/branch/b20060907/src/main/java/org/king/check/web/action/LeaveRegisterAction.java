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
import org.king.check.config.CommonConfig;
import org.king.check.service.LeaveInfoService;
import org.king.check.service.SysService;
import org.king.framework.web.action.BaseAction;
import org.springframework.web.util.WebUtils;

public class LeaveRegisterAction extends BaseAction{
	private static final Log log = LogFactory.getLog(LeaveRegisterAction.class);
	
	private LeaveInfoService leaveInfoService;
	private SysService sysService;
	
	

	public void setLeaveInfoService(LeaveInfoService leaveInfoService) {
		this.leaveInfoService = leaveInfoService;
	}
	
	public void setSysService(SysService sysService) {
		this.sysService = sysService;
	}


	public ActionForward goRegister(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("goRegister");
		
		request.setAttribute("display","none");
		return mapping.findForward("goRegister");
	}
	public ActionForward search(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("search clerk");
		Map filterMap = WebUtils.getParametersStartingWith(request, "register_");
		
		List clerkList=leaveInfoService.searchClerkForRegister(filterMap);
		
		if(clerkList.isEmpty())
		{
			request.setAttribute("display","none");
		}
		else 
		{
			request.setAttribute("display","block");
		}
		
		request.setAttribute("clerkList",clerkList);
		request.setAttribute("register_trueName",(String)filterMap.get("trueName"));
		request.setAttribute("register_cardNumber",(String)filterMap.get("cardNumber"));
		
		return mapping.findForward("searchClerk");
	}
	
	public ActionForward register(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("goRegister");
		
		String msg,url;
		Map filterMap = WebUtils.getParametersStartingWith(request, "register_");
						
		String checkValues[]=request.getParameterValues("itemlist");
		HttpSession session=request.getSession();
		
		
		log.debug("value-------------------------->"+checkValues[0]+"length------>"+checkValues.length);
		
		filterMap.put("checkValues",checkValues);
		filterMap.put("table",CommonConfig.table_LEAVEINFO);
		filterMap.put("operatorid",(String)session.getAttribute("account"));
		
		log.debug(request.getParameter("register_startDate"));
		
		List  existList=sysService.isExistDate(filterMap);
		if(!existList.isEmpty())
		{
			log.debug("isExist");
			url="history.back();";
			request.setAttribute("leaveList",existList);
			msg="登记失败,已有时间段重复";
		}
		else{
			List leaveList=leaveInfoService.addLeaveInfo(filterMap);
			url="window.location.href='leaveRegister.do?method=goRegister'";
			request.setAttribute("leaveList",leaveList);
			msg="登记成功";
		}
		
		request.setAttribute("display","none");
		request.setAttribute("msg",msg);
		request.setAttribute("url",url);
		return mapping.findForward("success");
	}
}
