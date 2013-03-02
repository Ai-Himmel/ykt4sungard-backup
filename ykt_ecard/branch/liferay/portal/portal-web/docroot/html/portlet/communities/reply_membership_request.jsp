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

<%@ include file="/html/portlet/communities/init.jsp" %>

<%
String redirect = ParamUtil.getString(request, "redirect");

ActionUtil.getGroup(request);

Group group = (Group)request.getAttribute(WebKeys.GROUP);

long groupId = BeanParamUtil.getLong(group, request, "groupId");

String friendlyURL = BeanParamUtil.getString(group, request, "friendlyURL");

ActionUtil.getMembershipRequest(request);

MembershipRequest membershipRequest = (MembershipRequest)request.getAttribute(WebKeys.MEMBERSHIP_REQUEST);
%>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/communities/reply_membership_request" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />groupId" type="hidden" value="<%= groupId %>" />
<input name="<portlet:namespace />membershipRequestId" type="hidden" value="<%= membershipRequest.getMembershipRequestId() %>" />

<liferay-ui:tabs
	names="community"
	backURL="<%= redirect %>"
/>

<liferay-ui:error exception="<%= DuplicateGroupException.class %>" message="please-enter-a-unique-name" />
<liferay-ui:error exception="<%= GroupNameException.class %>" message="please-enter-a-valid-name" />
<liferay-ui:error exception="<%= MembershipRequestCommentsException.class %>" message="please-enter-valid-comments" />
<liferay-ui:error exception="<%= RequiredGroupException.class %>" message="old-group-name-is-a-required-system-group" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="user-name" />
	</td>
	<td>
		<%= group.getName() %>
	</td>
</tr>

<c:if test="<%= Validator.isNotNull(group.getDescription()) %>">
	<tr>
		<td>
			<liferay-ui:message key="description" />
		</td>
		<td>
			<%= group.getDescription() %>
		</td>
	</tr>
</c:if>

<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="user-comments" />
	</td>
	<td>
		<%= membershipRequest.getComments() %>
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="status" />
	</td>
	<td>
		<select name="<portlet:namespace />statusId">
			<option value="<%=MembershipRequestImpl.STATUS_APPROVED %>"><liferay-ui:message key="approve" /></option>
			<option value="<%=MembershipRequestImpl.STATUS_DENIED %>"><liferay-ui:message key="deny" /></option>
		</select>
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="reply-comments" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= MembershipRequest.class %>" bean="<%= membershipRequest %>" field="replyComments" />
	</td>
</tr>
</table>

<br />

<input type="submit" value="<liferay-ui:message key="save" />" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />statusId);
	</script>
</c:if>