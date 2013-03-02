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
String redirect = ParamUtil.getString(request, "redirect");

JournalTemplate template = (JournalTemplate)request.getAttribute(WebKeys.JOURNAL_TEMPLATE);

long groupId = BeanParamUtil.getLong(template, request, "groupId", portletGroupId.longValue());

String templateId = BeanParamUtil.getString(template, request, "templateId");
String newTemplateId = ParamUtil.getString(request, "newTemplateId");

String structureId = BeanParamUtil.getString(template, request, "structureId");

String structureName = StringPool.BLANK;

if (Validator.isNotNull(structureId)) {
	try {
		JournalStructure structure = JournalStructureLocalServiceUtil.getStructure(groupId, structureId);

		structureName = structure.getName();
	}
	catch (NoSuchStructureException nsse) {
	}
}

String xslContent = request.getParameter("xslContent");

String xsl = xslContent;

if (xslContent != null) {
	xsl = JS.decodeURIComponent(xsl);
}
else {
	xsl = BeanParamUtil.getString(template, request, "xsl");
}

String langType = BeanParamUtil.getString(template, request, "langType", JournalTemplateImpl.LANG_TYPE_VM);

boolean cacheable = BeanParamUtil.getBoolean(template, request, "cacheable");

if (template == null) {
	cacheable = true;
}

boolean smallImage = BeanParamUtil.getBoolean(template, request, "smallImage");
String smallImageURL = BeanParamUtil.getString(template, request, "smallImageURL");
%>

