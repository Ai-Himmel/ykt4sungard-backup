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
String image = (String)request.getAttribute("liferay-ui:png_image:image");
String height = (String)request.getAttribute("liferay-ui:png_image:height");
String width = (String)request.getAttribute("liferay-ui:png_image:width");
%>

<div style="
		<c:choose>
			<c:when test="<%= BrowserSniffer.is_ie_5_5_up(request) %>">
				filter: progid:DXImageTransform.Microsoft.AlphaImageLoader(src='<%= image %>', sizingMethod='scale');
			</c:when>
			<c:otherwise>
				background-image: url(<%= image %>);
			</c:otherwise>
		</c:choose>

		height: <%= height %>px; width: <%= width %>px;"></div>