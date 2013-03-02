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
 * <a href="BlogsLinkUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BlogsLinkUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.blogs.model.BlogsLink"),
			"com.liferay.portlet.blogs.service.persistence.BlogsLinkPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.blogs.model.BlogsLink"));

	public static com.liferay.portlet.blogs.model.BlogsLink create(
		java.lang.String linkId) {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(linkId);
	}

	public static com.liferay.portlet.blogs.model.BlogsLink remove(
		java.lang.String linkId)
		throws com.liferay.portlet.blogs.NoSuchLinkException, 
			com.liferay.portal.SystemException {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(linkId));
		}

		com.liferay.portlet.blogs.model.BlogsLink blogsLink = persistence.remove(linkId);

		if (listener != null) {
			listener.onAfterRemove(blogsLink);
		}

		return blogsLink;
	}

	public static com.liferay.portlet.blogs.model.BlogsLink update(
		com.liferay.portlet.blogs.model.BlogsLink blogsLink)
		throws com.liferay.portal.SystemException {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = blogsLink.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(blogsLink);
			}
			else {
				listener.onBeforeUpdate(blogsLink);
			}
		}

		blogsLink = persistence.update(blogsLink);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(blogsLink);
			}
			else {
				listener.onAfterUpdate(blogsLink);
			}
		}

		return blogsLink;
	}

	public static com.liferay.portlet.blogs.model.BlogsLink findByPrimaryKey(
		java.lang.String linkId)
		throws com.liferay.portlet.blogs.NoSuchLinkException, 
			com.liferay.portal.SystemException {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(linkId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsLink findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchLinkException, 
			com.liferay.portal.SystemException {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsLink findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchLinkException, 
			com.liferay.portal.SystemException {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsLink[] findByCompanyId_PrevAndNext(
		java.lang.String linkId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchLinkException, 
			com.liferay.portal.SystemException {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(linkId, companyId, obc);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsLink findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchLinkException, 
			com.liferay.portal.SystemException {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsLink findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchLinkException, 
			com.liferay.portal.SystemException {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.blogs.model.BlogsLink[] findByUserId_PrevAndNext(
		java.lang.String linkId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.blogs.NoSuchLinkException, 
			com.liferay.portal.SystemException {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(linkId, userId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		BlogsLinkPersistence persistence = (BlogsLinkPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	private static final Log _log = LogFactory.getLog(BlogsLinkUtil.class);
}