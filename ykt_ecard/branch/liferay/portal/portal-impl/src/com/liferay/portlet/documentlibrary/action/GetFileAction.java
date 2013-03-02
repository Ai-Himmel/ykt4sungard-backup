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

import com.liferay.portal.PortalException;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.struts.ActionConstants;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.MimeTypesUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.ActionRequestImpl;
import com.liferay.portlet.ActionResponseImpl;
import com.liferay.portlet.documentlibrary.model.DLFileEntry;
import com.liferay.portlet.documentlibrary.model.DLFileShortcut;
import com.liferay.portlet.documentlibrary.service.DLFileEntryLocalServiceUtil;
import com.liferay.portlet.documentlibrary.service.DLFileShortcutServiceUtil;
import com.liferay.portlet.documentlibrary.service.permission.DLFileEntryPermission;
import com.liferay.portlet.documentlibrary.util.DocumentConversionUtil;
import com.liferay.util.FileUtil;
import com.liferay.util.servlet.ServletResponseUtil;

import java.io.InputStream;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="GetFileAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Jorge Ferrer
 * @author Charles May
 * @author Bruno Farache
 *
 */
public class GetFileAction extends PortletAction {

	public ActionForward strutsExecute(
			ActionMapping mapping, ActionForm form, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		try {
			long folderId = ParamUtil.getLong(req, "folderId");
			String name = ParamUtil.getString(req, "name");
			double version = ParamUtil.getDouble(req, "version");

			long fileShortcutId = ParamUtil.getLong(req, "fileShortcutId");

			String uuid = ParamUtil.getString(req, "uuid");
			long groupId = ParamUtil.getLong(req, "groupId");

			String targetExtension = ParamUtil.getString(
				req, "targetExtension");

			ThemeDisplay themeDisplay =
				(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

			getFile(
				folderId, name, version, fileShortcutId, uuid, groupId,
				targetExtension, themeDisplay, req, res);

			return null;
		}
		catch (Exception e) {
			req.setAttribute(PageContext.EXCEPTION, e);

			return mapping.findForward(ActionConstants.COMMON_ERROR);
		}
	}

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		long folderId = ParamUtil.getLong(req, "folderId");
		String name = ParamUtil.getString(req, "name");
		double version = ParamUtil.getDouble(req, "version");

		long fileShortcutId = ParamUtil.getLong(req, "fileShortcutId");

		String uuid = ParamUtil.getString(req, "uuid");
		long groupId = ParamUtil.getLong(req, "groupId");

		String targetExtension = ParamUtil.getString(req, "targetExtension");

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		HttpServletRequest httpReq =
			((ActionRequestImpl)req).getHttpServletRequest();
		HttpServletResponse httpRes =
			((ActionResponseImpl)res).getHttpServletResponse();

		getFile(
			folderId, name, version, fileShortcutId, uuid, groupId,
			targetExtension, themeDisplay, httpReq, httpRes);

		setForward(req, ActionConstants.COMMON_NULL);
	}

	protected void getFile(
			long folderId, String name, double version, long fileShortcutId,
			String uuid, long groupId, String targetExtension,
			ThemeDisplay themeDisplay, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		InputStream is = null;

		try {
			long companyId = themeDisplay.getCompanyId();
			long userId = themeDisplay.getUserId();

			DLFileEntry fileEntry = null;

			if (Validator.isNotNull(uuid) && (groupId > 0)) {
				try {
					fileEntry = DLFileEntryLocalServiceUtil.
						getFileEntryByUuidAndGroupId(
							uuid, groupId);

					folderId = fileEntry.getFolderId();
					name = fileEntry.getName();
				}
				catch (Exception e) {
				}
			}

			if (fileShortcutId <= 0) {
				DLFileEntryPermission.check(
					themeDisplay.getPermissionChecker(), folderId, name,
					ActionKeys.VIEW);
			}
			else {
				DLFileShortcut fileShortcut =
					DLFileShortcutServiceUtil.getFileShortcut(fileShortcutId);

				folderId = fileShortcut.getToFolderId();
				name = fileShortcut.getToName();
			}

			if (fileEntry == null) {
				fileEntry = DLFileEntryLocalServiceUtil.getFileEntry(
					folderId, name);
			}

			if (version == 0) {
				version = fileEntry.getVersion();
			}

			is = DLFileEntryLocalServiceUtil.getFileAsStream(
				companyId, userId, folderId, name, version);

			String fileName = fileEntry.getTitleWithExtension();

			if (Validator.isNotNull(targetExtension)) {
				StringMaker sm = new StringMaker();

				sm.append(fileEntry.getFileEntryId());
				sm.append(StringPool.PERIOD);
				sm.append(version);

				String id = sm.toString();

				String sourceExtension = FileUtil.getExtension(name);

				InputStream convertedIS = DocumentConversionUtil.convert(
					id, is, sourceExtension, targetExtension);

				if ((convertedIS != null) && (convertedIS != is)) {
					sm = new StringMaker();

					sm.append(fileEntry.getTitle());
					sm.append(StringPool.PERIOD);
					sm.append(targetExtension);

					fileName = sm.toString();

					is = convertedIS;
				}
			}

			String contentType = MimeTypesUtil.getContentType(fileName);

			ServletResponseUtil.sendFile(res, fileName, is, contentType);
		}
		catch (PortalException pe) {
			if (pe instanceof PrincipalException) {
				PortalUtil.sendError(
					HttpServletResponse.SC_FORBIDDEN, new PrincipalException(),
					req, res);
			}
			else {
				PortalUtil.sendError(
					HttpServletResponse.SC_NOT_FOUND, pe, req, res);
			}
		}
		finally {
			ServletResponseUtil.cleanUp(is);
		}
	}

	protected boolean isCheckMethodOnProcessAction() {
		return _CHECK_METHOD_ON_PROCESS_ACTION;
	}

	private static final boolean _CHECK_METHOD_ON_PROCESS_ACTION = false;

}