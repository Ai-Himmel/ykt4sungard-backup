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

import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.events.EventsProcessor;
import com.liferay.portal.servlet.PortletSessionPool;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.CookieKeys;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.ServerDetector;
import com.liferay.util.StringPool;

import java.util.Iterator;
import java.util.Map;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="LogoutAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.8 $
 *
 */
public class LogoutAction extends Action {

	public ActionForward execute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		try {
			HttpSession ses = req.getSession();

			EventsProcessor.process(PropsUtil.getArray(
				PropsUtil.LOGOUT_EVENTS_PRE), req, res);
			/* never process cookie
			Cookie cookie = new Cookie(CookieKeys.ID, StringPool.BLANK);
			cookie.setMaxAge(0);
			cookie.setPath("/");

			res.addCookie(cookie);

			cookie = new Cookie(CookieKeys.PASSWORD, StringPool.BLANK);
			cookie.setMaxAge(0);
			cookie.setPath("/");

			res.addCookie(cookie);
			*/
			if (ServerDetector.isWebLogic()) {
				Map sessions = PortletSessionPool.remove(ses.getId());

				if (sessions != null) {
					Iterator itr = sessions.entrySet().iterator();

					while (itr.hasNext()) {
						Map.Entry entry = (Map.Entry)itr.next();

						HttpSession portletSession =
							(HttpSession)entry.getValue();

						portletSession.invalidate();
					}
				}
			}

			try {
				
				/*adjust http session set for counter*/
				String value = (String) ses.getAttribute(EcardConstants.WEB_COUNTER_NAME);
				ses.invalidate();
				ses = req.getSession(true);
				ses.setAttribute(EcardConstants.WEB_COUNTER_NAME, value);
				/*end*/
			}
			catch (Exception e) {
			}

			EventsProcessor.process(PropsUtil.getArray(
				PropsUtil.LOGOUT_EVENTS_POST), req, res);

			return mapping.findForward(Constants.COMMON_REFERER);
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			return mapping.findForward(Constants.COMMON_ERROR);
		}
	}

	private static final Log _log = LogFactory.getLog(LogoutAction.class);

}