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

<%@ include file="/html/portlet/polls/init.jsp" %>

<%
String redirect = ParamUtil.getString(request, "redirect");

PollsQuestion question = (PollsQuestion)request.getAttribute(WebKeys.POLLS_QUESTION);

question = question.toEscapedModel();

List choices = PollsChoiceLocalServiceUtil.getChoices(question.getQuestionId());

boolean hasVoted = PollsUtil.hasVoted(request, question.getQuestionId());

boolean viewResults = ParamUtil.getBoolean(request, "viewResults", false);

if (viewResults && !PollsQuestionPermission.contains(permissionChecker, question, ActionKeys.UPDATE)) {
	viewResults = false;
}
%>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/polls/view_question" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="<%= Constants.ADD %>" />
<input name="<portlet:namespace />redirect" type="hidden" value="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/polls/view_question" /><portlet:param name="questionId" value="<%= String.valueOf(question.getQuestionId()) %>" /></portlet:renderURL>" />
<input name="<portlet:namespace />questionId" type="hidden" value="<%= question.getQuestionId() %>" />

<liferay-ui:error exception="<%= DuplicateVoteException.class %>" message="you-may-only-vote-once" />
<liferay-ui:error exception="<%= NoSuchChoiceException.class %>" message="please-select-an-option" />

<span style="font-size: small;"><b>
<%= question.getTitle() %>
</b></span><br />

<span style="font-size: x-small;">
<%= question.getDescription() %>
</span>

<br /><br />

<c:choose>
	<c:when test='<%= !viewResults && !question.isExpired() && !hasVoted && PollsQuestionPermission.contains(permissionChecker, question, ActionKeys.ADD_VOTE) %>'>
		<table class="lfr-table">

		<%
		Iterator itr = choices.iterator();

		while (itr.hasNext()) {
			PollsChoice choice = (PollsChoice)itr.next();

			choice = choice.toEscapedModel();
		%>

			<tr>
				<td>
					<input name="<portlet:namespace />choiceId" type="radio" value="<%= choice.getChoiceId() %>" />
				</td>
				<td>
					<b><%= choice.getName() %>.</b>
				</td>
				<td>
					<%= choice.getDescription() %>
				</td>
			</tr>

		<%
		}
		%>

		</table>

		<br />

		<c:if test="<%= PollsQuestionPermission.contains(permissionChecker, question, ActionKeys.UPDATE) %>">
			<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" var="viewResultsURL">
				<portlet:param name="struts_action" value="/polls/view_question" />
				<portlet:param name="redirect" value="<%= redirect %>" />
				<portlet:param name="questionId" value="<%= String.valueOf(question.getQuestionId()) %>" />
				<portlet:param name="viewResults" value="1" />
			</portlet:renderURL>

			<liferay-ui:icon image="view" message="view-results" url="<%= viewResultsURL %>" label="<%= true %>" />
		</c:if>

		<br /><br />

		<input type="button" value="<liferay-ui:message key="vote" />" onClick="submitForm(document.<portlet:namespace />fm);" />

		<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />
	</c:when>
	<c:otherwise>
		<%@ include file="/html/portlet/polls/view_question_results.jspf" %>

		<c:choose>
			<c:when test="<%= !question.isExpired() && !hasVoted && PollsQuestionPermission.contains(permissionChecker, question, ActionKeys.ADD_VOTE) %>">
				<br />

				<input type="button" value="<liferay-ui:message key="back-to-vote" />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/polls/view_question" /><portlet:param name="redirect" value="<%= redirect %>" /><portlet:param name="questionId" value="<%= String.valueOf(question.getQuestionId()) %>" /></portlet:renderURL>';" />
			</c:when>
			<c:when test="<%= Validator.isNotNull(redirect) %>">
				<br />

				<input type="button" value="<liferay-ui:message key="back" />" onClick="self.location = '<%= redirect %>';" />
			</c:when>
		</c:choose>
	</c:otherwise>
</c:choose>

</form>