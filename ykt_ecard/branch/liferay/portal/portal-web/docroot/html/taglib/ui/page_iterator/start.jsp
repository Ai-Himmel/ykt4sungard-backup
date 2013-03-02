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

<%
String formName = namespace + request.getAttribute("liferay-ui:page-iterator:formName");
String curParam = (String)request.getAttribute("liferay-ui:page-iterator:curParam");
int curValue = GetterUtil.getInteger((String)request.getAttribute("liferay-ui:page-iterator:curValue"));
int delta = GetterUtil.getInteger((String)request.getAttribute("liferay-ui:page-iterator:delta"));
String jsCall = (String)request.getAttribute("liferay-ui:page-iterator:jsCall");
int maxPages = GetterUtil.getInteger((String)request.getAttribute("liferay-ui:page-iterator:maxPages"));
String target = (String)request.getAttribute("liferay-ui:page-iterator:target");
int total = GetterUtil.getInteger((String)request.getAttribute("liferay-ui:page-iterator:total"));
String type = (String)request.getAttribute("liferay-ui:page-iterator:type");
String url = (String)request.getAttribute("liferay-ui:page-iterator:url");
String urlAnchor = (String)request.getAttribute("liferay-ui:page-iterator:urlAnchor");
int pages = GetterUtil.getInteger((String)request.getAttribute("liferay-ui:page-iterator:pages"));

int start = (curValue - 1) * delta;
int end = curValue * delta;

if (end > total) {
	end = total;
}

int resultRowsSize = delta;

if (total < delta) {
	resultRowsSize = total;
}
else {
	resultRowsSize = total - ((curValue - 1) * delta);

	if (resultRowsSize > delta) {
		resultRowsSize = delta;
	}
}

NumberFormat numberFormat = NumberFormat.getNumberInstance(locale);
%>

<c:if test='<%= type.equals("regular") %>'>
	<script type="text/javascript">
		function <%= namespace %>submitPageIterator() {
			var curValue = jQuery("option:selected", this).val();

			if (<%= Validator.isNotNull(url) %>) {
				var href = "<%= url + curParam %>" + "=" + curValue + "<%= urlAnchor %>";

				self.location = href;
			}
			else {
				document.<%= formName %>.<%= curParam %>.value = curValue;

				<%= jsCall %>;
			}
		}

		jQuery(
			function() {
				jQuery('.<%= namespace %>pageIteratorValue').change(<%= namespace %>submitPageIterator);
			}
		);
	</script>
</c:if>

