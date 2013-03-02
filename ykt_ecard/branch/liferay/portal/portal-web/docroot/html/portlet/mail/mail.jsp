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
String mailBgColor = "#F4F5EB";
String mailLineColor = "#B3B6B0";

String folderPaneWidth = prefs.getValue("folder-pane-width", "115px");
String previewPaneHeight = prefs.getValue("preview-pane-height", "200px");
String detailedFrameHeight = prefs.getValue("detailed-frame-height", "auto");

String fromTitleWidth = prefs.getValue("from-title-width", "125px");
String subjectTitleWidth = prefs.getValue("subject-title-width", "250px");
String receivedTitleWidth = prefs.getValue("received-title-width", "125px");
%>

<style type="text/css">
	.portlet-mail-toolbar {
		margin-bottom: 5px;
	}

	.portlet-mail-toolbar td {
		border: 1px solid <%= mailLineColor %>;
		cursor: pointer;
		padding-left: 10px;
		padding-right: 10px;
	}

	#portlet-mail-toolbar-search td {
		background-color: <%= mailBgColor %>;
		border: 0px;
		cursor: default;
		padding-left: 0px;
		padding-right: 0px;
	}

	#portlet-mail-toolbar-advanced-search {
		border: 1px solid <%= mailLineColor %>;
		margin: 0px 2px 7px 2px;
		padding: 10px;
	}
</style>

