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

package com.liferay.portal.servlet;

import com.liferay.portal.events.EventsProcessor;
import com.liferay.portal.model.UserTracker;
import com.liferay.portal.service.spring.UserTrackerLocalServiceUtil;
import com.liferay.portal.struts.ActionException;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.WebAppPool;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.mail.util.MailUtil;
import com.liferay.util.ServerDetector;

import java.util.Map;

import javax.servlet.http.HttpSession;
import javax.servlet.http.HttpSessionEvent;
import javax.servlet.http.HttpSessionListener;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="PortalSessionListener.java.html"><b><i>View Source </i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.8 $
 *
 */
public class PortalSessionListener implements HttpSessionListener {

	public void sessionCreated(HttpSessionEvent event) {
		HttpSession ses = event.getSession();

		PortalSessionContext.put(ses.getId(), ses);

		// Process session created events

		try {
			EventsProcessor.process(PropsUtil.getArray(
				PropsUtil.SERVLET_SESSION_CREATE_EVENTS), ses);
		}
		catch (ActionException ae) {
			_log.error(ae.getMessage());
		}
	}

	public void sessionDestroyed(HttpSessionEvent event) {
		HttpSession ses = event.getSession();

		PortalSessionContext.remove(ses.getId());

		if (ServerDetector.isWebLogic()) {
			PortletSessionPool.remove(ses.getId());
		}

		try {
			String companyId = (String)ses.getAttribute(WebKeys.COMPANY_ID);
			String userId = (String)ses.getAttribute(WebKeys.USER_ID);

			// Close mail connections

			MailUtil.clearCache(userId);

			// User tracker

			Map currentUsers =
				(Map)WebAppPool.get(companyId, WebKeys.CURRENT_USERS);

			UserTracker userTracker =
				(UserTracker)currentUsers.remove(ses.getId());

			try {
				if (userTracker != null) {
					UserTrackerLocalServiceUtil.addUserTracker(
						userTracker.getCompanyId(), userTracker.getUserId(),
						userTracker.getModifiedDate(),
						userTracker.getRemoteAddr(),
						userTracker.getRemoteHost(), userTracker.getUserAgent(),
						userTracker.getPaths());
				}
			}
			catch (Exception e1) {
				_log.warn(e1.getMessage());
			}
		}
		catch (IllegalStateException ise) {
			_log.warn("Please upgrade to a servlet 2.4 compliant container");
		}
		catch (Exception e2) {
			_log.error(e2.getMessage());
		}

		// Process session destroyed events

		try {
			EventsProcessor.process(PropsUtil.getArray(
				PropsUtil.SERVLET_SESSION_DESTROY_EVENTS), ses);
		}
		catch (ActionException ae) {
			_log.error(ae.getMessage());
		}
	}

	private static final Log _log =
		LogFactory.getLog(PortalSessionListener.class);

}