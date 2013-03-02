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

String tabs1 = ParamUtil.getString(request, "tabs1", "pending");

int statusId = -1;

if (tabs1.equals("approved")) {
	statusId = MembershipRequestImpl.STATUS_APPROVED;
}
else if (tabs1.equals("denied")) {
	statusId = MembershipRequestImpl.STATUS_DENIED;
}
else {
	statusId = MembershipRequestImpl.STATUS_PENDING;
}

Group group = (Group)request.getAttribute(WebKeys.GROUP);
%>

<liferay-ui:success key="membership_reply_sent" message="your-reply-will-be-sent-to-the-user-by-email" />

<liferay-ui:message key="edit-requests-for-community" />: <%= group.getName() %>

<br/>
<br/>

<liferay-ui:tabs
	names="pending,approved,denied"
	url="<%= currentURL %>"
	backURL="<%= redirect %>"
/>

<%
PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setParameter("struts_action", "/communities/reply_membership_request");
portletURL.setParameter("redirect", redirect);
portletURL.setParameter("tabs1", tabs1);
portletURL.setParameter("groupId", String.valueOf(group.getGroupId()));

List headerNames = new ArrayList();

headerNames.add("date");
headerNames.add("user");
headerNames.add("user-comments");

if (!tabs1.equals("pending")) {
	headerNames.add("reply-date");
	headerNames.add("replier");
	headerNames.add("reply-comments");
}

headerNames.add(StringPool.BLANK);

SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, SearchContainer.DEFAULT_DELTA, portletURL, headerNames, LanguageUtil.get(pageContext, "no-requests-were-found"));

searchContainer.setHeaderNames(headerNames);

List results = MembershipRequestLocalServiceUtil.search(group.getGroupId(), statusId, searchContainer.getStart(), searchContainer.getEnd());

int total = MembershipRequestLocalServiceUtil.searchCount(group.getGroupId(), statusId);

searchContainer.setTotal(total);

List resultRows = searchContainer.getResultRows();

for (int i = 0; i < results.size(); i++) {
	MembershipRequest membershipRequest = (MembershipRequest)results.get(i);

	long userId = 0L;

	User user2 = UserLocalServiceUtil.getUserById(membershipRequest.getUserId());

	ResultRow row = new ResultRow(new Object[]{user2, group, membershipRequest}, userId, i);

	// Date

	row.addText(dateFormatDate.format(membershipRequest.getCreateDate()));

	// User

	StringMaker sm = new StringMaker();
	sm.append(user2.getFullName());
	sm.append(" (");
	sm.append(user2.getEmailAddress());
	sm.append(")");

	row.addText(sm.toString());

	// Comments

	row.addText(membershipRequest.getComments());

	if (!tabs1.equals("pending")) {

		// Reply Date

		row.addText(dateFormatDate.format(membershipRequest.getReplyDate()));

		// Replier

		User user3 = UserLocalServiceUtil.getUserById(membershipRequest.getReplierUserId());

		row.addText(user3.getFullName());

		// Reply comments

		row.addText(membershipRequest.getReplyComments());
	}

	// Actions

	row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/communities/membership_request_action.jsp");

	// Add result row

	resultRows.add(row);
}
%>

<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />