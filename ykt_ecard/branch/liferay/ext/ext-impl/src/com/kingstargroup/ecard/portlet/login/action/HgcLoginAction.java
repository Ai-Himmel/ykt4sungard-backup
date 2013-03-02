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

import com.kingstargroup.ecard.KSConfiguration;
import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.PasswordExpiredException;
import com.liferay.portal.UserLockoutException;
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

/**
 * 黑工程登陆
 * 
 * @author Yiming.You
 * 
 */
public class HgcLoginAction extends PortletAction {

	public void processAction(ActionMapping mapping, ActionForm form, PortletConfig config, ActionRequest req, ActionResponse res) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);
		HttpServletResponse httpRes = PortalUtil.getHttpServletResponse(res);

		String cmd = req.getParameter(Constants.CMD);

		ThemeDisplay themeDisplay = (ThemeDisplay) req.getAttribute(WebKeys.THEME_DISPLAY);

		if (req.getRemoteUser() != null) {
			String path = PropsValues.DEFAULT_LANDING_PAGE_PATH;
			User user = PortalUtil.getUser(req);
			if (user != null) {
				path = "/web/" + user.getScreenName() + "/1";
			}
			res.sendRedirect(path);
		} else if (Validator.isNotNull(cmd)) {
			try {
				login(themeDisplay, req, res);
			} catch (Exception e) {
				if (e instanceof AuthException) {
					Throwable cause = e.getCause();
					if (cause instanceof PasswordExpiredException || cause instanceof UserLockoutException) {
						SessionErrors.add(req, cause.getClass().getName());
						httpReq.getSession().setAttribute("LOGIN_ERROR", "密码错误");
					} else {
						SessionErrors.add(req, e.getClass().getName());
						httpReq.getSession().setAttribute("LOGIN_ERROR", "用户名密码验证失败");
					}
				} else if (e instanceof CaptchaTextException) {
					SessionErrors.add(req, e.getClass().getName());
					httpReq.getSession().setAttribute("LOGIN_ERROR", "验证码错误");
				} else if (e instanceof NoSuchUserException) {
					SessionErrors.add(req, e.getClass().getName());
					httpReq.getSession().setAttribute("LOGIN_ERROR", "没有该用户");
				} else {
					req.setAttribute(PageContext.EXCEPTION, e);
					setForward(req, ActionConstants.COMMON_ERROR);
					httpReq.getSession().setAttribute("LOGIN_ERROR", "登陆失败");
				}
				httpRes.sendRedirect(KSConfiguration.getInstance().getProperty("indexUrl"));
			}
		}
	}

	public ActionForward render(ActionMapping mapping, ActionForm form, PortletConfig config, RenderRequest req, RenderResponse res) throws Exception {
		return null;
	}

	protected void login(ThemeDisplay themeDisplay, ActionRequest req, ActionResponse res) throws Exception {

		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);
		HttpServletResponse httpRes = PortalUtil.getHttpServletResponse(res);

		String login = ParamUtil.getString(req, "login");
		String password = ParamUtil.getString(req, "password");
		boolean rememberMe = ParamUtil.getBoolean(req, "rememberMe");

		Boolean isResponseCorrect = Boolean.FALSE;
		// remenber that we need an id to validate!
		String captchaId = httpReq.getSession().getId();
		// retrieve the response
		String response = httpReq.getParameter("authCode");
		// Call the Service method
		try {
			System.out.println("captchaId" + captchaId);
			isResponseCorrect = CaptchaServiceSingleton.getInstance().validateResponseForID(captchaId, response);
		} catch (CaptchaServiceException e) {
			// should not happen, may be thrown if the id is not valid
			e.printStackTrace();
			throw new CaptchaTextException();
		}

		if ((isResponseCorrect == null) || (isResponseCorrect.equals(Boolean.FALSE))) {
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

	protected boolean isCheckMethodOnProcessAction() {
		return _CHECK_METHOD_ON_PROCESS_ACTION;
	}

	private static final boolean _CHECK_METHOD_ON_PROCESS_ACTION = false;

}
