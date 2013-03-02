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

<%@ include file="/html/portlet/communities/init.jsp" %>

<%
Group group = (Group)request.getAttribute("edit_pages.jsp-group");
long groupId = ((Long)request.getAttribute("edit_pages.jsp-groupId")).longValue();
boolean privateLayout = ((Boolean)request.getAttribute("edit_pages.jsp-privateLayout")).booleanValue();
Layout selLayout = (Layout)request.getAttribute("edit_pages.jsp-selLayout");

String currentLanguageId = LanguageUtil.getLanguageId(request);
Locale currentLocale = LocaleUtil.fromLanguageId(currentLanguageId);
Locale defaultLocale = LocaleUtil.getDefault();
String defaultLanguageId = LocaleUtil.toLanguageId(defaultLocale);

Locale[] locales = LanguageUtil.getAvailableLocales();

String type = BeanParamUtil.getString(selLayout, request, "type");
String friendlyURL = BeanParamUtil.getString(selLayout, request, "friendlyURL");
%>

<table border="0" cellpadding="0" cellspacing="0" width="100%">
<tr>
	<td>
		<table class="lfr-table">
		<tr>
			<td></td>
			<td>
				<liferay-ui:message key="default-language" />: <%= defaultLocale.getDisplayName(defaultLocale) %>
			</td>
			<td>
				<liferay-ui:message key="localized-language" />:

				<select id="<portlet:namespace />languageId" onChange="<portlet:namespace />updateLanguage();">
					<option value="" />

					<%
					for (int i = 0; i < locales.length; i++) {
						if (locales[i].equals(defaultLocale)) {
							continue;
						}
					%>

						<option <%= (currentLanguageId.equals(LocaleUtil.toLanguageId(locales[i]))) ? "selected" : "" %> value="<%= LocaleUtil.toLanguageId(locales[i]) %>"><%= locales[i].getDisplayName(locales[i]) %></option>

					<%
					}
					%>

				</select>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="name" />
			</td>
			<td>
				<input id="<portlet:namespace />name_<%= defaultLanguageId %>" name="<portlet:namespace />name_<%= defaultLanguageId %>" size="30" type="text" value="<%= selLayout.getName(defaultLocale) %>" />
			</td>
			<td>

				<%
				for (int i = 0; i < locales.length; i++) {
					if (locales[i].equals(defaultLocale)) {
						continue;
					}
				%>

					<input id="<portlet:namespace />name_<%= LocaleUtil.toLanguageId(locales[i]) %>" name="<portlet:namespace />name_<%= LocaleUtil.toLanguageId(locales[i]) %>" type="hidden" value="<%= selLayout.getName(locales[i], false) %>" />

				<%
				}
				%>

				<input id="<portlet:namespace />name_temp" size="30" type="text" <%= currentLocale.equals(defaultLocale) ? "style='display: none'" : "" %> onChange="<portlet:namespace />onNameChanged();" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="html-title" />
			</td>
			<td>
				<input id="<portlet:namespace />title_<%= defaultLanguageId %>" name="<portlet:namespace />title_<%= defaultLanguageId %>" size="30" type="text" value="<%= selLayout.getTitle(defaultLocale) %>" />
			</td>
			<td>

				<%
				for (int i = 0; i < locales.length; i++) {
					if (locales[i].equals(defaultLocale)) {
						continue;
					}
				%>

					<input id="<portlet:namespace />title_<%= LocaleUtil.toLanguageId(locales[i]) %>" name="<portlet:namespace />title_<%= LocaleUtil.toLanguageId(locales[i]) %>" type="hidden" value="<%= selLayout.getTitle(locales[i], false) %>" />

				<%
				}
				%>

				<input id="<portlet:namespace />title_temp" size="30" type="text" <%= currentLocale.equals(defaultLocale) ? "style='display: none'" : "" %> onChange="<portlet:namespace />onTitleChanged();" />
			</td>
		</tr>
		<tr>
			<td colspan="3">
				<br />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="type" />
			</td>
			<td colspan="2">
				<select name="<portlet:namespace />type">

					<%
					for (int i = 0; i < LayoutImpl.TYPES.length; i++) {
					%>

						<option <%= type.equals(LayoutImpl.TYPES[i]) ? "selected" : "" %> value="<%= LayoutImpl.TYPES[i] %>"><%= LanguageUtil.get(pageContext, "layout.types." + LayoutImpl.TYPES[i]) %></option>

					<%
					}
					%>

				</select>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="hidden" />
			</td>
			<td colspan="2">
				<liferay-ui:input-checkbox param="hidden" defaultValue="<%= selLayout.isHidden() %>" />
			</td>
		</tr>

		<c:if test="<%= PortalUtil.isLayoutFriendliable(selLayout) %>">
			<tr>
				<td>
					<liferay-ui:message key="friendly-url" />
				</td>
				<td colspan="2" nowrap>

					<%
					StringMaker friendlyURLBase = new StringMaker();

					friendlyURLBase.append(PortalUtil.getPortalURL(request));

					String virtualHost = selLayout.getLayoutSet().getVirtualHost();

					if (Validator.isNull(virtualHost) || (friendlyURLBase.indexOf(virtualHost) == -1)) {
						friendlyURLBase.append(group.getPathFriendlyURL(privateLayout, themeDisplay));

						String parentFriendlyURL = group.getFriendlyURL();

						if (Validator.isNull(parentFriendlyURL)) {
							parentFriendlyURL = group.getDefaultFriendlyURL(privateLayout);
						}

						friendlyURLBase.append(parentFriendlyURL);
					}
					%>

					<%= friendlyURLBase.toString() %>

					<input name="<portlet:namespace />friendlyURL" size="30" type="text" value="<%= friendlyURL %>" />
				</td>
			</tr>
			<tr>
				<td>
					<br />
				</td>
				<td colspan="3">
					<%= LanguageUtil.format(pageContext, "for-example-x", "<i>/news</i>") %>
				</td>
			</tr>
		</c:if>

		<tr>
			<td colspan="3">
				<br />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="icon" />
			</td>
			<td colspan="2">
				<liferay-theme:layout-icon layout="<%= selLayout %>" />

				<input name="<portlet:namespace />iconFileName" size="30" type="file" onChange="document.<portlet:namespace />fm.<portlet:namespace />iconImage.value = true; document.<portlet:namespace />fm.<portlet:namespace />iconImageCheckbox.checked = true;" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="use-icon" />
			</td>
			<td colspan="2">
				<liferay-ui:input-checkbox param="iconImage" defaultValue="<%= selLayout.isIconImage() %>" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="target" />
			</td>
			<td>
				<%
				String curTarget = (String) selLayout.getTypeSettingsProperties().getProperty("target");

				if (curTarget == null) {
					curTarget = StringPool.BLANK;
				}
				%>
				<input name="TypeSettingsProperties(target)" size="15" type="text" value="<%= curTarget %>" />
			</td>
		</tr>
		</table>
	</td>
