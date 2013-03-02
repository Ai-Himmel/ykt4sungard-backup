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

import java.util.ArrayList;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.servlet.jsp.PageContext;

import org.apache.commons.codec.digest.DigestUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.util.DateUtil;
import com.kingstargroup.ecard.util.SimpleEncoding;
import com.liferay.portal.CookieNotSupportedException;
import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.PasswordExpiredException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SendPasswordException;
import com.liferay.portal.SystemException;
import com.liferay.portal.UserEmailAddressException;
import com.liferay.portal.UserIdException;
import com.liferay.portal.UserLockoutException;
import com.liferay.portal.UserPasswordException;
import com.liferay.portal.UserScreenNameException;
import com.liferay.portal.captcha.CaptchaTextException;
import com.liferay.portal.kernel.servlet.HttpHeaders;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.CompanyImpl;
import com.liferay.portal.security.auth.AuthException;
import com.liferay.portal.security.auth.Authenticator;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.struts.LastPath;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.CookieKeys;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.CookieUtil;
import com.liferay.util.Encryptor;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;
import com.liferay.util.servlet.SessionParameters;

/**
 * <a href="LoginAction.java.html"><b><i>View Source</i></b></a>
 * 
 * @author Brian Wing Shun Chan
 * @author Scott Lee
 * 
 */
public class LoginAction extends Action {

	public static String getLogin(HttpServletRequest req, String paramName,
			Company company) throws PortalException, SystemException {

		String login = req.getParameter(paramName);

		if ((login == null) || (login.equals(StringPool.NULL))) {
			login = GetterUtil.getString(CookieUtil.get(req.getCookies(),
					CookieKeys.LOGIN));

			if (Validator.isNull(login)
					&& company.getAuthType().equals(CompanyImpl.AUTH_TYPE_EA)) {

				login = "@" + company.getMx();
			}
		}

		return login;
	}

