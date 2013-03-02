/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.check.web.ClerkAction.java
 * 创建日期： 2006-6-13 13:48:18
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-6-13 13:48:18      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.check.web.action;

import java.util.ArrayList;
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
import org.king.check.domain.Tclerkinfo;
import org.king.check.domain.Toperlimit;
import org.king.check.domain.ToperlimitId;
import org.king.check.domain.Tworkconfinfo;
import org.king.check.domain.Tworktimeinfo;
import org.king.check.service.ClerkService;
import org.king.check.service.DepartmentService;
import org.king.check.service.SysService;
import org.king.check.service.WorkConfService;
import org.king.check.service.WorkTimeConfService;
import org.king.check.util.StringUtil;
import org.king.framework.util.MyUtils;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;
import org.king.security.domain.Person;
import org.king.security.service.AccountService;
import org.king.security.service.SecurityService;
import org.springframework.web.util.WebUtils;

/**
 * <p>
 * CheckAction.java
 * </p>
 * <p>
 * {功能说明}
 * </p>
 * 
 * <p>
 * <a href="ClerkAction.java.html"><i>查看源代码</i></a>
 * </p>
 * 
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-13
 * 
 * 
 */
public class ClerkAction extends BaseAction {

	private static final Log log = LogFactory.getLog(ClerkAction.class);

	private ClerkService clerkService;

	private DepartmentService departmentService;

	private SysService sysService;

	private WorkTimeConfService workTimeConfService;

	private WorkConfService workConfService;

	private AccountService accountService;
	
	private SecurityService securityService;

	public void setClerkService(ClerkService clerkService) {
		this.clerkService = clerkService;
	}

	public void setDepartmentService(DepartmentService departmentService) {
		this.departmentService = departmentService;
	}

	public void setSysService(SysService sysService) {
		this.sysService = sysService;
	}

	public void setWorkTimeConfService(WorkTimeConfService workTimeConfService) {
		this.workTimeConfService = workTimeConfService;
	}

	public void setWorkConfService(WorkConfService workConfService) {
		this.workConfService = workConfService;
	}

	public void setAccountService(AccountService accountService){
		this.accountService = accountService;
	}
	
	public void setSecurityService(SecurityService securityService){
		this.securityService = securityService;
	}


