<%
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
%>

<%@ include file="/html/taglib/ui/breadcrumb/init.jsp" %>

<%
StringMaker sm = new StringMaker();

_buildBreadcrumb(selLayout, selLayoutParam, portletURL, themeDisplay, true, sm);
%>

<%= sm.toString() %>

<%!
private void _buildBreadcrumb(Layout selLayout, String selLayoutParam, PortletURL portletURL, ThemeDisplay themeDisplay, boolean selectedLayout, StringMaker sm) throws Exception {
	String layoutURL = _getBreadcrumbLayoutURL(selLayout, selLayoutParam, portletURL, themeDisplay);
	String target = PortalUtil.getLayoutTarget(selLayout);

	StringMaker breadCrumbSM = new StringMaker();

	breadCrumbSM.append("<a href=\"");
	breadCrumbSM.append(layoutURL);
	breadCrumbSM.append("\" ");
	breadCrumbSM.append(target);
	breadCrumbSM.append(">");

	breadCrumbSM.append(selLayout.getName(themeDisplay.getLocale()));

	breadCrumbSM.append("</a>");

	Layout layoutParent = null;
	long layoutParentId = selLayout.getParentLayoutId();

	if (layoutParentId != LayoutImpl.DEFAULT_PARENT_LAYOUT_ID) {
		layoutParent = LayoutLocalServiceUtil.getLayout(selLayout.getGroupId(), selLayout.isPrivateLayout(), layoutParentId);

		_buildBreadcrumb(layoutParent, selLayoutParam, portletURL, themeDisplay, false, sm);

		sm.append(" &raquo; ");
		sm.append(breadCrumbSM.toString());
	}
	else {
		sm.append(breadCrumbSM.toString());
	}
}

private String _getBreadcrumbLayoutURL(Layout selLayout, String selLayoutParam, PortletURL portletURL, ThemeDisplay themeDisplay) throws Exception {
	if (portletURL == null) {
		return PortalUtil.getLayoutURL(selLayout, themeDisplay);
	}
	else {
		portletURL.setParameter(selLayoutParam, String.valueOf(selLayout.getPlid()));

		return portletURL.toString();
	}
}
%>