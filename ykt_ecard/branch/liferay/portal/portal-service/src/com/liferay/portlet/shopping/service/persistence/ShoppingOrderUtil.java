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

package com.liferay.portlet.shopping.service.persistence;

/**
 * <a href="ShoppingOrderUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingOrderUtil {
	public static com.liferay.portlet.shopping.model.ShoppingOrder create(
		long orderId) {
		return getPersistence().create(orderId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder remove(
		long orderId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchOrderException {
		return getPersistence().remove(orderId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder remove(
		com.liferay.portlet.shopping.model.ShoppingOrder shoppingOrder)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(shoppingOrder);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder update(
		com.liferay.portlet.shopping.model.ShoppingOrder shoppingOrder)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(shoppingOrder);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder update(
		com.liferay.portlet.shopping.model.ShoppingOrder shoppingOrder,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(shoppingOrder, merge);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder updateImpl(
		com.liferay.portlet.shopping.model.ShoppingOrder shoppingOrder,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(shoppingOrder, merge);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder findByPrimaryKey(
		long orderId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchOrderException {
		return getPersistence().findByPrimaryKey(orderId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder fetchByPrimaryKey(
		long orderId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(orderId);
	}

	public static java.util.List findByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByGroupId(groupId);
	}

	public static java.util.List findByGroupId(long groupId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByGroupId(groupId, begin, end);
	}

	public static java.util.List findByGroupId(long groupId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByGroupId(groupId, begin, end, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder findByGroupId_First(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchOrderException {
		return getPersistence().findByGroupId_First(groupId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder findByGroupId_Last(
		long groupId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchOrderException {
		return getPersistence().findByGroupId_Last(groupId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder[] findByGroupId_PrevAndNext(
		long orderId, long groupId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchOrderException {
		return getPersistence().findByGroupId_PrevAndNext(orderId, groupId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder findByNumber(
		java.lang.String number)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchOrderException {
		return getPersistence().findByNumber(number);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder fetchByNumber(
		java.lang.String number) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByNumber(number);
	}

	public static java.util.List findByG_U_PPPS(long groupId, long userId,
		java.lang.String ppPaymentStatus)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_U_PPPS(groupId, userId, ppPaymentStatus);
	}

	public static java.util.List findByG_U_PPPS(long groupId, long userId,
		java.lang.String ppPaymentStatus, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_U_PPPS(groupId, userId,
			ppPaymentStatus, begin, end);
	}

	public static java.util.List findByG_U_PPPS(long groupId, long userId,
		java.lang.String ppPaymentStatus, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByG_U_PPPS(groupId, userId,
			ppPaymentStatus, begin, end, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder findByG_U_PPPS_First(
		long groupId, long userId, java.lang.String ppPaymentStatus,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchOrderException {
		return getPersistence().findByG_U_PPPS_First(groupId, userId,
			ppPaymentStatus, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder findByG_U_PPPS_Last(
		long groupId, long userId, java.lang.String ppPaymentStatus,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchOrderException {
		return getPersistence().findByG_U_PPPS_Last(groupId, userId,
			ppPaymentStatus, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrder[] findByG_U_PPPS_PrevAndNext(
		long orderId, long groupId, long userId,
		java.lang.String ppPaymentStatus,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchOrderException {
		return getPersistence().findByG_U_PPPS_PrevAndNext(orderId, groupId,
			userId, ppPaymentStatus, obc);
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

	public static void removeByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByGroupId(groupId);
	}

	public static void removeByNumber(java.lang.String number)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchOrderException {
		getPersistence().removeByNumber(number);
	}

	public static void removeByG_U_PPPS(long groupId, long userId,
		java.lang.String ppPaymentStatus)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByG_U_PPPS(groupId, userId, ppPaymentStatus);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByGroupId(long groupId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByGroupId(groupId);
	}

	public static int countByNumber(java.lang.String number)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByNumber(number);
	}

	public static int countByG_U_PPPS(long groupId, long userId,
		java.lang.String ppPaymentStatus)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByG_U_PPPS(groupId, userId, ppPaymentStatus);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static ShoppingOrderPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(ShoppingOrderPersistence persistence) {
		_persistence = persistence;
	}

	private static ShoppingOrderUtil _getUtil() {
		if (_util == null) {
			_util = (ShoppingOrderUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = ShoppingOrderUtil.class.getName();
	private static ShoppingOrderUtil _util;
	private ShoppingOrderPersistence _persistence;
}