<div class="taglib-page-iterator">
	<c:if test='<%= type.equals("regular") %>'>
		<div class="search-results">
			<c:choose>
				<c:when test="<%= total > resultRowsSize %>">
					<%= LanguageUtil.format(pageContext, "showing-x-x-of-x-results", new Object[] {numberFormat.format(start + 1), numberFormat.format(end), numberFormat.format(total)}) %>
				</c:when>
				<c:otherwise>
					<c:choose>
						<c:when test="<%= total != 1 %>">
							<%= LanguageUtil.format(pageContext, "showing-x-results", numberFormat.format(total)) %>
						</c:when>
						<c:otherwise>
							<%= LanguageUtil.format(pageContext, "showing-x-result", numberFormat.format(total)) %>
						</c:otherwise>
					</c:choose>
				</c:otherwise>
			</c:choose>
		</div>
	</c:if>

	<c:if test='<%= type.equals("article") %>'>
		<div class="search-results">
			<c:if test="<%= total > resultRowsSize %>">
				<liferay-ui:message key="pages" />:

				<%
				int pagesIteratorMax = maxPages;
				int pagesIteratorBegin = 1;
				int pagesIteratorEnd = pages;

				if (pages > pagesIteratorMax) {
					pagesIteratorBegin = curValue - pagesIteratorMax;
					pagesIteratorEnd = curValue + pagesIteratorMax;

					if (pagesIteratorBegin < 1) {
						pagesIteratorBegin = 1;
					}

					if (pagesIteratorEnd > pages) {
						pagesIteratorEnd = pages;
					}
				}

				StringMaker sm = new StringMaker();

				for (int i = pagesIteratorBegin; i <= pagesIteratorEnd; i++) {
					if (i == curValue) {
						sm.append("<b class='journal-article-page-number'>");
					}
					else {
						sm.append("<a class='journal-article-page-number' href='");
						sm.append(_getHREF(formName, curParam, i, jsCall, url, urlAnchor));
						sm.append("'>");
					}

					sm.append(i);

					if (i == curValue) {
						sm.append("</b>");
					}
					else {
						sm.append("</a>");
					}

					sm.append("&nbsp;&nbsp;");
				}
				%>

				<%= sm.toString() %>
			</c:if>
		</div>
	</c:if>

	<c:if test="<%= total > delta %>">
		<div class="search-pages">
			<c:if test='<%= type.equals("regular") %>'>
				<div class="page-selector">
					<liferay-ui:message key="page" />

					<select class="pages <%= namespace %>pageIteratorValue">

						<%
						int pagesIteratorMax = maxPages;
						int pagesIteratorBegin = 1;
						int pagesIteratorEnd = pages;

						if (pages > pagesIteratorMax) {
							pagesIteratorBegin = curValue - pagesIteratorMax;
							pagesIteratorEnd = curValue + pagesIteratorMax;

							if (pagesIteratorBegin < 1) {
								pagesIteratorBegin = 1;
							}

							if (pagesIteratorEnd > pages) {
								pagesIteratorEnd = pages;
							}
						}

						for (int i = pagesIteratorBegin; i <= pagesIteratorEnd; i++) {
						%>

							<option <%= (i == curValue) ? "selected=\"selected\"" : "" %> value="<%= i %>"><%= i %></option>

						<%
						}
						%>

					</select>

					<liferay-ui:message key="of" />

					<%= numberFormat.format(pages) %>

					<%--<input class="page-iterator-submit" type="submit" value="<liferay-ui:message key="submit" />" />--%>
				</div>
			</c:if>

			<div class="page-links">
				<c:if test='<%= type.equals("regular") %>'>
					<c:choose>
						<c:when test="<%= curValue != 1 %>">
							<a class="first" href="<%= _getHREF(formName, curParam, 1, jsCall, url, urlAnchor) %>" target="<%= target %>">
						</c:when>
						<c:otherwise>
							<span class="first">
						</c:otherwise>
					</c:choose>

					<liferay-ui:message key="first" />

					<c:choose>
						<c:when test="<%= curValue != 1 %>">
							</a>
						</c:when>
						<c:otherwise>
							</span>
						</c:otherwise>
					</c:choose>
				</c:if>

				<c:choose>
					<c:when test="<%= curValue != 1 %>">
						<a class="previous" href="<%= _getHREF(formName, curParam, curValue - 1, jsCall, url, urlAnchor) %>" target="<%= target %>">
					</c:when>
					<c:when test='<%= type.equals("regular") %>'>
						<span class="previous">
					</c:when>
				</c:choose>

				<c:if test='<%= (type.equals("regular") || curValue != 1) %>'>
					<liferay-ui:message key="previous" />
				</c:if>

				<c:choose>
					<c:when test="<%= curValue != 1 %>">
						</a>
					</c:when>
					<c:when test='<%= type.equals("regular") %>'>
						</span>
					</c:when>
				</c:choose>

				<c:choose>
					<c:when test="<%= curValue != pages %>">
						<a class="next" href="<%= _getHREF(formName, curParam, curValue + 1, jsCall, url, urlAnchor) %>" target="<%= target %>">
					</c:when>
					<c:when test='<%= type.equals("regular") %>'>
						<span class="next">
					</c:when>
				</c:choose>

				<c:if test='<%= (type.equals("regular") || curValue != pages) %>'>
					<liferay-ui:message key="next" />
				</c:if>

				<c:choose>
					<c:when test="<%= curValue != pages %>">
						</a>
					</c:when>
					<c:when test='<%= type.equals("regular") %>'>
						</span>
					</c:when>
				</c:choose>

				<c:if test='<%= type.equals("regular") %>'>
					<c:choose>
						<c:when test="<%= curValue != pages %>">
							<a class="last" href="<%= _getHREF(formName, curParam, pages, jsCall, url, urlAnchor) %>" target="<%= target %>">
						</c:when>
						<c:otherwise>
							<span class="last">
						</c:otherwise>
					</c:choose>

					<liferay-ui:message key="last" />

					<c:choose>
						<c:when test="<%= curValue != pages %>">
							</a>
						</c:when>
						<c:otherwise>
							</span>
						</c:otherwise>
					</c:choose>
				</c:if>
			</div>
		</div>
	</c:if>
</div>

<%!
private String _getHREF(String formName, String curParam, int curValue, String jsCall, String url, String urlAnchor) throws Exception {
	String href = null;

	if (Validator.isNotNull(url)) {
		href = url + curParam + "=" + curValue + urlAnchor;
	}
	else {
		href = "javascript: document." + formName + "." + curParam + ".value = '" + curValue + "'; " + jsCall;
	}

	return href;
}
%>