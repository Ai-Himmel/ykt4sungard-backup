<%
/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

<%@ include file="/html/common/init.jsp" %>

<%
String namespace = ParamUtil.getString(request, "namespace");

List notes = (List)request.getAttribute(WebKeys.NOTES_LIST);
%>

<liferay:box top="/html/common/themes/inner_top.jsp" bottom="/html/common/themes/inner_bottom.jsp">
	<liferay:param name="box_title" value='<%= LanguageUtil.get(pageContext, "notes") %>' />

	<input name="<%= namespace %>note_id" type="hidden" value="">

	<table border="0" cellpadding="0" cellspacing="0" width="95%">
	<tr>
		<td>
			<div style="border-right: #CCCCCC 1px solid; border-top: #CCCCCC 1px solid; overflow: scroll; border-left: #CCCCCC 1px solid; width: <%= themeDisplay.getResTotal() * .95 %>px; border-bottom: #CCCCCC 1px solid; height: 150px">
				<table border="0" cellpadding="4" cellspacing="0" width="100%">
				<tr>
					<td>
						<table border="0" cellpadding="2" cellspacing="0" width="100%">

						<%
						DateFormat noteDF = DateFormat.getDateTimeInstance(DateFormat.SHORT, DateFormat.SHORT, locale);
						noteDF.setTimeZone(timeZone);

						for (int i = 0; i < notes.size(); i++) {
							Note note = (Note)notes.get(i);
						%>

							<tr>
								<td><font class="bg" size="1"><b>-</b></font></td>
								<td><font class="bg" size="1"><b><%= noteDF.format(note.getCreateDate()) %> &gt;</b> <%= PortalUtil.getUserName(note.getUserId(), note.getUserName()) %></font></td>
								<td align="right"><font class="bg" size="1">[<a class="bg" href="javascript: <%= namespace %>deleteNote('<%= note.getNoteId() %>');"><%= LanguageUtil.get(pageContext, "delete") %></a>]</font></td>
							</tr>
							<tr>
								<td>
								</td>
								<td width="99%">
									<font class="bg" size="1">
									<%= note.getContent() %>
									</font>
								</td>
								<td></td>
							</tr>
							<tr>
								<td colspan="3"><img border="0" height="4" hspace="0" src="<%= themeDisplay.getPathThemeImage() %>/spacer.gif" vspace="0" width="1"></td>
							</tr>

						<%
						}
						%>

						</table>
					</td>
				</tr>
				</table>
			</div>
		</td>
	</tr>
	<tr>
		<td>
			<br>
		</td>
	</tr>
	<tr>
		<td>
			<table border="0" cellpadding="0" cellspacing="0">
			<tr>
				<td>
					<input class="form-text" name="<%= namespace %>note_content" type="text" size="80">
				</td>
				<td width="10">
					&nbsp;
				</td>
				<td>
					<input class="portlet-form-button" type="button" value="<%= LanguageUtil.get(pageContext, "add-note") %>" onClick="<%= namespace %>addNote();">
				</td>
			</tr>
			</table>
		</td>
	</tr>
	</table>
</liferay:box>