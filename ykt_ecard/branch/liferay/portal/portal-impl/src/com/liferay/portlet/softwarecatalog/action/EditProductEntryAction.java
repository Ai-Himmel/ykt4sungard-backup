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
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Image;
import com.liferay.portal.model.Layout;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.impl.ImageLocalUtil;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.softwarecatalog.DuplicateProductEntryModuleIdException;
import com.liferay.portlet.softwarecatalog.NoSuchProductEntryException;
import com.liferay.portlet.softwarecatalog.ProductEntryAuthorException;
import com.liferay.portlet.softwarecatalog.ProductEntryLicenseException;
import com.liferay.portlet.softwarecatalog.ProductEntryNameException;
import com.liferay.portlet.softwarecatalog.ProductEntryPageURLException;
import com.liferay.portlet.softwarecatalog.ProductEntryScreenshotsException;
import com.liferay.portlet.softwarecatalog.ProductEntryShortDescriptionException;
import com.liferay.portlet.softwarecatalog.ProductEntryTypeException;
import com.liferay.portlet.softwarecatalog.model.SCProductScreenshot;
import com.liferay.portlet.softwarecatalog.service.SCProductEntryServiceUtil;
import com.liferay.portlet.softwarecatalog.service.SCProductScreenshotLocalServiceUtil;
import com.liferay.util.FileUtil;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.UploadPortletRequest;

import java.io.File;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Enumeration;
import java.util.Iterator;
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
 * <a href="EditProductEntryAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class EditProductEntryAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = ParamUtil.getString(req, Constants.CMD);

		try {
			if (cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE)) {
				updateProductEntry(req);
			}
			else if (cmd.equals(Constants.DELETE)) {
				deleteProductEntry(req);
			}

			if (Validator.isNotNull(cmd)) {
				sendRedirect(req, res);
			}
		}
		catch (Exception e) {
			if (e instanceof NoSuchProductEntryException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				setForward(req, "portlet.software_catalog.error");
			}
			else if (e instanceof DuplicateProductEntryModuleIdException ||
					 e instanceof ProductEntryAuthorException ||
					 e instanceof ProductEntryNameException ||
					 e instanceof ProductEntryLicenseException ||
					 e instanceof ProductEntryPageURLException ||
					 e instanceof ProductEntryScreenshotsException ||
					 e instanceof ProductEntryShortDescriptionException ||
					 e instanceof ProductEntryTypeException) {

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
			ActionUtil.getProductEntry(req);
		}
		catch (Exception e) {
			if (e instanceof NoSuchProductEntryException ||
				e instanceof PrincipalException) {

				SessionErrors.add(req, e.getClass().getName());

				return mapping.findForward("portlet.software_catalog.error");
			}
			else {
				throw e;
			}
		}

		return mapping.findForward(
			getForward(req, "portlet.software_catalog.edit_product_entry"));
	}

	protected void deleteProductEntry(ActionRequest req) throws Exception {
		long productEntryId = ParamUtil.getLong(req, "productEntryId");

		SCProductEntryServiceUtil.deleteProductEntry(productEntryId);
	}

	protected List getFullImages(UploadPortletRequest uploadReq)
		throws Exception {

		return getImages(uploadReq, "fullImage");
	}

	protected List getImages(UploadPortletRequest uploadReq, String imagePrefix)
		throws Exception {

		List images = new ArrayList();

		Iterator itr = getSortedParameterNames(
			uploadReq, imagePrefix).iterator();

		while (itr.hasNext()) {
			String name = (String)itr.next();

			int priority = GetterUtil.getInteger(
				name.substring(imagePrefix.length(), name.length()));

			File file = uploadReq.getFile(name);
			byte[] bytes = FileUtil.getBytes(file);

			boolean preserveScreenshot = ParamUtil.getBoolean(
				uploadReq, "preserveScreenshot" + priority);

			if (preserveScreenshot) {
				SCProductScreenshot productScreenshot = getProductScreenshot(
					uploadReq, priority);

				Image image = null;

				if (imagePrefix.equals("fullImage")) {
					image = ImageLocalUtil.getImage(
						productScreenshot.getFullImageId());
				}
				else {
					image = ImageLocalUtil.getImage(
						productScreenshot.getThumbnailId());
				}

				bytes = image.getTextObj();
			}

			if ((bytes != null) && (bytes.length > 0)) {
				images.add(bytes);
			}
			else {
				throw new ProductEntryScreenshotsException();
			}
		}

		return images;
	}

	protected SCProductScreenshot getProductScreenshot(
			UploadPortletRequest uploadReq, int priority)
		throws Exception {

		long productEntryId = ParamUtil.getLong(uploadReq, "productEntryId");

		try {
			return SCProductScreenshotLocalServiceUtil.getProductScreenshot(
				productEntryId, priority);
		}
		catch (Exception e) {
			throw new ProductEntryScreenshotsException();
		}
	}

	protected List getSortedParameterNames(
			UploadPortletRequest uploadReq, String imagePrefix)
		throws Exception {

		List parameterNames = new ArrayList();

		Enumeration enu = uploadReq.getParameterNames();

		while (enu.hasMoreElements()) {
			String name = (String)enu.nextElement();

			if (name.startsWith(imagePrefix)) {
				parameterNames.add(name);
			}
		}

		Collections.sort(parameterNames);

		return parameterNames;
	}

	protected List getThumbnails(UploadPortletRequest uploadReq)
		throws Exception {

		return getImages(uploadReq, "thumbnail");
	}

	protected void updateProductEntry(ActionRequest req) throws Exception {
		UploadPortletRequest uploadReq =
			PortalUtil.getUploadPortletRequest(req);

		Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);

		long productEntryId = ParamUtil.getLong(req, "productEntryId");

		String name = ParamUtil.getString(req, "name");
		String type = ParamUtil.getString(req, "type");
		String tags = ParamUtil.getString(req, "tags");
		String shortDescription = ParamUtil.getString(req, "shortDescription");
		String longDescription = ParamUtil.getString(req, "longDescription");
		String pageURL = ParamUtil.getString(req, "pageURL");
		String author = ParamUtil.getString(req, "author");
		String repoGroupId = ParamUtil.getString(req, "repoGroupId");
		String repoArtifactId = ParamUtil.getString(req, "repoArtifactId");

		long[] licenseIds = ParamUtil.getLongValues(req, "licenses");

		List thumbnails = getThumbnails(uploadReq);
		List fullImages = getFullImages(uploadReq);

		String[] communityPermissions = req.getParameterValues(
			"communityPermissions");
		String[] guestPermissions = req.getParameterValues(
			"guestPermissions");

		if (productEntryId <= 0) {

			// Add product entry

			SCProductEntryServiceUtil.addProductEntry(
				layout.getPlid(), name, type, tags, shortDescription,
				longDescription, pageURL, author, repoGroupId, repoArtifactId,
				licenseIds, thumbnails, fullImages, communityPermissions,
				guestPermissions);
		}
		else {

			// Update product entry

			SCProductEntryServiceUtil.updateProductEntry(
				productEntryId, name, type, tags, shortDescription,
				longDescription, pageURL, author, repoGroupId, repoArtifactId,
				licenseIds, thumbnails, fullImages);
		}
	}

}