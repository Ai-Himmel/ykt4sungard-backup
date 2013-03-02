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

<%@ include file="/html/portlet/shopping/init.jsp" %>

<%
String[] fieldsQuantities = StringUtil.split(ParamUtil.getString(request, "fieldsQuantities"));

List names = new ArrayList();
List values = new ArrayList();

for (int i = 0; i < 9; i++) {
	String n = request.getParameter("n" + i);
	String v = request.getParameter("v" + i);

	if (n == null || v == null) {
		break;
	}

	names.add(n);
	values.add(StringUtil.split(v));
}

int rowsCount = 1;

for (int i = 0; i < values.size(); i++) {
	String[] vArray = (String[])values.get(i);

	rowsCount = rowsCount * vArray.length;
}
%>

<script type="text/javascript">
	function <portlet:namespace />updateItemQuantities() {
		var itemQuantities = "";

		<%
		for (int i = 0; i < rowsCount; i++) {
		%>

			itemQuantities = itemQuantities + document.<portlet:namespace />fm.<portlet:namespace />fieldsQuantity<%= i %>.value + ",";

		<%
		}
		%>

		opener.document.<portlet:namespace />fm.<portlet:namespace />fieldsQuantities.value = itemQuantities;

		self.close();
	}
</script>

<form method="post" name="<portlet:namespace />fm">

<table border="1" cellpadding="4" cellspacing="0">
<tr>

	<%
	for (int i = 0; i < names.size(); i++) {
	%>

		<td>
			<b><%= names.get(i) %></b>
		</td>

	<%
	}
	%>

	<td>
		<b><liferay-ui:message key="quantity" /></b>
	</td>
</tr>

<%
for (int i = 0; i < rowsCount; i++) {
%>

	<tr>

		<%
		for (int j = 0; j < names.size(); j++) {
			int numOfRepeats = 1;

			for (int k = j + 1; k < values.size(); k++) {
				String[] vArray = (String[])values.get(k);

				numOfRepeats = numOfRepeats * vArray.length;
			}

			String[] vArray = (String[])values.get(j);

			int arrayPos;

			for (arrayPos = i / numOfRepeats; arrayPos >= vArray.length; arrayPos = arrayPos - vArray.length) {
			}
		%>

			<td>
				<%= vArray[arrayPos] %>
			</td>

		<%
		}

		int fieldsQuantity = 0;

		if (i < fieldsQuantities.length) {
			fieldsQuantity = GetterUtil.getInteger(fieldsQuantities[i]);
		}
		%>

		<td>
			<input name="<portlet:namespace />fieldsQuantity<%= i %>" type="text" size="4" value="<%= fieldsQuantity %>" />
		</td>
	</tr>

<%
}
%>

</table>

<br />

<input type="button" value="<liferay-ui:message key="update" />" onClick="<portlet:namespace />updateItemQuantities();" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.close();" />

</form>