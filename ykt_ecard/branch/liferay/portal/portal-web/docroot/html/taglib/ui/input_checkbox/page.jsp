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

<%@ include file="/html/taglib/init.jsp" %>

<%
String formName = namespace + request.getAttribute("liferay-ui:input-checkbox:formName");
String param = (String)request.getAttribute("liferay-ui:input-checkbox:param");
Boolean defaultValue = (Boolean)request.getAttribute("liferay-ui:input-checkbox:defaultValue");
String onClick = GetterUtil.getString((String)request.getAttribute("liferay-ui:input-checkbox:onClick"));
boolean disabled = GetterUtil.getBoolean((String)request.getAttribute("liferay-ui:input-checkbox:disabled"));

boolean value = ParamUtil.getBoolean(request, param, defaultValue.booleanValue());
%>

<input id="<%= namespace %><%= param %>" name="<%= namespace %><%= param %>" type="hidden" value="<%= value %>" />

<input <%= value ? "checked" : "" %> <%= disabled ? "disabled" : "" %> id="<%= namespace %><%= param %>Checkbox" name="<%= namespace %><%= param %>Checkbox" type="checkbox" onClick="document.getElementById('<%= namespace %><%= param %>').value = this.checked; <%= onClick %>">