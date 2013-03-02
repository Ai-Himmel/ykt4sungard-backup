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

package com.liferay.portlet.imagegallery.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.ImageLocalUtil;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.imagegallery.ImageNameException;
import com.liferay.portlet.imagegallery.ImageSizeException;
import com.liferay.portlet.imagegallery.NoSuchFolderException;
import com.liferay.portlet.imagegallery.model.IGFolder;
import com.liferay.portlet.imagegallery.model.IGImage;
import com.liferay.portlet.imagegallery.service.persistence.IGFolderUtil;
import com.liferay.portlet.imagegallery.service.persistence.IGImagePK;
import com.liferay.portlet.imagegallery.service.persistence.IGImageUtil;
import com.liferay.portlet.imagegallery.service.spring.IGImageService;
import com.liferay.util.FileUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.ImageUtil;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.dao.hibernate.OrderByComparator;

import java.awt.image.BufferedImage;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;

import java.util.Date;
import java.util.List;

import javax.imageio.ImageIO;

/**
 * <a href="IGImageServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class IGImageServiceImpl
	extends PrincipalBean implements IGImageService {

	// Business methods

	public IGImage addImage(
			String folderId, String description, File file, String contentType)
		throws PortalException, SystemException {

		try {
			folderId = _getFolderId(folderId);
			byte[] bytes = FileUtil.getBytes(file);

			_validate(folderId, file, bytes);

			User user = getUser();

			String imageId = Long.toString(CounterServiceUtil.increment(
				IGImage.class.getName() + "." + user.getCompanyId()));

			IGImagePK pk = new IGImagePK(imageId, user.getCompanyId());

			IGImage image = IGImageUtil.create(pk);

			Date now = new Date();

			BufferedImage bufferedImage = ImageIO.read(file);

			image.setCompanyId(pk.companyId);
			image.setUserId(user.getUserId());
			image.setCreateDate(now);
			image.setModifiedDate(now);
			image.setFolderId(folderId);
			image.setDescription(description);
			image.setHeight(bufferedImage.getHeight());
			image.setWidth(bufferedImage.getWidth());
			image.setSize(bytes.length);

			IGImageUtil.update(image);

			// Save images

			_saveImages(
				image.getLargeImageId(), bufferedImage, image.getSmallImageId(),
				file, bytes, contentType);

			return image;
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
	}

	public void deleteImage(String imageId)
		throws PortalException, SystemException {

		IGImagePK pk = new IGImagePK(imageId, getUser().getCompanyId());

		IGImage image = IGImageUtil.findByPrimaryKey(pk);

		deleteImage(image);
	}

	public void deleteImage(IGImage image)
		throws PortalException, SystemException {

		IGImagePK pk = image.getPrimaryKey();

		IGImageUtil.remove(pk);

		// Remove images

		ImageLocalUtil.remove(image.getLargeImageId());
		ImageLocalUtil.remove(image.getSmallImageId());
	}

	public IGImage getImage(String imageId)
		throws PortalException, SystemException {

		IGImagePK pk = new IGImagePK(imageId, getUser().getCompanyId());

		IGImage image = IGImageUtil.findByPrimaryKey(pk);

		return image;
	}

	public List getImages(String companyId) throws SystemException {
		return IGImageUtil.findByCompanyId(companyId);
	}

	public List getImages(IGFolder folder) throws SystemException {
		return IGImageUtil.findByC_F(
			folder.getCompanyId(), folder.getFolderId());
	}

	public List getImages(IGFolder folder, int begin, int end)
		throws SystemException {

		return IGImageUtil.findByC_F(
			folder.getCompanyId(), folder.getFolderId(), begin, end);
	}

	public List getImages(
			IGFolder folder, int begin, int end, OrderByComparator obc)
		throws SystemException {

		return IGImageUtil.findByC_F(
			folder.getCompanyId(), folder.getFolderId(), begin, end, obc);
	}

	public int getImagesSize(String companyId) throws SystemException {
		return IGImageUtil.countByCompanyId(companyId);
	}

	public int getImagesSize(IGFolder folder) throws SystemException {
		return IGImageUtil.countByC_F(
			folder.getCompanyId(), folder.getFolderId());
	}

	public IGImage updateImage(
			String imageId, String folderId, String description, File file,
			String contentType)
		throws PortalException, SystemException {

		try {
			folderId = _getFolderId(folderId);
			byte[] bytes = FileUtil.getBytes(file);

			_validate(folderId, file, bytes);

			IGImagePK pk = new IGImagePK(imageId, getUser().getCompanyId());

			IGImage image = IGImageUtil.findByPrimaryKey(pk);

			BufferedImage bufferedImage = ImageIO.read(file);

			image.setModifiedDate(new Date());
			image.setFolderId(folderId);
			image.setDescription(description);
			image.setHeight(bufferedImage.getHeight());
			image.setWidth(bufferedImage.getWidth());
			image.setSize(bytes.length);

			IGImageUtil.update(image);

			// Save images

			_saveImages(
				image.getLargeImageId(), bufferedImage, image.getSmallImageId(),
				file, bytes, contentType);

			return image;
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
	}

	// Private methods

	private String _getFolderId(String folderId)
		throws PortalException, SystemException {

		if (!folderId.equals(IGFolder.DEFAULT_PARENT_FOLDER_ID)) {

			// Ensure folder exists and belongs to the proper company

			try {
				IGFolder folder = IGFolderUtil.findByPrimaryKey(folderId);

				if (!folder.getCompanyId().equals(getUser().getCompanyId())) {
					folderId = IGFolder.DEFAULT_PARENT_FOLDER_ID;
				}
			}
			catch (NoSuchFolderException nsfe) {
				folderId = IGFolder.DEFAULT_PARENT_FOLDER_ID;
			}
		}

		return folderId;
	}

	private void _saveImages(
			String imageKey, BufferedImage bufferedImage, String thumbnailKey,
			File file, byte[] bytes, String contentType)
		throws SystemException {

		try {

			// Save image

			ImageLocalUtil.put(imageKey, bytes);

			// Create thumbnail

			BufferedImage thumbnail = ImageUtil.scale(bufferedImage, 50);

			ByteArrayOutputStream baos = new ByteArrayOutputStream();

			if (contentType.indexOf("gif") != -1) {
				ImageUtil.encodeGIF(thumbnail, baos);
			}
			else if (contentType.indexOf("jpg") != -1 ||
					 contentType.indexOf("jpeg") != -1) {

				ImageIO.write(thumbnail, "jpeg", baos);
			}
			else if (contentType.indexOf("png") != -1) {
				ImageIO.write(thumbnail, "png", baos);
			}

			// Save thumbnail

			ImageLocalUtil.put(thumbnailKey, baos.toByteArray());
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
	}

	private void _validate(String folderId, File file, byte[] bytes)
		throws PortalException, SystemException {

		IGFolder folder = IGFolderUtil.findByPrimaryKey(folderId);

		String imageName = StringPool.BLANK;
		if (file != null) {
			imageName = file.getName();
		}

		boolean validImageExtension = false;

		String[] imageExtensions =
			PropsUtil.getArray(PropsUtil.IG_IMAGE_EXTENSIONS);

		for (int i = 0; i < imageExtensions.length; i++) {
			if (StringPool.STAR.equals(imageExtensions[i]) ||
				StringUtil.endsWith(imageName, imageExtensions[i])) {

				validImageExtension = true;

				break;
			}
		}

		if (!validImageExtension) {
			throw new ImageNameException(imageName);
		}

		long imageMaxSize = GetterUtil.getLong(
			PropsUtil.get(PropsUtil.IG_IMAGE_MAX_SIZE));

		if ((imageMaxSize > 0) &&
			((bytes == null) || (bytes.length > imageMaxSize))) {

			throw new ImageSizeException();
		}
	}

}