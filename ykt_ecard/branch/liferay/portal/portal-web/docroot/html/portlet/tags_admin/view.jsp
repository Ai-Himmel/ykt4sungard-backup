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

<%@ include file="/html/portlet/tags_admin/init.jsp" %>

<form id="<portlet:namespace />fm">

<fieldset id="<portlet:namespace />searchEntriesFields">
	<legend><liferay-ui:message key="search-tag" /></legend>

	<liferay-ui:message key="enter-text-below-to-refine-the-list-of-tags" />

	<br /><br />

	<input id="<portlet:namespace />keywordsInput" type="text" size="40"/>

	<span id="<portlet:namespace />searchPropertiesSpan" style="padding-left: 10px;"></span>

	<br /><br />

	<liferay-ui:message key="click-on-any-tag-to-edit-it" />

	<div id="<portlet:namespace />searchResultsDiv" /></div>
</fieldset>

<fieldset id="<portlet:namespace />editEntryFields">
	<legend><liferay-ui:message key="edit-tag" /></legend>

	<liferay-ui:message key="tag-value" />

	<br />

	<input id="<portlet:namespace />editEntryNameInput" type="text" value="" />

	<%--<input id="<portlet:namespace />updateEntryButton" type="button" value="<liferay-ui:message key="copy" />" />--%>

	<br /><br />

	<liferay-ui:message key="properties" />

	<table border="0" cellpadding="0" cellspacing="0" id="<portlet:namespace />propertiesTable"></table>

	<input id="<portlet:namespace />addPropertyButton" type="button" value="<liferay-ui:message key="add-property" />" />

	<hr />

	<input id="<portlet:namespace />updateEntryButton" type="button" value="<liferay-ui:message key="save" />" />

	<input id="<portlet:namespace />deleteEntryButton" type="button" value="<liferay-ui:message key="delete" />" />

	<input id="<portlet:namespace />cancelEditEntryButton" type="button" value="<liferay-ui:message key="cancel" />" />
</fieldset>

<fieldset id="<portlet:namespace />addEntryFields">
	<legend><liferay-ui:message key="add-tag" /></legend>

	<input id="<portlet:namespace />addEntryNameInput" type="text" />

	<span id="<portlet:namespace />addToCategorySpan" style="padding-left: 10px;"></span>

	<input id="<portlet:namespace />addCategoryNameInput" type="text" value="" />

	<input id="<portlet:namespace />addEntryButton" type="button" value="<liferay-ui:message key="save" />" />
</fieldset>

</form>

<script type="text/javascript">
	var <portlet:namespace />tagsAdmin = new Liferay.Portlet.TagsAdmin(
		{
			instanceVar: "<portlet:namespace />tagsAdmin",
			addCategoryNameInput: "<portlet:namespace />addCategoryNameInput",
			addEntryButton: "<portlet:namespace />addEntryButton",
			addEntryNameInput: "<portlet:namespace />addEntryNameInput",
			addPropertyButton: "<portlet:namespace />addPropertyButton",
			addToCategorySpan: "<portlet:namespace />addToCategorySpan",
			cancelEditEntryButton: "<portlet:namespace />cancelEditEntryButton",
			deleteEntryButton: "<portlet:namespace />deleteEntryButton",
			editEntryFields: "<portlet:namespace />editEntryFields",
			editEntryNameInput: "<portlet:namespace />editEntryNameInput",
			form: "<portlet:namespace />fm",
			keywordsInput: "<portlet:namespace />keywordsInput",
			propertiesTable: "<portlet:namespace />propertiesTable",
			searchPropertiesSpan: "<portlet:namespace />searchPropertiesSpan",
			searchResultsDiv: "<portlet:namespace />searchResultsDiv",
			updateEntryButton: "<portlet:namespace />updateEntryButton"
		}
	);
</script>