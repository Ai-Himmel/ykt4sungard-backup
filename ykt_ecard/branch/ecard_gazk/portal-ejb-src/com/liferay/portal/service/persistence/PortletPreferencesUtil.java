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
 * <a href="PortletPreferencesUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class PortletPreferencesUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portal.model.PortletPreferences"),
			"com.liferay.portal.service.persistence.PortletPreferencesPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portal.model.PortletPreferences"));

	public static com.liferay.portal.model.PortletPreferences create(
		com.liferay.portal.service.persistence.PortletPreferencesPK portletPreferencesPK) {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(portletPreferencesPK);
	}

	public static com.liferay.portal.model.PortletPreferences remove(
		com.liferay.portal.service.persistence.PortletPreferencesPK portletPreferencesPK)
		throws com.liferay.portal.NoSuchPortletPreferencesException, 
			com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(portletPreferencesPK));
		}

		com.liferay.portal.model.PortletPreferences portletPreferences = persistence.remove(portletPreferencesPK);

		if (listener != null) {
			listener.onAfterRemove(portletPreferences);
		}

		return portletPreferences;
	}

	public static com.liferay.portal.model.PortletPreferences update(
		com.liferay.portal.model.PortletPreferences portletPreferences)
		throws com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = portletPreferences.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(portletPreferences);
			}
			else {
				listener.onBeforeUpdate(portletPreferences);
			}
		}

		portletPreferences = persistence.update(portletPreferences);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(portletPreferences);
			}
			else {
				listener.onAfterUpdate(portletPreferences);
			}
		}

		return portletPreferences;
	}

	public static com.liferay.portal.model.PortletPreferences findByPrimaryKey(
		com.liferay.portal.service.persistence.PortletPreferencesPK portletPreferencesPK)
		throws com.liferay.portal.NoSuchPortletPreferencesException, 
			com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(portletPreferencesPK);
	}

	public static java.util.List findByLayoutId(java.lang.String layoutId)
		throws com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByLayoutId(layoutId);
	}

	public static java.util.List findByLayoutId(java.lang.String layoutId,
		int begin, int end) throws com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByLayoutId(layoutId, begin, end);
	}

	public static java.util.List findByLayoutId(java.lang.String layoutId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByLayoutId(layoutId, begin, end, obc);
	}

	public static com.liferay.portal.model.PortletPreferences findByLayoutId_First(
		java.lang.String layoutId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchPortletPreferencesException, 
			com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByLayoutId_First(layoutId, obc);
	}

	public static com.liferay.portal.model.PortletPreferences findByLayoutId_Last(
		java.lang.String layoutId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchPortletPreferencesException, 
			com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByLayoutId_Last(layoutId, obc);
	}

	public static com.liferay.portal.model.PortletPreferences[] findByLayoutId_PrevAndNext(
		com.liferay.portal.service.persistence.PortletPreferencesPK portletPreferencesPK,
		java.lang.String layoutId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchPortletPreferencesException, 
			com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByLayoutId_PrevAndNext(portletPreferencesPK,
			layoutId, obc);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portal.model.PortletPreferences findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchPortletPreferencesException, 
			com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portal.model.PortletPreferences findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchPortletPreferencesException, 
			com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portal.model.PortletPreferences[] findByUserId_PrevAndNext(
		com.liferay.portal.service.persistence.PortletPreferencesPK portletPreferencesPK,
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchPortletPreferencesException, 
			com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(portletPreferencesPK,
			userId, obc);
	}

	public static java.util.List findByL_U(java.lang.String layoutId,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByL_U(layoutId, userId);
	}

	public static java.util.List findByL_U(java.lang.String layoutId,
		java.lang.String userId, int begin, int end)
		throws com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByL_U(layoutId, userId, begin, end);
	}

	public static java.util.List findByL_U(java.lang.String layoutId,
		java.lang.String userId, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByL_U(layoutId, userId, begin, end, obc);
	}

	public static com.liferay.portal.model.PortletPreferences findByL_U_First(
		java.lang.String layoutId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchPortletPreferencesException, 
			com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByL_U_First(layoutId, userId, obc);
	}

	public static com.liferay.portal.model.PortletPreferences findByL_U_Last(
		java.lang.String layoutId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchPortletPreferencesException, 
			com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByL_U_Last(layoutId, userId, obc);
	}

	public static com.liferay.portal.model.PortletPreferences[] findByL_U_PrevAndNext(
		com.liferay.portal.service.persistence.PortletPreferencesPK portletPreferencesPK,
		java.lang.String layoutId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchPortletPreferencesException, 
			com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByL_U_PrevAndNext(portletPreferencesPK,
			layoutId, userId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByLayoutId(java.lang.String layoutId)
		throws com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByLayoutId(layoutId);
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static void removeByL_U(java.lang.String layoutId,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByL_U(layoutId, userId);
	}

	public static int countByLayoutId(java.lang.String layoutId)
		throws com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByLayoutId(layoutId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	public static int countByL_U(java.lang.String layoutId,
		java.lang.String userId) throws com.liferay.portal.SystemException {
		PortletPreferencesPersistence persistence = (PortletPreferencesPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByL_U(layoutId, userId);
	}

	private static final Log _log = LogFactory.getLog(PortletPreferencesUtil.class);
}