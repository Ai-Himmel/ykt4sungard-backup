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

<%@ include file="/html/taglib/ui/navigation/init.jsp" %>

<c:if test="<%= layout != null %>">

	<%
	Layout rootLayout = null;
	boolean hidden = false;

	List selBranch = new ArrayList();

	selBranch.add(layout);
	selBranch.addAll(layout.getAncestors());

	if (rootLayoutType.equals("relative")) {
		if ((rootLayoutLevel >= 0) && (rootLayoutLevel < selBranch.size())) {
			rootLayout = (Layout) selBranch.get(rootLayoutLevel);
		}
		else {
			rootLayout = null;
		}
	}
	else if (rootLayoutType.equals("absolute")) {
		int ancestorIndex = selBranch.size() - rootLayoutLevel;

		if ((ancestorIndex >= 0) && (ancestorIndex < selBranch.size())) {
			rootLayout = (Layout) selBranch.get(ancestorIndex);
		}
		else if (ancestorIndex == selBranch.size()) {
			rootLayout = null;
		}
		else {
			hidden = true;
		}
	}
	%>

	<div class="nav-menu nav-menu-style-<%= bulletStyle %>">

		<c:choose>
			<c:when test='<%= (headerType.equals("root-layout") && (rootLayout != null)) %>'>

				<%
				String layoutURL = PortalUtil.getLayoutURL(rootLayout, themeDisplay);
				String target = PortalUtil.getLayoutTarget(rootLayout);
				String layoutName = rootLayout.getName(themeDisplay.getLocale());
				%>

				<h3>
					<a href="<%= layoutURL %>" <%= target %>><%= layoutName %></a>
				</h3>
			</c:when>
			<c:when test='<%= headerType.equals("portlet-title") %>'>
				<h3><%= themeDisplay.getPortletDisplay().getTitle() %></h3>
			</c:when>
			<c:when test='<%= headerType.equals("breadcrumb") %>'>
				<liferay-ui:breadcrumb />
			</c:when>
		</c:choose>

		<%
		if (!hidden) {
			StringMaker sm = new StringMaker();

			_buildNavigation(rootLayout, layout, selBranch, themeDisplay, 1, includedLayouts, sm);

			out.print(sm.toString());
		}
		%>

	</div>
</c:if>

<%!
private void _buildNavigation(Layout rootLayout, Layout selLayout, List selBranch, ThemeDisplay themeDisplay, int layoutLevel, String includedLayouts, StringMaker sm) throws Exception {
	List layoutChildren = null;

	if (rootLayout != null) {
		layoutChildren = rootLayout.getChildren();
	}
	else {
		layoutChildren = LayoutLocalServiceUtil.getLayouts(selLayout.getGroupId(), selLayout.isPrivateLayout(), LayoutImpl.DEFAULT_PARENT_LAYOUT_ID);
	}

	if (layoutChildren.size() > 0) {
		sm.append("<ul class=\"layouts\">");

		for (int i = 0; i < layoutChildren.size(); i++) {
			Layout layoutChild = (Layout)layoutChildren.get(i);

			if (!layoutChild.isHidden() && LayoutPermissionUtil.contains(themeDisplay.getPermissionChecker(), layoutChild, ActionKeys.VIEW)) {
				String layoutURL = PortalUtil.getLayoutURL(layoutChild, themeDisplay);
				String target = PortalUtil.getLayoutTarget(layoutChild);

				boolean open = false;

				if (includedLayouts.equals("auto") &&  selBranch.contains(layoutChild) && (layoutChild.getChildren().size() > 0)) {
					open = true;
				}

				if (includedLayouts.equals("all")) {
					open = true;
				}

				StringMaker className = new StringMaker();

				if (open) {
					className.append("open ");
				}

				if (selLayout.getLayoutId() == layoutChild.getLayoutId()) {
					className.append("selected ");
				}

				sm.append("<li ");

				if (Validator.isNotNull(className)) {
					sm.append("class=\"");
					sm.append(className);
					sm.append("\" ");
				}

				sm.append(">");
				sm.append("<a ");

				if (Validator.isNotNull(className)) {
					sm.append("class=\"");
					sm.append(className);
					sm.append("\" ");
				}

				sm.append("href=\"");
				sm.append(layoutURL);
				sm.append("\" ");
				sm.append(target);
				sm.append("> ");
				sm.append(layoutChild.getName(themeDisplay.getLocale()));
				sm.append("</a>");

				if (open) {
					_buildNavigation(layoutChild, selLayout, selBranch, themeDisplay, layoutLevel + 1, includedLayouts, sm);
				}

				sm.append("</li>");
			}
		}

		sm.append("</ul>");
	}
}
%>