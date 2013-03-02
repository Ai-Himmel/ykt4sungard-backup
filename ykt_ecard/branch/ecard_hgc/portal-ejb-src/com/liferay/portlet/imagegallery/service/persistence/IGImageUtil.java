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

package com.liferay.portlet.imagegallery.service.persistence;

import com.liferay.portal.model.ModelListener;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.Validator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="IGImageUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class IGImageUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.imagegallery.model.IGImage"),
			"com.liferay.portlet.imagegallery.service.persistence.IGImagePersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.imagegallery.model.IGImage"));

	public static com.liferay.portlet.imagegallery.model.IGImage create(
		com.liferay.portlet.imagegallery.service.persistence.IGImagePK igImagePK) {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(igImagePK);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage remove(
		com.liferay.portlet.imagegallery.service.persistence.IGImagePK igImagePK)
		throws com.liferay.portlet.imagegallery.NoSuchImageException, 
			com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		if (listener != null) {
			listener.onBeforeRemove(findByPrimaryKey(igImagePK));
		}

		com.liferay.portlet.imagegallery.model.IGImage igImage = persistence.remove(igImagePK);

		if (listener != null) {
			listener.onAfterRemove(igImage);
		}

		return igImage;
	}

	public static com.liferay.portlet.imagegallery.model.IGImage update(
		com.liferay.portlet.imagegallery.model.IGImage igImage)
		throws com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = igImage.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(igImage);
			}
			else {
				listener.onBeforeUpdate(igImage);
			}
		}

		igImage = persistence.update(igImage);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(igImage);
			}
			else {
				listener.onAfterUpdate(igImage);
			}
		}

		return igImage;
	}

	public static com.liferay.portlet.imagegallery.model.IGImage findByPrimaryKey(
		com.liferay.portlet.imagegallery.service.persistence.IGImagePK igImagePK)
		throws com.liferay.portlet.imagegallery.NoSuchImageException, 
			com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(igImagePK);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.imagegallery.NoSuchImageException, 
			com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.imagegallery.NoSuchImageException, 
			com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage[] findByCompanyId_PrevAndNext(
		com.liferay.portlet.imagegallery.service.persistence.IGImagePK igImagePK,
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.imagegallery.NoSuchImageException, 
			com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(igImagePK, companyId, obc);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.imagegallery.NoSuchImageException, 
			com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.imagegallery.NoSuchImageException, 
			com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage[] findByUserId_PrevAndNext(
		com.liferay.portlet.imagegallery.service.persistence.IGImagePK igImagePK,
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.imagegallery.NoSuchImageException, 
			com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(igImagePK, userId, obc);
	}

	public static java.util.List findByC_F(java.lang.String companyId,
		java.lang.String folderId) throws com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_F(companyId, folderId);
	}

	public static java.util.List findByC_F(java.lang.String companyId,
		java.lang.String folderId, int begin, int end)
		throws com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_F(companyId, folderId, begin, end);
	}

	public static java.util.List findByC_F(java.lang.String companyId,
		java.lang.String folderId, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_F(companyId, folderId, begin, end, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage findByC_F_First(
		java.lang.String companyId, java.lang.String folderId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.imagegallery.NoSuchImageException, 
			com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_F_First(companyId, folderId, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage findByC_F_Last(
		java.lang.String companyId, java.lang.String folderId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.imagegallery.NoSuchImageException, 
			com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_F_Last(companyId, folderId, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGImage[] findByC_F_PrevAndNext(
		com.liferay.portlet.imagegallery.service.persistence.IGImagePK igImagePK,
		java.lang.String companyId, java.lang.String folderId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.imagegallery.NoSuchImageException, 
			com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_F_PrevAndNext(igImagePK, companyId,
			folderId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static void removeByC_F(java.lang.String companyId,
		java.lang.String folderId) throws com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByC_F(companyId, folderId);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	public static int countByC_F(java.lang.String companyId,
		java.lang.String folderId) throws com.liferay.portal.SystemException {
		IGImagePersistence persistence = (IGImagePersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByC_F(companyId, folderId);
	}

	private static final Log _log = LogFactory.getLog(IGImageUtil.class);
}