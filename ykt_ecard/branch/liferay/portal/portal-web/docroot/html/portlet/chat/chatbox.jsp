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

<%@ include file="/html/portlet/chat/init.jsp" %>

<%
boolean addUser = ParamUtil.getBoolean(request, "addUser");
String messages = ParamUtil.getString(request, "messages");
String toId = ParamUtil.getString(request, "toId");
String toName = ParamUtil.getString(request, "toName");
int zIndex = ParamUtil.getInteger(request, "zIndex");
int top = ParamUtil.getInteger(request, "top");
int left = ParamUtil.getInteger(request, "left");
%>

<div class="chat-box" id="msg-chat-box_<%= toId.replace('.', '_') %>" style="border: 1px solid #000000; padding: 10px; z-index: <%= zIndex %>; left: <%= left %>px; position: absolute; top: <%= top %>px; background-color: #ffffff; text-align: left" onClick="this.style.zIndex = Liferay.zIndex.CHAT_BOX + Messaging.zIndex++">
	<div class="chat-box-width" style="WIDTH: 250px">
		<div class="chat-title" style="cursor: move">
			<table cellpadding="0" cellspacing="0" border="0" width="100%">
			<tr>
				<td>
					Chat with <span class="to-name" style="font-weight: bold"><%= toName %></span>
				</td>
				<td align="right">
					<a style="cursor: pointer" href="javascript: Messaging.removeChat('msg-chat-box_<%= toId.replace('.', '_') %>')"><img src="<%= themeDisplay.getPathThemeImages() %>/portlet/close.png" /></a>
				</td>
			</tr>
			</table>
		</div>

		<input class="to-input-id" type="hidden" value="<%= toId %>" />

		<div class="chat-area" style="border: #d0d0d0 1px solid; padding: 5px; overflow: auto; margin: 5px 0 5px 0; height: 100px">
			<%= messages %>
		</div>

		<input class="type-area" style="width: 100%" tabIndex="1" onKeyPress="Messaging.sendChat(this, event)" />

		<c:if test="<%= addUser %>">
			<img src="<%= themeDisplay.getPathThemeImages() %>/chat/add_user.png" style="cursor: pointer; margin-top: 2px" onclick="MessagingRoster.addEntry('<%= toId %>'); Element.remove(this)" />
		</c:if>
	</div>
</div>