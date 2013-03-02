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
SearchContainer searchContainer = (SearchContainer)request.getAttribute("liferay-ui:search:searchContainer");

boolean paginate = GetterUtil.getBoolean((String)request.getAttribute("liferay-ui:search-iterator:paginate"));

int start = searchContainer.getStart();
int end = searchContainer.getEnd();
int total = searchContainer.getTotal();
List resultRows = searchContainer.getResultRows();
List headerNames = searchContainer.getHeaderNames();
Map orderableHeaders = searchContainer.getOrderableHeaders();
String emptyResultsMessage = searchContainer.getEmptyResultsMessage();
RowChecker rowChecker = searchContainer.getRowChecker();

if (end > total) {
	end = total;
}

if (rowChecker != null) {
	if (headerNames != null) {
		headerNames.add(0, rowChecker.getAllRowsCheckBox());
	}
}
%>

<c:if test="<%= (resultRows.size() > 0) || ((resultRows.size() == 0) && (emptyResultsMessage != null)) %>">
	<c:if test="<%= paginate %>">
		<div class="taglib-search-iterator-page-iterator-top">
			<liferay-ui:search-paginator searchContainer="<%= searchContainer %>" />
		</div>
	</c:if>

	<table class="taglib-search-iterator">
	<tr class="portlet-section-header">

	<%
	for (int i = 0; (headerNames != null) && (i < headerNames.size()); i++) {
		String headerName = (String)headerNames.get(i);

		String orderKey = null;
		String orderByType = null;
		boolean orderCurrentHeader = false;

		if (orderableHeaders != null) {
			orderKey = (String)orderableHeaders.get(headerName);

			if (orderKey != null) {
				orderByType = searchContainer.getOrderByType();

				if (orderKey.equals(searchContainer.getOrderByCol())) {
					orderCurrentHeader = true;
				}
			}
		}

		if (orderCurrentHeader) {
			if (orderByType.equals("asc")) {
				orderByType = "desc";
			}
			else {
				orderByType = "asc";
			}
		}
	%>

		<th class="col-<%= i + 1 %>"

			<%--

			// Maximize the width of the second column if and only if the first
			// column is a row checker and there is only one second column.

			--%>

			<c:if test="<%= (rowChecker != null) && (headerNames.size() == 2) && (i == 1) %>">
				width="95%"
			</c:if>
		>
			<c:if test="<%= orderKey != null %>">
				<a href="<%= searchContainer.getIteratorURL().toString() %>&<%= namespace %>orderByCol=<%= orderKey %>&<%= namespace %>orderByType=<%= orderByType %>">
			</c:if>

			<c:if test="<%= orderCurrentHeader %>">
				<i>
			</c:if>

			<%
			String headerNameValue = LanguageUtil.get(pageContext, headerName);
			%>

			<c:choose>
				<c:when test="<%= headerNameValue.equals(StringPool.BLANK) %>">
					<%= StringPool.NBSP %>
				</c:when>
				<c:otherwise>
					<%= headerNameValue %>
				</c:otherwise>
			</c:choose>

			<c:if test="<%= orderCurrentHeader %>">
				</i>
			</c:if>

			<c:if test="<%= orderKey != null %>">
				</a>
			</c:if>
		</th>

	<%
	}
	%>

	</tr>

	<c:if test="<%= (headerNames != null) && (resultRows.size() == 0) && (emptyResultsMessage != null) %>">
		<tr class="portlet-section-body">
			<td align="center" colspan="<%= headerNames.size() %>">
				<%= LanguageUtil.get(pageContext, emptyResultsMessage) %>
			</td>
		</tr>
	</c:if>

	<%
	boolean allRowsIsChecked = true;

	for (int i = 0; i < resultRows.size(); i++) {
		ResultRow row = (ResultRow)resultRows.get(i);

		String className = "portlet-section-alternate";
		String classHoverName = "portlet-section-alternate-hover";

		if (MathUtil.isEven(i)) {
			className = "portlet-section-body";
			classHoverName = "portlet-section-body-hover";
		}

		if (Validator.isNotNull(row.getClassName())) {
			className += " " + row.getClassName();
		}

		if (Validator.isNotNull(row.getClassHoverName())) {
			classHoverName += " " + row.getClassHoverName();
		}

		if (row.isRestricted()) {
			className += " restricted";
			classHoverName += " restricted";
		}

		row.setClassName(className);
		row.setClassHoverName(classHoverName);

		request.setAttribute(WebKeys.SEARCH_CONTAINER_RESULT_ROW, row);

		List entries = row.getEntries();

		if (rowChecker != null) {
			boolean rowIsChecked = rowChecker.isChecked(row.getObject());

			if (!rowIsChecked) {
				allRowsIsChecked = false;
			}

			row.addText(0, rowChecker.getAlign(), rowChecker.getValign(), rowChecker.getColspan(), rowChecker.getRowCheckBox(rowIsChecked, row.getPrimaryKey()));
		}
	%>

		<tr class="<%= className %>"
			<c:if test="<%= searchContainer.isHover() %>">
				onmouseover="this.className = '<%= classHoverName %>';" onmouseout="this.className = '<%= className %>';"
			</c:if>
		>

		<%
		for (int j = 0; j < entries.size(); j++) {
			SearchEntry entry = (SearchEntry)entries.get(j);

			request.setAttribute(WebKeys.SEARCH_CONTAINER_RESULT_ROW_ENTRY, entry);
		%>

			<td align="<%= entry.getAlign() %>" class="col-<%= j + 1 %><%= row.isBold() ? " taglib-search-iterator-highlighted" : "" %>" colspan="<%= entry.getColspan() %>" valign="<%= entry.getValign() %>">

				<%
				entry.print(pageContext);
				%>

			</td>

		<%
		}
		%>

		</tr>

	<%
	}
	%>

	</table>

	<c:if test="<%= (resultRows.size() > 10) && paginate %>">
		<div class="taglib-search-iterator-page-iterator-bottom">
			<liferay-ui:search-paginator searchContainer="<%= searchContainer %>" />
		</div>
	</c:if>

	<c:if test="<%= (rowChecker != null) && (resultRows.size() > 0) && Validator.isNotNull(rowChecker.getAllRowsId()) && allRowsIsChecked %>">
		<script type="text/javascript">
			document.<%= rowChecker.getFormName() %>.<%= rowChecker.getAllRowsId() %>.checked = true;
		</script>
	</c:if>
</c:if>