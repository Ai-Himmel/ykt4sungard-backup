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

<%@ include file="/html/portlet/wiki/init.jsp" %>

<liferay-util:include page="/html/portlet/wiki/node_tabs.jsp" />

<%
String redirect = ParamUtil.getString(request, "redirect");

WikiNode node = (WikiNode)request.getAttribute(WebKeys.WIKI_NODE);
WikiPage wikiPage = (WikiPage)request.getAttribute(WebKeys.WIKI_PAGE);

long nodeId = BeanParamUtil.getLong(wikiPage, request, "nodeId");
String title = BeanParamUtil.getString(wikiPage, request, "title");

String content = BeanParamUtil.getString(wikiPage, request, "content");
String format = BeanParamUtil.getString(wikiPage, request, "format");
%>

<script type="text/javascript">
	function <portlet:namespace />changeFormat(formatSel) {
		<c:if test="<%= format.equals(WikiPageImpl.HTML_FORMAT) %>">
			document.<portlet:namespace />fm.<portlet:namespace />content.value = window.<portlet:namespace />editor.getHTML();
		</c:if>

		submitForm(document.<portlet:namespace />fm);
	}

	<c:if test="<%= format.equals(WikiPageImpl.HTML_FORMAT) %>">
		function initEditor() {
			return "<%= UnicodeFormatter.toString(content) %>";
		}
	</c:if>

	function <portlet:namespace />savePage() {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= Constants.UPDATE %>";

		<c:if test="<%= format.equals(WikiPageImpl.HTML_FORMAT) %>">
			document.<portlet:namespace />fm.<portlet:namespace />content.value = window.<portlet:namespace />editor.getHTML();
		</c:if>

		submitForm(document.<portlet:namespace />fm);
	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/wiki/edit_page" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm" onSubmit="<portlet:namespace />savePage(); return false;">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />nodeId" type="hidden" value="<%= nodeId %>" />
<input name="<portlet:namespace />title" type="hidden" value="<%= title %>" />

<liferay-ui:tags-error />

<%@ include file="/html/portlet/wiki/page_name.jspf" %>

<table class="lfr-table">
<tr>
	<td>
		<b><liferay-ui:message key="format" /></b>
	</td>
	<td>
		<select name="<portlet:namespace />format" onChange="<portlet:namespace />changeFormat(this);">
			<option <%= format.equals(WikiPageImpl.CLASSIC_WIKI_FORMAT) ? "selected" : "" %> value="classic_wiki"><liferay-ui:message key="classic-wiki" /></option>
			<option <%= format.equals(WikiPageImpl.HTML_FORMAT) ? "selected" : "" %> value="html">HTML</option>
			<option <%= format.equals(WikiPageImpl.PLAIN_TEXT_FORMAT) ? "selected" : "" %> value="plain_text"><liferay-ui:message key="plain-text" /></option>
		</select>
	</td>
</tr>
</table>

<br />

<div>
	<c:choose>
		<c:when test="<%= format.equals(WikiPageImpl.CLASSIC_WIKI_FORMAT) %>">
			<%@ include file="/html/portlet/wiki/edit_page_syntax_help.jspf" %>
		</c:when>
		<c:when test="<%= format.equals(WikiPageImpl.HTML_FORMAT) %>">
			<liferay-ui:input-editor editorImpl="<%= EDITOR_WYSIWYG_IMPL_KEY %>" width="100%" />

			<input name="<portlet:namespace />content" type="hidden" value="" />
		</c:when>
		<c:otherwise>
			<liferay-ui:input-field model="<%= WikiPage.class %>" bean="<%= wikiPage %>" field="content" />
		</c:otherwise>
	</c:choose>
</div>

<br />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="tags" />
	</td>
	<td>

		<%
		long classPK = wikiPage.getResourcePrimKey();
		%>

		<liferay-ui:tags-selector
			className="<%= WikiPage.class.getName() %>"
			classPK="<%= classPK %>"
			hiddenInput="tagsEntries"
		/>
	</td>
</tr>
</table>

<br />

<input type="submit" value="<liferay-ui:message key="save" />" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) && !format.equals(WikiPageImpl.HTML_FORMAT) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />content);
	</script>
</c:if>

<%!
public static final String EDITOR_WYSIWYG_IMPL_KEY = "editor.wysiwyg.portal-web.docroot.html.portlet.wiki.edit_page.jsp";
%>