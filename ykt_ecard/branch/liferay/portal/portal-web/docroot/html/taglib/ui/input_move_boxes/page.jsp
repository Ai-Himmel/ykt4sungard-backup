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
String formName = namespace + request.getAttribute("liferay-ui:input-move-boxes:formName");

String leftTitle = LanguageUtil.get(pageContext, (String)request.getAttribute("liferay-ui:input-move-boxes:leftTitle"));
String rightTitle = LanguageUtil.get(pageContext, (String)request.getAttribute("liferay-ui:input-move-boxes:rightTitle"));

String leftBoxName = namespace + request.getAttribute("liferay-ui:input-move-boxes:leftBoxName");
String rightBoxName = namespace + request.getAttribute("liferay-ui:input-move-boxes:rightBoxName");

String leftOnChange = (String)request.getAttribute("liferay-ui:input-move-boxes:leftOnChange");
String rightOnChange = (String)request.getAttribute("liferay-ui:input-move-boxes:rightOnChange");

boolean leftReorder = GetterUtil.getBoolean((String)request.getAttribute("liferay-ui:input-move-boxes:leftReorder"));
boolean rightReorder = GetterUtil.getBoolean((String)request.getAttribute("liferay-ui:input-move-boxes:rightReorder"));

List leftList = (List)request.getAttribute("liferay-ui:input-move-boxes:leftList");
List rightList = (List)request.getAttribute("liferay-ui:input-move-boxes:rightList");
%>

<table border="0" cellpadding="0" cellspacing="0" width="100%">
<tr>
	<td class="alpha">
		<table border="0" cellpadding="2" cellspacing="1" width="100%">
		<tr>
			<td align="center" class="gamma" valign="top" width="48%">
				<table border="0" cellpadding="2" cellspacing="0" width="100%">
				<tr>
					<td align="center" class="alpha">
						<font class="alpha" size="2"><b><%= leftTitle %></b></font>
					</td>
				</tr>
				<tr>
					<td align="center">
						<table border="0" cellpadding="0" cellspacing="2">
						<tr>
							<td>
								<select multiple name="<%= leftBoxName %>" size="10" <%= Validator.isNotNull(leftOnChange) ? "onChange=\"" + leftOnChange + "\"" : "" %> onFocus="document.<%= formName %>.<%= rightBoxName %>.selectedIndex = '-1';">

								<%
								for (int i = 0; i < leftList.size(); i++) {
									KeyValuePair kvp = (KeyValuePair)leftList.get(i);
								%>

									<option value="<%= kvp.getKey() %>"><%= kvp.getValue() %></option>

								<%
								}
								%>

								</select>
							</td>

							<c:if test="<%= leftReorder %>">
								<td valign="top">
									<a href="javascript: Liferay.Util.reorder(document.<%= formName %>.<%= leftBoxName %>, 0);"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/arrows/02_up.png" vspace="2" width="16" /></a><br />
									<a href="javascript: Liferay.Util.reorder(document.<%= formName %>.<%= leftBoxName %>, 1);"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/arrows/02_down.png" vspace="2" width="16" /></a><br />
								</td>
							</c:if>

						</tr>
						</table>
					</td>
				</tr>
				</table>
			</td>
			<td align="center" class="gamma" valign="middle" width="4%">
				<a href="javascript: Liferay.Util.moveItem(document.<%= formName %>.<%= leftBoxName %>, document.<%= formName %>.<%= rightBoxName %>, <%= !rightReorder %>);"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/arrows/02_right.png" vspace="2" width="16" onClick="self.focus();" /></a>

				<br /><br />

				<a href="javascript: Liferay.Util.moveItem(document.<%= formName %>.<%= rightBoxName %>, document.<%= formName %>.<%= leftBoxName %>, <%= !leftReorder %>);"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/arrows/02_left.png" vspace="2" width="16" onClick="self.focus();" /></a>
			</td>
			<td align="center" valign="top" width="48%">
				<table border="0" cellpadding="2" cellspacing="0" width="100%">
				<tr>
					<td align="center" class="alpha">
						<font class="alpha" size="2"><b><%= rightTitle %></b></font>
					</td>
				</tr>
				<tr>
					<td align="center">
						<table border="0" cellpadding="0" cellspacing="2">
						<tr>
							<td>
								<select multiple name="<%= rightBoxName %>" size="10" <%= Validator.isNotNull(rightOnChange) ? "onChange=\"" + rightOnChange + "\"" : "" %> onFocus="document.<%= formName %>.<%= leftBoxName %>.selectedIndex = '-1';">

								<%
								for (int i = 0; i < rightList.size(); i++) {
									KeyValuePair kvp = (KeyValuePair)rightList.get(i);
								%>

									<option value="<%= kvp.getKey() %>"><%= kvp.getValue() %></option>

								<%
								}
								%>

								</select>
							</td>

							<c:if test="<%= rightReorder %>">
								<td valign="top">
									<a href="javascript: Liferay.Util.reorder(document.<%= formName %>.<%= rightBoxName %>, 0);"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/arrows/02_up.png" vspace="2" width="16" /></a><br />
									<a href="javascript: Liferay.Util.reorder(document.<%= formName %>.<%= rightBoxName %>, 1);"><img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/arrows/02_down.png" vspace="2" width="16" /></a><br />
								</td>
							</c:if>

						</tr>
						</table>
					</td>
				</tr>
				</table>
			</td>
		</tr>
		</table>
	</td>
</tr>
</table>