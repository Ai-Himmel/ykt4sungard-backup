package org.king.check.web.action;

import java.util.ArrayList;
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
import org.king.check.domain.Tattserialrecord;
import org.king.check.service.DutyTimeService;
import org.king.check.service.LeaveInfoService;
import org.king.check.service.SysService;
import org.king.check.service.WorkInfoService;
import org.king.check.util.CreateWorkInfoThread;
import org.king.check.util.DateUtilExtend;
import org.king.framework.web.action.BaseAction;
import org.springframework.web.util.WebUtils;

public class WorkInfoAction extends BaseAction {

	private static final Log log = LogFactory.getLog(WorkInfoAction.class);

	private DutyTimeService dutyTimeService;

	private WorkInfoService workInfoService;

	private LeaveInfoService leaveInfoService;

	public void setLeaveInfoService(LeaveInfoService leaveInfoService) {
		this.leaveInfoService = leaveInfoService;
	}
	private SysService sysService;

	private static CreateWorkInfoThread createWorkInfoThread;// 开启生成考勤数据的线程

	public void setDutyTimeService(DutyTimeService dutyTimeService) {
		this.dutyTimeService = dutyTimeService;
	}

	public void setWorkInfoService(WorkInfoService workInfoService) {
		this.workInfoService = workInfoService;
	}

	public void setSysService(SysService sysService) {
		this.sysService = sysService;
	}

	/*
	public ActionForward searchNoSeatWorkInfo(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		return mapping.findForward("success");
	}

	public ActionForward noSeatWorkInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		DynaActionForm noSeatParaForm = (DynaActionForm) form;
		if (!StringUtils.isNotEmpty((String) noSeatParaForm
				.get(CommonConfig.startDate)))
			log.debug("test out ");
		List noSeatWorkInfoList = new ArrayList();
		request.getSession().setAttribute("noSeatWorkInfoList",
				noSeatWorkInfoList);
		return mapping.findForward("success");
	}
	
	public ActionForward dealWithNoSeatClerkInfo(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {

		// workInfoService.dealWithNoSeatClerk();
		return mapping.findForward("success");
	}
	*/
	/**
	 * hanjiwei save it 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward getNewFormatDutyTimeInfo(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {

		//Map filterMap = WebUtils.getParametersStartingWith(request, "dutyInfo_");
		
		HashMap filterMap=new HashMap();
		
		String startDate = (String)request.getParameter("dutyInfo_startDate");
		String endDate = (String)request.getParameter("dutyInfo_endDate");
		String deptId=(String)request.getParameter("dutyInfo_deptId");
		
		//资料引用:http://www.knowsky.com/371535.html
		//String startDate = (String)filterMap.get("startDate");
    	//String endDate = (String) filterMap.get("endDate");
		
		request.setAttribute(CommonConfig.startDate, startDate);
		request.setAttribute(CommonConfig.endDate, endDate);
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		request.setAttribute("accountId",accountId);
		
		filterMap.put("startDate",startDate);
		filterMap.put("endDate",endDate);	
		filterMap.put("deptId",deptId);		
		filterMap.put("accountId",accountId);		
				
		List departmentTree = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", departmentTree);
		request.setAttribute("admin",new Integer(1));
		
		String fmtStartDate = DateUtilExtend.formatDate2(startDate);
		String fmtEndDate = DateUtilExtend.formatDate2(endDate);
		
		List ss = sysService.getWeekByDate(fmtStartDate,fmtEndDate);
		request.setAttribute("ss",ss);
		
		request.setAttribute("dayNum",Integer.valueOf(String.valueOf(DateUtilExtend.diffDate(fmtStartDate,fmtEndDate)+1)));
		request.setAttribute("dateRange",fmtStartDate+"--"+fmtEndDate);
		
	/*	request.setAttribute("startDate", startDate);
		request.setAttribute("endDate", endDate);*/
		request.setAttribute("deptId", deptId);
		