	/**
	 * 装载考勤人员信息
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward load4queryClerk(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {

		// List departmentTree = departmentService.getDepartmentTree(0, null);
		// request.setAttribute("departments",departmentTree);
		// 增加取出所有的部门列表
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);
		//List deptList = sysService.getDeptList();
		request.setAttribute("departments", deptList);
		
		int deptCount = sysService.getDeptCount();
		int deptCountByLogin = sysService.getDeptByLogin(accountId);
		if (deptCount==deptCountByLogin){
			request.setAttribute("admin",new Integer(1));
		}else{
			request.setAttribute("admin",new Integer(0));
		}

		// 人员类型
		// List dictionarys = dictionaryService.findDictionaryByNo("1001");
		// request.setAttribute("dictionarys",dictionarys);
		return mapping.findForward("query");
	}

	/**
	 * 查询考勤人员
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward queryClerkInfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		Map filterMap = WebUtils.getParametersStartingWith(request, "search_");
		List clerkList = clerkService.queryClerk(filterMap);
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		
		List deptList = sysService.getDeptList(accountId);

		request.setAttribute("clerks", clerkList);
		request.setAttribute("departments", deptList);
		int deptCount = sysService.getDeptCount();
		int deptCountByLogin = sysService.getDeptByLogin(accountId);
		if (deptCount==deptCountByLogin){
			request.setAttribute("admin",new Integer(1));
		}else{
			request.setAttribute("admin",new Integer(0));
		}

		return mapping.findForward("success");
	}

	/**
	 * 装载可利用的人员
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward load4queryAvailableClerk(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {

		List departmentTree = departmentService.getDepartmentTree(0, null);
		request.setAttribute("departments", departmentTree);

		// 卡状态
		// List cardStatusList=sysService.getCardStatus();
		// request.setAttribute("cardStatusList",cardStatusList);

		// 人员类型
		//List personTypeList = sysService.getPersonType();
		//request.setAttribute("personTypeList", personTypeList);

		// 卡类别
		//List cardTypeList = sysService.getCardType();
		//request.setAttribute("cardTypeList", cardTypeList);
		
		//专业列表
		List specList = sysService.getSpecList();
		request.setAttribute("specList",specList);

		// 部门列表
		List departList = sysService.getDepartList();
		request.setAttribute("departList", departList);
		//考勤类别列表
		List checkattList = sysService.getCheckattType();
		request.setAttribute("checkattList",checkattList);
		//班次信息列表
		List checkTypeList = sysService.getCheckTypeInfo();
		request.setAttribute("checkTypeList",checkTypeList);
		//所属部门列表
		List deptList = sysService.getDeptList();
		request.setAttribute("personDept", deptList);
		return mapping.findForward("queryPerson");
	}

	/**
	 * 查询可利用的人员
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward QueryAvailablePerson(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {

		Map filterMap = WebUtils.getParametersStartingWith(request, "search_");
		// 卡状态
		// List cardStatusList=sysService.getCardStatus();
		// request.setAttribute("cardStatusList",cardStatusList);

		// 人员类型
		List personTypeList = sysService.getPersonType();
		request.setAttribute("personTypeList", personTypeList);

		// 卡类别
		//List cardTypeList = sysService.getCardType();
		//request.setAttribute("cardTypeList", cardTypeList);
		
		//专业列表
		List specList = sysService.getSpecList();
		request.setAttribute("specList",specList);

		// 部门列表
		List departList = sysService.getDepartList();
		request.setAttribute("departList", departList);
		
		//考勤类别列表
		List checkattList = sysService.getCheckattType();
		request.setAttribute("checkattList",checkattList);

		List searchRes = sysService.search(filterMap);
		request.setAttribute("searchRes", searchRes);
		
		//班次信息列表
		List checkTypeList = sysService.getCheckTypeInfo();
		request.setAttribute("checkTypeList",checkTypeList);
		//所属部门列表
		List deptList = sysService.getDeptList();
		request.setAttribute("personDept", deptList);

		return mapping.findForward("queryPerson");

	}

	/**
	 * 设置考勤人员信息
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward setupClerk(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		ActionMessages messages = new ActionMessages();
		String[] custIds = StringUtil.split(request.getParameter("groupedlist"),",");
		String deptId = request.getParameter("personDept");
		String isSeat = request.getParameter("isSeat");
		String checkType = request.getParameter("checkType");
		
		/*
		String aheadOverTime = request.getParameter("aheadOverTime");
		String delayOverTime = request.getParameter("delayOverTime");
		String overTime = request.getParameter("overTimeUnit");
		String twoReset = request.getParameter("twoReset");
		String holiday = request.getParameter("holiday");
		*/
		String aheadOverTime = "0";
		String delayOverTime = "0";
		String overTime = "0";
		String twoReset = "0";
		String holiday = "0";


		List idList = new ArrayList();
		for (int i = 0; i < custIds.length; i++) {
			if (!idList.contains(custIds[i])) {
				idList.add(custIds[i]);
			}
		}

