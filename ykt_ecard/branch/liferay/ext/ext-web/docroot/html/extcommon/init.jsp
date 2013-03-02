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

<%@ taglib uri="http://displaytag.sf.net" prefix="display" %>

<%@ taglib uri="http://java.sun.com/jstl/core_rt" prefix="c" %>
<%@ taglib uri="http://java.sun.com/jstl/fmt_rt" prefix="fmt" %>
<%@ taglib uri="http://java.sun.com/jstl/sql_rt" prefix="sql" %>
<%@ taglib uri="http://java.sun.com/jstl/xml_rt" prefix="x" %>

<%@ taglib uri="http://java.sun.com/portlet" prefix="portlet" %>

<%@ taglib uri="http://liferay.com/tld/portlet" prefix="liferay-portlet" %>
<%@ taglib uri="http://liferay.com/tld/security" prefix="liferay-security" %>
<%@ taglib uri="http://liferay.com/tld/theme" prefix="liferay-theme" %>
<%@ taglib uri="http://liferay.com/tld/ui" prefix="liferay-ui" %>
<%@ taglib uri="http://liferay.com/tld/util" prefix="liferay-util" %>

<%@ taglib uri="http://struts.apache.org/tags-bean" prefix="bean" %>
<%@ taglib uri="http://struts.apache.org/tags-bean-el" prefix="bean-el" %>
<%@ taglib uri="http://struts.apache.org/tags-html" prefix="html" %>
<%@ taglib uri="http://struts.apache.org/tags-html-el" prefix="html-el" %>
<%@ taglib uri="http://struts.apache.org/tags-logic" prefix="logic" %>
<%@ taglib uri="http://struts.apache.org/tags-logic-el" prefix="logic-el" %>
<%@ taglib uri="http://struts.apache.org/tags-nested" prefix="nested" %>
<%@ taglib uri="http://struts.apache.org/tags-tiles" prefix="tiles" %>
<%@ taglib uri="http://struts.apache.org/tags-tiles-el" prefix="tiles-el" %>

<%@ page import="com.germinus.easyconf.Filter" %>

