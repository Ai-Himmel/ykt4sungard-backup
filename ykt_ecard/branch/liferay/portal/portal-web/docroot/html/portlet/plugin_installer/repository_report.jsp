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

<%@ include file="/html/portlet/plugin_installer/init.jsp" %>

<c:if test="<%= SessionMessages.contains(renderRequest, WebKeys.PLUGIN_REPOSITORY_REPORT) %>">
	<br />

	<table class="lfr-table">

	<%
	RepositoryReport repositoryReport = (RepositoryReport)SessionMessages.get(renderRequest, WebKeys.PLUGIN_REPOSITORY_REPORT);

	Iterator itr = repositoryReport.getRepositoryURLs().iterator();

	while (itr.hasNext()) {
		String repositoryURL = (String)itr.next();

		Object status = repositoryReport.getState(repositoryURL);
	%>

		<tr>
			<td>
				<%= repositoryURL %>
			</td>
			<td>
				<c:choose>
					<c:when test="<%= status == RepositoryReport.SUCCESS %>">
						<span class="portlet-msg-success">
						<liferay-ui:message key="ok" />
						</span>
					</c:when>
					<c:otherwise>
						<span class="portlet-msg-error">
						<%= status %>
						</span>
					</c:otherwise>
				</c:choose>
			</td>
		</tr>

	<%
	}
	%>

	</table>
</c:if>