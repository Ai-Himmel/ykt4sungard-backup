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

<form action="<portlet:actionURL><portlet:param name="struts_action" value="/currency_converter/edit" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm">
<input name="<portlet:namespace /><%= Constants.CMD %>" type="hidden" value="<%= Constants.UPDATE %>" />
<input name="<portlet:namespace />symbols" type="hidden" value="" />

<%

// Left list

List leftList = new ArrayList();

for (int i = 0; i < symbols.length; i++) {
	leftList.add(new KeyValuePair(symbols[i], LanguageUtil.get(pageContext, "currency." + symbols[i])));
}

//Collections.sort(leftList, new KeyValuePairComparator(false, true));

// Right list

List rightList = new ArrayList();

Arrays.sort(symbols);

Iterator itr = allSymbols.entrySet().iterator();

while (itr.hasNext()) {
	Map.Entry entry = (Map.Entry)itr.next();

	String symbol = (String)entry.getValue();
	String currencyValue = (String)entry.getKey();

	if (Arrays.binarySearch(symbols, symbol) < 0) {
		rightList.add(new KeyValuePair(symbol, LanguageUtil.get(pageContext, "currency." + currencyValue)));
	}
}

Collections.sort(rightList, new KeyValuePairComparator(false, true));
%>

<liferay-ui:input-move-boxes
	formName="fm"
	leftTitle="current"
	rightTitle="available"
	leftBoxName="current_actions"
	rightBoxName="available_actions"
	leftReorder="true"
	leftList="<%= leftList %>"
	rightList="<%= rightList %>"
/>

<br />

<input type="button" value="<liferay-ui:message key="save" />" onClick="document.<portlet:namespace />fm.<portlet:namespace />symbols.value = Liferay.Util.listSelect(document.<portlet:namespace />fm.<portlet:namespace />current_actions); submitForm(document.<portlet:namespace />fm);" />

</form>