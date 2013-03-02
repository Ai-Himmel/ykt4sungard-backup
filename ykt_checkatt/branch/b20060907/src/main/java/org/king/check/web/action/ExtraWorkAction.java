package org.king.check.web.action;

import java.net.URLDecoder;
import java.text.DateFormat;
import java.util.Calendar;
import java.util.HashMap;
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
import org.king.check.domain.Extraworkinfo;
import org.king.check.service.DepartmentService;
import org.king.check.service.ExtraWorkService;
import org.king.check.service.LeaveInfoService;
import org.king.check.service.SysService;
import org.king.framework.web.action.BaseAction;
import org.springframework.web.util.WebUtils;

public class ExtraWorkAction  extends BaseAction{
	private static final Log log = LogFactory.getLog(ExtraWorkAction.class);
	
	private ExtraWorkService extraWorkService;
	
	private LeaveInfoService leaveInfoService;
	
	private DepartmentService departmentService;
	
	private SysService sysService;
	
	
	
	public void setSysService(SysService sysService) {
		this.sysService = sysService;
	}

	public void setDepartmentService(DepartmentService departmentService) {
		this.departmentService = departmentService;
	}

	public void setLeaveInfoService(LeaveInfoService leaveInfoService) {
		this.leaveInfoService = leaveInfoService;
	}
	
	public void setExtraWorkService(ExtraWorkService extraWorkService) {
		this.extraWorkService = extraWorkService;
	}



	public ActionForward goExtraWork(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("goExtraWork");

		
		return mapping.findForward("goExtraWork");
	}
	public ActionForward search(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("search");
		Map filterMap = WebUtils.getParametersStartingWith(request, "register_");
		
		List clerkList=leaveInfoService.searchClerkForRegister(filterMap);
		
		request.setAttribute("clerkList",clerkList);
		request.setAttribute("show","block");
		
		return mapping.findForward("search");
	}
	public ActionForward register(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("register");
		String msg,url;
		Map filterMap = WebUtils.getParametersStartingWith(request, "register_");
		HttpSession session=request.getSession();
		
		String checkValues[]=request.getParameterValues("itemlist");
		
		filterMap.put("checkValues",checkValues);
		filterMap.put("operatorid",(String)session.getAttribute("account"));

		filterMap.put("table",CommonConfig.table_EXTRAWORKINFO);
		
		List  existList=sysService.isExistDate(filterMap);
		if(!existList.isEmpty())
		{
			log.debug("isExist");
			url="history.back();";
			request.setAttribute("extraList",existList);
			msg="登记失败,已有时间段重复";
		}
		else
		{
			List extraList=extraWorkService.addExtraWork(filterMap);
			url="window.location.href='extraWork.do?method=goExtraWork'";
			request.setAttribute("extraList",extraList);
			msg="登记成功";
		}
		
		request.setAttribute("msg",msg);
		request.setAttribute("url",url);
		return mapping.findForward("registerOk");
	}
	public ActionForward goSearchExtra(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("goSearchExtra");
		
		List departmentTree=departmentService.getDepartmentTree(0,null);
		
		request.setAttribute("departmentTree",departmentTree);
		return mapping.findForward("goSearchExtra");
	}
	public ActionForward searchExtraInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("searchExtraInfo");
		Map filterMap = WebUtils.getParametersStartingWith(request, "extra_");
		List departmentTree=departmentService.getDepartmentTree(0,null);
		
		List extraInfoList=extraWorkService.searchExtraWork(filterMap);
		