		/*
		String msg = "";
		String beginDate = DateUtilExtend.formatDate2((String) filterMap.get(CommonConfig.startDate));
		String endDate = DateUtilExtend.formatDate2((String) filterMap.get(CommonConfig.endDate));
		if (DateUtilExtend.diffDate(beginDate,endDate)>6){
			msg = "请按照7天为时间段进行查询！";
		}
		if (!"".equals(msg)) {
			request.setAttribute("msg", msg);
			return mapping.findForward("newformat");
		}
		*/

		/*hanjiwei delete it 20071228
		Map newFormatM = dutyTimeService.searchForNewFormat(filterMap);
		request.setAttribute("newFormatL", (List) newFormatM.get(CommonConfig.dutyStrs));
		request.setAttribute("titleStr", (String) newFormatM.get(CommonConfig.titleStr));
		*/
		
		List noSeatList = dutyTimeService.getNoSeatList(filterMap);
		request.setAttribute("noSeatList",noSeatList);
		
		int deptCount = sysService.getDeptCount();
		int deptCountByLogin = sysService.getDeptByLogin(accountId);
		
		if (deptCount==deptCountByLogin){
			request.setAttribute("admin",new Integer(1));
		}else{
			request.setAttribute("admin",new Integer(0));
		}
		
		filterMap.clear();
		
