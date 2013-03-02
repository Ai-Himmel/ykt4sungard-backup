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

<%@ include file="/html/taglib/ui/search_toggle/init.jsp" %>

<script type="text/javascript">
	var <%= id %>curClickValue = "<%= clickValue %>";

	function <%= id %>toggleSearch() {
		jQuery("#<%= id %>basic").toggle();
		jQuery("#<%= id %>advanced").toggle();

		var advancedSearchObj = jQuery("#<%= id %><%= displayTerms.ADVANCED_SEARCH %>");

		if (<%= id %>curClickValue == "basic") {
			<%= id %>curClickValue = "advanced";

			advancedSearchObj.val(true);
		}
		else {
			<%= id %>curClickValue = "basic";

			advancedSearchObj.val(false);
		}

		loadPage(mainPath + "/portal/session_click", "<%= id %>=" + <%= id %>curClickValue);
	}
</script>

<input id="<%= id %><%= displayTerms.ADVANCED_SEARCH %>" name="<%= namespace %><%= displayTerms.ADVANCED_SEARCH %>" type="hidden" value="<%= clickValue.equals("basic") ? false : true %>" />

<div id="<%= id %>basic" style="display: <%= clickValue.equals("basic") ? "block" : "none" %>;">
	<label for="<%= id %><%= displayTerms.KEYWORDS %>"><liferay-ui:message key="search" /></label>

	<input id="<%= id %><%= displayTerms.KEYWORDS %>" name="<%= namespace %><%= displayTerms.KEYWORDS %>" size="30" type="text" value="<%= Html.escape(displayTerms.getKeywords()) %>" />

	&nbsp;<a href="javascript: <%= id %>toggleSearch();" tabindex="-1" ><liferay-ui:message key="advanced" /> &raquo;</a>
</div>

<div id="<%= id %>advanced" style="display: <%= !clickValue.equals("basic") ? "block" : "none" %>;">

	<%
	StringMaker sm = new StringMaker();

	sm.append("<select name=\"");
	sm.append(namespace);
	sm.append(displayTerms.AND_OPERATOR);
	sm.append("\">");

	sm.append("<option ");

	if (displayTerms.isAndOperator()) {
		sm.append("selected ");
	}

	sm.append("value=\"1\">");
	sm.append(LanguageUtil.get(pageContext, "all"));
	sm.append("</option>");

	sm.append("<option ");

	if (!displayTerms.isAndOperator()) {
		sm.append("selected ");
	}

	sm.append("value=\"0\">");
	sm.append(LanguageUtil.get(pageContext, "any"));
	sm.append("</option>");

	sm.append("</select>");
	%>

	<%= LanguageUtil.format(pageContext, "match-x-of-the-following-fields", sm.toString()) %>

	<br /><br />