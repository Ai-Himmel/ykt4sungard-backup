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

package com.liferay.portlet.documentlibrary.action;

import com.liferay.portal.kernel.portlet.ConfigurationAction;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portlet.PortletPreferencesFactoryUtil;
import com.liferay.portlet.documentlibrary.NoSuchFolderException;
import com.liferay.portlet.documentlibrary.model.impl.DLFolderImpl;
import com.liferay.portlet.documentlibrary.service.DLFolderLocalServiceUtil;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.SessionMessages;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletPreferences;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

/**
 * <a href="ConfigurationActionImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class ConfigurationActionImpl implements ConfigurationAction {

	public void processAction(
			PortletConfig config, ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		if (!cmd.equals(Constants.UPDATE)) {
			return;
		}

		String folderDisplayStyle = ParamUtil.getString(
			req, "folderDisplayStyle");

		long rootFolderId = ParamUtil.getLong(req, "rootFolderId");

		boolean showBreadcrumbs = ParamUtil.getBoolean(req, "showBreadcrumbs");
		boolean showFoldersSearch = ParamUtil.getBoolean(
			req, "showFoldersSearch");
		boolean showSubfolders = ParamUtil.getBoolean(req, "showSubfolders");
		int foldersPerPage = ParamUtil.getInteger(req, "foldersPerPage");
		String folderColumns = ParamUtil.getString(req, "folderColumns");

		boolean showFileEntriesSearch = ParamUtil.getBoolean(
			req, "showFileEntriesSearch");
		int fileEntriesPerPage = ParamUtil.getInteger(
			req, "fileEntriesPerPage");
		String fileEntryColumns = ParamUtil.getString(req, "fileEntryColumns");

		String portletResource = ParamUtil.getString(
			req, "portletResource");

		PortletPreferences prefs =
			PortletPreferencesFactoryUtil.getPortletSetup(
				req, portletResource, true, true);

		if (rootFolderId != DLFolderImpl.DEFAULT_PARENT_FOLDER_ID) {
			try {
				DLFolderLocalServiceUtil.getFolder(rootFolderId);
			}
			catch (NoSuchFolderException e) {
				SessionErrors.add(req, "rootFolderIdInvalid");
			}
		}

		prefs.setValue("folderDisplayStyle", folderDisplayStyle);

		prefs.setValue("rootFolderId", String.valueOf(rootFolderId));

		prefs.setValue("showBreadcrumbs", String.valueOf(showBreadcrumbs));
		prefs.setValue("showFoldersSearch", String.valueOf(showFoldersSearch));
		prefs.setValue("showSubfolders", String.valueOf(showSubfolders));
		prefs.setValue("foldersPerPage", String.valueOf(foldersPerPage));
		prefs.setValue("folderColumns", folderColumns);

		prefs.setValue(
			"showFileEntriesSearch", String.valueOf(showFileEntriesSearch));
		prefs.setValue(
			"fileEntriesPerPage", String.valueOf(fileEntriesPerPage));
		prefs.setValue("fileEntryColumns", fileEntryColumns);

		if (SessionErrors.isEmpty(req)) {
			prefs.store();

			SessionMessages.add(req, config.getPortletName() + ".doConfigure");
		}
	}

	public String render(
			PortletConfig config, RenderRequest req, RenderResponse res)
		throws Exception {

		return "/html/portlet/document_library/configuration.jsp";
	}

}