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
String id = (String)request.getAttribute("liferay-ui:upload-progress:id");
String iframeSrc = (String)request.getAttribute("liferay-ui:upload-progress:iframe-src");
String redirect = (String)request.getAttribute("liferay-ui:upload-progress:redirect");
String message = (String)request.getAttribute("liferay-ui:upload-progress:message");
%>

<script src="<%= themeDisplay.getPathJavaScript() %>/liferay/upload_progress.js" type="text/javascript"></script>

<script type="text/javascript">
	var <%= id %> = new UploadProgress("<%= id %>", "<%= HttpUtil.encodeURL(redirect) %>");
</script>

<c:if test="<%= Validator.isNotNull(iframeSrc) %>">
	<div><iframe frameborder="0" id="<%= id %>-iframe" src="<%= iframeSrc %>" style="width: 100%;"></iframe></div>
</c:if>

<div><iframe frameborder="0" id="<%= id %>-poller" src="" style="height: 0; width: 0;"></iframe></div>

<div id="<%= id %>-bar-div" style="display: none; text-align: center;">
	<br />

	<c:if test="<%= Validator.isNotNull(message) %>">
		<%= LanguageUtil.get(pageContext, message) %>...<br />
	</c:if>

	<div style="background: url(<%= themeDisplay.getPathThemeImages() %>/progress_bar/incomplete_middle.png) scroll repeat-x top left; margin: auto; text-align: left; width: 80%;">
		<div style="background: url(<%= themeDisplay.getPathThemeImages() %>/progress_bar/incomplete_left.png) scroll no-repeat top left;">
			<div style="height: 23px; background: url(<%= themeDisplay.getPathThemeImages() %>/progress_bar/incomplete_right.png) scroll no-repeat top right;">
				<div id="<%= id %>-bar" style="background: url(<%= themeDisplay.getPathThemeImages() %>/progress_bar/complete_middle.png) scroll repeat-x top left; overflow: hidden; width: 0;">
					<div style="background: url(<%= themeDisplay.getPathThemeImages() %>/progress_bar/complete_left.png) scroll no-repeat top left;">
						<div class="font-small" style="font-weight: bold; height: 23px; padding-top: 3px; text-align: center; background: url(<%= themeDisplay.getPathThemeImages() %>/progress_bar/complete_right.png) scroll no-repeat top right;">
						</div>
					</div>
				</div>
			</div>
		</div>
	</div>
</div>