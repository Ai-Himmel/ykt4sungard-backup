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

<script language="JavaScript" src="<%= themeDisplay.getPathJavaScript() %>/sniffer.js"></script>
<script language="JavaScript" src="<%= themeDisplay.getPathJavaScript() %>/init.js"></script>
<script language="JavaScript" src="<%= themeDisplay.getPathJavaScript() %>/menu.js"></script>
<script language="JavaScript" src="<%= themeDisplay.getPathJavaScript() %>/rollovers.js"></script>
<script language="JavaScript" src="<%= themeDisplay.getPathJavaScript() %>/util.js"></script>
<script language="JavaScript" src="<%= themeDisplay.getPathJavaScript() %>/validation.js"></script>
<script language="JavaScript" src="<%= themeDisplay.getPathJavaScript() %>/ajax.js"></script>

<script language="JavaScript">
	var mainPath = '<%= themeDisplay.getPathMain() %>';

	function submitFormAlert() {
		alert("<%= UnicodeLanguageUtil.get(pageContext, "this-form-has-already-been-submitted") %>");
	}
</script>

<theme:include page="javascript.jsp" flush="true" />