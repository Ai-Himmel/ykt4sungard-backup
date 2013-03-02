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

package com.liferay.portal.servlet.taglib.ui;

import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.SessionClicks;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.PwdGenerator;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.JspException;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ToggleTagUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ToggleTagUtil {

	public static void doEndTag(
			String page, String id, String onImage, String offImage,
			boolean defaultOn, String stateVar, ServletContext ctx,
			HttpServletRequest req, HttpServletResponse res)
		throws JspException {

		try {
			ThemeDisplay themeDisplay =
				(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

			if (Validator.isNull(onImage)) {
				onImage =
					themeDisplay.getPathThemeImages() + "/arrows/01_down.png";
			}

			if (Validator.isNull(offImage)) {
				offImage =
					themeDisplay.getPathThemeImages() + "/arrows/01_right.png";
			}

			String defaultStateValue = defaultOn ? StringPool.BLANK : "none";
			String defaultImage = defaultOn ? onImage : offImage;

			String clickValue = SessionClicks.get(req, id, null);

			if (defaultOn) {
				if ((clickValue != null) && (clickValue.equals("none"))) {
					defaultStateValue = "none";
					defaultImage = offImage;
				}
				else {
					defaultStateValue = "";
					defaultImage = onImage;
				}
			}
			else {
				if ((clickValue == null) || (clickValue.equals("none"))) {
					defaultStateValue = "none";
					defaultImage = offImage;
				}
				else {
					defaultStateValue = "";
					defaultImage = onImage;
				}
			}

			if (stateVar == null) {
				stateVar = PwdGenerator.getPassword(PwdGenerator.KEY3, 8);
			}

			req.setAttribute("liferay-ui:toggle:id", id);
			req.setAttribute("liferay-ui:toggle:onImage", onImage);
			req.setAttribute("liferay-ui:toggle:offImage", offImage);
			req.setAttribute("liferay-ui:toggle:stateVar", stateVar);
			req.setAttribute(
				"liferay-ui:toggle:defaultStateValue", defaultStateValue);
			req.setAttribute("liferay-ui:toggle:defaultImage", defaultImage);

			RequestDispatcher rd = ctx.getRequestDispatcher(page);

			rd.include(req, res);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new JspException(e);
		}
	}

	private static Log _log = LogFactory.getLog(ToggleTagUtil.class);

}