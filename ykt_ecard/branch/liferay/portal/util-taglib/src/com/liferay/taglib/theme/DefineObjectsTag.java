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

package com.liferay.taglib.theme;

import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.WebKeys;

import javax.servlet.ServletRequest;
import javax.servlet.jsp.tagext.TagSupport;

/**
 * <a href="DefineObjectsTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DefineObjectsTag extends TagSupport {

	public int doStartTag() {
		ServletRequest req = pageContext.getRequest();

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		if (themeDisplay != null) {
			pageContext.setAttribute("themeDisplay", themeDisplay);
			pageContext.setAttribute("company", themeDisplay.getCompany());
			pageContext.setAttribute("account", themeDisplay.getAccount());
			pageContext.setAttribute("user", themeDisplay.getUser());
			pageContext.setAttribute("realUser", themeDisplay.getRealUser());
			pageContext.setAttribute("contact", themeDisplay.getContact());

			if (themeDisplay.getLayout() != null) {
				pageContext.setAttribute("layout", themeDisplay.getLayout());
			}

			if (themeDisplay.getLayouts() != null) {
				pageContext.setAttribute("layouts", themeDisplay.getLayouts());
			}

			pageContext.setAttribute("plid", new Long(themeDisplay.getPlid()));

			if (themeDisplay.getLayoutTypePortlet() != null) {
				pageContext.setAttribute(
					"layoutTypePortlet", themeDisplay.getLayoutTypePortlet());
			}

			pageContext.setAttribute(
				"portletGroupId",
				new Long(themeDisplay.getPortletGroupId()));
			pageContext.setAttribute(
				"permissionChecker", themeDisplay.getPermissionChecker());
			pageContext.setAttribute("locale", themeDisplay.getLocale());
			pageContext.setAttribute("timeZone", themeDisplay.getTimeZone());
			pageContext.setAttribute("theme", themeDisplay.getTheme());
			pageContext.setAttribute(
				"colorScheme", themeDisplay.getColorScheme());
			pageContext.setAttribute(
				"portletDisplay", themeDisplay.getPortletDisplay());
		}

		return SKIP_BODY;
	}

	public int doEndTag() {
		return EVAL_PAGE;
	}

}