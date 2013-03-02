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

<%@ include file="/html/portlet/journal/init.jsp" %>

<%
ArticleSearch searchContainer = (ArticleSearch)request.getAttribute("liferay-ui:search:searchContainer");

ArticleDisplayTerms displayTerms = (ArticleDisplayTerms)searchContainer.getDisplayTerms();
%>

<liferay-ui:search-toggle
	id="toggle_id_journal_article_search"
	displayTerms="<%= displayTerms %>"
>
	<table class="lfr-table">
	<tr>
		<td>
			<liferay-ui:message key="id" />
		</td>
		<td>
			<liferay-ui:message key="version" />
		</td>
		<td>
			<liferay-ui:message key="name" />
		</td>
		<td>
			<liferay-ui:message key="description" />
		</td>
	</tr>
	<tr>
		<td>
			<input name="<portlet:namespace /><%= displayTerms.ARTICLE_ID %>" size="20" type="text" value="<%= Html.escape(displayTerms.getArticleId()) %>" />
		</td>
		<td>
			<input name="<portlet:namespace /><%= displayTerms.VERSION %>" size="20" type="text" value="<%= Html.escape(displayTerms.getVersionString()) %>" />
		</td>
		<td>
			<input name="<portlet:namespace /><%= displayTerms.TITLE %>" size="20" type="text" value="<%= Html.escape(displayTerms.getTitle()) %>" />
		</td>
		<td>
			<input name="<portlet:namespace /><%= displayTerms.DESCRIPTION %>" size="20" type="text" value="<%= Html.escape(displayTerms.getDescription()) %>" />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="content" />
		</td>
		<td>
			<liferay-ui:message key="type" />
		</td>
		<td colspan="2">
			<c:choose>
				<c:when test="<%= portletName.equals(PortletKeys.JOURNAL) %>">
					<liferay-ui:message key="status" />
				</c:when>
				<c:otherwise>
					<liferay-ui:message key="community" />
				</c:otherwise>
			</c:choose>
		</td>
	</tr>
	<tr>
		<td>
			<input name="<portlet:namespace /><%= displayTerms.CONTENT %>" size="20" type="text" value="<%= Html.escape(displayTerms.getContent()) %>" />
		</td>
		<td>
			<select name="<portlet:namespace /><%= displayTerms.TYPE %>">
				<option value=""></option>

				<%
				for (int i = 0; i < JournalArticleImpl.TYPES.length; i++) {
				%>

					<option <%= displayTerms.getType().equals(JournalArticleImpl.TYPES[i]) ? "selected" : "" %> value="<%= JournalArticleImpl.TYPES[i] %>"><%= LanguageUtil.get(pageContext, JournalArticleImpl.TYPES[i]) %></option>

				<%
				}
				%>

			</select>
		</td>
		<td colspan="2">
			<c:choose>
				<c:when test="<%= portletName.equals(PortletKeys.JOURNAL) %>">
					<select name="<portlet:namespace /><%= displayTerms.STATUS %>">
						<option value=""></option>
						<option <%= displayTerms.getStatus().equals("approved") ? "selected" : "" %> value="approved"><liferay-ui:message key="approved" /></option>
						<option <%= displayTerms.getStatus().equals("not-approved") ? "selected" : "" %> value="not-approved"><liferay-ui:message key="not-approved" /></option>
						<option <%= displayTerms.getStatus().equals("expired") ? "selected" : "" %> value="expired"><liferay-ui:message key="expired" /></option>
						<option <%= displayTerms.getStatus().equals("review") ? "selected" : "" %> value="review"><liferay-ui:message key="review" /></option>
					</select>
				</c:when>
				<c:otherwise>

					<%
					LinkedHashMap groupParams = new LinkedHashMap();

					groupParams.put("usersGroups", new Long(user.getUserId()));

					List communities = GroupLocalServiceUtil.search(company.getCompanyId(), null, null, groupParams, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
					%>

					<select name="<portlet:namespace /><%= displayTerms.GROUP_ID %>">
						<c:if test="<%= layout.getGroup().isUser() %>">
							<option <%= displayTerms.getGroupId() == layout.getGroupId() ? "selected" : "" %> value="<%= String.valueOf(layout.getGroupId()) %>"><liferay-ui:message key="my-community" /></option>
						</c:if>

						<%
						for (int i = 0; i < communities.size(); i++) {
							Group group = (Group)communities.get(i);
						%>

							<option <%= displayTerms.getGroupId() == group.getGroupId() ? "selected" : "" %> value="<%= String.valueOf(group.getGroupId()) %>"><%= group.getName() %></option>

						<%
						}
						%>

					</select>
				</c:otherwise>
			</c:choose>
		</td>
	</tr>
	</table>
</liferay-ui:search-toggle>

<br />

<div>
	<input type="submit" value="<liferay-ui:message key="search-articles" />" />

	<c:if test="<%= PortletPermissionUtil.contains(permissionChecker, plid.longValue(), PortletKeys.JOURNAL, ActionKeys.ADD_ARTICLE) %>">
		<input type="button" value="<liferay-ui:message key="add-article" />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/journal/edit_article" /><portlet:param name="redirect" value="<%= currentURL %>" /><portlet:param name="structureId" value="<%= displayTerms.getStructureId() %>" /><portlet:param name="templateId" value="<%= displayTerms.getTemplateId() %>" /></portlet:renderURL>';" />
	</c:if>
</div>

<c:if test="<%= Validator.isNotNull(displayTerms.getStructureId()) %>">
	<br />

	<input name="<portlet:namespace /><%= displayTerms.STRUCTURE_ID %>" type="hidden" value="<%= displayTerms.getStructureId() %>" />

	<liferay-ui:message key="filter-by-structure" />: <%= displayTerms.getStructureId() %><br />
</c:if>

<c:if test="<%= Validator.isNotNull(displayTerms.getTemplateId()) %>">
	<br />

	<input name="<portlet:namespace /><%= displayTerms.TEMPLATE_ID %>" type="hidden" value="<%= displayTerms.getTemplateId() %>" />

	<liferay-ui:message key="filter-by-template" />: <%= displayTerms.getTemplateId() %><br />
</c:if>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace /><%= displayTerms.ARTICLE_ID %>);
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace /><%= displayTerms.KEYWORDS %>);
	</script>
</c:if>