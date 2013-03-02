<%
/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

<%
boolean ROUNDED_TOP = true;
boolean ROUNDED_BOTTOM = false;
%>

<%--
java.util.Properties settingsProperties = colorScheme.getSettingsProperties();

settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.BODY_BG, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.LAYOUT_BG, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.LAYOUT_TEXT, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.LAYOUT_TAB_BG, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.LAYOUT_TAB_TEXT, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.LAYOUT_TAB_SELECTED_BG, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.LAYOUT_TAB_SELECTED_TEXT, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_TITLE_BG, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_TITLE_TEXT, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_MENU_BG, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_MENU_TEXT, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_BG, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_FONT, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_FONT_DIM, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_MSG_STATUS, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_MSG_INFO, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_MSG_ERROR, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_MSG_ALERT, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_MSG_SUCCESS, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_SECTION_HEADER, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_SECTION_HEADER_BG, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_SECTION_SUBHEADER, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_SECTION_SUBHEADER_BG, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_SECTION_BODY, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_SECTION_BODY_BG, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_SECTION_BODY_HOVER, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_SECTION_BODY_HOVER_BG, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_SECTION_ALTERNATE, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_SECTION_ALTERNATE_BG, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_SECTION_ALTERNATE_HOVER, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_SECTION_ALTERNATE_HOVER_BG, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_SECTION_SELECTED, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_SECTION_SELECTED_BG, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_SECTION_SELECTED_HOVER, "#000000");
settingsProperties.setProperty(com.liferay.portal.model.ColorScheme.PORTLET_SECTION_SELECTED_HOVER_BG, "#000000");

colorScheme.setSettingsProperties(settingsProperties);
--%>