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

--%><%@ taglib uri="http://displaytag.sf.net" prefix="display" %><%--

--%><%@ taglib uri="http://easyconf.sourceforge.net/tags-easyconf" prefix="easyconf" %><%--

--%><%@ taglib uri="http://java.sun.com/jstl/core_rt" prefix="c" %><%--
--%><%@ taglib uri="http://java.sun.com/jstl/fmt_rt" prefix="fmt" %><%--
--%><%@ taglib uri="http://java.sun.com/jstl/sql_rt" prefix="sql" %><%--
--%><%@ taglib uri="http://java.sun.com/jstl/xml_rt" prefix="x" %><%--

--%><%@ taglib uri="http://java.sun.com/portlet" prefix="portlet" %><%--

--%><%@ taglib uri="http://liferay.com/tld/theme" prefix="theme" %><%--
--%><%@ taglib uri="http://liferay.com/tld/util" prefix="liferay" %><%--

--%><%@ taglib uri="http://struts.apache.org/tags-bean" prefix="bean" %><%--
--%><%@ taglib uri="http://struts.apache.org/tags-bean-el" prefix="bean-el" %><%--
--%><%@ taglib uri="http://struts.apache.org/tags-html" prefix="html" %><%--
--%><%@ taglib uri="http://struts.apache.org/tags-html-el" prefix="html-el" %><%--
--%><%@ taglib uri="http://struts.apache.org/tags-logic" prefix="logic" %><%--
--%><%@ taglib uri="http://struts.apache.org/tags-logic-el" prefix="logic-el" %><%--
--%><%@ taglib uri="http://struts.apache.org/tags-nested" prefix="nested" %><%--
--%><%@ taglib uri="http://struts.apache.org/tags-tiles" prefix="tiles" %><%--
--%><%@ taglib uri="http://struts.apache.org/tags-tiles-el" prefix="tiles-el" %><%--

--%><%@ page contentType="text/html; charset=UTF-8" %><%--

