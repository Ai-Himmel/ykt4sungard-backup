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

<%@ include file="/html/portlet/rss/init.jsp" %>

<%
String url = ParamUtil.getString(request, "url");
int index = ParamUtil.getInteger(request, "index");

SyndFeed feed = null;

try {
	ObjectValuePair ovp = RSSUtil.getFeed(url);

	feed = (SyndFeed)ovp.getValue();
}
catch (Exception e) {
}
%>

<c:if test="<%= (url != null) && (feed != null) %>">
	<div style="padding: 10px 10px 10px 10px;">

		<%
		List entries = feed.getEntries();

		if (index < entries.size()) {
			SyndEntry entry = (SyndEntry)entries.get(index);

			SyndContent description = entry.getDescription();

			String contentString = description.getValue();

			SyndContent content = null;

			try {
				content = (SyndContent)entry.getContents().get(0);

				if (Validator.isNotNull(content.getValue().trim())) {
					contentString = content.getValue();
				}
			}
			catch (Throwable t) {
			}
		%>

			<a class="font-large" href="<%= entry.getLink() %>" style="font-weight: bold;" target="_blank"><%= entry.getTitle() %></a><br />

			<c:if test="<%= entry.getPublishedDate() != null %>">
				<%= dateFormatDateTime.format(entry.getPublishedDate()) %><br />
			</c:if>

			<div class="font-small">
				<%= contentString %>
			</div>

		<%
		}
		%>

	</div>
</c:if>