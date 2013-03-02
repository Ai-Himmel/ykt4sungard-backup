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

<%@ include file="/html/taglib/ui/tabs/init.jsp" %>

<%

// URL

LiferayPortletURL portletURL = (LiferayPortletURL)request.getAttribute("liferay-ui:tabs:portletURL");

String url = GetterUtil.getString((String)request.getAttribute("liferay-ui:tabs:url"));
String anchor = StringPool.BLANK;

if (url != null) {

	// Strip existing tab parameter and value from the URL

	int x = url.indexOf(param + "=");

	if (x != -1) {
		x = url.lastIndexOf("&", x);

		if (x == -1) {
			x = url.lastIndexOf("?", x);
		}

		int y = url.indexOf("&", x + 1);

		if (y == -1) {
			y = url.length();
		}

		url = url.substring(0, x) + url.substring(y, url.length());
	}

	// Strip training &

	if (url.endsWith("&")) {
		url = url.substring(0, url.length() - 1);
	}

	// Strip anchor

	x = url.indexOf("&#");

	if (x != -1) {
		url = url.substring(0, x);
		anchor = url.substring(x, url.length());
	}
}

// Back url

String backURL = (String)request.getAttribute("liferay-ui:tabs:backURL");

// Refresh

boolean refresh = GetterUtil.getBoolean((String)request.getAttribute("liferay-ui:tabs:refresh"));

// onClick

String onClick = GetterUtil.getString((String)request.getAttribute("liferay-ui:tabs:onClick"));
%>

<c:if test="<%= names.length > 0 %>">

	<%
	String oldPortletURLValue = null;

	if (portletURL != null) {
		oldPortletURLValue = portletURL.getParameter(param);
	}
	%>

	<input name="<%= namespace %><%= param %>TabsScroll" type="hidden" />

	<ul class="tabs">

		<%
		for (int i = 0; i < values.length; i++) {
			String curURL = (String)request.getAttribute("liferay-ui:tabs:url" + i);

			if (Validator.isNull(curURL)) {
				if (values.length == 1) {
					if (Validator.isNotNull(backURL)) {
						curURL = backURL;
					}
				}
				else {
					if (refresh) {
						if (portletURL != null) {
							portletURL.setParameter(param, values[i]);

							curURL = portletURL.toString();
						}
						else {
							if (values[i].equals("&raquo;")) {
								curURL = url + "&" + param + "=" + values[0] + anchor;
							}
							else {
								curURL = url + "&" + param + "=" + values[i] + anchor;
							}
						}
					}
					else {
						curURL = "javascript: ";

						if (Validator.isNotNull(formName)) {
							curURL += "document." + namespace + formName + "." + namespace + param + ".value = '" + names[i] + "';";
						}

						curURL += "Tabs.show('" + namespace + param + "', " + namesJS + ", '" + names[i] + "');";
					}
				}
			}

			String curOnClick = StringPool.BLANK;

			if (Validator.isNotNull(onClick)) {
				curOnClick = onClick + "('" + curURL + "', '" + values[i] + "'); return false;";
			}
		%>

			<li <%= (values.length == 1) || value.equals(values[i]) ? "class=\"current\"" : "" %> id="<%= namespace %><%= param %><%= values[i] %>TabsId">
				<c:choose>
					<c:when test="<%= Validator.isNotNull(curURL) %>">
						<a href="<%= curURL %>"
							<c:if test="<%= Validator.isNotNull(curOnClick) %>">
								onClick="<%= curOnClick %>"
							</c:if>
						>
					</c:when>
					<c:otherwise>
						<span>
					</c:otherwise>
				</c:choose>

				<%= LanguageUtil.get(pageContext, names[i]) %>

				<c:choose>
					<c:when test="<%= Validator.isNotNull(curURL) %>">
						</a>
					</c:when>
					<c:otherwise>
						</span>
					</c:otherwise>
				</c:choose>
			</li>

		<%
		}
		%>

		<c:if test="<%= Validator.isNotNull(backURL) %>">
			<li class="toggle">
				<a href="<%= backURL %>">&laquo; <liferay-ui:message key="back" /></a>
			</li>
		</c:if>
	</ul>

	<%
	if (portletURL != null) {
		portletURL.setParameter(param, oldPortletURLValue);
	}
	%>

</c:if>