/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.kingstargroup.ecard.portlet.login.action;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.liferay.portal.CookieNotSupportedException;
import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.PasswordExpiredException;
import com.liferay.portal.UserEmailAddressException;
import com.liferay.portal.UserIdException;
import com.liferay.portal.UserLockoutException;
import com.liferay.portal.UserPasswordException;
import com.liferay.portal.UserScreenNameException;
import com.liferay.portal.captcha.CaptchaTextException;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.User;
import com.liferay.portal.mycaptcha.CaptchaServiceSingleton;
import com.liferay.portal.security.auth.AuthException;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.servlet.SessionErrors;
import com.octo.captcha.service.CaptchaServiceException;
import com.sungard.Verify.IVerify;
import com.sungard.Verify.VerifyManager;

/**
 * <a href="ViewAction.java.html"><b><i>View Source</i></b></a>
 * 
 * @author Brian Wing Shun Chan
 * 
 */
public class ViewAction extends PortletAction {

	public void processAction(ActionMapping mapping, ActionForm form,
			PortletConfig config, ActionRequest req, ActionResponse res)
			throws Exception {
		String cmd = req.getParameter(Constants.CMD);
		String scode=req.getParameter("scode");

		ThemeDisplay themeDisplay = (ThemeDisplay) req
				.getAttribute(WebKeys.THEME_DISPLAY);

		if (req.getRemoteUser() != null) {
			String path = PropsValues.DEFAULT_LANDING_PAGE_PATH;
			User user = PortalUtil.getUser(req);
			if (user != null) {
				path = "/web/" + user.getScreenName() + "/1";
			}
			res.sendRedirect(path);
		} else if ("sso".equals(cmd)) {
			try {	
				if("SHITAC".equalsIgnoreCase(scode)){
					loginSHITACSSO(themeDisplay, req, res);
				}else{
					loginNJUSSO(themeDisplay, req, res);
				}
			} catch (Exception e) {
				if (e instanceof AuthException) {
					Throwable cause = e.getCause();
					if (cause instanceof PasswordExpiredException
							|| cause instanceof UserLockoutException) {
						SessionErrors.add(req, cause.getClass().getName());
					} else {
						SessionErrors.add(req, e.getClass().getName());
					}
				} else if (e instanceof CookieNotSupportedException
						|| e instanceof NoSuchUserException
						|| e instanceof PasswordExpiredException
						|| e instanceof UserEmailAddressException
						|| e instanceof UserIdException
						|| e instanceof UserLockoutException
						|| e instanceof UserPasswordException
						|| e instanceof UserScreenNameException
						|| e instanceof CaptchaTextException) {

					SessionErrors.add(req, e.getClass().getName());
				} else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, ActionConstants.COMMON_ERROR);
				}
			}
		} else if (Validator.isNotNull(cmd)) {
			try {
				login(themeDisplay, req, res);
			} catch (Exception e) {
				if (e instanceof AuthException) {
					Throwable cause = e.getCause();
					if (cause instanceof PasswordExpiredException
							|| cause instanceof UserLockoutException) {
						SessionErrors.add(req, cause.getClass().getName());
					} else {
						SessionErrors.add(req, e.getClass().getName());
					}
				} else if (e instanceof CookieNotSupportedException
						|| e instanceof NoSuchUserException
						|| e instanceof PasswordExpiredException
						|| e instanceof UserEmailAddressException
						|| e instanceof UserIdException
						|| e instanceof UserLockoutException
						|| e instanceof UserPasswordException
						|| e instanceof UserScreenNameException
						|| e instanceof CaptchaTextException) {

					SessionErrors.add(req, e.getClass().getName());
				} else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, ActionConstants.COMMON_ERROR);
				}
			}
		}
	}

	public ActionForward render(ActionMapping mapping, ActionForm form,
			PortletConfig config, RenderRequest req, RenderResponse res)
			throws Exception {
			return mapping.findForward("extportlet.login.view");		
	}

	protected void login(ThemeDisplay themeDisplay, ActionRequest req,
			ActionResponse res) throws Exception {

		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);
		HttpServletResponse httpRes = PortalUtil.getHttpServletResponse(res);

		String login = ParamUtil.getString(req, "login");
		String password = ParamUtil.getString(req, "password");
		boolean rememberMe = ParamUtil.getBoolean(req, "rememberMe");

		// CaptchaUtil.check(httpReq);

		/*
		 * 检查验证码是否正确
		 * 
		 * HttpSession ses = httpReq.getSession(); String authCode =
		 * ParamUtil.getString(req, "authCode"); Captcha captcha = (Captcha)
		 * ses.getAttribute("CAPTCHA"); if(null==captcha){
		 * System.out.println("captcha is null now!"); }else{ Boolean
		 * validResponse = captcha.validateResponse(authCode); if
		 * ((validResponse == null) || (validResponse.equals(Boolean.FALSE))) {
		 * System.out.println("*******possible?");
		 * ses.removeAttribute("CAPTCHA"); throw new ValidAuthCodeException(); } }
		 * 
		 */
		Boolean isResponseCorrect = Boolean.FALSE;
		// remenber that we need an id to validate!
		String captchaId = httpReq.getSession().getId();
		// retrieve the response
		String response = httpReq.getParameter("authCode");
		// Call the Service method
		try {
			System.out.println("captchaId" + captchaId);
			isResponseCorrect = CaptchaServiceSingleton.getInstance()
					.validateResponseForID(captchaId, response);
		} catch (CaptchaServiceException e) {
			// should not happen, may be thrown if the id is not valid
			e.printStackTrace();
			throw new CaptchaTextException();
		}

		if ((isResponseCorrect == null)
				|| (isResponseCorrect.equals(Boolean.FALSE))) {
			// ses.removeAttribute("CAPTCHA");
			throw new CaptchaTextException();
		}

		/*
		 * 检查完毕
		 */

		LoginAction.login(httpReq, httpRes, login, password, rememberMe);

		if (PropsValues.PORTAL_JAAS_ENABLE) {
			res.sendRedirect(themeDisplay.getPathMain() + "/portal/protected");
		} else {
			res.sendRedirect(themeDisplay.getPathMain());
		}
	}

	/**
	 * Method name:loginNJUSSO
	 * Description:  南京大学sso对接模块 
	 * Return: void
	 * @param themeDisplay
	 * @param req
	 * @param res
	 * @throws Exception
	 */
	protected void loginNJUSSO(ThemeDisplay themeDisplay, ActionRequest req,
			ActionResponse res) throws Exception {

		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);
		HttpServletResponse httpRes = PortalUtil.getHttpServletResponse(res);
		httpReq.setCharacterEncoding("UTF-8");
		String un = ParamUtil.getString(req, "un");
		String time = ParamUtil.getString(req, "time");
		String verify = ParamUtil.getString(req, "verify");

		/*
		 * 检查完毕
		 */

		LoginAction.loginNJUSSO(httpReq, httpRes, un, time, verify);

		if (PropsValues.PORTAL_JAAS_ENABLE) {
			res.sendRedirect(themeDisplay.getPathMain() + "/portal/protected");
		} else {
			res.sendRedirect(themeDisplay.getPathMain());
		}
	}
	
	/**
	 * Method name:loginCSGLSSO
	 * Description:重庆城市管理学院与数字化校园的对接   
	 * Return: void
	 * @param themeDisplay
	 * @param req
	 * @param res
	 * @throws Exception
	 */
	protected void loginCSGLSSO(ThemeDisplay themeDisplay, ActionRequest req,
			ActionResponse res) throws Exception {

		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);
		HttpServletResponse httpRes = PortalUtil.getHttpServletResponse(res);
		/*
		 * 检查完毕
		 */
		System.out.println("sso login");
		String un="";
		if("".equals(un)){
		com.sungard.beans.User ssouser = new com.sungard.beans.User();
		try {
			IVerify verify = (IVerify)VerifyManager.CreateVerify();			
			if(verify.CheckLogin(ssouser, httpReq)){
				un= ssouser.get_account()==null?"":ssouser.get_account().trim();
			}else{
				throw new UserIdException();
			}
		} catch (Exception e) {
			e.printStackTrace();
			throw new UserIdException();
		}
		}
		if(!"".equals(un)){
    		//学工号不存在
			LoginAction.loginCSGLSSO(httpReq, httpRes,un);
    	}else{
    		throw new UserIdException();
    	}
		

		if (PropsValues.PORTAL_JAAS_ENABLE) {
			res.sendRedirect(themeDisplay.getPathMain() + "/portal/protected");
		} else {
			res.sendRedirect(themeDisplay.getPathMain());
		}
	}
	
	/**
	 * Method name:loginCSGLSSO
	 * Description:上海信息技术学院与数字化校园的对接   
	 * Return: void
	 * @param themeDisplay
	 * @param req
	 * @param res
	 * @throws Exception
	 */
	protected void loginSHITACSSO(ThemeDisplay themeDisplay, ActionRequest req,
			ActionResponse res) throws Exception {

		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);
		HttpServletResponse httpRes = PortalUtil.getHttpServletResponse(res);
		httpReq.setCharacterEncoding("UTF-8");
		String un = ParamUtil.getString(req, "un");
		String time = ParamUtil.getString(req, "time");
		String verify = ParamUtil.getString(req, "verify");
		String key = ParamUtil.getString(req, "key");

		/*
		 * 检查完毕
		 */

		LoginAction.loginSHITACSSO(httpReq, httpRes, un, time, verify, key);

		if (PropsValues.PORTAL_JAAS_ENABLE) {
			res.sendRedirect(themeDisplay.getPathMain() + "/portal/protected");
		} else {
			res.sendRedirect(themeDisplay.getPathMain());
		}
	}
		
	
	protected boolean isCheckMethodOnProcessAction() {
		return _CHECK_METHOD_ON_PROCESS_ACTION;
		}

	private static final boolean _CHECK_METHOD_ON_PROCESS_ACTION = false;



}