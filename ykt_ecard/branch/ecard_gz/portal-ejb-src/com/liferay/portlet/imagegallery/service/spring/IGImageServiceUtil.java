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

package com.liferay.portlet.imagegallery.service.spring;

/**
 * <a href="IGImageServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class IGImageServiceUtil {
	public static com.liferay.portlet.imagegallery.model.IGImage addImage(
		java.lang.String folderId, java.lang.String description,
		java.io.File file, java.lang.String contentType)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			IGImageService igImageService = IGImageServiceFactory.getService();

			return igImageService.addImage(folderId, description, file,
				contentType);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteImage(java.lang.String imageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			IGImageService igImageService = IGImageServiceFactory.getService();
			igImageService.deleteImage(imageId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static void deleteImage(
		com.liferay.portlet.imagegallery.model.IGImage image)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			IGImageService igImageService = IGImageServiceFactory.getService();
			igImageService.deleteImage(image);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.imagegallery.model.IGImage getImage(
		java.lang.String imageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			IGImageService igImageService = IGImageServiceFactory.getService();

			return igImageService.getImage(imageId);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getImages(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		try {
			IGImageService igImageService = IGImageServiceFactory.getService();

			return igImageService.getImages(companyId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getImages(
		com.liferay.portlet.imagegallery.model.IGFolder folder)
		throws com.liferay.portal.SystemException {
		try {
			IGImageService igImageService = IGImageServiceFactory.getService();

			return igImageService.getImages(folder);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getImages(
		com.liferay.portlet.imagegallery.model.IGFolder folder, int begin,
		int end) throws com.liferay.portal.SystemException {
		try {
			IGImageService igImageService = IGImageServiceFactory.getService();

			return igImageService.getImages(folder, begin, end);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static java.util.List getImages(
		com.liferay.portlet.imagegallery.model.IGFolder folder, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		try {
			IGImageService igImageService = IGImageServiceFactory.getService();

			return igImageService.getImages(folder, begin, end, obc);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int getImagesSize(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		try {
			IGImageService igImageService = IGImageServiceFactory.getService();

			return igImageService.getImagesSize(companyId);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static int getImagesSize(
		com.liferay.portlet.imagegallery.model.IGFolder folder)
		throws com.liferay.portal.SystemException {
		try {
			IGImageService igImageService = IGImageServiceFactory.getService();

			return igImageService.getImagesSize(folder);
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}

	public static com.liferay.portlet.imagegallery.model.IGImage updateImage(
		java.lang.String imageId, java.lang.String folderId,
		java.lang.String description, java.io.File file,
		java.lang.String contentType)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			IGImageService igImageService = IGImageServiceFactory.getService();

			return igImageService.updateImage(imageId, folderId, description,
				file, contentType);
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			throw new com.liferay.portal.SystemException(e);
		}
	}
}