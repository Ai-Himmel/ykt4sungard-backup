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

import com.liferay.documentlibrary.DuplicateFileException;
import com.liferay.documentlibrary.FileNameException;
import com.liferay.documentlibrary.FileSizeException;
import com.liferay.documentlibrary.SourceFileNameException;
import com.liferay.lock.DuplicateLockException;
import com.liferay.portal.kernel.portlet.LiferayWindowState;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.PropertiesUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.documentlibrary.DuplicateFolderNameException;
import com.liferay.portlet.documentlibrary.NoSuchFileEntryException;
import com.liferay.portlet.documentlibrary.NoSuchFolderException;
import com.liferay.portlet.documentlibrary.form.FileEntryForm;
import com.liferay.portlet.documentlibrary.model.DLFileEntry;
import com.liferay.portlet.documentlibrary.service.DLFileEntryLocalServiceUtil;
import com.liferay.portlet.documentlibrary.service.DLFileEntryServiceUtil;
import com.liferay.portlet.documentlibrary.service.permission.DLFileEntryPermission;
import com.liferay.portlet.documentlibrary.service.permission.DLFolderPermission;
import com.liferay.portlet.taggedcontent.util.AssetPublisherUtil;
import com.liferay.portlet.tags.TagsEntryException;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.UploadPortletRequest;

import java.io.File;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditFileEntryAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Alexander Chow
 *
 */
public class EditFileEntryAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		FileEntryForm fileEntryForm = (FileEntryForm)form;

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				updateFileEntry(fileEntryForm, req, res);
			}
			else if (cmd.equals(Constants.DELETE)) {
				deleteFileEntry(req);

				sendRedirect(req, res);
			}
			else if (cmd.equals(Constants.LOCK)) {
				lockFileEntry(req);
			}
			else if (cmd.equals(Constants.UNLOCK)) {
				unlockFileEntry(req);
			}
		}
		catch (Exception e) {
			if (e instanceof DuplicateLockException ||
				e instanceof NoSuchFileEntryException ||
				e instanceof PrincipalException) {

				if (e instanceof DuplicateLockException) {
					DuplicateLockException dle = (DuplicateLockException)e;

					SessionErrors.add(
						req, dle.getClass().getName(), dle.getLock());
				}
				else {
					SessionErrors.add(req, e.getClass().getName());
				}

				setForward(req, "portlet.document_library.error");
			}
			else if (e instanceof DuplicateFileException ||
					 e instanceof DuplicateFolderNameException ||
					 e instanceof FileNameException ||
					 e instanceof FileSizeException ||
					 e instanceof NoSuchFolderException ||
					 e instanceof SourceFileNameException) {

				SessionErrors.add(req, e.getClass().getName());
			}
			else if (e instanceof TagsEntryException) {
				SessionErrors.add(req, e.getClass().getName(), e);
			}
			else {
				throw e;
			}
		}
	}

	public ActionForward render(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			RenderRequest req, RenderResponse res)
		throws Exception {

		try {
			ActionUtil.getFileEntry(req);
		}
		catch (Exception e) {
			if (e instanceof NoSuchFileEntryException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.document_library.error");
			}
			else {
				throw e;
			}
		}

		String forward = "portlet.document_library.edit_file_entry";

		if (req.getWindowState().equals(LiferayWindowState.POP_UP)) {
			forward = "portlet.document_library.edit_file_entry_form";
		}

		return mapping.findForward(getForward(req, forward));
	}

	protected void deleteFileEntry(ActionRequest req) throws Exception {
		long folderId = ParamUtil.getLong(req, "folderId");
		String name = ParamUtil.getString(req, "name");
		double version = ParamUtil.getDouble(req, "version");

		DLFileEntryServiceUtil.deleteFileEntry(folderId, name, version);
	}

	protected void lockFileEntry(ActionRequest req) throws Exception {
		long folderId = ParamUtil.getLong(req, "folderId");
		String name = ParamUtil.getString(req, "name");

		DLFileEntryServiceUtil.lockFileEntry(folderId, name);
	}

	protected void unlockFileEntry(ActionRequest req) throws Exception {
		long folderId = ParamUtil.getLong(req, "folderId");
		String name = ParamUtil.getString(req, "name");

		DLFileEntryServiceUtil.unlockFileEntry(folderId, name);
	}

	protected void updateFileEntry(
			FileEntryForm fileEntryForm, ActionRequest req, ActionResponse res)
		throws Exception {

		UploadPortletRequest uploadReq =
			PortalUtil.getUploadPortletRequest(req);

		String cmd = ParamUtil.getString(uploadReq, Constants.CMD);

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		long folderId = ParamUtil.getLong(uploadReq, "folderId");
		long newFolderId = ParamUtil.getLong(uploadReq, "newFolderId");
		String name = ParamUtil.getString(uploadReq, "name");
		String sourceFileName = uploadReq.getFileName("file");

		String title = ParamUtil.getString(uploadReq, "title");
		String description = ParamUtil.getString(uploadReq, "description");

		String[] tagsEntries = StringUtil.split(
			ParamUtil.getString(uploadReq, "tagsEntries"));

		String extraSettings = PropertiesUtil.toString(
			fileEntryForm.getExtraSettingsProperties());

		File file = uploadReq.getFile("file");

		String[] communityPermissions = req.getParameterValues(
			"communityPermissions");
		String[] guestPermissions = req.getParameterValues(
			"guestPermissions");

		if (cmd.equals(Constants.ADD)) {

			// Add file entry

			DLFolderPermission.check(
				themeDisplay.getPermissionChecker(), folderId,
				ActionKeys.ADD_DOCUMENT);

			DLFileEntry entry = DLFileEntryLocalServiceUtil.addFileEntry(
				themeDisplay.getUserId(), folderId, sourceFileName, title,
				description, tagsEntries, extraSettings, file,
				communityPermissions, guestPermissions);

			AssetPublisherUtil.addAndStoreSelection(
				req, DLFileEntry.class.getName(), entry.getFileEntryId(), -1);
		}
		else {

			// Update file entry

			DLFileEntryPermission.check(
				themeDisplay.getPermissionChecker(), folderId, name,
				ActionKeys.UPDATE);

			DLFileEntryLocalServiceUtil.updateFileEntry(
				themeDisplay.getUserId(), folderId, newFolderId, name,
				sourceFileName, title, description, tagsEntries, extraSettings,
				file);
		}

		AssetPublisherUtil.addRecentFolderId(
			req, DLFileEntry.class.getName(), folderId);
	}

}