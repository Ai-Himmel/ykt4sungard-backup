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

package com.liferay.taglib.ui;

import com.liferay.portal.model.Layout;
import com.liferay.taglib.util.IncludeTag;

import javax.portlet.PortletURL;

import javax.servlet.ServletRequest;

/**
 * <a href="BreadcrumbTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BreadcrumbTag extends IncludeTag {

	public int doStartTag() {
		ServletRequest req = pageContext.getRequest();

		req.setAttribute("liferay-ui:breadcrumb:selLayout", _selLayout);
		req.setAttribute(
			"liferay-ui:breadcrumb:selLayoutParam", _selLayoutParam);
		req.setAttribute("liferay-ui:breadcrumb:portletURL", _portletURL);
		req.setAttribute(
			"liferay-ui:breadcrumb:displayStyle",
			String.valueOf(_displayStyle));

		return EVAL_BODY_BUFFERED;
	}

	public void setSelLayout(Layout selLayout) {
		_selLayout = selLayout;
	}

	public void setSelLayoutParam(String selLayoutParam) {
		_selLayoutParam = selLayoutParam;
	}

	public void setPortletURL(PortletURL portletURL) {
		_portletURL = portletURL;
	}

	public void setDisplayStyle(int displayStyle) {
		_displayStyle = displayStyle;
	}

	protected String getDefaultPage() {
		return _PAGE;
	}

	private static final String _PAGE = "/html/taglib/ui/breadcrumb/page.jsp";

	private Layout _selLayout;
	private String _selLayoutParam;
	private PortletURL _portletURL;
	private int _displayStyle = 1;

}