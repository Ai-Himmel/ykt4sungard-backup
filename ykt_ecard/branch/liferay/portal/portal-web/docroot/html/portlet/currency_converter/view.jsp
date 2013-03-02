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

<%@ include file="/html/portlet/currency_converter/init.jsp" %>

<%
String from = ParamUtil.getString(request, "from", com.liferay.portlet.currencyconverter.model.Currency.DEFAULT_FROM);
String to = ParamUtil.getString(request, "to", com.liferay.portlet.currencyconverter.model.Currency.DEFAULT_TO);

com.liferay.portlet.currencyconverter.model.Currency currency = CurrencyUtil.getCurrency(from + to);

double number = ParamUtil.getDouble(request, "number", 1.0);

String chartId = ParamUtil.getString(request, "chartId", "3m");

NumberFormat decimalFormat = NumberFormat.getNumberInstance(locale);

decimalFormat.setMaximumFractionDigits(2);
decimalFormat.setMinimumFractionDigits(2);
%>

<form action="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/currency_converter/view" /></portlet:renderURL>" method="post" name="<portlet:namespace />fm" onSubmit="submitForm(this); return false;">

<input type="submit" value="<liferay-ui:message key="convert" />" />

<input name="<portlet:namespace />number" size="3" type="text" value="<%= number %>" />

<select name="<portlet:namespace />from">

	<%
	Iterator itr = allSymbols.entrySet().iterator();

	while (itr.hasNext()) {
		Map.Entry entry = (Map.Entry)itr.next();

		String symbol = (String)entry.getValue();
		String currencyValue = (String)entry.getKey();
	%>

		<option <%= symbol.equals("USD") ? "selected" : "" %> value="<%= symbol %>"><%= currencyValue %></option value>

	<%
	}
	%>

</select>

<b><liferay-ui:message key="to" /></b>

<select name="<portlet:namespace />to">

	<%
	itr = allSymbols.entrySet().iterator();

	while (itr.hasNext()) {
		Map.Entry entry = (Map.Entry)itr.next();

		String symbol = (String)entry.getValue();
		String currencyValue = (String)entry.getKey();
	%>

		<option <%= symbol.equals("EUR") ? "selected" : "" %> value="<%= symbol %>"><%= currencyValue %></option value>

	<%
	}
	%>

</select>

<br /><br />

<c:choose>
	<c:when test="<%= windowState.equals(WindowState.NORMAL) %>">
		<table border="1" cellpadding="3" cellspacing="0" width="100%">
		<tr class="portlet-section-header">
			<td>
				<b><liferay-ui:message key="currency" /></b>
			</td>

			<%
			for (int i = 0; i < symbols.length; i++) {
				String symbol = symbols[i];
			%>

				<td valign="top">
					<liferay-ui:message key='<%= "currency." + symbol %>' /><br />
					(<%= symbol %>)
				</td>

			<%
			}
			%>

		</tr>

		<%
		for (int i = 0; i < symbols.length; i++) {
			String symbol = symbols[i];
		%>

			<tr>
				<td class="portlet-section-header">
					<%= symbol %>
				</td>

		<%
				for (int j = 0; j < symbols.length; j++) {
					String symbol2 = symbols[j];

					currency = CurrencyUtil.getCurrency(symbol2 + symbol);

					if (currency != null) {
		%>

						<c:if test="<%= i != j %>">
							<td class="portlet-section-body"><%= currency.getRate() %></td>
						</c:if>

						<c:if test="<%= i == j %>">
							<td class="portlet-section-body">1</td>
						</c:if>

		<%
					}
				}
		%>

			</tr>

		<%
		}
		%>

		</table>
	</c:when>
	<c:otherwise>
		<table border="1" cellpadding="0" cellspacing="0" width="520">
		<tr>
			<td align="center" width="33%">
				<%= currency.getFromSymbol() %><br />
				<b><%= number %></b>
			</td>
			<td align="center" width="33%">
				<%= currency.getToSymbol() %><br />
				<b><%= decimalFormat.format(number * currency.getRate()) %></b>
			</td>
			<td align="center" width="34%">
				<liferay-ui:message key="historical-charts" /><br />

				<%
				PortletURL portletURL = renderResponse.createRenderURL();

				portletURL.setParameter("struts_action", "/currency_converter/view");
				portletURL.setParameter("number", Double.toString(number));
				portletURL.setParameter("from", currency.getFromSymbol());
				portletURL.setParameter("to", currency.getToSymbol());
				%>

				<c:if test='<%= chartId.equals("3m") %>'>
					3<liferay-ui:message key="month-abbreviation" />, <a href="<% portletURL.setParameter("chartId", "1y"); %><%= portletURL.toString() %>">1<liferay-ui:message key="year-abbreviation" /></a>, <a href="<% portletURL.setParameter("chartId", "2y"); %><%= portletURL.toString() %>">2<liferay-ui:message key="year-abbreviation" /></a>
				</c:if>

				<c:if test='<%= chartId.equals("1y") %>'>
					<a href="<% portletURL.setParameter("chartId", "3m"); %><%= portletURL.toString() %>">3<liferay-ui:message key="month-abbreviation" /></a>, 1<liferay-ui:message key="year-abbreviation" />, <a href="<% portletURL.setParameter("chartId", "2y"); %><%= portletURL.toString() %>">2<liferay-ui:message key="year-abbreviation" /></a>
				</c:if>

				<c:if test='<%= chartId.equals("2y") %>'>
					<a href="<% portletURL.setParameter("chartId", "3m"); %><%= portletURL.toString() %>">3<liferay-ui:message key="month-abbreviation" /></a>, <a href="<% portletURL.setParameter("chartId", "1y"); %><%= portletURL.toString() %>">1<liferay-ui:message key="year-abbreviation" /></a>, 2<liferay-ui:message key="year-abbreviation" />
				</c:if>
			</td>
		</tr>
		</table>

		<br />

		<table border="1" cellpadding="2" cellspacing="0">
		<tr>
			<td>
				<img height="288" src="http://ichart.yahoo.com/z?s=<%= currency.getSymbol() %>=X&t=<%= chartId %>?" width="512" />
			</td>
		</tr>
		</table>
	</c:otherwise>
</c:choose>

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script type="text/javascript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />number);
	</script>
</c:if>