		request.setAttribute("extra_startDate",filterMap.get("startDate"));
		request.setAttribute("extra_endDate",filterMap.get("endDate"));
		request.setAttribute("extra_trueName",filterMap.get("trueName"));
		request.setAttribute("extraInfoList",extraInfoList);
		request.setAttribute("departmentTree",departmentTree);
		return mapping.findForward("operateOk");
	}
	public ActionForward preUpdate(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("preUpdate");//展现需要修改的信息
		
		Calendar startCal=Calendar.getInstance();
		Calendar endCal=Calendar.getInstance();
		String extrainfoid=request.getParameter("pre_extrainfoid");
		String clerkName=request.getParameter("pre_clerkName");
		clerkName=URLDecoder.decode(clerkName,"UTF-8");//字符解码
		
		Extraworkinfo extraworkinfo=new Extraworkinfo();
		
		if(extrainfoid!=null)
			extraworkinfo=extraWorkService.get(extrainfoid);
		
		startCal.setTime(extraworkinfo.getStartdate());
		endCal.setTime(extraworkinfo.getEnddate());
		
		String new_startDate=DateFormat.getDateInstance().format(extraworkinfo.getStartdate());
		String new_endDate=DateFormat.getDateInstance().format(extraworkinfo.getEnddate());
		
		request.setAttribute("extraworkinfo",extraworkinfo);
		request.setAttribute("clerkName",clerkName);
		request.setAttribute("new_startDate",new_startDate);
		request.setAttribute("new_endDate",new_endDate);
		request.setAttribute("new_startHour",new Integer(startCal.get(Calendar.HOUR_OF_DAY)));
		request.setAttribute("new_startMin",new Integer(startCal.get(Calendar.MINUTE)));
		request.setAttribute("new_endHour",new Integer(endCal.get(Calendar.HOUR_OF_DAY)));
		request.setAttribute("new_endMin",new Integer(endCal.get(Calendar.MINUTE)));
		
		return mapping.findForward("updateExtra");
	}
	
	public ActionForward update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("update");
		List departmentTree=departmentService.getDepartmentTree(0,null);
		request.setAttribute("departmentTree",departmentTree);
		
		HttpSession session=request.getSession();
		
		Map filterMap = WebUtils.getParametersStartingWith(request, "new_");
		
		filterMap.put("operatorid",(String)session.getAttribute("account"));
		
		extraWorkService.updateExtraInfo(filterMap);
		request.setAttribute("msg","修改成功");
		
		return mapping.findForward("operateOk");
	}
	public ActionForward delete(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("delete");
		List departmentTree=departmentService.getDepartmentTree(0,null);
		request.setAttribute("departmentTree",departmentTree);
		
		String extraIds[]=request.getParameterValues("itemlist");
		
		extraWorkService.deleteExtraInfo(extraIds);
		
		request.setAttribute("msg","成功删除"+extraIds.length+"信息!");
		
		return mapping.findForward("operateOk");
	}
	public ActionForward goStatic(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("goStatic");
		List departmentTree=departmentService.getDepartmentTree(0,null);
		request.setAttribute("departmentTree",departmentTree);
		
		return mapping.findForward("goStatic");
	}
	public ActionForward staticExtraInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("staticExtraInfo");
		Map filterMap = WebUtils.getParametersStartingWith(request, "extra_");
		List departmentTree=departmentService.getDepartmentTree(0,null);
		request.setAttribute("departmentTree",departmentTree);
		
		
		List staticInfoList=extraWorkService.staticExtraInfo(filterMap);
		request.setAttribute("staticInfoList",staticInfoList);
		request.setAttribute("endDate",filterMap.get("endDate"));
		
		return mapping.findForward("goStatic");
	}
	public ActionForward viewExtraDetail(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("viewExtraDetail");
		String startDate=request.getParameter("startDate");
		String endDate=request.getParameter("endDate");
		Integer clerkId=new Integer(request.getParameter("clerkId"));
		
		Map filter=new HashMap();
		filter.put(CommonConfig.startDate,startDate);
		filter.put(CommonConfig.endDate,endDate);
		filter.put("clerkId",clerkId);
		
		List extraDetailList=extraWorkService.getExtraWorkDetail(filter);
		
		request.setAttribute("extraDetailList",extraDetailList);
		
		return mapping.findForward("showDetail");
	}

}
