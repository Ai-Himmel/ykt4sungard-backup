/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.security.web.action.SecurityAction.java
 * 创建日期： 2006-4-20 11:18:02
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-4-20 11:18:02      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.security.web.action;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.commons.beanutils.BeanUtils;
import org.apache.commons.lang.StringUtils;
import org.apache.struts.Globals;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessage;
import org.apache.struts.action.ActionMessages;
import org.apache.struts.action.DynaActionForm;
import org.apache.struts.util.LabelValueBean;
import org.apache.struts.validator.DynaValidatorForm;
import org.king.framework.exception.BusinessException;
import org.king.framework.util.MyUtils;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;
import org.king.security.domain.Menu;
import org.king.security.domain.Resource;
import org.king.security.domain.Role;
import org.king.security.exception.ResourceAlreadyExistException;
import org.king.security.service.AccountService;
import org.king.security.service.MenuService;
import org.king.security.service.SecurityService;
import org.king.security.util.LdapFromSunDS;
import org.king.utils.DateUtil;


/**
 * <p>
 * SecurityAction.java
 * </p>
 * <p>
 * {功能说明}
 * </p>
 * 
 * <p>
 * <a href="SecurityAction.java.html"><i>查看源代码</i></a>
 * </p>
 * 
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-20
 * 
 * 
 */

public class SecurityAction extends BaseAction {

	private SecurityService securityService;

	private AccountService accountService;

	private MenuService menuService;
	
	public void setSecurityService(SecurityService securityService) {
		this.securityService = securityService;
	}

	public void setAccountService(AccountService accountService) {
		this.accountService = accountService;
	}

	public void setMenuService(MenuService menuService) {
		this.menuService = menuService;
	}

