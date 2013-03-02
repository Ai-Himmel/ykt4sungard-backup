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

<%@ page import="com.liferay.portal.kernel.dao.search.DisplayTerms" %>

<%
String randomNamespace = (String)request.getAttribute("liferay-ui:search-toggle:randomNamespace");

String id = (String)request.getAttribute("liferay-ui:search-toggle:id");
DisplayTerms displayTerms = (DisplayTerms)request.getAttribute("liferay-ui:search-toggle:displayTerms");

String clickValue = GetterUtil.getString(SessionClicks.get(request, id, null), "basic");

if (clickValue.equals("basic")) {
	if (displayTerms.isAdvancedSearch()) {
		displayTerms.setAdvancedSearch(false);
	}
}
else {
	if (!displayTerms.isAdvancedSearch()) {
		displayTerms.setAdvancedSearch(true);
	}
}
%>