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

<%@ include file="/html/portlet/blogs/init.jsp" %>

<%
String redirect = ParamUtil.getString(request, "redirect");

if (Validator.isNull(redirect)) {
	redirect = PortalUtil.getLayoutURL(layout, themeDisplay) + "/blogs";
}

BlogsEntry entry = (BlogsEntry)request.getAttribute(WebKeys.BLOGS_ENTRY);

long entryId = BeanParamUtil.getLong(entry, request, "entryId");

pageDisplayStyle = RSSUtil.DISPLAY_STYLE_FULL_CONTENT;
%>

<form action="<portlet:actionURL><portlet:param name="struts_action" value="/blogs/edit_entry" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm1" onSubmit="<portlet:namespace />saveEntry(); return false;">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />entryId" type="hidden" value="<%= String.valueOf(entryId) %>" />

<liferay-ui:tabs
	names="entry"
	backURL="<%= redirect %>"
/>

<%@ include file="/html/portlet/blogs/view_entry_content.jspf" %>

</form>

<c:if test="<%= enableComments %>">
	<br />

	<liferay-ui:tabs names="comments" />

	<portlet:actionURL var="discussionURL">
		<portlet:param name="struts_action" value="/blogs/edit_entry_discussion" />
	</portlet:actionURL>

	<liferay-ui:discussion
		formName="fm2"
		formAction="<%= discussionURL %>"
		className="<%= BlogsEntry.class.getName() %>"
		classPK="<%= entry.getEntryId() %>"
		userId="<%= entry.getUserId() %>"
		subject="<%= entry.getTitle() %>"
		redirect="<%= currentURL %>"
	/>
</c:if>