--%><%@ page import="com.liferay.lock.DuplicateLockException" %><%--
--%><%@ page import="com.liferay.lock.model.Lock" %><%--
--%><%@ page import="com.liferay.lock.service.spring.LockServiceUtil" %><%--
--%><%@ page import="com.liferay.portal.NoSuchUserException" %><%--
--%><%@ page import="com.liferay.portal.auth.PrincipalException" %><%--
--%><%@ page import="com.liferay.portal.language.LanguageUtil" %><%--
--%><%@ page import="com.liferay.portal.language.LanguageWrapper" %><%--
--%><%@ page import="com.liferay.portal.language.UnicodeLanguageUtil" %><%--
--%><%@ page import="com.liferay.portal.lucene.LuceneFields" %><%--
--%><%@ page import="com.liferay.portal.model.*" %><%--
--%><%@ page import="com.liferay.portal.theme.PortletDisplay" %><%--
--%><%@ page import="com.liferay.portal.theme.ThemeDisplay" %><%--
--%><%@ page import="com.liferay.portal.service.spring.AddressServiceUtil" %><%--
--%><%@ page import="com.liferay.portal.service.spring.CompanyLocalServiceUtil" %><%--
--%><%@ page import="com.liferay.portal.service.spring.GroupLocalServiceUtil" %><%--
--%><%@ page import="com.liferay.portal.service.spring.PortletServiceUtil" %><%--
--%><%@ page import="com.liferay.portal.service.spring.PortletPreferencesServiceUtil" %><%--
--%><%@ page import="com.liferay.portal.service.spring.RoleLocalServiceUtil" %><%--
--%><%@ page import="com.liferay.portal.service.spring.ThemeServiceUtil" %><%--
--%><%@ page import="com.liferay.portal.service.spring.UserLocalServiceUtil" %><%--
--%><%@ page import="com.liferay.portal.util.CompanyPropsUtil" %><%--
--%><%@ page import="com.liferay.portal.util.Constants" %><%--
--%><%@ page import="com.liferay.portal.util.ContentUtil" %><%--
--%><%@ page import="com.liferay.portal.util.CookieKeys" %><%--
--%><%@ page import="com.liferay.portal.util.ImageKey" %><%--
--%><%@ page import="com.liferay.portal.util.OmniadminUtil" %><%--
--%><%@ page import="com.liferay.portal.util.PortalUtil" %><%--
--%><%@ page import="com.liferay.portal.util.PortletKeys" %><%--
--%><%@ page import="com.liferay.portal.util.PropsUtil" %><%--
--%><%@ page import="com.liferay.portal.util.Recipient" %><%--
--%><%@ page import="com.liferay.portal.util.RecipientComparator" %><%--
--%><%@ page import="com.liferay.portal.util.ReleaseInfo" %><%--
--%><%@ page import="com.liferay.portal.util.Resolution" %><%--
--%><%@ page import="com.liferay.portal.util.SessionClicks" %><%--
--%><%@ page import="com.liferay.portal.util.SessionTreeJSClicks" %><%--
--%><%@ page import="com.liferay.portal.util.ShutdownUtil" %><%--
--%><%@ page import="com.liferay.portal.util.WebAppPool" %><%--
--%><%@ page import="com.liferay.portal.util.WebKeys" %><%--
--%><%@ page import="com.liferay.portlet.CachePortlet" %><%--
--%><%@ page import="com.liferay.portlet.LiferayWindowState" %><%--
--%><%@ page import="com.liferay.portlet.PortletConfigFactory" %><%--
--%><%@ page import="com.liferay.portlet.PortletInstanceFactory" %><%--
--%><%@ page import="com.liferay.portlet.PortletURLImpl" %><%--
--%><%@ page import="com.liferay.portlet.RenderParametersPool" %><%--
--%><%@ page import="com.liferay.portlet.RenderRequestFactory" %><%--
--%><%@ page import="com.liferay.portlet.RenderRequestImpl" %><%--
--%><%@ page import="com.liferay.portlet.RenderResponseFactory" %><%--
--%><%@ page import="com.liferay.portlet.RenderResponseImpl" %><%--
--%><%@ page import="com.liferay.portlet.admin.model.EmailConfig" %><%--
--%><%@ page import="com.liferay.portlet.admin.model.JournalConfig" %><%--
--%><%@ page import="com.liferay.portlet.admin.model.ShoppingConfig" %><%--
--%><%@ page import="com.liferay.portlet.admin.model.UserConfig" %><%--
--%><%@ page import="com.liferay.portlet.admin.service.spring.AdminConfigServiceUtil" %><%--
--%><%@ page import="com.liferay.util.BrowserSniffer" %><%--
--%><%@ page import="com.liferay.util.CollectionFactory" %><%--
--%><%@ page import="com.liferay.util.CreditCard" %><%--
--%><%@ page import="com.liferay.util.FileUtil" %><%--
--%><%@ page import="com.liferay.util.GetterUtil" %><%--
--%><%@ page import="com.liferay.util.Html" %><%--
--%><%@ page import="com.liferay.util.Http" %><%--
--%><%@ page import="com.liferay.util.JS" %><%--
--%><%@ page import="com.liferay.util.KeyValuePair" %><%--
--%><%@ page import="com.liferay.util.KeyValuePairComparator" %><%--
--%><%@ page import="com.liferay.util.LocaleUtil" %><%--
--%><%@ page import="com.liferay.util.MathUtil" %><%--
--%><%@ page import="com.liferay.util.ObjectValuePair" %><%--
--%><%@ page import="com.liferay.util.OrderedProperties" %><%--
--%><%@ page import="com.liferay.util.ParamUtil" %><%--
--%><%@ page import="com.liferay.util.PropertiesUtil" %><%--
--%><%@ page import="com.liferay.util.ServerDetector" %><%--
--%><%@ page import="com.liferay.util.SimpleCachePool" %><%--
--%><%@ page import="com.liferay.util.SortedProperties" %><%--
--%><%@ page import="com.liferay.util.State" %><%--
--%><%@ page import="com.liferay.util.StateUtil" %><%--
--%><%@ page import="com.liferay.util.StringComparator" %><%--
--%><%@ page import="com.liferay.util.StringPool" %><%--
--%><%@ page import="com.liferay.util.StringUtil" %><%--
--%><%@ page import="com.liferay.util.TextFormatter" %><%--
--%><%@ page import="com.liferay.util.Time" %><%--
--%><%@ page import="com.liferay.util.UnicodeFormatter" %><%--
--%><%@ page import="com.liferay.util.Validator" %><%--
--%><%@ page import="com.liferay.util.cal.CalendarUtil" %><%--
--%><%@ page import="com.liferay.util.cal.Recurrence" %><%--
--%><%@ page import="com.liferay.util.dao.hibernate.OrderByComparator" %><%--
--%><%@ page import="com.liferay.util.format.PhoneNumberUtil" %><%--
--%><%@ page import="com.liferay.util.lang.BooleanWrapper" %><%--
--%><%@ page import="com.liferay.util.lang.FastStringBuffer" %><%--
--%><%@ page import="com.liferay.util.lang.IntegerWrapper" %><%--
--%><%@ page import="com.liferay.util.log4j.Levels" %><%--
--%><%@ page import="com.liferay.util.lucene.Hits" %><%--
--%><%@ page import="com.liferay.util.servlet.DynamicServletRequest" %><%--
--%><%@ page import="com.liferay.util.servlet.SessionErrors" %><%--
--%><%@ page import="com.liferay.util.servlet.SessionMessages" %><%--
--%><%@ page import="com.liferay.util.servlet.SessionParameters" %><%--
--%><%@ page import="com.liferay.util.servlet.StringServletResponse" %><%--
--%><%@ page import="com.liferay.util.servlet.UploadException" %><%--
--%><%@ page import="com.liferay.util.xml.XMLFormatter" %><%--

