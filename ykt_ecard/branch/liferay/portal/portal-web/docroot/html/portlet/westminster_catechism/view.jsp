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

<%@ include file="/html/portlet/westminster_catechism/init.jsp" %>

<%
String tabs1 = ParamUtil.getString(request, "tabs1", "larger");

PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(WindowState.MAXIMIZED);

portletURL.setParameter("struts_action", "/westminster_catechism/view");
portletURL.setParameter("tabs1", tabs1);
%>

<liferay-ui:tabs
	names="larger,shorter"
	url="<%= portletURL.toString() %>"
/>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<c:choose>
		<c:when test='<%= tabs1.equals("larger") %>'>
			<table class="lfr-table">

			<%
			List entries = WCUtil.getLarger();

			for (int i = 0; i < entries.size(); i++) {
				WCEntry entry = (WCEntry)entries.get(i);
			%>

				<tr>
					<td valign="top">
						<b><%= i + 1 %>.</b>
					</td>
					<td valign="top">
						<a name="q<%= i + 1%>">

						<a href="#a<%= i + 1 %>"><u><%= WCUtil.translate(entry.getQuestion()) %></u></a>

						<br /><br />
					</td>
				</tr>

			<%
			}
			%>

			<tr>
				<td colspan="2">
					<br />
				</td>
			</tr>

			<%
			for (int i = 0; i < entries.size(); i++) {
				WCEntry entry = (WCEntry)entries.get(i);
			%>

				<tr>
					<td valign="top">
						<b><%= i + 1 %>.</b>
					</td>
					<td valign="top">
						<a name="a<%= i + 1%>">

						<b><%= WCUtil.translate(entry.getQuestion()) %></b>&nbsp;&nbsp;<a href="#q<%= i + 1 %>">&laquo;</a>

						<br /><br />
					</td>
				</tr>
				<tr>
					<td></td>
					<td>
						<%= WCUtil.translate(entry.getAnswer()) %>

						<br /><br />
					</td>
				</tr>
				<tr>
					<td></td>
					<td>
						<span style="font-size: xx-small;">

						<%
						int letter = (int)'a';
						String letterSuffix = "";

						String[][] proofs = entry.getProofs();

						for (int j = 0; j < proofs.length; j++) {
							String[] scriptures = proofs[j];
						%>

							[<%= (char)letter %><%= letterSuffix %>].

						<%

							for (int k = 0; k < scriptures.length; k++) {
						%>

								<%= scriptures[k] %><%= (k + 1) < scriptures.length ? ";" : "" %>

						<%
							}
						%>


							<br />

						<%
							if ((char)letter == 'z') {
								letter = (int)'a';
								letterSuffix = String.valueOf(GetterUtil.getInteger(letterSuffix) + 1);
						%>

							<br />

						<%
							}
							else {
								letter++;
							}
						}
						%>

						<%= (i + 1) < entries.size() ? "<br /><br />" : "" %>

						</span>
					</td>
				</tr>
			<%
			}
			%>

			</table>
		</c:when>
		<c:when test='<%= tabs1.equals("shorter") %>'>
			<table class="lfr-table">

			<%
			List entries = WCUtil.getShorter();

			for (int i = 0; i < entries.size(); i++) {
				WCEntry entry = (WCEntry)entries.get(i);
			%>

				<tr>
					<td valign="top">
						<b><%= i + 1 %>.</b>
					</td>
					<td valign="top">
						<a name="q<%= i + 1%>">

						<a href="#a<%= i + 1 %>"><u><%= WCUtil.translate(entry.getQuestion()) %></u></a>

						<br /><br />
					</td>
				</tr>

			<%
			}
			%>

			<tr>
				<td colspan="2">
					<br />
				</td>
			</tr>

			<%
			for (int i = 0; i < entries.size(); i++) {
				WCEntry entry = (WCEntry)entries.get(i);
			%>

				<tr>
					<td valign="top">
						<b><%= i + 1 %>.</b>
					</td>
					<td valign="top">
						<a name="a<%= i + 1%>">

						<b><%= WCUtil.translate(entry.getQuestion()) %></b>&nbsp;&nbsp;<a href="#q<%= i + 1 %>">&laquo;</a>

						<br /><br />
					</td>
				</tr>
				<tr>
					<td></td>
					<td>
						<%= WCUtil.translate(entry.getAnswer()) %>

						<br /><br />
					</td>
				</tr>
				<tr>
					<td></td>
					<td>
						<span style="font-size: xx-small;">

						<%
						int letter = 97;

						String[][] proofs = entry.getProofs();

						for (int j = 0; j < proofs.length; j++) {
							String[] scriptures = proofs[j];
						%>

							[<%= (char)letter++ %>].

						<%

							for (int k = 0; k < scriptures.length; k++) {
						%>

								<%= scriptures[k] %><%= (k + 1) < scriptures.length ? ";" : "" %>

						<%
							}
						%>


							<br />

						<%
						}
						%>

						<%= (i + 1) < entries.size() ? "<br /><br />" : "" %>

						</span>
					</td>
				</tr>
			<%
			}
			%>

			</table>
		</c:when>
	</c:choose>
</c:if>