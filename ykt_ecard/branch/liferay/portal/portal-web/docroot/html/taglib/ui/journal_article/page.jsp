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

<%@ page import="com.liferay.portlet.journal.model.JournalArticleDisplay"%>
<%@ page import="com.liferay.portlet.journal.model.JournalArticleResource"%>
<%@ page import="com.liferay.portlet.journal.service.JournalArticleResourceLocalServiceUtil"%>
<%@ page import="com.liferay.portlet.journalcontent.util.JournalContentUtil"%>

<%
long classPK = GetterUtil.getLong((String)request.getAttribute("liferay-ui:journal-article:classPK"));
String languageId = (String)request.getAttribute("liferay-ui:journal-article:languageId");
int articlePage = GetterUtil.getInteger((String)request.getAttribute("liferay-ui:journal-article:articlePage"));
String xmlRequest = (String)request.getAttribute("liferay-ui:journal-article:xmlRequest");
boolean showTitle = GetterUtil.getBoolean((String)request.getAttribute("liferay-ui:journal-article:showTitle"));
boolean showAvailableLocales = GetterUtil.getBoolean((String)request.getAttribute("liferay-ui:journal-article:showAvailableLocales"));

JournalArticleResource articleResource = JournalArticleResourceLocalServiceUtil.getArticleResource(classPK);

JournalArticleDisplay articleDisplay = JournalContentUtil.getDisplay(articleResource.getGroupId(), articleResource.getArticleId(), null, languageId, themeDisplay, articlePage, xmlRequest);

String title = null;

if (articleDisplay != null) {
	title = articleDisplay.getTitle();
}
%>

<c:if test="<%= articleDisplay != null %>">
	<c:if test="<%= showTitle %>">
		<h3 class="journal-content-title"><%= title %></h3>
	</c:if>

	<c:if test="<%= showAvailableLocales %>">

		<%
		String[] availableLocales = articleDisplay.getAvailableLocales();
		%>

		<c:if test="<%= availableLocales.length > 0 %>">
			<div>
				<br />

				<liferay-ui:language languageIds="<%= availableLocales %>" displayStyle="<%= 0 %>" />
			</div>
		</c:if>
	</c:if>

	<%= articleDisplay.getContent() %>
</c:if>