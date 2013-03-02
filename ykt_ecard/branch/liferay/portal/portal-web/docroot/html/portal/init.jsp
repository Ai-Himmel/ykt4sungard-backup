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

<%@ page import="com.liferay.documentlibrary.NoSuchFileException" %>
<%@ page import="com.liferay.portal.CookieNotSupportedException" %>
<%@ page import="com.liferay.portal.LayoutFriendlyURLException" %>
<%@ page import="com.liferay.portal.LayoutHiddenException" %>
<%@ page import="com.liferay.portal.LayoutNameException" %>
<%@ page import="com.liferay.portal.LayoutParentLayoutIdException" %>
<%@ page import="com.liferay.portal.LayoutPermissionException" %>
<%@ page import="com.liferay.portal.LayoutTypeException" %>
<%@ page import="com.liferay.portal.NoSuchGroupException" %>
<%@ page import="com.liferay.portal.NoSuchImageException" %>
<%@ page import="com.liferay.portal.NoSuchLayoutException" %>
<%@ page import="com.liferay.portal.NoSuchLayoutSetException" %>
<%@ page import="com.liferay.portal.NoSuchResourceException" %>
<%@ page import="com.liferay.portal.NoSuchUserException" %>
<%@ page import="com.liferay.portal.PasswordExpiredException" %>
<%@ page import="com.liferay.portal.PortletActiveException" %>
<%@ page import="com.liferay.portal.RequiredLayoutException" %>
<%@ page import="com.liferay.portal.RequiredRoleException" %>
<%@ page import="com.liferay.portal.SendPasswordException" %>
<%@ page import="com.liferay.portal.UserActiveException" %>
<%@ page import="com.liferay.portal.UserEmailAddressException" %>
<%@ page import="com.liferay.portal.UserLockoutException" %>
<%@ page import="com.liferay.portal.UserPasswordException" %>
<%@ page import="com.liferay.portal.UserScreenNameException" %>
<%@ page import="com.liferay.portal.action.LoginAction" %>
<%@ page import="com.liferay.portal.security.auth.AuthException" %>
<%@ page import="com.liferay.portal.service.impl.ThemeLocalUtil" %>
<%@ page import="com.liferay.portal.service.permission.GroupPermissionUtil" %>
<%@ page import="com.liferay.portal.service.permission.OrganizationPermissionUtil" %>
<%@ page import="com.liferay.portal.struts.PortletRequestProcessor" %>
<%@ page import="com.liferay.portal.util.LayoutLister" %>
<%@ page import="com.liferay.portal.util.LayoutView" %>
<%@ page import="com.liferay.portal.util.OpenIdUtil" %>
<%@ page import="com.liferay.portlet.documentlibrary.NoSuchFileEntryException" %>
<%@ page import="com.liferay.portlet.journal.TransformException" %>
<%@ page import="com.liferay.portlet.journalcontent.util.JournalContentUtil" %>
<%@ page import="com.liferay.portlet.layoutconfiguration.util.RuntimePortletUtil" %>
<%@ page import="com.liferay.util.servlet.fileupload.LiferayFileUpload" %>

<%@ page import="org.apache.struts.action.ActionMapping" %>
<%@ page import="org.apache.struts.taglib.tiles.ComponentConstants" %>
<%@ page import="org.apache.struts.tiles.ComponentDefinition" %>
<%@ page import="org.apache.struts.tiles.TilesUtil" %>

<%@ page import="org.openid4java.association.AssociationException" %>
<%@ page import="org.openid4java.consumer.ConsumerException" %>
<%@ page import="org.openid4java.discovery.DiscoveryException" %>
<%@ page import="org.openid4java.message.MessageException" %>

<%@page import="com.liferay.portal.captcha.CaptchaTextException"%>