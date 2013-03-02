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

<%@ include file="/html/portlet/init.jsp" %>

<%@ page import="com.liferay.portal.DuplicateUserEmailAddressException" %>
<%@ page import="com.liferay.portal.UserEmailAddressException" %>
<%@ page import="com.liferay.portlet.mail.ContentException" %>
<%@ page import="com.liferay.portlet.mail.RecipientException" %>
<%@ page import="com.liferay.portlet.mail.model.MailEnvelope" %>
<%@ page import="com.liferay.portlet.mail.model.MailFolder" %>
<%@ page import="com.liferay.portlet.mail.model.MailMessage" %>
<%@ page import="com.liferay.portlet.mail.model.RemoteMailAttachment" %>
<%@ page import="com.liferay.portlet.mail.search.MailDisplayTerms" %>
<%@ page import="com.liferay.portlet.mail.util.MailUtil" %>
<%@ page import="com.liferay.portlet.mail.util.comparator.DateComparator" %>
<%@ page import="com.liferay.portlet.mail.util.recipient.RecipientFinder" %>
<%@ page import="com.liferay.portlet.mail.util.recipient.RecipientFinderLocator" %>
<%@ page import="com.liferay.util.mail.MailServerException" %>

<%@ page import="javax.mail.Address" %>

<%@ page import="org.apache.commons.collections.map.MultiValueMap" %>

<%
PortletPreferences prefs = renderRequest.getPreferences();

String forwardAddress = prefs.getValue("forward-address", StringPool.BLANK);
boolean leaveCopy = GetterUtil.getBoolean(prefs.getValue("leave-copy", StringPool.BLANK));
String signature = prefs.getValue("signature", StringPool.BLANK);
String vacationMessage = prefs.getValue("vacation-message", StringPool.BLANK);

DateFormat dateFormatDateTime = DateFormats.getDateTime(locale, timeZone);

MailUtil.setAccount(request);
%>