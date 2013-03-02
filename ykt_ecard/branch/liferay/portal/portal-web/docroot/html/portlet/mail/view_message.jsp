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

<%@ include file="/html/portlet/mail/init.jsp" %>

<%
MailMessage mailMessage = MailUtil.getMessage(request);

Address from = mailMessage.getFrom();
Address[] to = mailMessage.getTo();
Address[] cc = mailMessage.getCc();
Address[] bcc = mailMessage.getBcc();

Date sentDate = mailMessage.getSentDate();

List attachments = mailMessage.getRemoteAttachments();

boolean header = ParamUtil.getBoolean(request, "header");
%>

<c:if test="<%= mailMessage != null %>">

	<div id="portlet-mail-msg-header-hidden" style="display: none;">
		<div style="font-weight: bold;">
			<%= mailMessage.getSubject() %>
		</div>

		<table cellpadding="0" cellspacing="0" border="0" class="font-small;">
		<tr>
			<td align="right" style="padding-right: 5px;" valign="top">
				<liferay-ui:message key="from" />:&nbsp;
			</td>
			<td>
				<%= Html.escape(InternetAddressUtil.toString(from)) %>
			</td>
		</tr>

		<c:if test="<%= to != null %>">
			<tr>
				<td align="right" style="padding-right: 5px;" valign="top">
					<liferay-ui:message key="to" />:&nbsp;
				</td>
				<td>
					<%= Html.escape(InternetAddressUtil.toString(to)) %>
				</td>
			</tr>
		</c:if>

		<c:if test="<%= cc != null %>">
			<tr>
				<td align="right" style="padding-right: 5px;" valign="top">
					<liferay-ui:message key="cc" />:&nbsp;
				</td>
				<td>
					<%= Html.escape(InternetAddressUtil.toString(cc)) %>
				</td>
			</tr>
		</c:if>

		<c:if test="<%= bcc != null %>">
			<tr>
				<td align="right" style="padding-right: 5px;" valign="top">
					<liferay-ui:message key="bcc" />:&nbsp;
				</td>
				<td>
					<%= Html.escape(InternetAddressUtil.toString(bcc)) %>
				</td>
			</tr>
		</c:if>

		<c:if test="<%= sentDate != null %>">
			<tr>
				<td align="right" style="padding-right: 5px;" valign="top">
					<liferay-ui:message key="date" />:&nbsp;
				</td>
				<td>
					<%= dateFormatDateTime.format(sentDate) %>
				</td>
			</tr>
		</c:if>

		<c:if test="<%= attachments.size() > 0 %>">
			<tr>
				<td align="right" style="padding-right: 5px;" valign="top">
					<img src="<%= themeDisplay.getPathThemeImages() %>/mail/clip.png" />&nbsp;
				</td>
				<td>

					<%
					for (int i = 0; i < attachments.size(); i++) {
						RemoteMailAttachment remoteMailAttachment = (RemoteMailAttachment)attachments.get(i);

						String url = themeDisplay.getPathMain() + "/mail/get_attachment?fileName=" + remoteMailAttachment.getFilename() + "&contentPath=" + remoteMailAttachment.getContentPath();
					%>

						<a href="<%= url %>"><%= remoteMailAttachment.getFilename() %></a><%= (i + 1 < attachments.size()) ? ", " : "" %>

					<%
					}
					%>

				</td>
			</tr>
		</c:if>

		</table>
	</div>

	<%= mailMessage.getBody(true, header) %>

	<script type="text/javascript">
		var hiddenHeader = document.getElementById("portlet-mail-msg-header-hidden");

		<c:choose>
			<c:when test="<%= header %>">
				hiddenHeader.innerHTML = hiddenHeader.innerHTML + "<hr /><br />";
				hiddenHeader.style.display = "block";
			</c:when>
			<c:otherwise>
				parent.setHeader(hiddenHeader.innerHTML);
			</c:otherwise>
		</c:choose>
	</script>
</c:if>