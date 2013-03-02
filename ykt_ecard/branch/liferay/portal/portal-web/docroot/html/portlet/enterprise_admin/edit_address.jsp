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

<%@ include file="/html/portlet/enterprise_admin/init.jsp" %>

<%
themeDisplay.setIncludeServiceJs(true);

String redirect = ParamUtil.getString(request, "redirect");

Address address = (Address)request.getAttribute(WebKeys.ADDRESS);

long addressId = BeanParamUtil.getLong(address, request, "addressId");

String className = ParamUtil.getString(request, "className");
long classPK = BeanParamUtil.getLong(address, request, "classPK");

long regionId = BeanParamUtil.getLong(address, request, "regionId");
long countryId = BeanParamUtil.getLong(address, request, "countryId");
int typeId = BeanParamUtil.getInteger(address, request, "typeId");
%>

<script type="text/javascript">
	function <portlet:namespace />saveAddress() {
		document.<portlet:namespace />fm.<portlet:namespace /><%= Constants.CMD %>.value = "<%= address == null ? Constants.ADD : Constants.UPDATE %>";
		submitForm(document.<portlet:namespace />fm);
	}
</script>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_address" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm" onSubmit="<portlet:namespace />saveAddress(); return false;">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="" />
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />addressId" type="hidden" value="<%= addressId %>" />
<input name="<portlet:namespace />className" type="hidden" value="<%= className %>" />
<input name="<portlet:namespace />classPK" type="hidden" value="<%= classPK %>" />

<liferay-ui:tabs
	names="address"
	backURL="<%= redirect %>"
/>

<liferay-ui:error exception="<%= AddressCityException.class %>" message="please-enter-a-valid-city" />
<liferay-ui:error exception="<%= AddressStreetException.class %>" message="please-enter-a-valid-street" />
<liferay-ui:error exception="<%= AddressZipException.class %>" message="please-enter-a-valid-zip" />
<liferay-ui:error exception="<%= NoSuchCountryException.class %>" message="please-select-a-country" />
<liferay-ui:error exception="<%= NoSuchRegionException.class %>" message="please-select-a-region" />
<liferay-ui:error exception="<%= NoSuchListTypeException.class %>" message="please-select-a-type" />

<table class="lfr-table">
<tr>
	<td valign="top">
		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="street1" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= Address.class %>" bean="<%= address %>" field="street1" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="street2" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= Address.class %>" bean="<%= address %>" field="street2" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="street3" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= Address.class %>" bean="<%= address %>" field="street3" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="city" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= Address.class %>" bean="<%= address %>" field="city" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="zip" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= Address.class %>" bean="<%= address %>" field="zip" />
			</td>
		</tr>
		</table>
	</td>
	<td valign="top">
		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="country" />
			</td>
			<td>
				<select id="<portlet:namespace />countryId" name="<portlet:namespace />countryId"></select>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="region" />
			</td>
			<td>
				<select id="<portlet:namespace />regionId" name="<portlet:namespace />regionId"></select>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="type" />
			</td>
			<td>
				<select name="<portlet:namespace />typeId">
					<option value=""></option>

					<%
					List addressTypes = ListTypeServiceUtil.getListTypes(className + ListTypeImpl.ADDRESS);

					for (int i = 0; i < addressTypes.size(); i++) {
						ListType suffix = (ListType)addressTypes.get(i);
					%>

						<option <%= suffix.getListTypeId() == typeId ? "selected" : "" %> value="<%= String.valueOf(suffix.getListTypeId()) %>"><%= LanguageUtil.get(pageContext, suffix.getName()) %></option>

					<%
					}
					%>

				</select>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="mailing" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= Address.class %>" bean="<%= address %>" field="mailing" />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="primary" />
			</td>
			<td>
				<liferay-ui:input-field model="<%= Address.class %>" bean="<%= address %>" field="primary" />
			</td>
		</tr>
		</table>
	</td>
</tr>
</table>

<br />

<input type="submit" value="<liferay-ui:message key="save" />" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

</form>

<script type="text/javascript">
	<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />street1);
	</c:if>

	new Liferay.DynamicSelect(
		[
			{
				select: "<portlet:namespace />countryId",
				selectId: "countryId",
				selectDesc: "name",
				selectVal: "<%= countryId %>",
				selectData: function(callback) {
					Liferay.Service.Portal.Country.getCountries(
						{
							active: true
						},
						callback
					);
				}
			},
			{
				select: "<portlet:namespace />regionId",
				selectId: "regionId",
				selectDesc: "name",
				selectVal: "<%= regionId %>",
				selectData: function(callback, selectKey) {
					Liferay.Service.Portal.Region.getRegions(
						{
							countryId: selectKey,
							active: true
						},
						callback
					);
				}
			}
		]
	);
</script>