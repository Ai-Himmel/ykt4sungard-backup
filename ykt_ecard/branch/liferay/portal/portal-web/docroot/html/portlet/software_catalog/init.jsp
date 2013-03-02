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

<%@ page import="com.liferay.portal.kernel.search.Document" %>
<%@ page import="com.liferay.portal.kernel.search.DocumentComparator" %>
<%@ page import="com.liferay.portal.kernel.search.Hits" %>
<%@ page import="com.liferay.portal.service.permission.PortalPermissionUtil" %>
<%@ page import="com.liferay.portlet.imagegallery.ImageSizeException" %>
<%@ page import="com.liferay.portlet.softwarecatalog.action.ActionUtil" %>
<%@ page import="com.liferay.portlet.softwarecatalog.DuplicateProductEntryModuleIdException" %>
<%@ page import="com.liferay.portlet.softwarecatalog.DuplicateProductVersionDirectDownloadURLException" %>
<%@ page import="com.liferay.portlet.softwarecatalog.FrameworkVersionNameException" %>
<%@ page import="com.liferay.portlet.softwarecatalog.LicenseNameException" %>
<%@ page import="com.liferay.portlet.softwarecatalog.ProductEntryAuthorException" %>
<%@ page import="com.liferay.portlet.softwarecatalog.ProductEntryLicenseException" %>
<%@ page import="com.liferay.portlet.softwarecatalog.ProductEntryNameException" %>
<%@ page import="com.liferay.portlet.softwarecatalog.ProductEntryPageURLException" %>
<%@ page import="com.liferay.portlet.softwarecatalog.ProductEntryScreenshotsException" %>
<%@ page import="com.liferay.portlet.softwarecatalog.ProductEntryShortDescriptionException" %>
<%@ page import="com.liferay.portlet.softwarecatalog.ProductEntryTypeException" %>
<%@ page import="com.liferay.portlet.softwarecatalog.ProductVersionChangeLogException" %>
<%@ page import="com.liferay.portlet.softwarecatalog.ProductVersionDownloadURLException" %>
<%@ page import="com.liferay.portlet.softwarecatalog.ProductVersionFrameworkVersionException" %>
<%@ page import="com.liferay.portlet.softwarecatalog.ProductVersionNameException" %>
<%@ page import="com.liferay.portlet.softwarecatalog.NoSuchFrameworkVersionException" %>
<%@ page import="com.liferay.portlet.softwarecatalog.NoSuchLicenseException" %>
<%@ page import="com.liferay.portlet.softwarecatalog.NoSuchProductEntryException" %>
<%@ page import="com.liferay.portlet.softwarecatalog.NoSuchProductVersionException" %>
<%@ page import="com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion" %>
<%@ page import="com.liferay.portlet.softwarecatalog.model.SCLicense" %>
<%@ page import="com.liferay.portlet.softwarecatalog.model.SCProductEntry" %>
<%@ page import="com.liferay.portlet.softwarecatalog.model.SCProductScreenshot" %>
<%@ page import="com.liferay.portlet.softwarecatalog.model.SCProductVersion" %>
<%@ page import="com.liferay.portlet.softwarecatalog.model.impl.SCProductEntryImpl" %>
<%@ page import="com.liferay.portlet.softwarecatalog.service.SCFrameworkVersionLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.softwarecatalog.service.SCFrameworkVersionServiceUtil" %>
<%@ page import="com.liferay.portlet.softwarecatalog.service.SCLicenseLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.softwarecatalog.service.SCProductEntryLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.softwarecatalog.service.SCProductEntryServiceUtil" %>
<%@ page import="com.liferay.portlet.softwarecatalog.service.SCProductScreenshotLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.softwarecatalog.service.SCProductVersionLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.softwarecatalog.service.SCProductVersionServiceUtil" %>
<%@ page import="com.liferay.portlet.softwarecatalog.service.permission.SCFrameworkVersionPermission" %>
<%@ page import="com.liferay.portlet.softwarecatalog.service.permission.SCLicensePermission" %>
<%@ page import="com.liferay.portlet.softwarecatalog.service.permission.SCProductEntryPermission" %>
<%@ page import="com.liferay.portlet.softwarecatalog.util.SCUtil" %>

<%
PortalPreferences portalPrefs = PortletPreferencesFactoryUtil.getPortalPreferences(request);

DateFormat dateFormatDateTime = DateFormats.getDateTime(locale, timeZone);
%>