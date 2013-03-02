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

package com.liferay.portlet.softwarecatalog.action;

import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portlet.softwarecatalog.DuplicateProductVersionDirectDownloadURLException;
import com.liferay.portlet.softwarecatalog.NoSuchProductVersionException;
import com.liferay.portlet.softwarecatalog.ProductVersionChangeLogException;
import com.liferay.portlet.softwarecatalog.ProductVersionDownloadURLException;
import com.liferay.portlet.softwarecatalog.ProductVersionFrameworkVersionException;
import com.liferay.portlet.softwarecatalog.ProductVersionNameException;
import com.liferay.portlet.softwarecatalog.service.SCProductVersionServiceUtil;
import com.liferay.util.servlet.SessionErrors;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditProductVersionAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class EditProductVersionAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				updateProductVersion(req);
			}
			else if (cmd.equals(Constants.DELETE)) {
				deleteProductVersion(req);
			}

			sendRedirect(req, res);
		}
		catch (Exception e) {
			if (e instanceof NoSuchProductVersionException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.software_catalog.error");
			}
			else if (e instanceof
						DuplicateProductVersionDirectDownloadURLException ||
					 e instanceof ProductVersionChangeLogException ||
					 e instanceof ProductVersionDownloadURLException ||
					 e instanceof ProductVersionFrameworkVersionException ||
					 e instanceof ProductVersionNameException) {

				SessionErrors.add(req, e.getClass().getName());
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
			ActionUtil.getProductVersion(req);
		}
		catch (Exception e) {
			if (e instanceof NoSuchProductVersionException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.software_catalog.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(getForward(
			req, "portlet.software_catalog.edit_product_version"));
	}

	protected void deleteProductVersion(ActionRequest req) throws Exception {
		long productVersionId = ParamUtil.getLong(req, "productVersionId");

		SCProductVersionServiceUtil.deleteProductVersion(productVersionId);
	}

	protected void updateProductVersion(ActionRequest req) throws Exception {
		long productVersionId = ParamUtil.getLong(req, "productVersionId");

		long productEntryId = ParamUtil.getLong(req, "productEntryId");
		String version = ParamUtil.getString(req, "version");
		String changeLog = ParamUtil.getString(req, "changeLog");
		String downloadPageURL = ParamUtil.getString(req, "downloadPageURL");
		String directDownloadURL = ParamUtil.getString(
			req, "directDownloadURL");
		boolean repoStoreArtifact = ParamUtil.getBoolean(
			req, "repoStoreArtifact");

		long[] frameworkVersionIds = ParamUtil.getLongValues(
			req, "frameworkVersions");

		String[] communityPermissions = req.getParameterValues(
			"communityPermissions");
		String[] guestPermissions = req.getParameterValues(
			"guestPermissions");

		if (productVersionId <= 0) {

			// Add product version

			SCProductVersionServiceUtil.addProductVersion(
				productEntryId, version, changeLog, downloadPageURL,
				directDownloadURL, repoStoreArtifact, frameworkVersionIds,
				communityPermissions, guestPermissions);
		}
		else {

			// Update product version

			SCProductVersionServiceUtil.updateProductVersion(
				productVersionId, version, changeLog, downloadPageURL,
				directDownloadURL, repoStoreArtifact, frameworkVersionIds);
		}
	}

}