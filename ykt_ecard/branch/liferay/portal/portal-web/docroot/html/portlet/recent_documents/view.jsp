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

<%@ include file="/html/portlet/recent_documents/init.jsp" %>

<%
List fileRanks = DLFileRankLocalServiceUtil.getFileRanks(portletGroupId.longValue(), user.getUserId(), 0, SearchContainer.DEFAULT_DELTA);
%>

<c:choose>
	<c:when test="<%= fileRanks.size() == 0 %>">
		<liferay-ui:message key="there-are-no-recent-documents" />
	</c:when>
	<c:otherwise>
		<table class="lfr-table">

		<%
		for (int i = 0; i < fileRanks.size(); i++) {
			DLFileRank fileRank = (DLFileRank)fileRanks.get(i);

			try {
				DLFileEntry fileEntry = DLFileEntryLocalServiceUtil.getFileEntry(fileRank.getFolderId(), fileRank.getName());

				fileEntry = fileEntry.toEscapedModel();

				PortletURL rowURL = renderResponse.createActionURL();

				rowURL.setWindowState(LiferayWindowState.EXCLUSIVE);

				rowURL.setParameter("struts_action", "/recent_documents/get_file");
				rowURL.setParameter("folderId", String.valueOf(fileRank.getFolderId()));
				rowURL.setParameter("name", Html.unescape(fileRank.getName()));
		%>

				<tr>
					<td>
						<a href="<%= rowURL.toString() %>"><img align="left" border="0" src="<%= themeDisplay.getPathThemeImages() %>/document_library/<%= DLUtil.getFileExtension(fileRank.getName()) %>.png" /><%= fileEntry.getTitleWithExtension() %></a>
					</td>
				</tr>

		<%
			}
			catch (Exception e) {
			}
		}
		%>

		</table>
	</c:otherwise>
</c:choose>