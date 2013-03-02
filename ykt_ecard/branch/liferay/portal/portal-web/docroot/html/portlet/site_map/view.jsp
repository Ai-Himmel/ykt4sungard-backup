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

<%@ include file="/html/portlet/site_map/init.jsp" %>

<%
List rootLayouts = null;

if (rootPlid > 0) {
	Layout rootLayout = LayoutLocalServiceUtil.getLayout(rootPlid);

	rootLayouts = rootLayout.getChildren();
}
else {
	rootLayouts = LayoutLocalServiceUtil.getLayouts(layout.getGroupId(), layout.isPrivateLayout(), LayoutImpl.DEFAULT_PARENT_LAYOUT_ID);
}

StringMaker sm = new StringMaker();

_buildSiteMap(rootLayouts, displayDepth, 1, themeDisplay, sm);
%>

<%= sm.toString() %>

<%!
private void _buildSiteMap(List layouts, int displayDepth, int curDepth, ThemeDisplay themeDisplay, StringMaker sm) throws Exception {
	PermissionChecker permissionChecker = themeDisplay.getPermissionChecker();

	sm.append("<ul style=\"padding-left: 25px\">");

	for (int i = 0; i < layouts.size(); i++) {
		Layout layout = (Layout)layouts.get(i);

		if (!layout.isHidden() && LayoutPermissionUtil.contains(permissionChecker, layout, ActionKeys.VIEW)) {
			String layoutURL = PortalUtil.getLayoutURL(layout, themeDisplay);
			String target = PortalUtil.getLayoutTarget(layout);

			sm.append("<li>");
			sm.append("<a href=\"");
			sm.append(layoutURL);
			sm.append("\" ");
			sm.append(target);
			sm.append("> ");
			sm.append(layout.getName(themeDisplay.getLocale()));
			sm.append("</a>");
			sm.append("</li>");

			if ((displayDepth == 0) || (displayDepth > curDepth)) {
				_buildSiteMap(layout.getChildren(), displayDepth, curDepth + 1, themeDisplay, sm);
			}
		}
	}

	sm.append("</ul>");
}
%>