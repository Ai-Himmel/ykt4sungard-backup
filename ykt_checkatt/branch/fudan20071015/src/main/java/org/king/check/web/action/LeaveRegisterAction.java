package org.king.check.web.action;

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
				request.setAttribute("msg","���ʱ�䲻�ܽ��棺"+msg);
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
		request.setAttribute("msg","��ٵǼǳɹ���");
		request.setAttribute("url","window.location.href='leaveRegister.do?method=goRegister'");
		return mapping.findForward("success");
	}
	/**
	 * ��λ���������ҳ��
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
		
		//HttpSession session = request.getSession();
		//String  accountId = (String)session.getAttribute("account");
		
		//List deptList = sysService.getDeptList(accountId);
		//request.setAttribute("departList", deptList);
		String endDate = DateUtilExtend.getNowDate();
		String beginDate = DateUtilExtend.formatDate3(DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-7));
		request.setAttribute("beginDate",beginDate);
		request.setAttribute("endDate",endDate);
		return mapping.findForward("goLeaveReportQuery");
	}
	/**
	 * ��ѯ��ǰ�����������Ϣ
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
	 * ��λ���������ҳ��
	 * hanjiwe add it 20061113
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
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
			request.setAttribute("custId",new Integer(sysService.getCustIdByStuempNo((String)session.getAttribute("personCode"))));
			request.setAttribute("repCustId",new Integer(0));
			
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
	 * ������뱣��
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
		String getCustId[] = request.getParameterValues("itemlist");
		HttpSession session = request.getSession();
		int  custId=0;
		int replaceCustId;
		if (request.getParameter("repLeaveSign")!=null){
			replaceCustId = sysService.getCustIdByStuempNo((String)session.getAttribute("personCode"));
			for (int i=0;i<getCustId.length;i++){
				if (("".equals(getCustId[i]))||(getCustId[i]==null)){
					continue;
				}
				custId = Integer.parseInt(getCustId[i]);
			}
		}else{
			replaceCustId = Integer.parseInt(request.getParameter("register_repCustId"));
			custId = Integer.parseInt(request.getParameter("register_custId"));
		}
		Map stuemp = new TreeMap();
		stuemp.put("stuempNo",(String)session.getAttribute("personCode"));
		String loginDeptId = ((Map)sysService.getCustInfo(stuemp).get(0)).get("DEPT_ID").toString();
		
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
		request.setAttribute("msg","������ٳɹ���");
		return mapping.findForward("goLeaveReportQuery");
	}
	/**
	 * ȡ�����
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
			request.setAttribute("msg","�ɹ�ɾ��һ�������Ϣ��");

		}else{
		}
		String endDate = DateUtilExtend.getNowDate();
		String beginDate = DateUtilExtend.formatDate3(DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-7));
		request.setAttribute("beginDate",beginDate);
		request.setAttribute("endDate",endDate);
		return mapping.findForward("goLeaveReportQuery");
	}
	/**
	 * �����ϸ��Ϣ
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
	 * �������������ϸ��Ϣ���
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
	 * �������ȡ��ȷ��
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
	 * ���������������
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
		filterMap.put("operid",operId);
		String leaveReportId = (String)filterMap.get("leaveReportId");
		leaveInfoService.reportLeaveCheck(leaveReportId,filterMap);
		String endDate = DateUtilExtend.getNowDate();
		String beginDate = DateUtilExtend.formatDate3(DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-7));
		request.setAttribute("beginDate",beginDate);
		request.setAttribute("endDate",endDate);
		request.setAttribute("msg","�����Ϣ�����ɹ���");
		return mapping.findForward("goLeaveReportCheck");
	}
	
	/**
	 * �������ȡ����Ϣ����
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
		request.setAttribute("msg","������Ϣȡ���ɹ���");
		return mapping.findForward("goLeaveReportCancelCheck");
	}
	/**
	 * hanjiwei add it 20061115
	 * ����������
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
		request.getSession().setAttribute("beginDate",beginDate);
		request.getSession().setAttribute("endDate",endDate);
		return mapping.findForward("goLeaveReportCheck");
	}
	/**
	 * �������ȡ����ѯ
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
	 * ��λ�������������ҳ��
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
		return mapping.findForward("goLeaveReportCheck");
	}
	
	/**
	 * ��λ�������������ȡ��ҳ��
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