<%@ page import="com.liferay.lock.DuplicateLockException" %>
<%@ page import="com.liferay.lock.model.Lock" %>
<%@ page import="com.liferay.lock.service.LockServiceUtil" %>
<%@ page import="com.liferay.portal.NoSuchUserException" %>
<%@ page import="com.liferay.portal.PortalException" %>
<%@ page import="com.liferay.portal.SystemException" %>
<%@ page import="com.liferay.portal.captcha.CaptchaTextException" %>
<%@ page import="com.liferay.portal.kernel.cal.Recurrence" %>
<%@ page import="com.liferay.portal.kernel.dao.DAOParamUtil" %>
<%@ page import="com.liferay.portal.kernel.dao.search.DisplayTerms" %>
<%@ page import="com.liferay.portal.kernel.dao.search.ResultRow" %>
<%@ page import="com.liferay.portal.kernel.dao.search.RowChecker" %>
<%@ page import="com.liferay.portal.kernel.dao.search.SearchContainer" %>
<%@ page import="com.liferay.portal.kernel.dao.search.SearchEntry" %>
<%@ page import="com.liferay.portal.kernel.dao.search.TextSearchEntry" %>
<%@ page import="com.liferay.portal.kernel.language.LanguageUtil" %>
<%@ page import="com.liferay.portal.kernel.language.LanguageWrapper" %>
<%@ page import="com.liferay.portal.kernel.language.UnicodeLanguageUtil" %>
<%@ page import="com.liferay.portal.kernel.log.Log" %>
<%@ page import="com.liferay.portal.kernel.log.LogFactoryUtil" %>
<%@ page import="com.liferay.portal.kernel.log.LogUtil" %>
<%@ page import="com.liferay.portal.kernel.portlet.DynamicRenderRequest" %>
<%@ page import="com.liferay.portal.kernel.portlet.LiferayPortletMode" %>
<%@ page import="com.liferay.portal.kernel.portlet.LiferayPortletURL" %>
<%@ page import="com.liferay.portal.kernel.portlet.LiferayWindowState" %>
<%@ page import="com.liferay.portal.kernel.security.permission.ActionKeys" %>
<%@ page import="com.liferay.portal.kernel.security.permission.PermissionChecker" %>
<%@ page import="com.liferay.portal.kernel.servlet.BrowserSniffer" %>
<%@ page import="com.liferay.portal.kernel.servlet.ImageServletTokenUtil" %>
<%@ page import="com.liferay.portal.kernel.servlet.StringServletResponse" %>
<%@ page import="com.liferay.portal.kernel.util.ArrayUtil" %>
<%@ page import="com.liferay.portal.kernel.util.BooleanWrapper" %>
<%@ page import="com.liferay.portal.kernel.util.CalendarFactoryUtil" %>
<%@ page import="com.liferay.portal.kernel.util.Constants" %>
<%@ page import="com.liferay.portal.kernel.util.ContentTypes" %>
<%@ page import="com.liferay.portal.kernel.util.DateUtil" %>
<%@ page import="com.liferay.portal.kernel.util.GetterUtil" %>
<%@ page import="com.liferay.portal.kernel.util.IntegerWrapper" %>
<%@ page import="com.liferay.portal.kernel.util.JavaConstants" %>
<%@ page import="com.liferay.portal.kernel.util.KeyValuePair" %>
<%@ page import="com.liferay.portal.kernel.util.KeyValuePairComparator" %>
<%@ page import="com.liferay.portal.kernel.util.LocaleUtil" %>
<%@ page import="com.liferay.portal.kernel.util.ObjectValuePair" %>
<%@ page import="com.liferay.portal.kernel.util.ObjectValuePairComparator" %>
<%@ page import="com.liferay.portal.kernel.util.OrderByComparator" %>
<%@ page import="com.liferay.portal.kernel.util.OrderedProperties" %>
<%@ page import="com.liferay.portal.kernel.util.ParamUtil" %>
<%@ page import="com.liferay.portal.kernel.util.PrefsParamUtil" %>
<%@ page import="com.liferay.portal.kernel.util.PropertiesParamUtil" %>
<%@ page import="com.liferay.portal.kernel.util.PropertiesUtil" %>
<%@ page import="com.liferay.portal.kernel.util.Randomizer" %>
<%@ page import="com.liferay.portal.kernel.util.ReleaseInfo" %>
<%@ page import="com.liferay.portal.kernel.util.ServerDetector" %>
<%@ page import="com.liferay.portal.kernel.util.SortedProperties" %>
<%@ page import="com.liferay.portal.kernel.util.StackTraceUtil" %>
<%@ page import="com.liferay.portal.kernel.util.StringComparator" %>
<%@ page import="com.liferay.portal.kernel.util.StringMaker" %>
<%@ page import="com.liferay.portal.kernel.util.StringPool" %>
<%@ page import="com.liferay.portal.kernel.util.StringUtil" %>
<%@ page import="com.liferay.portal.kernel.util.UnicodeFormatter" %>
<%@ page import="com.liferay.portal.kernel.util.Validator" %>
<%@ page import="com.liferay.portal.language.LanguageImpl" %>
<%@ page import="com.liferay.portal.lucene.LuceneFields" %>
<%@ page import="com.liferay.portal.model.*" %>
<%@ page import="com.liferay.portal.model.impl.*" %>
<%@ page import="com.liferay.portal.security.auth.PrincipalException" %>
<%@ page import="com.liferay.portal.service.*" %>
<%@ page import="com.liferay.portal.service.impl.LayoutTemplateLocalUtil" %>
<%@ page import="com.liferay.portal.service.permission.GroupPermissionUtil" %>
<%@ page import="com.liferay.portal.service.permission.LayoutPermissionUtil" %>
<%@ page import="com.liferay.portal.service.permission.PortletPermissionUtil" %>
<%@ page import="com.liferay.portal.struts.StrutsUtil" %>
<%@ page import="com.liferay.portal.theme.PortletDisplay" %>
<%@ page import="com.liferay.portal.theme.ThemeDisplay" %>
<%@ page import="com.liferay.portal.util.ContentUtil" %>
<%@ page import="com.liferay.portal.util.CookieKeys" %>
<%@ page import="com.liferay.portal.util.DateFormats" %>
<%@ page import="com.liferay.portal.util.PortalUtil" %>
<%@ page import="com.liferay.portal.util.PortletKeys" %>
<%@ page import="com.liferay.portal.util.PrefsPropsUtil" %>
<%@ page import="com.liferay.portal.util.PropsUtil" %>
<%@ page import="com.liferay.portal.util.PropsValues" %>
<%@ page import="com.liferay.portal.util.Recipient" %>
<%@ page import="com.liferay.portal.util.SessionClicks" %>
<%@ page import="com.liferay.portal.util.SessionTreeJSClicks" %>
<%@ page import="com.liferay.portal.util.ShutdownUtil" %>
<%@ page import="com.liferay.portal.util.WebAppPool" %>
<%@ page import="com.liferay.portal.util.WebKeys" %>
<%@ page import="com.liferay.portal.util.comparator.RecipientComparator" %>
<%@ page import="com.liferay.portal.util.comparator.PortletCategoryComparator" %>
<%@ page import="com.liferay.portal.util.comparator.PortletTitleComparator" %>
<%@ page import="com.liferay.portlet.CachePortlet" %>
<%@ page import="com.liferay.portlet.PortalPreferences" %>
<%@ page import="com.liferay.portlet.PortletConfigFactory" %>
<%@ page import="com.liferay.portlet.PortletConfigImpl" %>
<%@ page import="com.liferay.portlet.PortletInstanceFactory" %>
<%@ page import="com.liferay.portlet.PortletPreferencesFactoryUtil" %>
<%@ page import="com.liferay.portlet.PortletSetupUtil" %>
<%@ page import="com.liferay.portlet.PortletURLImpl" %>
<%@ page import="com.liferay.portlet.PortletURLUtil" %>
<%@ page import="com.liferay.portlet.RenderParametersPool" %>
<%@ page import="com.liferay.portlet.RenderRequestFactory" %>
<%@ page import="com.liferay.portlet.RenderRequestImpl" %>
<%@ page import="com.liferay.portlet.RenderResponseFactory" %>
<%@ page import="com.liferay.portlet.RenderResponseImpl" %>
<%@ page import="com.liferay.portlet.UserAttributes" %>
<%@ page import="com.liferay.portlet.messaging.util.MessagingUtil" %>
<%@ page import="com.liferay.portlet.portletconfiguration.util.PortletConfigurationUtil" %>
<%@ page import="com.liferay.util.BeanParamUtil" %>
<%@ page import="com.liferay.util.BeanUtil" %>
<%@ page import="com.liferay.util.CollectionFactory" %>
<%@ page import="com.liferay.util.CookieUtil" %>
<%@ page import="com.liferay.util.CreditCard" %>
<%@ page import="com.liferay.util.FileUtil" %>
<%@ page import="com.liferay.util.Html" %>
<%@ page import="com.liferay.util.Http" %>
<%@ page import="com.liferay.util.HttpUtil" %>
<%@ page import="com.liferay.util.JS" %>
<%@ page import="com.liferay.util.ListUtil" %>
<%@ page import="com.liferay.util.LocalizationUtil" %>
<%@ page import="com.liferay.util.MathUtil" %>
<%@ page import="com.liferay.util.PKParser" %>
<%@ page import="com.liferay.util.PwdGenerator" %>
<%@ page import="com.liferay.util.SetUtil" %>
<%@ page import="com.liferay.util.State" %>
<%@ page import="com.liferay.util.StateUtil" %>
<%@ page import="com.liferay.util.TextFormatter" %>
<%@ page import="com.liferay.util.Time" %>
<%@ page import="com.liferay.util.UniqueList" %>
<%@ page import="com.liferay.util.cal.CalendarUtil" %>
<%@ page import="com.liferay.util.dao.hibernate.QueryUtil" %>
<%@ page import="com.liferay.util.format.PhoneNumberUtil" %>
<%@ page import="com.liferay.util.log4j.Levels" %>
<%@ page import="com.liferay.util.mail.InternetAddressUtil" %>
<%@ page import="com.liferay.util.portlet.PortletRequestUtil" %>
<%@ page import="com.liferay.util.servlet.DynamicServletRequest" %>
<%@ page import="com.liferay.util.servlet.SessionErrors" %>
<%@ page import="com.liferay.util.servlet.SessionMessages" %>
<%@ page import="com.liferay.util.servlet.SessionParameters" %>
<%@ page import="com.liferay.util.servlet.UploadException" %>
<%@ page import="com.liferay.util.xml.XMLFormatter" %>

