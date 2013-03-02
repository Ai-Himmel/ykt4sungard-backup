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

package com.liferay.portlet.documentlibrary.service.persistence;

import com.liferay.portal.model.ModelListener;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.Validator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="DLFileRankUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class DLFileRankUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.documentlibrary.model.DLFileRank"),
			"com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.documentlibrary.model.DLFileRank"));

	public static com.liferay.portlet.documentlibrary.model.DLFileRank create(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPK dlFileRankPK) {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(dlFileRankPK);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank remove(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPK dlFileRankPK)
		throws com.liferay.portlet.documentlibrary.NoSuchFileRankException, 
			com.liferay.portal.SystemException {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(dlFileRankPK));
		}

		com.liferay.portlet.documentlibrary.model.DLFileRank dlFileRank = persistence.remove(dlFileRankPK);

		if (listener != null) {
			listener.onAfterRemove(dlFileRank);
		}

		return dlFileRank;
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank update(
		com.liferay.portlet.documentlibrary.model.DLFileRank dlFileRank)
		throws com.liferay.portal.SystemException {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = dlFileRank.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(dlFileRank);
			}
			else {
				listener.onBeforeUpdate(dlFileRank);
			}
		}

		dlFileRank = persistence.update(dlFileRank);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(dlFileRank);
			}
			else {
				listener.onAfterUpdate(dlFileRank);
			}
		}

		return dlFileRank;
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank findByPrimaryKey(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPK dlFileRankPK)
		throws com.liferay.portlet.documentlibrary.NoSuchFileRankException, 
			com.liferay.portal.SystemException {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(dlFileRankPK);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.documentlibrary.NoSuchFileRankException, 
			com.liferay.portal.SystemException {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.documentlibrary.NoSuchFileRankException, 
			com.liferay.portal.SystemException {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank[] findByUserId_PrevAndNext(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPK dlFileRankPK,
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.documentlibrary.NoSuchFileRankException, 
			com.liferay.portal.SystemException {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(dlFileRankPK, userId, obc);
	}

	public static java.util.List findByC_R_FN(java.lang.String companyId,
		java.lang.String repositoryId, java.lang.String fileName)
		throws com.liferay.portal.SystemException {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_R_FN(companyId, repositoryId, fileName);
	}

	public static java.util.List findByC_R_FN(java.lang.String companyId,
		java.lang.String repositoryId, java.lang.String fileName, int begin,
		int end) throws com.liferay.portal.SystemException {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_R_FN(companyId, repositoryId, fileName,
			begin, end);
	}

	public static java.util.List findByC_R_FN(java.lang.String companyId,
		java.lang.String repositoryId, java.lang.String fileName, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_R_FN(companyId, repositoryId, fileName,
			begin, end, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank findByC_R_FN_First(
		java.lang.String companyId, java.lang.String repositoryId,
		java.lang.String fileName,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.documentlibrary.NoSuchFileRankException, 
			com.liferay.portal.SystemException {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_R_FN_First(companyId, repositoryId,
			fileName, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank findByC_R_FN_Last(
		java.lang.String companyId, java.lang.String repositoryId,
		java.lang.String fileName,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.documentlibrary.NoSuchFileRankException, 
			com.liferay.portal.SystemException {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_R_FN_Last(companyId, repositoryId, fileName,
			obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLFileRank[] findByC_R_FN_PrevAndNext(
		com.liferay.portlet.documentlibrary.service.persistence.DLFileRankPK dlFileRankPK,
		java.lang.String companyId, java.lang.String repositoryId,
		java.lang.String fileName,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.documentlibrary.NoSuchFileRankException, 
			com.liferay.portal.SystemException {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_R_FN_PrevAndNext(dlFileRankPK, companyId,
			repositoryId, fileName, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static void removeByC_R_FN(java.lang.String companyId,
		java.lang.String repositoryId, java.lang.String fileName)
		throws com.liferay.portal.SystemException {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByC_R_FN(companyId, repositoryId, fileName);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	public static int countByC_R_FN(java.lang.String companyId,
		java.lang.String repositoryId, java.lang.String fileName)
		throws com.liferay.portal.SystemException {
		DLFileRankPersistence persistence = (DLFileRankPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByC_R_FN(companyId, repositoryId, fileName);
	}

	private static final Log _log = LogFactory.getLog(DLFileRankUtil.class);
}