<script type="text/javascript">
	function <portlet:namespace />removeStructure() {
		document.<portlet:namespace />fm.<portlet:namespace />structureId.value = "";

		var nameEl = document.getElementById("<portlet:namespace />structureName");

		nameEl.href = "#";
		nameEl.innerHTML = "";

		document.getElementById("<portlet:namespace />removeStructureButton").disabled = true;
	}

	function <portlet:namespace />saveTemplate() {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= template == null ? Constants.ADD : Constants.UPDATE %>";

		<c:if test="<%= template == null %>">
			document.<portlet:namespace />fm.<portlet:namespace />templateId.value = document.<portlet:namespace />fm.<portlet:namespace />newTemplateId.value;
		</c:if>

		submitForm(document.<portlet:namespace />fm);
	}

	function <portlet:namespace />selectStructure(structureId, structureName) {
		document.<portlet:namespace />fm.<portlet:namespace />structureId.value = structureId;

		var nameEl = document.getElementById("<portlet:namespace />structureName");

		nameEl.href = "<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/journal/edit_structure" /><portlet:param name="redirect" value="<%= currentURL %>" /><portlet:param name="groupId" value="<%= String.valueOf(groupId) %>" /></portlet:renderURL>&<portlet:namespace />structureId=" + structureId;
		nameEl.innerHTML = structureName + "&nbsp;";

		document.getElementById("<portlet:namespace />removeStructureButton").disabled = false;
	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/journal/edit_template" /></portlet:actionURL>" enctype="multipart/form-data" method="post" name="<portlet:namespace />fm" onSubmit="<portlet:namespace />saveTemplate(); return false;">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />groupId" type="hidden" value="<%= groupId %>" />
<input name="<portlet:namespace />templateId" type="hidden" value="<%= templateId %>" />
<input name="<portlet:namespace />xslContent" type="hidden" value="<%= JS.encodeURIComponent(xsl) %>" />

<liferay-ui:tabs
	names="template"
	backURL="<%= redirect %>"
/>

<liferay-ui:error exception="<%= DuplicateTemplateIdException.class %>" message="please-enter-a-unique-id" />
<liferay-ui:error exception="<%= TemplateDescriptionException.class %>" message="please-enter-a-valid-description" />
<liferay-ui:error exception="<%= TemplateIdException.class %>" message="please-enter-a-valid-id" />
<liferay-ui:error exception="<%= TemplateNameException.class %>" message="please-enter-a-valid-name" />

<liferay-ui:error exception="<%= TemplateSmallImageNameException.class %>">

	<%
	String[] imageExtensions = PropsUtil.getArray(PropsUtil.JOURNAL_IMAGE_EXTENSIONS);
	%>

	<liferay-ui:message key="image-names-must-end-with-one-of-the-following-extensions" /> <%= StringUtil.merge(imageExtensions, ", ") %>.
</liferay-ui:error>


<liferay-ui:error exception="<%= TemplateSmallImageSizeException.class %>" message="please-enter-a-file-with-a-valid-file-size" />
<liferay-ui:error exception="<%= TemplateXslException.class %>" message="please-enter-a-valid-script-template" />

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="id" />
	</td>
	<td>
		<c:choose>
			<c:when test="<%= PropsValues.JOURNAL_TEMPLATE_FORCE_AUTOGENERATE_ID %>">
				<c:choose>
					<c:when test="<%= template == null %>">
						<liferay-ui:message key="autogenerate-id" />

						<input name="<portlet:namespace />newTemplateId" type="hidden" value="" />
						<input name="<portlet:namespace />autoTemplateId" type="hidden" value="true" />
					</c:when>
					<c:otherwise>
						<%= templateId %>
					</c:otherwise>
				</c:choose>
			</c:when>
			<c:otherwise>
				<table class="lfr-table">
				<tr>
					<td>
						<c:choose>
							<c:when test="<%= template == null %>">
								<liferay-ui:input-field model="<%= JournalTemplate.class %>" bean="<%= template %>" field="templateId" fieldParam="newTemplateId" defaultValue="<%= newTemplateId %>" />
							</c:when>
							<c:otherwise>
								<%= templateId %>
							</c:otherwise>
						</c:choose>
					</td>
					<td>
						<c:if test="<%= template == null %>">
							<liferay-ui:input-checkbox param="autoTemplateId" />

							<liferay-ui:message key="autogenerate-id" />
						</c:if>
					</td>
				</tr>
				</table>
			</c:otherwise>
		</c:choose>
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="name" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= JournalTemplate.class %>" bean="<%= template %>" field="name" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="description" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= JournalTemplate.class %>" bean="<%= template %>" field="description" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="cacheable" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= JournalTemplate.class %>" bean="<%= template %>" field="cacheable" defaultValue="<%= new Boolean(cacheable) %>" />

		<liferay-ui:icon-help message="journal-template-cacheable-help" />
	</td>
</tr>

<c:if test="<%= template != null %>">
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
				url='<%= PortalUtil.getPortalURL(request) + themeDisplay.getPathMain() + "/journal/get_template?groupId=" + groupId + "&templateId=" + templateId %>'
			/>
		</td>
	</tr>
	<tr>
		<td>
			<liferay-ui:message key="webdav-url" />
		</td>
		<td>
			<liferay-ui:input-resource
				url='<%= PortalUtil.getPortalURL(request) + "/tunnel-web/secure/webdav/journal/" + company.getCompanyId() + "/" + portletGroupId + "/Templates/" + templateId %>'
			/>
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
		<liferay-ui:message key="structure" />
	</td>
	<td>
		<input name="<portlet:namespace />structureId" type="hidden" value="<%= structureId %>" />

		<c:choose>
			<c:when test="<%= (template == null) || (Validator.isNotNull(structureId)) %>">
				<a href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/journal/edit_structure" /><portlet:param name="redirect" value="<%= currentURL %>" /><portlet:param name="groupId" value="<%= String.valueOf(groupId) %>" /><portlet:param name="structureId" value="<%= structureId %>" /></portlet:renderURL>" id="<portlet:namespace />structureName">
				<%= structureName %>
				</a>
			</c:when>
			<c:otherwise>
				<a id="<portlet:namespace />structureName"></a>
			</c:otherwise>
		</c:choose>

		<c:if test="<%= (template == null) || (Validator.isNull(template.getStructureId())) %>">
			<input type="button" value="<liferay-ui:message key="select" />" onClick="var structureWindow = window.open('<portlet:renderURL windowState="<%= LiferayWindowState.POP_UP.toString() %>"><portlet:param name="struts_action" value="/journal/select_structure" /><portlet:param name="groupId" value="<%= String.valueOf(groupId) %>" /></portlet:renderURL>', 'structure', 'directories=no,height=640,location=no,menubar=no,resizable=yes,scrollbars=yes,status=no,toolbar=no,width=680'); void(''); structureWindow.focus();" />

			<input <%= Validator.isNull(structureId) ? "disabled" : "" %> id="<portlet:namespace />removeStructureButton" type="button" value="<liferay-ui:message key="remove" />" onClick="<portlet:namespace />removeStructure();">
		</c:if>
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="language-type" />
	</td>
	<td>
		<select name="<portlet:namespace />langType">

			<%
			for (int i = 0; i < JournalTemplateImpl.LANG_TYPES.length; i++) {
			%>

				<option <%= langType.equals(JournalTemplateImpl.LANG_TYPES[i]) ? "selected" : "" %> value="<%= JournalTemplateImpl.LANG_TYPES[i] %>"><%= JournalTemplateImpl.LANG_TYPES[i].toUpperCase() %></option>

			<%
			}
			%>

		</select>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="script" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />xsl" type="file" />

		<input id="<portlet:namespace />editorButton" type="button" value="<liferay-ui:message key="launch-editor" />" />

		<c:if test="<%= template != null %>">
			<input type="button" value="<liferay-ui:message key="download" />" onClick="self.location = '<%= themeDisplay.getPathMain() %>/journal/get_template?groupId=<%= String.valueOf(template.getGroupId()) %>&templateId=<%= template.getTemplateId() %>&transform=0';" />
		</c:if>
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="format-script" />
	</td>
	<td>
		<liferay-ui:input-checkbox param="formatXsl" />
	</td>
</tr>
<tr>
	<td colspan="2">
		<br />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="small-image-url" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= JournalTemplate.class %>" bean="<%= template %>" field="smallImageURL" />
	</td>
</tr>
<tr>
	<td>
		<span style="font-size: xx-small;">-- <%= LanguageUtil.get(pageContext, "or").toUpperCase() %> --</span> <liferay-ui:message key="small-image" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />smallFile" type="file" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="use-small-image" />
	</td>
	<td>
		<liferay-ui:input-field model="<%= JournalTemplate.class %>" bean="<%= template %>" field="smallImage" />
	</td>
</tr>

<c:if test="<%= template == null %>">
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
				modelName="<%= JournalTemplate.class.getName() %>"
			/>
		</td>
	</tr>
</c:if>

</table>

<br />

<input type="submit" value="<liferay-ui:message key="save" />" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

</form>

<script type="text/javascript">
	Liferay.Util.inlineEditor(
		{
			url: '<portlet:renderURL windowState="<%= LiferayWindowState.EXCLUSIVE.toString() %>"><portlet:param name="struts_action" value="/journal/edit_template_xsl" /></portlet:renderURL>&<portlet:namespace />langType=' + document.<portlet:namespace />fm.<portlet:namespace />langType.value,
			button: '#<portlet:namespace />editorButton',
			textarea: '<portlet:namespace />xslContent'
		}
	);

	<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
		<c:choose>
			<c:when test="<%= PropsValues.JOURNAL_TEMPLATE_FORCE_AUTOGENERATE_ID %>">
				Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />name);
			</c:when>
			<c:otherwise>
				Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace /><%= (template == null) ? "newTemplateId" : "name" %>);
			</c:otherwise>
		</c:choose>
	</c:if>
</script>