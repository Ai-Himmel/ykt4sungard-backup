/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portal.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.exceptions.ValidAuthCodeException;
import com.kingstargroup.ecard.hibernate.util.AccountUtil;
import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SendPasswordException;
import com.liferay.portal.SystemException;
import com.liferay.portal.UserEmailAddressException;
import com.liferay.portal.UserIdException;
import com.liferay.portal.UserPasswordException;
import com.liferay.portal.auth.AuthException;
import com.liferay.portal.auth.Authenticator;
import com.liferay.portal.auth.PrincipalFinder;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.User;
import com.liferay.portal.service.spring.UserLocalServiceUtil;
import com.liferay.portal.service.spring.UserServiceUtil;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.EncryptorException;
import com.liferay.util.InstancePool;
import com.liferay.util.ParamUtil;
import com.liferay.util.ServerDetector;
import com.liferay.util.Validator;
import com.liferay.util.Xss;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;
import com.octo.captcha.Captcha;

/**
 * <a href="LoginAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.9 $
 *
 */
public class LoginAction extends Action {
    
	//这个类干什么?
	public static String getLogin(
		HttpServletRequest req, String paramName, Company company) {

		String login = ParamUtil.getString(req, paramName);
		/*never get login name from cookie
		if ((login == null) || (login.equals(StringPool.NULL))) {
			login = GetterUtil.getString(
				CookieUtil.get(req.getCookies(), CookieKeys.LOGIN));

			if (Validator.isNull(login) &&
				company.getAuthType().equals(Company.AUTH_TYPE_EA)) {

				login = "@" + company.getMx();
			}
		}*/

		login = Xss.strip(login);//login取得的是什么???

		return login;
	}

	public static void login(
			HttpServletRequest req, HttpServletResponse res, String login,
			String password, boolean rememberMe)
		throws Exception {

		HttpSession ses = req.getSession();
		/*
		 * 检查验证码是否正确
		 */
		String authCode = ParamUtil.getString(req, "authCode");
		Captcha captcha = (Captcha) ses.getAttribute(WebKeys.CAPTCHA);
		if(null==captcha){
			System.out.println("captcha is null now!");
		}else{
			Boolean validResponse = captcha.validateResponse(authCode);	
			if ((validResponse == null) ||
					(validResponse.equals(Boolean.FALSE))) {
				System.out.println("*******possible?");
				ses.removeAttribute(WebKeys.CAPTCHA);			
				throw new ValidAuthCodeException();
			}
		}
		/*
		 * 检查完毕
		 */
		System.out.println("******************here go**************");
		String userId = login;

		int authResult = Authenticator.FAILURE;

		Company company = PortalUtil.getCompany(req);//这是取得什么?

		if (company.getAuthType().equals(Company.AUTH_TYPE_EA)) {//判断什么?
			authResult = UserServiceUtil.authenticateByEmailAddress( //这个是实现什么功能?
				company.getCompanyId(), login, password);

			userId = UserServiceUtil.getUserId(company.getCompanyId(), login);
		}
		else {
			authResult = UserServiceUtil.authenticateByUserId(//这个是实现什么功能?
				company.getCompanyId(), login, password);
		}
		try {//这个实现什么功能?
			PrincipalFinder principalFinder =
				(PrincipalFinder)InstancePool.get(
					PropsUtil.get(PropsUtil.PRINCIPAL_FINDER));

			userId = principalFinder.fromLiferay(userId);
		}
		catch (Exception e) {
		}
		System.out.println("******************"+login+"="+authResult+"**************");
		if (authResult == Authenticator.SUCCESS) {
			User user = UserLocalServiceUtil.getUserById(userId);

			ses.setAttribute("j_username", userId);
			ses.setAttribute("j_password", user.getPassword());

			ses.setAttribute(WebKeys.USER_PASSWORD, password);
			
			//ignore jaas
			ses.setAttribute(WebKeys.USER_ID, userId);
			//登录日志
			try {
				AccountUtil.loginInfo(userId);
			} catch (Exception e) {
				// TODO: handle exception
			}
			
			/* we do not need cookie
			Cookie idCookie = new Cookie(
				CookieKeys.ID,
				UserServiceUtil.encryptUserId(userId));
			idCookie.setPath("/");

			Cookie passwordCookie = new Cookie(
				CookieKeys.PASSWORD,
				Encryptor.encrypt(company.getKeyObj(), password));
			passwordCookie.setPath("/");			
			if (rememberMe) {
				idCookie.setMaxAge(CookieKeys.MAX_AGE);
				passwordCookie.setMaxAge(CookieKeys.MAX_AGE);
			}
			else {
				idCookie.setMaxAge(0);
				passwordCookie.setMaxAge(0);
			}
			
			Cookie loginCookie = new Cookie(CookieKeys.LOGIN, login);
			loginCookie.setPath("/");
			loginCookie.setMaxAge(CookieKeys.MAX_AGE);

			res.addCookie(idCookie);
			res.addCookie(passwordCookie);
			res.addCookie(loginCookie);
			*/
		}
		else {
//			all exception remove captcha key
			req.getSession().removeAttribute(WebKeys.CAPTCHA);
			throw new AuthException();
		}
	}
    //这个类干什么？?
	public static void processAuthenticatedUser(
			HttpServletRequest req, HttpServletResponse res, Company company,
			String login, String userId, String password, boolean rememberMe)
		throws EncryptorException, PortalException, SystemException {

		HttpSession ses = req.getSession();

		User user = UserLocalServiceUtil.getUserById(userId);

		ses.setAttribute("j_username", userId);
		ses.setAttribute("j_password", user.getPassword());

		ses.setAttribute(WebKeys.USER_PASSWORD, password);
		/*we don't need cookie
		Cookie idCookie = new Cookie(
			CookieKeys.ID,
			UserServiceUtil.encryptUserId(userId));
		idCookie.setPath("/");

		Cookie passwordCookie = new Cookie(
			CookieKeys.PASSWORD,
			Encryptor.encrypt(company.getKeyObj(), password));
		passwordCookie.setPath("/");

		if (rememberMe) {
			idCookie.setMaxAge(CookieKeys.MAX_AGE);
			passwordCookie.setMaxAge(CookieKeys.MAX_AGE);
		}
		else {
			idCookie.setMaxAge(0);
			passwordCookie.setMaxAge(0);
		}

		Cookie loginCookie = new Cookie(CookieKeys.LOGIN, login);
		loginCookie.setPath("/");
		loginCookie.setMaxAge(CookieKeys.MAX_AGE);

		res.addCookie(idCookie);
		res.addCookie(passwordCookie);
		res.addCookie(loginCookie);*/
	}

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		HttpSession ses = req.getSession();

