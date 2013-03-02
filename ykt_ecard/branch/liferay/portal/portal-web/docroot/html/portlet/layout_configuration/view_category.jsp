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

<%@ include file="/html/portlet/layout_configuration/init.jsp" %>

<%
PortletCategory portletCategory = (PortletCategory)request.getAttribute(WebKeys.PORTLET_CATEGORY);

String oldCategoryPath = (String)request.getAttribute(WebKeys.PORTLET_CATEGORY_PATH);

String newCategoryPath = LanguageUtil.get(pageContext, portletCategory.getName());

Pattern pattern = Pattern.compile("[:,a-z,A-Z,0-9]+");

Matcher matcher = pattern.matcher(newCategoryPath);

StringMaker divId = new StringMaker();

while (matcher.find()) {
	divId.append(matcher.group());
}

newCategoryPath = divId.toString();

if (Validator.isNotNull(oldCategoryPath)) {
	newCategoryPath = oldCategoryPath + ":" + newCategoryPath;
}

List categories = ListUtil.fromCollection(portletCategory.getCategories());

Collections.sort(categories, new PortletCategoryComparator(company.getCompanyId(), locale));

List portlets = new ArrayList();

Iterator itr = portletCategory.getPortlets().iterator();

String externalPortletCategory = null;

while (itr.hasNext()) {
	String portletId = (String)itr.next();

	Portlet portlet = PortletLocalServiceUtil.getPortletById(user.getCompanyId(), portletId);

	if (portlet != null) {
		if (portlet.isSystem()) {
		}
		else if (!portlet.isActive()) {
		}
		else if (!portlet.isInstanceable() && layoutTypePortlet.hasPortletId(portlet.getPortletId())) {
			portlets.add(portlet);
		}
		else if (!portlet.hasAddPortletPermission(user.getUserId())) {
		}
		else {
			portlets.add(portlet);
		}

		if (portlet.isWARFile() && Validator.isNull(externalPortletCategory)) {
			PortletConfig ptltConfig = PortletConfigFactory.create(portlet, application);

			ResourceBundle resourceBundle = ptltConfig.getResourceBundle(locale);

			try {
				externalPortletCategory = resourceBundle.getString(portletCategory.getName());
			}
			catch (MissingResourceException mre) {
			}
		}
	}
}

Collections.sort(portlets, new PortletTitleComparator(application, locale));

if ((categories.size() > 0) || (portlets.size() > 0)) {
%>

	<div class="lfr-add-content collapsed" id="<%= newCategoryPath.replace(':', '-') %>">
		<h2>
			<span><%= Validator.isNotNull(externalPortletCategory) ? externalPortletCategory : LanguageUtil.get(pageContext, portletCategory.getName()) %></span>
		</h2>

		<div class="lfr-content-category hidden">

			<%
			itr = categories.iterator();

			while (itr.hasNext()) {
				request.setAttribute(WebKeys.PORTLET_CATEGORY, itr.next());
				request.setAttribute(WebKeys.PORTLET_CATEGORY_PATH, newCategoryPath);
			%>

				<liferay-util:include page="/html/portlet/layout_configuration/view_category.jsp" />

			<%
				request.setAttribute(WebKeys.PORTLET_CATEGORY_PATH, oldCategoryPath);
			}

			itr = portlets.iterator();

			while (itr.hasNext()) {
				Portlet portlet = (Portlet)itr.next();

				divId = new StringMaker();

				divId.append(newCategoryPath);
				divId.append(":");

				matcher = pattern.matcher(PortalUtil.getPortletTitle(portlet, application, locale));

				while (matcher.find()) {
					divId.append(matcher.group());
				}

				boolean portletInstanceable = portlet.isInstanceable();
				boolean portletUsed = layoutTypePortlet.hasPortletId(portlet.getPortletId());
				boolean portletLocked = (!portletInstanceable && portletUsed);
			%>

				<div class="lfr-portlet-item<c:if test="<%= portletLocked %>"> lfr-portlet-used</c:if><c:if test="<%= portletInstanceable %>"> lfr-instanceable</c:if>"" id="<%= divId.toString().replace(':', '-') %>" instanceable="<%= portletInstanceable %>" plid="<%= plid %>" portletId="<%= portlet.getPortletId() %>">
					<p><%= PortalUtil.getPortletTitle(portlet, application, locale) %> <a href="javascript: ;"><liferay-ui:message key="add" /></a></p>
				</div>

			<%
			}
			%>

		</div>
	</div>

<%
}
%>