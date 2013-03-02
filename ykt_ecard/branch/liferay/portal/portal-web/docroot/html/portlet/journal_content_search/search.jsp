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

<%@ include file="/html/portlet/journal_content_search/init.jsp" %>

<c:choose>
	<c:when test="<%= windowState.equals(WindowState.MAXIMIZED) %>">

		<%
		String defaultKeywords = LanguageUtil.get(pageContext, "search") + "...";
		String unicodeDefaultKeywords = UnicodeFormatter.toString(defaultKeywords);

		String keywords = ParamUtil.getString(request, "keywords", defaultKeywords);
		%>

		<form action="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/journal_content_search/search" /></portlet:renderURL>" method="post" name="<portlet:namespace />fm" onSubmit="submitForm(this); return false;">

		<%
		PortletURL portletURL = renderResponse.createRenderURL();

		portletURL.setWindowState(WindowState.MAXIMIZED);

		portletURL.setParameter("struts_action", "/journal_content_search/search");
		portletURL.setParameter("keywords", keywords);

		List headerNames = new ArrayList();

		headerNames.add("#");
		headerNames.add("name");
		headerNames.add("content");
		headerNames.add("score");

		SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, SearchContainer.DEFAULT_DELTA, portletURL, headerNames, LanguageUtil.format(pageContext, "no-pages-were-found-that-matched-the-keywords-x", "<b>" + Html.escape(keywords) + "</b>"));

		Hits hits = null;

		try {
			hits = CompanyLocalServiceUtil.search(company.getCompanyId(), PortletKeys.JOURNAL, 0, type, keywords);

			ContentHits contentHits = new ContentHits();

			contentHits.setShowListed(showListed);

			contentHits.recordHits(hits, layout.getGroupId(), layout.isPrivateLayout());

			hits = contentHits;

			Hits results = hits.subset(searchContainer.getStart(), searchContainer.getEnd());
			int total = hits.getLength();

			searchContainer.setTotal(total);

			List resultRows = searchContainer.getResultRows();

			for (int i = 0; i < results.getLength(); i++) {
				Document doc = results.doc(i);

				ResultRow row = new ResultRow(doc, i, i);

				// Position

				row.addText(searchContainer.getStart() + i + 1 + StringPool.PERIOD);

				// Title

				String title = doc.get(LuceneFields.TITLE);

				title = StringUtil.highlight(title, keywords);

				row.addText(title);

				// Content

				row.addJSP("/html/portlet/journal_content_search/article_content.jsp");

				// Score

				row.addScore(results.score(i));

				// Add result row

				resultRows.add(row);
			}
		%>

			<table border="0" cellpadding="0" cellspacing="0" width="100%">
			<tr>
				<td>
					<input name="<portlet:namespace />keywords" size="30" type="text" value="<%= Html.escape(keywords) %>" onBlur="if (this.value == '') { this.value = '<%= unicodeDefaultKeywords %>'; }" onFocus="if (this.value == '<%= unicodeDefaultKeywords %>') { this.value = ''; }" />

					<input align="absmiddle" border="0" src="<%= themeDisplay.getPathThemeImages() %>/common/search.png" title="<liferay-ui:message key="search" />" type="image" />
				</td>
				<td align="right">
					<liferay-ui:search-speed searchContainer="<%= searchContainer %>" hits="<%= hits %>" />
				</td>
			</tr>
			</table>

			<br />

			<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />

		<%
		}
		catch (Exception e) {
			_log.error(e.getMessage());
		}
		finally {
			if (hits != null) {
				hits.closeSearcher();
			}
		}
		%>

		</form>

		<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
			<script type="text/javascript">
				if (document.<portlet:namespace />fm.<portlet:namespace />keywords) {
					Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />keywords);
				}
			</script>
		</c:if>
	</c:when>
	<c:otherwise>
		<liferay-ui:journal-content-search />
	</c:otherwise>
</c:choose>

<%!
private static Log _log = LogFactoryUtil.getLog("portal-web.docroot.html.portlet.journal_content_search.search.jsp");
%>