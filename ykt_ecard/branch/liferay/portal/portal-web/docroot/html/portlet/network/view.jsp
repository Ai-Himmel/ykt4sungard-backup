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

<%@ include file="/html/portlet/network/init.jsp" %>

<%
String cmd = ParamUtil.getString(request, Constants.CMD);

String tabs1 = ParamUtil.getString(request, "tabs1", "dns-lookup");

PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setParameter("struts_action", "/network/view");
portletURL.setParameter("tabs1", tabs1);
%>

<form action="<portlet:renderURL><portlet:param name="struts_action" value="/network/view" /></portlet:renderURL>" method="post" name="<portlet:namespace />fm" onSubmit="submitForm(this); return false;">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="<%= Constants.SEARCH %>" />
<input name="<portlet:namespace />tabs1" type="hidden" value="<%= tabs1 %>" />

<liferay-ui:tabs
	names="dns-lookup,whois"
	url="<%= portletURL.toString() %>"
/>

<c:choose>
	<c:when test='<%= tabs1.equals("dns-lookup") %>'>
		<%
		String domain = ParamUtil.getString(request, "domain");

		DNSLookup dnsLookup = null;

		if (cmd.equals(Constants.SEARCH)) {
			dnsLookup = NetworkUtil.getDNSLookup(domain);

			if (dnsLookup == null) {
				SessionErrors.add(renderRequest, DNSLookup.class.getName());
			}
		}
		%>

		<liferay-ui:error exception="<%= DNSLookup.class %>" message="please-enter-a-valid-host-name-or-ip" />

		<input name="<portlet:namespace />domain" size="30" type="text" value="<%= Html.escape(domain) %>" /> <input type="submit" value="<liferay-ui:message key="search" />" />

		<c:if test="<%= dnsLookup != null %>">
<pre>
<%= dnsLookup.getResults() %>
</pre>
		</c:if>
	</c:when>
	<c:when test='<%= tabs1.equals("whois") %>'>

		<%
		String domain = ParamUtil.getString(request, "domain");

		Whois whois = null;

		if (cmd.equals(Constants.SEARCH)) {
			whois = NetworkUtil.getWhois(domain);

			if (whois == null) {
				SessionErrors.add(renderRequest, Whois.class.getName());
			}
		}
		%>

		<liferay-ui:error exception="<%= Whois.class %>" message="an-unexpected-error-occurred" />

		<input name="<portlet:namespace />domain" size="30" type="text" value="<%= Html.escape(domain) %>" /> <input type="submit" value="<liferay-ui:message key="search" />" />

		<c:if test="<%= whois != null %>">
<pre>
<%= whois.getResults() %>
</pre>
		</c:if>
	</c:when>
</c:choose>

</form>

<c:if test='<%= windowState.equals(WindowState.MAXIMIZED) && (tabs1.equals("dns-lookup") || tabs1.equals("whois")) %>'>
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />domain);
	</script>
</c:if>