		if (ses.getAttribute("j_username") != null &&
			ses.getAttribute("j_password") != null) {
             //
			if (ServerDetector.isOrion() || ServerDetector.isRexIP()) {//此处的判断是什么意思?

				// Post to j_security

				return mapping.findForward("/portal/j_login.jsp");//此页面是干什么用的?
			}
			else {

				// Touch protected resource

				return mapping.findForward("/portal/touch_protected.jsp");//此页面干什么用的?
			}
		}

		String cmd = req.getParameter("my_account_cmd");//这是取得什么？

		if ((cmd != null) && (cmd.equals("auth"))) {
			try {
				_login(req, res);//?

				if (ServerDetector.isOrion() || ServerDetector.isRexIP()) {

					// Post to j_security
					return mapping.findForward("/portal/touch_protected.jsp");//这个页面做什么？
					//return mapping.findForward("/portal/j_login.jsp");
				}
				else {

					// Touch protected resource

					return mapping.findForward("/portal/touch_protected.jsp");//这个和if语句的转向是一样?
				}
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof AuthException ||
					e instanceof NoSuchUserException ||
					e instanceof UserEmailAddressException ||
					e instanceof UserIdException ||
					e instanceof UserPasswordException ||
					e instanceof ValidAuthCodeException) {

					SessionErrors.add(req, e.getClass().getName());
					//all exception remove captcha key
					req.getSession().removeAttribute(WebKeys.CAPTCHA);
					return mapping.findForward("portal.login");
				}
				else {
//					all exception remove captcha key
					req.getSession().removeAttribute(WebKeys.CAPTCHA);
					req.setAttribute(PageContext.EXCEPTION, e);

					return mapping.findForward(Constants.COMMON_ERROR);
				}
			}
		}
		else if ((cmd != null) && (cmd.equals("send"))) {
			try {
				_sendPassword(req);

				return mapping.findForward("portal.login");//这个页面做什么处理?
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof NoSuchUserException ||
					e instanceof SendPasswordException ||
					e instanceof UserEmailAddressException) {

					SessionErrors.add(req, e.getClass().getName());

					return mapping.findForward("portal.login");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					return mapping.findForward(Constants.COMMON_ERROR);
				}
			}
		}
		else {
			return mapping.findForward("portal.login");
		}
	}
    
	   //这个类干什么用？
	private void _login(HttpServletRequest req, HttpServletResponse res)
		throws Exception {

		String login = ParamUtil.getString(
			req, "my_account_login").toLowerCase();//这是什么意思?在那个页面定义?

		String password = null;
		/*ParamUtil.getString(
			req, SessionParameters.get(req, "my_account_password"));*/
		if (Validator.isNull(password)) {
			password = ParamUtil.getString(req, "my_account_password");//my_account_password在那个页面定义?
		}

		boolean rememberMe = ParamUtil.get(req, "my_account_r_m", false);//my_account_r_m是什么意思?在那个页面定义?
		login(req, res, login, password, rememberMe);
		
	}
    //这个类干什么用？
	private void _sendPassword(HttpServletRequest req) throws Exception {
		String emailAddress = ParamUtil.getString(
			req, "my_account_email_address");

		UserServiceUtil.sendPassword(
			PortalUtil.getCompanyId(req), emailAddress);

		SessionMessages.add(req, "new_password_sent", emailAddress);
	}

}