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

<%@ include file="/html/portlet/layout_configuration/init.jsp" %>

<%
String redirect = ParamUtil.getString(request, "redirect");
%>

<c:if test="<%= themeDisplay.isSignedIn() && (layout != null) && layout.getType().equals(LayoutImpl.TYPE_PORTLET) %>">
	<form action="<%= themeDisplay.getPathMain() %>/portal/update_layout?p_l_id=<%= plid %>" method="post" name="layoutTemplates">
	<input name="doAsUserId" type="hidden" value="<%= themeDisplay.getDoAsUserId() %>" />
	<input name="<%= Constants.CMD %>" type="hidden" value="template" />
	<input name="<%= WebKeys.REFERER %>" type="hidden" value="<%= redirect %>" />
	<input name="refresh" type="hidden" value="true" />

	<table border="0" cellpadding="0" cellspacing="10" style="margin-top: 10px;" width="100%">

	<%
	int CELLS_PER_ROW = 4;

	List layoutTemplates = LayoutTemplateLocalUtil.getLayoutTemplates(theme.getThemeId());

	layoutTemplates = PluginUtil.restrictPlugins(layoutTemplates, user);

	Group group = layout.getGroup();

	String selector1 = StringPool.BLANK;

	if (group.isUser()) {
		selector1 = "desktop";
	}
	else if (group.isCommunity()) {
		selector1 = "community";
	}
	else if (group.isOrganization()) {
		selector1 = "organization";
	}

	String selector2 = StringPool.BLANK;

	if ((layout.getPriority() == 0) && (layout.getParentLayoutId() == LayoutImpl.DEFAULT_PARENT_LAYOUT_ID)) {
		selector2 = "firstLayout";
	}

	for (int i = 0; i < layoutTemplates.size(); i++) {
		LayoutTemplate layoutTemplate = (LayoutTemplate)layoutTemplates.get(i);
	%>

		<c:if test="<%= (i % CELLS_PER_ROW) == 0 %>">
			<tr>
		</c:if>

		<td align="center" width="<%= 100 / CELLS_PER_ROW %>%">
			<img onclick="document.getElementById('layoutTemplateId<%= i %>').checked = true;" src="<%= layoutTemplate.getContextPath() %><%= layoutTemplate.getThumbnailPath() %>" /><br />

			<input <%= layoutTypePortlet.getLayoutTemplateId().equals(layoutTemplate.getLayoutTemplateId()) ? "checked" : "" %> id="layoutTemplateId<%= i %>" name="layoutTemplateId" type="radio" value="<%= layoutTemplate.getLayoutTemplateId() %>" />

			<label for="layoutTemplateId<%= i %>"><%= layoutTemplate.getName() %></label>
		</td>

		<c:if test="<%= (i % CELLS_PER_ROW) == (CELLS_PER_ROW - 1) %>">
			</tr>
		</c:if>

	<%
	}
	%>

	</table>

	<input class="form-button" type="submit" value="<liferay-ui:message key="save" />" style="margin: 10px" />

	</form>
</c:if>