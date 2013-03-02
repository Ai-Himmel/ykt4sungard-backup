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

package com.liferay.portal.servlet;

import com.liferay.portal.events.EventsProcessor;
import com.liferay.portal.kernel.events.ActionException;
import com.liferay.portal.model.User;
import com.liferay.portal.security.auth.CompanyThreadLocal;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.util.LiveUsers;
import com.liferay.portal.util.PortalInstances;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.mail.util.MailSessionLock;
import com.liferay.portlet.messaging.util.MessagingUtil;

import javax.servlet.http.HttpSession;
import javax.servlet.http.HttpSessionEvent;
import javax.servlet.http.HttpSessionListener;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="PortalSessionListener.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortalSessionListener implements HttpSessionListener {

	public void sessionCreated(HttpSessionEvent event) {
		if (PropsValues.SESSION_DISABLED) {
			return;
		}

		HttpSession ses = event.getSession();

		PortalSessionContext.put(ses.getId(), ses);

		// Process session created events

		try {
			EventsProcessor.process(PropsUtil.getArray(
				PropsUtil.SERVLET_SESSION_CREATE_EVENTS), ses);
		}
		catch (ActionException ae) {
			_log.error(ae, ae);
		}
	}

	public void sessionDestroyed(HttpSessionEvent event) {
		if (PropsValues.SESSION_DISABLED) {
			return;
		}

		HttpSession ses = event.getSession();

		PortalSessionContext.remove(ses.getId());

		try {
			Long userIdObj = (Long)ses.getAttribute(WebKeys.USER_ID);

			if (userIdObj == null) {
				_log.warn("User id is not in the session");
			}

			if (userIdObj == null) {
				return;
			}

			long userId = userIdObj.longValue();

			if (CompanyThreadLocal.getCompanyId() == 0) {
				setCompanyId(userId);
			}

			MailSessionLock.cleanUp(ses);

			LiveUsers.signOut(ses.getId(), userId);
		}
		catch (IllegalStateException ise) {
			_log.warn("Please upgrade to a servlet 2.4 compliant container");
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		ses.removeAttribute(WebKeys.PORTLET_SESSION_TRACKER);
		ses.removeAttribute(WebKeys.REVERSE_AJAX);

		MessagingUtil.closeXMPPConnection(ses);

		// Process session destroyed events

		try {
			EventsProcessor.process(PropsUtil.getArray(
				PropsUtil.SERVLET_SESSION_DESTROY_EVENTS), ses);
		}
		catch (ActionException ae) {
			_log.error(ae, ae);
		}
	}

	protected void setCompanyId(long userId) throws Exception {
		long[] companyIds = PortalInstances.getCompanyIds();

		long companyId = 0;

		if (companyIds.length == 1) {
			companyId = companyIds[0];
		}
		else if (companyIds.length > 1) {
			try {
				User user = UserLocalServiceUtil.getUserById(userId);

				companyId = user.getCompanyId();
			}
			catch (Exception e) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"Unable to set the company id for user " + userId, e);
				}
			}
		}

		if (companyId > 0) {
			CompanyThreadLocal.setCompanyId(companyId);
		}
	}

	private static Log _log = LogFactory.getLog(PortalSessionListener.class);

}