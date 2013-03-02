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

package com.liferay.portlet.bookmarks.action;

import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.bookmarks.DuplicateFolderException;
import com.liferay.portlet.bookmarks.FolderNameException;
import com.liferay.portlet.bookmarks.NoSuchFolderException;
import com.liferay.portlet.bookmarks.model.BookmarksFolder;
import com.liferay.portlet.bookmarks.service.spring.BookmarksFolderServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditFolderAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class EditFolderAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) &&
			(cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE))) {

			try {
				_editFolder(req);

				_updateFolder(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof DuplicateFolderException ||
					e instanceof FolderNameException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.bookmarks.edit_folder");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals(Constants.DELETE)) {
			try {
				_deleteFolder(req, res);
			}
			catch (Exception e) {
				req.setAttribute(PageContext.EXCEPTION, e);

				setForward(req, Constants.COMMON_ERROR);
			}
		}
		else if (cmd != null && cmd.equals(Constants.EDIT)) {
			try {
				_editFolder(req);

				setForward(req, "portlet.bookmarks.edit_folder");
			}
			catch (Exception e) {
				req.setAttribute(PageContext.EXCEPTION, e);

				setForward(req, Constants.COMMON_ERROR);
			}
		}
		else {
			setForward(req, "portlet.bookmarks.edit_folder");
		}
	}

	private void _deleteFolder(ActionRequest req, ActionResponse res)
		throws Exception {

		String folderId = ParamUtil.getString(req, "folder_id");

		BookmarksFolderServiceUtil.deleteFolder(folderId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _editFolder(ActionRequest req) throws Exception {
		String folderId = ParamUtil.getString(req, "folder_id");

		BookmarksFolder folder = null;

		try {
			folder = BookmarksFolderServiceUtil.getFolder(folderId);
		}
		catch (NoSuchFolderException nsfe) {
		}

		req.setAttribute(WebKeys.BOOKMARKS_FOLDER, folder);
	}

	private void _updateFolder(ActionRequest req, ActionResponse res)
		throws Exception {

		String folderId = ParamUtil.getString(req, "folder_id");

		String parentFolderId = ParamUtil.getString(req, "parent_folder_id");
		String name = ParamUtil.getString(req, "folder_name");

		if (Validator.isNull(folderId)) {

			// Add folder

			BookmarksFolderServiceUtil.addFolder(
				PortalUtil.getPortletGroupId(req), parentFolderId, name);
		}
		else {

			// Update folder

			BookmarksFolderServiceUtil.updateFolder(
				folderId, parentFolderId, name);
		}

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}