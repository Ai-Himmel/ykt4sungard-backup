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

<%@ page import="com.liferay.portal.kernel.servlet.BrowserSniffer" %>
<%@ page import="com.liferay.portal.kernel.util.Constants" %>
<%@ page import="com.liferay.portal.kernel.util.ParamUtil" %>
<%@ page import="com.liferay.portal.struts.StrutsUtil" %>
<%@ page import="com.liferay.portal.util.PropsValues" %>

<%
String editorImpl = ParamUtil.getString(request, "editorImpl", PropsValues.EDITOR_WYSIWYG_DEFAULT);

if (BrowserSniffer.is_safari(request)) {
	if (editorImpl.indexOf("simple") == -1) {
		editorImpl = "tinymcesimple";
	}
}
else if (!BrowserSniffer.is_rtf(request)) {
	editorImpl = "simple";
}

//editorImpl = "fckeditor";
//editorImpl = "liferay";
//editorImpl = "simple";
//editorImpl = "tinymce";
//editorImpl = "tinymcesimple";

// Resin won't allow dynamic content inside the jsp:include tag

RequestDispatcher rd = application.getRequestDispatcher(StrutsUtil.TEXT_HTML_DIR + "/js/editor/" + editorImpl + ".jsp");

rd.include(request, response);
%>

<%--<jsp:include page='<%= StrutsUtil.TEXT_HTML_DIR + "/js/editor/" + editorImpl + ".jsp" %>' />--%>