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

<%@ include file="/html/portlet/software_catalog/init.jsp" %>

<%
String redirect = ParamUtil.getString(request, "redirect");

SCProductEntry productEntry = (SCProductEntry) request.getAttribute(WebKeys.SOFTWARE_CATALOG_PRODUCT_ENTRY);

long productEntryId = BeanParamUtil.getLong(productEntry, request, "productEntryId");

String type = BeanParamUtil.getString(productEntry, request, "type");

Set licenseIds = CollectionFactory.getHashSet();

if ((productEntry != null) && (request.getParameterValues("licenses") == null)) {
	Iterator itr = productEntry.getLicenses().iterator();

	while (itr.hasNext()) {
		SCLicense license = (SCLicense) itr.next();

		licenseIds.add(new Long(license.getLicenseId()));
	}
}
else {
	long[] licenses = ParamUtil.getLongValues(request, "licenses");

	for (int i = 0; i < licenses.length; i++) {
		licenseIds.add(new Long(licenses[i]));
	}
}

List productScreenshots = SCProductScreenshotLocalServiceUtil.getProductScreenshots(productEntryId);

int screenshotsCount = ParamUtil.getInteger(request, "screenshotsCount", productScreenshots.size());
%>

<script type="text/javascript">
	function <portlet:namespace />addScreenShot() {
		document.<portlet:namespace />fm.<portlet:namespace />screenshotsCount.value = "<%= screenshotsCount + 1 %>";
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />removeScreenShot() {
		document.<portlet:namespace />fm.<portlet:namespace />screenshotsCount.value = "<%= screenshotsCount - 1 %>";
		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />saveProductEntry() {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= productEntry == null ? Constants.ADD : Constants.UPDATE %>";
		submitForm(document.<portlet:namespace />fm);
	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/software_catalog/edit_product_entry" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm" enctype="multipart/form-data" onSubmit="<portlet:namespace />saveProductEntry(); return false;">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />productEntryId" type="hidden" value="<%= productEntryId %>" />
<input name="<portlet:namespace />screenshotsCount" type="hidden" value="<%= screenshotsCount %>" />

<liferay-ui:tabs
	names="product"
	backURL="<%= redirect %>"
/>

<liferay-ui:error exception="<%= DuplicateProductEntryModuleIdException.class %>" message="please-enter-a-unique-group-id-and-artifact-id-combination" />
<liferay-ui:error exception="<%= ProductEntryAuthorException.class %>" message="please-enter-a-valid-author" />
<liferay-ui:error exception="<%= ProductEntryLicenseException.class %>" message="please-select-at-least-one-license" />
<liferay-ui:error exception="<%= ProductEntryNameException.class %>" message="please-enter-a-valid-name" />
<liferay-ui:error exception="<%= ProductEntryPageURLException.class %>" message="please-enter-a-valid-page-url" />
<liferay-ui:error exception="<%= ProductEntryScreenshotsException.class %>" message="screenshots-must-contain-a-valid-thumbnail-and-a-valid-full-image" />
<liferay-ui:error exception="<%= ProductEntryShortDescriptionException.class %>" message="please-enter-a-valid-short-description" />
<liferay-ui:error exception="<%= ProductEntryTypeException.class %>" message="please-select-a-valid-type" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="name" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= SCProductEntry.class %>" bean="<%= productEntry %>" field="name" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="type" />
	</td>
	<td>
		<select name="<portlet:namespace/>type">
			<option <%= type.equals(PortletImpl.PLUGIN_TYPE) ? "selected" : "" %> value="<%= PortletImpl.PLUGIN_TYPE %>"><liferay-ui:message key="<%= PortletImpl.PLUGIN_TYPE %>" /></option>
			<option <%= type.equals(ThemeImpl.PLUGIN_TYPE) ? "selected" : "" %> value="<%= ThemeImpl.PLUGIN_TYPE %>"><liferay-ui:message key="<%= ThemeImpl.PLUGIN_TYPE %>" /></option>
			<option <%= type.equals(LayoutTemplateImpl.PLUGIN_TYPE) ? "selected" : "" %> value="<%= LayoutTemplateImpl.PLUGIN_TYPE %>"><liferay-ui:message key="<%= LayoutTemplateImpl.PLUGIN_TYPE %>" /></option>
			<%--<option <%= type.equals("extension") ? "selected" : "" %> value="extension"><liferay-ui:message key="extension" /></option>--%>
		</select>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="licenses" />
	</td>
	<td>
		<select name="<portlet:namespace/>licenses" multiple="true">
			<optgroup label="<liferay-ui:message key="recommended-licenses" />">

				<%
				Iterator itr = SCLicenseLocalServiceUtil.getLicenses(true, true).iterator();

				while (itr.hasNext()) {
					SCLicense license = (SCLicense) itr.next();
				%>

					<option <%= licenseIds.contains(new Long(license.getLicenseId())) ? "selected" : "" %> value="<%= license.getLicenseId() %>"><%= license.getName() %></option>

				<%
				}
				%>

			</optgroup>

			<optgroup label="<liferay-ui:message key="other-licenses" />">

				<%
				itr = SCLicenseLocalServiceUtil.getLicenses(true, false).iterator();

				while (itr.hasNext()) {
					SCLicense license = (SCLicense) itr.next();
				%>

					<option <%= licenseIds.contains(new Long(license.getLicenseId())) ? "selected" : "" %> value="<%= license.getLicenseId() %>"><%= license.getName() %></option>

				<%
				}
				%>

			</optgroup>
		</select>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="author" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= SCProductEntry.class %>" bean="<%= productEntry %>" field="author" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="page-url" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= SCProductEntry.class %>" bean="<%= productEntry %>" field="pageURL" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="tags" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= SCProductEntry.class %>" bean="<%= productEntry %>" field="tags" /> (<liferay-ui:message key="comma-delimited-list" />)
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="short-description" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= SCProductEntry.class %>" bean="<%= productEntry %>" field="shortDescription" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="long-description" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= SCProductEntry.class %>" bean="<%= productEntry %>" field="longDescription" />
	</td>
</tr>

<c:if test="<%= productEntry == null %>">
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
				modelName="<%= SCProductEntry.class.getName() %>"
			/>
		</td>
	</tr>
</c:if>

</table>

<br />

<input type="submit" value="<liferay-ui:message key="save" />" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

<br /><br />

<liferay-ui:tabs names="plugin-repository" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="group-id" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= SCProductEntry.class %>" bean="<%= productEntry %>" field="repoGroupId" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="artifact-id" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= SCProductEntry.class %>" bean="<%= productEntry %>" field="repoArtifactId" />
	</td>
</tr>
</table>

<br />

<liferay-ui:tabs names="screenshots" />

<table class="lfr-table">

<%
for (int i = 0; i < screenshotsCount; i++) {
	SCProductScreenshot productScreenshot = null;

	if (i < productScreenshots.size()) {
		productScreenshot = (SCProductScreenshot)productScreenshots.get(i);
	}
%>

	<tr>
		<td>
			<liferay-ui:message key="thumbnail" />
		</td>
		<td>
			<input class="lfr-input-text" name="<portlet:namespace />thumbnail<%= i %>" type="file" />
		</td>

		<c:if test="<%= productScreenshot != null %>">
			<td rowspan="3" valign="top">
				<table class="lfr-table">
				<tr>
					<td>
						<a href="<%= themeDisplay.getPathImage() %>/software_catalog?img_id=<%= productScreenshot.getThumbnailId() %>&t=<%= ImageServletTokenUtil.getToken(productScreenshot.getThumbnailId()) %>" target="_blank"><liferay-ui:message key="see-thumbnail" /></a>
					</td>
					<td>
						<a href="<%= themeDisplay.getPathImage() %>/software_catalog?img_id=<%= productScreenshot.getFullImageId() %>&t=<%= ImageServletTokenUtil.getToken(productScreenshot.getFullImageId()) %>" target="_blank"><liferay-ui:message key="see-full-image" /></a>
					</td>
				</tr>
				<tr>
					<td colspan="2">
						<liferay-ui:message key="use-existing-images" /> <liferay-ui:input-checkbox param='<%= "preserveScreenshot" + i %>' defaultValue="<%= true %>" />
					</td>
				</tr>
				</table>
			</td>
		</c:if>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="full-image" />
		</td>
		<td>
			<input class="lfr-input-text" name="<portlet:namespace />fullImage<%= i %>" type="file" />
		</td>
	</tr>
	<tr>
		<td colspan="2">
			<br />
		</td>
	</tr>

<%
}
%>
</table>

<input type="button" value="<liferay-ui:message key="add-screenshot" />" onClick="<portlet:namespace />addScreenShot();" />

<c:if test="<%= screenshotsCount > 0 %>">
	<input type="button" value="<liferay-ui:message key="remove-screenshot" />" onClick="<portlet:namespace />removeScreenShot();" />
</c:if>

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />name);
	</script>
</c:if>