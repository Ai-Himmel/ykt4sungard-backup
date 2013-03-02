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

<meta content="<%= Constants.TEXT_HTML %>; charset=<%= LanguageUtil.DEFAULT_ENCODING %>" http-equiv="content-type">

<%
String refreshRate = request.getParameter("refresh_rate");
%>

<c:if test='<%= (refreshRate != null) && (!refreshRate.equals("0")) %>'>
	<meta content="<%= refreshRate %>;" http-equiv="Refresh">
</c:if>

<%
String cacheControl = request.getParameter("cache_control");
%>

<c:if test='<%= (cacheControl != null) && (cacheControl.equals("0")) %>'>
	<meta content="no-cache" http-equiv="Cache-Control">
	<meta content="no-cache" http-equiv="Pragma">
	<meta content="0" http-equiv="Expires">
</c:if>