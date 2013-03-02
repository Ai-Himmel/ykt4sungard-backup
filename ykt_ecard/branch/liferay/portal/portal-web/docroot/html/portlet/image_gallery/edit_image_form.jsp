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

<%@ include file="/html/portlet/image_gallery/init.jsp" %>

<%
String cmd = ParamUtil.getString(request, Constants.CMD);

String redirect = ParamUtil.getString(request, "redirect");

String referringPortletResource = ParamUtil.getString(request, "referringPortletResource");

String uploadProgressId = ParamUtil.getString(request, "uploadProgressId");

IGImage image = (IGImage)request.getAttribute(WebKeys.IMAGE_GALLERY_IMAGE);

long imageId = BeanParamUtil.getLong(image, request, "imageId");

long folderId = BeanParamUtil.getLong(image, request, "folderId");
%>

<script type="text/javascript">
	<c:if test="<%= Validator.isNotNull(cmd) && SessionErrors.isEmpty(renderRequest) %>">
		parent.<%= uploadProgressId %>.sendRedirect();
	</c:if>

	function <portlet:namespace />saveImage() {
		parent.<%= uploadProgressId %>.startProgress();

		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= image == null ? Constants.ADD : Constants.UPDATE %>";
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />selectFolder(folderId, folderName) {
		document.<portlet:namespace />fm.<portlet:namespace />folderId.value = folderId;

		var nameEl = document.getElementById("<portlet:namespace />folderName");

		nameEl.href = "<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/image_gallery/view" /></portlet:renderURL>&<portlet:namespace />folderId=" + folderId;
		nameEl.innerHTML = folderName + "&nbsp;";
	}
</script>

<form action="<portlet:actionURL windowState="<%= LiferayWindowState.POP_UP.toString() %>"><portlet:param name="struts_action" value="/image_gallery/edit_image" /></portlet:actionURL>" enctype="multipart/form-data" method="post" name="<portlet:namespace />fm" onSubmit="<portlet:namespace />saveImage(); return false;">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />referringPortletResource" type="hidden" value="<%= referringPortletResource %>" />
<input name="<portlet:namespace />uploadProgressId" type="hidden" value="<%= uploadProgressId %>" />
<input name="<portlet:namespace />imageId" type="hidden" value="<%= imageId %>" />
<input name="<portlet:namespace />folderId" type="hidden" value="<%= folderId %>" />

<liferay-ui:error exception="<%= ImageNameException.class %>">
	<liferay-ui:message key="image-names-must-end-with-one-of-the-following-extensions" /> <%= StringUtil.merge(PropsValues.IG_IMAGE_EXTENSIONS, ", ") %>.
</liferay-ui:error>

<liferay-ui:error exception="<%= ImageSizeException.class %>" message="please-enter-a-file-with-a-valid-file-size" />
<liferay-ui:error exception="<%= NoSuchFolderException.class %>" message="please-enter-a-valid-folder" />

<liferay-ui:tags-error />

<%
String imageMaxSize = String.valueOf(PropsValues.IG_IMAGE_MAX_SIZE / 1024);
%>

<c:if test='<%= !imageMaxSize.equals("0") %>'>
	<%= LanguageUtil.format(pageContext, "upload-images-no-larger-than-x-k", imageMaxSize, false) %>

	<br /><br />
</c:if>

<table class="lfr-table">

<c:if test="<%= ((image != null) || (folderId <= 0)) %>">
	<tr>
		<td>
			<liferay-ui:message key="folder" />
		</td>
		<td>

			<%
			String folderName = StringPool.BLANK;

			if (folderId > 0) {
				IGFolder folder = IGFolderLocalServiceUtil.getFolder(folderId);

				folder = folder.toEscapedModel();

				folderId = folder.getFolderId();
				folderName = folder.getName();
			}
			%>

			<a href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/image_gallery/view" /><portlet:param name="folderId" value="<%= String.valueOf(folderId) %>" /></portlet:renderURL>" id="<portlet:namespace />folderName">
			<%= folderName %></a>

			<input type="button" value="<liferay-ui:message key="select" />" onClick="var folderWindow = window.open('<portlet:renderURL windowState="<%= LiferayWindowState.POP_UP.toString() %>"><portlet:param name="struts_action" value="/image_gallery/select_folder" /><portlet:param name="folderId" value="<%= String.valueOf(folderId) %>" /></portlet:renderURL>', 'folder', 'directories=no,height=640,location=no,menubar=no,resizable=yes,scrollbars=no,status=no,toolbar=no,width=680'); void(''); folderWindow.focus();" />
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
		<liferay-ui:message key="description" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= IGImage.class %>" bean="<%= image %>" field="description" />
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

		if (image != null) {
			classPK = image.getImageId();
		}
		%>

		<liferay-ui:tags-selector
			className="<%= IGImage.class.getName() %>"
			classPK="<%= classPK %>"
			hiddenInput="tagsEntries"
		/>
	</td>
</tr>

<c:if test="<%= image == null %>">
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
				modelName="<%= IGImage.class.getName() %>"
			/>
		</td>
	</tr>
</c:if>

</table>

<br />

<input type="submit" value="<liferay-ui:message key="save" />" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="parent.location = '<%= redirect %>';" />

</form>

<script type="text/javascript">
	<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />file);
	</c:if>

	jQuery(document).ready(function() {
		parent.<%= uploadProgressId %>.updateIFrame(document.<portlet:namespace />fm.offsetHeight);
	});
</script>