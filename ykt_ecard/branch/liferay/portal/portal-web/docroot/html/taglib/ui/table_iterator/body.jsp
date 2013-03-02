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

<%
List list = (List)request.getAttribute("liferay-ui:table-iterator:list");
int listPos = GetterUtil.getInteger((String)request.getAttribute("liferay-ui:table-iterator:listPos"));
int rowLength = GetterUtil.getInteger((String)request.getAttribute("liferay-ui:table-iterator:rowLength"));
String rowPadding = (String)request.getAttribute("liferay-ui:table-iterator:rowPadding");
String rowValign = (String)request.getAttribute("liferay-ui:table-iterator:rowValign");
String rowBreak = (String)request.getAttribute("liferay-ui:table-iterator:rowBreak");
%>

</td>

<c:if test="<%= ((listPos + 1) % rowLength) == 0 %>">
	</tr>

	<c:if test="<%= Validator.isNotNull(rowBreak) %>">
		<tr>
			<td colspan="<%= rowLength * 2 - 1 %>">
				<%= rowBreak %>
			</td>
		</tr>
	</c:if>

	<c:if test="<%= (listPos + 1) < list.size() %>">
		<tr>
	</c:if>
</c:if>

<c:if test="<%= (listPos + 1) < list.size() %>">
	<c:if test="<%= (listPos % rowLength) + 1 < rowLength %>">
		<td style="padding-left: <%= rowPadding %>px;"></td>
	</c:if>

	<td valign="<%= rowValign %>">
</c:if>