--%><%@ page import="java.io.ByteArrayInputStream" %><%--
--%><%@ page import="java.io.StringReader" %><%--

--%><%@ page import="java.text.DateFormat" %><%--
--%><%@ page import="java.text.DecimalFormat" %><%--
--%><%@ page import="java.text.MessageFormat" %><%--
--%><%@ page import="java.text.NumberFormat" %><%--
--%><%@ page import="java.text.SimpleDateFormat" %><%--

--%><%@ page import="java.util.ArrayList" %><%--
--%><%@ page import="java.util.Arrays" %><%--
--%><%@ page import="java.util.Calendar" %><%--
--%><%@ page import="java.util.Collection" %><%--
--%><%@ page import="java.util.Collections" %><%--
--%><%@ page import="java.util.Currency" %><%--
--%><%@ page import="java.util.Date" %><%--
--%><%@ page import="java.util.Enumeration" %><%--
--%><%@ page import="java.util.GregorianCalendar" %><%--
--%><%@ page import="java.util.HashMap" %><%--
--%><%@ page import="java.util.HashSet" %><%--
--%><%@ page import="java.util.Iterator" %><%--
--%><%@ page import="java.util.LinkedHashMap" %><%--
--%><%@ page import="java.util.LinkedHashSet" %><%--
--%><%@ page import="java.util.List" %><%--
--%><%@ page import="java.util.Map" %><%--
--%><%@ page import="java.util.Locale" %><%--
--%><%@ page import="java.util.Properties" %><%--
--%><%@ page import="java.util.Random" %><%--
--%><%@ page import="java.util.Set" %><%--
--%><%@ page import="java.util.Stack" %><%--
--%><%@ page import="java.util.TimeZone" %><%--
--%><%@ page import="java.util.TreeMap" %><%--
--%><%@ page import="java.util.TreeSet" %><%--

--%><%@ page import="javax.portlet.PortletConfig" %><%--
--%><%@ page import="javax.portlet.PortletContext" %><%--
--%><%@ page import="javax.portlet.PortletException" %><%--
--%><%@ page import="javax.portlet.PortletMode" %><%--
--%><%@ page import="javax.portlet.PortletPreferences" %><%--
--%><%@ page import="javax.portlet.PortletURL" %><%--
--%><%@ page import="javax.portlet.UnavailableException" %><%--
--%><%@ page import="javax.portlet.ValidatorException" %><%--
--%><%@ page import="javax.portlet.WindowState" %><%--

--%><%@ page import="org.apache.commons.logging.Log" %><%--
--%><%@ page import="org.apache.commons.logging.LogFactory" %><%--
--%><%@ page import="org.apache.struts.Globals" %><%--

--%><theme:defineObjects /><%--

--%><%@ include file="/html/common/init-ext.jsp" %>