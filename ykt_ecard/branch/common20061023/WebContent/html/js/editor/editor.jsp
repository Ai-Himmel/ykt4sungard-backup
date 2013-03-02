<%
/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

<%@ include file="/html/common/init.jsp" %>

<%
String editorImpl = ParamUtil.get(request, "editor_impl", PropsUtil.get(EDITOR_WYSIWYG_IMPL_KEY));

editorImpl = "fckeditor";
//editorImpl = "liferay";
//editorImpl = "tinymce";

// Resin won't allow dynamic content inside the jsp:include tag

RequestDispatcher rd = application.getRequestDispatcher(Constants.TEXT_HTML_DIR + "/js/editor/" + editorImpl + ".jsp");

rd.include(request, response);
%>

<%--<jsp:include page='<%= Constants.TEXT_HTML_DIR + "/js/editor/" + editorImpl + ".jsp" %>' />--%>

<%!
public static final String EDITOR_WYSIWYG_IMPL_KEY = "editor.wysiwyg.default";
%>