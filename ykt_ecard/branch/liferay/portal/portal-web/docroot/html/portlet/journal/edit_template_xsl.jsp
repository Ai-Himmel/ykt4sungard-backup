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

<%@ include file="/html/portlet/journal/init.jsp" %>

<%
String langType = ParamUtil.getString(request, "langType");

String editorType = ParamUtil.getString(request, "editorType");

if (Validator.isNotNull(editorType)) {
	portalPrefs.setValue(PortletKeys.JOURNAL, "editor-type", editorType);
}
else {
	editorType = portalPrefs.getValue(PortletKeys.JOURNAL, "editor-type", "html");
}

boolean useEditorCodepress = editorType.equals("codepress");

String defaultContent = null;

if (langType.equals(JournalTemplateImpl.LANG_TYPE_XSL)) {
	defaultContent = ContentUtil.get("com/liferay/portlet/journal/dependencies/template.xsl");
}
else if (langType.equals(JournalTemplateImpl.LANG_TYPE_CSS)) {
	defaultContent = ContentUtil.get("com/liferay/portlet/journal/dependencies/template.css");
}
else {
	defaultContent = ContentUtil.get("com/liferay/portlet/journal/dependencies/template.vm");
}
%>

<script type="text/javascript">
	function <portlet:namespace />getEditorContent() {
		var xslContent = jQuery('input[@name=<portlet:namespace />xslContent]');
		var content = decodeURIComponent(xslContent.val());

		if (content == "") {
			content = "<%= UnicodeFormatter.toString(defaultContent) %>";
		}

		return content;
	}

	function <portlet:namespace />updateEditorType() {

		<%
		String newEditorType = "codepress";

		if (useEditorCodepress) {
			newEditorType = "html";
		}
		%>

		Liferay.Util.switchEditor(
			{
				url: '<portlet:renderURL windowState="<%= LiferayWindowState.EXCLUSIVE.toString() %>"><portlet:param name="struts_action" value="/journal/edit_template_xsl" /><portlet:param name="langType" value="<%= langType %>" /><portlet:param name="editorType" value="<%= newEditorType %>" /></portlet:renderURL>',
				textarea: '<portlet:namespace />xslContent',
				popup: jQuery(document.<portlet:namespace />editorForm).parents('.popup:first')
			}
		);
	}

	function <portlet:namespace />updateTemplateXsl() {
		var xslContent = jQuery('input[@name=<portlet:namespace />xslContent]');
		var content = '';

		<c:choose>
			<c:when test="<%= useEditorCodepress %>">
				content = encodeURIComponent(<portlet:namespace />xslContent.getCode());
			</c:when>
			<c:otherwise>
				content = encodeURIComponent(document.<portlet:namespace />editorForm.<portlet:namespace />xslContent.value);
			</c:otherwise>
		</c:choose>

		xslContent.attr('value', content);

		Liferay.Popup.close(document.<portlet:namespace />editorForm);
	}
</script>

<form method="post" name="<portlet:namespace />editorForm">

<table class="lfr-table">
<tr>
	<td>
		<b><liferay-ui:message key="editor-type" /></b>
	</td>
	<td>
		<select name="<portlet:namespace />editorType" onChange="<portlet:namespace />updateEditorType();">
			<option value="1"><liferay-ui:message key="plain" /></option>
			<option <%= useEditorCodepress ? "selected" : "" %> value="0"><liferay-ui:message key="rich" /></option>
		</select>
	</td>
</tr>
</table>

<br />

<c:choose>
	<c:when test="<%= useEditorCodepress %>">
		<textarea class="codepress html" id="<portlet:namespace />xslContent" name="<portlet:namespace />xslContent" wrap="off"></textarea>
	</c:when>
	<c:otherwise>
		<textarea class="lfr-textarea" id="<portlet:namespace />xslContent" name="<portlet:namespace />xslContent" wrap="off" onKeyDown="Liferay.Util.checkTab(this); Liferay.Util.disableEsc();"></textarea>
	</c:otherwise>
</c:choose>

<br /><br />

<input type="button" value="<liferay-ui:message key="update" />" onClick="<portlet:namespace />updateTemplateXsl();" />

<c:if test="<%= !useEditorCodepress %>">
	<input type="button" value="<liferay-ui:message key="select-and-copy" />" onClick="Liferay.Util.selectAndCopy(document.<portlet:namespace />editorForm.<portlet:namespace />xslContent);" />
</c:if>

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="Liferay.Popup.close(this);" />

</form>

<script type="text/javascript">
	jQuery(
		function() {
			document.<portlet:namespace />editorForm.<portlet:namespace />xslContent.value = <portlet:namespace />getEditorContent();

			Liferay.Util.resizeTextarea('<portlet:namespace />xslContent', <%= useEditorCodepress %>, true);
		}
	);
</script>

<c:if test="<%= useEditorCodepress %>">
	<script src="<%= themeDisplay.getPathContext() %>/html/js/editor/codepress/codepress.js" type="text/javascript"></script>
</c:if>