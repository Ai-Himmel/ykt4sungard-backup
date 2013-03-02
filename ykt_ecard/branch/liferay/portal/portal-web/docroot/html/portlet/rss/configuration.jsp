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

<%@ include file="/html/portlet/rss/init.jsp" %>

<%
String tabs2 = ParamUtil.getString(request, "tabs2");

String redirect = ParamUtil.getString(request, "redirect");

String typeSelection = ParamUtil.getString(request, "typeSelection");

PortletURL configurationActionURL = renderResponse.createActionURL();

configurationActionURL.setParameter("struts_action", "/portlet_configuration/edit_configuration");
configurationActionURL.setParameter("redirect", redirect);
configurationActionURL.setParameter("backURL", redirect);
configurationActionURL.setParameter("portletResource", portletResource);

PortletURL configurationRenderURL = renderResponse.createRenderURL();

configurationRenderURL.setParameter("struts_action", "/portlet_configuration/edit_configuration");
configurationRenderURL.setParameter("redirect", redirect);
configurationRenderURL.setParameter("backURL", redirect);
configurationRenderURL.setParameter("portletResource", portletResource);
%>

<script type="text/javascript">
	<portlet:namespace />addRssRow = function(table) {
		table.insertRow(table.rows.length);

		var row = table.rows[table.rows.length - 1];

		row.insertCell(0);
		row.insertCell(1);
		row.insertCell(2);

		row.cells[0].innerHTML = "<input name=\"<portlet:namespace />title\" />";
		row.cells[1].innerHTML = "<input name=\"<portlet:namespace />url\" style=\"width: <%= ModelHintsDefaults.TEXT_DISPLAY_WIDTH %>px;\" />";
		row.cells[2].innerHTML = "<a href=\"javascript: ;\" onclick=\"Element.remove(this.parentNode.parentNode);\"><img src=\"<%= themeDisplay.getPathThemeImages() %>/common/unsubscribe.png\" /></a>";

		table.appendChild(row);
	}

	function <portlet:namespace />removeSelectionForFooter() {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = 'remove-footer-article';
		submitForm(document.<portlet:namespace />fm, '<%= configurationActionURL.toString() %>');
	}

	function <portlet:namespace />removeSelectionForHeader() {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = 'remove-header-article';
		submitForm(document.<portlet:namespace />fm, '<%= configurationActionURL.toString() %>');
	}

	function <portlet:namespace />selectAsset(resourceId, resourceTitle, assetOrder) {
		if (assetOrder == 1) {
			document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = 'set-footer-article';
		}
		else {
			document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = 'set-header-article';
		}

		document.<portlet:namespace />fm.<portlet:namespace />resourceId.value = resourceId;
		document.<portlet:namespace />fm.<portlet:namespace />resourceTitle.value = resourceTitle;
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />selectionForHeader() {
		document.<portlet:namespace />fm.<portlet:namespace />typeSelection.value = '<%= JournalArticle.class.getName() %>';
		document.<portlet:namespace />fm.<portlet:namespace />assetOrder.value = 0;
		submitForm(document.<portlet:namespace />fm, '<%= configurationRenderURL.toString() %>');
	}

	function <portlet:namespace />selectionForFooter() {
		document.<portlet:namespace />fm.<portlet:namespace />typeSelection.value = '<%= JournalArticle.class.getName() %>';
		document.<portlet:namespace />fm.<portlet:namespace />assetOrder.value = 1;
		submitForm(document.<portlet:namespace />fm, '<%= configurationRenderURL.toString() %>');
	}
</script>

<form action="<liferay-portlet:actionURL portletConfiguration="true" />" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="<%= Constants.UPDATE %>" />
<input name="<portlet:namespace />typeSelection" type="hidden" value="" />
<input name="<portlet:namespace />resourceId" type="hidden" value="" />
<input name="<portlet:namespace />resourceTitle" type="hidden" value="" />
<input name="<portlet:namespace />assetOrder" type="hidden" value="-1" />

<c:choose>
	<c:when test="<%= typeSelection.equals(StringPool.BLANK) %>">
		<liferay-ui:error exception="<%= ValidatorException.class %>">

			<%
			ValidatorException ve = (ValidatorException)errorException;
			%>

			<liferay-ui:message key="the-following-are-invalid-urls" />

			<%
			Enumeration enu = ve.getFailedKeys();

			while (enu.hasMoreElements()) {
				String url = (String)enu.nextElement();
			%>

				<b><%= url %></b><%= (enu.hasMoreElements()) ? ", " : "." %>

			<%
			}
			%>

		</liferay-ui:error>

		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="title" />
			</td>
			<td>
				<liferay-ui:message key="url" />
			</td>
			<td>
				<a href="javascript: ;" onclick="<portlet:namespace />addRssRow(this.parentNode.parentNode.parentNode);"><img src="<%= themeDisplay.getPathThemeImages() %>/common/add_location.png" /></a>
			</td>
		</tr>

		<%
		for (int i = 0; i < urls.length; i++) {
			String title = StringPool.BLANK;

			if (i < titles.length) {
				title = titles[i];
			}
		%>

			<tr>
				<td>
					<input name="<portlet:namespace />title" type="text" value="<%= title %>" />
				</td>
				<td>
					<input class="lfr-input-text" name="<portlet:namespace />url" type="text" value="<%= urls[i] %>" />
				</td>
				<td>
					<a href="javascript: ;" onclick="Element.remove(this.parentNode.parentNode);"><img src="<%= themeDisplay.getPathThemeImages() %>/common/unsubscribe.png" /></a>
				</td>
			</tr>

		<%
		}
		%>

		</table>

		<br />

		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="show-feed-title" />
			</td>
			<td>
				<liferay-ui:input-checkbox param="showFeedTitle" defaultValue="<%= showFeedTitle %>" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="show-feed-published-date" />
			</td>
			<td>
				<liferay-ui:input-checkbox param="showFeedPublishedDate" defaultValue="<%= showFeedPublishedDate %>" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="show-feed-description" />
			</td>
			<td>
				<liferay-ui:input-checkbox param="showFeedDescription" defaultValue="<%= showFeedDescription %>" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="show-feed-image" />
			</td>
			<td>
				<liferay-ui:input-checkbox param="showFeedImage" defaultValue="<%= showFeedImage %>" onClick='<%= "if(this.checked) {document." + renderResponse.getNamespace() + "fm." + renderResponse.getNamespace() + "feedImageAlignment.disabled = '';}else{document." + renderResponse.getNamespace() + "fm." + renderResponse.getNamespace() + "feedImageAlignment.disabled = 'disabled';}" %>' />
			</td>
		</tr>
		<tr>
			<td colspan="2">
				<br />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="num-of-entries-per-feed" />
			</td>
			<td>
				<select name="<portlet:namespace />entriesPerFeed">

					<%
					for (int i = 1; i < 10; i++) {
					%>

						<option <%= (i == entriesPerFeed) ? "selected" : "" %> value="<%= i %>"><%= i %></option>

					<%
					}
					%>

				</select>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="feed-image-alignment" />
			</td>
			<td>
				<select name="<portlet:namespace />feedImageAlignment" <%= !showFeedImage ? "disabled" : "" %>>
					<option <%= feedImageAlignment.equals("left") ? "selected" : "" %> value="left"><liferay-ui:message key="left" /></option>
					<option <%= feedImageAlignment.equals("right") ? "selected" : "" %> value="right"><liferay-ui:message key="right" /></option>
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
				<liferay-ui:message key="header-article" />
			</td>
			<td>
				<%= headerArticleResouceTitle %>

				<input type="button" value="<liferay-ui:message key="select" />" onClick='<%= renderResponse.getNamespace() + "selectionForHeader();" %>' />

				<input type="button" value="<liferay-ui:message key="remove" />" onClick='<%= renderResponse.getNamespace() + "removeSelectionForHeader();" %>' />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="footer-article" />
			</td>
			<td>
				<%= footerArticleResouceTitle %>

				<input type="button" value="<liferay-ui:message key="select" />" onClick='<%= renderResponse.getNamespace() + "selectionForFooter();" %>' />

				<input type="button" value="<liferay-ui:message key="remove" />" onClick='<%= renderResponse.getNamespace() + "removeSelectionForFooter();" %>' />
			</td>
		</tr>
		</table>

		<br />

		<input type="button" value="<liferay-ui:message key="save" />" onClick="submitForm(document.<portlet:namespace />fm);" />
	</c:when>
	<c:when test="<%= typeSelection.equals(JournalArticle.class.getName()) %>">
		<input name="<portlet:namespace />assetType" type="hidden" value="<%= JournalArticle.class.getName() %>" />

		<liferay-ui:message key="select" />: <liferay-ui:message key='<%= "model.resource." + JournalArticle.class.getName() %>' />

		<br /><br />

		<%@ include file="/html/portlet/rss/select_journal_article.jspf" %>
	</c:when>
</c:choose>

</form>