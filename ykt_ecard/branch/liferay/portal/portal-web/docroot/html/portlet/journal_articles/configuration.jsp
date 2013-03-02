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

<%@ include file="/html/portlet/journal_articles/init.jsp" %>

<%
groupId = ParamUtil.getLong(request, "groupId", groupId);

List communities = GroupLocalServiceUtil.search(company.getCompanyId(), null, null, null, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
%>

<form action="<liferay-portlet:actionURL portletConfiguration="true" />" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="<%= Constants.UPDATE %>" />

<liferay-ui:error exception="<%= NoSuchGroupException.class %>" message="the-community-could-not-be-found" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="community" />
	</td>
	<td>
		<select name="<portlet:namespace />groupId">
			<option value=""></option>

			<%
			for (int i = 0; i < communities.size(); i++) {
				Group group = (Group)communities.get(i);

				group = group.toEscapedModel();
			%>

				<option <%= groupId == group.getGroupId() ? "selected" : "" %> value="<%= group.getGroupId() %>"><%= group.getName() %></option>

			<%
			}
			%>

		</select>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="article-type" />
	</td>
	<td>
		<select name="<portlet:namespace />type">
			<option value=""></option>

			<%
			for (int i = 0; i < JournalArticleImpl.TYPES.length; i++) {
			%>

				<option <%= type.equals(JournalArticleImpl.TYPES[i]) ? "selected" : "" %> value="<%= JournalArticleImpl.TYPES[i] %>"><%= LanguageUtil.get(pageContext, JournalArticleImpl.TYPES[i]) %></option>

			<%
			}
			%>

		</select>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="display-url" />
	</td>
	<td>
		<select name="<portlet:namespace />pageURL">
			<option <%= pageURL.equals("maximized") ? "selected" : "" %> value="maximized"><liferay-ui:message key="maximized" /></option>
			<option <%= pageURL.equals("popUp") ? "selected" : "" %> value="popUp"><liferay-ui:message key="pop-up" /></option>
		</select>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="display-per-page" />
	</td>
	<td>
		<select name="<portlet:namespace />pageDelta">

			<%
			String[] pageDeltaValues = PropsUtil.getArray(PropsUtil.JOURNAL_ARTICLES_PAGE_DELTA_VALUES);

			for (int i = 0; i < pageDeltaValues.length; i++) {
			%>

				<option <%= (pageDelta == GetterUtil.getInteger(pageDeltaValues[i])) ? "selected" : "" %> value="<%= pageDeltaValues[i] %>"><%= pageDeltaValues[i] %></option>

			<%
			}
			%>

		</select>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="order-by-column" />
	</td>
	<td>
		<select name="<portlet:namespace />orderByCol">
			<option <%= orderByCol.equals("display-date") ? "selected" : "" %> value="display-date"><liferay-ui:message key="display-date" /></option>
			<option <%= orderByCol.equals("create-date") ? "selected" : "" %> value="create-date"><liferay-ui:message key="create-date" /></option>
			<option <%= orderByCol.equals("modified-date") ? "selected" : "" %> value="modified-date"><liferay-ui:message key="modified-date" /></option>
			<option <%= orderByCol.equals("title") ? "selected" : "" %> value="title"><liferay-ui:message key="article-title" /></option>
			<option <%= orderByCol.equals("articleId") ? "selected" : "" %> value="articleId"><liferay-ui:message key="article-id" /></option>
		</select>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="order-by-type" />
	</td>
	<td>
		<select name="<portlet:namespace />orderByType">
			<option <%= orderByType.equals("asc") ? "selected" : "" %> value="asc"><liferay-ui:message key="ascending" /></option>
			<option <%= orderByType.equals("desc") ? "selected" : "" %> value="desc"><liferay-ui:message key="descending" /></option>
		</select>
	</td>
</tr>
</table>

<br />

<input type="button" value="<liferay-ui:message key="save" />" onClick="submitForm(document.<portlet:namespace />fm);" />

</form>