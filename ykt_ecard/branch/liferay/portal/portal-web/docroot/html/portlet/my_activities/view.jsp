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

<%@ include file="/html/portlet/my_activities/init.jsp" %>

<%
List activityTrackers = ActivityTrackerLocalServiceUtil.getCompanyActivityTrackers(company.getCompanyId(), 0, SearchContainer.DEFAULT_DELTA);
%>

<table class="lfr-table">

<%
for (int i = 0; i < activityTrackers.size(); i++) {
	ActivityTracker activityTracker = (ActivityTracker)activityTrackers.get(i);

	ActivityFeedEntry activityFeedEntry = ActivityTrackerInterpreterUtil.interpret(activityTracker, themeDisplay);

	if (activityFeedEntry != null) {
%>

		<tr>
			<td>
				<%= activityFeedEntry.getTitle() %>
			</td>
			<td>
				<%= timeFormatDate.format(activityTracker.getCreateDate()) %>
			</td>
		</tr>
		<tr>
			<td>
				<%= activityFeedEntry.getBody() %>
			</td>
			<td></td>
		</tr>

<%
	}
}
%>

</table>