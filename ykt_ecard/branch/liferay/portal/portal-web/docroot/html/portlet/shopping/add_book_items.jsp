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
String redirect = ParamUtil.getString(request, "redirect");

long categoryId = ParamUtil.getLong(request, "categoryId", ShoppingCategoryImpl.DEFAULT_PARENT_CATEGORY_ID);
%>

<form action="<portlet:actionURL><portlet:param name="struts_action" value="/shopping/add_book_items" /></portlet:actionURL>" method="post" name="<portlet:namespace />fm" onSubmit="alert('<%= UnicodeLanguageUtil.get(pageContext, "please-be-patient") %>'); submitForm(this); return false;">
<input name="<portlet:namespace />redirect" type="hidden" value="<%= redirect %>" />
<input name="<portlet:namespace />categoryId" type="hidden" value="<%= categoryId %>" />

<liferay-util:include page="/html/portlet/shopping/tabs1.jsp">
	<liferay-util:param name="tabs1" value="categories" />
</liferay-util:include>

<div class="breadcrumbs">
	<%= ShoppingUtil.getBreadcrumbs(categoryId, pageContext, renderRequest, renderResponse) %>
</div>

<liferay-ui:message key="add-all-isbn-numbers-separated-by-spaces" />

<br /><br />

<textarea class="lfr-textarea" name="<portlet:namespace />isbns" wrap="soft"></textarea>

<br /><br />

<input type="submit" value="<liferay-ui:message key="save" />" />

<input type="button" value="<liferay-ui:message key="cancel" />" onClick="self.location = '<%= redirect %>';" />

</form>

<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
	<script language="JavaScript">
		Liferay.Util.focusFormField(document.<portlet:namespace />fm.<portlet:namespace />isbns);
	</script>
</c:if>