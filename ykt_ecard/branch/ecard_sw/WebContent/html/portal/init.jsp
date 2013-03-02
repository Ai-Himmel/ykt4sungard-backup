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
%><%--

--%><%@ include file="/html/common/init.jsp" %><%--

--%><%@ page import="com.liferay.portal.LayoutFriendlyURLException" %><%--
--%><%@ page import="com.liferay.portal.LayoutNameException" %><%--
--%><%@ page import="com.liferay.portal.LayoutTypeException" %><%--
--%><%@ page import="com.liferay.portal.NoSuchUserException" %><%--
--%><%@ page import="com.liferay.portal.PortletActiveException" %><%--
--%><%@ page import="com.liferay.portal.RequiredLayoutException" %><%--
--%><%@ page import="com.liferay.portal.RequiredRoleException" %><%--
--%><%@ page import="com.liferay.portal.SendPasswordException" %><%--
--%><%@ page import="com.liferay.portal.UserActiveException" %><%--
--%><%@ page import="com.liferay.portal.UserEmailAddressException" %><%--
--%><%@ page import="com.liferay.portal.UserPasswordException" %><%--
--%><%@ page import="com.liferay.portal.UserIdException" %><%--
--%><%@ page import="com.liferay.portal.action.LoginAction" %><%--
--%><%@ page import="com.liferay.portal.auth.AuthException" %><%--
--%><%@ page import="com.liferay.portal.struts.PortletRequestProcessor" %><%--
--%><%@ page import="com.liferay.portal.util.LayoutLister" %><%--
--%><%@ page import="com.liferay.portal.util.LayoutView" %><%--
--%><%@ page import="com.liferay.portal.util.PortletTitleComparator" %><%--
--%><%@ page import="com.liferay.util.servlet.fileupload.LiferayFileUpload" %><%--

--%><%@ page import="org.apache.struts.action.ActionMapping" %><%--
--%><%@ page import="org.apache.struts.taglib.tiles.ComponentConstants" %><%--
--%><%@ page import="org.apache.struts.tiles.ComponentDefinition" %><%--
--%><%@ page import="org.apache.struts.tiles.TilesUtil" %>
<%@ page import="com.kingstargroup.ecard.exceptions.ValidAuthCodeException" %>