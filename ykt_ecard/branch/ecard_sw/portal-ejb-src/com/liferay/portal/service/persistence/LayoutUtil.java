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

package com.liferay.portal.service.persistence;

import com.liferay.portal.model.ModelListener;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.Validator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="LayoutUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class LayoutUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portal.model.Layout"),
			"com.liferay.portal.service.persistence.LayoutPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portal.model.Layout"));

	public static com.liferay.portal.model.Layout create(
		com.liferay.portal.service.persistence.LayoutPK layoutPK) {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(layoutPK);
	}

	public static com.liferay.portal.model.Layout remove(
		com.liferay.portal.service.persistence.LayoutPK layoutPK)
		throws com.liferay.portal.NoSuchLayoutException, 
			com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(layoutPK));
		}

		com.liferay.portal.model.Layout layout = persistence.remove(layoutPK);

		if (listener != null) {
			listener.onAfterRemove(layout);
		}

		return layout;
	}

	public static com.liferay.portal.model.Layout update(
		com.liferay.portal.model.Layout layout)
		throws com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = layout.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(layout);
			}
			else {
				listener.onBeforeUpdate(layout);
			}
		}

		layout = persistence.update(layout);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(layout);
			}
			else {
				listener.onAfterUpdate(layout);
			}
		}

		return layout;
	}

	public static com.liferay.portal.model.Layout findByPrimaryKey(
		com.liferay.portal.service.persistence.LayoutPK layoutPK)
		throws com.liferay.portal.NoSuchLayoutException, 
			com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(layoutPK);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portal.model.Layout findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchLayoutException, 
			com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portal.model.Layout findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchLayoutException, 
			com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portal.model.Layout[] findByUserId_PrevAndNext(
		com.liferay.portal.service.persistence.LayoutPK layoutPK,
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchLayoutException, 
			com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(layoutPK, userId, obc);
	}

	public static java.util.List findByU_P(java.lang.String userId,
		java.lang.String parentLayoutId)
		throws com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_P(userId, parentLayoutId);
	}

	public static java.util.List findByU_P(java.lang.String userId,
		java.lang.String parentLayoutId, int begin, int end)
		throws com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_P(userId, parentLayoutId, begin, end);
	}

	public static java.util.List findByU_P(java.lang.String userId,
		java.lang.String parentLayoutId, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_P(userId, parentLayoutId, begin, end, obc);
	}

	public static com.liferay.portal.model.Layout findByU_P_First(
		java.lang.String userId, java.lang.String parentLayoutId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchLayoutException, 
			com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_P_First(userId, parentLayoutId, obc);
	}

	public static com.liferay.portal.model.Layout findByU_P_Last(
		java.lang.String userId, java.lang.String parentLayoutId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchLayoutException, 
			com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_P_Last(userId, parentLayoutId, obc);
	}

	public static com.liferay.portal.model.Layout[] findByU_P_PrevAndNext(
		com.liferay.portal.service.persistence.LayoutPK layoutPK,
		java.lang.String userId, java.lang.String parentLayoutId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchLayoutException, 
			com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_P_PrevAndNext(layoutPK, userId,
			parentLayoutId, obc);
	}

	public static com.liferay.portal.model.Layout findByU_F(
		java.lang.String userId, java.lang.String friendlyURL)
		throws com.liferay.portal.NoSuchLayoutException, 
			com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByU_F(userId, friendlyURL);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static void removeByU_P(java.lang.String userId,
		java.lang.String parentLayoutId)
		throws com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByU_P(userId, parentLayoutId);
	}

	public static void removeByU_F(java.lang.String userId,
		java.lang.String friendlyURL)
		throws com.liferay.portal.NoSuchLayoutException, 
			com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByU_F(userId, friendlyURL);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	public static int countByU_P(java.lang.String userId,
		java.lang.String parentLayoutId)
		throws com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByU_P(userId, parentLayoutId);
	}

	public static int countByU_F(java.lang.String userId,
		java.lang.String friendlyURL) throws com.liferay.portal.SystemException {
		LayoutPersistence persistence = (LayoutPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByU_F(userId, friendlyURL);
	}

	private static final Log _log = LogFactory.getLog(LayoutUtil.class);
}