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

<%
Element el = (Element)request.getAttribute(WebKeys.JOURNAL_STRUCTURE_EL);

String elName = el.attributeValue("name", StringPool.BLANK);
String elType = el.attributeValue("type", StringPool.BLANK);

String parentElType = el.getParent().attributeValue("type", StringPool.BLANK);

IntegerWrapper count = (IntegerWrapper)request.getAttribute(WebKeys.JOURNAL_STRUCTURE_EL_COUNT);
Integer depth = (Integer)request.getAttribute(WebKeys.JOURNAL_STRUCTURE_EL_DEPTH);
Boolean hasSiblings = (Boolean)request.getAttribute(WebKeys.JOURNAL_STRUCTURE_EL_SIBLINGS);
IntegerWrapper tabIndex = (IntegerWrapper)request.getAttribute(WebKeys.TAB_INDEX);
%>

<input id="<portlet:namespace />structure_el<%= count.getValue() %>_depth" type="hidden" value="<%= depth %>" />

<tr>
	<td><img border="0" height="10" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/spacer.png" vspace="0" width="1" /></td>
</tr>
<tr>
	<td>
		<table border="0" cellpadding="0" cellspacing="0">
		<tr>
			<c:if test="<%= depth.intValue() > 0 %>">
				<td><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/spacer.png" vspace="0" width="<%= depth.intValue() * 50 %>" /></td>
			</c:if>

			<td>
				<input id="<portlet:namespace />structure_el<%= count.getValue() %>_name" tabindex="<%= tabIndex.getValue() %>" type="text" size="20" value="<%= elName %>" />
			</td>
			<td><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/spacer.png" vspace="0" width="10" /></td>
			<td>
				<c:choose>
					<c:when test='<%= parentElType.equals("list") || parentElType.equals("multi-list") %>'>
						<input id="<portlet:namespace />structure_el<%= count.getValue() %>_type" tabindex="<%= tabIndex.getValue() %>" type="text" size="20" value="<%= elType %>" />
					</c:when>
					<c:otherwise>
						<select id="<portlet:namespace />structure_el<%= count.getValue() %>_type" tabindex="<%= tabIndex.getValue() %>">
							<option value=""></option>
							<option <%= elType.equals("text") ? "selected" : "" %> value="text"><liferay-ui:message key="text" /></option>
							<option <%= elType.equals("text_box") ? "selected" : "" %> value="text_box"><liferay-ui:message key="text-box" /></option>
							<option <%= elType.equals("text_area") ? "selected" : "" %> value="text_area"><liferay-ui:message key="text-area" /></option>
							<option <%= elType.equals("image") ? "selected" : "" %> value="image"><liferay-ui:message key="image" /></option>
							<option <%= elType.equals("image_gallery") ? "selected" : "" %> value="image_gallery"><%= PortalUtil.getPortletTitle(PortletKeys.IMAGE_GALLERY, user) %></option>
							<option <%= elType.equals("document_library") ? "selected" : "" %> value="document_library"><%= PortalUtil.getPortletTitle(PortletKeys.DOCUMENT_LIBRARY, user) %></option>
							<option <%= elType.equals("boolean") ? "selected" : "" %> value="boolean"><liferay-ui:message key="boolean-flag" /></option>
							<option <%= elType.equals("list") ? "selected" : "" %> value="list"><liferay-ui:message key="selection-list" /></option>
							<option <%= elType.equals("multi-list") ? "selected" : "" %> value="multi-list"><liferay-ui:message key="multi-selection-list" /></option>
						</select>
					</c:otherwise>
				</c:choose>
			</td>

			<c:if test='<%= !parentElType.equals("list") && !parentElType.equals("multi-list") %>'>
				<td><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/spacer.png" vspace="0" width="5" /></td>
				<td>
					<a href="javascript: <portlet:namespace />editElement('add', <%= count.getValue() %>);">
					<img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/arrows/01_plus.png" title="<liferay-ui:message key="add" />" vspace="0" width="16" />
					</a>
				</td>
			</c:if>

			<td><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/spacer.png" vspace="0" width="5" /></td>

			<c:choose>
				<c:when test="<%= el.elements().size() == 0 %>">
					<td>
						<a href="javascript: <portlet:namespace />editElement('remove', <%= count.getValue() %>);">
						<img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/arrows/01_minus.png" title="<liferay-ui:message key="remove" />" vspace="0" width="16" />
						</a>
					</td>
				</c:when>
				<c:otherwise>
					<td><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/spacer.png" vspace="0" width="9" /></td>
				</c:otherwise>
			</c:choose>

			<c:if test="<%= hasSiblings.booleanValue() %>">
				<td><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/spacer.png" vspace="0" width="10" /></td>
				<td>
					<a href="javascript: <portlet:namespace />moveElement(true, <%= count.getValue() %>);">
					<img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/arrows/01_up.png" title="<liferay-ui:message key="up" />" vspace="0" width="16" />
					</a>
				</td>
				<td><img border="0" height="1" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/spacer.png" vspace="0" width="5" /></td>
				<td>
					<a href="javascript: <portlet:namespace />moveElement(false, <%= count.getValue() %>);">
					<img border="0" height="16" hspace="0" src="<%= themeDisplay.getPathThemeImages() %>/arrows/01_down.png" title="<liferay-ui:message key="down" />" vspace="0" width="16" />
					</a>
				</td>
			</c:if>
		</tr>
		</table>
	</td>
</tr>

<%
tabIndex.setValue(tabIndex.getValue() + 2);
%>