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

<%@ include file="/html/portlet/document_library/init.jsp" %>

<%
String cmd = ParamUtil.getString(request, Constants.CMD);

String redirect = ParamUtil.getString(request, "redirect");

String referringPortletResource = ParamUtil.getString(request, "referringPortletResource");

String uploadProgressId = ParamUtil.getString(request, "uploadProgressId");

DLFileEntry fileEntry = (DLFileEntry)request.getAttribute(WebKeys.DOCUMENT_LIBRARY_FILE_ENTRY);

long folderId = BeanParamUtil.getLong(fileEntry, request, "folderId");
String name = BeanParamUtil.getString(fileEntry, request, "name");

String extension = StringPool.BLANK;

if (fileEntry != null) {
	extension = StringPool.PERIOD + FileUtil.getExtension(fileEntry.getName());
}

Lock lock = null;
Boolean isLocked = Boolean.FALSE;
Boolean hasLock = Boolean.FALSE;

if (fileEntry != null) {
	try {
		lock = LockServiceUtil.getLock(DLFileEntry.class.getName(), DLUtil.getLockId(fileEntry.getFolderId(), fileEntry.getName()));

		isLocked = Boolean.TRUE;

		if (lock.getUserId() == user.getUserId()) {
			hasLock = Boolean.TRUE;
		}
	}
	catch (Exception e) {
	}
}
%>