		return mapping.findForward("newformat");
	}

	/**
	 * hajiwei save it 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward goNewFormat(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String startDate, endDate;
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List departmentTree = sysService.getDeptList(accountId);
		log.info("------------departmentTree------------"+departmentTree.size());
		endDate = DateUtilExtend.getNowDate();
		startDate = DateUtilExtend.formatDate3(DateUtilExtend.addDate2(DateUtilExtend.formatDate2(endDate),-6));
		
		String fmtStartDate = DateUtilExtend.formatDate2(startDate);
		String fmtEndDate = DateUtilExtend.formatDate2(endDate);
		List ss = sysService.getWeekByDate(fmtStartDate,fmtEndDate);
		request.setAttribute("ss",ss);
		
		request.setAttribute("dayNum",Integer.valueOf(String.valueOf(DateUtilExtend.diffDate(fmtStartDate,fmtEndDate)+1)));
		/*hanjiwei delete it 20071228
		String titleStr = "<td width='100' align='center'  bgcolor='#A8D1E6'>部门</td>  <td><table border='1'  cellpadding='1'"
				+ "  cellspacing='2' > <tr>";
		titleStr += "<td  width='50' align='center' class='tdHeader1'>姓名</td>";
		titleStr += "<td width='95' class='tableHeader6' align='center'>"
				+ startDate + "</td>";
		titleStr += "<td width='95' class='tableHeader6' align='center'>"
				+ endDate + "</td>";
		titleStr += "</tr></table></td>";

		request.setAttribute("titleStr", titleStr);
		*/
		request.setAttribute(CommonConfig.startDate, startDate);
		request.setAttribute(CommonConfig.endDate, endDate);
		request.setAttribute("dateRange",fmtStartDate+"--"+fmtEndDate);
		request.setAttribute("departmentTree", departmentTree);
		
		int deptCount = sysService.getDeptCount();
		int deptCountByLogin = sysService.getDeptByLogin(accountId);
		if (deptCount==deptCountByLogin){
			request.setAttribute("admin",new Integer(1));
		}else{
			request.setAttribute("admin",new Integer(0));
		}

		return mapping.findForward("gonewformat");
	}
	
	/**
	 * hanjiwei add it 20061204
	 * 取得请假详细信息
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward goLeaveDetailInfo(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		String leaveReportId = request.getParameter("leaveReportId");
		request.setAttribute("leaveReportDetail",leaveInfoService.getReportLeaveDetailInfo(leaveReportId));
		
		return mapping.findForward("leaveDetail");
	}
	public ActionForward goManualDetailInfo(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		String custId = request.getParameter("custId");
		String clerkDate = request.getParameter("clerkDate");
		String maxTime = request.getParameter("maxTime");
		String minTime = request.getParameter("minTime");
		request.setAttribute("leaveReportDetail",leaveInfoService.getManualDetailInfo(custId,clerkDate,maxTime,minTime));
		
		return mapping.findForward("manualDetail");
	}


	/**
	 * hanjiwei modify it 20060910
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward goMenualRegister(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);
		//考勤类别列表
		List checkattList = sysService.getCheckattType();
		request.setAttribute("checkattList",checkattList);

		return mapping.findForward("goMenualRegister");
	}

	/**
	 * hanjiwei modify it 20060910
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward searchClerk(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		//List departmentTree = departmentService.getDepartmentTree(0, null);
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		String stuempName = request.getParameter("register_trueName");
		String stuempNo = request.getParameter("register_stuNumber");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);
		//考勤类别列表
		List checkattList = sysService.getCheckattType();
		request.setAttribute("checkattList",checkattList);

		Map filterMap = WebUtils.getParametersStartingWith(request, "register_");
		filterMap.put("accountId",accountId);
		List clerkList = workInfoService.searchClerkForReg(filterMap);

		if (!clerkList.isEmpty()) {
			request.setAttribute("show", "block");
		}
		request.setAttribute("checkDate",DateUtilExtend.getNowDate());
		request.setAttribute("clerkList", clerkList);
		request.setAttribute("stuempName",stuempName);
		request.setAttribute("stuempNo",stuempNo);

		return mapping.findForward("goMenualRegister");
	}
	
	/**
	 * 查找要代替请假的人员列表
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward searchClerkForReplace(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		//List departmentTree = departmentService.getDepartmentTree(0, null);
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);

		Map filterMap = WebUtils.getParametersStartingWith(request, "register_");
		String stuempNo = filterMap.get("stuNumber").toString();
		String stuempName = filterMap.get("trueName").toString();
		filterMap.put("accountId",accountId);
		List clerkList = workInfoService.searchClerkForReg(filterMap);

		if (!clerkList.isEmpty()) {
			request.setAttribute("show", "block");
		}
		request.setAttribute("stuempNo",stuempNo);
		request.setAttribute("stuempName",stuempName);
		String currentDate = DateUtilExtend.getNowDate();
		request.setAttribute("beginDate",currentDate);
		request.setAttribute("endDate",currentDate);
		List leaveType = sysService.getLeaveList();
		request.setAttribute("leavetype",leaveType);
		request.setAttribute("beginHour","00");
		request.setAttribute("beginMin","00");
		request.setAttribute("endHour","00");
		request.setAttribute("endMin","00");
		request.setAttribute("checkDate",DateUtilExtend.getNowDate());
		request.setAttribute("clerkList", clerkList);

		return mapping.findForward("replaceReportLeave");
	}
	/**
	 * hanjiwei add it 20061227
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward goMenualModify(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);
		String endDate = DateUtilExtend.getNowDate2();
		String beginDate = DateUtilExtend.addDate2(endDate,-7);
		request.setAttribute("endDate",DateUtilExtend.formatDate3(endDate));
		request.setAttribute("beginDate",DateUtilExtend.formatDate3(beginDate));
		return mapping.findForward("goMenualModify");
	}

	/**
	 * 手工考勤修改查询
	 * hanjiwei add it 20061227
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward searchClerkModify(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);

		Map filterMap = WebUtils.getParametersStartingWith(request, "register_");
		String beginDate = filterMap.get("sDate").toString();
		String endDate = filterMap.get("eDate").toString();
		filterMap.put("accountId",accountId);
		filterMap.put("beginDate",DateUtilExtend.formatDate2(beginDate));
		filterMap.put("endDate",DateUtilExtend.formatDate2(endDate));
		List clerkList = workInfoService.searchClerkForModify(filterMap);

		request.setAttribute("endDate",endDate);
		request.setAttribute("beginDate",beginDate);
		request.setAttribute("checkDate",DateUtilExtend.getNowDate());
		request.setAttribute("clerkList", clerkList);
		//System.out.print(StringUtil.changeToBig(916956896325.24));
		return mapping.findForward("goMenualModify");
	}

	/**
	 * 手工考勤修改页面
	 * hanjiwei add it 20061227
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward goClerkModify(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String seriId = request.getParameter("serial_id").toString();
		Map clerkMap = workInfoService.searchClerkForModify(Integer.parseInt(seriId));
		request.setAttribute("STUEMP_NO",clerkMap.get("STUEMP_NO"));
		request.setAttribute("CUT_NAME",clerkMap.get("CUT_NAME"));
		request.setAttribute("ATT_DATE",clerkMap.get("ATT_DATE"));
		request.setAttribute("ATT_HOUR",clerkMap.get("ATT_HOUR"));
		request.setAttribute("ATT_MIN",clerkMap.get("ATT_MIN"));
		request.setAttribute("DEPT_NAME",clerkMap.get("DEPT_NAME"));
		request.setAttribute("serial_id",clerkMap.get("serial_id"));
		request.setAttribute("oper_name",clerkMap.get("oper_name"));
		request.setAttribute("oper_date",clerkMap.get("oper_date"));
		return mapping.findForward("menualModify");
	}
	
	/**
	 * 手工考勤记录删除
	 * hanjiwei add it 20061228
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward deleteManual(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String[] manualIds = request.getParameterValues("itemlist");
		String endDate = DateUtilExtend.getNowDate2();
		String beginDate = DateUtilExtend.addDate2(endDate,-7);
		request.setAttribute("endDate",DateUtilExtend.formatDate3(endDate));
		request.setAttribute("beginDate",DateUtilExtend.formatDate3(beginDate));
		for (int i=0;i<manualIds.length;i++){
			Tattserialrecord attserial = workInfoService.get(Integer.valueOf(manualIds[i]));
			workInfoService.deleteRegister(attserial);
		}
		ActionMessages messages = new ActionMessages();
		messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
				"success.delete", String.valueOf(manualIds.length)));
		saveMessages(request, messages);
		return mapping.findForward("goMenualModify");
	}
	/**
	 * 手工打卡
	 * hanjiwei modify it 20060918
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward manualRegister(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession();
		String operator = session.getAttribute("account").toString();
		//List departmentTree = departmentService.getDepartmentTree(0, null);
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);

		Map filterMap = WebUtils
				.getParametersStartingWith(request, "register_");
		String ids = request.getParameter("itemlist");

		String startDate = (String) filterMap.get("startDate");
		String startHour = (String) filterMap.get("startHour");
		if (startHour.length()<2){
			startHour = "0" + startHour;
		}

		String startMin = (String) filterMap.get("startMin");
		if (startMin.length()<2){
			startMin = "0" + startMin;
		}

		String checkDate = DateUtilExtend.formatDate2(startDate);
		String checkTime = startHour + startMin + "00";

		//String deptId = sysService.getDeptInfo(Integer.parseInt(ids)).get("dept_id").toString();
		
		if (//(sysService.getReportRecord(deptId,checkDate.substring(0,6))>0)||
				//(sysService.getReportRecord("0",checkDate.substring(0,6))>0)||
				//(sysService.getReportRecord(deptId,checkDate)>0)||
				//(sysService.getReportRecord("0",checkDate)>0)
				1<0){
			//提示不能手工签到
			String msg = "已经生成考勤报表,不能手工考勤";
			request.setAttribute("msg", msg);
			return mapping.findForward("goMenualRegister");
		}else{		
			ActionMessages messages = new ActionMessages();
			List regList = new ArrayList();
			if (ids != null) {
				/*
				for (int i = 0; i < ids.length; i++) {
					if (("".equals(ids[i]))||(ids[i]==null)){
						continue;
					}
					*/
				//检查该人员是否有考勤记录，如果不坐班超过两条，坐班超过8条，不允许再添加
				List manualList = workInfoService.getManualCheckList(Integer.parseInt(ids),checkDate);
				int manualSize = manualList.size();
				if (manualSize>0){
					Map manualMap = (Map)manualList.get(0);
					if (("2".equals(manualMap.get("IFOFFICE"))&& manualSize>=4)||
							("1".equals(manualMap.get("IFOFFICE"))&& manualSize>=8)){
						messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
								"success.tomany", ""));
						saveMessages(request, messages);	
						return mapping.findForward("goMenualRegister");
					}
				}
				Tattserialrecord attserial = new Tattserialrecord();
				attserial.setCardId(workInfoService.getCardIdByCustId(ids));
				attserial.setCustId(Integer.valueOf(ids));
				attserial.setAttDate(checkDate);
				attserial.setAttTime(checkTime);
				attserial.setOperDate(DateUtilExtend.getNowDate2());
				attserial.setOperId(operator);
				attserial.setOperTime(DateUtilExtend.getNowTime());
				attserial.setPhyId(workInfoService.getPhyCardIdByCustId(ids));
				attserial.setRemark("0");
				attserial.setShowCardno("");
				regList.add(attserial);
				//}
			}
	
			workInfoService.manualRegister(regList);			
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"success.setup", String.valueOf(1)));
			saveMessages(request, messages);	
			return mapping.findForward("goMenualRegister");
		}
	}

	/**
	 * 手工打卡修改
	 * hanjiwei add it 20061227
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward manualRegisterModify(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		HttpSession session = request.getSession();
		String operator = session.getAttribute("account").toString();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);

		Map filterMap = WebUtils.getParametersStartingWith(request, "register_");

		String startDate = (String) filterMap.get("sDate");
		String startHour = (String) filterMap.get("startHour");
		if (Integer.parseInt(startHour) < 10
				&& Integer.parseInt(startHour) != 0)
			startHour = "0" + startHour;

		String startMin = (String) filterMap.get("startMin");
		if (Integer.parseInt(startMin) < 10 && Integer.parseInt(startMin) != 0)
			startMin = "0" + startMin;

		String checkDate = DateUtilExtend.formatDate2(startDate);
		String checkTime = startHour + startMin + "00";
		
		//String deptId = sysService.getDeptInfoBySeriId(Integer.parseInt(filterMap.get("seriId").toString())).get("dept_id").toString();
		
		if (//(sysService.getReportRecord(deptId,checkDate.substring(0,6))>0)||
				//(sysService.getReportRecord("0",checkDate.substring(0,6))>0)||
				//(sysService.getReportRecord(deptId,checkDate)>0)||
				//(sysService.getReportRecord("0",checkDate)>0))
				1<0){
			//提示不能手工签到
			String msg = "已经生成考勤报表,不能手工考勤";
			request.setAttribute("msg", msg);
			return mapping.findForward("goMenualModify");
		}else{
			Tattserialrecord attserial = workInfoService.get(Integer.valueOf(filterMap.get("seriId").toString()));
			attserial.setAttDate(checkDate);
			attserial.setAttTime(checkTime);
			attserial.setOperDate(DateUtilExtend.getNowDate2());
			attserial.setOperId(operator);
			attserial.setOperTime(DateUtilExtend.getNowTime());
	
			workInfoService.updateRegister(attserial);
			ActionMessages messages = new ActionMessages();
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"success.modify", "1"));
			saveMessages(request, messages);
			String endDate = DateUtilExtend.getNowDate2();
			String beginDate = DateUtilExtend.addDate2(endDate,-7);
			request.setAttribute("endDate",DateUtilExtend.formatDate3(endDate));
			request.setAttribute("beginDate",DateUtilExtend.formatDate3(beginDate));
	
			return mapping.findForward("goMenualModify");
		}
	}

	/**
	 * hanjiwei modify it 20061019
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward goCreateWorkInfo(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {

		if (createWorkInfoThread != null) {
			if (createWorkInfoThread.runThread) {
				request.setAttribute("closeDisabled", " ");
			} else {
				request.setAttribute("openDisabled", " ");
			}

		} else {
			request.setAttribute("openDisabled", " ");
		}
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);

		String startDate = DateUtilExtend.getNowDate();
		String endDate = startDate;
		request.setAttribute("startDate",startDate);
		request.setAttribute("endDate",endDate);
		return mapping.findForward("goCreateWorkInfo");
	}

	/**
	 * hanjiwei modify it 20061019
	 * 生成考勤统计数据
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward createWorkInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		//再增加一个部门查询和学工号查询
		String startDate = request.getParameter("startDate");
		String endDate =request.getParameter("endDate");
		String deptId = request.getParameter("deptId");
		//List getCustWorkTime = workInfoService.getCustWorkTime(deptId,DateUtilExtend.formatDate2(startDate),DateUtilExtend.formatDate2(endDate));
		String stuEmpNo = request.getParameter("stuEmpNo");
		Map map = new HashMap();
		map.put("startDate", DateUtilExtend.formatDate2(startDate));
		map.put("endDate",DateUtilExtend.formatDate2(endDate));
		map.put("stuEmpNo",stuEmpNo);
		map.put("deptId",deptId);

		workInfoService.createAllWorkInfoByDptConf(map);
		workInfoService.createAllWorkReportByDptConf(map);
		String msg = "生成"+startDate+"--"+endDate+"的考勤数据成功！";

		request.setAttribute("msg", msg);
		
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);
		request.setAttribute("startDate", startDate);
		request.setAttribute("endDate",endDate);
		request.setAttribute("stuEmpNo",stuEmpNo);
		request.setAttribute("deptId",deptId);
		return mapping.findForward("goCreateWorkInfo");
	}

	/**
	 * hanjiwei modify it 20061019
	 * 打开生成统计数据线程
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward openTread(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		createWorkInfoThread = new CreateWorkInfoThread();
		String startDate = DateUtilExtend.getNowDate();
		String endDate = startDate;
		request.setAttribute("startDate",startDate);
		request.setAttribute("endDate",endDate);
		request.setAttribute("closeDisabled", " ");
		return mapping.findForward("goCreateWorkInfo");
	}

	/**
	 * hanjiwei modify it 20061019
	 * 关闭生成考勤数据线程
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward closeTread(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		if (createWorkInfoThread != null) {
			createWorkInfoThread.runThread = false;
			if (createWorkInfoThread.isAlive()) {
				log.debug("still alive");
			}
		}
		String startDate = DateUtilExtend.getNowDate();
		String endDate = startDate;
		request.setAttribute("startDate",startDate);
		request.setAttribute("endDate",endDate);
		request.setAttribute("openDisabled", " ");
		return mapping.findForward("goCreateWorkInfo");
	}
	
	public ActionForward goCustWorkTimeInfo(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {

		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);

		String startDate = DateUtilExtend.getNowDate();
		String endDate = startDate;
		request.setAttribute("startDate",startDate);
		request.setAttribute("endDate",endDate);
		return mapping.findForward("goCustWorkTimeInfo");
	}

	public ActionForward custWorkTimeInfoStat(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String startDate = request.getParameter("startDate");
		String endDate =request.getParameter("endDate");
		String deptId = request.getParameter("deptId");
		List custWorkTimeList = workInfoService.getCustWorkTime(deptId,DateUtilExtend.formatDate2(startDate),DateUtilExtend.formatDate2(endDate));
		
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", deptList);
		request.setAttribute("startDate", startDate);
		request.setAttribute("endDate",endDate);
		request.setAttribute("custWorkTimeList",custWorkTimeList);
		request.setAttribute("deptId",deptId);
		return mapping.findForward("goCustWorkTimeInfo");
	}
	
}
