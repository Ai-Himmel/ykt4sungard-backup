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
 * <a href="DLRepositoryUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class DLRepositoryUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.documentlibrary.model.DLRepository"),
			"com.liferay.portlet.documentlibrary.service.persistence.DLRepositoryPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.documentlibrary.model.DLRepository"));

	public static com.liferay.portlet.documentlibrary.model.DLRepository create(
		java.lang.String repositoryId) {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(repositoryId);
	}

	public static com.liferay.portlet.documentlibrary.model.DLRepository remove(
		java.lang.String repositoryId)
		throws com.liferay.portlet.documentlibrary.NoSuchRepositoryException, 
			com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(repositoryId));
		}

		com.liferay.portlet.documentlibrary.model.DLRepository dlRepository = persistence.remove(repositoryId);

		if (listener != null) {
			listener.onAfterRemove(dlRepository);
		}

		return dlRepository;
	}

	public static com.liferay.portlet.documentlibrary.model.DLRepository update(
		com.liferay.portlet.documentlibrary.model.DLRepository dlRepository)
		throws com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = dlRepository.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(dlRepository);
			}
			else {
				listener.onBeforeUpdate(dlRepository);
			}
		}

		dlRepository = persistence.update(dlRepository);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(dlRepository);
			}
			else {
				listener.onAfterUpdate(dlRepository);
			}
		}

		return dlRepository;
	}

	public static com.liferay.portlet.documentlibrary.model.DLRepository findByPrimaryKey(
		java.lang.String repositoryId)
		throws com.liferay.portlet.documentlibrary.NoSuchRepositoryException, 
			com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(repositoryId);
	}

	public static java.util.List findByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId);
	}

	public static java.util.List findByGroupId(java.lang.String groupId,
		int begin, int end) throws com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId, begin, end);
	}

	public static java.util.List findByGroupId(java.lang.String groupId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId(groupId, begin, end, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLRepository findByGroupId_First(
		java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.documentlibrary.NoSuchRepositoryException, 
			com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLRepository findByGroupId_Last(
		java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.documentlibrary.NoSuchRepositoryException, 
			com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLRepository[] findByGroupId_PrevAndNext(
		java.lang.String repositoryId, java.lang.String groupId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.documentlibrary.NoSuchRepositoryException, 
			com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByGroupId_PrevAndNext(repositoryId, groupId, obc);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLRepository findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.documentlibrary.NoSuchRepositoryException, 
			com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLRepository findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.documentlibrary.NoSuchRepositoryException, 
			com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLRepository[] findByCompanyId_PrevAndNext(
		java.lang.String repositoryId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.documentlibrary.NoSuchRepositoryException, 
			com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(repositoryId, companyId,
			obc);
	}

	public static java.util.List findByG_C(java.lang.String groupId,
		java.lang.String companyId) throws com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C(groupId, companyId);
	}

	public static java.util.List findByG_C(java.lang.String groupId,
		java.lang.String companyId, int begin, int end)
		throws com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C(groupId, companyId, begin, end);
	}

	public static java.util.List findByG_C(java.lang.String groupId,
		java.lang.String companyId, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C(groupId, companyId, begin, end, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLRepository findByG_C_First(
		java.lang.String groupId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.documentlibrary.NoSuchRepositoryException, 
			com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C_First(groupId, companyId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLRepository findByG_C_Last(
		java.lang.String groupId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.documentlibrary.NoSuchRepositoryException, 
			com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C_Last(groupId, companyId, obc);
	}

	public static com.liferay.portlet.documentlibrary.model.DLRepository[] findByG_C_PrevAndNext(
		java.lang.String repositoryId, java.lang.String groupId,
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.documentlibrary.NoSuchRepositoryException, 
			com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByG_C_PrevAndNext(repositoryId, groupId,
			companyId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByGroupId(groupId);
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByG_C(java.lang.String groupId,
		java.lang.String companyId) throws com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByG_C(groupId, companyId);
	}

	public static int countByGroupId(java.lang.String groupId)
		throws com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByGroupId(groupId);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByG_C(java.lang.String groupId,
		java.lang.String companyId) throws com.liferay.portal.SystemException {
		DLRepositoryPersistence persistence = (DLRepositoryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByG_C(groupId, companyId);
	}

	private static final Log _log = LogFactory.getLog(DLRepositoryUtil.class);
}