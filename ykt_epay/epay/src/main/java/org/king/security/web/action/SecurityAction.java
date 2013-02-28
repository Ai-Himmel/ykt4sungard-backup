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

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.*;
import org.king.common.Constant;
import org.king.framework.util.DES;
import org.king.framework.util.MyUtils;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.TNetacc;
import org.king.security.domain.TOperator;
import org.king.security.domain.TShopacc;
import org.king.security.service.SecurityService;
import org.king.utils.DateUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.util.List;
import java.util.Map;

/**
 * <p>
 * SecurityAction.java
 * </p>
 * <p>
 * {功能说明}
 * </p>
 * <p/>
 * <p>
 * <a href="SecurityAction.java.html"><i>查看源代码</i></a>
 * </p>
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-20
 */

public class SecurityAction extends BaseAction {
	
	private static Log log = LogFactory.getLog(SecurityAction.class);

    private SecurityService securityService;

    public void setSecurityService(SecurityService securityService) {
        this.securityService = securityService;
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
    public ActionForward login(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        // 添加登陆逻辑
        HttpSession session = request.getSession(false);
        if (session == null) {
            session = request.getSession(true);
        }

        final String destinatedUrl = request.getParameter("DEST_URL");

        ActionMessages errors = new ActionMessages();
        DynaActionForm loginForm = (DynaActionForm) form;
        String accno = (String) loginForm.get("name");
        String password = (String) loginForm.get("password");
        String acctype = (String) loginForm.get("acctype");
        request.setAttribute("password", "");

        //1. 检查验证码
        if (session.getAttribute("chkCode") != null && !session.getAttribute("chkCode").equals(request.getParameter("chkCode"))) {
            errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage("errors.chkCodeNoMatch"));
            saveErrors(request, errors);
            return mapping.findForward("faile");
        }

        // 3.如果为持卡人账户登陆
        if (Constant.ACCOUT_TYPE_CARD.equals(acctype)) {
            TNetacc netacc = securityService.getNetaccByAccno(accno);

            // 3.1、如果账户不存在，登陆失败
            if (netacc == null) {
                savalog(accno, Constant.EPAY_ACC_LOG_LOGIN, "登陆失败，账户[" + accno + "]不存在", request);
                errors.add("User login", new ActionMessage("errors.LoginError.accnull"));
                saveErrors(request, errors);
                return mapping.findForward("faile");
            } else {
                String status = netacc.getStatus();// 账户状态
                // 3.2如果为未激活状态，登陆失败
                if (Constant.NETACC_STATUS_UNACTIVE.equals(status)) {
                    savalog(accno, Constant.EPAY_ACC_LOG_LOGIN, "登陆失败，账户["
                            + accno + "]未激活", request);
                    errors.add("User login", new ActionMessage(
                            "errors.LoginError.unactive"));
                    saveErrors(request, errors);
                    return mapping.findForward("faile");
                }
                // 3.3如果为锁定状态，登陆失败
                if (Constant.NETACC_STATUS_LOCKED.equals(status)) {
                    savalog(accno, Constant.EPAY_ACC_LOG_LOGIN, "登陆失败，账户["
                            + accno + "]已锁定", request);
                    errors.add("User login", new ActionMessage(
                            "errors.LoginError.locked"));
                    saveErrors(request, errors);
                    return mapping.findForward("faile");
                }
                // 3.4如果账户为正常状态
                if (Constant.NETACC_STATUS_NORMAL.equals(status)) {
                    String accpwd = netacc.getAccpwd();
                    // 3.4.1如果密码不正确，登陆失败
                    if (!accpwd.equals(MyUtils.toMD5(password))) {
                        Long failedcnt = netacc.getFailedcnt();
                        // 如果登陆失败次数为2，锁定账户
                        if (failedcnt == 2) {
                            netacc.setStatus(Constant.NETACC_STATUS_LOCKED);
                            netacc.setLastblocktime(DateUtil.getNow());
                        }
                        netacc.setFailedcnt(failedcnt + 1);
                        // 更新网络账户信息
                        securityService.updateTnetacc(netacc);
                        savalog(accno, Constant.EPAY_ACC_LOG_LOGIN,
                                "登陆失败，账户[" + accno + "]密码输入错误", request);
                        errors.add("User login", new ActionMessage(
                                "errors.LoginError.wrongPwd"));
                        saveErrors(request, errors);
                        return mapping.findForward("faile");

                    } else {
                        // 3.4.2正常登陆
                        netacc.setFailedcnt(0L);
                        session.setAttribute("lastlogintime", DateUtil.reFormatTime(netacc.getLastlogintime()));
                        netacc.setLastlogintime(DateUtil.getNow());
                        // 更新网络账户信息
                        securityService.updateTnetacc(netacc);

                        // 将登陆用户信息存入session
                        removeAttribute(mapping, request);
                        session.setAttribute("accno", accno);
                        session.setAttribute("acctype", acctype);
                        session.setAttribute("personName", netacc.getAccname());
                        if ((destinatedUrl != null)
                                && (destinatedUrl.length() > 0)) {
                            return new ActionForward(destinatedUrl);
                        } else {
                            return (mapping.findForward("success"));
                        }
                    }
                }
            }
        }

        // 4.如果为商户账户登陆
        if (Constant.ACCOUT_TYPE_SHOP.equals(acctype)) {
            TShopacc shopacc = securityService.getShopaccByAccno(accno);
            // 4.1、如果商户不存在，登陆失败
            if (shopacc == null) {
                savalog(accno, Constant.EPAY_ACC_LOG_LOGIN, "登陆失败，商户["
                        + accno + "]不存在", request);
                errors.add("User login", new ActionMessage(
                        "errors.LoginError.shopnull"));
                saveErrors(request, errors);
                return mapping.findForward("faile");
            } else {
                String accpwd = shopacc.getAccpwd();
                // 4.2如果密码不正确，登陆失败
                if (password != null && !MyUtils.toDes(password).equals(accpwd)) {
                    savalog(accno, Constant.EPAY_ACC_LOG_LOGIN, "登陆失败，商户["
                            + accno + "]密码输入错误", request);
                    errors.add("User login", new ActionMessage(
                            "errors.LoginError.wrongPwd"));
                    saveErrors(request, errors);
                    return mapping.findForward("faile");
                } else {
                    // 将登陆用户信息存入session
                    removeAttribute(mapping, request);
                    session.setAttribute("accno", accno);
                    session.setAttribute("acctype", acctype);
                    session.setAttribute("personName", shopacc.getAccname());
                    session.setAttribute("shopid", shopacc.getShopid());
                    // If there is a destinated url,forward to this url
                    if ((destinatedUrl != null) && (destinatedUrl.length() > 0)) {
                        return new ActionForward(destinatedUrl);
                    } else {
                        return (mapping.findForward("success"));
                    }
                }

            }
        }
        
       // 5.如果为操作员登陆
        if (Constant.ACCOUT_TYPE_OPER.equals(acctype)) {
        	TOperator operator = securityService.getOperBycode(accno);
            // 5.1、如果操作员不存在，登陆失败
            if (operator == null) {
                savalog(accno, Constant.EPAY_ACC_LOG_LOGIN, "登陆失败，操作员["
                        + accno + "]不存在", request);
                errors.add("User login", new ActionMessage(
                        "errors.LoginError.opernull"));
                saveErrors(request, errors);
                return mapping.findForward("faile");
            } else {
            	 String operpwd = operator.getOperpwd();
            	 String status = operator.getStatus();// 状态
            	 
            	 if(!Constant.OPER_STATUS_NORMAL.equals(status)){
            		  savalog(accno, Constant.EPAY_ACC_LOG_LOGIN, "登陆失败，操作员["
                              + accno + "]不是正常状态", request);
                      errors.add("User login", new ActionMessage(
                              "errors.LoginError.unnormal"));
                      saveErrors(request, errors);
                      return mapping.findForward("faile");
            	 }
            	 
                 // 5.2如果密码不正确，登陆失败
                 if (password != null && !DES.DESEnc(accno, password).equals(operpwd)) {
                     savalog(accno, Constant.EPAY_ACC_LOG_LOGIN, "登陆失败，操作员["
                             + accno + "]密码输入错误", request);
                     errors.add("User login", new ActionMessage(
                             "errors.LoginError.wrongPwd"));
                     saveErrors(request, errors);
                     return mapping.findForward("faile");
                 } else {
                	 // 将登陆用户信息存入session
                     removeAttribute(mapping, request);
                     session.setAttribute("accno", accno);
                     session.setAttribute("acctype", acctype);
                     session.setAttribute("personName", operator.getOpername());
                     // If there is a destinated url,forward to this url
                     if ((destinatedUrl != null) && (destinatedUrl.length() > 0)) {
                         return new ActionForward(destinatedUrl);
                     } else {
                         return (mapping.findForward("success"));
                     }
                 }
            }
            }

        errors.add("User login", new ActionMessage("errors.LoginError.untype"));
        saveErrors(request, errors);
        return mapping.findForward("faile");

    }

