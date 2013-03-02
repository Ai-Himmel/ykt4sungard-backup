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

<%@ include file="/html/portlet/enterprise_admin/init.jsp" %>

<%
String redirect = ParamUtil.getString(request, "redirect");

String sessionId = ParamUtil.getString(request, "sessionId");

Map liveUsers = LiveUsers.getSessionUsers();

UserTracker userTracker = (UserTracker)liveUsers.get(sessionId);

userTracker = userTracker.toEscapedModel();
%>

<form action="<portlet:actionURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/enterprise_admin/edit_session" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />sessionId" type="hidden" value="<%= sessionId %>" />

<liferay-util:include page="/html/portlet/enterprise_admin/tabs1.jsp">
	<liferay-util:param name="tabs1" value="monitoring" />
</liferay-util:include>

<liferay-ui:tabs names="live-session" />

<c:choose>
	<c:when test="<%= userTracker == null %>">
		<liferay-ui:message key="session-id-not-found" />

		<br /><br />

		<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />
	</c:when>
	<c:otherwise>

		<%
		User user2 = null;

		try {
			user2 = UserLocalServiceUtil.getUserById(userTracker.getUserId());
		}
		catch (NoSuchUserException nsue) {
		}
		%>

		<table class="lfr-table">
		<tr>
			<td>
				<liferay-ui:message key="session-id" />:
			</td>
			<td>
				<%= sessionId %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="user-id" />:
			</td>
			<td>
				<%= userTracker.getUserId() %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="name" />:
			</td>
			<td>
				<%= (user2 != null) ? user2.getFullName() : LanguageUtil.get(pageContext, "not-available") %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="email-address" />:
			</td>
			<td>
				<%= (user2 != null) ? user2.getEmailAddress() : LanguageUtil.get(pageContext, "not-available") %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="last-request" />:
			</td>
			<td>
				<%= dateFormatDateTime.format(userTracker.getModifiedDate()) %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="num-of-hits" />:
			</td>
			<td>
				<%= userTracker.getHits() %>
			</td>
		</tr>
		<tr>
			<td colspan="2">
				<br />
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="browser-os-type" />:
			</td>
			<td>
				<%= userTracker.getUserAgent() %>
			</td>
		</tr>
		<tr>
			<td>
				<liferay-ui:message key="remote-host-ip" />:
			</td>
			<td>
				<%= userTracker.getRemoteAddr() %> / <%= userTracker.getRemoteHost() %>
			</td>
		</tr>
		</table>

		<br />

		<table border="0" cellpadding="0" cellspacing="0" width="100%">
		<tr class="portlet-section-header">
			<td>
				<b><liferay-ui:message key="accessed-urls" /></b>
			</td>
			<td align="right">
				<span style="font-size: xx-small;">
				[<a href="javascript: void(0);" onClick="Liferay.Util.toggleByIdSpan(this, '<portlet:namespace />accessedUrls'); self.focus();"><span><liferay-ui:message key="show" /></span><span style="display: none;"><liferay-ui:message key="hide" /></span></a>]
				</span>
			</td>
		</tr>
		<tr class="portlet-section-header">
			<td colspan="2">
				<div id="<portlet:namespace />accessedUrls" style="display: none;">
					<table border="0" cellpadding="4" cellspacing="0" width="100%">

					<%
					List paths = userTracker.getPaths();

					for (int i = 0; i < paths.size(); i++) {
						UserTrackerPath userTrackerPath = (UserTrackerPath)paths.get(i);

						String className = "portlet-section-body";
						String classHoverName = "portlet-section-body-hover";

						if (MathUtil.isEven(i)) {
							className = "portlet-section-alternate";
							classHoverName = "portlet-section-alternate-hover";
						}
					%>

						<tr class="<%= className %>" style="font-size: xx-small;" onMouseEnter="this.className = '<%= classHoverName %>';" onMouseLeave="this.className = '<%= className %>';">
							<td valign="top">
								<%= StringUtil.replace(userTrackerPath.getPath(), "&", "& ") %>
							</td>
							<td nowrap valign="top">
								<%= dateFormatDateTime.format(userTrackerPath.getPathDate()) %>
							</td>
						</tr>

					<%
					}
					%>

					</table>
				</div>
			</td>
		</tr>
		<tr class="portlet-section-header">
			<td>
				<b><liferay-ui:message key="session-attributes" /></b>
			</td>
			<td align="right">
				<span style="font-size: xx-small;">
				[<a href="javascript: void(0);" onClick="Liferay.Util.toggleByIdSpan(this, '<portlet:namespace />sessionAttributes'); self.focus();"><span><liferay-ui:message key="show" /></span><span style="display: none;"><liferay-ui:message key="hide" /></span></a>]
				</span>
			</td>
		</tr>
		<tr>
			<td colspan="2">
				<div id="<portlet:namespace />sessionAttributes" style="display: none;">
					<table border="0" cellpadding="4" cellspacing="0" width="100%">

					<%
					boolean userSessionAlive = true;

					HttpSession userSession = PortalSessionContext.get(sessionId);

					if (userSession != null) {
						try {
							int counter = 0;

							Set sortedAttrNames = new TreeSet();

							Enumeration enu = userSession.getAttributeNames();

							while (enu.hasMoreElements()) {
								String attrName = (String)enu.nextElement();

								sortedAttrNames.add(attrName);
							}

							Iterator itr = sortedAttrNames.iterator();

							while (itr.hasNext()) {
								String attrName = (String)itr.next();

								String className = "portlet-section-body";
								String classHoverName = "portlet-section-body-hover";

								if (MathUtil.isEven(counter++)) {
									className = "portlet-section-alternate";
									classHoverName = "portlet-section-alternate-hover";
								}
					%>

								<tr class="<%= className %>" style="font-size: xx-small;" onMouseEnter="this.className = '<%= classHoverName %>';" onMouseLeave="this.className = '<%= className %>';">
									<td valign="top">
										<%= attrName %>
									</td>
								</tr>

					<%
							}
						}
						catch (Exception e) {
							userSessionAlive = false;

							e.printStackTrace();
						}
					}
					%>

					</table>
				</div>
			</td>
		</tr>
		</table>

		<br />

		<c:if test="<%= userSessionAlive && !session.getId().equals(sessionId) %>">
			<input type="submit" value="<liferay-ui:message key="kill-session" />" />
		</c:if>

		<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />
	</c:otherwise>
</c:choose>

</form>