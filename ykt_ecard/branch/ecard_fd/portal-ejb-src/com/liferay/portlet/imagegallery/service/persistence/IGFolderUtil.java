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
 * <a href="IGFolderUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class IGFolderUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.imagegallery.model.IGFolder"),
			"com.liferay.portlet.imagegallery.service.persistence.IGFolderPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.imagegallery.model.IGFolder"));

	public static com.liferay.portlet.imagegallery.model.IGFolder create(
		java.lang.String folderId) {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(folderId);
	}

	public static com.liferay.portlet.imagegallery.model.IGFolder remove(
		java.lang.String folderId)
		throws com.liferay.portlet.imagegallery.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(folderId));
		}

		com.liferay.portlet.imagegallery.model.IGFolder igFolder = persistence.remove(folderId);

		if (listener != null) {
			listener.onAfterRemove(igFolder);
		}

		return igFolder;
	}

	public static com.liferay.portlet.imagegallery.model.IGFolder update(
		com.liferay.portlet.imagegallery.model.IGFolder igFolder)
		throws com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = igFolder.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(igFolder);
			}
			else {
				listener.onBeforeUpdate(igFolder);
			}
		}

		igFolder = persistence.update(igFolder);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(igFolder);
			}
			else {
				listener.onAfterUpdate(igFolder);
			}
		}

		return igFolder;
	}

	public static com.liferay.portlet.imagegallery.model.IGFolder findByPrimaryKey(
		java.lang.String folderId)
		throws com.liferay.portlet.imagegallery.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(folderId);
	}

	public static java.util.List findByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId);
	}

	public static java.util.List findByGroupId(java.lang.String groupId,
		int begin, int end) throws com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId, begin, end);
	}

	public static java.util.List findByGroupId(java.lang.String groupId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId, begin, end, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGFolder findByGroupId_First(
		java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.imagegallery.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGFolder findByGroupId_Last(
		java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.imagegallery.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGFolder[] findByGroupId_PrevAndNext(
		java.lang.String folderId, java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.imagegallery.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_PrevAndNext(folderId, groupId, obc);
	}

	public static java.util.List findByG_C(java.lang.String groupId,
		java.lang.String companyId) throws com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C(groupId, companyId);
	}

	public static java.util.List findByG_C(java.lang.String groupId,
		java.lang.String companyId, int begin, int end)
		throws com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C(groupId, companyId, begin, end);
	}

	public static java.util.List findByG_C(java.lang.String groupId,
		java.lang.String companyId, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C(groupId, companyId, begin, end, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGFolder findByG_C_First(
		java.lang.String groupId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.imagegallery.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C_First(groupId, companyId, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGFolder findByG_C_Last(
		java.lang.String groupId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.imagegallery.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C_Last(groupId, companyId, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGFolder[] findByG_C_PrevAndNext(
		java.lang.String folderId, java.lang.String groupId,
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.imagegallery.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C_PrevAndNext(folderId, groupId, companyId,
			obc);
	}

	public static java.util.List findByG_C_P(java.lang.String groupId,
		java.lang.String companyId, java.lang.String parentFolderId)
		throws com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C_P(groupId, companyId, parentFolderId);
	}

	public static java.util.List findByG_C_P(java.lang.String groupId,
		java.lang.String companyId, java.lang.String parentFolderId, int begin,
		int end) throws com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C_P(groupId, companyId, parentFolderId,
			begin, end);
	}

	public static java.util.List findByG_C_P(java.lang.String groupId,
		java.lang.String companyId, java.lang.String parentFolderId, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C_P(groupId, companyId, parentFolderId,
			begin, end, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGFolder findByG_C_P_First(
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String parentFolderId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.imagegallery.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C_P_First(groupId, companyId,
			parentFolderId, obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGFolder findByG_C_P_Last(
		java.lang.String groupId, java.lang.String companyId,
		java.lang.String parentFolderId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.imagegallery.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C_P_Last(groupId, companyId, parentFolderId,
			obc);
	}

	public static com.liferay.portlet.imagegallery.model.IGFolder[] findByG_C_P_PrevAndNext(
		java.lang.String folderId, java.lang.String groupId,
		java.lang.String companyId, java.lang.String parentFolderId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.imagegallery.NoSuchFolderException, 
			com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C_P_PrevAndNext(folderId, groupId,
			companyId, parentFolderId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByGroupId(groupId);
	}

	public static void removeByG_C(java.lang.String groupId,
		java.lang.String companyId) throws com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByG_C(groupId, companyId);
	}

	public static void removeByG_C_P(java.lang.String groupId,
		java.lang.String companyId, java.lang.String parentFolderId)
		throws com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByG_C_P(groupId, companyId, parentFolderId);
	}

	public static int countByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByGroupId(groupId);
	}

	public static int countByG_C(java.lang.String groupId,
		java.lang.String companyId) throws com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByG_C(groupId, companyId);
	}

	public static int countByG_C_P(java.lang.String groupId,
		java.lang.String companyId, java.lang.String parentFolderId)
		throws com.liferay.portal.SystemException {
		IGFolderPersistence persistence = (IGFolderPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByG_C_P(groupId, companyId, parentFolderId);
	}

	private static final Log _log = LogFactory.getLog(IGFolderUtil.class);
}