package org.king.check.web.action;

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
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.king.check.config.CommonConfig;
import org.king.check.domain.Tleaveinfo;
import org.king.check.service.DepartmentService;
import org.king.check.service.LeaveInfoService;
import org.king.check.service.SysService;
import org.king.check.util.DateUtilExtend;
import org.king.framework.web.action.BaseAction;
import org.springframework.web.util.WebUtils;

public class LeaveInfoAction extends BaseAction {
	private static final Log log = LogFactory.getLog(LeaveInfoAction.class);

	private DepartmentService departmentService;

	private LeaveInfoService leaveInfoService;
	 
	private SysService sysService;
	
	public void setDepartmentService(DepartmentService departmentService) {
		this.departmentService = departmentService;
	}

	public void setLeaveInfoService(LeaveInfoService leaveInfoService) {
		this.leaveInfoService = leaveInfoService;
	}

	public void setSysService(SysService sysService) {
		this.sysService = sysService;
	}

	public ActionForward searchLeaveInfo(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		Map filterMap = WebUtils.getParametersStartingWith(request, "leave_");

		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List departmentTree = sysService.getDeptList(accountId);
		List leaveInfoList = leaveInfoService.searchLeaveInfo(filterMap);

		request.setAttribute("departmentTree", departmentTree);
		request.setAttribute("leaveInfoList", leaveInfoList);

		return mapping.findForward("leaveInfoQuery");
	}

	public ActionForward goStatic(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		//List departmentTree = departmentService.getDepartmentTree(0, null);
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List departmentTree = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", departmentTree);

		request.setAttribute("leave_startDate",DateUtilExtend.getNowDate());
		request.setAttribute("leave_endDate",DateUtilExtend.getNowDate());
		return mapping.findForward("leaveInfoQuery");
	}

	public ActionForward staticLeaveInfo(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {

		Map filterMap = WebUtils.getParametersStartingWith(request, "leave_");

		log.debug("Static");

		//List departmentTree = departmentService.getDepartmentTree(0, null);
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List departmentTree = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", departmentTree);

		List staticInfoList = leaveInfoService
				.staticLeaveInfoByFilter(filterMap);
		request.setAttribute("staticInfoList", staticInfoList);

		request.setAttribute("endDate", filterMap.get("endDate"));

		return mapping.findForward("goStatic");
	}

	public ActionForward viewLeaveDetail(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		log.debug("viewDetail");

		String startDate = request.getParameter("startDate");
		String endDate = request.getParameter("endDate");
		Integer clerkId = new Integer(request.getParameter("clerkId"));

		Map filter = new HashMap();
		filter.put(CommonConfig.startDate, startDate);
		filter.put(CommonConfig.endDate, endDate);
		filter.put("clerkId", clerkId);

		List leaveDetailList = leaveInfoService.getLeaveInfoDetail(filter);

		request.setAttribute("leaveDetailList", leaveDetailList);

		return mapping.findForward("viewDetail");
	}

	/**
	 * hanjiwei modify it 20060920
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward delete(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("delete");
		ActionMessages messages = new ActionMessages();
		//List departmentTree = departmentService.getDepartmentTree(0, null);
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List departmentTree = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", departmentTree);

		String[] leaveIds = request.getParameterValues("itemlist");

		leaveInfoService.deleteLeaveInfo(leaveIds);

		String msg= "销假"+String.valueOf(leaveIds.length)+"条记录";
		messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
				"success.delete",msg));
		saveMessages(request, messages);
		
		//request.setAttribute("msg", "成功删除" + leaveIds.length + "条请假信息");

		return mapping.findForward("operOk");
	}

	/**
	 * hanjiwei modify it 20060920
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		ActionMessages messages = new ActionMessages();
		//List departmentTree = departmentService.getDepartmentTree(0, null);
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List departmentTree = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", departmentTree);

		Map filterMap = WebUtils.getParametersStartingWith(request, "new_");
		
		Integer custId = Integer.valueOf((String)filterMap.get("custId"));
		String custName = (String)filterMap.get("clerkName");
		String startTime = DateUtilExtend.formatDate2((String) filterMap.get("startDate"))+(String) filterMap.get("startHour")+ (String) filterMap.get("startMin") + "00";
		String endTime = DateUtilExtend.formatDate2((String) filterMap.get("endDate"))+(String) filterMap.get("endHour")+ (String) filterMap.get("endMin") + "00";

		String msg = leaveInfoService.checkIsLeaveByClerkId(custId,startTime,endTime);
		if (!"".equals(msg)){
			String tipMsg = custName+"请假信息设置有重复，请重新设置！";
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"fail.modify", tipMsg));
			saveMessages(request, messages);
			return mapping.findForward("operOk");
		}
		filterMap.put("operatorid",accountId);

		leaveInfoService.updateLeaveInfo(filterMap);

		//request.setAttribute("msg", "修改成功");
		String tipMsg = custName+"请假修改成功！";
		messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
				"success.modify", tipMsg));
		saveMessages(request, messages);
		return mapping.findForward("operOk");
	}

	/**
	 * hanjiwei modify it 20060920
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward preUpdate(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String leaveInfoId = request.getParameter("pre_leaveinfoId");

		Tleaveinfo leaveinfo = new Tleaveinfo();

		if (leaveInfoId != null)
			leaveinfo = leaveInfoService.getLeaveInfoById(leaveInfoId);
		List typeList = sysService.getLeaveList();
		
		request.setAttribute("leaveType",typeList);
		request.setAttribute("leaveinfo", leaveinfo);
		request.setAttribute("custId",leaveinfo.getCustId());
		request.setAttribute("clerkName",sysService.getCustomerNameByCustomerId(leaveinfo.getCustId()));
		request.setAttribute("new_leaveInfoId",leaveInfoId);
		request.setAttribute("leaveInfoName",sysService.getLeaveTypeName(leaveinfo.getLeaveTypeid()));
		request.setAttribute("new_description",leaveinfo.getLeaveInfo());
		request.setAttribute("new_type",leaveinfo.getLeaveTypeid());
		request.setAttribute("new_startDate", DateUtilExtend.formatDate3(leaveinfo.getStartdate()));
		request.setAttribute("new_endDate", DateUtilExtend.formatDate3(leaveinfo.getEnddate()));
		request.setAttribute("new_startHour", leaveinfo.getStarttime().substring(0,2));
		request.setAttribute("new_startMin", leaveinfo.getStarttime().substring(2,4));
		request.setAttribute("new_endHour", leaveinfo.getEndtime().substring(0,2));
		request.setAttribute("new_endMin", leaveinfo.getEndtime().substring(2,4));

		return mapping.findForward("preupdate");
	}

}
