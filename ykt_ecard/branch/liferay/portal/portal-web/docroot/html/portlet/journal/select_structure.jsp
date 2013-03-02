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

<%@ include file="/html/portlet/journal/init.jsp" %>

<form method="post" name="<portlet:namespace />fm">

<liferay-ui:tabs names="structures" />

<%
PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(LiferayWindowState.POP_UP);

portletURL.setParameter("struts_action", "/journal/select_structure");

StructureSearch searchContainer = new StructureSearch(renderRequest, portletURL);

searchContainer.setDelta(10);
%>

<liferay-ui:search-form
	page="/html/portlet/journal/structure_search.jsp"
	searchContainer="<%= searchContainer %>"
/>

<%
StructureSearchTerms searchTerms = (StructureSearchTerms)searchContainer.getSearchTerms();
%>

<%@ include file="/html/portlet/journal/structure_search_results.jspf" %>

<div class="separator"><!-- --></div>

<%

List resultRows = searchContainer.getResultRows();

for (int i = 0; i < results.size(); i++) {
	JournalStructure structure = (JournalStructure)results.get(i);

	ResultRow row = new ResultRow(structure, structure.getId(), i);

	StringMaker sm = new StringMaker();

	sm.append("javascript: opener.");
	sm.append(renderResponse.getNamespace());
	sm.append("selectStructure('");
	sm.append(structure.getStructureId());
	sm.append("', '");
	sm.append(structure.getName());
	sm.append("'); window.close();");

	String rowHREF = sm.toString();

	// Structure id

	row.addText(structure.getStructureId(), rowHREF);

	// Name and description

	sm = new StringMaker();

	sm.append(structure.getName());

	if (Validator.isNotNull(structure.getDescription())) {
		sm.append("<br />");
		sm.append(structure.getDescription());
	}

	row.addText(sm.toString(), rowHREF);

	// Add result row

	resultRows.add(row);
}
%>

<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />

</form>

<script type="text/javascript">
	Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />searchStructureId);
</script>