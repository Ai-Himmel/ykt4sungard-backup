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

<%@ include file="/html/portlet/init.jsp" %>

<%@ page import="com.liferay.portlet.workflow.DefinitionXmlException" %>
<%@ page import="com.liferay.portlet.workflow.NoSuchDefinitionException" %>
<%@ page import="com.liferay.portlet.workflow.action.EditTaskAction" %>
<%@ page import="com.liferay.portlet.workflow.jbi.WorkflowXMLUtil" %>
<%@ page import="com.liferay.portlet.workflow.model.WorkflowDefinition" %>
<%@ page import="com.liferay.portlet.workflow.model.WorkflowInstance" %>
<%@ page import="com.liferay.portlet.workflow.model.WorkflowTask" %>
<%@ page import="com.liferay.portlet.workflow.model.WorkflowTaskFormElement" %>
<%@ page import="com.liferay.portlet.workflow.model.WorkflowToken" %>
<%@ page import="com.liferay.portlet.workflow.search.DefinitionDisplayTerms" %>
<%@ page import="com.liferay.portlet.workflow.search.DefinitionSearch" %>
<%@ page import="com.liferay.portlet.workflow.search.DefinitionSearchTerms" %>
<%@ page import="com.liferay.portlet.workflow.search.InstanceDisplayTerms" %>
<%@ page import="com.liferay.portlet.workflow.search.InstanceSearch" %>
<%@ page import="com.liferay.portlet.workflow.search.InstanceSearchTerms" %>
<%@ page import="com.liferay.portlet.workflow.search.TaskDisplayTerms" %>
<%@ page import="com.liferay.portlet.workflow.search.TaskSearch" %>
<%@ page import="com.liferay.portlet.workflow.search.TaskSearchTerms" %>
<%@ page import="com.liferay.portlet.workflow.service.WorkflowComponentServiceUtil" %>
<%@ page import="com.liferay.portlet.workflow.service.permission.WorkflowDefinitionPermission" %>
<%@ page import="com.liferay.portlet.workflow.service.permission.WorkflowInstancePermission" %>
<%@ page import="com.liferay.portlet.workflow.service.permission.WorkflowTaskPermission" %>

<%
PortletPreferences prefs = renderRequest.getPreferences();

String portletResource = ParamUtil.getString(request, "portletResource");

if (Validator.isNotNull(portletResource)) {
	prefs = PortletPreferencesFactoryUtil.getPortletSetup(request, portletResource, true, true);
}

String viewType = prefs.getValue("viewType", "administrator");
String definitionName = prefs.getValue("definitionName", StringPool.BLANK);

DateFormat dateFormatDateTime = DateFormats.getDateTime(locale, timeZone);
%>