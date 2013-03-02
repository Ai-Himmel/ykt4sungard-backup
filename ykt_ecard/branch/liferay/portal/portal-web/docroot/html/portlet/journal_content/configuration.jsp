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

<%@ include file="/html/portlet/journal_content/init.jsp" %>

<%
String cur = ParamUtil.getString(request, "cur");

JournalArticle article = null;

String type = StringPool.BLANK;

try {
	if (Validator.isNotNull(articleId)) {
		article = JournalArticleLocalServiceUtil.getLatestArticle(groupId, articleId);

		groupId = article.getGroupId();
		type = article.getType();
	}
}
catch (NoSuchArticleException nsae) {
}

groupId = ParamUtil.getLong(request, "groupId", groupId);
type = ParamUtil.getString(request, "type", type);
%>

<liferay-portlet:renderURL portletConfiguration="true" varImpl="portletURL" />

<script type="text/javascript">
	function <portlet:namespace />save() {
		AjaxUtil.submit(document.<portlet:namespace />fm1);
	}

	function <portlet:namespace />selectArticle(articleId) {
		document.<portlet:namespace />fm1.<portlet:namespace />articleId.value = articleId;
		document.<portlet:namespace />fm1.<portlet:namespace />templateId.value = "";
		submitForm(document.<portlet:namespace />fm1);
	}
</script>

<form action="<liferay-portlet:actionURL portletConfiguration="true" />" method="post" name="<portlet:namespace />fm1">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="<%= Constants.UPDATE %>" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= portletURL.toString() %>&<portlet:namespace />cur=<%= cur %>" />
<input name="<portlet:namespace />groupId" type="hidden" value="<%= groupId %>" />
<input name="<portlet:namespace />articleId" type="hidden" value="<%= articleId %>" />
<input name="<portlet:namespace />templateId" type="hidden" value="<%= templateId %>" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="portlet-id" />:
	</td>
	<td>
		<%= portletResource %>
	</td>
</tr>
</table>

<br />

<c:if test="<%= article != null %>">
	<div class="portlet-msg-info">
		<liferay-ui:message key="displaying-content" />: <%= articleId %>
	</div>

	<%
	String structureId = article.getStructureId();

	if (Validator.isNotNull(structureId)) {
		List templates = JournalTemplateLocalServiceUtil.getStructureTemplates(groupId, structureId);

		if (templates.size() > 0) {
			if (Validator.isNull(templateId)) {
				templateId = article.getTemplateId();
			}
	%>

			<table class="lfr-table">
			<tr>
				<td>
					<liferay-ui:message key="override-default-template" />
				</td>
				<td>
					<liferay-ui:table-iterator
						list="<%= templates %>"
						listType="com.liferay.portlet.journal.model.JournalTemplate"
						rowLength="3"
						rowPadding="30"
					>

						<%
						boolean templateChecked = false;

						if (templateId.equals(tableIteratorObj.getTemplateId())) {
							templateChecked = true;
						}

						if ((tableIteratorPos.intValue() == 0) && Validator.isNull(templateId)) {
							templateChecked = true;
						}
						%>

						<input <%= templateChecked ? "checked" : "" %> name="<portlet:namespace />radioTemplateId" type="radio" value="<%= tableIteratorObj.getTemplateId() %>" onClick="document.<portlet:namespace />fm1.<portlet:namespace />templateId.value = this.value; <portlet:namespace />save();">

						<a href="<liferay-portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletName="<%= PortletKeys.JOURNAL %>"><portlet:param name="struts_action" value="/journal/edit_template" /><portlet:param name="redirect" value="<%= currentURL %>" /><portlet:param name="groupId" value="<%= String.valueOf(tableIteratorObj.getGroupId()) %>" /><portlet:param name="templateId" value="<%= tableIteratorObj.getTemplateId() %>" /></liferay-portlet:renderURL>">
						<%= Html.escape(tableIteratorObj.getName()) %>
						</a>

						<c:if test="<%= tableIteratorObj.isSmallImage() %>">
							<br />

							<img border="0" hspace="0" src="<%= Validator.isNotNull(tableIteratorObj.getSmallImageURL()) ? tableIteratorObj.getSmallImageURL() : themeDisplay.getPathImage() + "/journal/template?img_id=" + tableIteratorObj.getSmallImageId() + "&t=" + ImageServletTokenUtil.getToken(tableIteratorObj.getSmallImageId()) %>" vspace="0" />
						</c:if>
					</liferay-ui:table-iterator>
				</td>
			</tr>
			</table>

			<br />

	<%
		}
	}
	%>

	<table class="lfr-table">
	<tr>
		<td>
			<liferay-ui:message key="show-available-locales" />
		</td>
		<td>
			<liferay-ui:input-checkbox param="showAvailableLocales" defaultValue="<%= showAvailableLocales %>" onClick='<%= renderResponse.getNamespace() + "save();" %>' />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="enable-ratings" />
		</td>
		<td>
			<liferay-ui:input-checkbox param="enableRatings" defaultValue="<%= enableRatings %>" onClick='<%= renderResponse.getNamespace() + "save();" %>' />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="enable-comments" />
		</td>
		<td>
			<liferay-ui:input-checkbox param="enableComments" defaultValue="<%= enableComments %>" onClick='<%= renderResponse.getNamespace() + "save();" %>' />
		</td>
	</tr>
	</table>
