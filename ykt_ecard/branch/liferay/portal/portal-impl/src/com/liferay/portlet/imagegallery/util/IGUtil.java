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

package com.liferay.portlet.imagegallery.util;

import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.portlet.LiferayWindowState;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portlet.imagegallery.model.IGFolder;
import com.liferay.portlet.imagegallery.model.IGImage;
import com.liferay.portlet.imagegallery.service.IGFolderLocalServiceUtil;
import com.liferay.portlet.imagegallery.service.IGImageLocalServiceUtil;

import javax.portlet.PortletURL;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import javax.portlet.WindowState;

import javax.servlet.jsp.PageContext;

/**
 * <a href="IGUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class IGUtil {

	public static String getBreadcrumbs(
			long folderId, long imageId, PageContext pageContext,
			RenderRequest req, RenderResponse res)
		throws Exception {

		if (imageId > 0) {
			IGImage image = IGImageLocalServiceUtil.getImage(imageId);

			return getBreadcrumbs(
				image.getFolder(), image, pageContext, req, res);
		}
		else {
			IGFolder folder = null;

			try {
				folder = IGFolderLocalServiceUtil.getFolder(folderId);
			}
			catch (Exception e) {
			}

			return getBreadcrumbs(folder, null, pageContext, req, res);
		}
	}

	public static String getBreadcrumbs(
			IGFolder folder, IGImage image, PageContext pageContext,
			RenderRequest req, RenderResponse res)
		throws Exception {

		if ((image != null) && (folder == null)) {
			folder = image.getFolder();
		}

		PortletURL foldersURL = res.createRenderURL();

		WindowState windowState = req.getWindowState();

		if (windowState.equals(LiferayWindowState.POP_UP)) {
			foldersURL.setWindowState(LiferayWindowState.POP_UP);

			foldersURL.setParameter(
				"struts_action", "/image_gallery/select_folder");
		}
		else {
			foldersURL.setWindowState(WindowState.MAXIMIZED);

			foldersURL.setParameter("struts_action", "/image_gallery/view");
		}

		String foldersLink =
			"<a href=\"" + foldersURL.toString() + "\">" +
				LanguageUtil.get(pageContext, "folders") + "</a>";

		if (folder == null) {
			return foldersLink;
		}

		String breadcrumbs = StringPool.BLANK;

		if (folder != null) {
			for (int i = 0;; i++) {
				folder = folder.toEscapedModel();

				PortletURL portletURL = res.createRenderURL();

				if (windowState.equals(LiferayWindowState.POP_UP)) {
					portletURL.setWindowState(LiferayWindowState.POP_UP);

					portletURL.setParameter(
						"struts_action", "/image_gallery/select_folder");
					portletURL.setParameter(
						"folderId", String.valueOf(folder.getFolderId()));
				}
				else {
					portletURL.setWindowState(WindowState.MAXIMIZED);

					portletURL.setParameter(
						"struts_action", "/image_gallery/view");
					portletURL.setParameter(
						"folderId", String.valueOf(folder.getFolderId()));
				}

				String folderLink =
					"<a href=\"" + portletURL.toString() + "\">" +
						folder.getName() + "</a>";

				if (i == 0) {
					breadcrumbs = folderLink;
				}
				else {
					breadcrumbs = folderLink + " &raquo; " + breadcrumbs;
				}

				if (folder.isRoot()) {
					break;
				}

				folder = IGFolderLocalServiceUtil.getFolder(
					folder.getParentFolderId());
			}
		}

		breadcrumbs = foldersLink + " &raquo; " + breadcrumbs;

		if (image != null) {
			image = image.toEscapedModel();

			PortletURL imageURL = res.createRenderURL();

			imageURL.setWindowState(WindowState.MAXIMIZED);

			imageURL.setParameter("struts_action", "/image_gallery/edit_image");
			imageURL.setParameter(
				"imageId", String.valueOf(image.getImageId()));

			String imageLink =
				"<a href=\"" + imageURL.toString() + "\">" +
					image.getImageId() + "</a>";

			breadcrumbs = breadcrumbs + " &raquo; " + imageLink;
		}

		return breadcrumbs;
	}

}