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

<%@ include file="/html/portal/init.jsp" %>

<%
String title = ParamUtil.getString(request, "title");

String height = ParamUtil.getString(request, "height", "768");
String width = ParamUtil.getString(request, "width", "1024");

String movie = ParamUtil.getString(request, "movie");
%>

<html>
<head>
	<title><%= title %></title>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<script src="<%= themeDisplay.getPathJavaScript() %>/misc/swfobject.js" type="text/javascript"></script>
</head>

<body leftmargin="0" marginheight="0" marginwidth="0" rightmargin="0" topmargin="0">

<center>

<c:if test="<%= Validator.isNotNull(movie) %>">
	<div id="flashMovie"></div>

	<script type="text/javascript">
		var so = new SWFObject("<%= movie %>", "flashMovie", "<%= width %>", "<%= height %>", "6", "#FFFFFF");

		so.write("flashMovie");
	</script>
</c:if>

</center>

</body>

</html>