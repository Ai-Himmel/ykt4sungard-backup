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

<%@ include file="/html/portlet/amazon_rankings/init.jsp" %>

<table class="lfr-table">

<%
Set amazonRankingsSet = new TreeSet();

for (int i = 0; i < isbns.length; i++) {
	AmazonRankings rankings = AmazonRankingsUtil.getAmazonRankings(isbns[i]);

	if (rankings != null) {
		amazonRankingsSet.add(rankings);
	}
}

Iterator itr = amazonRankingsSet.iterator();

while (itr.hasNext()) {
	AmazonRankings amazonRankings = (AmazonRankings)itr.next();
%>

	<tr>
		<td>
			<a href="http://www.amazon.com/exec/obidos/ASIN/<%= amazonRankings.getISBN() %>" target="_blank">
			<img border="0" src="<%= amazonRankings.getSmallImageURL() %>" />
			</a>
		</td>
		<td>
			<span style="font-size: xx-small;">
			<liferay-ui:message key="title" />: <%= StringUtil.shorten(amazonRankings.getProductName(), _DESCRIPTION_LENGTH) %><br />
			<liferay-ui:message key="author" />: <%= StringUtil.shorten(StringUtil.merge(amazonRankings.getAuthors(), ", "), _DESCRIPTION_LENGTH) %><br />
			<liferay-ui:message key="publisher" />: <%= StringUtil.shorten(amazonRankings.getManufacturer() + "; (" + amazonRankings.getReleaseDateAsString() + ")", _DESCRIPTION_LENGTH) %><br />
			<liferay-ui:message key="isbn" />: <%= amazonRankings.getISBN() %><br />
			<liferay-ui:message key="rank" />: <%= numberFormat.format(amazonRankings.getSalesRank()) %>
			</span>
		</td>
	</tr>

	<c:if test="<%= itr.hasNext() %>">
		<tr>
			<td>
				<br />
			</td>
		</tr>
	</c:if>

<%
}
%>

</table>

<%!
private static final int _DESCRIPTION_LENGTH = 16;
%>