</tr>
<tr>
	<td>
		<div class="separator"><!-- --></div>
	</td>
</tr>
<tr>
	<td>

		<%
		request.setAttribute(WebKeys.SEL_LAYOUT, selLayout);
		%>

		<liferay-util:include page="<%= StrutsUtil.TEXT_HTML_DIR + PortalUtil.getLayoutEditPage(selLayout) %>" />
	</td>
</tr>
</table>

<br />

<input type="submit" value="<liferay-ui:message key="save" />" />

<liferay-security:permissionsURL
	modelResource="<%= Layout.class.getName() %>"
	modelResourceDescription="<%= selLayout.getName(locale) %>"
	resourcePrimKey="<%= String.valueOf(selLayout.getPlid()) %>"
	var="permissionURL"
/>

<input type="button" value="<liferay-ui:message key="permissions" />" onClick="self.location = '<%= permissionURL %>';" />

<input type="button" value="<liferay-ui:message key="delete" />" onClick="<portlet:namespace />deletePage();" />

<script type="text/javascript">
	<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />name_<%= defaultLanguageId %>);
	</c:if>

	var nameChanged = false;
	var titleChanged = false;
	var lastLanguageId = "<%= currentLanguageId %>";

	function <portlet:namespace />onNameChanged() {
		nameChanged = true;
	}

	function <portlet:namespace />onTitleChanged() {
		titleChanged = true;
	}

	function <portlet:namespace />updateLanguage() {
		if (lastLanguageId != "<%= defaultLanguageId %>") {
			if (nameChanged) {
				var nameValue = jQuery("#<portlet:namespace />name_temp").attr("value");

				if (nameValue == null) {
					nameValue = "";
				}

				jQuery("#<portlet:namespace />name_" + lastLanguageId).attr("value", nameValue);

				nameChanged = false;
			}

			if (titleChanged) {
				var titleValue = jQuery("#<portlet:namespace />title_temp").attr("value");

				if (titleValue == null) {
					titleValue = "";
				}

				jQuery("#<portlet:namespace />title_" + lastLanguageId).attr("value", titleValue);

				titleChanged = false;
			}
		}

		var selLanguageId = "";

		for (var i = 0; i < document.<portlet:namespace />fm.<portlet:namespace />languageId.length; i++) {
			if (document.<portlet:namespace />fm.<portlet:namespace />languageId.options[i].selected) {
				selLanguageId = document.<portlet:namespace />fm.<portlet:namespace />languageId.options[i].value;

				break;
			}
		}

		if (selLanguageId != "") {
			<portlet:namespace />updateLanguageTemps(selLanguageId);

			jQuery("#<portlet:namespace />name_temp").show();
			jQuery("#<portlet:namespace />title_temp").show();
		}
		else {
			jQuery("#<portlet:namespace />name_temp").hide();
			jQuery("#<portlet:namespace />title_temp").hide();
		}

		lastLanguageId = selLanguageId;

		return null;
	}

	function <portlet:namespace />updateLanguageTemps(lang) {
		if (lang != "<%= defaultLanguageId %>") {
			var nameValue = jQuery("#<portlet:namespace />name_" + lang).attr("value");
			var titleValue = jQuery("#<portlet:namespace />title_" + lang).attr("value");
			var defaultNameValue = jQuery("#<portlet:namespace />name_<%= defaultLanguageId %>").attr("value");
			var defaultTitleValue = jQuery("#<portlet:namespace />title_<%= defaultLanguageId %>").attr("value");

			if (defaultNameValue == null) {
				defaultNameValue = "";
			}

			if (defaultTitleValue == null) {
				defaultTitleValue = "";
			}

			if ((nameValue == null) || (nameValue == "")) {
				jQuery("#<portlet:namespace />name_temp").attr("value", defaultNameValue);
			}
			else {
				jQuery("#<portlet:namespace />name_temp").attr("value", nameValue);
			}

			if ((titleValue == null) || (titleValue == "")) {
				jQuery("#<portlet:namespace />title_temp").attr("value", defaultTitleValue);
			}
			else {
				jQuery("#<portlet:namespace />title_temp").attr("value", titleValue);
			}
		}
	}

	<portlet:namespace />updateLanguageTemps(lastLanguageId);
</script>