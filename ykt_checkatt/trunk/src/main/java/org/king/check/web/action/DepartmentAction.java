/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.check.web.action.DepartmentAction.java
 * 创建日期： 2006-6-16 10:55:44
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-6-16 10:55:44      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
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
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.action.DynaActionForm;

import org.king.check.config.ClerkConfig;
import org.king.check.domain.Department;
import org.king.check.domain.Tdeptworkconfinfo;
import org.king.check.domain.TdeptworkconfinfoId;
import org.king.check.service.DepartConfService;
import org.king.check.service.DepartmentService;
import org.king.check.service.SysService;
import org.king.check.service.WorkConfService;
import org.king.check.service.WorkTimeConfService;
import org.king.check.util.DateUtilExtend;
import org.king.framework.exception.BusinessException;
import org.king.framework.web.action.BaseAction;
import org.springframework.web.util.WebUtils;

public class DepartmentAction extends BaseAction {
	private static final Log log = LogFactory.getLog(DepartmentAction.class);

	private DepartmentService departmentService;

	private WorkTimeConfService workTimeConfService;

	private WorkConfService workConfService;

	private DepartConfService departConfService;

	private SysService sysService;
	public void setSysService(SysService sysService) {
		this.sysService = sysService;
	}
	public void setWorkConfService(WorkConfService workConfService) {
		this.workConfService = workConfService;
	}

	public void setWorkTimeConfService(WorkTimeConfService workTimeConfService) {
		this.workTimeConfService = workTimeConfService;
	}

	public void setDepartmentService(DepartmentService departmentService) {
		this.departmentService = departmentService;
	}

	public void setDepartConfService(DepartConfService departConfService) {
		this.departConfService = departConfService;
	}

	public ActionForward load4add(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		DynaActionForm departmentForm = (DynaActionForm) form;
		Department dept = new Department();
		String pid = (String) request.getParameter("pid");
		if (pid != null) {
			Department entity = departmentService.getDepartment(pid);
			dept.setParent(entity);
		}

		departmentForm.set("department", dept);
		departmentForm.set("methodToCall", "add");

		saveToken(request);

		return (mapping.findForward("input"));
	}

	/**
	 * 
	 * 创建部门
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 */
	public ActionForward create(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		ActionMessages errors = new ActionMessages();
		// Was this transaction cancelled?
		if (isCancelled(request)) {
			removeAttribute(mapping, request);

			return (mapping.findForward("cancel"));
		}

		// check token
		if (!isTokenValid(request)) {
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"errors.TokenError"));
			resetToken(request);
			saveErrors(request, errors);