<script type="text/javascript">
	<c:if test="<%= Validator.isNotNull(cmd) && SessionErrors.isEmpty(renderRequest) %>">
		parent.<%= uploadProgressId %>.sendRedirect();
	</c:if>

	function <portlet:namespace />saveFileEntry() {
		parent.<%= uploadProgressId %>.startProgress();

		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= fileEntry == null ? Constants.ADD : Constants.UPDATE %>";
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />selectFolder(folderId, folderName) {
		if (document.<portlet:namespace />fm.<portlet:namespace />folderId.value <= 0) {
			document.<portlet:namespace />fm.<portlet:namespace />folderId.value = folderId;
		}

		document.<portlet:namespace />fm.<portlet:namespace />newFolderId.value = folderId;

		var nameEl = document.getElementById("<portlet:namespace />folderName");

		nameEl.href = "javascript: parent.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/document_library/view" /></portlet:renderURL>&<portlet:namespace />folderId=" + folderId + "'; void('');";
		nameEl.innerHTML = folderName + "&nbsp;";
	}
</script>

<form action="<portlet:actionURL windowState="<%= LiferayWindowState.POP_UP.toString() %>"><portlet:param name="struts_action" value="/document_library/edit_file_entry" /></portlet:actionURL>" enctype="multipart/form-data" method="post" name="<portlet:namespace />fm" onSubmit="<portlet:namespace />saveFileEntry(); return false;">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />referringPortletResource" type="hidden" value="<%= referringPortletResource %>" />
<input name="<portlet:namespace />uploadProgressId" type="hidden" value="<%= uploadProgressId %>" />
<input name="<portlet:namespace />folderId" type="hidden" value="<%= folderId %>" />
<input name="<portlet:namespace />newFolderId" type="hidden" value="" />
<input name="<portlet:namespace />name" type="hidden" value="<%= name %>" />

<liferay-ui:error exception="<%= DuplicateFileException.class %>" message="please-enter-a-unique-document-name" />
<liferay-ui:error exception="<%= DuplicateFolderNameException.class %>" message="please-enter-a-unique-document-name" />

<liferay-ui:error exception="<%= FileNameException.class %>">
	<liferay-ui:message key="document-names-must-end-with-one-of-the-following-extensions" /> <%= StringUtil.merge(PropsValues.DL_FILE_EXTENSIONS, ", ") %>.
</liferay-ui:error>

<liferay-ui:error exception="<%= NoSuchFolderException.class %>" message="please-enter-a-valid-folder" />

<liferay-ui:error exception="<%= SourceFileNameException.class %>">
	<liferay-ui:message key="document-extensions-does-not-match" />
</liferay-ui:error>

<liferay-ui:error exception="<%= FileSizeException.class %>" message="please-enter-a-file-with-a-valid-file-size" />

<liferay-ui:tags-error />

<%
String fileMaxSize = String.valueOf(PropsValues.DL_FILE_MAX_SIZE / 1024);
%>

<c:if test='<%= !fileMaxSize.equals("0") %>'>
	<%= LanguageUtil.format(pageContext, "upload-documents-no-larger-than-x-k", fileMaxSize, false) %>

	<br /><br />
</c:if>

<table class="lfr-table">

<c:if test="<%= ((fileEntry != null) || (folderId <= 0)) %>">
	<tr>
		<td>
			<liferay-ui:message key="folder" />
		</td>
		<td>

			<%
			String folderName = StringPool.BLANK;

			if (folderId > 0) {
				DLFolder folder = DLFolderLocalServiceUtil.getFolder(folderId);

				folder = folder.toEscapedModel();

				folderId = folder.getFolderId();
				folderName = folder.getName();
			}

			%>

			<a href="javascript: parent.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/document_library/view" /><portlet:param name="folderId" value="<%= String.valueOf(folderId) %>" /></portlet:renderURL>'; void('');" id="<portlet:namespace />folderName">
			<%= folderName %></a>

			<input type="button" value="<liferay-ui:message key="select" />" onClick="var folderWindow = window.open('<portlet:renderURL windowState="<%= LiferayWindowState.POP_UP.toString() %>"><portlet:param name="struts_action" value="/document_library/select_folder" /><portlet:param name="folderId" value="<%= String.valueOf(folderId) %>" /></portlet:renderURL>', 'folder', 'directories=no,height=640,location=no,menubar=no,resizable=yes,scrollbars=no,status=no,toolbar=no,width=680'); void(''); folderWindow.focus();" />
		</td>
	</tr>
	<tr>
		<td colspan="2">
			<br />
		</td>
	</tr>
</c:if>

<tr>
	<td>
		<liferay-ui:message key="file" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />file" type="file" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="title" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= DLFileEntry.class %>" bean="<%= fileEntry %>" field="title" /><%= extension %>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="description" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= DLFileEntry.class %>" bean="<%= fileEntry %>" field="description" />
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="tags" />
	</td>
	<td>

		<%
		long classPK = 0;

		if (fileEntry != null) {
			classPK = fileEntry.getFileEntryId();
		}
		%>

		<liferay-ui:tags-selector
			className="<%= DLFileEntry.class.getName() %>"
			classPK="<%= classPK %>"
			hiddenInput="tagsEntries"
		/>
	</td>
</tr>

<%
if (fileEntry == null) {
	request.setAttribute(WebKeys.DOCUMENT_LIBRARY_FILE_ENTRY, new DLFileEntryImpl());
}
%>

<%@ include file="/html/portlet/document_library/edit_file_entry_form_extra_fields.jsp" %>

<%
if (fileEntry == null) {
	request.removeAttribute(WebKeys.DOCUMENT_LIBRARY_FILE_ENTRY);
}
%>

<c:if test="<%= fileEntry == null %>">
	<tr>
		<td colspan="2">
			<br />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="permissions" />
		</td>
		<td>
			<liferay-ui:input-permissions
				modelName="<%= DLFileEntry.class.getName() %>"
			/>
		</td>
	</tr>
</c:if>

</table>

<br />

<input <%= isLocked.booleanValue() && !hasLock.booleanValue() ? "disabled" : "" %> type="submit" value="<liferay-ui:message key="save" />">

<c:if test="<%= (fileEntry != null) && ((isLocked.booleanValue() && hasLock.booleanValue()) || !isLocked.booleanValue()) %>">
	<c:choose>
		<c:when test="<%= !hasLock.booleanValue() %>">
			<input type="button" value="<liferay-ui:message key="lock" />" onClick="parent.<portlet:namespace />lock();" />
		</c:when>
		<c:otherwise>
			<input type="button" value="<liferay-ui:message key="unlock" />" onClick="parent.<portlet:namespace />unlock();" />
		</c:otherwise>
	</c:choose>
</c:if>

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="parent.location = '<%= redirect %>';" />

</form>

<script type="text/javascript">
	<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />file);
	</c:if>

	jQuery(document).ready(
		function() {
			parent.<%= uploadProgressId %>.updateIFrame(document.<portlet:namespace />fm.offsetHeight);
		}
	);
</script>