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

package com.liferay.portal.servlet;

import com.liferay.portal.NoSuchImageException;
import com.liferay.portal.kernel.servlet.HttpHeaders;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.model.Image;
import com.liferay.portal.model.impl.ImageImpl;
import com.liferay.portal.service.impl.ImageLocalUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.imagegallery.model.IGImage;
import com.liferay.portlet.imagegallery.service.IGImageLocalServiceUtil;
import com.liferay.util.servlet.ServletResponseUtil;

import java.io.IOException;

import java.util.Date;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ImageServlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Brett Randall
 *
 */
public class ImageServlet extends HttpServlet {

	public void service(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		long lastModified = getLastModified(req);

		if (lastModified > 0) {
			long ifModifiedSince =
				req.getDateHeader(HttpHeaders.IF_MODIFIED_SINCE);

			if ((ifModifiedSince > 0) && (ifModifiedSince == lastModified)) {
				res.setStatus(HttpServletResponse.SC_NOT_MODIFIED);

				return;
			}
		}

		//res.addHeader(HttpHeaders.CACHE_CONTROL, "max-age=0");

		if (lastModified > 0) {
			res.setDateHeader(HttpHeaders.LAST_MODIFIED, lastModified);
		}

		try {
			writeImage(req, res);
		}
		catch (NoSuchImageException nsie) {
			PortalUtil.sendError(
				HttpServletResponse.SC_NOT_FOUND, nsie, req, res);
		}
	}

	protected Image getDefaultImage(HttpServletRequest req, long imageId)
		throws NoSuchImageException {

		String path = GetterUtil.getString(req.getPathInfo());

		if (path.startsWith("/company_logo")) {
			return ImageLocalUtil.getDefaultCompanyLogo();
		}
		else if (path.startsWith("/user_portrait")) {
			return ImageLocalUtil.getDefaultUserPortrait();
		}
		else {
			throw new NoSuchImageException(
				"No default image exists for " + imageId);
		}
	}

	protected Image getImage(HttpServletRequest req, boolean getDefault)
		throws NoSuchImageException {

		long imageId = getImageId(req);

		Image image = null;

		if (imageId > 0) {
			image = ImageLocalUtil.getImage(imageId);
		}
		else {
			String uuid = ParamUtil.getString(req, "uuid");
			long groupId = ParamUtil.getLong(req, "groupId");

			try {
				IGImage igImage =
					IGImageLocalServiceUtil.getImageByUuidAndGroupId(
						uuid, groupId);

				image = ImageLocalUtil.getImage(igImage.getLargeImageId());
			}
			catch (Exception e) {
			}
		}

		if (getDefault) {
			if (image == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("Get a default image for " + imageId);
				}

				image = getDefaultImage(req, imageId);
			}
		}

		return image;
	}

	protected long getImageId(HttpServletRequest req) {

		// The image id may be passed in as image_id, img_id, or i_id

		long imageId = ParamUtil.getLong(req, "image_id");

		if (imageId <= 0) {
			imageId = ParamUtil.getLong(req, "img_id");

			if (imageId <= 0) {
				imageId = ParamUtil.getLong(req, "i_id");
			}
		}

		return imageId;
	}

	protected long getLastModified(HttpServletRequest req) {
		try {
			Image image = getImage(req, false);

			if (image == null) {
				return -1;
			}

			Date modifiedDate = image.getModifiedDate();

			if (modifiedDate == null) {
				modifiedDate = PortalUtil.UP_TIME;
			}

			// Round down and remove milliseconds

			return (modifiedDate.getTime() / 1000) * 1000;
		}
		catch (Exception e) {
			_log.error(e, e);

			return -1;
		}
	}

	protected void writeImage(HttpServletRequest req, HttpServletResponse res)
		throws IOException, NoSuchImageException, ServletException {

		Image image = getImage(req, true);

		if (image == null) {
			throw new NoSuchImageException("Image is null");
		}
		else {
			if (!image.getType().equals(ImageImpl.TYPE_NOT_AVAILABLE)) {
				res.setContentType("image/" + image.getType());
			}

			try {
				ServletResponseUtil.write(res, image.getTextObj());
			}
			catch (Exception e) {
				if (_log.isWarnEnabled()) {
					_log.warn(e, e);
				}
			}
		}
	}

	private static Log _log = LogFactory.getLog(ImageServlet.class);

}