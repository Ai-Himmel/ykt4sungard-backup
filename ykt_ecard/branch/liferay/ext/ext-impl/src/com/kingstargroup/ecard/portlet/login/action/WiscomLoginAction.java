package com.kingstargroup.ecard.portlet.login.action;

import java.net.URLDecoder;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.ecard.KSConfiguration;
import com.liferay.portal.CookieNotSupportedException;
import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.PasswordExpiredException;
import com.liferay.portal.UserEmailAddressException;
import com.liferay.portal.UserIdException;
import com.liferay.portal.UserLockoutException;
import com.liferay.portal.UserPasswordException;
import com.liferay.portal.UserScreenNameException;
import com.liferay.portal.captcha.CaptchaTextException;
import com.liferay.portal.security.auth.AuthException;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.servlet.SessionErrors;
import com.wiscom.is.IdentityFactory;
import com.wiscom.is.IdentityManager;

public class WiscomLoginAction extends PortletAction {

	public void processAction(ActionMapping mapping, ActionForm form, PortletConfig config, ActionRequest req, ActionResponse res) throws Exception {
		ThemeDisplay themeDisplay = (ThemeDisplay) req.getAttribute(WebKeys.THEME_DISPLAY);
		try {
			wiscomLogin(themeDisplay, req, res);
		} catch (Exception e) {
			if (e instanceof AuthException) {
				Throwable cause = e.getCause();
				if (cause instanceof PasswordExpiredException || cause instanceof UserLockoutException) {
					SessionErrors.add(req, cause.getClass().getName());
				} else {
					SessionErrors.add(req, e.getClass().getName());
				}
			} else if (e instanceof CookieNotSupportedException || e instanceof NoSuchUserException || e instanceof PasswordExpiredException || e instanceof UserEmailAddressException
					|| e instanceof UserIdException || e instanceof UserLockoutException || e instanceof UserPasswordException || e instanceof UserScreenNameException
					|| e instanceof CaptchaTextException) {
				SessionErrors.add(req, e.getClass().getName());
			} else {
				req.setAttribute(PageContext.EXCEPTION, e);
				setForward(req, ActionConstants.COMMON_ERROR);
			}
		}
	}

	/**
	 * Method name:loginNJUSSO Description: 黑工程金智sso对接模块 Return: void
	 * 
	 * @param themeDisplay
	 * @param req
	 * @param res
	 * @throws Exception
	 */
	protected void wiscomLogin(ThemeDisplay themeDisplay, ActionRequest request, ActionResponse response) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(request);
		HttpServletResponse httpRes = PortalUtil.getHttpServletResponse(response);
		httpReq.setCharacterEncoding("UTF-8");

		String is_config = KSConfiguration.getInstance().getProperty("constant.ldap.path")+"/client.properties";
		Cookie all_cookies[] = httpReq.getCookies();
		Cookie myCookie;
		String decodedCookieValue = null;
		if (all_cookies != null) {
			for (int i = 0; i < all_cookies.length; i++) {
				myCookie = all_cookies[i];
				if (myCookie.getName().equals("iPlanetDirectoryPro")) {
					decodedCookieValue = URLDecoder.decode(myCookie.getValue(), "GB2312");
				}
			}
		}

		IdentityFactory factory = IdentityFactory.createFactory(is_config);
		IdentityManager im = factory.getIdentityManager();

		String curUser = "";
		
		if (decodedCookieValue != null) {
			curUser = im.getCurrentUser(decodedCookieValue);
		}
		LoginAction.loginWiscom(httpReq, httpRes, curUser);

		if (PropsValues.PORTAL_JAAS_ENABLE) {
			response.sendRedirect(themeDisplay.getPathMain() + "/portal/protected");
		} else {
			response.sendRedirect(themeDisplay.getPathMain());
		}
	}

	public ActionForward render(ActionMapping mapping, ActionForm form, PortletConfig config, RenderRequest req, RenderResponse res) throws Exception {
		return mapping.findForward("extportlet.login.view");
	}

	protected boolean isCheckMethodOnProcessAction() {
		return _CHECK_METHOD_ON_PROCESS_ACTION;
	}

	private static final boolean _CHECK_METHOD_ON_PROCESS_ACTION = false;

}