<c:choose>
	<c:when test="<%= windowState.equals(WindowState.NORMAL) %>">

		<%
		boolean mailServerExists = true;
		MailFolder folder = null;

		try {
			MailUtil.setFolder(request, MailUtil.MAIL_INBOX_NAME);
			folder = MailUtil.getFolder(request);
		}
		catch (MailServerException mse) {
			mailServerExists = false;
		}
		%>

		<c:choose>
			<c:when test="<%= mailServerExists %>">
				<table border="0" cellpadding="2" cellspacing="2" class="portlet-mail-toolbar font-small" id="portlet-mail-main-toolbar">
				<tr>
					<td nowrap onClick="location.href = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" />';">
						<img align="absmiddle" src="<%= themeDisplay.getPathThemeImages() %>/mail/check_mail.png" /> <liferay-ui:message key="check-mail" />
					</td>
					<td nowrap onClick="location.href = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/mail/edit_message" /></portlet:renderURL>';">
						<img align="absmiddle" src="<%= themeDisplay.getPathThemeImages() %>/mail/compose.png" /> <liferay-ui:message key="new" />
					</td>
				</tr>
				</table>

				<liferay-ui:message key="unread-messages" />: <%= folder.getUnreadMessageCount() %>

				<br /><br />

				<%
				int count = 0;

				Set envelopes = MailUtil.getEnvelopes(request, new DateComparator(false));

				Iterator itr = envelopes.iterator();

				while (itr.hasNext() && (count < 10)) {
					MailEnvelope mailEnvelope = (MailEnvelope)itr.next();

					String recipient = GetterUtil.getString(mailEnvelope.getRecipient(), StringPool.NBSP);
					String subject = GetterUtil.getString(mailEnvelope.getSubject(), StringPool.NBSP);

					if (!mailEnvelope.isRead()) {
				%>

						<a href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="messageId" value="<%= String.valueOf(mailEnvelope.getMessageId()) %>" /><portlet:param name="folderId" value="<%= MailUtil.MAIL_INBOX_NAME %>" /></portlet:renderURL>">
						<span style="font-weight: bold"><%= recipient %></span> - <%= subject %><br />
						</a>

				<%
						count++;
					}
				}
				%>
			</c:when>
			<c:otherwise>
				<liferay-ui:message key="please-contact-the-administrator-to-configure-a-valid-mail-server" />
			</c:otherwise>
		</c:choose>

	</c:when>
	<c:otherwise>
		<script type="text/javascript">
			function changeRange(range) {
				var input = document.getElementById("portlet-mail-toolbar-advanced-search-dates-input");

				input.style.display = (range == "any-day") ? "none" : "";
			}

			function compose(to) {
				window.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/mail/edit_message" /></portlet:renderURL>&to=' + to;
			}

			function hideAdvancedSearch() {
				var search = document.getElementById("portlet-mail-toolbar-search");
				var advSearch = document.getElementById("portlet-mail-toolbar-advanced-search");

				search.style.display = "";
				advSearch.style.display = "none";
			}

			function showAdvancedSearch(filter) {
				var search = document.getElementById("portlet-mail-toolbar-search");
				var searchInput = document.getElementById("portlet-mail-toolbar-search-input");
				var advSearch = document.getElementById("portlet-mail-toolbar-advanced-search");

				search.style.display = "none";
				advSearch.style.display = "";

				var dates = document.getElementById("portlet-mail-toolbar-advanced-search-dates");

				dates.style.display = filter ? "none" : "";
			}

			function setHeader(html) {
				var mailHeader = document.getElementById("portlet-mail-msg-header-div");
				mailHeader.innerHTML = html;
			}
		</script>

		<style type="text/css">
			.portlet-mail-folder-text {
				color: #339933;
				padding-right: 5px;
				font-weight: normal;
				font-size: 0.8em;
				vertical-align: middle;
			}

			#p_p_body_<%= PortletKeys.MAIL %> {
				background-color: <%= mailBgColor %>;
			}

			#portlet-mail-drag-indicator {
				background: #fff;
				border: 1px solid #000;
				font-weight: bold;
				padding: 2px 5px 2px 15px;
				position: absolute;
				cursor: pointer;
			}

			#portlet-mail-folder-pane ul {
				margin: 5px 0 5px 5px;
				overflow: hidden;
			}

			.portlet-mail-folder-selected {
			}

			#portlet-mail-folder-pane ul li {
				padding: 2px 2px 2px 5px;
				margin: 1px 5px 1px 0;
				white-space: nowrap;
			}

			#portlet-mail-folder-pane-td {
				border: 1px solid <%= mailLineColor %>;
			}

			#portlet-mail-folder-pane {
				overflow: hidden;
				width: <%= folderPaneWidth %>;
			}

			#portlet-mail-msgs-pane {
				width: 100%;
			}

			.portlet-mail-msgs-pane-td {
				border: 1px solid <%= mailLineColor %>;
			}

			#portlet-mail-handle {
				background-color: <%= mailBgColor %>;
			}

			#portlet-mail-handle div {
				width: 5px;
				height: 1px;
				font-size: 0;
			}

			#portlet-mail-msgs-preview{
				overflow: hidden;
			}

			#portlet-mail-msgs-preview-pane {
				height: <%= previewPaneHeight %>;
				width: 100%;
				<c:choose>
					<c:when test="<%= BrowserSniffer.is_ie(request) %>">
						overflow: hidden;
						overflow-y: auto;
					</c:when>
					<c:when test="<%= BrowserSniffer.is_safari(request) %>">
						overflow: auto;
					</c:when>
					<c:otherwise>
						overflow: -moz-scrollbars-vertical;
					</c:otherwise>
				</c:choose>
			}

			#portlet-mail-msgs-preview-pane table {
				cursor: pointer;
			}

			#portlet-mail-msgs-handle {
				background-color: <%= mailBgColor %>;
				font-size: 0;
				height: 5px;
			}

			#portlet-mail-msg-header {
				overflow: hidden;
			}

			#portlet-mail-msg-header-div {
				padding: 5px;
			}

			#portlet-mail-msg-detailed-pane {
				overflow: hidden;
			}

			#portlet-mail-msg-frame-div {
				margin-left: 0px;
			}

			#portlet-mail-msg-detailed-frame {
				height: <%= detailedFrameHeight %>;
			}

			.portlet-mail-title-text span {
				padding-right: 5px;
			}

			#portlet-mail-msgs-title-state {
				overflow: hidden;
				width: 24px;
			}

			#portlet-mail-msgs-title-state div {
				padding: 2px 0 2px 5px;
			}

			#portlet-mail-msgs-title-from {
				overflow: hidden;
				width: <%= fromTitleWidth %>;
			}

			#portlet-mail-msgs-title-from div {
				padding: 2px 0 2px 5px;
			}

			#portlet-mail-msgs-title-subject {
				overflow: hidden;
				width: <%= subjectTitleWidth %>;
			}

			#portlet-mail-msgs-title-subject div {
				padding: 2px 0 2px 5px;
			}

			#portlet-mail-msgs-title-received {
				overflow: hidden;
				width: <%= receivedTitleWidth %>;
			}

			#portlet-mail-msgs-title-received div {
				padding: 2px 0 2px 5px;
			}

			#portlet-mail-msgs-title-size {
				overflow: hidden;
				width: 100%;
			}

			#portlet-mail-msgs-title-size div {
				padding: 2px 0 2px 5px;
			}

			.portlet-mail-msgs-title {
				background: #DCDCDC;
			}

			#portlet-mail-msgs-from-handle {
			}

			#portlet-mail-msgs-subject-handle {
			}

			#portlet-mail-msgs-received-handle {
			}

			.portlet-mail-msgs-title-handle {
				font-size: 0;
				height: 1px;
				width: 3px;
			}

			#portlet-mail-msgs-state {
				overflow: hidden;
				width: 24px;
			}

			#portlet-mail-msgs-state div {
				height: 16px;
				overflow: hidden;
				padding-left: 5px;
				width: 24px;
			}

			#portlet-mail-msgs-from {
				overflow: hidden;
				width: <%= fromTitleWidth %>;
			}

			#portlet-mail-msgs-from div {
				height: 16px;
				overflow: hidden;
				padding-left: 5px;
				width: 800px;
			}

			#portlet-mail-msgs-subject {
				overflow: hidden;
				width: <%= subjectTitleWidth %>;
			}

			#portlet-mail-msgs-subject div {
				height: 16px;
				overflow: hidden;
				padding-left: 5px;
				width: 800px;
			}

			#portlet-mail-msgs-received {
				overflow: hidden;
				width: <%= receivedTitleWidth %>;
			}

			#portlet-mail-msgs-received div {
				height: 16px;
				overflow: hidden;
				padding-left: 5px;
				width: 800px;
			}

			#portlet-mail-msgs-size {
				overflow: hidden;
				width: 100%;
			}

			#portlet-mail-msgs-size div {
				height: 16px;
				overflow: hidden;
				padding-left: 5px;
				<c:choose>
					<c:when test="<%= BrowserSniffer.is_safari(request) %>">
						width: 100%;
					</c:when>
					<c:otherwise>
						width: 800px;
					</c:otherwise>
				</c:choose>
			}

			#portlet-mail-bottom-handle {
				border-bottom: 1px solid <%= mailLineColor %>;
			}

			#portlet-mail-bottom-handle div {
				cursor: n-resize;
				font-size: 0;
				height: 5px;
			}
		</style>

		<table border="0" cellpadding="2" cellspacing="2" class="portlet-mail-toolbar font-small" id="portlet-mail-main-toolbar" width="100%">
		<tr>
			<td nowrap onClick="location.href = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/mail/edit_message" /></portlet:renderURL>';">
				<img align="absmiddle" src="<%= themeDisplay.getPathThemeImages() %>/mail/compose.png" /> <liferay-ui:message key="new" />
			</td>
			<td nowrap onClick="Mail.getFolders(true);">
				<img align="absmiddle" src="<%= themeDisplay.getPathThemeImages() %>/mail/check_mail.png" /> <liferay-ui:message key="check-mail" />
			</td>
			<td nowrap onClick="Mail.submitCompose('reply', document.<portlet:namespace />fm);">
				<img align="absmiddle" src="<%= themeDisplay.getPathThemeImages() %>/mail/reply.png" /> <liferay-ui:message key="reply" />
			</td>
			<td nowrap onClick="Mail.submitCompose('replyAll', document.<portlet:namespace />fm);">
				<img align="absmiddle" src="<%= themeDisplay.getPathThemeImages() %>/mail/reply_all.png" /> <liferay-ui:message key="reply-all" />
			</td>
			<td nowrap onClick="Mail.submitCompose('forward', document.<portlet:namespace />fm);">
				<img align="absmiddle" src="<%= themeDisplay.getPathThemeImages() %>/mail/forward.png" /> <liferay-ui:message key="forward" />
			</td>
			<td nowrap onClick="Mail.deleteSelectedMessages();">
				<img align="absmiddle" src="<%= themeDisplay.getPathThemeImages() %>/mail/delete.png" /> <liferay-ui:message key="delete" />
			</td>
			<td nowrap onClick="Mail.print();">
				<img align="absmiddle" src="<%= themeDisplay.getPathThemeImages() %>/mail/print.png" /> <liferay-ui:message key="print" />
			</td>
			<td style="background-color: <%= mailBgColor %>; border: 0px; cursor: default; padding-left: 0px; padding-right: 0px;" width="90%" />
			<td style="background-color: <%= mailBgColor %>; border: 0px; cursor: default; padding-left: 0px; padding-right: 0px;">
				<form method="post" name="<portlet:namespace />search" onSubmit="this.action = themeDisplay.getPathMain() + '/mail/action?sortBy=' + Mail.sortBy.value + '&asc=' + Mail.sortBy.asc; AjaxUtil.submit(this,{onComplete: Mail.getSearchReturn}); return false;">
				<input name="<%= Constants.CMD %>" type="hidden" value="getSearch" />

				<table class="lfr-table" id="portlet-mail-toolbar-search">
				<tr>
					<td>
						<input class="font-small" name="<%= MailDisplayTerms.ENTIRE_MESSAGE %>" size="20" type="text" />
					</td>
					<td>
						<input align="absmiddle" border="0" src="<%= themeDisplay.getPathThemeImages() %>/common/search.png" title="Search" type="image" />
					</td>
					<td style="cursor: pointer; font-size: xx-small; text-align: right;">
						<span onClick="showAdvancedSearch();"><liferay-ui:message key="more" /></span>
					</td>
				</tr>
				</table>

				</form>
			</td>
		</tr>
		</table>

		<table border="0" cellpadding="2" cellspacing="2" class="portlet-mail-toolbar font-small" id="portlet-mail-drafts-toolbar" style="display: none;">
		<tr>
			<td nowrap onClick="location.href='<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/mail/edit_message" /></portlet:renderURL>'">
				<img align="absmiddle" src="<%= themeDisplay.getPathThemeImages() %>/mail/compose.png" /> <liferay-ui:message key="new" />
			</td>
			<td nowrap onClick="Mail.submitCompose('edit', document.<portlet:namespace />fm)">
				<img align="absmiddle" src="<%= themeDisplay.getPathThemeImages() %>/mail/edit_draft.png" /> <liferay-ui:message key="edit" />
			</td>
			<td nowrap onClick="Mail.deleteSelectedMessages()">
				<img align="absmiddle" src="<%= themeDisplay.getPathThemeImages() %>/mail/delete.png" /> <liferay-ui:message key="delete" />
			</td>
		</tr>
		</table>

		<form method="post" name="<portlet:namespace />advSearch" onSubmit='loadForm(document.<portlet:namespace />advSearch, themeDisplay.getPathMain() + "/mail/action?sortBy=" + Mail.sortBy.value + "&asc=" + Mail.sortBy.asc, null, Mail.getSearchReturn); return false;'>
		<input name="<%= Constants.CMD %>" type="hidden" value="getSearch" />

		<div id="portlet-mail-toolbar-advanced-search" style="display: none;" width="100%">
			<table class="lfr-table">
			<tr>
				<td>
					<liferay-ui:message key="from" />
				</td>
				<td>
					<liferay-ui:message key="to" />
				</td>
				<td>
					<liferay-ui:message key="subject" />
				</td>
				<td>
					<liferay-ui:message key="entire-message" />
				</td>
			</tr>
			<tr>
				<td>
					<input name="<%= MailDisplayTerms.FROM %>" size="20" type="text" />
				</td>
				<td>
					<input name="<%= MailDisplayTerms.TO %>" size="20" type="text" />
				</td>
				<td>
					<input name="<%= MailDisplayTerms.SUBJECT %>" size="20" type="text" />
				</td>
				<td>
					<input name="<%= MailDisplayTerms.ENTIRE_MESSAGE %>" size="20" type="text" />
				</td>
			</tr>
			</table>

			<br />

			<table class="lfr-table" id="portlet-mail-toolbar-advanced-search-dates">
			<tr>
				<td>
					<liferay-ui:message key="within" />
				</td>
				<td>
					<select name="dateRange" onchange="changeRange(this.value)">
						<%
						for (int i = 0; i < MailDisplayTerms.DATE_RANGE_OPTIONS.length; i++) {
						%>
							<option value="<%= MailDisplayTerms.DATE_RANGE_OPTIONS[i] %>" <%= (i == 0) ? "selected=\"selected\"" : "" %>>
								<%= LanguageUtil.get(pageContext, MailDisplayTerms.DATE_RANGE_OPTIONS[i]) %>
							</option>
						<%
						}
						%>
					</select>
				</td>
				<td>
					<div id="portlet-mail-toolbar-advanced-search-dates-input">
						<liferay-ui:message key="of" />

						<span style="padding-left: 5px;" />

						<%
						Calendar cal = CalendarFactoryUtil.getCalendar(timeZone, locale);
						%>

						<liferay-ui:input-date
							disableNamespace="<%= true %>"
							formName='<%= renderResponse.getNamespace() + "advSearch" %>'
							monthParam="dateMonth"
							monthValue="<%= cal.get(Calendar.MONTH) %>"
							dayParam="dateDay"
							dayValue="<%= cal.get(Calendar.DATE) %>"
							yearParam="dateYear"
							yearValue="<%= cal.get(Calendar.YEAR) %>"
							yearRangeStart="<%= cal.get(Calendar.YEAR) - 100 %>"
							yearRangeEnd="<%= cal.get(Calendar.YEAR) %>"
							firstDayOfWeek="<%= cal.getFirstDayOfWeek() - 1 %>"
							disabled="<%= false %>"
						/>
					</div>
				</td>
			</tr>
			</table>

			<br />

			<table class="lfr-table">
			<tr>
				<td>
					<select name="<%= MailDisplayTerms.AND_OPERATOR %>">
						<option selected="selected" value="true"><liferay-ui:message key="and" /></option>
						<option value="false"><liferay-ui:message key="or" /></option>
					</select>
				</td>
				<td>
					<input type="submit" value="<liferay-ui:message key="search" />" />
				</td>
				<td>
					<input type="button" value="<liferay-ui:message key="cancel" />" onClick="hideAdvancedSearch();" />
				</td>
			</tr>
			</table>
		</div>

		</form>

		<form action="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/mail/edit_message" /></portlet:renderURL>" method="post" name="<portlet:namespace />fm">
		<input name="<portlet:namespace /><%= Constants.CMD %>" id="portlet-mail-compose-action" type="hidden" />
		<input name="<portlet:namespace />messageId" id="portlet-mail-message-id" type="hidden" />
		<input name="<portlet:namespace />folderId" id="portlet-mail-folder-id" type="hidden" />
		</form>

		<table border="0" cellpadding="0" cellspacing="0">
		<tr>
			<td id="portlet-mail-folder-pane-td" valign="top">
				<div id="portlet-mail-folder-pane">
					<div style="text-align: left;">
						<img src="<%= themeDisplay.getPathThemeImages() %>/progress_bar/loading_animation.gif" />
					</div>
				</div>
			</td>
			<td id="portlet-mail-handle" style="cursor: e-resize;">
				<div style="font-size: 0; height: 30px; width: 5px;"></div>
			</td>
			<td valign="top" width="100%">
				<div id="portlet-mail-msgs-pane">
					<table border="0" cellpadding="0" cellspacing="0" width="100%">
					<tr>
						<td class="portlet-mail-msgs-pane-td" width="100%">
							<div id="portlet-mail-msgs-preview">
								<table id="portlet-mail-msgs-preview-pane-title" border="0" cellpadding="0" cellspacing="0" width="100%">
								<tr>
									<td class="portlet-mail-msgs-title">
										<div id="portlet-mail-msgs-title-state">
											<div class="portlet-mail-title-text">
												<img src="<%= themeDisplay.getPathThemeImages() %>/mail/read.png" />
											</div>
										</div>
									</td>
									<td>
										<div class="portlet-mail-msgs-title-handle"></div>
									</td>
									<td class="portlet-mail-msgs-title">
										<div id="portlet-mail-msgs-title-from">
											<div class="portlet-mail-title-text">
												<span><liferay-ui:message key="from" /></span>
												<span style="display: none;"><liferay-ui:message key="to" /></span>
												<span style="display: none;"><liferay-ui:message key="recipient" /></span>
											</div>
										</div>
									</td>
									<td id="portlet-mail-msgs-from-handle" style="cursor: e-resize;">
										<div class="portlet-mail-msgs-title-handle"></div>
									</td>
									<td class="portlet-mail-msgs-title">
										<div id="portlet-mail-msgs-title-subject">
											<div class="portlet-mail-title-text">
												<span><liferay-ui:message key="subject" /></span>
											</div>
										</div>
									</td>
									<td id="portlet-mail-msgs-subject-handle" style="cursor: e-resize;">
										<div class="portlet-mail-msgs-title-handle"></div>
									</td>
									<td class="portlet-mail-msgs-title">
										<div id="portlet-mail-msgs-title-received">
											<div class="portlet-mail-title-text">
												<span><liferay-ui:message key="date" /></span>
											</div>
										</div>
									</td>
									<td id="portlet-mail-msgs-received-handle" style="cursor: e-resize;">
										<div class="portlet-mail-msgs-title-handle"></div>
									</td>
									<td class="portlet-mail-msgs-title" width="90%">
										<div id="portlet-mail-msgs-title-size">
											<div class="portlet-mail-title-text">
												<span><liferay-ui:message key="size" /></span>
											</div>
										</div>
									</td>
								</tr>
								</table>
							</div>

							<div id="portlet-mail-msgs-preview-pane">
								<table border="0" cellpadding="0" cellspacing="0" width="100%">
								<tr>
									<td valign="top">
										<div id="portlet-mail-msgs-state">
										</div>
									</td>
									<td valign="top">
										<div class="portlet-mail-msgs-title-handle"></div>
									</td>
									<td valign="top">
										<div id="portlet-mail-msgs-from">
										</div>
									</td>
									<td valign="top">
										<div class="portlet-mail-msgs-title-handle"></div>
									</td>
									<td valign="top">
										<div id="portlet-mail-msgs-subject">
										</div>
									</td>
									<td valign="top">
										<div class="portlet-mail-msgs-title-handle"></div>
									</td>
									<td valign="top">
										<div id="portlet-mail-msgs-received">
										</div>
									</td>
									<td valign="top">
										<div class="portlet-mail-msgs-title-handle"></div>
									</td>
									<td valign="top" width="90%">
										<div id="portlet-mail-msgs-size">
										</div>
									</td>
								</tr>
								</table>
							</div>
						</td>
					</tr>
					<tr>
						<td>
							<div id="portlet-mail-msgs-handle" style="cursor: n-resize;">
							</div>
						</td>
					</tr>
					<tr>
						<td class="portlet-mail-msgs-pane-td" width="100%">
							<div id="portlet-mail-msg-header">
								<div id="portlet-mail-msg-header-div"></div>
							</div>
							<div id="portlet-mail-msg-detailed-pane">
								<div id="portlet-mail-msg-frame-div">
									<iframe frameborder="0" id="portlet-mail-msg-detailed-frame" src="" width="100%"></iframe>
								</div>
							</div>
						</td>
					</tr>
					</table>
				</div>
			</td>
		</tr>
		</table>

		<div id="portlet-mail-bottom-handle"><div></div></div>

		<script type="text/javascript">
			changeRange(document.getElementsByName("dateRange")[0].value);

			<%
			String messageIdParam = ParamUtil.getString(request, "messageId", null);

			try {
				String folderId = MailUtil.getFolderName(request);
				long messageId = MailUtil.getMessageId(request);
			%>

				Mail.currentFolderId = "<%= folderId %>";
				Mail.currentMessageId = <%= (messageIdParam != null) ? messageIdParam : (messageId + "") %>;

			<%
			}
			catch (Exception e) {
			}
			%>

			Mail.init("<%= PropsUtil.get(PropsUtil.MAIL_INBOX_NAME) %>", "<%= PropsUtil.get(PropsUtil.MAIL_DRAFTS_NAME) %>", "<%= PropsUtil.get(PropsUtil.MAIL_SENT_NAME) %>", "<%= PropsUtil.get(PropsUtil.MAIL_SPAM_NAME) %>", "<%= PropsUtil.get(PropsUtil.MAIL_TRASH_NAME) %>");
		</script>
	</c:otherwise>
</c:choose>