<%@ page import="java.io.ByteArrayInputStream" %>
<%@ page import="java.io.StringReader" %>

<%@ page import="java.text.DateFormat" %>
<%@ page import="java.text.DecimalFormat" %>
<%@ page import="java.text.MessageFormat" %>
<%@ page import="java.text.NumberFormat" %>
<%@ page import="java.text.SimpleDateFormat" %>

<%@ page import="java.util.ArrayList" %>
<%@ page import="java.util.Arrays" %>
<%@ page import="java.util.Calendar" %>
<%@ page import="java.util.Collection" %>
<%@ page import="java.util.Collections" %>
<%@ page import="java.util.Currency" %>
<%@ page import="java.util.Date" %>
<%@ page import="java.util.Enumeration" %>
<%@ page import="java.util.HashMap" %>
<%@ page import="java.util.HashSet" %>
<%@ page import="java.util.Iterator" %>
<%@ page import="java.util.LinkedHashMap" %>
<%@ page import="java.util.LinkedHashSet" %>
<%@ page import="java.util.List" %>
<%@ page import="java.util.Locale" %>
<%@ page import="java.util.Map" %>
<%@ page import="java.util.Properties" %>
<%@ page import="java.util.ResourceBundle" %>
<%@ page import="java.util.Set" %>
<%@ page import="java.util.Stack" %>
<%@ page import="java.util.TimeZone" %>
<%@ page import="java.util.TreeMap" %>
<%@ page import="java.util.TreeSet" %>

<%@ page import="javax.portlet.PortletConfig" %>
<%@ page import="javax.portlet.PortletContext" %>
<%@ page import="javax.portlet.PortletException" %>
<%@ page import="javax.portlet.PortletMode" %>
<%@ page import="javax.portlet.PortletPreferences" %>
<%@ page import="javax.portlet.PortletSession" %>
<%@ page import="javax.portlet.PortletURL" %>
<%@ page import="javax.portlet.RenderRequest" %>
<%@ page import="javax.portlet.RenderResponse" %>
<%@ page import="javax.portlet.UnavailableException" %>
<%@ page import="javax.portlet.ValidatorException" %>
<%@ page import="javax.portlet.WindowState" %>

<%@ page import="org.apache.struts.Globals" %>

<%@ page import="org.json.JSONObject" %>


<%@page import="com.liferay.portal.kernel.util.UnicodeFormatter"%>
<%@page import="com.liferay.portal.kernel.servlet.BrowserSniffer"%>
<%@page import="com.liferay.portal.kernel.language.LanguageUtil"%>
<%@page import="com.liferay.portal.kernel.language.UnicodeLanguageUtil"%>

<liferay-theme:defineObjects />
<%@ include file="/html/extcommon/init-ext.jsp" %>