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

package com.liferay.portal.events;

import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutTypePortlet;
import com.liferay.portal.model.UserTracker;
import com.liferay.portal.service.spring.LayoutServiceUtil;
import com.liferay.portal.service.spring.UserServiceUtil;
import com.liferay.portal.struts.Action;
import com.liferay.portal.struts.ActionException;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.WebAppPool;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.GetterUtil;

import java.util.Date;
import java.util.Iterator;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.Globals;

/**
 * <a href="LoginPostAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.29 $
 *
 */
public class LoginPostAction extends Action {

	public void run(HttpServletRequest req, HttpServletResponse res)
		throws ActionException {

		try {
			HttpSession ses = req.getSession();

			String companyId = PortalUtil.getCompanyId(req);
			String userId = PortalUtil.getUserId(req);

			Map currentUsers =
				(Map)WebAppPool.get(companyId, WebKeys.CURRENT_USERS);

			boolean simultaenousLogins = GetterUtil.get(
				PropsUtil.get(PropsUtil.AUTH_SIMULTANEOUS_LOGINS), true);

			if (!simultaenousLogins) {
				Map.Entry[] currentUsersArray =
					(Map.Entry[])currentUsers.entrySet().toArray(
						new Map.Entry[0]);

				for (int i = 0; i < currentUsersArray.length; i++) {
					Map.Entry mapEntry = currentUsersArray[i];

					UserTracker userTracker = (UserTracker)mapEntry.getValue();

					if (userTracker.getUserId().equals(userId)) {

						// Disable old login

						userTracker.getHttpSession().setAttribute(
							WebKeys.STALE_SESSION, Boolean.TRUE);
					}
				}
			}

			UserTracker userTracker =
				(UserTracker)currentUsers.get(ses.getId());

			if (userTracker == null) {
				userTracker = new UserTracker(
					ses.getId(), companyId, req.getRemoteUser(), new Date(),
					req.getRemoteAddr(), req.getRemoteHost(),
					req.getHeader("USER-AGENT"));

				userTracker.setHttpSession(ses);

				currentUsers.put(ses.getId(), userTracker);
			}

			if (!GetterUtil.getBoolean(PropsUtil.get(
					PropsUtil.LAYOUT_REMEMBER_WINDOW_STATE_MAXIMIZED))) {

				Iterator itr = UserServiceUtil.getLayouts(userId).iterator();

				while (itr.hasNext()) {
					Layout layout = (Layout)itr.next();

					LayoutTypePortlet layoutType =
						(LayoutTypePortlet)layout.getLayoutType();

					if (layoutType.hasStateMax()) {

						// Set the window state to normal for the maximized
						// portlet

						layoutType.resetStates();

						// Set the portlet mode to view because other modes may
						// require a maximized window state

						layoutType.resetModes();

						LayoutServiceUtil.updateLayout(
							layout.getPrimaryKey(), layout.getTypeSettings());
					}
				}
			}

			// Reset the locale

			ses.removeAttribute(Globals.LOCALE_KEY);
		}
		catch (Exception e) {
			throw new ActionException(e);
		}
	}

}