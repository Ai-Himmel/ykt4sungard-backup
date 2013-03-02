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

package com.liferay.portal.service.impl;

import com.liferay.portal.NoSuchImageException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Image;
import com.liferay.portal.service.base.ImageLocalServiceBaseImpl;

import java.util.Date;
import java.util.List;

/**
 * <a href="ImageLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ImageLocalServiceImpl extends ImageLocalServiceBaseImpl {

	public void deleteImage(long imageId) throws SystemException {
		try {
			if (imageId > 0) {
				imagePersistence.remove(imageId);
			}
		}
		catch (NoSuchImageException nsie) {
		}
	}

	public Image getImage(long imageId)
		throws PortalException, SystemException {

		return imagePersistence.findByPrimaryKey(imageId);
	}

	public List getImages() throws SystemException {
		return imagePersistence.findAll();
	}

	public List getImages(int begin, int end) throws SystemException {
		return imagePersistence.findAll(begin, end);
	}

	public List getImagesBySize(int size) throws SystemException {
		return imagePersistence.findBySize(size);
	}

	public Image updateImage(
			long imageId, byte[] bytes, String type, int height, int width,
			int size)
		throws SystemException {

		Image image = imagePersistence.fetchByPrimaryKey(imageId);

		if (image == null) {
			image = imagePersistence.create(imageId);
		}

		image.setModifiedDate(new Date());
		image.setTextObj(bytes);
		image.setType(type);
		image.setHeight(height);
		image.setWidth(width);
		image.setSize(size);

		imagePersistence.update(image);

		return image;
	}

}