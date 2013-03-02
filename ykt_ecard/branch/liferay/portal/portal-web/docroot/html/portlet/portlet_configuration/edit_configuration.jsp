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

<%@ include file="/html/portlet/portlet_configuration/init.jsp" %>

<%
String portletResource = ParamUtil.getString(request, "portletResource");

Portlet selPortlet = PortletLocalServiceUtil.getPortletById(company.getCompanyId(), portletResource);

String path = (String)request.getAttribute(WebKeys.CONFIGURATION_ACTION_PATH);
%>

<liferay-util:include page="/html/portlet/portlet_configuration/tabs1.jsp">
	<liferay-util:param name="tabs1" value="setup" />
</liferay-util:include>

<c:if test="<%= (selPortlet != null) && Validator.isNotNull(path) %>">
	<c:choose>
		<c:when test="<%= selPortlet.isWARFile() %>">

			<%
			PortletConfig selPortletConfig = PortletConfigFactory.create(selPortlet, application);
			PortletContextImpl selPortletCtx = (PortletContextImpl)selPortletConfig.getPortletContext();

			RequestDispatcher selRd = selPortletCtx.getServletContext().getRequestDispatcher(path);

			StringServletResponse stringServletRes = new StringServletResponse(response);

			selRd.include(request, stringServletRes);
			%>

			<%= stringServletRes.getString() %>
		</c:when>
		<c:otherwise>
			<liferay-util:include page="<%= path %>" />
		</c:otherwise>
	</c:choose>
</c:if>