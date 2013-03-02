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

<%@ page import="com.liferay.taglib.ui.LanguageTag" %>

<%
String formName = namespace + request.getAttribute("liferay-ui:language:formName");

String formAction = (String)request.getAttribute("liferay-ui:language:formAction");

if (Validator.isNull(formAction)) {
	PortletURLImpl portletURLImpl = new PortletURLImpl(request, PortletKeys.LANGUAGE, plid.longValue(), true);

	portletURLImpl.setWindowState(WindowState.NORMAL);
	portletURLImpl.setPortletMode(PortletMode.VIEW);
	portletURLImpl.setAnchor(false);

	portletURLImpl.setParameter("struts_action", "/language/view");
	portletURLImpl.setParameter("redirect", currentURL);

	formAction = portletURLImpl.toString();
}

String name = (String)request.getAttribute("liferay-ui:language:name");
Locale[] locales = (Locale[])request.getAttribute("liferay-ui:language:locales");
int displayStyle = GetterUtil.getInteger((String)request.getAttribute("liferay-ui:language:displayStyle"));

Map langCounts = CollectionFactory.getHashMap();

for (int i = 0; i < locales.length; i++) {
	Integer count = (Integer)langCounts.get(locales[i].getLanguage());

	if (count == null) {
		count = new Integer(1);
	}
	else {
		count = new Integer(count.intValue() + 1);
	}

	langCounts.put(locales[i].getLanguage(), count);
}

Set duplicateLanguages = CollectionFactory.getHashSet();

for (int i = 0; i < locales.length; i++) {
	Integer count = (Integer)langCounts.get(locales[i].getLanguage());

	if (count.intValue() != 1) {
		duplicateLanguages.add(locales[i].getLanguage());
	}
}
%>

<c:choose>
	<c:when test="<%= displayStyle == LanguageTag.SELECT_BOX %>">
		<form action="<%= formAction %>" method="post" name="<%= formName %>">

		<select name="<%= namespace + name %>" onChange="submitForm(document.<%= formName %>);">

			<%
			for (int i = 0; i < locales.length; i++) {
			%>

				<option <%= (locale.getLanguage().equals(locales[i].getLanguage()) && locale.getCountry().equals(locales[i].getCountry())) ? "selected" : "" %> style="padding-left: 26px; margin: 1px 1px 1px 1px;" value="<%= locales[i].getLanguage() + "_" + locales[i].getCountry() %>"><%= locales[i].getDisplayName(locales[i]) %></option>

			<%
			}
			%>

		</select>

		</form>

		<script type="text/javascript">

			<%
			for (int i = 0; i < locales.length; i++) {
			%>

				document.<%= formName %>.<%= namespace + name %>.options[<%= i %>].style.backgroundImage = "url(<%= themeDisplay.getPathThemeImages() %>/language/<%= LocaleUtil.toLanguageId(locales[i]) %>.png)";
				document.<%= formName %>.<%= namespace + name %>.options[<%= i %>].style.backgroundRepeat = "no-repeat";
				document.<%= formName %>.<%= namespace + name %>.options[<%= i %>].style.backgroundPosition = "center left";

			<%
			}
			%>

		</script>
	</c:when>
	<c:otherwise>

		<%
		for (int i = 0; i < locales.length; i++) {
			String language = locales[i].getDisplayLanguage(locales[i]);
			String country = locales[i].getDisplayCountry(locales[i]);

			if (displayStyle == LanguageTag.LIST_SHORT_TEXT) {
				if (language.length() > 3) {
					language = locales[i].getLanguage().toUpperCase();
				}

				country = locales[i].getCountry().toUpperCase();
			}
		%>

			<c:choose>
				<c:when test="<%= (displayStyle == LanguageTag.LIST_LONG_TEXT) || (displayStyle == LanguageTag.LIST_SHORT_TEXT) %>">
					<a href="<%= formAction %>&<%= name %>=<%= locales[i].getLanguage() + "_" + locales[i].getCountry() %>">
						<%= language %>

						<c:if test="<%= duplicateLanguages.contains(locales[i].getLanguage()) %>">
							(<%= country %>)
						</c:if>
					</a>

					<c:if test="<%= i + 1 < locales.length %>">
						|
					</c:if>
				</c:when>
				<c:otherwise>
					<a href="<%= formAction %>&<%= name %>=<%= locales[i].getLanguage() + "_" + locales[i].getCountry() %>">
					<img border="0" src="<%= themeDisplay.getPathThemeImages() %>/language/<%= LocaleUtil.toLanguageId(locales[i]) %>.png" alt="<%= locales[i].getDisplayName(locales[i]) %>" title="<%= locales[i].getDisplayName(locales[i]) %>" /></a>
				</c:otherwise>
			</c:choose>

		<%
		}
		%>

	</c:otherwise>
</c:choose>