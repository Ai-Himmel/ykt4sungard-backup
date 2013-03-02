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

package com.liferay.portlet.blogs.service.persistence;

import com.liferay.portal.model.ModelListener;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.Validator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="BlogsEntryUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsEntryUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.blogs.model.BlogsEntry"),
			"com.liferay.portlet.blogs.service.persistence.BlogsEntryPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.blogs.model.BlogsEntry"));

	public static com.liferay.portlet.blogs.model.BlogsEntry create(
		java.lang.String entryId) {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(entryId);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry remove(
		java.lang.String entryId)
		throws com.liferay.portlet.blogs.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(entryId));
		}

		com.liferay.portlet.blogs.model.BlogsEntry blogsEntry = persistence.remove(entryId);

		if (listener != null) {
			listener.onAfterRemove(blogsEntry);
		}

		return blogsEntry;
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry update(
		com.liferay.portlet.blogs.model.BlogsEntry blogsEntry)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = blogsEntry.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(blogsEntry);
			}
			else {
				listener.onBeforeUpdate(blogsEntry);
			}
		}

		blogsEntry = persistence.update(blogsEntry);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(blogsEntry);
			}
			else {
				listener.onAfterUpdate(blogsEntry);
			}
		}

		return blogsEntry;
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByPrimaryKey(
		java.lang.String entryId)
		throws com.liferay.portlet.blogs.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(entryId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry[] findByCompanyId_PrevAndNext(
		java.lang.String entryId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(entryId, companyId, obc);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry[] findByUserId_PrevAndNext(
		java.lang.String entryId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(entryId, userId, obc);
	}

	public static java.util.List findByCategoryId(java.lang.String categoryId)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCategoryId(categoryId);
	}

	public static java.util.List findByCategoryId(java.lang.String categoryId,
		int begin, int end) throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCategoryId(categoryId, begin, end);
	}

	public static java.util.List findByCategoryId(java.lang.String categoryId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCategoryId(categoryId, begin, end, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByCategoryId_First(
		java.lang.String categoryId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCategoryId_First(categoryId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByCategoryId_Last(
		java.lang.String categoryId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCategoryId_Last(categoryId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry[] findByCategoryId_PrevAndNext(
		java.lang.String entryId, java.lang.String categoryId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCategoryId_PrevAndNext(entryId, categoryId, obc);
	}

	public static java.util.List findByU_C(java.lang.String userId,
		java.lang.String categoryId) throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_C(userId, categoryId);
	}

	public static java.util.List findByU_C(java.lang.String userId,
		java.lang.String categoryId, int begin, int end)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_C(userId, categoryId, begin, end);
	}

	public static java.util.List findByU_C(java.lang.String userId,
		java.lang.String categoryId, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_C(userId, categoryId, begin, end, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByU_C_First(
		java.lang.String userId, java.lang.String categoryId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_C_First(userId, categoryId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByU_C_Last(
		java.lang.String userId, java.lang.String categoryId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_C_Last(userId, categoryId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry[] findByU_C_PrevAndNext(
		java.lang.String entryId, java.lang.String userId,
		java.lang.String categoryId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_C_PrevAndNext(entryId, userId, categoryId,
			obc);
	}

	public static java.util.List findByU_S(java.lang.String userId,
		boolean sharing) throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S(userId, sharing);
	}

	public static java.util.List findByU_S(java.lang.String userId,
		boolean sharing, int begin, int end)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S(userId, sharing, begin, end);
	}

	public static java.util.List findByU_S(java.lang.String userId,
		boolean sharing, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S(userId, sharing, begin, end, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByU_S_First(
		java.lang.String userId, boolean sharing,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S_First(userId, sharing, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByU_S_Last(
		java.lang.String userId, boolean sharing,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S_Last(userId, sharing, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry[] findByU_S_PrevAndNext(
		java.lang.String entryId, java.lang.String userId, boolean sharing,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_S_PrevAndNext(entryId, userId, sharing, obc);
	}

	public static java.util.List findByU_C_S(java.lang.String userId,
		java.lang.String categoryId, boolean sharing)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_C_S(userId, categoryId, sharing);
	}

	public static java.util.List findByU_C_S(java.lang.String userId,
		java.lang.String categoryId, boolean sharing, int begin, int end)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_C_S(userId, categoryId, sharing, begin, end);
	}

	public static java.util.List findByU_C_S(java.lang.String userId,
		java.lang.String categoryId, boolean sharing, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_C_S(userId, categoryId, sharing, begin, end,
			obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByU_C_S_First(
		java.lang.String userId, java.lang.String categoryId, boolean sharing,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_C_S_First(userId, categoryId, sharing, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry findByU_C_S_Last(
		java.lang.String userId, java.lang.String categoryId, boolean sharing,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_C_S_Last(userId, categoryId, sharing, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsEntry[] findByU_C_S_PrevAndNext(
		java.lang.String entryId, java.lang.String userId,
		java.lang.String categoryId, boolean sharing,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchEntryException, 
			com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_C_S_PrevAndNext(entryId, userId, categoryId,
			sharing, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static void removeByCategoryId(java.lang.String categoryId)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCategoryId(categoryId);
	}

	public static void removeByU_C(java.lang.String userId,
		java.lang.String categoryId) throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByU_C(userId, categoryId);
	}

	public static void removeByU_S(java.lang.String userId, boolean sharing)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByU_S(userId, sharing);
	}

	public static void removeByU_C_S(java.lang.String userId,
		java.lang.String categoryId, boolean sharing)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByU_C_S(userId, categoryId, sharing);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	public static int countByCategoryId(java.lang.String categoryId)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCategoryId(categoryId);
	}

	public static int countByU_C(java.lang.String userId,
		java.lang.String categoryId) throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByU_C(userId, categoryId);
	}

	public static int countByU_S(java.lang.String userId, boolean sharing)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByU_S(userId, sharing);
	}

	public static int countByU_C_S(java.lang.String userId,
		java.lang.String categoryId, boolean sharing)
		throws com.liferay.portal.SystemException {
		BlogsEntryPersistence persistence = (BlogsEntryPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByU_C_S(userId, categoryId, sharing);
	}

	private static final Log _log = LogFactory.getLog(BlogsEntryUtil.class);
}