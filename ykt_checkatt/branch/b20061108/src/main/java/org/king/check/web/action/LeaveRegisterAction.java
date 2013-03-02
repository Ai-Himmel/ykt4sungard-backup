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
import org.king.check.service.DepartmentService;
import org.king.check.service.LeaveInfoService;
import org.king.check.service.SysService;
import org.king.check.util.DateUtilExtend;
import org.king.framework.web.action.BaseAction;
import org.springframework.web.util.WebUtils;

public class LeaveRegisterAction extends BaseAction{
	private static final Log log = LogFactory.getLog(LeaveRegisterAction.class);
	
	private LeaveInfoService leaveInfoService;
	private SysService sysService;
	private DepartmentService departmentService;
	

	public void setLeaveInfoService(LeaveInfoService leaveInfoService) {
		this.leaveInfoService = leaveInfoService;
	}
	
	public void setSysService(SysService sysService) {
		this.sysService = sysService;
	}
	public void setDepartmentService(DepartmentService departmentService) {
		this.departmentService = departmentService;
	}



	public ActionForward goRegister(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("goRegister");
		List departmentTree=departmentService.getDepartmentTree(0,null);
		request.setAttribute("departmentTree",departmentTree);
		request.setAttribute("display","none");
		return mapping.findForward("goRegister");
	}
	public ActionForward search(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
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
		List departmentTree=departmentService.getDepartmentTree(0,null);
		request.setAttribute("departmentTree",departmentTree);
		List leaveType = sysService.getLeaveList();
		request.setAttribute("leavetype",leaveType);
		
		
		return mapping.findForward("searchClerk");
	}
	
	public ActionForward register(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		Map filterMap = WebUtils.getParametersStartingWith(request, "register_");
						
		String checkValues[]=request.getParameterValues("itemlist");
		HttpSession session=request.getSession();
		filterMap.put("operatorid",(String)session.getAttribute("account"));
		filterMap.put("operDate",DateUtilExtend.getNowDate2());
		filterMap.put("operTime",DateUtilExtend.getNowTime());
		filterMap.put("checkValues",checkValues);
	
		String startTime = DateUtilExtend.formatDate2((String) filterMap.get("startDate"))+(String) filterMap.get("startHour")+ (String) filterMap.get("startMin") + "00";
		String endTime = DateUtilExtend.formatDate2((String) filterMap.get("endDate"))+(String) filterMap.get("endHour")+ (String) filterMap.get("endMin") + "00";
		for (int i=0;i<checkValues.length;i++){
			String msg = leaveInfoService.checkIsLeaveByClerkId(Integer.valueOf(checkValues[i]),startTime,endTime);
			if (!"".equals(msg)){
				request.setAttribute("msg","请假时间不能交叉："+msg);
				List departmentTree=departmentService.getDepartmentTree(0,null);
				request.setAttribute("departmentTree",departmentTree);
				request.setAttribute("display","none");
				return mapping.findForward("goRegister");
			}
		}
	
		leaveInfoService.addLeaveInfo(filterMap);
		
		List leaveList = leaveInfoService.getLeaveInfo(checkValues);
		request.setAttribute("leaveList",leaveList);
		
		request.setAttribute("display","none");
		request.setAttribute("msg","请假登记成功！");
		request.setAttribute("url","window.location.href='leaveRegister.do?method=goRegister'");
		return mapping.findForward("success");
	}
}
