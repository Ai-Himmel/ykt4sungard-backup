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

<%@ include file="/html/common/init.jsp" %>

<c:if test="<%= themeDisplay.isIncludeCalendarJs() %>">
	<link href="<%= themeDisplay.getPathJavaScript() %>/calendar/skins/aqua/theme.css" rel="stylesheet" type="text/css" />

	<script src="<%= themeDisplay.getPathJavaScript() %>/calendar/calendar_stripped.js" type="text/javascript"></script>

	<script type="text/javascript">

		<%
		String[] calendarDays = CalendarUtil.getDays(locale, "EEEE");
		%>

		Calendar._DN = new Array(
			"<%= calendarDays[0] %>",
			"<%= calendarDays[1] %>",
			"<%= calendarDays[2] %>",
			"<%= calendarDays[3] %>",
			"<%= calendarDays[4] %>",
			"<%= calendarDays[5] %>",
			"<%= calendarDays[6] %>",
			"<%= calendarDays[0] %>"
		);

		<%
		calendarDays = CalendarUtil.getDays(locale, "EEE");
		%>

		Calendar._SDN = new Array(
			"<%= calendarDays[0] %>",
			"<%= calendarDays[1] %>",
			"<%= calendarDays[2] %>",
			"<%= calendarDays[3] %>",
			"<%= calendarDays[4] %>",
			"<%= calendarDays[5] %>",
			"<%= calendarDays[6] %>",
			"<%= calendarDays[0] %>"
		);

		<%
		String[] calendarMonths = CalendarUtil.getMonths(locale);
		%>

		Calendar._MN = new Array(
			"<%= calendarMonths[0] %>",
			"<%= calendarMonths[1] %>",
			"<%= calendarMonths[2] %>",
			"<%= calendarMonths[3] %>",
			"<%= calendarMonths[4] %>",
			"<%= calendarMonths[5] %>",
			"<%= calendarMonths[6] %>",
			"<%= calendarMonths[7] %>",
			"<%= calendarMonths[8] %>",
			"<%= calendarMonths[9] %>",
			"<%= calendarMonths[10] %>",
			"<%= calendarMonths[11] %>"
		);

		<%
		calendarMonths = CalendarUtil.getMonths(locale, "MMM");
		%>

		Calendar._SMN = new Array(
			"<%= calendarMonths[0] %>",
			"<%= calendarMonths[1] %>",
			"<%= calendarMonths[2] %>",
			"<%= calendarMonths[3] %>",
			"<%= calendarMonths[4] %>",
			"<%= calendarMonths[5] %>",
			"<%= calendarMonths[6] %>",
			"<%= calendarMonths[7] %>",
			"<%= calendarMonths[8] %>",
			"<%= calendarMonths[9] %>",
			"<%= calendarMonths[10] %>",
			"<%= calendarMonths[11] %>"
		);

		Calendar._TT = {};

		Calendar._TT["ABOUT"] = "<liferay-ui:message key="date-selection" />";
		Calendar._TT["ABOUT"] = Calendar._TT["ABOUT"].replace("{0}", String.fromCharCode(0x2039));
		Calendar._TT["ABOUT"] = Calendar._TT["ABOUT"].replace("{1}", String.fromCharCode(0x203a));

		Calendar._TT["ABOUT_TIME"] = "";
		Calendar._TT["CLOSE"] = "<liferay-ui:message key="close" />";
		Calendar._TT["DAY_FIRST"] = "Display %s First";
		Calendar._TT["DRAG_TO_MOVE"] = "";
		Calendar._TT["GO_TODAY"] = "<liferay-ui:message key="today" />";
		Calendar._TT["INFO"] = "<liferay-ui:message key="help" />";
		Calendar._TT["NEXT_MONTH"] = "<liferay-ui:message key="next-month" />";
		Calendar._TT["NEXT_YEAR"] = "<liferay-ui:message key="next-year" />";
		Calendar._TT["PART_TODAY"] = "";
		Calendar._TT["PREV_MONTH"] = "<liferay-ui:message key="previous-month" />";
		Calendar._TT["PREV_YEAR"] = "<liferay-ui:message key="previous-year" />";
		Calendar._TT["SEL_DATE"] = "<liferay-ui:message key="select-date" />";
		Calendar._TT["SUN_FIRST"] = "";
		Calendar._TT["TIME_PART"] = "";
		Calendar._TT["TODAY"] = "<liferay-ui:message key="today" />";
		Calendar._TT["WK"] = "";

		Calendar._TT["DEF_DATE_FORMAT"] = "%Y-%m-%d";
		Calendar._TT["TT_DATE_FORMAT"] = "%a, %b %e";

		Calendar._TT["WEEKEND"] = "0,6";
	</script>
</c:if>

<c:if test="<%= themeDisplay.isIncludePortletCssJs() %>">
	<script src="<%= themeDisplay.getPathJavaScript() %>/liferay/portlet_css_packed.js" type="text/javascript"></script>
</c:if>

<%
List portlets = null;

if ((layout != null) && layout.getType().equals(LayoutImpl.TYPE_PORTLET)) {
	portlets = layoutTypePortlet.getPortlets();
}
%>

