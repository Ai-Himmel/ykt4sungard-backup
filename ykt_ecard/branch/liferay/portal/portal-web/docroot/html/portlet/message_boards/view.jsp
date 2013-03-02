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

<%@ include file="/html/portlet/message_boards/init.jsp" %>

<%
String tabs1 = ParamUtil.getString(request, "tabs1", "categories");
String tabs2 = ParamUtil.getString(request, "tabs2", "general");

String redirect = ParamUtil.getString(request, "redirect");

MBCategory category = (MBCategory)request.getAttribute(WebKeys.MESSAGE_BOARDS_CATEGORY);

long categoryId = BeanParamUtil.getLong(category, request, "categoryId", MBCategoryImpl.DEFAULT_PARENT_CATEGORY_ID);

PortletURL portletURL = renderResponse.createRenderURL();

portletURL.setWindowState(WindowState.MAXIMIZED);

portletURL.setParameter("struts_action", "/message_boards/view");
portletURL.setParameter("tabs1", tabs1);
portletURL.setParameter("tabs2", tabs2);
portletURL.setParameter("categoryId", String.valueOf(categoryId));
%>

<liferay-util:include page="/html/portlet/message_boards/tabs1.jsp" />

<liferay-portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" varImpl="searchURL"><portlet:param name="struts_action" value="/message_boards/search" /></liferay-portlet:renderURL>

