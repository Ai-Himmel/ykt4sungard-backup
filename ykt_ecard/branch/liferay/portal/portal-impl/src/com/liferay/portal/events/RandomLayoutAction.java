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

package com.liferay.portal.events;

import com.liferay.portal.kernel.events.Action;
import com.liferay.portal.kernel.events.ActionException;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.Randomizer;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutTypePortlet;
import com.liferay.portal.model.impl.GroupImpl;
import com.liferay.portal.service.GroupLocalServiceUtil;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.WebKeys;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="RandomLayoutAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RandomLayoutAction extends Action {

	public void run(HttpServletRequest req, HttpServletResponse res)
		throws ActionException {

		try {

			// Disable caching for CSS and JavaScript

			PropsUtil.set(PropsUtil.LAST_MODIFIED_CHECK, "false");

			// Do not randomize layout unless the user is logged in

			ThemeDisplay themeDisplay =
				(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

			if (!themeDisplay.isSignedIn()) {
				return;
			}

			// Do not randomize layout unless the user is accessing the portal

			String requestURI = GetterUtil.getString(req.getRequestURI());

			if (!requestURI.endsWith("/portal/layout")) {
				return;
			}

			// Do not randomize layout unless the user is accessing a personal
			// layout

			Layout layout = themeDisplay.getLayout();

			if (layout == null) {
				return;
			}

			Group generalGuestGroup = GroupLocalServiceUtil.getGroup(
				themeDisplay.getCompanyId(), GroupImpl.GUEST);

			List layouts = LayoutLocalServiceUtil.getLayouts(
				generalGuestGroup.getGroupId(), false);

			if (layouts.size() > 0) {
				Layout randomLayout = (Layout)layouts.get(
					Randomizer.getInstance().nextInt(layouts.size()));

				themeDisplay.setLayout(randomLayout);
				themeDisplay.setLayoutTypePortlet(
					(LayoutTypePortlet)randomLayout.getLayoutType());

				req.setAttribute(WebKeys.LAYOUT, randomLayout);
			}
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new ActionException(e);
		}
	}

	private static Log _log = LogFactory.getLog(RandomLookAndFeelAction.class);

}