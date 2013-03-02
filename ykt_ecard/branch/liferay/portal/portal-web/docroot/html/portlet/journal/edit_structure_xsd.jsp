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
String editorType = ParamUtil.getString(request, "editorType");

if (Validator.isNotNull(editorType)) {
	portalPrefs.setValue(PortletKeys.JOURNAL, "editor-type", editorType);
}
else {
	editorType = portalPrefs.getValue(PortletKeys.JOURNAL, "editor-type", "html");
}

boolean useEditorCodepress = editorType.equals("codepress");
%>

<script type="text/javascript">
	function getEditorContent() {
		return <portlet:namespace />getXsd();
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
				url: '<portlet:renderURL windowState="<%= LiferayWindowState.EXCLUSIVE.toString() %>"><portlet:param name="struts_action" value="/journal/edit_structure_xsd" /><portlet:param name="editorType" value="<%= newEditorType %>" /></portlet:renderURL>',
				textarea: '<portlet:namespace />xsdContent',
				popup: jQuery(document.<portlet:namespace />editorForm).parents('.popup:first')
			}
		);
	}

	function <portlet:namespace />updateStructureXsd() {
		document.<portlet:namespace />fm.scroll.value = "<portlet:namespace />xsd";

		var xsdContent = jQuery('input[@name=<portlet:namespace />xsd]');
		var content = '';

		<c:choose>
			<c:when test="<%= useEditorCodepress %>">
				content = <portlet:namespace />xsdContent.getCode();
			</c:when>
			<c:otherwise>
				content = document.<portlet:namespace />editorForm.<portlet:namespace />xsdContent.value;
			</c:otherwise>
		</c:choose>

		xsdContent.attr('value', content);

		Liferay.Popup.close(document.<portlet:namespace />editorForm);

		submitForm(document.<portlet:namespace />fm);
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
		<textarea class="codepress html" id="<portlet:namespace />xsdContent" name="<portlet:namespace />xsdContent" wrap="off"></textarea>
	</c:when>
	<c:otherwise>
		<textarea class="lfr-textarea" id="<portlet:namespace />xsdContent" name="<portlet:namespace />xsdContent" wrap="off" onKeyDown="Liferay.Util.checkTab(this); Liferay.Util.disableEsc();"></textarea>
	</c:otherwise>
</c:choose>

<br /><br />

<input type="button" value="<liferay-ui:message key="update" />" onClick="<portlet:namespace />updateStructureXsd();" />

<c:if test="<%= !useEditorCodepress %>">
	<input type="button" value="<liferay-ui:message key="select-and-copy" />" onClick="Liferay.Util.selectAndCopy(document.<portlet:namespace />editorForm.<portlet:namespace />xsdContent);" />
</c:if>

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="Liferay.Popup.close(this);" />

</form>

<script type="text/javascript">
	jQuery(
		function() {
			document.<portlet:namespace />editorForm.<portlet:namespace />xsdContent.value = getEditorContent();

			Liferay.Util.resizeTextarea('<portlet:namespace />xsdContent', <%= useEditorCodepress %>);
		}
	);
</script>

<c:if test="<%= useEditorCodepress %>">
	<script src="<%= themeDisplay.getPathContext() %>/html/js/editor/codepress/codepress.js" type="text/javascript"></script>
</c:if>