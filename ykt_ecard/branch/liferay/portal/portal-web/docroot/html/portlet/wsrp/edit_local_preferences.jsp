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

<%@ include file="/html/portlet/wsrp/init.jsp" %>

<%
PortletPreferences prefs = renderRequest.getPreferences();

String wsrpServiceUrl = prefs.getValue("wsrp-service-url", StringPool.BLANK);
String markupEndpoint = prefs.getValue("markup-endpoint", StringPool.BLANK);
String serviceDescriptionEndpoint = prefs.getValue("service-description-endpoint", StringPool.BLANK);
String registrationEndpoint = prefs.getValue("registration-endpoint", StringPool.BLANK);
String portletManagementEndpoint = prefs.getValue("portlet-management-endpoint", StringPool.BLANK);
String portletHandle = prefs.getValue("portlet-handle", StringPool.BLANK);

PortletDescription[] portletDescs = {};

Throwable error = null;

try {
	Producer producer = (Producer)renderRequest.getAttribute(WebKeys.WSRP_PRODUCER);

	ServiceDescription serviceDesc = producer.getServiceDescription(true);

	portletDescs = serviceDesc.getOfferedPortlets();

	Arrays.sort(portletDescs, WSRPUtil.getPortletDescriptionComparator());
}
catch (Throwable t) {
	error = t;
}
%>

<form action="<portlet:actionURL><portlet:param name="struts_action" value="/wsrp/edit_local_preferences" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm">

<c:if test="<%= error != null %>">
	<span class="portlet-message-error">
	<liferay-ui:message key="wsrp-your-service-url-or-endpoints-are-unreachable" />
	</span>
</c:if>

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="wsrp-service-url" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />wsrp_service_url" type="text" value="<%= wsrpServiceUrl %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="wsrp-markup-endpoint" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />markup_endpoint" type="text" value="<%= markupEndpoint %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="wsrp-service-description-endpoint" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />service_description_endpoint" type="text" value="<%= serviceDescriptionEndpoint %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="wsrp-registration-endpoint" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />registration_endpoint" type="text" value="<%= registrationEndpoint %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="wsrp-portlet-management-endpoint" />
	</td>
	<td>
		<input class="lfr-input-text" name="<portlet:namespace />portlet_management_endpoint" type="text" value="<%= portletManagementEndpoint %>" />
	</td>
</tr>
<tr>
	<td>
		<liferay-ui:message key="wsrp-portlet" />
	</td>
	<td>
		<select name="<portlet:namespace />portlet_handle">

			<%
			for (int i = 0; i < portletDescs.length; i++) {
			%>

				<option <%= portletHandle.equals(portletDescs[i].getPortletHandle()) ? "selected" : "" %> value="<%= portletDescs[i].getPortletHandle() %>"><%= portletDescs[i].getTitle().getValue() %></option>

			<%
			}
			%>

		</select>
	</td>
</tr>
</table>

<br />

<input type="button" value="<liferay-ui:message key="save" />" onClick="submitForm(document.<portlet:namespace />fm);" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<portlet:renderURL><portlet:param name="struts_action" value="/wsrp/edit" /></portlet:renderURL>';" />

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />wsrp_service_url);
	</script>
</c:if>