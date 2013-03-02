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
String redirect = ParamUtil.getString(request, "redirect");

String referringPortletResource = ParamUtil.getString(request, "referringPortletResource");

IGImage image = (IGImage)request.getAttribute(WebKeys.IMAGE_GALLERY_IMAGE);

long imageId = BeanParamUtil.getLong(image, request, "imageId");

long folderId = BeanParamUtil.getLong(image, request, "folderId");

String tagsEntries = ParamUtil.getString(renderRequest, "tagsEntries");

Image largeImage = null;

if (image != null) {
	largeImage = ImageLocalServiceUtil.getImage(image.getLargeImageId());
}
%>

<liferay-ui:tabs
	names="image"
	backURL="<%= redirect %>"
/>

<div class="breadcrumbs">
	<%= IGUtil.getBreadcrumbs(folderId, 0, pageContext, renderRequest, renderResponse) %>
</div>

<c:if test="<%= image != null %>">
	<table class="lfr-table">
	<tr>
		<td>
			<liferay-ui:message key="thumbnail" />
		</td>
		<td>
			<a href="<%= themeDisplay.getPathImage() %>/image_gallery?img_id=<%= image.getLargeImageId() %>" target="_blank">
			<img alt="<%= image.getDescription() %>" border="1" src="<%= themeDisplay.getPathImage() %>/image_gallery?img_id=<%= image.getSmallImageId() %>" />
			</a>
		</td>
	</tr>
	<tr>
		<td colspan="2">
			<br />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="height" />
		</td>
		<td>
			<%= largeImage.getHeight() %>
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="width" />
		</td>
		<td>
			<%= largeImage.getWidth() %>
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="size" />
		</td>
		<td>
			<%= TextFormatter.formatKB(largeImage.getSize(), locale) %>k
		</td>
	</tr>
	<tr>
		<td colspan="2">
			<br />
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="url" />
		</td>
		<td>
			<liferay-ui:input-resource
				url='<%= PortalUtil.getPortalURL(request) + themeDisplay.getPathImage() + "/image_gallery?img_id=" + image.getLargeImageId() +"&t=" + ImageServletTokenUtil.getToken(image.getLargeImageId()) %>'
			/>
		</td>
	</tr>
	</table>

	<br />
</c:if>

<%
String uploadProgressId = "igImageUploadProgress";
%>

<portlet:renderURL windowState="<%= LiferayWindowState.POP_UP.toString() %>" var="uploadProgressURL">
	<portlet:param name="struts_action" value="/image_gallery/edit_image" />
	<portlet:param name="redirect" value="<%= redirect %>" />

	<c:if test="<%= Validator.isNotNull(referringPortletResource) %>">
		<portlet:param name="referringPortletResource" value="<%= referringPortletResource %>" />
	</c:if>

	<portlet:param name="uploadProgressId" value="<%= uploadProgressId %>" />
	<portlet:param name="imageId" value="<%= String.valueOf(imageId) %>" />
	<portlet:param name="folderId" value="<%= String.valueOf(folderId) %>" />

	<c:if test="<%= Validator.isNotNull(tagsEntries) %>">
		<portlet:param name="tagsEntries" value="<%= tagsEntries %>" />
	</c:if>
</portlet:renderURL>

<c:if test="<%= image == null %>">
	<script type="text/javascript">
		jQuery(
			function() {
				new Liferay.Upload({
					allowedFileTypes: '<%= StringUtil.merge(PropsValues.IG_IMAGE_EXTENSIONS) %>',
					container: '#<portlet:namespace />fileUpload',
					fileDescription: '<%= StringUtil.merge(PropsValues.IG_IMAGE_EXTENSIONS) %>',
					fallbackContainer: '#<portlet:namespace />fallback',
					maxFileSize: <%= PropsValues.IG_IMAGE_MAX_SIZE %>,
					namespace: '<portlet:namespace />',
					uploadFile: '<liferay-portlet:actionURL windowState="<%= LiferayWindowState.POP_UP.toString() %>" doAsUserId="<%= user.getUserId() %>"><portlet:param name="struts_action" value="/image_gallery/edit_image" /><portlet:param name="<%= Constants.CMD %>" value="<%= Constants.ADD %>" /><portlet:param name="folderId" value="<%= String.valueOf(folderId) %>" /></liferay-portlet:actionURL><liferay-ui:input-permissions-params modelName="<%= IGImage.class.getName() %>" />'
				});
			}
		);
	</script>

	<div class="lfr-upload-container" id="<portlet:namespace />fileUpload"></div>

	<div class="lfr-fallback" id="<portlet:namespace />fallback">
</c:if>

<liferay-ui:upload-progress
	id="<%= uploadProgressId %>"
	iframeSrc="<%= uploadProgressURL %>"
	redirect="<%= redirect %>"
/>

<c:if test="<%= image == null %>">
	</div>
</c:if>