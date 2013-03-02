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
String tabs1 = ParamUtil.getString(request, "tabs1", "recipients");

signature = ParamUtil.getString(request, "signature", signature);
vacationMessage = ParamUtil.getString(request, "vacationMessage", vacationMessage);

PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(WindowState.MAXIMIZED);

portletURL.setParameter("struts_action", "/mail/edit");
portletURL.setParameter("tabs1", tabs1);
%>

<script type="text/javascript">

	<%
	String editorParam = "";
	String editorContent = "";

	if (tabs1.equals("signature")) {
		editorParam = "signature";
		editorContent = signature;
	}
	else if (tabs1.equals("vacation-message")) {
		editorParam = "vacationMessage";
		editorContent = vacationMessage;
	}
	%>

	function initEditor() {
		return "<%= UnicodeFormatter.toString(editorContent) %>";
	}

	function <portlet:namespace />savePreferences() {
		<c:if test='<%= tabs1.equals("signature") || tabs1.equals("vacation-message") %>'>
			document.<portlet:namespace />fm.<portlet:namespace /><%= editorParam %>.value = window.<portlet:namespace />editor.getHTML();
		</c:if>

		submitForm(document.<portlet:namespace />fm);
	}
</script>

<form action="<portlet:actionURL><portlet:param name="struts_action" value="/mail/edit" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="<%= Constants.UPDATE %>" />
<input name="<portlet:namespace />tabs1" type="hidden" value="<%= tabs1 %>" />

<liferay-ui:tabs
	names="recipients,filters,forward-address,signature,vacation-message"
	url="<%= portletURL.toString() %>"
/>

<c:choose>
	<c:when test='<%= tabs1.equals("recipients") %>'>
		<liferay-ui:message key="find-potential-recipients-from-the-following" />

		<br /><br />

		<%
		List recipientFinders = RecipientFinderLocator.getInstances();

		for (int i = 0; i < recipientFinders.size(); i++) {
			RecipientFinder recipientFinder = (RecipientFinder)recipientFinders.get(i);

			String rfName = recipientFinder.getClass().getName();

			boolean enabled = GetterUtil.getBoolean(prefs.getValue(rfName, Boolean.TRUE.toString()));

			MultiValueMap options = recipientFinder.getOptions(user.getUserId());

			if (options.size() > 0) {
				Iterator itr1 = new TreeSet(options.keySet()).iterator();
		%>

				<b><%= LanguageUtil.get(pageContext, recipientFinder.getName()) %></b>

				<table class="lfr-table">
				<tr>
					<td>
						<liferay-ui:message key="enabled" />
					</td>
					<td>
						<select name="<portlet:namespace /><%= rfName %>">
							<option value="<%= Boolean.TRUE.toString() %>" <%= enabled ? "selected='selected'" : "" %>><liferay-ui:message key="yes" /></option>
							<option value="<%= Boolean.FALSE.toString() %>" <%= !enabled ? "selected='selected'" : "" %>><liferay-ui:message key="no" /></option>
						</select>
					</td>
				</tr>

			<%
			while (itr1.hasNext()) {
				String option = (String)itr1.next();

				String optionPref = prefs.getValue(rfName + StringPool.PERIOD + option, StringPool.BLANK);
			%>

				<tr>
					<td>
						<%= LanguageUtil.get(pageContext, option) %>
					</td>
					<td>
						<select name="<portlet:namespace /><%= rfName + StringPool.PERIOD + option %>">

							<%
							Iterator itr2 = options.iterator(option);

							while (itr2.hasNext()) {
								String choice = (String)itr2.next();
							%>

								<option value="<%= choice %>" <%= choice.equals(optionPref) ? "selected='selected'" : "" %>><%= LanguageUtil.get(pageContext, choice) %></option>

							<%
							}
							%>

						</select>
					</td>
				</tr>

			<%
			}
			%>

			</table>

			<br /><br />

		<%
			}
		}
		%>

	</c:when>
	<c:when test='<%= tabs1.equals("filters") %>'>
		<liferay-ui:message key="set-the-following-values-to-filter-emails-associated-with-an-email-address-to-a-folder" />

		<br /><br />

		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="email-address" />
			</td>
			<td>
				<liferay-ui:message key="folder" />
			</td>
		</tr>

		<%
		String[] filters = prefs.getValues("filters", new String[0]);

		for (int i = 0; i < 10; i++) {
			String emailAddress = StringPool.BLANK;
			String folder = StringPool.BLANK;

			if (filters.length > i) {
				String[] filter = StringUtil.split(filters[i], "[$FILTER_SEPARATOR$]");

				try {
					emailAddress = filter[0];
					folder = filter[1];
				}
				catch (Exception e) {
				}
			}
		%>

			<tr>
				<td>
					<input class="lfr-input-text" name="<portlet:namespace />filterEmailAddress<%= i %>" type="text" value="<%= emailAddress %>" />
				</td>
				<td>
					<input class="lfr-input-text" name="<portlet:namespace />filterFolder<%= i %>" type="text" value="<%= folder %>" />
				</td>
			</tr>

		<%
		}
		%>

		</table>

		<br />
	</c:when>
	<c:when test='<%= tabs1.equals("forward-address") %>'>

		<%
		forwardAddress = ParamUtil.getString(request, "forwardAddress", forwardAddress);
		forwardAddress = StringUtil.replace(forwardAddress, " ", "\n");
		%>

		<liferay-ui:message key="all-email-will-be-forwarded-to-the-email-addresses-below" /> <liferay-ui:message key="enter-one-email-address-per-line" /> <liferay-ui:message key="remove-all-entries-to-disable-email-forwarding" />

		<br /><br />

		<textarea class="lfr-textarea" name="<portlet:namespace />forwardAddress" wrap="soft"><%= forwardAddress %></textarea>

		<br /><br />

		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="leave-a-copy-of-the-forwarded-message" />
			</td>
			<td>
				<liferay-ui:input-select param="leaveCopy" defaultValue="<%= leaveCopy %>" />
			</td>
		</tr>
		</table>

		<br />
	</c:when>
	<c:when test='<%= tabs1.equals("signature") || tabs1.equals("vacation-message") %>'>
		<c:choose>
			<c:when test='<%= tabs1.equals("signature") %>'>
				<liferay-ui:message key="the-signature-below-will-be-added-to-each-outgoing-message" />
			</c:when>
			<c:otherwise>
				<liferay-ui:message key="the-vacation-message-notifies-others-of-your-absence" />
			</c:otherwise>
		</c:choose>

		<br /><br />

		<liferay-ui:input-editor editorImpl="<%= EDITOR_WYSIWYG_IMPL_KEY %>" />

		<input name="<portlet:namespace /><%= editorParam %>" type="hidden" value="" />

		<br /><br />
	</c:when>
</c:choose>

<input type="button" value="<liferay-ui:message key="save" />" onClick="<portlet:namespace />savePreferences();" />

</form>

<%!
public static final String EDITOR_WYSIWYG_IMPL_KEY = "editor.wysiwyg.portal-web.docroot.html.portlet.mail.edit.jsp";
%>