    public ActionForward activate(ActionMapping mapping, ActionForm form,
                                  HttpServletRequest request, HttpServletResponse response)
            throws Exception {
        HttpSession session = request.getSession(false);
        if (session == null) {
            session = request.getSession(true);
        }
        ActionMessages errors = new ActionMessages();
        String account = request.getParameter("account");
        String activatecode = request.getParameter("activatecode");
        String accpwd1 = request.getParameter("accpwd1");
        String paypwd1 = request.getParameter("paypwd1");
        // 检查验证码
        if (!session.getAttribute("chkCode").equals(
                request.getParameter("checkcode"))) {
            errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
                    "errors.chkCodeNoMatch"));
            saveErrors(request, errors);
            return mapping.findForward("faile");
        }
        if (securityService.actiCheckActivate(account, activatecode)) {
            if (securityService.activate(account, accpwd1, paypwd1,
                    activatecode, request.getRemoteAddr())) {
                savalog(account, "5", "激活成功", request);
                errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
                        "errors.activatesuccess"));
                saveErrors(request, errors);
                return mapping.findForward("success");
            } else {
                savalog(account, "5", "激活失败", request);
                errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
                        "errors.activatefaile"));
                saveErrors(request, errors);
                return mapping.findForward("faile");
            }
        } else {
            savalog(account, "5", "激活失败", request);
            errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
                    "errors.activateaccounterrors"));
            saveErrors(request, errors);
            return mapping.findForward("faile");
        }
    }

    public  ActionForward findacc(ActionMapping mapping, ActionForm form,
            HttpServletRequest request, HttpServletResponse response){
    	HttpSession session = request.getSession(false);
        if (session == null) {
            session = request.getSession(true);
        }
        ActionMessages errors = new ActionMessages();
    	String xh = request.getParameter("xh");
    	request.setAttribute("xh",xh);
    	String pwd = request.getParameter("pwd");
    	if(xh!=null&&pwd!=null){
    		if (!session.getAttribute("chkCode").equals(
                    request.getParameter("checkcode"))) {
                errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage(
                        "errors.chkCodeNoMatch"));
                saveErrors(request, errors);
                return mapping.findForward("findacc");
            }
    		List l = securityService.getacc(xh, pwd);
        	if(l!=null&&l.size()>0){
        		Map m = (Map)l.get(0);
        		String st = m.get("status")==null?"":m.get("status").toString();
        		request.setAttribute("accname", m.get("accname"));
        		request.setAttribute("netaccno", m.get("accno"));
        		request.setAttribute("stutes", "1".equals(st)?"正常":"未激活");
        		request.setAttribute("emflag","1");
        		return mapping.findForward("findacc");
        	}else{
        		errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionMessage("errors.findempty"));
        		saveErrors(request, errors);
        		return mapping.findForward("findacc");
        	}
    	}else{
    		return mapping.findForward("findacc");
    	}
	}
    public final ActionForward logout(final ActionMapping mapping,
                                      final ActionForm form, final HttpServletRequest request,
                                      final HttpServletResponse response) throws Exception {
        // todo 添加注销逻辑
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
        String acctype = (String) session.getAttribute("acctype");
        List menuTree = securityService.getAccountMenus(acctype);
        request.setAttribute("menuTreeList", menuTree);
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


    /**
     * 得到登陆用户的账户信息
     *
     * @param mapping
     * @param form
     * @param request
     * @param response
     * @return
     * @throws Exception
     */
    public ActionForward getLoginNetAcc(ActionMapping mapping, ActionForm form,
                                        HttpServletRequest request, HttpServletResponse response)
            throws Exception {
        HttpSession session = request.getSession(false);
        if (session == null) {
            session = request.getSession(true);
        }
        String accno = (String) session.getAttribute("accno");
        TNetacc tNetacc = securityService.getNetaccByAccno(accno);
        request.setAttribute("tNetacc", tNetacc);
        return (mapping.findForward("success"));
    }

    /**
     * 得到登陆用户的商户账户信息
     *
     * @param mapping
     * @param form
     * @param request
     * @param response
     * @return
     * @throws Exception
     */
    public ActionForward getLoginShopAcc(ActionMapping mapping, ActionForm form,
                                         HttpServletRequest request, HttpServletResponse response)
            throws Exception {
        HttpSession session = request.getSession(false);
        if (session == null) {
            session = request.getSession(true);
        }
        String accno = (String) session.getAttribute("accno");
        TShopacc tShopacc = securityService.getShopaccByAccno(accno);
        request.setAttribute("tShopacc", tShopacc);
        return (mapping.findForward("success"));
    }
    
    /**
     * 获取登陆用户的操作员信息
     *
     * @param mapping
     * @param form
     * @param request
     * @param response
     * @return
     * @throws Exception
     */
    public ActionForward getLoginOper(ActionMapping mapping, ActionForm form,
                                         HttpServletRequest request, HttpServletResponse response)
            throws Exception {
        HttpSession session = request.getSession(false);
        if (session == null) {
            session = request.getSession(true);
        }
        String operCode = (String) session.getAttribute("accno");
        TOperator operator = securityService.getOperBycode(operCode);
        request.setAttribute("operator", operator);
        return (mapping.findForward("success"));
    }
    
}
