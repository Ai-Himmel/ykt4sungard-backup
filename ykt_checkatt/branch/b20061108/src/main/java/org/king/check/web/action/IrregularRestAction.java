package org.king.check.web.action;

import java.net.URLDecoder;
import java.text.DateFormat;
import java.util.Calendar;
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
import org.king.check.domain.Irregularrest;
import org.king.check.service.DepartmentService;
import org.king.check.service.IrregularRestService;
import org.king.check.service.LeaveInfoService;
import org.king.framework.web.action.BaseAction;
import org.springframework.web.util.WebUtils;

public class IrregularRestAction extends BaseAction{
	private static final Log log = LogFactory.getLog(IrregularRestAction.class);
	
    private LeaveInfoService leaveInfoService;
	
	private DepartmentService departmentService;
	
	private IrregularRestService irregularRestService;

	public void setDepartmentService(DepartmentService departmentService) {
		this.departmentService = departmentService;
	}

	public void setLeaveInfoService(LeaveInfoService leaveInfoService) {
		this.leaveInfoService = leaveInfoService;
	}
	
	public void setIrregularRestService(IrregularRestService irregularRestService) {
		this.irregularRestService = irregularRestService;
	}
	
	public ActionForward goIrregularRest(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("goIrregularRest");
		
		return mapping.findForward("goIrre");
	}
	public ActionForward goSearchIrre(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("goSearchIrre");
        List departmentTree=departmentService.getDepartmentTree(0,null);
		
		request.setAttribute("departmentTree",departmentTree);
		return mapping.findForward("goSearchIrre");
	}
	
	public ActionForward searchClerk(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("searchClerk");
       Map filterMap = WebUtils.getParametersStartingWith(request, "register_");
		
		List clerkList=leaveInfoService.searchClerkForRegister(filterMap);
		
		request.setAttribute("clerkList",clerkList);
		request.setAttribute("show","block");
		
		return mapping.findForward("goIrre");
	}
	public ActionForward register(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("register");
		Map filterMap = WebUtils.getParametersStartingWith(request, "register_");
		HttpSession session=request.getSession();
		
		String checkValues[]=request.getParameterValues("itemlist");
		
		filterMap.put("checkValues",checkValues);
		filterMap.put("operatorid",(String)session.getAttribute("account"));
		
		List irreList=irregularRestService.register(filterMap);

		
		request.setAttribute("irreList",irreList);
		return mapping.findForward("registerOk");
	}
	public ActionForward searchIrregularInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("searchIrregularInfo");
		
		Map filterMap = WebUtils.getParametersStartingWith(request, "irregular_");
		List irreInfoList=irregularRestService.searchIrregular(filterMap);
        List departmentTree=departmentService.getDepartmentTree(0,null);
		
        request.setAttribute("irregular_startDate",filterMap.get("startDate"));
		request.setAttribute("irregular_endDate",filterMap.get("endDate"));
		request.setAttribute("irregular_trueName",filterMap.get("trueName"));
		request.setAttribute("departmentTree",departmentTree);
		request.setAttribute("irreInfoList",irreInfoList);
		return mapping.findForward("goSearchIrre");
	}
	public ActionForward preUpdate(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
        log.debug("preUpdate");//展现需要修改的信息
		
		Calendar startCal=Calendar.getInstance();
		Calendar endCal=Calendar.getInstance();
		String irregularinfoid=request.getParameter("pre_irregularinfoid");
		String clerkName=request.getParameter("pre_clerkName");
		clerkName=URLDecoder.decode(clerkName,"UTF-8");//字符解码
		
		
		
		Irregularrest irregularrest=irregularRestService.get(irregularinfoid);
		
		startCal.setTime(irregularrest.getStartdate());
		endCal.setTime(irregularrest.getEnddate());
		log.debug("irregularinfoid-------------->"+irregularinfoid);
		
		String new_startDate=DateFormat.getDateInstance().format(irregularrest.getStartdate());
		String new_endDate=DateFormat.getDateInstance().format(irregularrest.getEnddate());
		
		request.setAttribute("irregularrest",irregularrest);
		request.setAttribute("clerkName",clerkName);
		request.setAttribute("new_startDate",new_startDate);
		request.setAttribute("new_endDate",new_endDate);
		request.setAttribute("new_startHour",new Integer(startCal.get(Calendar.HOUR_OF_DAY)));
		request.setAttribute("new_startMin",new Integer(startCal.get(Calendar.MINUTE)));
		request.setAttribute("new_endHour",new Integer(endCal.get(Calendar.HOUR_OF_DAY)));
		request.setAttribute("new_endMin",new Integer(endCal.get(Calendar.MINUTE)));
		
		return mapping.findForward("updateIrre");
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
		
		irregularRestService.updateIrregular(filterMap);
		
		request.setAttribute("msg","修改成功");
		
		return mapping.findForward("goSearchIrre");
	}
	public ActionForward delete(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("delete");
		List departmentTree=departmentService.getDepartmentTree(0,null);
		request.setAttribute("departmentTree",departmentTree);
		
		String irreIds[]=request.getParameterValues("itemlist");
		
		irregularRestService.deleteIrregular(irreIds);
		
		request.setAttribute("msg","成功删除"+irreIds.length+"信息!");
		return mapping.findForward("goSearchIrre");
	}

}
