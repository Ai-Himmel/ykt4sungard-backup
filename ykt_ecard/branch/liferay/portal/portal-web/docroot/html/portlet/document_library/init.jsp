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

<%@ page import="com.liferay.documentlibrary.DirectoryNameException" %>
<%@ page import="com.liferay.documentlibrary.DuplicateDirectoryException" %>
<%@ page import="com.liferay.documentlibrary.DuplicateFileException" %>
<%@ page import="com.liferay.documentlibrary.FileNameException" %>
<%@ page import="com.liferay.documentlibrary.FileSizeException" %>
<%@ page import="com.liferay.documentlibrary.NoSuchDirectoryException" %>
<%@ page import="com.liferay.documentlibrary.NoSuchFileException" %>
<%@ page import="com.liferay.documentlibrary.SourceFileNameException" %>
<%@ page import="com.liferay.portal.kernel.search.Document" %>
<%@ page import="com.liferay.portal.kernel.search.Hits" %>
<%@ page import="com.liferay.portlet.documentlibrary.DuplicateFolderNameException" %>
<%@ page import="com.liferay.portlet.documentlibrary.FileShortcutPermissionException" %>
<%@ page import="com.liferay.portlet.documentlibrary.FolderNameException" %>
<%@ page import="com.liferay.portlet.documentlibrary.NoSuchFileEntryException" %>
<%@ page import="com.liferay.portlet.documentlibrary.NoSuchFolderException" %>
<%@ page import="com.liferay.portlet.documentlibrary.model.DLFileEntry" %>
<%@ page import="com.liferay.portlet.documentlibrary.model.DLFileShortcut" %>
<%@ page import="com.liferay.portlet.documentlibrary.model.DLFileVersion" %>
<%@ page import="com.liferay.portlet.documentlibrary.model.DLFolder" %>
<%@ page import="com.liferay.portlet.documentlibrary.model.impl.DLFileEntryImpl" %>
<%@ page import="com.liferay.portlet.documentlibrary.model.impl.DLFolderImpl" %>
<%@ page import="com.liferay.portlet.documentlibrary.service.DLFileEntryLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.documentlibrary.service.DLFileVersionLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.documentlibrary.service.DLFolderLocalServiceUtil" %>
<%@ page import="com.liferay.portlet.documentlibrary.service.permission.DLFileEntryPermission" %>
<%@ page import="com.liferay.portlet.documentlibrary.service.permission.DLFileShortcutPermission" %>
<%@ page import="com.liferay.portlet.documentlibrary.service.permission.DLFolderPermission" %>
<%@ page import="com.liferay.portlet.documentlibrary.util.DLUtil" %>
<%@ page import="com.liferay.portlet.documentlibrary.util.DocumentConversionUtil" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.GroupSearch" %>
<%@ page import="com.liferay.portlet.enterpriseadmin.search.GroupSearchTerms" %>

<%
PortletPreferences prefs = renderRequest.getPreferences();

String portletResource = ParamUtil.getString(request, "portletResource");

if (Validator.isNotNull(portletResource)) {
	prefs = PortletPreferencesFactoryUtil.getPortletSetup(request, portletResource, true, true);
}

DLFolder rootFolder = null;

long rootFolderId = PrefsParamUtil.getLong(prefs, request, "rootFolderId", DLFolderImpl.DEFAULT_PARENT_FOLDER_ID);
String rootFolderName = StringPool.BLANK;

if (rootFolderId != DLFolderImpl.DEFAULT_PARENT_FOLDER_ID) {
	try {
		rootFolder = DLFolderLocalServiceUtil.getFolder(rootFolderId);

		rootFolderName = rootFolder.getName();
	}
	catch (NoSuchFolderException nsfe) {
	}
}

String folderDisplayStyle = PrefsParamUtil.getString(prefs, request, "folderDisplayStyle", "tree");

boolean showBreadcrumbs = PrefsParamUtil.getBoolean(prefs, request, "showBreadcrumbs", true);
boolean showFoldersSearch = PrefsParamUtil.getBoolean(prefs, request, "showFoldersSearch", true);
boolean showSubfolders = PrefsParamUtil.getBoolean(prefs, request, "showSubfolders", true);
int foldersPerPage = PrefsParamUtil.getInteger(prefs, request, "foldersPerPage", SearchContainer.DEFAULT_DELTA);

String defaultFolderColumns = "folder,num-of-folders,num-of-documents,action";
String allFolderColumns = defaultFolderColumns;

String[] folderColumns = StringUtil.split(PrefsParamUtil.getString(prefs, request, "folderColumns", defaultFolderColumns));

boolean showFileEntriesSearch = PrefsParamUtil.getBoolean(prefs, request, "showFileEntriesSearch", true);
int fileEntriesPerPage = PrefsParamUtil.getInteger(prefs, request, "fileEntriesPerPage", SearchContainer.DEFAULT_DELTA);

String defaultFileEntryColumns = "document,size,downloads,locked,action";
String allFileEntryColumns = defaultFileEntryColumns;

String[] fileEntryColumns = StringUtil.split(PrefsParamUtil.getString(prefs, request, "fileEntryColumns", defaultFileEntryColumns));

boolean showTabs = false;
boolean showButtons = false;

if (portletConfig.getPortletName().equals(PortletKeys.DOCUMENT_LIBRARY)) {
	showTabs = true;
	showButtons = true;
}

DateFormat dateFormatDateTime = DateFormats.getDateTime(locale, timeZone);
%>