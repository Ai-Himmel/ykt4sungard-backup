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

package com.liferay.portal.verify;

import com.liferay.portal.NoSuchCompanyException;
import com.liferay.portal.NoSuchLayoutException;
import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.model.Image;
import com.liferay.portal.service.CompanyLocalServiceUtil;
import com.liferay.portal.service.ImageLocalServiceUtil;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portlet.imagegallery.NoSuchImageException;
import com.liferay.portlet.imagegallery.service.IGImageLocalServiceUtil;
import com.liferay.portlet.journal.NoSuchArticleImageException;
import com.liferay.portlet.journal.NoSuchTemplateException;
import com.liferay.portlet.journal.service.JournalArticleImageLocalServiceUtil;
import com.liferay.portlet.journal.service.JournalArticleLocalServiceUtil;
import com.liferay.portlet.journal.service.JournalTemplateLocalServiceUtil;
import com.liferay.portlet.shopping.NoSuchItemException;
import com.liferay.portlet.shopping.service.ShoppingItemLocalServiceUtil;
import com.liferay.portlet.softwarecatalog.NoSuchProductScreenshotException;
import com.liferay.portlet.softwarecatalog.service.SCProductScreenshotLocalServiceUtil;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="VerifyImage.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * This class is very powerful because it removes all images that it believes
 * is stale. Do not run this unless you are also not managing images in
 * Liferay's Image service for your custom models.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class VerifyImage extends VerifyProcess {

	public void verify() throws VerifyException {
		_log.info("Verifying integrity");

		try {
			verifyImage();
		}
		catch (Exception e) {
			throw new VerifyException(e);
		}
	}

	protected boolean isStaleImage(Image image) throws Exception {
		long imageId = image.getImageId();

		try {
			CompanyLocalServiceUtil.getCompanyByLogoId(imageId);

			return false;
		}
		catch (NoSuchCompanyException nsce) {
		}

		try {
			LayoutLocalServiceUtil.getLayoutByIconImageId(imageId);

			return false;
		}
		catch (NoSuchLayoutException nsle) {
		}

		try {
			UserLocalServiceUtil.getUserByPortraitId(imageId);

			return false;
		}
		catch (NoSuchUserException nsue) {
		}

		try {
			IGImageLocalServiceUtil.getImageBySmallImageId(imageId);

			return false;
		}
		catch (NoSuchImageException nsie) {
		}

		try {
			IGImageLocalServiceUtil.getImageByLargeImageId(imageId);

			return false;
		}
		catch (NoSuchImageException nsie) {
		}

		List journalArticles =
			JournalArticleLocalServiceUtil.getArticlesBySmallImageId(imageId);

		if (journalArticles.size() > 0) {
			return false;
		}

		try {
			JournalArticleImageLocalServiceUtil.getArticleImage(imageId);

			return false;
		}
		catch (NoSuchArticleImageException nsaie) {
		}

		try {
			JournalTemplateLocalServiceUtil.getTemplateBySmallImageId(imageId);

			return false;
		}
		catch (NoSuchTemplateException nste) {
		}

		try {
			SCProductScreenshotLocalServiceUtil.
				getProductScreenshotByFullImageId(imageId);

			return false;
		}
		catch (NoSuchProductScreenshotException nspse) {
		}

		try {
			SCProductScreenshotLocalServiceUtil.
				getProductScreenshotByThumbnailId(imageId);

			return false;
		}
		catch (NoSuchProductScreenshotException nspse) {
		}

		try {
			ShoppingItemLocalServiceUtil.getItemByLargeImageId(imageId);

			return false;
		}
		catch (NoSuchItemException nsie) {
		}

		try {
			ShoppingItemLocalServiceUtil.getItemByMediumImageId(imageId);

			return false;
		}
		catch (NoSuchItemException nsie) {
		}

		try {
			ShoppingItemLocalServiceUtil.getItemBySmallImageId(imageId);

			return false;
		}
		catch (NoSuchItemException nsie) {
		}

		return true;
	}

	protected void verifyImage() throws Exception {
		List images = ImageLocalServiceUtil.getImages();

		if (_log.isDebugEnabled()) {
			_log.debug("Processing " + images.size() + " stale images");
		}

		for (int i = 0; i < images.size(); i++) {
			Image image = (Image)images.get(i);

			if (isStaleImage(image)) {
				if (_log.isInfoEnabled()) {
					_log.info("Deleting stale image " + image.getImageId());
				}

				ImageLocalServiceUtil.deleteImage(image.getImageId());
			}
		}
	}

	private static Log _log = LogFactory.getLog(VerifyImage.class);

}