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
String id = (String)request.getAttribute("liferay-ui:toggle:id");
String onImage = (String)request.getAttribute("liferay-ui:toggle:onImage");
String offImage = (String)request.getAttribute("liferay-ui:toggle:offImage");
String stateVar = (String)request.getAttribute("liferay-ui:toggle:stateVar");
String defaultStateValue = (String)request.getAttribute("liferay-ui:toggle:defaultStateValue");
String defaultImage = (String)request.getAttribute("liferay-ui:toggle:defaultImage");
%>

<script type="text/javascript">
	var <%= stateVar %> = "<%= defaultStateValue %>";

	function <%= stateVar %>Toggle(state, saveState) {
		if (state == null) {
			state = <%= stateVar %>;
		}

		if (state == "") {
			document.getElementById("<%= id %>").style.display = "none";
			document.getElementById("<%= id %>_image").src = "<%= offImage %>";
			<%= stateVar %> = "none";

			if ((saveState == null) || saveState) {
				loadPage(mainPath + "/portal/session_click", "<%= id %>=none");
			}
		}
		else {
			document.getElementById("<%= id %>").style.display = "";
			document.getElementById("<%= id %>_image").src = "<%= onImage %>";
			<%= stateVar %> = "";

			if ((saveState == null) || saveState) {
				loadPage(mainPath + "/portal/session_click", "<%= id %>=");
			}
		}
	}
</script>

<img hspace="0" id="<%= id %>_image" vspace="0" src="<%= defaultImage %>" onClick="<%= stateVar %>Toggle();" />