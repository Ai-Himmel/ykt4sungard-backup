package org.king.check.web.action;

import java.util.ArrayList;
import java.util.HashMap;
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
import org.king.check.config.CommonConfig;
import org.king.check.domain.Tattserialrecord;
import org.king.check.service.DepartmentService;
import org.king.check.service.DutyTimeService;
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

	private DepartmentService departmentService;
	
	private SysService sysService;

	private static CreateWorkInfoThread createWorkInfoThread;// 开启生成考勤数据的线程

	public void setDutyTimeService(DutyTimeService dutyTimeService) {
		this.dutyTimeService = dutyTimeService;
	}

	public void setWorkInfoService(WorkInfoService workInfoService) {
		this.workInfoService = workInfoService;
	}

	public void setDepartmentService(DepartmentService departmentService) {
		this.departmentService = departmentService;
	}

	public void setSysService(SysService sysService) {
		this.sysService = sysService;
	}

	
	public ActionForward searchNoSeatWorkInfo(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		DynaActionForm noSeatParaForm = (DynaActionForm) form;
		String startDate = (String) noSeatParaForm.get(CommonConfig.startDate);
		String endDate = (String) noSeatParaForm.get(CommonConfig.endDate);
		String departId = (String) noSeatParaForm.get(CommonConfig.deptId);

		if (StringUtils.isNotEmpty(startDate)
				&& StringUtils.isNotEmpty(endDate)) {
			startDate = startDate + " 00:00:00";
			endDate = endDate + " 23:59:59";

			// log.debug(startDate+endDate);
		}

		HashMap paraMap = new HashMap();
		paraMap.put(CommonConfig.startDate, startDate);
		paraMap.put(CommonConfig.endDate, endDate);
		paraMap.put(CommonConfig.deptId, departId);

		List noSeatWorkInfoList = dutyTimeService.searchInfo(paraMap);
		List departmentTree = departmentService.getDepartmentTree(0, null);

		request.getSession().setAttribute("noSeatWorkInfoList",
				noSeatWorkInfoList);
		request.setAttribute("departmentTree", departmentTree);
		request.setAttribute(CommonConfig.startDate, (String) noSeatParaForm
				.get(CommonConfig.startDate));
		request.setAttribute(CommonConfig.endDate, (String) noSeatParaForm
				.get(CommonConfig.endDate));

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
		Map filterMap = WebUtils
				.getParametersStartingWith(request, "dutyInfo_");

		request.setAttribute(CommonConfig.startDate, (String) filterMap
				.get(CommonConfig.startDate));
		request.setAttribute(CommonConfig.endDate, (String) filterMap
				.get(CommonConfig.endDate));
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List departmentTree = sysService.getDeptList(accountId);
		request.setAttribute("departmentTree", departmentTree);

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

		Map newFormatM = dutyTimeService.searchForNewFormat(filterMap);

		// log.debug("action over");

		request.setAttribute("newFormatL", (List) newFormatM
				.get(CommonConfig.dutyStrs));
		request.setAttribute("titleStr", (String) newFormatM
				.get(CommonConfig.titleStr));

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
		//List departmentTree = departmentService.getDepartmentTree(0, null);
		//Date curDate = new Date();
		//int offSet = 6;

		endDate = DateUtilExtend.getNowDate();
		startDate = DateUtilExtend.formatDate3(DateUtilExtend.addDate2(DateUtilExtend.formatDate2(endDate),-6));

		String titleStr = "<td width='100' align='center'  bgcolor='#A8D1E6'>部门</td>  <td><table border='1'  cellpadding='1'"
				+ "  cellspacing='2' > <tr>";
		titleStr += "<td  width='50' align='center' class='tdHeader1'>姓名</td>";
		titleStr += "<td width='95' class='tableHeader6' align='center'>"
				+ startDate + "</td>";
		titleStr += "<td width='95' class='tableHeader6' align='center'>"
				+ endDate + "</td>";
		titleStr += "</tr></table></td>";

		request.setAttribute("titleStr", titleStr);
		request.setAttribute(CommonConfig.startDate, startDate);
		request.setAttribute(CommonConfig.endDate, endDate);
		request.setAttribute("departmentTree", departmentTree);
		return mapping.findForward("gonewformat");
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
		// log.debug("goMenualRegister");
		List departmentTree = departmentService.getDepartmentTree(0, null);
		request.setAttribute("departmentTree", departmentTree);

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
		List departmentTree = departmentService.getDepartmentTree(0, null);
		request.setAttribute("departmentTree", departmentTree);

		Map filterMap = WebUtils
				.getParametersStartingWith(request, "register_");

		List clerkList = workInfoService.searchClerkForReg(filterMap);

		if (!clerkList.isEmpty()) {
			request.setAttribute("show", "block");
		}

		request.setAttribute("clerkList", clerkList);

		return mapping.findForward("goMenualRegister");
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
		List departmentTree = departmentService.getDepartmentTree(0, null);
		request.setAttribute("departmentTree", departmentTree);

		Map filterMap = WebUtils
				.getParametersStartingWith(request, "register_");
		String ids[] = request.getParameterValues("itemlist");

		String startDate = (String) filterMap.get("startDate");
		String startHour = (String) filterMap.get("startHour");
		if (Integer.parseInt(startHour) < 10
				&& Integer.parseInt(startHour) != 0)
			startHour = "0" + startHour;

		String startMin = (String) filterMap.get("startMin");
		if (Integer.parseInt(startMin) < 10 && Integer.parseInt(startMin) != 0)
			startMin = "0" + startMin;

		String checkDate = DateUtilExtend.formatDate2(startDate);
		String checkTime = startHour + startMin + "00";

		if ((workInfoService.judgeIsOwnValidCardByClerkId(ids)) == null) {
			request.setAttribute("msg", "卡号无效,请检查!");

			return mapping.findForward("goMenualRegister");
		}
		List regList = new ArrayList();
		if (ids != null) {
			for (int i = 0; i < ids.length; i++) {
				Tattserialrecord attserial = new Tattserialrecord();
				attserial.setCardId(workInfoService.getCardIdByCustId(ids[i]));
				attserial.setCustId(Integer.valueOf(ids[i]));
				attserial.setAttDate(checkDate);
				attserial.setAttTime(checkTime);
				attserial.setOperDate(DateUtilExtend.getNowDate2());
				attserial.setOperId(operator);
				attserial.setOperTime(DateUtilExtend.getNowTime());
				attserial
						.setPhyId(workInfoService.getPhyCardIdByCustId(ids[i]));
				attserial.setRemark("0");
				attserial.setShowCardno("");
				regList.add(attserial);
			}
		}

		workInfoService.manualRegister(regList);
		ActionMessages messages = new ActionMessages();
		messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
				"success.setup", String.valueOf(ids.length)));
		saveMessages(request, messages);

		// request.setAttribute("msg","签到成功，共签到"+ids.length+"个人！");
		return mapping.findForward("goMenualRegister");
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
		String startDate = DateUtilExtend.formatDate2(request.getParameter("startDate"));
		String endDate = DateUtilExtend.formatDate2(request.getParameter("endDate"));
		Map map = new HashMap();
		map.put("startDate", startDate);
		map.put("endDate",endDate);

		workInfoService.createAllWorkInfoByDptConf(map);
		String msg = "生成"+startDate+"--"+endDate+"的考勤数据成功！";

		request.setAttribute("msg", msg);
		
		request.setAttribute("startDate", startDate);
		request.setAttribute("endDate",endDate);

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
		request.setAttribute("openDisabled", " ");
		return mapping.findForward("goCreateWorkInfo");
	}
	
	/**
	 * hanjiwei add it 20061107
	 * 个人考勤情况明细
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward goOnesCheckDetail(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		String endDate = DateUtilExtend.getNowDate();
		String startDate = DateUtilExtend.formatDate3(DateUtilExtend.addDate2(DateUtilExtend.formatDate2(endDate),-6));

		request.setAttribute(CommonConfig.startDate, startDate);
		request.setAttribute(CommonConfig.endDate, endDate);
		return mapping.findForward("queryPersonalCheckDetail");
	}
	public ActionForward getOnesCheckDetail(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		Map filterMap = WebUtils
		.getParametersStartingWith(request, "dutyInfo_");

		request.setAttribute(CommonConfig.startDate, (String) filterMap
				.get(CommonConfig.startDate));
		request.setAttribute(CommonConfig.endDate, (String) filterMap
				.get(CommonConfig.endDate));
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("userName");
		
		int custId = sysService.getCustIdByStuempNo(accountId);
		String custName = sysService.getOperName(accountId);
		request.setAttribute("custName", custName);
		
		String beginDate = DateUtilExtend.formatDate2((String) filterMap.get(CommonConfig.startDate));
		String endDate = DateUtilExtend.formatDate2((String) filterMap.get(CommonConfig.endDate));
		
		List checkDetail = workInfoService.getOneCheckDetail(custId,beginDate,endDate);
		request.setAttribute("checkDetail",checkDetail);
		return mapping.findForward("queryPersonalCheckDetail");
	}
	
}
