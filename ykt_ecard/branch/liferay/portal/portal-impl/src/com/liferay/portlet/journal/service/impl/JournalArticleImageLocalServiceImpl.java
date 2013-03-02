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

package com.liferay.portlet.journal.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.service.impl.ImageLocalUtil;
import com.liferay.portlet.journal.DuplicateArticleImageIdException;
import com.liferay.portlet.journal.NoSuchArticleImageException;
import com.liferay.portlet.journal.model.JournalArticleImage;
import com.liferay.portlet.journal.service.base.JournalArticleImageLocalServiceBaseImpl;

import java.util.Iterator;
import java.util.List;

/**
 * <a href="JournalArticleImageLocalServiceImpl.java.html"><b><i>View Source</i>
 * </b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalArticleImageLocalServiceImpl
	extends JournalArticleImageLocalServiceBaseImpl {

	public void addArticleImageId(
			long articleImageId, long groupId, String articleId, double version,
			String elName, String languageId)
		throws PortalException, SystemException {

		if (articleImageId <= 0) {
			return;
		}

		JournalArticleImage articleImage =
			journalArticleImagePersistence.fetchByG_A_V_E_L(
				groupId, articleId, version, elName, languageId);

		if (articleImage == null) {
			articleImage = journalArticleImagePersistence.create(
				articleImageId);

			articleImage.setGroupId(groupId);
			articleImage.setArticleId(articleId);
			articleImage.setVersion(version);
			articleImage.setElName(elName);
			articleImage.setLanguageId(languageId);
			articleImage.setTempImage(false);

			journalArticleImagePersistence.update(articleImage);
		}
		else if (articleImage.getArticleImageId() == articleImageId) {
		}
		else {
			throw new DuplicateArticleImageIdException();
		}
	}

	public void deleteArticleImage(long articleImageId) throws SystemException {
		try {
			journalArticleImagePersistence.remove(articleImageId);
		}
		catch (NoSuchArticleImageException nsaie) {
		}
	}

	public void deleteArticleImage(
			long groupId, String articleId, double version, String elName,
			String languageId)
		throws SystemException {

		try {
			journalArticleImagePersistence.removeByG_A_V_E_L(
				groupId, articleId, version, elName, languageId);
		}
		catch (NoSuchArticleImageException nsaie) {
		}
	}

	public void deleteImages(long groupId, String articleId, double version)
		throws SystemException {

		Iterator itr = journalArticleImagePersistence.findByG_A_V(
			groupId, articleId, version).iterator();

		while (itr.hasNext()) {
			JournalArticleImage articleImage = (JournalArticleImage)itr.next();

			ImageLocalUtil.deleteImage(articleImage.getArticleImageId());

			journalArticleImagePersistence.remove(articleImage);
		}
	}

	public JournalArticleImage getArticleImage(long articleImageId)
		throws PortalException, SystemException {

		return journalArticleImagePersistence.findByPrimaryKey(articleImageId);
	}

	public long getArticleImageId(
			long groupId, String articleId, double version, String elName,
			String languageId)
		throws SystemException {

		return getArticleImageId(
			groupId, articleId, version, elName, languageId, false);
	}

	public long getArticleImageId(
			long groupId, String articleId, double version, String elName,
			String languageId, boolean tempImage)
		throws SystemException {

		JournalArticleImage articleImage =
			journalArticleImagePersistence.fetchByG_A_V_E_L(
				groupId, articleId, version, elName, languageId);

		if (articleImage == null) {
			long articleImageId = counterLocalService.increment();

			articleImage = journalArticleImagePersistence.create(
				articleImageId);

			articleImage.setGroupId(groupId);
			articleImage.setArticleId(articleId);
			articleImage.setVersion(version);
			articleImage.setElName(elName);
			articleImage.setLanguageId(languageId);
			articleImage.setTempImage(tempImage);

			journalArticleImagePersistence.update(articleImage);
		}

		return articleImage.getArticleImageId();
	}

	public List getArticleImages(long groupId) throws SystemException {
		return journalArticleImagePersistence.findByGroupId(groupId);
	}

}