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

<%@ include file="/html/portlet/recent_bloggers/init.jsp" %>

<%
List statsUsers = null;

if (organizationId > 0) {
	statsUsers = BlogsStatsUserLocalServiceUtil.getOrganizationStatsUsers(organizationId, 0, max, new StatsUserLastPostDateComparator(false));
}
else {
	statsUsers = BlogsStatsUserLocalServiceUtil.getCompanyStatsUsers(company.getCompanyId(), 0, max, new StatsUserLastPostDateComparator(false));
}
%>

<c:choose>
	<c:when test="<%= statsUsers.size() == 0 %>">
		<liferay-ui:message key="there-are-no-recent-bloggers" />
	</c:when>
	<c:otherwise>

		<%
		SearchContainer searchContainer = new SearchContainer();

		List headerNames = new ArrayList();

		headerNames.add("user");
		//headerNames.add("place");
		headerNames.add("posts");
		headerNames.add("date");

		if (displayStyle.equals("user-name")) {
			searchContainer.setHeaderNames(headerNames);
		}

		List resultRows = searchContainer.getResultRows();

		for (int i = 0; i < statsUsers.size(); i++) {
			BlogsStatsUser statsUser = (BlogsStatsUser)statsUsers.get(i);

			try {
				Group group = GroupLocalServiceUtil.getGroup(statsUser.getGroupId());
				User user2 = UserLocalServiceUtil.getUserById(statsUser.getUserId());

				String blogType = LanguageUtil.get(pageContext, "personal");

				if (group.isCommunity()) {
					blogType = group.getName();// + " " + LanguageUtil.get(pageContext, "community");
				}
				else if (group.isOrganization()) {
					Organization organization = OrganizationLocalServiceUtil.getOrganization(group.getClassPK());

					blogType = organization.getName();// + " " + LanguageUtil.get(pageContext, "organization");
				}

				int entryCount = BlogsEntryLocalServiceUtil.getGroupUserEntriesCount(group.getGroupId(), user2.getUserId());

				List entries = BlogsEntryLocalServiceUtil.getGroupUserEntries(group.getGroupId(), user2.getUserId(), 0, 1);

				if (entries.size() == 1) {
					BlogsEntry entry = (BlogsEntry)entries.get(0);

					StringMaker sm = new StringMaker();

					sm.append(themeDisplay.getPathMain());
					sm.append("/blogs/find_entry?entryId=");
					sm.append(entry.getEntryId());
					sm.append("&showAllEntries=1");

					String rowHREF = sm.toString();

					ResultRow row = new ResultRow(new Object[] {statsUser, rowHREF}, statsUser.getStatsUserId(), i);

					if (displayStyle.equals("user-name")) {

						// User

						row.addText(user2.getFullName(), rowHREF);

						// Type

						//row.addText(blogType, rowHREF);

						// Number of posts

						row.addText(String.valueOf(entryCount), rowHREF);

						// Last post date

						row.addText(dateFormatDate.format(entry.getModifiedDate()), rowHREF);
					}
					else {

						// User display

						row.addJSP("/html/portlet/recent_bloggers/user_display.jsp");
					}

					// Add result row

					resultRows.add(row);
				}
			}
			catch (Exception e) {
			}
		}
		%>

		<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" paginate="<%= false %>" />
	</c:otherwise>
</c:choose>