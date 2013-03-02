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

<%@ include file="/html/taglib/init.jsp" %>

<%@ page import="com.liferay.util.diff.DiffResult" %>
<%@ page import="com.liferay.util.diff.DiffUtil" %>

<%
String sourceName = (String)request.getAttribute("liferay-ui:diff:sourceName");
String targetName = (String)request.getAttribute("liferay-ui:diff:targetName");
List[] diffResults = (List[])request.getAttribute("liferay-ui:diff:diffResults");

List sourceResults = diffResults[0];
List targetResults = diffResults[1];
%>

<c:choose>
	<c:when test="<%= sourceResults.size() > 0 %>">
		<table class="taglib-search-iterator" id="taglib-diff-results">
		<tr>
			<td>
				<%= sourceName %>
			</td>
			<td>
				<%= targetName %>
			</td>
		</tr>

		<%
		Iterator sourceItr = sourceResults.iterator();
		Iterator targetItr = targetResults.iterator();

		while (sourceItr.hasNext()) {
			DiffResult sourceResult = (DiffResult)sourceItr.next();
			DiffResult targetResult = (DiffResult)targetItr.next();
		%>

			<tr class="portlet-section-header">
				<th>
					<liferay-ui:message key="line" /> <%= sourceResult.getLineNumber() %>
				</th>
				<th>
					<liferay-ui:message key="line" /> <%= targetResult.getLineNumber() %>
				</th>
			</tr>
			<tr>
				<td width="50%" valign="top">
					<table class="taglib-diff-table">

					<%
					Iterator itr = sourceResult.getChangedLines().iterator();

					while (itr.hasNext()) {
						String changedLine = (String)itr.next();
					%>

						<tr valign="top">
							<%= _processColumn(changedLine) %>
						</tr>

					<%
					}
					%>

					</table>
				</td>
				<td width="50%" valign="top">
					<table class="taglib-diff-table">

					<%
					itr = targetResult.getChangedLines().iterator();

					while (itr.hasNext()) {
						String changedLine = (String)itr.next();
					%>

						<tr valign="top">
							<%= _processColumn(changedLine) %>
						</tr>

					<%
					}
					%>

					</table>
				</td>
			</tr>

		<%
		}
		%>

		</table>
	</c:when>
	<c:otherwise>
		<%= LanguageUtil.format(pageContext, "there-are-no-differences-between-x-and-x", new Object[] {sourceName, targetName}) %>
	</c:otherwise>
</c:choose>

<%!
private static String _processColumn(String changedLine) {
	changedLine = changedLine.replaceAll(" ", "&nbsp;");
	changedLine = changedLine.replaceAll("\t", "&nbsp;&nbsp;&nbsp;");

	String column = "<td>" + changedLine + "</td>";

	if (changedLine.equals(StringPool.BLANK)) {
		return "<td>&nbsp;</td>";
	}
	else if (changedLine.equals(DiffUtil.CONTEXT_LINE)) {
		return "<td class=\"taglib-diff-context\">&nbsp;</td>";
	}
	else if (changedLine.equals(DiffUtil.OPEN_INS + DiffUtil.CLOSE_INS)) {
		return "<td class=\"taglib-diff-addedline\">&nbsp;</td>";
	}
	else if (changedLine.equals(DiffUtil.OPEN_DEL + DiffUtil.CLOSE_DEL)) {
		return "<td class=\"taglib-diff-deletedline\">&nbsp;</td>";
	}

	return column;
}
%>