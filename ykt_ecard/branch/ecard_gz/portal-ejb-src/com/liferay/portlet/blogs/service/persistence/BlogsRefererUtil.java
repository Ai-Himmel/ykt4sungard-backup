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
 * <a href="BlogsRefererUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsRefererUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.blogs.model.BlogsReferer"),
			"com.liferay.portlet.blogs.service.persistence.BlogsRefererPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.blogs.model.BlogsReferer"));

	public static com.liferay.portlet.blogs.model.BlogsReferer create(
		java.lang.String refererId) {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(refererId);
	}

	public static com.liferay.portlet.blogs.model.BlogsReferer remove(
		java.lang.String refererId)
		throws com.liferay.portlet.blogs.NoSuchRefererException, 
			com.liferay.portal.SystemException {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(refererId));
		}

		com.liferay.portlet.blogs.model.BlogsReferer blogsReferer = persistence.remove(refererId);

		if (listener != null) {
			listener.onAfterRemove(blogsReferer);
		}

		return blogsReferer;
	}

	public static com.liferay.portlet.blogs.model.BlogsReferer update(
		com.liferay.portlet.blogs.model.BlogsReferer blogsReferer)
		throws com.liferay.portal.SystemException {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = blogsReferer.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(blogsReferer);
			}
			else {
				listener.onBeforeUpdate(blogsReferer);
			}
		}

		blogsReferer = persistence.update(blogsReferer);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(blogsReferer);
			}
			else {
				listener.onAfterUpdate(blogsReferer);
			}
		}

		return blogsReferer;
	}

	public static com.liferay.portlet.blogs.model.BlogsReferer findByPrimaryKey(
		java.lang.String refererId)
		throws com.liferay.portlet.blogs.NoSuchRefererException, 
			com.liferay.portal.SystemException {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(refererId);
	}

	public static java.util.List findByEntryId(java.lang.String entryId)
		throws com.liferay.portal.SystemException {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByEntryId(entryId);
	}

	public static java.util.List findByEntryId(java.lang.String entryId,
		int begin, int end) throws com.liferay.portal.SystemException {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByEntryId(entryId, begin, end);
	}

	public static java.util.List findByEntryId(java.lang.String entryId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByEntryId(entryId, begin, end, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsReferer findByEntryId_First(
		java.lang.String entryId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchRefererException, 
			com.liferay.portal.SystemException {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByEntryId_First(entryId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsReferer findByEntryId_Last(
		java.lang.String entryId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchRefererException, 
			com.liferay.portal.SystemException {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByEntryId_Last(entryId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsReferer[] findByEntryId_PrevAndNext(
		java.lang.String refererId, java.lang.String entryId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchRefererException, 
			com.liferay.portal.SystemException {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByEntryId_PrevAndNext(refererId, entryId, obc);
	}

	public static java.util.List findByE_T(java.lang.String entryId,
		java.lang.String type) throws com.liferay.portal.SystemException {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByE_T(entryId, type);
	}

	public static java.util.List findByE_T(java.lang.String entryId,
		java.lang.String type, int begin, int end)
		throws com.liferay.portal.SystemException {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByE_T(entryId, type, begin, end);
	}

	public static java.util.List findByE_T(java.lang.String entryId,
		java.lang.String type, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByE_T(entryId, type, begin, end, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsReferer findByE_T_First(
		java.lang.String entryId, java.lang.String type,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchRefererException, 
			com.liferay.portal.SystemException {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByE_T_First(entryId, type, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsReferer findByE_T_Last(
		java.lang.String entryId, java.lang.String type,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchRefererException, 
			com.liferay.portal.SystemException {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByE_T_Last(entryId, type, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsReferer[] findByE_T_PrevAndNext(
		java.lang.String refererId, java.lang.String entryId,
		java.lang.String type,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchRefererException, 
			com.liferay.portal.SystemException {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByE_T_PrevAndNext(refererId, entryId, type, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByEntryId(java.lang.String entryId)
		throws com.liferay.portal.SystemException {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByEntryId(entryId);
	}

	public static void removeByE_T(java.lang.String entryId,
		java.lang.String type) throws com.liferay.portal.SystemException {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByE_T(entryId, type);
	}

	public static int countByEntryId(java.lang.String entryId)
		throws com.liferay.portal.SystemException {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByEntryId(entryId);
	}

	public static int countByE_T(java.lang.String entryId, java.lang.String type)
		throws com.liferay.portal.SystemException {
		BlogsRefererPersistence persistence = (BlogsRefererPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByE_T(entryId, type);
	}

	private static final Log _log = LogFactory.getLog(BlogsRefererUtil.class);
}