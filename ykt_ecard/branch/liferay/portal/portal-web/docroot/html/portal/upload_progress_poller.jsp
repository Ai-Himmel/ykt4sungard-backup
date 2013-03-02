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
String uploadProgressId = ParamUtil.getString(request, "uploadProgressId");

String fileName = GetterUtil.getString((String)session.getAttribute(LiferayFileUpload.FILE_NAME + uploadProgressId));

if (fileName == null) {
	fileName = GetterUtil.getString((String)session.getAttribute(LiferayFileUpload.FILE_NAME));
}

Integer percent = (Integer)session.getAttribute(LiferayFileUpload.PERCENT + uploadProgressId);

if (percent == null) {
	percent = (Integer)session.getAttribute(LiferayFileUpload.PERCENT);
}
if (percent == null) {
	percent = new Integer(100);
}

if (percent.floatValue() >= 100) {
	session.removeAttribute(LiferayFileUpload.FILE_NAME);
	session.removeAttribute(LiferayFileUpload.FILE_NAME + uploadProgressId);
	session.removeAttribute(LiferayFileUpload.PERCENT);
	session.removeAttribute(LiferayFileUpload.PERCENT + uploadProgressId);
}
%>

<html>

<body>

<script type="text/javascript">
	parent.<%= uploadProgressId %>.updateBar(<%= percent.intValue() %>, "<%= fileName %>");

	<c:if test="<%= percent.intValue() < 100 %>">
		setTimeout("window.location.reload();", 1000);
	</c:if>
</script>

</body>

</html>