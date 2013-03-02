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
IntegerWrapper iconMenuIconCount = (IntegerWrapper)request.getAttribute("liferay-ui:icon-menu:icon-count");

if (iconMenuIconCount != null) {
	iconMenuIconCount.increment();
}

Boolean iconMenuSingleIcon = (Boolean)request.getAttribute("liferay-ui:icon-menu:single-icon");

String image = (String)request.getAttribute("liferay-ui:icon:image");

String message = (String)request.getAttribute("liferay-ui:icon:message");

if (message == null) {
	message = StringUtil.replace(image, StringPool.UNDERLINE, StringPool.DASH);
}

String src = (String)request.getAttribute("liferay-ui:icon:src");

if (Validator.isNull(src)) {
	src = themeDisplay.getPathThemeImages() + "/common/" + image + ".png";
}

String url = (String)request.getAttribute("liferay-ui:icon:url");
String target = GetterUtil.getString((String)request.getAttribute("liferay-ui:icon:target"));
boolean label = GetterUtil.getBoolean((String)request.getAttribute("liferay-ui:icon:label"));
boolean toolTip = GetterUtil.getBoolean((String)request.getAttribute("liferay-ui:icon:toolTip"));

if ((iconMenuIconCount != null) || (iconMenuSingleIcon != null)) {
	label = true;
}

String details = StringPool.BLANK;

if (!label) {
	if (toolTip) {
		details = "onmousemove=\"ToolTip.show(event, this, '" + UnicodeLanguageUtil.get(pageContext, message) + "')\"";
	}
	else {
		details = "title=\"" + LanguageUtil.get(pageContext, message) + "\"";
	}
}
%>