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

<%@ include file="/html/portal/layout/edit/init.jsp" %>

<table class="lfr-table">
<tr>
	<td>
		<liferay-ui:message key="link-to-layout" />
	</td>
	<td>
		<input name="TypeSettingsProperties(groupId)" type="hidden" value="<%= layout.getGroupId() %>"></input>
		<input name="TypeSettingsProperties(privateLayout)" type="hidden" value="<%= layout.isPrivateLayout() %>"></input>

		<%
		long linkToLayoutId = GetterUtil.getLong(selLayout.getTypeSettingsProperties().getProperty("linkToLayoutId", StringPool.BLANK));
		%>

		<select name="TypeSettingsProperties(linkToLayoutId)">
			<option value=""></option>

			<%
			List layoutList = (List)request.getAttribute(WebKeys.LAYOUT_LISTER_LIST);

			for (int i = 0; i < layoutList.size(); i++) {

				// id | parentId | ls | obj id | name | img | depth

				String layoutDesc = (String)layoutList.get(i);

				String[] nodeValues = StringUtil.split(layoutDesc, "|");

				long objId = GetterUtil.getLong(nodeValues[3]);
				String name = nodeValues[4];

				int depth = 0;

				if (i != 0) {
					depth = GetterUtil.getInteger(nodeValues[6]);
				}

				for (int j = 0; j < depth; j++) {
					name = "-&nbsp;" + name;
				}

				Layout linkableLayout = null;

				try {
					linkableLayout = LayoutLocalServiceUtil.getLayout(objId);
				}
				catch (Exception e) {
				}

				if (linkableLayout != null) {
			%>

					<option <%= (linkToLayoutId == linkableLayout.getLayoutId()) ? "selected" : "" %> value="<%= linkableLayout.getLayoutId() %>"><%= name %></option>

			<%
				}
			}
			%>

		</select>
	</td>
</tr>
</table>