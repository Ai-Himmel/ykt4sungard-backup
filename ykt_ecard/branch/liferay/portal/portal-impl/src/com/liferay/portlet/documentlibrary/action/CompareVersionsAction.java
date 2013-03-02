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

import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.documentlibrary.NoSuchFileEntryException;
import com.liferay.portlet.documentlibrary.service.DLFileEntryLocalServiceUtil;
import com.liferay.portlet.documentlibrary.service.permission.DLFileEntryPermission;
import com.liferay.util.diff.DiffUtil;
import com.liferay.util.servlet.SessionErrors;

import java.io.InputStream;
import java.io.InputStreamReader;

import java.util.List;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="CompareVersionsAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Bruno Farache
 *
 */
public class CompareVersionsAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		try {
			compareVersions(req);
		}
		catch (Exception e) {
			if (e instanceof NoSuchFileEntryException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.document_library.error");
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

		return mapping.findForward("portlet.document_library.compare_versions");
	}

	protected void compareVersions(ActionRequest req) throws Exception {
		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		long companyId = themeDisplay.getCompanyId();
		long userId = themeDisplay.getUserId();

		long folderId = ParamUtil.getLong(req, "folderId");
		String name = ParamUtil.getString(req, "name");

		DLFileEntryPermission.check(
			themeDisplay.getPermissionChecker(), folderId, name,
			ActionKeys.VIEW);

		String titleWithExtension = ParamUtil.getString(
			req, "titleWithExtension");

		double sourceVersion = ParamUtil.getDouble(req, "sourceVersion");
		double targetVersion = ParamUtil.getDouble(req, "targetVersion");

		InputStream sourceIs = DLFileEntryLocalServiceUtil.getFileAsStream(
			companyId, userId, folderId, name, sourceVersion);
		InputStream targetIs = DLFileEntryLocalServiceUtil.getFileAsStream(
			companyId, userId, folderId, name, targetVersion);

		List[] diffResults = DiffUtil.diff(
			new InputStreamReader(sourceIs), new InputStreamReader(targetIs));

		req.setAttribute(
			WebKeys.SOURCE_NAME,
			titleWithExtension + StringPool.SPACE + sourceVersion);
		req.setAttribute(
			WebKeys.TARGET_NAME,
			titleWithExtension + StringPool.SPACE + targetVersion);
		req.setAttribute(WebKeys.DIFF_RESULTS, diffResults);
	}

}