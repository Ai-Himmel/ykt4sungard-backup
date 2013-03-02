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
String bulletStyle = (String)request.getAttribute("liferay-ui:navigation:bulletStyle");
String displayStyle = (String)request.getAttribute("liferay-ui:navigation:displayStyle");

String headerType = null;
String rootLayoutType = null;
int rootLayoutLevel = 0;
String includedLayouts = null;

String[] displayStyleDefinition = _getDisplayStyleDefinition(displayStyle);

if ((displayStyleDefinition != null) && (displayStyleDefinition.length == 4)) {
	headerType = displayStyleDefinition[0];
	rootLayoutType = displayStyleDefinition[1];
	rootLayoutLevel = GetterUtil.getInteger(displayStyleDefinition[2]);
	includedLayouts = displayStyleDefinition[3];
}
else {
	headerType = (String)request.getAttribute("liferay-ui:navigation:headerType");
	rootLayoutType = (String)request.getAttribute("liferay-ui:navigation:rootLayoutType");
	rootLayoutLevel = GetterUtil.getInteger((String)request.getAttribute("liferay-ui:navigation:rootLayoutLevel"));
	includedLayouts = (String)request.getAttribute("liferay-ui:navigation:includedLayouts");
}
%>

<%!
private String[] _getDisplayStyleDefinition(String displayStyle) {
	return PropsUtil.getComponentProperties().getStringArray(
		"navigation.display.style", com.germinus.easyconf.Filter.by(displayStyle));
}
%>