		List clerkList = new ArrayList();
		if (custIds != null) {
			for (int i = 0; i < idList.size(); i++) {
				Tclerkinfo clerk = new Tclerkinfo();
				clerk.setCustId(Integer.valueOf((String) idList.get(i)));
				clerk.setDeptId(deptId);
				clerk.setIfoffice(isSeat);
				clerk.setAheadOvertime(aheadOverTime);
				clerk.setDelayOvertime(delayOverTime);
				clerk.setOvertimeValue(Integer.valueOf(overTime));
				clerk.setHolidayOvertime(holiday);
				clerk.setTworestOvertime(twoReset);
				clerk.setChecktypeId(checkType);
				
				clerkList.add(clerk);
				saveAccountInfo(Integer.parseInt(idList.get(i).toString()));
				saveRoleInfo(Integer.parseInt(idList.get(i).toString()));
				//saveLimitInfo(deptId,Integer.parseInt(idList.get(i).toString()));
			}

			int count = clerkService.setupClerk(clerkList);
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"success.setup", String.valueOf(count)));
			saveMessages(request, messages);
		}
		return mapping.findForward("success");//
	}

	/**
	 * 保存账号信息
	 * hanjiwei add it 20061107
	 * @param custId
	 * @throws Exception
	 */
	private void saveAccountInfo(int custId)throws Exception{
		Account account = new Account();
		Person person = new Person();
		Map custInfo = sysService.getCustInfoByCustId(custId);
		String stuempNo = custInfo.get("STUEMP_NO").toString();
		String custName = custInfo.get("CUT_NAME").toString().trim();
		person.setPersonCode(stuempNo);
		person.setPersonName(custName);
		person.setPersonType("1");
		person.setSex("");
		account.setPassword(MyUtils.toMD5(stuempNo));
		account.setPerson(person);
		account.setName(stuempNo);
		account.setEnabled("");
		if (null==accountService.findAccountByName(stuempNo)){
			accountService.saveAccount(account);
		}

	}
	
	/**
	 * 保存角色信息
	 * @param custId
	 * @throws Exception
	 */
	private void saveRoleInfo(int custId)throws Exception{
		Map custInfo = sysService.getCustInfoByCustId(custId);
		String stuempNo = custInfo.get("STUEMP_NO").toString();
		String accId = sysService.getAccountIdByStuempNo(stuempNo);
		String[] role = {"3"};
		securityService.grantAccountRoles(accId, role);
	}
	
	/**
	 * 保存权限信息
	 * @param deptId
	 * @param custId
	 * @throws Exception
	 */
	private void saveLimitInfo(String deptId,int custId)throws Exception{
		Map custInfo = sysService.getCustInfoByCustId(custId);
		String stuempNo = custInfo.get("STUEMP_NO").toString();
		String operId = sysService.getAccountIdByStuempNo(stuempNo);
		if (!"".equals(deptId) && null!=deptId){
			Toperlimit operLimit = new Toperlimit();
			ToperlimitId operLimitId = new ToperlimitId();
			operLimitId.setDeptId(deptId);
			operLimitId.setOperId(operId);
			operLimit.setId(operLimitId);
			if (accountService.getAccountLimit(deptId,operId).size()==0){
				accountService.saveAccountLimit(operLimit);
			}else{
				accountService.updateAccountLimit(operLimit);
			}
		}
	}
	
	/**
	 * 在删除考勤人员信息的同时删除帐户信息和权限信息
	 * hanjiwei modify it 20061113
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward deleteClerk(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		ActionMessages messages = new ActionMessages();
		int count = 0;
		String[] ids = request.getParameterValues("itemlist");
		accountService.deleteAccountLimitIds(ids);
		if (ids != null) {
			for (int i = 0; i < ids.length; i++) {
				Account account = accountService.findAccountByName(sysService.getCustInfoByCustId(Integer.parseInt(ids[i].toString())).get("STUEMP_NO").toString());
				if (null!=account){
					String accountId = account.getId().toString();
					if (!"".equals(accountId)){
						accountService.deleteAccount(accountId);
					}
				}
				clerkService.deleteClerk(ids[i]);
				count++;
			}

			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"success.delete", String.valueOf(count)));
			saveMessages(request, messages);

		}
		HttpSession session = request.getSession();
		String  accountId = (String)session.getAttribute("account");
		List deptList = sysService.getDeptList(accountId);
		//List deptList = sysService.getDeptList();
		request.setAttribute("departments", deptList);
		
		Map filterMap = WebUtils.getParametersStartingWith(request, "search_");
		List clerkList = clerkService.queryClerk(filterMap);
		request.setAttribute("clerks", clerkList);

		return mapping.findForward("success");
	}

	/**
	 * hanjiwei delete it 20060917
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward setupSeatClerk(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		return mapping.findForward("success");
	}

	public ActionForward getConfDetail(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String workConfId = request.getParameter("clerkRule");// 添加工作制度细节
		if (StringUtils.isNotEmpty(workConfId)) {
			Tworkconfinfo workconf = workConfService.getWorkConf(workConfId);
			String workconfDetail = "";
			workconfDetail += "允许早退:" + workconf.getLeaveearlyTime() + "分钟 ";
			workconfDetail += "允许迟到:" + workconf.getOverdueTime() + "分钟 ";
			workconfDetail += "上班提前打卡不允许超过:" + workconf.getOverTime() + "分钟 ";
			workconfDetail += "下班打卡允许滞后:" + workconf.getDelayTime()
					+ "分钟 ";
			request.setAttribute("workconfDetail", workconfDetail);
		}

		String workTimeConfId = request.getParameter("cherkTimeRule");// 添加工作时间细节
		if (StringUtils.isNotEmpty(workTimeConfId)) {
			Tworktimeinfo worktimeconf = workTimeConfService
					.getWorkTimeConf(workTimeConfId);
			String timeDetail = "";
			int token = 1;
			String ondutytime, offdutytime;
			if (StringUtils.isNotEmpty(worktimeconf.getOntime1())
					|| StringUtils.isNotEmpty(worktimeconf.getOfftime1())) {
				ondutytime = worktimeconf.getOntime1();
				offdutytime = worktimeconf.getOfftime1();
				timeDetail += StringUtils.isNotEmpty(ondutytime) ? "上班时间"
						+ token + ": " + ondutytime.substring(0, 2) + "点"
						+ ondutytime.substring(2) + "分 " : "";
				timeDetail += StringUtils.isNotEmpty(offdutytime) ? "下班时间"
						+ token + ": " + offdutytime.substring(0, 2) + "点"
						+ offdutytime.substring(2) + "分 " : "";
				token++;
			}
			if (StringUtils.isNotEmpty(worktimeconf.getOntime2())
					|| StringUtils.isNotEmpty(worktimeconf.getOfftime2())) {
				ondutytime = worktimeconf.getOntime2();
				offdutytime = worktimeconf.getOfftime2();
				timeDetail += StringUtils.isNotEmpty(ondutytime) ? "上班时间"
						+ token + ": " + ondutytime.substring(0, 2) + "点"
						+ ondutytime.substring(2) + "分 " : "";
				timeDetail += StringUtils.isNotEmpty(offdutytime) ? "下班时间"
						+ token + ": " + offdutytime.substring(0, 2) + "点"
						+ offdutytime.substring(2) + "分 " : "";
				token++;
			}
			if (StringUtils.isNotEmpty(worktimeconf.getOntime3())
					|| StringUtils.isNotEmpty(worktimeconf.getOfftime3())) {
				ondutytime = worktimeconf.getOntime3();
				offdutytime = worktimeconf.getOfftime3();
				timeDetail += StringUtils.isNotEmpty(ondutytime) ? "上班时间"
						+ token + ": " + ondutytime.substring(0, 2) + "点"
						+ ondutytime.substring(2) + "分 " : "";
				timeDetail += StringUtils.isNotEmpty(offdutytime) ? "下班时间"
						+ token + ": " + offdutytime.substring(0, 2) + "点"
						+ offdutytime.substring(2) + "分 " : "";
				token++;
			}
			if (StringUtils.isNotEmpty(worktimeconf.getOntime4())
					|| StringUtils.isNotEmpty(worktimeconf.getOfftime4())) {
				ondutytime = worktimeconf.getOntime4();
				offdutytime = worktimeconf.getOfftime4();
				timeDetail += StringUtils.isNotEmpty(ondutytime) ? "上班时间"
						+ token + ": " + ondutytime.substring(0, 2) + "点"
						+ ondutytime.substring(2) + "分 " : "";
				timeDetail += StringUtils.isNotEmpty(offdutytime) ? "下班时间"
						+ token + ": " + offdutytime.substring(0, 2) + "点"
						+ offdutytime.substring(2) + "分 " : "";
				token++;
			}
			request.setAttribute("timeDetail", timeDetail);
		}

		List workConfList = workConfService.getAll();
		List workTimeConfList = workTimeConfService.getAll();
		List departmentTree = departmentService.getDepartmentTree(0, null);

		request.setAttribute("workConfList", workConfList);
		request.setAttribute("workTimeConfList", workTimeConfList);
		request.setAttribute("departments", departmentTree);

		return mapping.findForward("setup");
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
	public ActionForward viewClerkDetail(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		log.debug("viewClerkDetail");
		String clerkId = request.getParameter("custId");

		Map clerkInfo = clerkService.getClerkDetailByClerkId(clerkId);
		
		request.setAttribute("clerkInfo", clerkInfo);

		return mapping.findForward("showDetail");
	}
}
