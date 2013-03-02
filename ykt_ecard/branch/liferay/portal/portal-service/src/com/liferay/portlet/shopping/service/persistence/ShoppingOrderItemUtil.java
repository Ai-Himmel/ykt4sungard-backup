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
 * <a href="ShoppingOrderItemUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingOrderItemUtil {
	public static com.liferay.portlet.shopping.model.ShoppingOrderItem create(
		long orderItemId) {
		return getPersistence().create(orderItemId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderItem remove(
		long orderItemId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchOrderItemException {
		return getPersistence().remove(orderItemId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderItem remove(
		com.liferay.portlet.shopping.model.ShoppingOrderItem shoppingOrderItem)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(shoppingOrderItem);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderItem update(
		com.liferay.portlet.shopping.model.ShoppingOrderItem shoppingOrderItem)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(shoppingOrderItem);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderItem update(
		com.liferay.portlet.shopping.model.ShoppingOrderItem shoppingOrderItem,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(shoppingOrderItem, merge);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderItem updateImpl(
		com.liferay.portlet.shopping.model.ShoppingOrderItem shoppingOrderItem,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(shoppingOrderItem, merge);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderItem findByPrimaryKey(
		long orderItemId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchOrderItemException {
		return getPersistence().findByPrimaryKey(orderItemId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderItem fetchByPrimaryKey(
		long orderItemId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(orderItemId);
	}

	public static java.util.List findByOrderId(long orderId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByOrderId(orderId);
	}

	public static java.util.List findByOrderId(long orderId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByOrderId(orderId, begin, end);
	}

	public static java.util.List findByOrderId(long orderId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByOrderId(orderId, begin, end, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderItem findByOrderId_First(
		long orderId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchOrderItemException {
		return getPersistence().findByOrderId_First(orderId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderItem findByOrderId_Last(
		long orderId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchOrderItemException {
		return getPersistence().findByOrderId_Last(orderId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingOrderItem[] findByOrderId_PrevAndNext(
		long orderItemId, long orderId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchOrderItemException {
		return getPersistence().findByOrderId_PrevAndNext(orderItemId, orderId,
			obc);
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

	public static void removeByOrderId(long orderId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByOrderId(orderId);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByOrderId(long orderId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByOrderId(orderId);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static ShoppingOrderItemPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(ShoppingOrderItemPersistence persistence) {
		_persistence = persistence;
	}

	private static ShoppingOrderItemUtil _getUtil() {
		if (_util == null) {
			_util = (ShoppingOrderItemUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = ShoppingOrderItemUtil.class.getName();
	private static ShoppingOrderItemUtil _util;
	private ShoppingOrderItemPersistence _persistence;
}