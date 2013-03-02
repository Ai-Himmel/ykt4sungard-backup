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
 * <a href="BlogsPropsUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsPropsUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.blogs.model.BlogsProps"),
			"com.liferay.portlet.blogs.service.persistence.BlogsPropsPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.blogs.model.BlogsProps"));

	public static com.liferay.portlet.blogs.model.BlogsProps create(
		java.lang.String propsId) {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(propsId);
	}

	public static com.liferay.portlet.blogs.model.BlogsProps remove(
		java.lang.String propsId)
		throws com.liferay.portlet.blogs.NoSuchPropsException, 
			com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(propsId));
		}

		com.liferay.portlet.blogs.model.BlogsProps blogsProps = persistence.remove(propsId);

		if (listener != null) {
			listener.onAfterRemove(blogsProps);
		}

		return blogsProps;
	}

	public static com.liferay.portlet.blogs.model.BlogsProps update(
		com.liferay.portlet.blogs.model.BlogsProps blogsProps)
		throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = blogsProps.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(blogsProps);
			}
			else {
				listener.onBeforeUpdate(blogsProps);
			}
		}

		blogsProps = persistence.update(blogsProps);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(blogsProps);
			}
			else {
				listener.onAfterUpdate(blogsProps);
			}
		}

		return blogsProps;
	}

	public static com.liferay.portlet.blogs.model.BlogsProps findByPrimaryKey(
		java.lang.String propsId)
		throws com.liferay.portlet.blogs.NoSuchPropsException, 
			com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(propsId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsProps findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchPropsException, 
			com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsProps findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchPropsException, 
			com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsProps[] findByCompanyId_PrevAndNext(
		java.lang.String propsId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchPropsException, 
			com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(propsId, companyId, obc);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsProps findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchPropsException, 
			com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsProps findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchPropsException, 
			com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsProps[] findByUserId_PrevAndNext(
		java.lang.String propsId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchPropsException, 
			com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(propsId, userId, obc);
	}

	public static java.util.List findByEntryId(java.lang.String entryId)
		throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByEntryId(entryId);
	}

	public static java.util.List findByEntryId(java.lang.String entryId,
		int begin, int end) throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByEntryId(entryId, begin, end);
	}

	public static java.util.List findByEntryId(java.lang.String entryId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByEntryId(entryId, begin, end, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsProps findByEntryId_First(
		java.lang.String entryId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchPropsException, 
			com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByEntryId_First(entryId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsProps findByEntryId_Last(
		java.lang.String entryId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchPropsException, 
			com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByEntryId_Last(entryId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsProps[] findByEntryId_PrevAndNext(
		java.lang.String propsId, java.lang.String entryId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchPropsException, 
			com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByEntryId_PrevAndNext(propsId, entryId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsProps findByU_E(
		java.lang.String userId, java.lang.String entryId)
		throws com.liferay.portlet.blogs.NoSuchPropsException, 
			com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_E(userId, entryId);
	}

	public static java.util.List findByE_Q(java.lang.String entryId,
		int quantity) throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByE_Q(entryId, quantity);
	}

	public static java.util.List findByE_Q(java.lang.String entryId,
		int quantity, int begin, int end)
		throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByE_Q(entryId, quantity, begin, end);
	}

	public static java.util.List findByE_Q(java.lang.String entryId,
		int quantity, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByE_Q(entryId, quantity, begin, end, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsProps findByE_Q_First(
		java.lang.String entryId, int quantity,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchPropsException, 
			com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByE_Q_First(entryId, quantity, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsProps findByE_Q_Last(
		java.lang.String entryId, int quantity,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchPropsException, 
			com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByE_Q_Last(entryId, quantity, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsProps[] findByE_Q_PrevAndNext(
		java.lang.String propsId, java.lang.String entryId, int quantity,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchPropsException, 
			com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByE_Q_PrevAndNext(propsId, entryId, quantity, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static void removeByEntryId(java.lang.String entryId)
		throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByEntryId(entryId);
	}

	public static void removeByU_E(java.lang.String userId,
		java.lang.String entryId)
		throws com.liferay.portlet.blogs.NoSuchPropsException, 
			com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByU_E(userId, entryId);
	}

	public static void removeByE_Q(java.lang.String entryId, int quantity)
		throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByE_Q(entryId, quantity);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	public static int countByEntryId(java.lang.String entryId)
		throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByEntryId(entryId);
	}

	public static int countByU_E(java.lang.String userId,
		java.lang.String entryId) throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByU_E(userId, entryId);
	}

	public static int countByE_Q(java.lang.String entryId, int quantity)
		throws com.liferay.portal.SystemException {
		BlogsPropsPersistence persistence = (BlogsPropsPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByE_Q(entryId, quantity);
	}

	private static final Log _log = LogFactory.getLog(BlogsPropsUtil.class);
}