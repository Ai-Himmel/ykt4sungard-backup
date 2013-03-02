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

<%@ page import="com.liferay.portlet.tags.service.TagsEntryLocalServiceUtil" %>

<%
themeDisplay.setIncludeServiceJs(true);

String randomNamespace = PwdGenerator.getPassword(PwdGenerator.KEY3, 4) + StringPool.UNDERLINE;

String className = (String)request.getAttribute("liferay-ui:tags_selector:className");
long classPK = GetterUtil.getLong((String)request.getAttribute("liferay-ui:tags_selector:classPK"));
String hiddenInput = (String)request.getAttribute("liferay-ui:tags_selector:hiddenInput");
String curTags = GetterUtil.getString((String)request.getAttribute("liferay-ui:tags_selector:curTags"));
boolean focus = GetterUtil.getBoolean((String)request.getAttribute("liferay-ui:tags_selector:focus"));

if (Validator.isNotNull(className) && (classPK > 0)) {
	List entries = TagsEntryLocalServiceUtil.getEntries(className, classPK);

	curTags = ListUtil.toString(entries, "name");
}

String curTagsParam = request.getParameter(hiddenInput);

if (curTagsParam != null) {
	curTags = curTagsParam;
}
%>

<input id="<%= namespace %><%= hiddenInput %>" type="hidden" />

<table class="lfr-table">
<tr>
	<td>
		<span id="<%= randomNamespace %>tagsSummary"></span>
	</td>
</tr>
<tr>
	<td>
		<nobr>
			<input id="<%= randomNamespace %>tags" size="15" type="text" />

			<input disabled id="<%= randomNamespace %>addTag" type="button" value="<liferay-ui:message key="add-tags" />" />
		</nobr>

		<liferay-ui:message key="or" />

		<input id="<%= randomNamespace %>selectTag" type="button" value="<liferay-ui:message key="select-tags" />" />
	</td>
</tr>
</table>

<script type="text/javascript">
	var <%= randomNamespace %> = null;

	jQuery(
		function() {
			<%= randomNamespace %> = new Liferay.TagsSelector(
				{
					instanceVar: "<%= randomNamespace %>",
					hiddenInput: "<%= namespace + hiddenInput %>",
					textInput: "<%= randomNamespace %>tags",
					summarySpan: "<%= randomNamespace %>tagsSummary",
					curTags: "<%= curTags %>",
					focus: <%= focus %>,
                    addTagButton: "<%= randomNamespace %>addTag",
					selectTagButton: '<%= randomNamespace %>selectTag'
                }
			);

			jQuery("#<%= randomNamespace %>tags").keyup(
				function() {
					var addTagInput = jQuery("#<%= randomNamespace %>addTag");

					if (this.value != "") {
						addTagInput.attr("disabled", false);
					}
					else {
						addTagInput.attr("disabled", true);
					}
				}
			);
		}
	);
</script>