	/**
	 * 登录
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward login(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		
		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}
				
		
		ActionMessages errors = new ActionMessages();
		DynaActionForm loginForm = (DynaActionForm) form;
		String userName = (String) loginForm.get("name");
		String password = (String) loginForm.get("password");

		// 检查验证码
		if (!session.getAttribute("chkCode").equals(
				request.getParameter("chkCode"))) {
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"errors.chkCodeNoMatch"));
			saveErrors(request, errors);

			return mapping.findForward("faile");
		}

		Account account = null;

		// 数据库验证
		try {
			account = securityService.login(userName, password);
		} catch (Exception e) {
			// errors.add("User login", new ActionMessage("errors.LoginError"));
		}
		
		if (account == null) {
			errors.add("User login", new ActionMessage("errors.LoginError"));
		}

		// Report any errors we have discovered back to the original form
		if (!errors.isEmpty()) {
			saveErrors(request, errors);

			return mapping.findForward("faile");
		}

		// Remove the obsolete form bean
		removeAttribute(mapping, request);

		// Set account Object to session
		session.setAttribute("accountPerson", account);
		session.setAttribute("account", account.getId());
		// session.setAttribute("group", account.);
		session.setAttribute("userName", userName);
		session.setAttribute("personName", account.getPerson().getPersonName());

		final String destinatedUrl = request.getParameter("DEST_URL");

		// If there is a destinated url,forward to this url
		if ((destinatedUrl != null) && (destinatedUrl.length() > 0)) {
			return new ActionForward(destinatedUrl);
		} else {			
			return (mapping.findForward("success"));
		}

	}

	public final ActionForward logout(final ActionMapping mapping,
			final ActionForm form, final HttpServletRequest request,
			final HttpServletResponse response) throws Exception {

		String userName = (String) request.getSession()
				.getAttribute("userName");

		if (request.getSession(false) != null) {
			request.getSession(false).invalidate();
		}

		// Remove the obsolete form bean
		removeAttribute(mapping, request);

		return mapping.findForward("success");
	}

	/**
	 * 得到用户所拥有的菜单
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward getUserMenu(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {

		HttpSession session = request.getSession(false);

		if (session == null) {
			session = request.getSession(true);
		}

		String accountId = (String) session.getAttribute("account");

		List menuTree = securityService.getAccountMenus(accountId);

		request.setAttribute("menuTreeList", menuTree);

		return (mapping.findForward("success"));

	}

	/*--------------------------用户管理action方法-----------*/
	/**
	 * 
	 * 查询帐户
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward searchAccount(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'securityAction->listAccount' method");
		}
		ActionMessages messages = new ActionMessages();
		List roleList = securityService.findAllRole();
		request.setAttribute("roleList", roleList);
		// 处理查询条件
		// 用户名
		String para = request.getParameter("para");
		String roleId = request.getParameter("roleId");
		// 姓名
		String paraPersonName = request.getParameter("paraPersonName");
		// 起始页
		String page = request.getParameter("pager.offset");

		String[] args = { para, paraPersonName, page ,roleId};

		List accounts = null;
		Integer accountCount = new Integer(0);
		accounts = accountService.findAccount(args);
		accountCount = accountService.getAccountCount(args);

		request.setAttribute("accounts", accounts);
		request.setAttribute("accountCount", accountCount);

		return (mapping.findForward("success"));

	}

	/**
	 * 装载为了新增帐户
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward loadAccount4Add(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'securityAction->loadAccount4Add' method");
		}
		ActionMessages messages = new ActionMessages();
		Account account = new Account();

		account.getPerson().setSex("1");
		DynaValidatorForm aform = (DynaValidatorForm) form;
		aform.set("account", account);

		saveToken(request);

		return (mapping.findForward("input"));
	}

	/**
	 * 装载帐户为了更新帐户
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward loadAccount4Edit(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'securityAction->loadAccount4Edit' method");
		}
		ActionMessages errors = new ActionMessages();
		String accountId = (String) request.getParameter("id");

		if (MyUtils.isBlank(accountId)) {
			errors.add("account id is not empty", new ActionMessage(
					"errors.AccountIdNotEmpty"));
		}

		String offset = request.getParameter("offset");
		if (offset == null) {
			offset = "0";
		}

		Account account = accountService.findAccountById(accountId);

		if (account == null) {
			errors.add("update account",
					new ActionMessage("errors.UnKnowError"));
		} else {
			DynaValidatorForm aform = (DynaValidatorForm) form;
			account.setRepassword(account.getPassword());
			aform.set("account", account);
    	}

		if (!errors.isEmpty()) {
			saveErrors(request, errors);
			saveToken(request);

			return mapping.getInputForward();
		}

		return (mapping.findForward("edit"));
	}

	/**
	 * 增加帐户
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward addAccount(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'securityAction->addAccount' method");
		}
		ActionMessages errors = new ActionMessages();
		Account account = (Account) ((DynaActionForm) form).get("account");

		if (StringUtils.equals(request.getParameter("encryptPass"), "true")) {
			account.setPassword(MyUtils.toMD5(account.getPassword()));
			
		}
		
		account.getPerson().setCreatedate(DateUtil.getNow().substring(0,8));
		account.getPerson().setLastdate(DateUtil.getNow().substring(0,8));
		accountService.saveAccount(account);

		return (mapping.findForward("success"));
	}

	/**
	 * 更新帐户
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward editAccount(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'securityAction->loadPerson4Edit' method");
		}
		ActionMessages errors = new ActionMessages();
		Account account = (Account) ((DynaActionForm) form).get("account");

		if (StringUtils.equals(request.getParameter("encryptPass"), "true")) {
			account.setPassword(MyUtils.toMD5(account.getPassword()));
			
		}
		
		account.getPerson().setCreatedate(DateUtil.getNow().substring(0,8));
		account.getPerson().setLastdate(DateUtil.getNow().substring(0,8));
		
		accountService.updateAccount(account);

		return (mapping.findForward("success"));
	}

	/**
	 * 删除帐户
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward removeAccount(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'securityAction->loadPerson4Edit' method");
		}
		ActionMessages messages = new ActionMessages();

		String[] accountIds = request.getParameterValues("id");

		accountService.deleteAccount(accountIds);

		messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
				"account.deleted"));

		if (!messages.isEmpty()) {
			saveErrors(request, messages);
		}

		return (mapping.findForward("search"));
	}

	/**
	 * 装载为了改变密码
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward load4ChangePWD(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'securityAction->load4ChangePWD' method");
		}

		return (mapping.findForward("input"));
	}

	/**
	 * 修改帐户密码
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward changeAccountPWD(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'securityAction->changeAccountPWD' method");
		}
		ActionMessages errors = new ActionMessages();
		HttpSession session = request.getSession();
		// 原密码
		String oldPWD = (String) request.getParameter("oldPWD");
		// 新密码
		String newPWD = (String) request.getParameter("newPWD");

		String  accountId = (String)session.getAttribute("account");
		
		Account account = accountService.findAccountById(accountId);
	
			oldPWD = MyUtils.toMD5(oldPWD);
			
	        if(!oldPWD.equals(account.getPassword())){
	        	errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage("errors.oldpassword.mismatch"));
	        }
	        
	        if (!errors.isEmpty()) {
				saveErrors(request, errors);
				return (mapping.findForward("input"));
	        }
			
	        newPWD = MyUtils.toMD5(newPWD);
	        
	        account.setPassword(newPWD);
	        
	        accountService.updateAccount(account);
		
	        errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage("success.changepassword"));
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
	public ActionForward searchMenu(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'searchMenu' method");
		}

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
	public ActionForward loadMenu4Add(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'loadMenu4Add' method");
		}

		DynaActionForm menuForm = (DynaActionForm) form;

		// removeAttribute(mapping, request);

		Menu menu = new Menu();

		String menuPid = (String) request.getParameter("pid");
		if (menuPid != null) {
			menu.setPid(menuPid);
		}
		menuForm.set("menu", menu);
		menuForm.set("methodToCall", "add");

		return mapping.findForward("edit");
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
	public ActionForward loadMenu4Edit(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'loadMenu4Edit' method");
		}
		DynaActionForm menuForm = (DynaActionForm) form;

		Menu menu = (Menu) menuForm.get("menu");
		// HttpSession session = request.getSession();

		// Exceptions are caught by ActionExceptionHandler

		// Menu menu = null;
		String menuId = (String) request.getParameter("id");
		// if a menu's menuCode is passed in
		if (menuId != null) {
			// lookup the menu using that menuCode
			menu = (Menu) menuService.findMenuById(menuId);
		}

		menuForm.set("menu", menu);
		menuForm.set("methodToCall", "edit");

		// return a forward to edit forward
		return mapping.findForward("edit");
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
	public ActionForward addMenu(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'addMenu' method");
		}

		// Extract attributes and parameters we will need
		ActionMessages errors = new ActionMessages();
		ActionMessages messages = new ActionMessages();
		HttpSession session = request.getSession();
		Menu menu = (Menu) ((DynaActionForm) form).get("menu");
		log.debug("Menu bean : " + menu.getName());

		try {
			menuService.saveMenu(menu);
			// request.setAttribute("menuForm", menu);
		} catch (Exception e) {
			if ((e.getMessage() != null)
					&& (e.getMessage().indexOf("Duplicate entry") != -1)) {
				// user already exists!
				log.warn("Menu already exists: " + e.getMessage());
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"errors.existing.user", menu.getId(), menu.getName()));
				saveErrors(request, errors);
				((DynaActionForm) form).set("menu", menu);
				return mapping.findForward("edit");
			}

			e.printStackTrace();
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"errors.general"));

			while (e != null) {
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"errors.detail", e.getMessage()));
				e = (Exception) e.getCause();
			}

			saveErrors(request, errors);
			((DynaActionForm) form).set("menu", menu);

			return mapping.findForward("edit");
		}

		// if (!StringUtils.equals(request.getParameter("from"), "list")) {
		// session.setAttribute(Constants.MENU_KEY, menu);

		// add success messages
		// messages.add(ActionMessages.GLOBAL_MESSAGE,
		// new ActionMessage("menu.updated"));
		// saveMessages(request, messages);

		// return a forward to main Menu
		// return mapping.findForward("mainMenu");
		// } else {
		// add success messages
		if (menu.getId() == "") {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"menu.added", menu.getId()));
			session.setAttribute(Globals.MESSAGE_KEY, messages);

			return mapping.getInputForward();
		} else {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"menu.updated.byAdmin", menu.getId()));
			saveMessages(request, messages);
			return mapping.findForward("success");
		}
		// }
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
	public ActionForward updateMenu(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'updateMenu' method");
		}
		// Extract attributes and parameters we will need
		ActionMessages errors = new ActionMessages();
		ActionMessages messages = new ActionMessages();
		HttpSession session = request.getSession();
		Menu menu = (Menu) ((DynaActionForm) form).get("menu");
		log.debug("Menu bean : " + menu.getName());

		try {
			menuService.updateMenu(menu);
			// request.setAttribute("menuForm", menu);
		} catch (Exception e) {
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"errors.general"));

			while (e != null) {
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
						"errors.detail", e.getMessage()));
				e = (Exception) e.getCause();
			}

			saveErrors(request, errors);
			((DynaActionForm) form).set("menu", menu);
			request.setAttribute("menu", menu);
			return mapping.findForward("edit");
		}

		if (menu.getId() == "") {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"menu.added", menu.getId()));
			session.setAttribute(Globals.MESSAGE_KEY, messages);

			return mapping.getInputForward();
		} else {
			messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"menu.updated.byAdmin", menu.getId()));
			saveMessages(request, messages);
			return mapping.findForward("success");
		}
		// }
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
	public ActionForward cancelMenu(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'cancelMenu' method");
		}

		return mapping.findForward("search");

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
	public ActionForward deleteMenu(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'deleteMenu' method");
		}

		// Extract attributes and parameters we will need
		ActionMessages messages = new ActionMessages();

		Menu menu = (Menu) ((DynaActionForm) form).get("menu");

		String menuId = (String) request.getParameter("id");
		// Exceptions are caught by ActionExceptionHandler

		if (menuId != null) {
			menuService.removeMenu(menuId);
		}
		messages.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
				"menu.deleted", menu.getName()));

		saveMessages(request, messages);

		// return a forward to searching users
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
	public ActionForward getXMLMenuTree(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'getXMLMenu' method");
		}

		String menuTree = menuService.getXmlMenuTree();

		request.setAttribute("menuTree", menuTree);

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
	public ActionForward loadRole4GrantMenu(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'loadRole4GrantMenu' method");
		}

		List roles = securityService.findAllRole();
		request.setAttribute("roles", roles);

		return mapping.findForward("listRole");
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
	public ActionForward loadRoleMenu4Grant(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'loadRoleMenu4Grant' method");
		}

		String roleId = "";

		if (request.getParameter("id") != null) {

			roleId = request.getParameter("id");
			request.setAttribute("roleId", roleId);
		} else {
			//
		}

		// 设置用户已经有的菜单
		// init select string
		String roleMenus = "";

		String m_sCheckKey = ","; // checkdata 分隔符(返回值中)
		String sSelKey = "#$#$#$"; // 数据分隔符(显示值text与数据值value)

		// get role manager

		List roleMenu = securityService.getRoleMenus(roleId);

		for (Iterator it = roleMenu.iterator(); it.hasNext();) {
			Menu menu = (Menu) it.next();

			// convert the role's menus to string
			roleMenus += menu.getName() + sSelKey + menu.getId();
			roleMenus += m_sCheckKey;
		}

		request.setAttribute("roleMenus", roleMenus);

		return mapping.findForward("listRoleMenu");
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
	public ActionForward loadAllMenu4Grant(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'loadAllMenu4Grant' method");
		}
		return mapping.findForward("listAllMenu");
	}

	/**
	 * 授权角色菜单
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward grantRoleMenus(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'grantRoleMenu' method");
		}

		// 得到角色的编号和分配的菜单权限
		String roleId = "";
		String submitMenus;
		if (request.getParameter("roleId") != null) {
			roleId = request.getParameter("roleId");
		} else {

		}

		submitMenus = request.getParameter("submitMenus");

		// 如果提交的菜单为空，说明角色所有的菜单权限被删除

		// 保存给角色分配的菜单权限

		String temp[] = submitMenus.split(",");

		List roleMenus = new ArrayList();

		for (int i = 0; i < temp.length; i++) {

			Menu menu = new Menu();
			menu.setId(temp[i]);
			roleMenus.add(menu);
		}

		securityService.grantRoleMenus(roleId, roleMenus);
		return mapping.findForward("success");

	}

	/**
	 * 装载用户要授权的角色
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward loadAccountRole4Grant(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'loadAccountRole4Grant' method");
		}
		ActionMessages errors = new ActionMessages();

		String accountId = (String) request.getParameter("id");

		if (MyUtils.isBlank(accountId)) {
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
					"errors.general"));
			return (mapping.findForward("faile"));
		}
		Account account = accountService.findAccountById(accountId);

		List roles = securityService.findAllRole();
		Set currentAccountRoles = account.getRoles();
		List currentRole = new ArrayList();
		List availableRole = new ArrayList();

		if (currentAccountRoles != null) {
			for (Iterator iterator = currentAccountRoles.iterator(); iterator
					.hasNext();) {
				LabelValueBean lv = new LabelValueBean();
				Role role = (Role) iterator.next();
				lv.setLabel(role.getName());
				lv.setValue(role.getId());
				currentRole.add(lv);
			}
		}

		for (int i = 0; i < roles.size(); i++) {
			Role role = (Role) roles.get(i);
			if (!currentRole.contains(role)) {
				LabelValueBean lv = new LabelValueBean();
				lv.setLabel(role.getName());
				lv.setValue(role.getId());
				availableRole.add(lv);

			}
		}

		request.setAttribute("currentAccount", account);
		request.setAttribute("currentRole", currentRole);
		request.setAttribute("availableRole", availableRole);

		return mapping.findForward("listAccountRole");
	}

	public ActionForward grantAccountRole(ActionMapping mapping,
			ActionForm form, HttpServletRequest request,
			HttpServletResponse response) throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'grantAccountRole' method");
		}
		// 帐户id
		String accountId = (String) request.getParameter("id");
		String[] currentRole = request.getParameterValues("currentRole");

		securityService.grantAccountRoles(accountId, currentRole);

		return mapping.findForward("success");

	}

	// -------------------------角色管理－－－－－－－－－－－－－

	public ActionForward loadRole(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'loadRole' method");
		}
		ActionMessages errors = new ActionMessages();

		List roles = securityService.findAllRole();
		List resources = securityService.findAllResource();
		
		// Remove the obsolete form bean
		removeAttribute(mapping, request);
		
		request.setAttribute("roles", roles);
		request.setAttribute("resources", resources);
		
		
		return mapping.findForward("success");
	}

	public ActionForward loadRole4Edit(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'loadRole4Edit' method");
		}
		ActionMessages errors = new ActionMessages();

		Role role = null;
		List resources = null;

		String roleId = request.getParameter("id");

		role = securityService.findRoleById(roleId);
		resources = securityService.findAllResource();

		Map resourceList = new HashMap();

		for (int i = 0; i < resources.size(); i++) {
			resourceList.put(((Resource) resources.get(i)).getId(),
					(Resource) resources.get(i));
		}

		for (Iterator i = role.getResources().iterator(); i.hasNext();) {
			resourceList.remove(((Resource) i.next()).getId());
		}

		((DynaActionForm) form).set("role", role);
		request.getSession(false).setAttribute("resources",
				resourceList.values());
		request.getSession(false).setAttribute("removeresources",
				role.getResources());
		// List currentResource = role.get

		return mapping.findForward("edit");
	}

	public ActionForward addRole(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'addRole' method");
		}
		ActionMessages errors = new ActionMessages();

		Role role = (Role) ((DynaActionForm) form).get("role");
		String[] resources = request.getParameterValues("resource");
		resources = resources == null ? new String[0] : resources;

		securityService.saveRole(role, resources);

		return mapping.findForward("success");
	}

	public ActionForward updateRole(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'updateRole' method");
		}
		ActionMessages errors = new ActionMessages();
		String[] removeResource = request.getParameterValues("removeResource");
		String[] addResource = request.getParameterValues("addResource");
		Role role = (Role) ((DynaActionForm) form).get("role");

		try {
			securityService.updateRole(role, removeResource, addResource);
		} catch (BusinessException e) {
			log.error("update role error: ", e);
			errors.add("update role", new ActionMessage("errors.UnKnowError"));
		}

		if (!errors.isEmpty()) {
			saveErrors(request, errors);

			return mapping.findForward("faile");
		}

		removeAttribute(mapping, request);

		return (mapping.findForward("success"));
	}

	public ActionForward removeRole(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'removeRole' method");
		}
		ActionMessages errors = new ActionMessages();

		String[] ids = request.getParameterValues("id");

		securityService.removeRole(ids);

		return mapping.findForward("success");
	}

	// ----------------资源管理--------------------

	public ActionForward loadResource(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'loadResource' method");
		}
		ActionMessages errors = new ActionMessages();

		List resources = securityService.findAllResource();

		request.setAttribute("resources", resources);
		return mapping.findForward("success");
	}

	public ActionForward addResource(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'addResource' method");
		}
		ActionMessages errors = new ActionMessages();

		Resource resource = new Resource();

		try {
			BeanUtils.copyProperties(resource, form);
		} catch (Exception e) {
			log.error("copy form to resource error: " + e);
			errors.add("add resource", new ActionMessage("errors.UnKnowError"));
		}

		try {
			securityService.saveResource(resource);
		} catch (BusinessException e) {
			log.error("add resource error: " + e);
			errors.add("add resource", new ActionMessage("errors.UnKnowError"));
		} catch (ResourceAlreadyExistException e) {
			errors.add("add resource", new ActionMessage(
					"errors.ResourceAlreadyExist"));
		}

		if (!errors.isEmpty()) {
			saveErrors(request, errors);

			return mapping.findForward("faile");
		} else {
			removeAttribute(mapping, request);
			return (mapping.findForward("success"));
		}
	}

	public ActionForward updateResource(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'updateResource' method");
		}
		ActionMessages errors = new ActionMessages();

		String[] index = request.getParameterValues("index");
		String[] ids = request.getParameterValues("id");
		String[] codes = request.getParameterValues("code");
		String[] names = request.getParameterValues("name");
		String[] urls = request.getParameterValues("url");
		Resource[] resources = new Resource[index.length];
		int j = 0;

		for (int i = 0, n = index.length; i < n; i++) {
			j = Integer.parseInt(index[i]);
			resources[i] = new Resource();
			resources[i].setId(ids[j]);
			resources[i].setCode(codes[j]);
			resources[i].setName(names[j]);
			resources[i].setUrl(urls[j]);
		}

		try {
			securityService.updateResource(resources);
		} catch (BusinessException e) {
			log.error("update right error: ", e);
			errors.add("update right", new ActionMessage("errors.UnKnowError"));
		}

		if (!errors.isEmpty()) {
			saveErrors(request, errors);
		}

		removeAttribute(mapping, request);

		return (mapping.findForward("success"));
	}

	public ActionForward removeResource(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		if (log.isDebugEnabled()) {
			log.debug("Entering 'removeResource' method");
		}
		ActionMessages errors = new ActionMessages();

		String[] index = request.getParameterValues("index");
		String[] ids = request.getParameterValues("id");
		String[] resources = new String[index.length];
		int j = 0;

		for (int i = 0, n = index.length; i < n; i++) {
			j = Integer.parseInt(index[i]);
			resources[i] = ids[j];
		}

		try {
			securityService.deleteResource(resources);
		} catch (BusinessException e) {
			log.error("remove resource error: ", e);
			errors.add("remove resourc",
					new ActionMessage("errors.UnKnowError"));
		}

		if (!errors.isEmpty()) {
			saveErrors(request, errors);
		}

		return (mapping.findForward("success"));
	}

	public final ActionForward noRight(final ActionMapping mapping,
			final ActionForm form, final HttpServletRequest request,
			final HttpServletResponse response) throws Exception {
		ActionMessages errors = new ActionMessages();
		errors.add("no right", new ActionMessage("errors.NoRight"));

		// Remove the obsolete form bean
		removeAttribute(mapping, request);

		if (!errors.isEmpty()) {
			saveErrors(request, errors);
		}

		return mapping.findForward("success");
	}
	
	
	public final ActionForward searchSysOpLog(ActionMapping mapping,
			 ActionForm form,  HttpServletRequest request,
			 HttpServletResponse response) throws Exception {
		String beginDate = (String)request.getParameter("beginDate");
		if(beginDate==null||beginDate.equals("")){
			beginDate=org.king.framework.util.DateUtil.getToday();
		}
		String endDate = (String)request.getParameter("endDate");
		if(endDate==null||endDate.equals("")){
			endDate=org.king.framework.util.DateUtil.getToday();
		}
		String personCode = (String)request.getParameter("personCode");
		if(personCode==null){
			personCode="";
		}
		String personName = (String)request.getParameter("personName");
		if(personName==null){
			personName="";
		}
		String page = request.getParameter("pager.offset");
		if(page==null||page.equals("")){
			page = "0";
		}
		String maxPageItems = request.getParameter("maxPageItems");
		if(maxPageItems==null||maxPageItems.equals("")){
			maxPageItems = "10";
		}
			
		Map filterMap = new HashMap();
		filterMap.put("beginDate",beginDate);
		filterMap.put("endDate",endDate);
		filterMap.put("personCode",personCode);
		filterMap.put("personName",personName);
		
        List sysOpLogs = securityService.findSysOpLog(filterMap);
        Integer logCount = Integer.valueOf(String.valueOf(sysOpLogs.size()));
        
        List curSysOpLogs = new ArrayList();
        for(int i=Integer.parseInt(page),l=Math.min(i+Integer.parseInt(maxPageItems),logCount.intValue());i<l;i++){
        	curSysOpLogs.add(sysOpLogs.get(i));
        	
        }
        
        request.setAttribute("beginDate",beginDate);
        request.setAttribute("endDate",endDate);
        request.setAttribute("personCode",personCode);
        request.setAttribute("personName",personName);
        
        request.setAttribute("sysOpLogs",curSysOpLogs);
        request.setAttribute("logCount",logCount);
        
		return mapping.findForward("success");
	}

}
