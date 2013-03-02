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

<%@ include file="/html/portlet/bookmarks/init.jsp" %>

<%
String redirect = ParamUtil.getString(request, "redirect");

String referringPortletResource = ParamUtil.getString(request, "referringPortletResource");

BookmarksEntry entry = (BookmarksEntry)request.getAttribute(WebKeys.BOOKMARKS_ENTRY);

long entryId = BeanParamUtil.getLong(entry, request, "entryId");

long folderId = BeanParamUtil.getLong(entry, request, "folderId");
%>

<script type="text/javascript">
	function <portlet:namespace />saveEntry() {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= entry == null ? Constants.ADD : Constants.UPDATE %>";
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />selectFolder(folderId, folderName) {
		document.<portlet:namespace />fm.<portlet:namespace />folderId.value = folderId;

		var nameEl = document.getElementById("<portlet:namespace />folderName");

		nameEl.href = "<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/bookmarks/view" /></portlet:renderURL>&<portlet:namespace />folderId=" + folderId;
		nameEl.innerHTML = folderName + "&nbsp;";
	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/bookmarks/edit_entry" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm" onSubmit="<portlet:namespace />saveEntry(); return false;">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />referringPortletResource" type="hidden" value="<%= referringPortletResource %>" />
<input name="<portlet:namespace />entryId" type="hidden" value="<%= entryId %>" />
<input name="<portlet:namespace />folderId" type="hidden" value="<%= folderId %>" />

<liferay-ui:tabs
	names="entry"
	backURL="<%= redirect %>"
/>

<liferay-ui:error exception="<%= EntryURLException.class %>" message="please-enter-a-valid-url" />
<liferay-ui:error exception="<%= NoSuchFolderException.class %>" message="please-enter-a-valid-folder" />

<liferay-ui:tags-error />

<c:if test="<%= folderId > 0 %>">
	<div class="breadcrumbs">
		<%= BookmarksUtil.getBreadcrumbs(folderId, -1, pageContext, renderRequest, renderResponse) %>
	</div>
</c:if>

<table class="lfr-table">

<c:if test="<%= ((entry != null) || (folderId <= 0)) %>">
	<tr>
		<td>
			<liferay-ui:message key="folder" />
		</td>
		<td>

			<%
			String folderName = StringPool.BLANK;

			if (folderId > 0) {
				BookmarksFolder folder = BookmarksFolderLocalServiceUtil.getFolder(folderId);

				folderId = folder.getFolderId();
				folderName = folder.getName();
			}
			%>

			<a href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/bookmarks/view" /><portlet:param name="folderId" value="<%= String.valueOf(folderId) %>" /></portlet:renderURL>" id="<portlet:namespace />folderName">
			<%= folderName %></a>

			<input type="button" value="<liferay-ui:message key="select" />" onClick="var folderWindow = window.open('<portlet:renderURL windowState="<%= LiferayWindowState.POP_UP.toString() %>"><portlet:param name="struts_action" value="/bookmarks/select_folder" /><portlet:param name="folderId" value="<%= String.valueOf(folderId) %>" /></portlet:renderURL>', 'folder', 'directories=no,height=640,location=no,menubar=no,resizable=yes,scrollbars=no,status=no,toolbar=no,width=680'); void(''); folderWindow.focus();" />
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
		<liferay-ui:message key="name" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= BookmarksEntry.class %>" bean="<%= entry %>" field="name" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="url" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= BookmarksEntry.class %>" bean="<%= entry %>" field="url" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="description" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= BookmarksEntry.class %>" bean="<%= entry %>" field="comments" />
	</td>
</tr>

<c:if test="<%= entry != null %>">
	<tr>
		<td>
			<liferay-ui:message key="visits" />
		</td>
		<td>
			<%= entry.getVisits() %>
		</td>
	</tr>
</c:if>

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

		if (entry != null) {
			classPK = entry.getEntryId();
		}
		%>

		<liferay-ui:tags-selector
			className="<%= BookmarksEntry.class.getName() %>"
			classPK="<%= classPK %>"
			hiddenInput="tagsEntries"
		/>
	</td>
</tr>

<c:if test="<%= entry == null %>">
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
				modelName="<%= BookmarksEntry.class.getName() %>"
			/>
		</td>
	</tr>
</c:if>

</table>

<br />

<input type="submit" value="<liferay-ui:message key="save" />" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />name);
	</script>
</c:if>