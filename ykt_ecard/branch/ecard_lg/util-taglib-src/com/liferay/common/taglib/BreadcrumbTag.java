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

package com.liferay.common.taglib;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Layout;
import com.liferay.portal.service.persistence.LayoutPK;
import com.liferay.portal.service.spring.LayoutLocalServiceUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.Validator;
import com.liferay.util.lang.FastStringBuffer;

import javax.servlet.ServletRequest;
import javax.servlet.jsp.JspTagException;
import javax.servlet.jsp.tagext.TagSupport;

/**
 * <a href="BreadcrumbTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.10 $
 *
 */
public class BreadcrumbTag extends TagSupport {

	public static final String SEPARATOR_HTML = "<font class=\"portlet-font\" style=\"font-size: x-small;\">&nbsp;&nbsp;&#187;&nbsp;&nbsp;</font>";

	public int doStartTag() throws JspTagException {
		try {
			ServletRequest req = pageContext.getRequest();

			ThemeDisplay themeDisplay =
				(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

			Layout layout = themeDisplay.getLayout();

			if (layout != null) {
				String groupId = layout.getGroupId();

				FastStringBuffer sb = new FastStringBuffer();

				buildBreadcrumb(layout, themeDisplay, true, sb);

				pageContext.getOut().print(sb.toString());
			}

			return EVAL_BODY_INCLUDE;
		}
		catch (Exception e) {
			throw new JspTagException(e.getMessage());
		}
	}

	public int doEndTag() {
		return EVAL_PAGE;
	}

	public void setClassName(String className) {
		_className = className;
	}

	public void setSeparatorHtml(String separatorHtml) {
		_separatorHtml = separatorHtml;
	}

	protected void buildBreadcrumb(
			Layout layout, ThemeDisplay themeDisplay, boolean selectedLayout,
			FastStringBuffer sb)
		throws PortalException, SystemException {

		String layoutURL = PortalUtil.getLayoutURL(layout, themeDisplay);
		String target = PortalUtil.getLayoutTarget(layout);

		FastStringBuffer breadCrumbSB = new FastStringBuffer();

		if (!selectedLayout) {
			breadCrumbSB.append("<a ");

			if (Validator.isNotNull(_className)) {
				breadCrumbSB.append("class=\"");
				breadCrumbSB.append(_className);
				breadCrumbSB.append("\" ");
			}

			breadCrumbSB.append("href=\"");
			breadCrumbSB.append(layoutURL);
			breadCrumbSB.append("\" ");
			breadCrumbSB.append(target);
			breadCrumbSB.append(">");
		}

		breadCrumbSB.append(layout.getName());

		if (!selectedLayout) {
			breadCrumbSB.append("</a>");
		}

		Layout layoutParent = null;
		String layoutParentId = layout.getParentLayoutId();

		if (!layoutParentId.equals(Layout.DEFAULT_PARENT_LAYOUT_ID)) {
			String userId = themeDisplay.getUserId();
			String groupId = layout.getGroupId();

			if (Validator.isNull(groupId)) {
				layoutParent = LayoutLocalServiceUtil.getLayout(
					new LayoutPK(layoutParentId, userId));
			}
			else {
				layoutParent = LayoutLocalServiceUtil.getLayout(
					new LayoutPK(layoutParentId, Layout.GROUP + groupId));
			}

			buildBreadcrumb(layoutParent, themeDisplay, false, sb);

			sb.append(_separatorHtml);
			sb.append(breadCrumbSB.toString());
		}
		else {
			sb.append(breadCrumbSB.toString());
		}
	}

	private String _className;
	private String _separatorHtml = SEPARATOR_HTML;

}