			return (mapping.getInputForward());
		}

		Department department = (Department) ((DynaActionForm) form)
				.get("department");
		department.setId(null);

		try {
			departmentService.saveDepartment(department);
		} catch (BusinessException be) {
			errors.add("create error", new ActionMessage("errors.UnKnowError"));
		}

		if (!errors.isEmpty()) {
			saveErrors(request, errors);
			saveToken(request);

			return (mapping.getInputForward());
		} else {
			// Remove the obsolete form bean
			removeAttribute(mapping, request);

			return (mapping.findForward("success"));
		}
	}

	/**
	 * 装载为了修改
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 */
	public final ActionForward load4edit(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {

		DynaActionForm departmentForm = (DynaActionForm) form;
		String deptId = (String) request.getParameter("id");
		Department dept = null;
		if (deptId != null) {
			dept = departmentService.getDepartment(deptId);
		}

		departmentForm.set("department", dept);
		departmentForm.set("methodToCall", "edit");

		saveToken(request);
		return (mapping.findForward("edit"));
	}

	public final ActionForward update(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		ActionMessages errors = new ActionMessages();
		Department department = (Department) ((DynaActionForm) form)
				.get("department");

		try {
			departmentService.updateDepartment(department);
		} catch (BusinessException e) {
			errors.add("update error", new ActionMessage("errors.UnKnowError"));
		}

		if (!errors.isEmpty()) {
			saveErrors(request, errors);
			saveToken(request);

			return (mapping.getInputForward());
		} else {
			// Remove the obsolete form bean
			removeAttribute(mapping, request);

			return (mapping.findForward("success"));
		}
	}

	/**
	 * 删除目录
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 */
	public final ActionForward remove(final ActionMapping mapping,
			final ActionForm form, final HttpServletRequest request,
			final HttpServletResponse response) throws Exception {
		ActionMessages errors = new ActionMessages();
		ActionMessages messages = new ActionMessages();
		String id = request.getParameter("id");
		if (id == null) {
			errors.add("remove error", new ActionMessage("errors.UnKnowError"));
		}
		try {
			departmentService.deleteDepartment(id);
		} catch (BusinessException be) {
			errors.add("remove error", new ActionMessage("errors.UnKnowError"));
		}

		if (!errors.isEmpty()) {
			saveErrors(request, errors);
			saveToken(request);
			return (mapping.getInputForward());
		}

		messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
				"success.delete", "1"));

		saveMessages(request, messages);
		// Remove the obsolete form bean
		removeAttribute(mapping, request);

		return (mapping.findForward("success"));
	}

	/**
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward getDepartmentXMLTree(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'getXMLMenu' method");
		}

		String deptTree = departmentService.getDepartmentXmlTree();

		request.setAttribute("menuTree", deptTree);

		return mapping.findForward("success");
	}

	/**
	 * 载入部门列表
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward load4list(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		return mapping.findForward("list");
	}

	/**
	 * 取消
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward cancel(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		return mapping.findForward("success");
	}

	/**
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward loadDepartmentTree(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {

		return mapping.findForward("selectTree");
	}

	/**
	 * hanjiwei modify it 20061009
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward goDeptConf(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String getNowDate = DateUtilExtend.getNowDate();
		String getDateBefore = DateUtilExtend.formatDate3(DateUtilExtend.addDate2(DateUtilExtend.formatDate2(getNowDate),30));
		//List departmentTree = departmentService.getDepartmentTree(0, null);
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List departmentTree = sysService.getDeptList(accountId);
		request.setAttribute("startDate",getNowDate);
		request.setAttribute("endDate",getDateBefore);
		request.setAttribute("departmentTree", departmentTree);
		return mapping.findForward("goDeptConf");
	}

	/*
	 * 添加部门设置选择部门
	 */
	public ActionForward addConfSltDpt(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		request.getSession().removeAttribute("dptConfList");
		request.getSession().removeAttribute("new_department");
		request.getSession().removeAttribute("dptName");
		request.getSession().removeAttribute("dptConfList");
		return mapping.findForward("addConfSltDpt");
	}

	/*
	 * hanjiwei modify it 20061011
	 * 进行参数设置
	 */
	public ActionForward addConfStep1(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		//List departmentTree = departmentService.getDepartmentTree(0, null);
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List departmentTree = sysService.getDeptList(accountId);

		request.setAttribute("departmentTree", departmentTree);

		List workConfList = workConfService.getAll();
		List workTimeConfList = workTimeConfService.getAll();
		request.getSession().setAttribute("workConfList", workConfList);
		request.getSession().setAttribute("workTimeConfList", workTimeConfList);
		request.setAttribute("display", "block");

		return mapping.findForward("addConfStep1");
	}
	
	/*
	 * 取得部门排班详细信息
	 * hanjiwei add it 20061009
	 */
	public ActionForward getDeptConfDetail(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String deptId = request.getParameter("pre_deptId").toString();
		String confDate = request.getParameter("pre_beginDate").toString();
		Map getConfAndTimeId = departConfService.getConfAndTimeId(deptId,confDate);
		String deptName = getConfAndTimeId.get("DEPT_NAME").toString();
		String workConfId = getConfAndTimeId.get("WORKINFO_ID").toString();
		String timeConfId = getConfAndTimeId.get("WORKTIME_ID").toString();
		String ifWork = getConfAndTimeId.get("IFWORK").toString();
		String workConfDetail = workConfService.getWorkConfInfo(workConfId);
		String workTimeDetail = workTimeConfService.getWorkTimeInfo(timeConfId);
		request.setAttribute("ifWORK",ifWork);
		request.setAttribute("workConfDetail",workConfDetail);
		request.setAttribute("workTimeDetail",workTimeDetail);
		request.setAttribute("deptName",deptName);
		request.setAttribute("confDate",confDate);
		return mapping.findForward("goDeptConfDetail");
	}
	/*
	 * 修改部门排班信息
	 * hanjiwei add it 20061009
	 */
	public ActionForward modifyDeptConf(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String deptId = request.getParameter("pre_deptId").toString();
		String confDate = request.getParameter("pre_beginDate");
		Map getConfAndTimeId = departConfService.getConfAndTimeId(deptId,confDate);
		String deptName = getConfAndTimeId.get("DEPT_NAME").toString();
		String workConfId = getConfAndTimeId.get("WORKINFO_ID").toString();
		String timeConfId = getConfAndTimeId.get("WORKTIME_ID").toString();
		String ifWork = getConfAndTimeId.get("IFWORK").toString();
		String workConfDetail = workConfService.getWorkConfInfo(workConfId);
		String workTimeDetail = workTimeConfService.getWorkTimeInfo(timeConfId);
		request.setAttribute("ifWORK",ifWork);
		request.setAttribute("workConfDetail",workConfDetail);
		request.setAttribute("workTimeDetail",workTimeDetail);
		request.setAttribute("workConfId",workConfId);
		request.setAttribute("timeConfId",timeConfId);
		request.setAttribute("deptName",deptName);
		request.setAttribute("confDate",confDate);
		return mapping.findForward("goDeptConfModify");
	}
	

	/*
	 * hanjiwei modify it 20061011
	 * 得到制度信息
	 */
	public ActionForward getConfDetail(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String workConfId = request.getParameter("new_clerkRule");// 添加工作制度细节
		if (StringUtils.isNotEmpty(workConfId)) {
			String workConfDetail = workConfService.getWorkConfInfo(workConfId);
			request.setAttribute("workconfDetail", workConfDetail);
		}

		String timeConfId = request.getParameter("new_cherkTimeRule");// 添加工作时间细节
		if (StringUtils.isNotEmpty(timeConfId)) {
			String workTimeDetail = workTimeConfService.getWorkTimeInfo(timeConfId);
			request.setAttribute("timeDetail", workTimeDetail);
		}

		List workConfList = workConfService.getAll();
		List workTimeConfList = workTimeConfService.getAll();
		//List departmentTree = departmentService.getDepartmentTree(0, null);
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List departmentTree = sysService.getDeptList(accountId);

		request.setAttribute("workConfList", workConfList);
		request.setAttribute("workTimeConfList", workTimeConfList);
		request.setAttribute("departmentTree", departmentTree);

		return mapping.findForward("addConfStep1");
	}

	/*
	 * hanjiwei modify it 20061011
	 * 添加考勤制度
	 */
	public ActionForward addConf(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		Map filterMap = WebUtils.getParametersStartingWith(request, "new_");
		String startDate = DateUtilExtend.formatDate2((String) filterMap.get("startDate"));
		String endDate = DateUtilExtend.formatDate2((String) filterMap.get("endDate"));
		String deptId = (String)filterMap.get("deptId");
		String ifWork = "";
		if (null==filterMap.get("ifWork")){
			ifWork = "0";
		}else{
			ifWork = (String) filterMap.get("ifWork");
		}
		//判断是否已经存在已分配过的考勤制度，如果存在则修改，否则添加
		long diffDate = DateUtilExtend.diffDate(startDate,endDate);
		for (long diffDay = 0;diffDay<=diffDate;diffDay++){
			String workDate = DateUtilExtend.addDate2(startDate,(int)diffDay);
			TdeptworkconfinfoId id = new TdeptworkconfinfoId();
			id.setBegindate(workDate);
			id.setDeptId(deptId);
			Tdeptworkconfinfo deptConfInfo = new Tdeptworkconfinfo();
			deptConfInfo.setId(id);
			deptConfInfo.setIfwork(ifWork);
			deptConfInfo.setWorkinfoId((String) filterMap.get("clerkRule"));
			deptConfInfo.setWorktimeId((String) filterMap.get("cherkTimeRule"));
			if (departConfService.ifExistDeptConf(deptId,workDate)){
				departConfService.update(deptConfInfo);
			}else{
				departConfService.save(deptConfInfo);
			}
		}

		String msg = "设置成功,您可以继续设置";
		String buttonInfo = "继续设置";
		String actionUrl = "window.location.href='department.do?method=addConfStep1';";// 动作信息
		request.setAttribute("btnInfo", buttonInfo);// 按钮信息
		request.setAttribute("actionUrl", actionUrl);
		request.setAttribute("msg", msg);// 提示信息
		request.setAttribute("startDate", startDate);
		request.setAttribute("deptName",sysService.getDeptName(deptId));
		request.setAttribute("endDate", endDate);
		request.setAttribute("display", "none");
		request.setAttribute("timeDetail", (String) filterMap.get("timeDetail"));
		request.setAttribute("workconfDetail", (String) filterMap.get("workconfDetail"));
		if (ifWork.equals(Integer.toString(ClerkConfig.isSeat))) {
			request.setAttribute("ifWork", "上班");
		} else {
			request.setAttribute("ifWork", "不上班");
		}

		return mapping.findForward("finish");
	}

	/**
	 * hanjiwei modify it 20061009
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward search(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		Map filterMap = WebUtils.getParametersStartingWith(request, "search_");
		List dptConfList = departConfService.search(filterMap);
		//List departmentTree = departmentService.getDepartmentTree(0, null);
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List departmentTree = sysService.getDeptList(accountId);

		request.setAttribute("departmentTree", departmentTree);
		request.setAttribute("dpConfList", dptConfList);
		request.setAttribute("startDate", (String) filterMap.get("startDate"));
		request.setAttribute("endDate", (String) filterMap.get("endDate"));
		return mapping.findForward("goDeptConf");
	}

}
