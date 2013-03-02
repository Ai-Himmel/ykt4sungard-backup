package org.king.check.web.action;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.check.domain.Treportleave;
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


	/**
	 * hanjiwei modify it 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward goRegister(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		log.debug("goRegister");
		//List departmentTree=departmentService.getDepartmentTree(0,null);
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List departmentTree = sysService.getDeptList(accountId);
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
		//考勤类别列表
		List checkattList = sysService.getCheckattType();
		request.setAttribute("checkattList",checkattList);
		
		
		return mapping.findForward("searchClerk");
	}
	
	/**
	 * hanjiwei modify it 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
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
	/**
	 * 定位到请假申请页面
	 * hanjiwe modify it 20061113
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward goLeaveReportQuery(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		String endDate = DateUtilExtend.getNowDate();
		String beginDate = DateUtilExtend.formatDate3(DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-7));
		request.setAttribute("beginDate",beginDate);
		request.setAttribute("endDate",endDate);
		
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("personCode");
		
		int custId = sysService.getCustIdByStuempNo(accountId);
		Map filterMap = new HashMap();
		filterMap.put("custId",new Integer(custId));
		filterMap.put("sDate",beginDate);
		filterMap.put("eDate",endDate);
		filterMap.put("ifcheck","-1");
		filterMap.put("ifagree","-1");
		List leaveReportList = leaveInfoService.getLeaveQuery(filterMap);
		request.setAttribute("leaveReportList",leaveReportList);

		return mapping.findForward("goLeaveReportQuery");
	}
	/**
	 * 查询以前的请假申请信息
	 * hanjiwe add it 20061113
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward queryLeaveReport(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		Map filterMap = WebUtils.getParametersStartingWith(request, "query_");
		String beginDate = (String)filterMap.get("sDate");
		String endDate = (String)filterMap.get("eDate");
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("personCode");
		
		//List deptList = sysService.getDeptList(accountId);
		//request.setAttribute("departList", deptList);
		int custId = sysService.getCustIdByStuempNo(accountId);
		filterMap.put("custId",new Integer(custId));
		List leaveReportList = leaveInfoService.getLeaveQuery(filterMap);
		request.setAttribute("leaveReportList",leaveReportList);
		request.setAttribute("beginDate",beginDate);
		request.setAttribute("endDate",endDate);
		return mapping.findForward("goLeaveReportQuery");
	}
	
	/**
	 * 定位到请假申请页面
	 * hanjiwe add it 20061113
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 * 
	 */
	public ActionForward goLeaveReport(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String leaveReportId = request.getParameter("leaveReportId");
		HttpSession session = request.getSession();
		//Map custInfo = sysService.getCustInfoByCustId();
		if (("".equals(leaveReportId))||(null==leaveReportId)){
			String currentDate = DateUtilExtend.getNowDate();
			request.setAttribute("beginDate",currentDate);
			request.setAttribute("endDate",currentDate);
			List leaveType = sysService.getLeaveList();
			request.setAttribute("leavetype",leaveType);
			request.setAttribute("beginHour","00");
			request.setAttribute("beginMin","00");
			request.setAttribute("endHour","00");
			request.setAttribute("endMin","00");
			int custId = sysService.getCustIdByStuempNo((String)session.getAttribute("personCode"));
			request.setAttribute("custId",new Integer(custId));
			request.setAttribute("repCustId",new Integer(0));
			Map custInfo = sysService.getCustInfoByCustId(custId);
			if (null==custInfo){
				request.setAttribute("custName","");
			}else{
				request.setAttribute("custName",custInfo.get("CUT_NAME"));
			}
			
		}else{
			Treportleave reportLeave = leaveInfoService.getReportLeaveInfo(leaveReportId);
			String beginTime = reportLeave.getLeaveBegintime();
			String endTime = reportLeave.getLeaveEndtime();
			request.setAttribute("beginDate",DateUtilExtend.formatDate3(reportLeave.getLeaveBegindate()));
			request.setAttribute("endDate",DateUtilExtend.formatDate3(reportLeave.getLeaveEnddate()));
			request.setAttribute("leaveInfo",reportLeave.getLeaveInfo());
			request.setAttribute("leaveTypeId",reportLeave.getLeaveId());
			request.setAttribute("beginHour",DateUtilExtend.getHour(beginTime));
			request.setAttribute("beginMin",DateUtilExtend.getMin(beginTime));
			request.setAttribute("endHour",DateUtilExtend.getHour(endTime));
			request.setAttribute("endMin",DateUtilExtend.getMin(endTime));
			request.setAttribute("leaveReportId",leaveReportId);
			int repLeaveId = Integer.parseInt(reportLeave.getRepcustid().toString());
			if (repLeaveId > 0){
				request.setAttribute("repCustName",sysService.getCustInfoByCustId(repLeaveId).get("CUT_NAME"));
			}else{
				request.setAttribute("repCustName","");
			}
			
			request.setAttribute("custName",sysService.getCustInfoByCustId(Integer.parseInt(reportLeave.getCustId().toString())).get("CUT_NAME"));
			request.setAttribute("repCustId",reportLeave.getRepcustid());
			request.setAttribute("custId",reportLeave.getCustId());
			List leaveType = sysService.getLeaveList();
			request.setAttribute("leavetype",leaveType);
		}
		return mapping.findForward("leaveReport");
	}
	
	public ActionForward goReplaceLeaveReport(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String currentDate = DateUtilExtend.getNowDate();
		request.setAttribute("beginDate",currentDate);
		request.setAttribute("endDate",currentDate);
		List leaveType = sysService.getLeaveList();
		request.setAttribute("leavetype",leaveType);
		request.setAttribute("beginHour","00");
		request.setAttribute("beginMin","00");
		request.setAttribute("endHour","00");
		request.setAttribute("endMin","00");
		
		return mapping.findForward("replaceReportLeave");
	}
	
	/**
	 * 请假申请保存
	 * hanjiwe add it 20061113
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward leaveReport(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		//ActionMessages messages = new ActionMessages();
		String leaveReportId = request.getParameter("leaveReportId");
		String getCustId = request.getParameter("itemlist");
		HttpSession session = request.getSession();
		int  custId=0;
		int replaceCustId;
		if (request.getParameter("repLeaveSign")!=null){
			replaceCustId = sysService.getCustIdByStuempNo((String)session.getAttribute("personCode"));
			/*
			for (int i=0;i<getCustId.length;i++){
				if (("".equals(getCustId[i]))||(getCustId[i]==null)){
					continue;
				}
				custId = Integer.parseInt(getCustId);
			}*/
			custId = Integer.parseInt(getCustId);
		}else{
			replaceCustId = Integer.parseInt(request.getParameter("register_repCustId"));
			custId = Integer.parseInt(request.getParameter("register_custId"));
		}
		Map stuemp = new TreeMap();
		stuemp.put("stuempNo",(String)session.getAttribute("personCode"));
		String loginDeptId = "";
		if (((Map)sysService.getCustInfo(stuemp).get(0)).get("DEPT_ID")!=null){
			loginDeptId = ((Map)sysService.getCustInfo(stuemp).get(0)).get("DEPT_ID").toString();
		}
		
		
		//String personDeptId = (String)session.getAttribute("personDeptId");
		Map filterMap = WebUtils.getParametersStartingWith(request, "register_");
		
		filterMap.put("custId",new Integer(custId));
		filterMap.put("deptId",loginDeptId);
		filterMap.put("reportLeaveId",leaveReportId);
		filterMap.put("repCustId",new Integer(replaceCustId));
		leaveInfoService.saveLeaveReport(filterMap);	
		String endDate = DateUtilExtend.getNowDate();
		String beginDate = DateUtilExtend.formatDate3(DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-7));
		request.setAttribute("beginDate",beginDate);
		request.setAttribute("endDate",endDate);
		request.setAttribute("msg","申请请假成功！");
		
		String  accountId = (String)session.getAttribute("personCode");
		int custIds = sysService.getCustIdByStuempNo(accountId);
		Map filterMaps = new HashMap();
		filterMaps.put("custId",new Integer(custIds));
		filterMaps.put("sDate",beginDate);
		filterMaps.put("eDate",endDate);
		filterMaps.put("ifcheck","-1");
		filterMaps.put("ifagree","-1");
		List leaveReportList = leaveInfoService.getLeaveQuery(filterMaps);
		request.setAttribute("leaveReportList",leaveReportList);

		return mapping.findForward("goLeaveReportQuery");
	}
	/**
	 * 取消请假
	 * hanjiwei modify it 20061115
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward deleteLeaveReport(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String leaveIds = request.getParameter("leaveId");
		if (!"".equals(leaveIds)){
			leaveInfoService.deleteLeaveReport(leaveIds);
			request.setAttribute("msg","成功删除一条请假信息！");

		}else{
		}
		String endDate = DateUtilExtend.getNowDate();
		String beginDate = DateUtilExtend.formatDate3(DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-7));
		request.setAttribute("beginDate",beginDate);
		request.setAttribute("endDate",endDate);
		return mapping.findForward("goLeaveReportQuery");
	}
	/**
	 * 请假详细信息
	 * hanjiwei modify it 20061115
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward leaveReportDetailInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String leaveReportId = request.getParameter("leaveReportId");
		request.setAttribute("leaveReportDetail",leaveInfoService.getReportLeaveDetailInfo(leaveReportId));
		
		return mapping.findForward("leaveReportDetail");
	}
	/**
	 * 请假申请审批详细信息浏览
	 * hanjiwei modify it 20061115
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward leaveReportCheck(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String leaveReportId = request.getParameter("leaveReportId");
		request.setAttribute("leaveReportCheck",leaveInfoService.getReportLeaveDetailInfo(leaveReportId));
		request.setAttribute("leaveReportId",leaveReportId);
		
		return mapping.findForward("leaveReportCheck");
	}
	
	/**
	 * 请假申请取消确认
	 * hanjiwei add it 20070510
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward leaveReportCheckCancel(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String leaveReportId = request.getParameter("leaveReportId");
		request.setAttribute("leaveReportCheck",leaveInfoService.getReportLeaveDetailInfo(leaveReportId));
		request.setAttribute("leaveReportId",leaveReportId);
		
		return mapping.findForward("leaveReportCheckCancel");
	}
	
	/**
	 * 请假申请审批保存
	 * hanjiwei modify it 20061115
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward saveLeaveReportCheck(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		Map filterMap = WebUtils.getParametersStartingWith(request, "check_");
		HttpSession session = request.getSession();
		String  operId = (String)session.getAttribute("account");
		/**
		if ((sysService.getReportRecord(deptId,checkDate.substring(0,6))>0)||
				(sysService.getReportRecord("0",checkDate.substring(0,6))>0)){
			//提示不能手工签到
			String msg = "该月已经生成考勤报表,不能手工考勤";
			request.setAttribute("msg", msg);
			return mapping.findForward("goMenualModify");
		}else{
			
		}**/
		filterMap.put("operid",operId);
		String leaveReportId = (String)filterMap.get("leaveReportId");
		String leaveReportName = (String)filterMap.get("leaveReportName");
		leaveInfoService.reportLeaveCheck(leaveReportId,filterMap);
		String endDate = DateUtilExtend.getNowDate();
		String beginDate = DateUtilExtend.formatDate3(DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-7));
		request.setAttribute("beginDate",beginDate);
		request.setAttribute("endDate",endDate);
		request.setAttribute("msg","姓名："+leaveReportName+"--请假信息审批成功！");
		
		Map tempMap=new HashMap();
		tempMap.put("operId",operId);
		tempMap.put("eDate",endDate);
		tempMap.put("sDate",beginDate);
		tempMap.put("ifcheck","-1");
		tempMap.put("ifagree","-1");
		List leaveReportList = leaveInfoService.getLeaveCheckQuery(tempMap);
		request.setAttribute("leaveReportList",leaveReportList);

		return mapping.findForward("goLeaveReportCheck");
	}
	
	/**
	 * 请假申请取消信息保存
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward saveLeaveReportCheckCancel(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		Map filterMap = WebUtils.getParametersStartingWith(request, "check_");
		HttpSession session = request.getSession();
		String  operId = (String)session.getAttribute("account");
		filterMap.put("operid",operId);
		String leaveReportId = (String)filterMap.get("leaveReportId");
		leaveInfoService.reportLeaveCheckCancel(leaveReportId,filterMap);
		String endDate = DateUtilExtend.getNowDate();
		String beginDate = DateUtilExtend.formatDate3(DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-7));
		request.setAttribute("beginDate",beginDate);
		request.setAttribute("endDate",endDate);
		request.setAttribute("msg","审批信息取消成功！");
		return mapping.findForward("goLeaveReportCancelCheck");
	}
	/**
	 * hanjiwei add it 20061115
	 * 请假审批浏览
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward leaveReportCheckQuery(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		Map filterMap = WebUtils.getParametersStartingWith(request, "query_");
		String beginDate = (String)filterMap.get("sDate");
		String endDate = (String)filterMap.get("eDate");
		HttpSession session = request.getSession();
		String  operId = (String)session.getAttribute("account");
		
		filterMap.put("operId",operId);
		List leaveReportList = leaveInfoService.getLeaveCheckQuery(filterMap);
		request.setAttribute("leaveReportList",leaveReportList);
		request.setAttribute("beginDate",beginDate);
		request.setAttribute("endDate",endDate);
		return mapping.findForward("goLeaveReportCheck");
	}
	/**
	 * 请假申请取消查询
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward leaveReportCheckCancelQuery(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		Map filterMap = WebUtils.getParametersStartingWith(request, "query_");
		String beginDate = (String)filterMap.get("sDate");
		String endDate = (String)filterMap.get("eDate");
		HttpSession session = request.getSession();
		String  operId = (String)session.getAttribute("account");
		
		filterMap.put("operId",operId);
		List leaveReportList = leaveInfoService.getLeaveCheckQuery(filterMap);
		request.setAttribute("leaveReportList",leaveReportList);
		request.setAttribute("beginDate",beginDate);
		request.setAttribute("endDate",endDate);
		return mapping.findForward("goLeaveReportCancelCheck");
	}

	/**
	 * 定位到请假申请审批页面
	 * hanjiwei add it 20061115
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward goLeaveReportCheckQuery(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String endDate = DateUtilExtend.getNowDate();
		String beginDate = DateUtilExtend.formatDate3(DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-7));
		request.setAttribute("beginDate",beginDate);
		request.setAttribute("endDate",endDate);
		
		HttpSession session = request.getSession();
		String  operId = (String)session.getAttribute("account");
		Map filterMap=new HashMap();
		filterMap.put("operId",operId);
		filterMap.put("eDate",endDate);
		filterMap.put("sDate",beginDate);
		filterMap.put("ifcheck","-1");
		filterMap.put("ifagree","-1");
		List leaveReportList = leaveInfoService.getLeaveCheckQuery(filterMap);
		request.setAttribute("leaveReportList",leaveReportList);

		return mapping.findForward("goLeaveReportCheck");
	}
	
	/**
	 * 定位到请假申请审批取消页面
	 * hanjiwei add it 20070510
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward goLeaveReportCheckCancelQuery(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String endDate = DateUtilExtend.getNowDate();
		String beginDate = DateUtilExtend.formatDate3(DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-7));
		request.setAttribute("beginDate",beginDate);
		request.setAttribute("endDate",endDate);
		return mapping.findForward("goLeaveReportCancelCheck");
	}
}