	public static void login(HttpServletRequest req, HttpServletResponse res,
			String login, String password, boolean rememberMe) throws Exception {

		CookieKeys.validateSupportCookie(req);

		HttpSession ses = req.getSession();

		login = login.trim().toUpperCase();// ת�ɴ�д

		long userId = GetterUtil.getLong(login);

		int authResult = Authenticator.FAILURE;

		Company company = PortalUtil.getCompany(req);

		Map headerMap = new HashMap();

		Enumeration enu1 = req.getHeaderNames();

		while (enu1.hasMoreElements()) {
			String name = (String) enu1.nextElement();

			Enumeration enu2 = req.getHeaders(name);

			List headers = new ArrayList();

			while (enu2.hasMoreElements()) {
				String value = (String) enu2.nextElement();

				headers.add(value);
			}

			headerMap.put(name, (String[]) headers.toArray(new String[0]));
		}

		Map parameterMap = req.getParameterMap();

		if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_EA)) {
			authResult = UserLocalServiceUtil.authenticateByEmailAddress(
					company.getCompanyId(), login, password, headerMap,
					parameterMap);

			userId = UserLocalServiceUtil.getUserIdByEmailAddress(company
					.getCompanyId(), login);
		} else if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_SN)) {
			authResult = UserLocalServiceUtil.authenticateByScreenName(company
					.getCompanyId(), login, password, headerMap, parameterMap);
			if (authResult >= 0) {
				userId = UserLocalServiceUtil.getUserIdByScreenName(company
						.getCompanyId(), login);
			}
		} else if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_ID)) {
			authResult = UserLocalServiceUtil.authenticateByUserId(company
					.getCompanyId(), userId, password, headerMap, parameterMap);
		}

		if (authResult > Authenticator.DNE) {
			if (PropsValues.SESSION_ENABLE_PHISHING_PROTECTION) {

				// Invalidate the previous session to prevent phishing

				Boolean httpsInitial = (Boolean) ses
						.getAttribute(WebKeys.HTTPS_INITIAL);

				LastPath lastPath = (LastPath) ses
						.getAttribute(WebKeys.LAST_PATH);

				try {
					ses.invalidate();
				} catch (IllegalStateException ise) {

					// This only happens in Geronimo

					if (_log.isWarnEnabled()) {
						_log.warn(ise.getMessage());
					}
				}

				ses = req.getSession(true);

				if (httpsInitial != null) {
					ses.setAttribute(WebKeys.HTTPS_INITIAL, httpsInitial);
				}

				if (lastPath != null) {
					ses.setAttribute(WebKeys.LAST_PATH, lastPath);
				}
			}

			// Set cookies

			String domain = CookieKeys.getDomain(req);

			User user = UserLocalServiceUtil.getUserById(userId);

			String userIdString = String.valueOf(userId);
			ses.setAttribute("j_status", authResult);
			ses.setAttribute("j_screenname", login);
			ses.setAttribute("j_username", userIdString);
			ses.setAttribute("j_password", user.getPassword());
			ses.setAttribute("j_remoteuser", userIdString);
 
			ses.setAttribute(WebKeys.USER_PASSWORD, password);

			Cookie companyIdCookie = new Cookie(CookieKeys.COMPANY_ID, String
					.valueOf(company.getCompanyId()));

			if (Validator.isNotNull(domain)) {
				companyIdCookie.setDomain(domain);
			}

			companyIdCookie.setPath(StringPool.SLASH);

			Cookie idCookie = new Cookie(CookieKeys.ID, UserLocalServiceUtil
					.encryptUserId(userIdString));

			if (Validator.isNotNull(domain)) {
				idCookie.setDomain(domain);
			}

			idCookie.setPath(StringPool.SLASH);

			Cookie passwordCookie = new Cookie(CookieKeys.PASSWORD, Encryptor
					.encrypt(company.getKeyObj(), password));

			if (Validator.isNotNull(domain)) {
				passwordCookie.setDomain(domain);
			}

			passwordCookie.setPath(StringPool.SLASH);

			int loginMaxAge = PropsValues.COMPANY_SECURITY_AUTO_LOGIN_MAX_AGE;

			if (PropsValues.SESSION_DISABLED) {
				rememberMe = true;
			}

			if (rememberMe) {
				companyIdCookie.setMaxAge(loginMaxAge);
				idCookie.setMaxAge(loginMaxAge);
				passwordCookie.setMaxAge(loginMaxAge);
			} else {

				// This was explicitly changed from 0 to -1 so that the cookie
				// lasts as long as the browser. This allows an external servlet
				// wrapped in AutoLoginFilter to work throughout the client
				// connection. The cookies ARE removed on an actual logout, so
				// there is no security issue. See LEP-4678.

				companyIdCookie.setMaxAge(-1);
				idCookie.setMaxAge(-1);
				passwordCookie.setMaxAge(-1);
			}

			Cookie loginCookie = new Cookie(CookieKeys.LOGIN, login);

			if (Validator.isNotNull(domain)) {
				loginCookie.setDomain(domain);
			}

			loginCookie.setMaxAge(loginMaxAge);
			loginCookie.setPath(StringPool.SLASH);

			Cookie screenNameCookie = new Cookie(CookieKeys.SCREEN_NAME,
					Encryptor
							.encrypt(company.getKeyObj(), user.getScreenName()));

			if (Validator.isNotNull(domain)) {
				screenNameCookie.setDomain(domain);
			}

			screenNameCookie.setMaxAge(loginMaxAge);
			screenNameCookie.setPath(StringPool.SLASH);

			CookieKeys.addCookie(res, companyIdCookie);
			CookieKeys.addCookie(res, idCookie);
			CookieKeys.addCookie(res, passwordCookie);
			CookieKeys.addCookie(res, loginCookie);
			CookieKeys.addCookie(res, screenNameCookie);
		} else {
			throw new AuthException();
		}
	}

	public static void loginNJUSSO(HttpServletRequest req,
			HttpServletResponse res, String un, String time, String verify)
			throws Exception {

		CookieKeys.validateSupportCookie(req);

		HttpSession ses = req.getSession();
		
		if("".equals(un)||"".equals(time)||"".equals(verify)){
			throw new UserIdException();
		}
		System.out.println(un+" "+time+" "+verify);
		un = un.trim().toUpperCase();// ת�ɴ�д
		
		long interval = DateUtil.getIntervalTime(time, DateUtil.getNow("yyyy-MM-dd HH:mm:ss"),"yyyy-MM-dd HH:mm:ss");
		System.out.println(interval);
		if(interval>3600000L||interval<-3600000L){
			throw new UserPasswordException(3);
		}
		String encStr = un+"njuneusoftecard"+time;
		
		String encodedStr = SimpleEncoding.byte2hex(SimpleEncoding.md5(encStr.getBytes()));
		String verfiy_upcase = verify.toUpperCase();
		System.out.println(encodedStr);
		if(!verfiy_upcase.equals(encodedStr)){
			throw new UserPasswordException(8);
		}

		long userId = GetterUtil.getLong(un);

		int authResult = Authenticator.FAILURE;

		Company company = PortalUtil.getCompany(req);

		if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_EA)) {
			authResult = UserLocalServiceUtil.authenticateByEmailAddress(
					company.getCompanyId(), un);

			userId = UserLocalServiceUtil.getUserIdByEmailAddress(company
					.getCompanyId(), un);
		} else if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_SN)) {
			authResult = UserLocalServiceUtil.authenticateByScreenName(company
					.getCompanyId(), un);
			if (authResult >= 0) {
				userId = UserLocalServiceUtil.getUserIdByScreenName(company
						.getCompanyId(), un);
			}
		} else if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_ID)) {
			authResult = UserLocalServiceUtil.authenticateByUserId(company
					.getCompanyId(), userId);
		}

		if (authResult > Authenticator.DNE) {
			if (PropsValues.SESSION_ENABLE_PHISHING_PROTECTION) {

				// Invalidate the previous session to prevent phishing

				Boolean httpsInitial = (Boolean) ses
						.getAttribute(WebKeys.HTTPS_INITIAL);

				LastPath lastPath = (LastPath) ses
						.getAttribute(WebKeys.LAST_PATH);

				try {
					ses.invalidate();
				} catch (IllegalStateException ise) {

					// This only happens in Geronimo

					if (_log.isWarnEnabled()) {
						_log.warn(ise.getMessage());
					}
				}

				ses = req.getSession(true);

				if (httpsInitial != null) {
					ses.setAttribute(WebKeys.HTTPS_INITIAL, httpsInitial);
				}

				if (lastPath != null) {
					ses.setAttribute(WebKeys.LAST_PATH, lastPath);
				}
			}

			// Set cookies

			String domain = CookieKeys.getDomain(req);

			User user = UserLocalServiceUtil.getUserById(userId);

			String userIdString = String.valueOf(userId);
			ses.setAttribute("j_status", authResult);
			ses.setAttribute("j_screenname", un);
			ses.setAttribute("j_username", userIdString);
			ses.setAttribute("j_password", user.getPassword());
			ses.setAttribute("j_remoteuser", userIdString);

			Cookie companyIdCookie = new Cookie(CookieKeys.COMPANY_ID, String
					.valueOf(company.getCompanyId()));

			if (Validator.isNotNull(domain)) {
				companyIdCookie.setDomain(domain);
			}

			companyIdCookie.setPath(StringPool.SLASH);

			Cookie idCookie = new Cookie(CookieKeys.ID, UserLocalServiceUtil
					.encryptUserId(userIdString));

			if (Validator.isNotNull(domain)) {
				idCookie.setDomain(domain);
			}

			idCookie.setPath(StringPool.SLASH);

			int loginMaxAge = PropsValues.COMPANY_SECURITY_AUTO_LOGIN_MAX_AGE;

			companyIdCookie.setMaxAge(-1);
			idCookie.setMaxAge(-1);

			Cookie loginCookie = new Cookie(CookieKeys.LOGIN, un);

			if (Validator.isNotNull(domain)) {
				loginCookie.setDomain(domain);
			}

			loginCookie.setMaxAge(loginMaxAge);
			loginCookie.setPath(StringPool.SLASH);

			Cookie screenNameCookie = new Cookie(CookieKeys.SCREEN_NAME,
					Encryptor
							.encrypt(company.getKeyObj(), user.getScreenName()));

			if (Validator.isNotNull(domain)) {
				screenNameCookie.setDomain(domain);
			}

			screenNameCookie.setMaxAge(loginMaxAge);
			screenNameCookie.setPath(StringPool.SLASH);

			CookieKeys.addCookie(res, companyIdCookie);
			CookieKeys.addCookie(res, idCookie);
			CookieKeys.addCookie(res, loginCookie);
			CookieKeys.addCookie(res, screenNameCookie);
		} else {
			throw new AuthException();
		}
	}
	
	
	public static void loginCSGLSSO(HttpServletRequest req,
			HttpServletResponse res,String un)
			throws Exception {

//		CookieKeys.validateSupportCookie(req);

		
		

		System.out.println("sso check end.stuempno:"+un+"login ecard sys. visa sso");
		long userId = GetterUtil.getLong(un);

		int authResult = Authenticator.FAILURE;

		Company company = PortalUtil.getCompany(req);

		if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_EA)) {
			authResult = UserLocalServiceUtil.authenticateByEmailAddress(
					company.getCompanyId(), un);

			userId = UserLocalServiceUtil.getUserIdByEmailAddress(company
					.getCompanyId(), un);
		} else if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_SN)) {
			authResult = UserLocalServiceUtil.authenticateByScreenName(company
					.getCompanyId(), un);
			if (authResult >= 0) {
				userId = UserLocalServiceUtil.getUserIdByScreenName(company
						.getCompanyId(), un);
			}
		} else if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_ID)) {
			authResult = UserLocalServiceUtil.authenticateByUserId(company
					.getCompanyId(), userId);
		}
		HttpSession ses = req.getSession();

		if (authResult > Authenticator.DNE) {
			if (PropsValues.SESSION_ENABLE_PHISHING_PROTECTION) {

				// Invalidate the previous session to prevent phishing

				Boolean httpsInitial = (Boolean) ses
						.getAttribute(WebKeys.HTTPS_INITIAL);

				LastPath lastPath = (LastPath) ses
						.getAttribute(WebKeys.LAST_PATH);

				try {
					ses.invalidate();
				} catch (IllegalStateException ise) {

					// This only happens in Geronimo

					if (_log.isWarnEnabled()) {
						_log.warn(ise.getMessage());
					}
				}

				ses = req.getSession(true);

				if (httpsInitial != null) {
					ses.setAttribute(WebKeys.HTTPS_INITIAL, httpsInitial);
				}

				if (lastPath != null) {
					ses.setAttribute(WebKeys.LAST_PATH, lastPath);
				}
			}

			// Set cookies

			String domain = CookieKeys.getDomain(req);

			User user = UserLocalServiceUtil.getUserById(userId);

			String userIdString = String.valueOf(userId);
			ses.setAttribute("j_status", authResult);
			ses.setAttribute("j_screenname", un);
			ses.setAttribute("j_username", userIdString);
			ses.setAttribute("j_password", user.getPassword());
			ses.setAttribute("j_remoteuser", userIdString);

			Cookie companyIdCookie = new Cookie(CookieKeys.COMPANY_ID, String
					.valueOf(company.getCompanyId()));

			if (Validator.isNotNull(domain)) {
				companyIdCookie.setDomain(domain);
			}

			companyIdCookie.setPath(StringPool.SLASH);

			Cookie idCookie = new Cookie(CookieKeys.ID, UserLocalServiceUtil
					.encryptUserId(userIdString));

			if (Validator.isNotNull(domain)) {
				idCookie.setDomain(domain);
			}

			idCookie.setPath(StringPool.SLASH);

			int loginMaxAge = PropsValues.COMPANY_SECURITY_AUTO_LOGIN_MAX_AGE;

			companyIdCookie.setMaxAge(-1);
			idCookie.setMaxAge(-1);

			Cookie loginCookie = new Cookie(CookieKeys.LOGIN, un);

			if (Validator.isNotNull(domain)) {
				loginCookie.setDomain(domain);
			}

			loginCookie.setMaxAge(loginMaxAge);
			loginCookie.setPath(StringPool.SLASH);

			Cookie screenNameCookie = new Cookie(CookieKeys.SCREEN_NAME,
					Encryptor
							.encrypt(company.getKeyObj(), user.getScreenName()));

			if (Validator.isNotNull(domain)) {
				screenNameCookie.setDomain(domain);
			}

			screenNameCookie.setMaxAge(loginMaxAge);
			screenNameCookie.setPath(StringPool.SLASH);

			CookieKeys.addCookie(res, companyIdCookie);
			CookieKeys.addCookie(res, idCookie);
			CookieKeys.addCookie(res, loginCookie);
			CookieKeys.addCookie(res, screenNameCookie);
		} else {
			throw new AuthException();
		}
	}
	
	/**
	 * Method name:loginDSDXSSO
	 * Description:   �Ϻ����Ӵ�ѧͳһ��ݶԽ�
	 * Return: void
	 * @param req
	 * @param res
	 * @throws Exception
	 */
	public static void loginDSDXSSO(HttpServletRequest req,
			HttpServletResponse res)
			throws Exception {

		CookieKeys.validateSupportCookie(req);

		HttpSession ses = req.getSession();
		String un=req.getHeader("LDAP_UIP");
		if(un==null||"".equals(un)){
			throw new UserIdException();
		}
		System.out.println("stuempno��"+un+"login ecard sys. visa sso");
		long userId = GetterUtil.getLong(un);

		int authResult = Authenticator.FAILURE;

		Company company = PortalUtil.getCompany(req);

		if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_EA)) {
			authResult = UserLocalServiceUtil.authenticateByEmailAddress(
					company.getCompanyId(), un);

			userId = UserLocalServiceUtil.getUserIdByEmailAddress(company
					.getCompanyId(), un);
		} else if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_SN)) {
			authResult = UserLocalServiceUtil.authenticateByScreenName(company
					.getCompanyId(), un);
			if (authResult >= 0) {
				userId = UserLocalServiceUtil.getUserIdByScreenName(company
						.getCompanyId(), un);
			}
		} else if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_ID)) {
			authResult = UserLocalServiceUtil.authenticateByUserId(company
					.getCompanyId(), userId);
		}

		if (authResult > Authenticator.DNE) {
			if (PropsValues.SESSION_ENABLE_PHISHING_PROTECTION) {

				// Invalidate the previous session to prevent phishing

				Boolean httpsInitial = (Boolean) ses
						.getAttribute(WebKeys.HTTPS_INITIAL);

				LastPath lastPath = (LastPath) ses
						.getAttribute(WebKeys.LAST_PATH);

				try {
					ses.invalidate();
				} catch (IllegalStateException ise) {

					// This only happens in Geronimo

					if (_log.isWarnEnabled()) {
						_log.warn(ise.getMessage());
					}
				}

				ses = req.getSession(true);

				if (httpsInitial != null) {
					ses.setAttribute(WebKeys.HTTPS_INITIAL, httpsInitial);
				}

				if (lastPath != null) {
					ses.setAttribute(WebKeys.LAST_PATH, lastPath);
				}
			}

			// Set cookies

			String domain = CookieKeys.getDomain(req);

			User user = UserLocalServiceUtil.getUserById(userId);

			String userIdString = String.valueOf(userId);
			ses.setAttribute("j_status", authResult);
			ses.setAttribute("j_screenname", un);
			ses.setAttribute("j_username", userIdString);
			ses.setAttribute("j_password", user.getPassword());
			ses.setAttribute("j_remoteuser", userIdString);

			Cookie companyIdCookie = new Cookie(CookieKeys.COMPANY_ID, String
					.valueOf(company.getCompanyId()));

			if (Validator.isNotNull(domain)) {
				companyIdCookie.setDomain(domain);
			}

			companyIdCookie.setPath(StringPool.SLASH);

			Cookie idCookie = new Cookie(CookieKeys.ID, UserLocalServiceUtil
					.encryptUserId(userIdString));

			if (Validator.isNotNull(domain)) {
				idCookie.setDomain(domain);
			}

			idCookie.setPath(StringPool.SLASH);

			int loginMaxAge = PropsValues.COMPANY_SECURITY_AUTO_LOGIN_MAX_AGE;

			companyIdCookie.setMaxAge(-1);
			idCookie.setMaxAge(-1);

			Cookie loginCookie = new Cookie(CookieKeys.LOGIN, un);

			if (Validator.isNotNull(domain)) {
				loginCookie.setDomain(domain);
			}

			loginCookie.setMaxAge(loginMaxAge);
			loginCookie.setPath(StringPool.SLASH);

			Cookie screenNameCookie = new Cookie(CookieKeys.SCREEN_NAME,
					Encryptor
							.encrypt(company.getKeyObj(), user.getScreenName()));

			if (Validator.isNotNull(domain)) {
				screenNameCookie.setDomain(domain);
			}

			screenNameCookie.setMaxAge(loginMaxAge);
			screenNameCookie.setPath(StringPool.SLASH);

			CookieKeys.addCookie(res, companyIdCookie);
			CookieKeys.addCookie(res, idCookie);
			CookieKeys.addCookie(res, loginCookie);
			CookieKeys.addCookie(res, screenNameCookie);
		} else {
			throw new AuthException();
		}
	}
	
	/**
	 * Method name:loginWiscom 
	 * Description: �ڹ�������ǶԽӵ����¼ 
	 * Return: void
	 * 
	 * @param req
	 * @param res
	 * @param stuempno
	 * @throws Exception
	 */
	public static void loginWiscom(HttpServletRequest req, HttpServletResponse res,String stuempno) throws Exception {
		CookieKeys.validateSupportCookie(req);

		HttpSession ses = req.getSession();
		System.out.println("stuempno:" + stuempno + " loginWiscom");
		//long userId = GetterUtil.getLong(stuempno);
		long userId = 0;

		int authResult = Authenticator.FAILURE;

		Company company = PortalUtil.getCompany(req);

		if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_EA)) {
			authResult = UserLocalServiceUtil.authenticateByEmailAddress(company.getCompanyId(), stuempno);

			userId = UserLocalServiceUtil.getUserIdByEmailAddress(company.getCompanyId(), stuempno);
		} else if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_SN)) {
			authResult = UserLocalServiceUtil.authenticateByScreenName(company.getCompanyId(), stuempno);
			if (authResult >= 0) {
				userId = UserLocalServiceUtil.getUserIdByScreenName(company.getCompanyId(), stuempno);
			}
		} else if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_ID)) {
			//authResult = UserLocalServiceUtil.authenticateByUserId(company.getCompanyId(), userId);
		}

		if (authResult > Authenticator.DNE) {
			if (PropsValues.SESSION_ENABLE_PHISHING_PROTECTION) {

				// Invalidate the previous session to prevent phishing
				Boolean httpsInitial = (Boolean) ses.getAttribute(WebKeys.HTTPS_INITIAL);
				LastPath lastPath = (LastPath) ses.getAttribute(WebKeys.LAST_PATH);

				try {
					ses.invalidate();
				} catch (IllegalStateException ise) {
					// This only happens in Geronimo
					if (_log.isWarnEnabled()) {
						_log.warn(ise.getMessage());
					}
				}

				ses = req.getSession(true);
				if (httpsInitial != null) {
					ses.setAttribute(WebKeys.HTTPS_INITIAL, httpsInitial);
				}
				if (lastPath != null) {
					ses.setAttribute(WebKeys.LAST_PATH, lastPath);
				}
			}

			// Set cookies
			String domain = CookieKeys.getDomain(req);
			User user = UserLocalServiceUtil.getUserById(userId);
			_log.debug("screenname:"+stuempno);

			String userIdString = String.valueOf(userId);
			ses.setAttribute("j_status", authResult);
			ses.setAttribute("j_screenname", stuempno);
			ses.setAttribute("j_username", userIdString);
			ses.setAttribute("j_password", user.getPassword());
			ses.setAttribute("j_remoteuser", userIdString);

			Cookie companyIdCookie = new Cookie(CookieKeys.COMPANY_ID, String.valueOf(company.getCompanyId()));

			if (Validator.isNotNull(domain)) {
				companyIdCookie.setDomain(domain);
			}

			companyIdCookie.setPath(StringPool.SLASH);

			Cookie idCookie = new Cookie(CookieKeys.ID, UserLocalServiceUtil.encryptUserId(userIdString));

			if (Validator.isNotNull(domain)) {
				idCookie.setDomain(domain);
			}

			idCookie.setPath(StringPool.SLASH);

			int loginMaxAge = PropsValues.COMPANY_SECURITY_AUTO_LOGIN_MAX_AGE;

			companyIdCookie.setMaxAge(-1);
			idCookie.setMaxAge(-1);

			Cookie loginCookie = new Cookie(CookieKeys.LOGIN, stuempno);

			if (Validator.isNotNull(domain)) {
				loginCookie.setDomain(domain);
			}

			loginCookie.setMaxAge(loginMaxAge);
			loginCookie.setPath(StringPool.SLASH);

			Cookie screenNameCookie = new Cookie(CookieKeys.SCREEN_NAME, Encryptor.encrypt(company.getKeyObj(), user.getScreenName()));

			if (Validator.isNotNull(domain)) {
				screenNameCookie.setDomain(domain);
			}

			screenNameCookie.setMaxAge(loginMaxAge);
			screenNameCookie.setPath(StringPool.SLASH);

			CookieKeys.addCookie(res, companyIdCookie);
			CookieKeys.addCookie(res, idCookie);
			CookieKeys.addCookie(res, loginCookie);
			CookieKeys.addCookie(res, screenNameCookie);
		} else {
			throw new AuthException();
		}
	}

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest req, HttpServletResponse res) throws Exception {

		if (PropsValues.COMPANY_SECURITY_AUTH_REQUIRES_HTTPS && !req.isSecure()) {

			ThemeDisplay themeDisplay = (ThemeDisplay) req
					.getAttribute(WebKeys.THEME_DISPLAY);

			StringMaker sm = new StringMaker();

			sm.append(PortalUtil.getPortalURL(req, true));
			sm.append(themeDisplay.getURLSignIn());

			res.sendRedirect(sm.toString());

			return null;
		}

		HttpSession ses = req.getSession();

		ThemeDisplay themeDisplay = (ThemeDisplay) req
				.getAttribute(WebKeys.THEME_DISPLAY);

		if (ses.getAttribute("j_username") != null
				&& ses.getAttribute("j_password") != null) {

			if (PropsValues.PORTAL_JAAS_ENABLE) {
				return mapping.findForward("/portal/touch_protected.jsp");
			} else {
				res.sendRedirect(themeDisplay.getPathMain());

				return null;
			}
		}

		String cmd = ParamUtil.getString(req, Constants.CMD);

		if (cmd.equals("already-registered")) {
			try {
				login(req, res);

				if (PropsValues.PORTAL_JAAS_ENABLE) {
					return mapping.findForward("/portal/touch_protected.jsp");
				} else {
					String redirect = ParamUtil.getString(req, "redirect");

					if (Validator.isNotNull(redirect)) {
						res.sendRedirect(redirect);
					} else {
						res.sendRedirect(themeDisplay.getPathMain());
					}

					return null;
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

					return mapping.findForward("portal.login");
				} else if (e instanceof CookieNotSupportedException
						|| e instanceof NoSuchUserException
						|| e instanceof PasswordExpiredException
						|| e instanceof UserEmailAddressException
						|| e instanceof UserIdException
						|| e instanceof UserLockoutException
						|| e instanceof UserPasswordException
						|| e instanceof UserScreenNameException) {

					SessionErrors.add(req, e.getClass().getName());

					return mapping.findForward("portal.login");
				} else {
					req.setAttribute(PageContext.EXCEPTION, e);

					return mapping.findForward(ActionConstants.COMMON_ERROR);
				}
			}
		} else if (cmd.equals("forgot-password")) {
			try {
				sendPassword(req);

				return mapping.findForward("portal.login");
			} catch (Exception e) {
				if (e instanceof CaptchaTextException
						|| e instanceof NoSuchUserException
						|| e instanceof SendPasswordException
						|| e instanceof UserEmailAddressException) {

					SessionErrors.add(req, e.getClass().getName());

					return mapping.findForward("portal.login");
				} else {
					req.setAttribute(PageContext.EXCEPTION, e);

					return mapping.findForward(ActionConstants.COMMON_ERROR);
				}
			}
		} else {
			return mapping.findForward("portal.login");
		}
	}

	protected void login(HttpServletRequest req, HttpServletResponse res)
			throws Exception {

		String login = ParamUtil.getString(req, "login");
		String password = ParamUtil.getString(req, SessionParameters.get(req,
				"password"));
		boolean rememberMe = ParamUtil.getBoolean(req, "rememberMe");

		login(req, res, login, password, rememberMe);
	}

	protected void sendPassword(HttpServletRequest req) throws Exception {
		ThemeDisplay themeDisplay = (ThemeDisplay) req
				.getAttribute(WebKeys.THEME_DISPLAY);

		Company company = themeDisplay.getCompany();

		if (!company.isSendPassword()) {
			return;
		}

		String emailAddress = ParamUtil.getString(req, "emailAddress");

		String remoteAddr = req.getRemoteAddr();
		String remoteHost = req.getRemoteHost();
		String userAgent = req.getHeader(HttpHeaders.USER_AGENT);

		UserLocalServiceUtil.sendPassword(PortalUtil.getCompanyId(req),
				emailAddress, remoteAddr, remoteHost, userAgent);

		SessionMessages.add(req, "request_processed", emailAddress);
	}
	
	
	public static void loginSHITACSSO(HttpServletRequest req,
			HttpServletResponse res, String un, String time, String verify,String key)
			throws Exception {

		CookieKeys.validateSupportCookie(req);

		HttpSession ses = req.getSession();
		
		if("".equals(un)||"".equals(time)||"".equals(verify)){
			throw new UserIdException();
		}
		System.out.println(un+" "+time+" "+verify);
		un = un.trim().toUpperCase();// ת�ɴ�д
		String encStr = un+key+time;
		//����DigestUtils���md5Hex(String data) ����
		String encodedStr = DigestUtils.md5Hex(encStr);
		System.out.println(encodedStr);
		
		if(!verify.equalsIgnoreCase(encodedStr)){
			throw new UserPasswordException(8);
		}

		long userId = GetterUtil.getLong(un);

		int authResult = Authenticator.FAILURE;

		Company company = PortalUtil.getCompany(req);

		if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_EA)) {
			authResult = UserLocalServiceUtil.authenticateByEmailAddress(
					company.getCompanyId(), un);

			userId = UserLocalServiceUtil.getUserIdByEmailAddress(company
					.getCompanyId(), un);
		} else if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_SN)) {
			authResult = UserLocalServiceUtil.authenticateByScreenName(company
					.getCompanyId(), un);
			if (authResult >= 0) {
				userId = UserLocalServiceUtil.getUserIdByScreenName(company
						.getCompanyId(), un);
			}
		} else if (company.getAuthType().equals(CompanyImpl.AUTH_TYPE_ID)) {
			authResult = UserLocalServiceUtil.authenticateByUserId(company
					.getCompanyId(), userId);
		}

		if (authResult > Authenticator.DNE) {
			if (PropsValues.SESSION_ENABLE_PHISHING_PROTECTION) {

				// Invalidate the previous session to prevent phishing

				Boolean httpsInitial = (Boolean) ses
						.getAttribute(WebKeys.HTTPS_INITIAL);

				LastPath lastPath = (LastPath) ses
						.getAttribute(WebKeys.LAST_PATH);

				try {
					ses.invalidate();
				} catch (IllegalStateException ise) {

					// This only happens in Geronimo

					if (_log.isWarnEnabled()) {
						_log.warn(ise.getMessage());
					}
				}

				ses = req.getSession(true);

				if (httpsInitial != null) {
					ses.setAttribute(WebKeys.HTTPS_INITIAL, httpsInitial);
				}

				if (lastPath != null) {
					ses.setAttribute(WebKeys.LAST_PATH, lastPath);
				}
			}

			// Set cookies

			String domain = CookieKeys.getDomain(req);

			User user = UserLocalServiceUtil.getUserById(userId);

			String userIdString = String.valueOf(userId);
			ses.setAttribute("j_status", authResult);
			ses.setAttribute("j_screenname", un);
			ses.setAttribute("j_username", userIdString);
			ses.setAttribute("j_password", user.getPassword());
			ses.setAttribute("j_remoteuser", userIdString);

			Cookie companyIdCookie = new Cookie(CookieKeys.COMPANY_ID, String
					.valueOf(company.getCompanyId()));

			if (Validator.isNotNull(domain)) {
				companyIdCookie.setDomain(domain);
			}

			companyIdCookie.setPath(StringPool.SLASH);

			Cookie idCookie = new Cookie(CookieKeys.ID, UserLocalServiceUtil
					.encryptUserId(userIdString));

			if (Validator.isNotNull(domain)) {
				idCookie.setDomain(domain);
			}

			idCookie.setPath(StringPool.SLASH);

			int loginMaxAge = PropsValues.COMPANY_SECURITY_AUTO_LOGIN_MAX_AGE;

			companyIdCookie.setMaxAge(-1);
			idCookie.setMaxAge(-1);

			Cookie loginCookie = new Cookie(CookieKeys.LOGIN, un);

			if (Validator.isNotNull(domain)) {
				loginCookie.setDomain(domain);
			}

			loginCookie.setMaxAge(loginMaxAge);
			loginCookie.setPath(StringPool.SLASH);

			Cookie screenNameCookie = new Cookie(CookieKeys.SCREEN_NAME,
					Encryptor
							.encrypt(company.getKeyObj(), user.getScreenName()));

			if (Validator.isNotNull(domain)) {
				screenNameCookie.setDomain(domain);
			}

			screenNameCookie.setMaxAge(loginMaxAge);
			screenNameCookie.setPath(StringPool.SLASH);

			CookieKeys.addCookie(res, companyIdCookie);
			CookieKeys.addCookie(res, idCookie);
			CookieKeys.addCookie(res, loginCookie);
			CookieKeys.addCookie(res, screenNameCookie);
		} else {
			throw new AuthException();
		}
	}	

	private static Log _log = LogFactory.getLog(LoginAction.class);

}