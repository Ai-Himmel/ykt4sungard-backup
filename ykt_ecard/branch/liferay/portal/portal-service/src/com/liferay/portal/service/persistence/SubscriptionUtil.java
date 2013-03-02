/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
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

/**
 * <a href="SubscriptionUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class SubscriptionUtil {
	public static com.liferay.portal.model.Subscription create(
		long subscriptionId) {
		return getPersistence().create(subscriptionId);
	}

	public static com.liferay.portal.model.Subscription remove(
		long subscriptionId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchSubscriptionException {
		return getPersistence().remove(subscriptionId);
	}

	public static com.liferay.portal.model.Subscription remove(
		com.liferay.portal.model.Subscription subscription)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(subscription);
	}

	public static com.liferay.portal.model.Subscription update(
		com.liferay.portal.model.Subscription subscription)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(subscription);
	}

	public static com.liferay.portal.model.Subscription update(
		com.liferay.portal.model.Subscription subscription, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(subscription, merge);
	}

	public static com.liferay.portal.model.Subscription updateImpl(
		com.liferay.portal.model.Subscription subscription, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(subscription, merge);
	}

	public static com.liferay.portal.model.Subscription findByPrimaryKey(
		long subscriptionId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchSubscriptionException {
		return getPersistence().findByPrimaryKey(subscriptionId);
	}

	public static com.liferay.portal.model.Subscription fetchByPrimaryKey(
		long subscriptionId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(subscriptionId);
	}

	public static java.util.List findByUserId(long userId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUserId(userId);
	}

	public static java.util.List findByUserId(long userId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(long userId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portal.model.Subscription findByUserId_First(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchSubscriptionException {
		return getPersistence().findByUserId_First(userId, obc);
	}

	public static com.liferay.portal.model.Subscription findByUserId_Last(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchSubscriptionException {
		return getPersistence().findByUserId_Last(userId, obc);
	}

	public static com.liferay.portal.model.Subscription[] findByUserId_PrevAndNext(
		long subscriptionId, long userId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchSubscriptionException {
		return getPersistence().findByUserId_PrevAndNext(subscriptionId,
			userId, obc);
	}

	public static java.util.List findByC_C_C(long companyId, long classNameId,
		long classPK) throws com.liferay.portal.SystemException {
		return getPersistence().findByC_C_C(companyId, classNameId, classPK);
	}

	public static java.util.List findByC_C_C(long companyId, long classNameId,
		long classPK, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_C_C(companyId, classNameId, classPK,
			begin, end);
	}

	public static java.util.List findByC_C_C(long companyId, long classNameId,
		long classPK, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_C_C(companyId, classNameId, classPK,
			begin, end, obc);
	}

	public static com.liferay.portal.model.Subscription findByC_C_C_First(
		long companyId, long classNameId, long classPK,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchSubscriptionException {
		return getPersistence().findByC_C_C_First(companyId, classNameId,
			classPK, obc);
	}

	public static com.liferay.portal.model.Subscription findByC_C_C_Last(
		long companyId, long classNameId, long classPK,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchSubscriptionException {
		return getPersistence().findByC_C_C_Last(companyId, classNameId,
			classPK, obc);
	}

	public static com.liferay.portal.model.Subscription[] findByC_C_C_PrevAndNext(
		long subscriptionId, long companyId, long classNameId, long classPK,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchSubscriptionException {
		return getPersistence().findByC_C_C_PrevAndNext(subscriptionId,
			companyId, classNameId, classPK, obc);
	}

	public static com.liferay.portal.model.Subscription findByC_U_C_C(
		long companyId, long userId, long classNameId, long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchSubscriptionException {
		return getPersistence().findByC_U_C_C(companyId, userId, classNameId,
			classPK);
	}

	public static com.liferay.portal.model.Subscription fetchByC_U_C_C(
		long companyId, long userId, long classNameId, long classPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByC_U_C_C(companyId, userId, classNameId,
			classPK);
	}

	public static java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		return getPersistence().findWithDynamicQuery(queryInitializer);
	}

	public static java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findWithDynamicQuery(queryInitializer, begin,
			end);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll();
	}

	public static java.util.List findAll(int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll(begin, end);
	}

	public static java.util.List findAll(int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll(begin, end, obc);
	}

	public static void removeByUserId(long userId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByUserId(userId);
	}

	public static void removeByC_C_C(long companyId, long classNameId,
		long classPK) throws com.liferay.portal.SystemException {
		getPersistence().removeByC_C_C(companyId, classNameId, classPK);
	}

	public static void removeByC_U_C_C(long companyId, long userId,
		long classNameId, long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchSubscriptionException {
		getPersistence().removeByC_U_C_C(companyId, userId, classNameId, classPK);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByUserId(long userId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUserId(userId);
	}

	public static int countByC_C_C(long companyId, long classNameId,
		long classPK) throws com.liferay.portal.SystemException {
		return getPersistence().countByC_C_C(companyId, classNameId, classPK);
	}

	public static int countByC_U_C_C(long companyId, long userId,
		long classNameId, long classPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_U_C_C(companyId, userId, classNameId,
			classPK);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static SubscriptionPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(SubscriptionPersistence persistence) {
		_persistence = persistence;
	}

	private static SubscriptionUtil _getUtil() {
		if (_util == null) {
			_util = (SubscriptionUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = SubscriptionUtil.class.getName();
	private static SubscriptionUtil _util;
	private SubscriptionPersistence _persistence;
}