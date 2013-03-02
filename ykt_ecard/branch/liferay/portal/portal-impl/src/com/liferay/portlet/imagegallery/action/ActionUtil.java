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

package com.liferay.portlet.imagegallery.action;

import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.imagegallery.model.IGFolder;
import com.liferay.portlet.imagegallery.model.IGImage;
import com.liferay.portlet.imagegallery.model.impl.IGFolderImpl;
import com.liferay.portlet.imagegallery.service.IGFolderServiceUtil;
import com.liferay.portlet.imagegallery.service.IGImageServiceUtil;

import javax.portlet.ActionRequest;
import javax.portlet.RenderRequest;

import javax.servlet.http.HttpServletRequest;

/**
 * <a href="ActionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ActionUtil {

	public static void getFolder(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getFolder(httpReq);
	}

	public static void getFolder(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getFolder(httpReq);
	}

	public static void getFolder(HttpServletRequest req) throws Exception {
		long folderId = ParamUtil.getLong(req, "folderId");

		IGFolder folder = null;

		if ((folderId > 0) &&
			(folderId != IGFolderImpl.DEFAULT_PARENT_FOLDER_ID)) {

			folder = IGFolderServiceUtil.getFolder(folderId);
		}

		req.setAttribute(WebKeys.IMAGE_GALLERY_FOLDER, folder);
	}

	public static void getImage(ActionRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getImage(httpReq);
	}

	public static void getImage(RenderRequest req) throws Exception {
		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		getImage(httpReq);
	}

	public static void getImage(HttpServletRequest req) throws Exception {
		long imageId = ParamUtil.getLong(req, "imageId");

		IGImage image = null;

		if (imageId > 0) {
			image = IGImageServiceUtil.getImage(imageId);
		}

		req.setAttribute(WebKeys.IMAGE_GALLERY_IMAGE, image);
	}

}