<c:choose>
	<c:when test='<%= tabs1.equals("categories") %>'>
		<form action="<%= searchURL %>" method="get" name="<portlet:namespace />fm1" onSubmit="submitForm(this); return false;">
		<liferay-portlet:renderURLParams varImpl="searchURL" />
		<input name="<portlet:namespace />redirect" type="hidden" value="<%= currentURL %>" />
		<input name="<portlet:namespace />breadcrumbsCategoryId" type="hidden" value="<%= categoryId %>" />
		<input name="<portlet:namespace />searchCategoryIds" type="hidden" value="<%= categoryId %>" />

		<c:if test="<%= category != null %>">
			<div class="breadcrumbs">
				<%= MBUtil.getBreadcrumbs(category, null, pageContext, renderRequest, renderResponse) %>
			</div>
		</c:if>

		<%
		List headerNames = new ArrayList();

		headerNames.add("category");
		headerNames.add("categories");
		headerNames.add("threads");
		headerNames.add("posts");
		headerNames.add(StringPool.BLANK);

		SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, "cur1", SearchContainer.DEFAULT_DELTA, portletURL, headerNames, null);

		int total = MBCategoryLocalServiceUtil.getCategoriesCount(portletGroupId.longValue(), categoryId);

		searchContainer.setTotal(total);

		List results = MBCategoryLocalServiceUtil.getCategories(portletGroupId.longValue(), categoryId, searchContainer.getStart(), searchContainer.getEnd());

		searchContainer.setResults(results);

		List resultRows = searchContainer.getResultRows();

		for (int i = 0; i < results.size(); i++) {
			MBCategory curCategory = (MBCategory)results.get(i);

			curCategory = curCategory.toEscapedModel();

			ResultRow row = new ResultRow(curCategory, curCategory.getCategoryId(), i);

			boolean restricted = !MBCategoryPermission.contains(permissionChecker, curCategory, ActionKeys.VIEW);

			row.setRestricted(restricted);

			PortletURL rowURL = renderResponse.createRenderURL();

			rowURL.setWindowState(WindowState.MAXIMIZED);

			rowURL.setParameter("struts_action", "/message_boards/view");
			rowURL.setParameter("categoryId", String.valueOf(curCategory.getCategoryId()));

			// Name and description

			StringMaker sm = new StringMaker();

			if (!restricted) {
				sm.append("<a href=\"");
				sm.append(rowURL);
				sm.append("\">");
			}

			sm.append("<b>");
			sm.append(curCategory.getName());
			sm.append("</b>");

			if (Validator.isNotNull(curCategory.getDescription())) {
				sm.append("<br />");
				sm.append(curCategory.getDescription());
			}

			if (!restricted) {
				sm.append("</a>");

				List subcategories = MBCategoryLocalServiceUtil.getCategories(portletGroupId.longValue(), curCategory.getCategoryId(), 0, 5);

				if (subcategories.size() > 0) {
					sm.append("<br /><u>");
					sm.append(LanguageUtil.get(pageContext, "subcategories"));
					sm.append("</u>: ");

					for (int j = 0; j < subcategories.size(); j++) {
						MBCategory subcategory = (MBCategory)subcategories.get(j);

						rowURL.setParameter("categoryId", String.valueOf(subcategory.getCategoryId()));

						sm.append("<a href=\"");
						sm.append(rowURL);
						sm.append("\">");
						sm.append(subcategory.getName());
						sm.append("</a>");

						if ((j + 1) < subcategories.size()) {
							sm.append(", ");
						}
					}

					rowURL.setParameter("categoryId", String.valueOf(curCategory.getCategoryId()));
				}
			}

			row.addText(sm.toString());

			// Statistics

			List subcategoryIds = new ArrayList();

			subcategoryIds.add(new Long(curCategory.getCategoryId()));

			MBCategoryLocalServiceUtil.getSubcategoryIds(subcategoryIds, portletGroupId.longValue(), curCategory.getCategoryId());

			int categoriesCount = subcategoryIds.size() - 1;
			int threadsCount = MBThreadLocalServiceUtil.getCategoriesThreadsCount(subcategoryIds);
			int messagesCount = MBMessageLocalServiceUtil.getCategoriesMessagesCount(subcategoryIds);

			row.addText(String.valueOf(categoriesCount), rowURL);
			row.addText(String.valueOf(threadsCount), rowURL);
			row.addText(String.valueOf(messagesCount), rowURL);

			// Action

			if (restricted) {
				row.addText(StringPool.BLANK);
			}
			else {
				row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/message_boards/category_action.jsp");
			}

			// Add result row

			resultRows.add(row);
		}

		boolean showAddCategoryButton = MBCategoryPermission.contains(permissionChecker, plid.longValue(), categoryId, ActionKeys.ADD_CATEGORY);
		%>

		<c:if test="<%= showAddCategoryButton || (results.size() > 0) %>">
			<div>
				<c:if test="<%= results.size() > 0 %>">
					<label for="<portlet:namespace />keywords1"><liferay-ui:message key="search" /></label>

					<input id="<portlet:namespace />keywords1" name="<portlet:namespace />keywords" size="30" type="text" />

					<input type="submit" value="<liferay-ui:message key="search-messages" />" />
				</c:if>

				<c:if test="<%= showAddCategoryButton %>">
					<input type="button" value="<liferay-ui:message key='<%= (category == null) ? "add-category" : "add-subcategory" %>' />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/message_boards/edit_category" /><portlet:param name="redirect" value="<%= currentURL %>" /><portlet:param name="parentCategoryId" value="<%= String.valueOf(categoryId) %>" /></portlet:renderURL>';" />
				</c:if>
			</div>

			<c:if test="<%= results.size() > 0 %>">
				<br />
			</c:if>
		</c:if>

		<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />

		<c:if test="<%= (category != null) && (showAddCategoryButton || (results.size() > 0)) %>">
			<br />
		</c:if>

		</form>

		<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
			<script type="text/javascript">
				Liferay.Util.focusFormField(document.<portlet:namespace />fm1.<portlet:namespace />keywords);
			</script>
		</c:if>

		<c:if test="<%= category != null %>">
			<form action="<%= searchURL %>" method="get" name="<portlet:namespace />fm2" onSubmit="submitForm(this); return false;">
			<liferay-portlet:renderURLParams varImpl="searchURL" />
			<input name="<portlet:namespace />redirect" type="hidden" value="<%= currentURL %>" />
			<input name="<portlet:namespace />breadcrumbsCategoryId" type="hidden" value="<%= categoryId %>" />
			<input name="<portlet:namespace />searchCategoryId" type="hidden" value="<%= categoryId %>" />

			<liferay-ui:tabs names="threads" />

			<%
			headerNames.clear();

			headerNames.add("thread");
			headerNames.add("started-by");
			headerNames.add("posts");
			headerNames.add("views");
			headerNames.add("last-post");
			headerNames.add(StringPool.BLANK);

			searchContainer = new SearchContainer(renderRequest, null, null, "cur2", SearchContainer.DEFAULT_DELTA, portletURL, headerNames, null);

			total = MBThreadLocalServiceUtil.getThreadsCount(categoryId);

			searchContainer.setTotal(total);

			results = MBThreadLocalServiceUtil.getThreads(categoryId, searchContainer.getStart(), searchContainer.getEnd());

			searchContainer.setResults(results);

			resultRows = searchContainer.getResultRows();

			for (int i = 0; i < results.size(); i++) {
				MBThread thread = (MBThread)results.get(i);

				MBMessage message = MBMessageLocalServiceUtil.getMessage(thread.getRootMessageId());

				message = message.toEscapedModel();

				boolean readThread = MBThreadLocalServiceUtil.hasReadThread(themeDisplay.getUserId(), thread.getThreadId());

				ResultRow row = new ResultRow(message, thread.getThreadId(), i, !readThread);

				row.setRestricted(!MBMessagePermission.contains(permissionChecker, message, ActionKeys.VIEW));

				PortletURL rowURL = renderResponse.createRenderURL();

				rowURL.setWindowState(WindowState.MAXIMIZED);

				rowURL.setParameter("struts_action", "/message_boards/view_message");
				rowURL.setParameter("messageId", String.valueOf(message.getMessageId()));

				// Thread

				StringMaker sm = new StringMaker();

				String[] threadPriority = MBUtil.getThreadPriority(prefs, themeDisplay.getLanguageId(), thread.getPriority(), themeDisplay);

				if ((threadPriority != null) && (thread.getPriority() > 0)) {
					sm.append("<img align=\"left\" alt=\"");
					sm.append(threadPriority[0]);
					sm.append("\" border=\"0\" src=\"");
					sm.append(threadPriority[1]);
					sm.append("\" title=\"");
					sm.append(threadPriority[0]);
					sm.append("\" >");
				}

				sm.append(message.getSubject());

				row.addText(sm.toString(), rowURL);

				// Started by

				if (message.isAnonymous()) {
					row.addText(LanguageUtil.get(pageContext, "anonymous"), rowURL);
				}
				else {
					row.addText(PortalUtil.getUserName(message.getUserId(), message.getUserName()), rowURL);
				}

				// Number of posts

				row.addText(String.valueOf(thread.getMessageCount()), rowURL);

				// Number of views

				row.addText(String.valueOf(thread.getViewCount()), rowURL);

				// Last post

				if (thread.getLastPostDate() == null) {
					row.addText(LanguageUtil.get(pageContext, "none"), rowURL);
				}
				else {
					sm = new StringMaker();

					sm.append(LanguageUtil.get(pageContext, "date"));
					sm.append(": ");
					sm.append(dateFormatDateTime.format(thread.getLastPostDate()));

					String lastPostByUserName = PortalUtil.getUserName(thread.getLastPostByUserId(), StringPool.BLANK);

					if (Validator.isNotNull(lastPostByUserName)) {
						sm.append("<br />");
						sm.append(LanguageUtil.get(pageContext, "by"));
						sm.append(": ");
						sm.append(lastPostByUserName);
					}

					row.addText(sm.toString(), rowURL);
				}

				// Action

				row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/message_boards/message_action.jsp");

				// Add result row

				resultRows.add(row);
			}

			boolean showAddMessageButton = MBCategoryPermission.contains(permissionChecker, category, ActionKeys.ADD_MESSAGE);

			if (showAddMessageButton && !themeDisplay.isSignedIn()) {
				if (!allowAnonymousPosting) {
					showAddMessageButton = false;
				}
			}
			%>

			<c:if test="<%= showAddMessageButton || (results.size() > 0) %>">
				<div>
					<c:if test="<%= results.size() > 0 %>">
						<label for="<portlet:namespace />keywords2"><liferay-ui:message key="search" /></label>

						<input id="<portlet:namespace />keywords2" name="<portlet:namespace />keywords" size="30" type="text" />

						<input type="submit" value="<liferay-ui:message key="search-messages" />" />
					</c:if>

					<c:if test="<%= showAddMessageButton %>">
						<input type="button" value="<liferay-ui:message key="post-new-thread" />" onClick="self.location = '<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>"><portlet:param name="struts_action" value="/message_boards/edit_message" /><portlet:param name="redirect" value="<%= currentURL %>" /><portlet:param name="categoryId" value="<%= String.valueOf(categoryId) %>" /></portlet:renderURL>';" />
					</c:if>
				</div>

				<c:if test="<%= results.size() > 0 %>">
					<br />
				</c:if>
			</c:if>

			<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />

			</form>

			<c:if test="<%= windowState.equals(WindowState.MAXIMIZED) %>">
				<script type="text/javascript">
					Liferay.Util.focusFormField(document.<portlet:namespace />fm2.<portlet:namespace />keywords);
					Liferay.Util.focusFormField(document.<portlet:namespace />fm1.<portlet:namespace />keywords);
				</script>
			</c:if>
		</c:if>
	</c:when>
	<c:when test='<%= tabs1.equals("my_posts") || tabs1.equals("my_subscriptions") || tabs1.equals("recent_posts") %>'>

		<%
		long groupThreadsUserId = ParamUtil.getLong(request, "groupThreadsUserId");

		if ((tabs1.equals("my_posts") || tabs1.equals("my_subscriptions")) && themeDisplay.isSignedIn()) {
			groupThreadsUserId = user.getUserId();
		}

		if (groupThreadsUserId > 0) {
			portletURL.setParameter("groupThreadsUserId", String.valueOf(groupThreadsUserId));
		}
		%>

		<c:if test='<%= tabs1.equals("recent_posts") %>'>

			<%
			String rssURL = themeDisplay.getPathMain() + "/message_boards/rss?p_l_id=" + plid + "&groupId=" + portletGroupId.longValue();

			if (groupThreadsUserId > 0) {
				rssURL += "&userId=" + groupThreadsUserId;
			}

			rssURL += rssURLParams;
			%>

			<table class="lfr-table">
			<tr>
				<td>
					<liferay-ui:icon
						image="rss"
						message="recent-posts-rss"
						url="<%= rssURL %>"
						target="_blank"
						label="<%= true %>"
					/>
				</td>

				<c:if test="<%= groupThreadsUserId > 0 %>">
					<td>
						<liferay-ui:message key="filter-by-user" />: <%= PortalUtil.getUserName(groupThreadsUserId, StringPool.BLANK) %>
					</td>
				</c:if>
			</tr>
			</table>

			<br />
		</c:if>

		<%
		int totalCategories = 0;
		%>

		<c:if test='<%= tabs1.equals("my_subscriptions") %>'>

			<%
			List headerNames = new ArrayList();

			headerNames.add("category");
			headerNames.add("categories");
			headerNames.add("threads");
			headerNames.add("posts");
			headerNames.add(StringPool.BLANK);

			SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, "cur1", SearchContainer.DEFAULT_DELTA, portletURL, headerNames, "you-are-not-subscribed-to-any-categories");

			int total = MBCategoryLocalServiceUtil.getSubscribedCategoriesCount(portletGroupId.longValue(), user.getUserId());

			searchContainer.setTotal(total);

			totalCategories = total;

			List results = MBCategoryLocalServiceUtil.getSubscribedCategories(portletGroupId.longValue(), user.getUserId(), searchContainer.getStart(), searchContainer.getEnd());

			searchContainer.setResults(results);

			List resultRows = searchContainer.getResultRows();

			for (int i = 0; i < results.size(); i++) {
				MBCategory curCategory = (MBCategory)results.get(i);

				curCategory = curCategory.toEscapedModel();

				ResultRow row = new ResultRow(curCategory, curCategory.getCategoryId(), i);

				boolean restricted = !MBCategoryPermission.contains(permissionChecker, curCategory, ActionKeys.VIEW);

				row.setRestricted(restricted);

				PortletURL rowURL = renderResponse.createRenderURL();

				rowURL.setWindowState(WindowState.MAXIMIZED);

				rowURL.setParameter("struts_action", "/message_boards/view");
				rowURL.setParameter("categoryId", String.valueOf(curCategory.getCategoryId()));

				// Name and description

				StringMaker sm = new StringMaker();

				if (!restricted) {
					sm.append("<a href=\"");
					sm.append(rowURL);
					sm.append("\">");
				}

				sm.append("<b>");
				sm.append(curCategory.getName());
				sm.append("</b>");

				if (Validator.isNotNull(curCategory.getDescription())) {
					sm.append("<br />");
					sm.append(curCategory.getDescription());
				}

				row.addText(sm.toString());

				// Statistics

				List subcategoryIds = new ArrayList();

				subcategoryIds.add(new Long(curCategory.getCategoryId()));

				MBCategoryLocalServiceUtil.getSubcategoryIds(subcategoryIds, portletGroupId.longValue(), curCategory.getCategoryId());

				int categoriesCount = subcategoryIds.size() - 1;
				int threadsCount = MBThreadLocalServiceUtil.getCategoriesThreadsCount(subcategoryIds);
				int messagesCount = MBMessageLocalServiceUtil.getCategoriesMessagesCount(subcategoryIds);

				row.addText(String.valueOf(categoriesCount), rowURL);
				row.addText(String.valueOf(threadsCount), rowURL);
				row.addText(String.valueOf(messagesCount), rowURL);

				// Action

				if (restricted) {
					row.addText(StringPool.BLANK);
				}
				else {
					row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/message_boards/category_action.jsp");
				}

				// Add result row

				resultRows.add(row);
			}
			%>

			<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
		</c:if>

		<%
		List headerNames = new ArrayList();

		headerNames.add("thread");
		headerNames.add("started-by");
		headerNames.add("posts");
		headerNames.add("views");
		headerNames.add("last-post");
		headerNames.add(StringPool.BLANK);

		String emptyResultsMessage = null;

		if (tabs1.equals("my_posts")) {
			emptyResultsMessage = "you-do-not-have-any-posts";
		}
		else if (tabs1.equals("my_subscriptions")) {
			emptyResultsMessage = "you-are-not-subscribed-to-any-threads";
		}
		else if (tabs1.equals("recent_posts")) {
			emptyResultsMessage = "there-are-no-recent-posts";
		}

		SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, SearchContainer.DEFAULT_DELTA, portletURL, headerNames, emptyResultsMessage);

		List results = null;

		if (tabs1.equals("my_subscriptions")) {
			int total = MBThreadLocalServiceUtil.getGroupThreadsCount(portletGroupId.longValue(), groupThreadsUserId, true);

			searchContainer.setTotal(total);

			results = MBThreadLocalServiceUtil.getGroupThreads(portletGroupId.longValue(), groupThreadsUserId, true, searchContainer.getStart(), searchContainer.getEnd());

			searchContainer.setResults(results);
		}
		else {
			int total = MBThreadLocalServiceUtil.getGroupThreadsCount(portletGroupId.longValue(), groupThreadsUserId);

			searchContainer.setTotal(total);

			results = MBThreadLocalServiceUtil.getGroupThreads(portletGroupId.longValue(), groupThreadsUserId, searchContainer.getStart(), searchContainer.getEnd());

			searchContainer.setResults(results);
		}

		List resultRows = searchContainer.getResultRows();

		for (int i = 0; i < results.size(); i++) {
			MBThread thread = (MBThread)results.get(i);

			MBMessage message = MBMessageLocalServiceUtil.getMessage(thread.getRootMessageId());

			message = message.toEscapedModel();

			boolean readThread = MBThreadLocalServiceUtil.hasReadThread(themeDisplay.getUserId(), thread.getThreadId());

			ResultRow row = new ResultRow(message, thread.getThreadId(), i, !readThread);

			row.setRestricted(!MBMessagePermission.contains(permissionChecker, message, ActionKeys.VIEW));

			PortletURL rowURL = renderResponse.createRenderURL();

			rowURL.setWindowState(WindowState.MAXIMIZED);

			rowURL.setParameter("struts_action", "/message_boards/view_message");
			rowURL.setParameter("messageId", String.valueOf(message.getMessageId()));

			// Thread

			StringMaker sm = new StringMaker();

			String[] threadPriority = MBUtil.getThreadPriority(prefs, themeDisplay.getLanguageId(), thread.getPriority(), themeDisplay);

			if ((threadPriority != null) && (thread.getPriority() > 0)) {
				sm.append("<img align=\"left\" alt=\"");
				sm.append(threadPriority[0]);
				sm.append("\" border=\"0\" src=\"");
				sm.append(threadPriority[1]);
				sm.append("\" title=\"");
				sm.append(threadPriority[0]);
				sm.append("\" >");
			}

			sm.append(message.getSubject());

			row.addText(sm.toString(), rowURL);

			// Started by

			if (message.isAnonymous()) {
				row.addText(LanguageUtil.get(pageContext, "anonymous"), rowURL);
			}
			else {
				row.addText(PortalUtil.getUserName(message.getUserId(), message.getUserName()), rowURL);
			}

			// Number of posts

			row.addText(String.valueOf(thread.getMessageCount()), rowURL);

			// Number of views

			row.addText(String.valueOf(thread.getViewCount()), rowURL);

			// Last post

			if (thread.getLastPostDate() == null) {
				row.addText(LanguageUtil.get(pageContext, "none"), rowURL);
			}
			else {
				sm = new StringMaker();

				sm.append(LanguageUtil.get(pageContext, "date"));
				sm.append(": ");
				sm.append(dateFormatDateTime.format(thread.getLastPostDate()));

				String lastPostByUserName = PortalUtil.getUserName(thread.getLastPostByUserId(), StringPool.BLANK);

				if (Validator.isNotNull(lastPostByUserName)) {
					sm.append("<br />");
					sm.append(LanguageUtil.get(pageContext, "by"));
					sm.append(": ");
					sm.append(lastPostByUserName);
				}

				row.addText(sm.toString(), rowURL);
			}

			// Action

			row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/message_boards/message_action.jsp");

			// Add result row

			resultRows.add(row);
		}
		%>

		<c:if test='<%= tabs1.equals("my_subscriptions") %>'>
			<br />
		</c:if>

		<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
	</c:when>
	<c:when test='<%= tabs1.equals("statistics") %>'>
		<liferay-ui:tabs
			names="general,top-posters"
			param="tabs2"
			url="<%= portletURL.toString() %>"
		/>

		<c:choose>
			<c:when test='<%= tabs2.equals("general") %>'>
				<liferay-ui:message key="num-of-categories" />: <%= numberFormat.format(MBCategoryLocalServiceUtil.getCategoriesCount(portletGroupId.longValue())) %><br />
				<liferay-ui:message key="num-of-posts" />: <%= numberFormat.format(MBMessageLocalServiceUtil.getGroupMessagesCount(portletGroupId.longValue())) %><br />
				<liferay-ui:message key="num-of-participants" />: <%= numberFormat.format(MBStatsUserLocalServiceUtil.getStatsUsersCount(portletGroupId.longValue())) %>
			</c:when>
			<c:when test='<%= tabs2.equals("top-posters") %>'>

				<%
				SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, SearchContainer.DEFAULT_DELTA, portletURL, null, "there-are-no-top-posters");

				int total = MBStatsUserLocalServiceUtil.getStatsUsersCount(portletGroupId.longValue());

				searchContainer.setTotal(total);

				List results = MBStatsUserLocalServiceUtil.getStatsUsers(portletGroupId.longValue(), searchContainer.getStart(), searchContainer.getEnd());

				searchContainer.setResults(results);

				List resultRows = searchContainer.getResultRows();

				for (int i = 0; i < results.size(); i++) {
					MBStatsUser statsUser = (MBStatsUser)results.get(i);

					ResultRow row = new ResultRow(statsUser, statsUser.getStatsUserId(), i);

					// User display

					row.addJSP("/html/portlet/message_boards/top_posters_user_display.jsp");

					// Add result row

					resultRows.add(row);
				}
				%>

				<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
			</c:when>
		</c:choose>
	</c:when>
	<c:when test='<%= tabs1.equals("banned_users") %>'>

		<%
		List headerNames = new ArrayList();

		headerNames.add("banned-user");
		headerNames.add("banned-by");
		headerNames.add("ban-date");

		if (PropsValues.MESSAGE_BOARDS_EXPIRE_BAN_INTERVAL > 0) {
			headerNames.add("unban-date");
		}

		headerNames.add(StringPool.BLANK);

		SearchContainer searchContainer = new SearchContainer(renderRequest, null, null, SearchContainer.DEFAULT_CUR_PARAM, SearchContainer.DEFAULT_DELTA, portletURL, headerNames, "there-are-no-banned-users");

		int total = MBBanLocalServiceUtil.getBansCount(portletGroupId.longValue());

		searchContainer.setTotal(total);

		List results = MBBanLocalServiceUtil.getBans(portletGroupId.longValue(), searchContainer.getStart(), searchContainer.getEnd());

		searchContainer.setResults(results);

		List resultRows = searchContainer.getResultRows();

		for (int i = 0; i < results.size(); i++) {
			MBBan ban = (MBBan)results.get(i);

			ResultRow row = new ResultRow(ban, ban.getBanId(), i);

			// Banned User

			row.addText(PortalUtil.getUserName(ban.getBanUserId(), StringPool.BLANK));

			// Banned By

			row.addText(PortalUtil.getUserName(ban.getUserId(), StringPool.BLANK));

			// Ban Date

			row.addText(dateFormatDateTime.format(ban.getCreateDate()));

			// Unban Date

			if (PropsValues.MESSAGE_BOARDS_EXPIRE_BAN_INTERVAL > 0) {
				row.addText(dateFormatDateTime.format(MBUtil.getUnbanDate(ban, PropsValues.MESSAGE_BOARDS_EXPIRE_BAN_INTERVAL)));
			}

			// Action

			row.addJSP("right", SearchEntry.DEFAULT_VALIGN, "/html/portlet/message_boards/ban_user_action.jsp");

			// Add result row

			resultRows.add(row);
		}
		%>

		<liferay-ui:search-iterator searchContainer="<%= searchContainer %>" />
	</c:when>
</c:choose>