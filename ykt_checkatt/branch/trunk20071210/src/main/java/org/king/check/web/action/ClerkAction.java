/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.check.web.ClerkAction.java
 * �������ڣ� 2006-6-13 13:48:18
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-6-13 13:48:18      ljf        �����ļ���ʵ�ֻ�������
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
 * {����˵��}
 * </p>
 * 
 * <p>
 * <a href="ClerkAction.java.html"><i>�鿴Դ����</i></a>
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
	 * װ�ؿ�����Ա��Ϣ
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
		// ����ȡ�����еĲ����б�
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

		// ��Ա����
		// List dictionarys = dictionaryService.findDictionaryByNo("1001");
		// request.setAttribute("dictionarys",dictionarys);
		return mapping.findForward("query");
	}

	/**
	 * ��ѯ������Ա
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
	 * װ�ؿ����õ���Ա
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

		// ��״̬
		// List cardStatusList=sysService.getCardStatus();
		// request.setAttribute("cardStatusList",cardStatusList);

		// ��Ա����
		//List personTypeList = sysService.getPersonType();
		//request.setAttribute("personTypeList", personTypeList);

		// �����
		//List cardTypeList = sysService.getCardType();
		//request.setAttribute("cardTypeList", cardTypeList);
		
		//רҵ�б�
		List specList = sysService.getSpecList();
		request.setAttribute("specList",specList);

		// �����б�
		List departList = sysService.getDepartList();
		request.setAttribute("departList", departList);
		//��������б�
		List checkattList = sysService.getCheckattType();
		request.setAttribute("checkattList",checkattList);
		//�����Ϣ�б�
		List checkTypeList = sysService.getCheckTypeInfo();
		request.setAttribute("checkTypeList",checkTypeList);
		//���������б�
		List deptList = sysService.getDeptList();
		request.setAttribute("personDept", deptList);
		return mapping.findForward("queryPerson");
	}

	/**
	 * ��ѯ�����õ���Ա
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
		// ��״̬
		// List cardStatusList=sysService.getCardStatus();
		// request.setAttribute("cardStatusList",cardStatusList);

		// ��Ա����
		List personTypeList = sysService.getPersonType();
		request.setAttribute("personTypeList", personTypeList);

		// �����
		//List cardTypeList = sysService.getCardType();
		//request.setAttribute("cardTypeList", cardTypeList);
		
		//רҵ�б�
		List specList = sysService.getSpecList();
		request.setAttribute("specList",specList);

		// �����б�
		List departList = sysService.getDepartList();
		request.setAttribute("departList", departList);
		
		//��������б�
		List checkattList = sysService.getCheckattType();
		request.setAttribute("checkattList",checkattList);

		List searchRes = sysService.search(filterMap);
		request.setAttribute("searchRes", searchRes);
		
		//�����Ϣ�б�
		List checkTypeList = sysService.getCheckTypeInfo();
		request.setAttribute("checkTypeList",checkTypeList);
		//���������б�
		List deptList = sysService.getDeptList();
		request.setAttribute("personDept", deptList);

		return mapping.findForward("queryPerson");

	}

	/**
	 * ���ÿ�����Ա��Ϣ
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
	 * �����˺���Ϣ
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
	 * �����ɫ��Ϣ
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
	 * ����Ȩ����Ϣ
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
	 * ��ɾ��������Ա��Ϣ��ͬʱɾ���ʻ���Ϣ��Ȩ����Ϣ
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
		String workConfId = request.getParameter("clerkRule");// ��ӹ����ƶ�ϸ��
		if (StringUtils.isNotEmpty(workConfId)) {
			Tworkconfinfo workconf = workConfService.getWorkConf(workConfId);
			String workconfDetail = "";
			workconfDetail += "��������:" + workconf.getLeaveearlyTime() + "���� ";
			workconfDetail += "����ٵ�:" + workconf.getOverdueTime() + "���� ";
			workconfDetail += "�ϰ���ǰ�򿨲�������:" + workconf.getOverTime() + "���� ";
			workconfDetail += "�°�������ͺ�:" + workconf.getDelayTime()
					+ "���� ";
			request.setAttribute("workconfDetail", workconfDetail);
		}

		String workTimeConfId = request.getParameter("cherkTimeRule");// ��ӹ���ʱ��ϸ��
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
				timeDetail += StringUtils.isNotEmpty(ondutytime) ? "�ϰ�ʱ��"
						+ token + ": " + ondutytime.substring(0, 2) + "��"
						+ ondutytime.substring(2) + "�� " : "";
				timeDetail += StringUtils.isNotEmpty(offdutytime) ? "�°�ʱ��"
						+ token + ": " + offdutytime.substring(0, 2) + "��"
						+ offdutytime.substring(2) + "�� " : "";
				token++;
			}
			if (StringUtils.isNotEmpty(worktimeconf.getOntime2())
					|| StringUtils.isNotEmpty(worktimeconf.getOfftime2())) {
				ondutytime = worktimeconf.getOntime2();
				offdutytime = worktimeconf.getOfftime2();
				timeDetail += StringUtils.isNotEmpty(ondutytime) ? "�ϰ�ʱ��"
						+ token + ": " + ondutytime.substring(0, 2) + "��"
						+ ondutytime.substring(2) + "�� " : "";
				timeDetail += StringUtils.isNotEmpty(offdutytime) ? "�°�ʱ��"
						+ token + ": " + offdutytime.substring(0, 2) + "��"
						+ offdutytime.substring(2) + "�� " : "";
				token++;
			}
			if (StringUtils.isNotEmpty(worktimeconf.getOntime3())
					|| StringUtils.isNotEmpty(worktimeconf.getOfftime3())) {
				ondutytime = worktimeconf.getOntime3();
				offdutytime = worktimeconf.getOfftime3();
				timeDetail += StringUtils.isNotEmpty(ondutytime) ? "�ϰ�ʱ��"
						+ token + ": " + ondutytime.substring(0, 2) + "��"
						+ ondutytime.substring(2) + "�� " : "";
				timeDetail += StringUtils.isNotEmpty(offdutytime) ? "�°�ʱ��"
						+ token + ": " + offdutytime.substring(0, 2) + "��"
						+ offdutytime.substring(2) + "�� " : "";
				token++;
			}
			if (StringUtils.isNotEmpty(worktimeconf.getOntime4())
					|| StringUtils.isNotEmpty(worktimeconf.getOfftime4())) {
				ondutytime = worktimeconf.getOntime4();
				offdutytime = worktimeconf.getOfftime4();
				timeDetail += StringUtils.isNotEmpty(ondutytime) ? "�ϰ�ʱ��"
						+ token + ": " + ondutytime.substring(0, 2) + "��"
						+ ondutytime.substring(2) + "�� " : "";
				timeDetail += StringUtils.isNotEmpty(offdutytime) ? "�°�ʱ��"
						+ token + ": " + offdutytime.substring(0, 2) + "��"
						+ offdutytime.substring(2) + "�� " : "";
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