<c:if test="<%= portlets != null %>">

	<%
	Set footerPortalCssPaths = new LinkedHashSet();

	for (int i = 0; i < portlets.size(); i++) {
		Portlet portlet = (Portlet)portlets.get(i);

		List footerPortalCssList = portlet.getFooterPortalCss();

		for (int j = 0; j < footerPortalCssList.size(); j++) {
			String footerPortalCss = (String)footerPortalCssList.get(j);

			String footerPortalCssPath = request.getContextPath() + footerPortalCss;

			if (!footerPortalCssPaths.contains(footerPortalCssPath) && !themeDisplay.isIncludedJs(footerPortalCssPath)) {
				footerPortalCssPaths.add(footerPortalCssPath);
	%>

				<link href="<%= footerPortalCssPath %>" rel="stylesheet" type="text/css" />

	<%
			}
		}
	}

	Set footerPortletCssPaths = new LinkedHashSet();

	for (int i = 0; i < portlets.size(); i++) {
		Portlet portlet = (Portlet)portlets.get(i);

		List footerPortletCssList = portlet.getFooterPortletCss();

		for (int j = 0; j < footerPortletCssList.size(); j++) {
			String footerPortletCss = (String)footerPortletCssList.get(j);

			String footerPortletCssPath = portlet.getContextPath() + footerPortletCss;

			if (!footerPortletCssPaths.contains(footerPortletCssPath)) {
				footerPortletCssPaths.add(footerPortletCssPath);

				if (footerPortletCssPath.endsWith(".jsp")) {
					footerPortletCssPath += "?themeId=" + themeDisplay.getTheme().getThemeId() + "&amp;colorSchemeId=" + themeDisplay.getColorScheme().getColorSchemeId() + "&amp;t=" + theme.getTimestamp();
				}
	%>

				<link href="<%= footerPortletCssPath %>" rel="stylesheet" type="text/css" />

	<%
			}
		}
	}

	Set footerPortalJavaScriptPaths = new LinkedHashSet();

	for (int i = 0; i < portlets.size(); i++) {
		Portlet portlet = (Portlet)portlets.get(i);

		List footerPortalJavaScriptList = portlet.getFooterPortalJavaScript();

		for (int j = 0; j < footerPortalJavaScriptList.size(); j++) {
			String footerPortalJavaScript = (String)footerPortalJavaScriptList.get(j);

			String footerPortalJavaScriptPath = request.getContextPath() + footerPortalJavaScript;

			if (!footerPortalJavaScriptPaths.contains(footerPortalJavaScriptPath)) {
				footerPortalJavaScriptPaths.add(footerPortalJavaScriptPath);
	%>

				<script src="<%= footerPortalJavaScriptPath %>" type="text/javascript"></script>

	<%
			}
		}
	}

	Set footerPortletJavaScriptPaths = new LinkedHashSet();

	for (int i = 0; i < portlets.size(); i++) {
		Portlet portlet = (Portlet)portlets.get(i);

		List footerPortletJavaScriptList = portlet.getFooterPortletJavaScript();

		for (int j = 0; j < footerPortletJavaScriptList.size(); j++) {
			String footerPortletJavaScript = (String)footerPortletJavaScriptList.get(j);

			String footerPortletJavaScriptPath = portlet.getContextPath() + footerPortletJavaScript;

			if (!footerPortletJavaScriptPaths.contains(footerPortletJavaScriptPath)) {
				footerPortletJavaScriptPaths.add(footerPortletJavaScriptPath);
	%>

				<script src="<%= footerPortletJavaScriptPath %>" type="text/javascript"></script>

	<%
			}
		}
	}
	%>

</c:if>

<%
if (layout != null) {
	Properties groupTypeSettings = layout.getGroup().getTypeSettingsProperties();

	String googleAnalyticsId = groupTypeSettings.getProperty("googleAnalyticsId");

	if (Validator.isNotNull(googleAnalyticsId)) {
%>

		<%--<script src="<%= themeDisplay.getPathJavaScript() %>/google/urchin.js" type="text/javascript"></script>

		<script type="text/javascript">
			_uacct = "<%= googleAnalyticsId %>";
			urchinTracker();
		</script>--%>

		<script type="text/javascript">
			var gaJsHost = (("https:" == document.location.protocol) ? "https://ssl." : "http://www.");

			document.write(unescape("%3Cscript src='" + gaJsHost + "google-analytics.com/ga.js' type='text/javascript'%3E%3C/script%3E"));
		</script>

		<script type="text/javascript">
			var pageTracker = _gat._getTracker("<%= googleAnalyticsId %>");

			pageTracker._initData();
			pageTracker._trackPageview();
		</script>

<%
	}
}
%>

<c:if test="<%= PropsValues.WEB_SERVER_DISPLAY_NODE %>">
	<div class="portlet-msg-info">
		<liferay-ui:message key="node" />: <%= PortalUtil.getComputerName() %>
	</div>
</c:if>

<form method="post" name="hrefFm"></form>

<liferay-util:include page="/html/common/themes/bottom-ext.jsp" />