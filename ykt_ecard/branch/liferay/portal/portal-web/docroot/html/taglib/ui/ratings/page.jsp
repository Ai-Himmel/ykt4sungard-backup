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

<%@ page import="com.liferay.portlet.ratings.NoSuchEntryException" %>
<%@ page import="com.liferay.portlet.ratings.model.RatingsEntry" %>
<%@ page import="com.liferay.portlet.ratings.model.RatingsStats" %>
<%@ page import="com.liferay.portlet.ratings.service.RatingsEntryLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.ratings.service.RatingsStatsLocalServiceUtil" %>

<%
String randomNamespace = PwdGenerator.getPassword(PwdGenerator.KEY3, 4) + StringPool.UNDERLINE;

String className = (String)request.getAttribute("liferay-ui:ratings:className");
long classPK = GetterUtil.getLong((String)request.getAttribute("liferay-ui:ratings:classPK"));
String url = (String)request.getAttribute("liferay-ui:ratings:url");

double yourScore = 0.0;

try {
	RatingsEntry entry = RatingsEntryLocalServiceUtil.getEntry(themeDisplay.getUserId(), className, classPK);

	yourScore = entry.getScore();
}
catch (NoSuchEntryException nsee) {
}

RatingsStats stats = RatingsStatsLocalServiceUtil.getStats(className, classPK);
%>

<table border="0" cellpadding="0" cellspacing="0" class="taglib-ratings">
<tr>
	<c:if test="<%= themeDisplay.isSignedIn() %>">
		<td>
			<div style="font-size: xx-small; padding-bottom: 2px;">
				<liferay-ui:message key="your-rating" />
			</div>

			<div id="<%= randomNamespace %>yourRating">
				<img src="<%= themeDisplay.getPathThemeImages() %>/ratings/star_off.png" /><img src="<%= themeDisplay.getPathThemeImages() %>/ratings/star_off.png" /><img src="<%= themeDisplay.getPathThemeImages() %>/ratings/star_off.png" /><img src="<%= themeDisplay.getPathThemeImages() %>/ratings/star_off.png" /><img src="<%= themeDisplay.getPathThemeImages() %>/ratings/star_off.png" />
			</div>
		</td>
		<td style="padding-left: 30px;"></td>
	</c:if>

	<td>
		<div style="font-size: xx-small; padding-bottom: 2px;">
			<liferay-ui:message key="average" /> (<span id="<%= randomNamespace %>totalEntries"><%= stats.getTotalEntries() %></span> <%= LanguageUtil.get(pageContext, (stats.getTotalEntries() == 1) ? "vote" : "votes") %>)<br />
		</div>

		<div id="<%= randomNamespace %>averageRating" onmousemove="ToolTip.show(event, this, '<%= stats.getAverageScore() %> Stars')">
			<img src="<%= themeDisplay.getPathThemeImages() %>/ratings/star_off.png" /><img src="<%= themeDisplay.getPathThemeImages() %>/ratings/star_off.png" /><img src="<%= themeDisplay.getPathThemeImages() %>/ratings/star_off.png" /><img src="<%= themeDisplay.getPathThemeImages() %>/ratings/star_off.png" /><img src="<%= themeDisplay.getPathThemeImages() %>/ratings/star_off.png" />
		</div>
	</td>
</tr>
</table>

<script type="text/javascript">
	<%= randomNamespace %>yourRatingObj = new StarRating(
		"<%= randomNamespace %>yourRating",
		{
			rating: <%= yourScore %>,
			onComplete: function(rating) {
				var url = "<%= url %>?p_l_id=<%= themeDisplay.getPlid() %>&className=<%= className %>&classPK=<%= classPK %>&score=" + rating;

				AjaxUtil.request(
					url,
					{
						onComplete: function(xmlHttpReq) {
							var res = Liferay.Util.toJSONObject(xmlHttpReq.responseText);

							document.getElementById("<%= randomNamespace %>totalEntries").innerHTML = res.totalEntries;
							document.getElementById("<%= randomNamespace %>averageRating").onmousemove = function(event) {
								ToolTip.show(event, this, res.averageScore.toFixed(1) + ' Stars');
							};

							<%= randomNamespace %>averageRatingObj.display(res.averageScore);
						}
					}
				);
			}
		});

	<%= randomNamespace %>averageRatingObj = new StarRating(
		"<%= randomNamespace %>averageRating",
		{
			displayOnly: true,
			rating: <%= stats.getAverageScore() %>
		});
</script>