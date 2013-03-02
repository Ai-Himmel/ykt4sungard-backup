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

package com.liferay.portlet.imagegallery.action;

import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.imagegallery.ImageNameException;
import com.liferay.portlet.imagegallery.ImageSizeException;
import com.liferay.portlet.imagegallery.NoSuchImageException;
import com.liferay.portlet.imagegallery.model.IGImage;
import com.liferay.portlet.imagegallery.service.spring.IGImageServiceUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.Validator;
import com.liferay.util.servlet.SessionErrors;
import com.liferay.util.servlet.UploadPortletRequest;

import java.io.File;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.jsp.PageContext;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

/**
 * <a href="EditImageAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class EditImageAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		String cmd = req.getParameter(Constants.CMD);

		if ((cmd != null) &&
			(cmd.equals(Constants.ADD) || cmd.equals(Constants.UPDATE))) {

			try {
				_editImage(req);

				_updateImage(req, res);
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof ImageNameException ||
					e instanceof ImageSizeException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.image_gallery.edit_image");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}
		}
		else if (cmd != null && cmd.equals(Constants.DELETE)) {
			try {
				_deleteImage(req, res);
			}
			catch (Exception e) {
				req.setAttribute(PageContext.EXCEPTION, e);

				setForward(req, Constants.COMMON_ERROR);
			}
		}
		else if (cmd != null && cmd.equals(Constants.EDIT)) {
			try {
				_editImage(req);

				setForward(req, "portlet.image_gallery.edit_image");
			}
			catch (Exception e) {
				req.setAttribute(PageContext.EXCEPTION, e);

				setForward(req, Constants.COMMON_ERROR);
			}
		}
		else {
			setForward(req, "portlet.image_gallery.edit_image");
		}
	}

	private void _deleteImage(ActionRequest req, ActionResponse res)
		throws Exception {

		String imageId = ParamUtil.getString(req, "image_id");

		IGImageServiceUtil.deleteImage(imageId);

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

	private void _editImage(ActionRequest req) throws Exception {
		String imageId = ParamUtil.getString(req, "image_id");

		IGImage image = null;

		try {
			image = IGImageServiceUtil.getImage(imageId);
		}
		catch (NoSuchImageException nsie) {
		}

		req.setAttribute(WebKeys.IMAGE_GALLERY_IMAGE, image);
	}

	private void _updateImage(ActionRequest req, ActionResponse res)
		throws Exception {

		UploadPortletRequest uploadReq =
			PortalUtil.getUploadPortletRequest(req);

		String imageId = ParamUtil.getString(uploadReq, "image_id");

		String folderId = ParamUtil.getString(uploadReq, "folder_id");
		String description = ParamUtil.getString(uploadReq, "image_desc");

		File file = uploadReq.getFile("image_file");
		String contentType = uploadReq.getContentType("image_file");

		if (Validator.isNull(imageId)) {

			// Add image

			IGImageServiceUtil.addImage(
				folderId, description, file, contentType);
		}
		else {

			// Update image

			IGImageServiceUtil.updateImage(
				imageId, folderId, description, file, contentType);
		}

		// Send redirect

		res.sendRedirect(ParamUtil.getString(req, "redirect"));
	}

}