</c:if>

</form>

<c:if test="<%= Validator.isNotNull(articleId) %>">
	<div class="separator"><!-- --></div>
</c:if>

<form action="<liferay-portlet:actionURL portletConfiguration="true" />" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= portletURL.toString() %>&<portlet:namespace />cur=<%= cur %>" />

<liferay-ui:error exception="<%= NoSuchArticleException.class %>" message="the-article-could-not-be-found" />

<%
DynamicRenderRequest dynamicRenderReq = new DynamicRenderRequest(renderRequest);

dynamicRenderReq.setParameter("type", type);
dynamicRenderReq.setParameter("groupId", String.valueOf(groupId));

ArticleSearch searchContainer = new ArticleSearch(dynamicRenderReq, portletURL);
%>

<liferay-ui:search-form
	page="/html/portlet/journal/article_search.jsp"
	searchContainer="<%= searchContainer %>"
>
	<liferay-ui:param name="groupId" value="<%= String.valueOf(groupId) %>" />
	<liferay-ui:param name="type" value="<%= type %>" />
</liferay-ui:search-form>

<div class="separator"><!-- --></div>

<%
OrderByComparator orderByComparator = JournalUtil.getArticleOrderByComparator(searchContainer.getOrderByCol(), searchContainer.getOrderByType());

ArticleSearchTerms searchTerms = (ArticleSearchTerms)searchContainer.getSearchTerms();
%>

<%@ include file="/html/portlet/journal/article_search_results.jspf" %>

<%
List resultRows = searchContainer.getResultRows();

for (int i = 0; i < results.size(); i++) {
	JournalArticle curArticle = (JournalArticle)results.get(i);

	curArticle = curArticle.toEscapedModel();

	ResultRow row = new ResultRow(null, curArticle.getArticleId() + EditArticleAction.VERSION_SEPARATOR + curArticle.getVersion(), i);

	StringMaker sm = new StringMaker();

	sm.append("javascript: ");
	sm.append(renderResponse.getNamespace());
	sm.append("selectArticle('");
	sm.append(curArticle.getArticleId());
	sm.append("');");

	String rowHREF = sm.toString();

	// Article id

	row.addText(curArticle.getArticleId(), rowHREF);

	// Title

	row.addText(curArticle.getTitle(), rowHREF);

	// Version

	row.addText(String.valueOf(curArticle.getVersion()), rowHREF);

	// Modified date

	row.addText(dateFormatDate.format(curArticle.getModifiedDate()), rowHREF);

	// Display date

	row.addText(dateFormatDate.format(curArticle.getDisplayDate()), rowHREF);

	// Author

	row.addText(PortalUtil.getUserName(curArticle.getUserId(), curArticle.getUserName()), rowHREF);

	// Add result row

	resultRows.add(row);
}
%>

<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />

</form>