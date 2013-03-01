/**
 * 
 */
package com.kingstargroup.advquery.user.action;

import java.net.URLDecoder;
import com.wiscom.is.SSOToken;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.net.URLEncoder;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import com.kingstargroup.advquery.common.DateUtilExtend;
import com.kingstargroup.advquery.hibernate.util.UserUtil;
import com.kingstargroup.advquery.util.ParamUtil;
import com.kingstargroup.advquery.util.SessionErrors;
import com.kingstargroup.advquery.util.WebKeys;
import com.octo.captcha.image.ImageCaptcha;
import com.wiscom.is.IdentityFactory;
import com.wiscom.is.IdentityManager;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: LoginAction.java<br>
 * Description: <br>
 * Modify History: <br>
 * �������� ������ ����ʱ�� ��������<br>
 * ===================================<br>
 * ���� Xiao Qi 2005-11-10 <br>
 * 
 * @author Xiao Qi
 * @version
 * @since 1.0
 */
public class LoginAction extends Action {

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.apache.struts.action.Action#execute(org.apache.struts.action.ActionMapping,
	 *      org.apache.struts.action.ActionForm,
	 *      javax.servlet.http.HttpServletRequest,
	 *      javax.servlet.http.HttpServletResponse)
	 */

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest req, HttpServletResponse res) throws Exception {

		// ͳһ��֤
		String username = LoginAction.getUser(req);
		// ��֤����ȡ���û���
		if (username != null) {
			HttpSession session = req.getSession();
			session.setAttribute("username", username);
			UserUtil.createLoginInfo(username);
			iniDate(req);
			if (UserUtil.getUserParentFuncList(username).size() == 0) {
				return mapping.findForward("eadvquery.warning");
			} else {
				return mapping.findForward("eadvquery.main");
			}
		} else {

			// ��������½����
			username = ParamUtil.getString(req, "username");
			String password = ParamUtil.getString(req, "password");
			String authCode = ParamUtil.getString(req, "authCode");
			if (username.equals("")) {
				return mapping.findForward("eadvquery.login");
			}
			ImageCaptcha captcha = (ImageCaptcha) req.getSession()
					.getAttribute(WebKeys.CAPTCHA);
			// ��֤���Ƿ���
			if (captcha == null) {
				return mapping.findForward("eadvquery.login");
			}
			Boolean validResponse = captcha.validateResponse(authCode);
			if ((validResponse == null)
					|| (validResponse.equals(Boolean.FALSE))) {
				req.getSession().removeAttribute(WebKeys.CAPTCHA);
				SessionErrors.add(req, "eadvquery.error.validate");
				return mapping.findForward("eadvquery.login");
			}
			if (!UserUtil.login(username, password)) {
				SessionErrors.add(req, "eadvquery.error.validate");
				req.getSession().removeAttribute(WebKeys.CAPTCHA);
				return mapping.findForward("eadvquery.login");
			}
			HttpSession session = req.getSession();
			session.setAttribute("username", username);
			UserUtil.createLoginInfo(username);
			iniDate(req);
			if (UserUtil.getUserParentFuncList(username).size() == 0) {
				return mapping.findForward("eadvquery.warning");
			}

			String is_config = req.getRealPath("/client.properties");
			// System.out.println("***********"+is_config);
			IdentityFactory factory = IdentityFactory.createFactory(is_config);
			IdentityManager im = factory.getIdentityManager();

			SSOToken token = im.createStoken(username, password);
			if (token != null) {
				String value = token.getTokenValue();
				String encodeCookieValue = URLEncoder.encode(value, "UTF-8");
				Cookie cookie = new Cookie("iPlanetDirectoryPro",
						encodeCookieValue);
				cookie.setDomain(".usst.edu.cn");
				cookie.setMaxAge(-1);
				cookie.setPath("/");
				res.addCookie(cookie);
				// System.out.print("********Create cookie*************value=" +
				// value);
			}
		}
		return mapping.findForward("eadvquery.main");

	}

	public static String getUser(HttpServletRequest req) {

		/*HttpSession ses = req.getSession();
		String username = (String) ses.getAttribute("username");

		if (username == null) {
			// Portlet WARs may have the correct remote user and not have the
			// correct user id because the user id is saved in the session
			// and may not be accessible by the portlet WAR's session. This
			// behavior is inconsistent across different application servers.

			username = req.getRemoteUser();*/
			//if (username == null) {
				//
		  String username = null;
				try {
					Cookie all_cookies[] = req.getCookies();
					Cookie myCookie;
					String decodedCookieValue = null;
					if (all_cookies != null) {
						for (int i = 0; i < all_cookies.length; i++) {
							myCookie = all_cookies[i];
							if (myCookie.getName()
									.equals("iPlanetDirectoryPro")) {
								decodedCookieValue = URLDecoder.decode(myCookie
										.getValue(), "UTF-8");
							}
						}
					}
					if (decodedCookieValue != null) {
						String is_config = req
								.getRealPath("/client.properties");
						IdentityFactory factory = IdentityFactory
								.createFactory(is_config);
						IdentityManager im = factory.getIdentityManager();
						username = im.getCurrentUser(decodedCookieValue);
						if (username == null || "".equals(username)) {
							return null;
						}
					}
				} catch (Exception e) {
					// TODO: handle exception
					return null;
				}

				if (username == null || "".equals(username)) {
					return null;
				}
			//}
		//}
		return username;
	}

	/**
	 * ��ʼ����ʼ����
	 * 
	 * @param req
	 */
	private void iniDate(HttpServletRequest req) {
		String beginDate = DateUtilExtend.getDateLaterMonth();
		String endDate = DateUtilExtend.getNowDate();
		String beginMonth = beginDate.substring(0, 7);
		String endMonth = endDate.substring(0, 7);
		HttpSession session = req.getSession();
		session.setAttribute("begindate21d", endDate);
		session.setAttribute("begindate22d", beginDate);
		session.setAttribute("enddate22d", endDate);
		session.setAttribute("begindate22m", beginMonth);
		session.setAttribute("enddate22m", endMonth);
		session.setAttribute("begindate22w", beginDate);
		session.setAttribute("enddate22w", endDate);

		session.setAttribute("begindate23d", beginDate);
		session.setAttribute("enddate23d", endDate);
		session.setAttribute("begindate23m", beginMonth);
		session.setAttribute("enddate23m", endMonth);
		session.setAttribute("begindate23w", beginDate);
		session.setAttribute("enddate23w", endDate);

		session.setAttribute("begindate24d", beginDate);
		session.setAttribute("enddate24d", endDate);
		session.setAttribute("begindate24m", beginMonth);
		session.setAttribute("enddate24m", endMonth);

		session.setAttribute("begindate25d", beginDate);
		session.setAttribute("enddate25d", endDate);
		session.setAttribute("begindate25m", beginMonth);
		session.setAttribute("enddate25m", endMonth);
		session.setAttribute("begindate25w", beginDate);
		session.setAttribute("enddate25w", endDate);

		session.setAttribute("begindate27d", beginDate);
		session.setAttribute("enddate27d", endDate);

		session.setAttribute("begindate32d", beginDate);
		session.setAttribute("enddate32d", endDate);
		session.setAttribute("begindate32m", beginMonth);
		session.setAttribute("enddate32m", endMonth);
		session.setAttribute("begindate32w", beginDate);
		session.setAttribute("enddate32w", endDate);

		session.setAttribute("begindate33d", beginDate);
		session.setAttribute("enddate33d", endDate);
		session.setAttribute("begindate33m", beginMonth);
		session.setAttribute("enddate33m", endMonth);
		session.setAttribute("begindate33w", beginDate);
		session.setAttribute("enddate33w", endDate);

		session.setAttribute("begindate34d", beginDate);
		session.setAttribute("enddate34d", endDate);
		session.setAttribute("begindate34m", beginMonth);
		session.setAttribute("enddate34m", endMonth);
		session.setAttribute("begindate34w", beginDate);
		session.setAttribute("enddate34w", endDate);

		session.setAttribute("begindate35d", beginDate);
		session.setAttribute("enddate35d", endDate);
		session.setAttribute("begindate35m", beginMonth);
		session.setAttribute("enddate35m", endMonth);

		session.setAttribute("begindate41d", beginDate);
		session.setAttribute("enddate41d", endDate);
		session.setAttribute("begindate41m", beginMonth);
		session.setAttribute("enddate41m", endMonth);
		session.setAttribute("begindate41w", beginDate);
		session.setAttribute("enddate41w", endDate);

		session.setAttribute("begindate42d", beginDate);
		session.setAttribute("enddate42d", endDate);
		session.setAttribute("begindate42m", beginMonth);
		session.setAttribute("enddate42m", endMonth);
		session.setAttribute("begindate42w", beginDate);
		session.setAttribute("enddate42w", endDate);

		session.setAttribute("begindate43d", beginDate);
		session.setAttribute("enddate43d", endDate);
		session.setAttribute("begindate43m", beginMonth);
		session.setAttribute("enddate43m", endMonth);
		session.setAttribute("begindate43w", beginDate);
		session.setAttribute("enddate43w", endDate);

		session.setAttribute("begindate44d", beginDate);
		session.setAttribute("enddate44d", endDate);
		session.setAttribute("begindate44m", beginMonth);
		session.setAttribute("enddate44m", endMonth);
		session.setAttribute("begindate44w", beginDate);
		session.setAttribute("enddate44w", endDate);

		session.setAttribute("begindate45d", beginDate);
		session.setAttribute("enddate45d", endDate);
		session.setAttribute("begindate45m", beginMonth);
		session.setAttribute("enddate45m", endMonth);
		session.setAttribute("begindate45w", beginDate);
		session.setAttribute("enddate45w", endDate);

		session.setAttribute("begindate46d", beginDate);
		session.setAttribute("enddate46d", endDate);
		session.setAttribute("begindate46m", beginMonth);
		session.setAttribute("enddate46m", endMonth);
		session.setAttribute("begindate46w", beginDate);
		session.setAttribute("enddate46w", endDate);

		session.setAttribute("begindate48d", beginDate);
		session.setAttribute("enddate48d", endDate);
		session.setAttribute("begindate48m", beginMonth);
		session.setAttribute("enddate48m", endMonth);
		session.setAttribute("begindate48w", beginDate);
		session.setAttribute("enddate48w", endDate);

		session.setAttribute("begindate51d", beginDate);
		session.setAttribute("enddate51d", endDate);
		session.setAttribute("begindate51m", beginMonth);
		session.setAttribute("enddate51m", endMonth);

		session.setAttribute("begindate52d", beginDate);
		session.setAttribute("enddate52d", endDate);
		session.setAttribute("begindate52m", beginMonth);
		session.setAttribute("enddate52m", endMonth);
		session.setAttribute("begindate52w", beginDate);
		session.setAttribute("enddate52w", endDate);

		session.setAttribute("begindate53d", beginDate);
		session.setAttribute("enddate53d", endDate);
		session.setAttribute("begindate53m", beginMonth);
		session.setAttribute("enddate53m", endMonth);

		session.setAttribute("begindate54d", beginDate);
		session.setAttribute("enddate54d", endDate);
		session.setAttribute("begindate54m", beginMonth);
		session.setAttribute("enddate54m", endMonth);

		session.setAttribute("begindate99", endDate);
	}

}
