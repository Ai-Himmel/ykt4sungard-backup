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
String types = GetterUtil.getString((String)request.getAttribute("liferay-ui:social-bookmark:types"));
String url = GetterUtil.getString((String)request.getAttribute("liferay-ui:social-bookmark:url"));
String title = GetterUtil.getString((String)request.getAttribute("liferay-ui:social-bookmark:title"));
String target = GetterUtil.getString((String)request.getAttribute("liferay-ui:social-bookmark:target"));

String[] typesArray = null;

if (Validator.isNotNull(types)) {
	typesArray = StringUtil.split(types);
}
else {
	typesArray = PropsUtil.getArray(PropsUtil.SOCIAL_BOOKMARK_TYPES);
}
%>