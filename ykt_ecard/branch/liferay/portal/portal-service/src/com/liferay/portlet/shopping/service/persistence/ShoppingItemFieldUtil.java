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
 * <a href="ShoppingItemFieldUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingItemFieldUtil {
	public static com.liferay.portlet.shopping.model.ShoppingItemField create(
		long itemFieldId) {
		return getPersistence().create(itemFieldId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemField remove(
		long itemFieldId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemFieldException {
		return getPersistence().remove(itemFieldId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemField remove(
		com.liferay.portlet.shopping.model.ShoppingItemField shoppingItemField)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(shoppingItemField);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemField update(
		com.liferay.portlet.shopping.model.ShoppingItemField shoppingItemField)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(shoppingItemField);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemField update(
		com.liferay.portlet.shopping.model.ShoppingItemField shoppingItemField,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(shoppingItemField, merge);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemField updateImpl(
		com.liferay.portlet.shopping.model.ShoppingItemField shoppingItemField,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(shoppingItemField, merge);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemField findByPrimaryKey(
		long itemFieldId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemFieldException {
		return getPersistence().findByPrimaryKey(itemFieldId);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemField fetchByPrimaryKey(
		long itemFieldId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(itemFieldId);
	}

	public static java.util.List findByItemId(long itemId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByItemId(itemId);
	}

	public static java.util.List findByItemId(long itemId, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByItemId(itemId, begin, end);
	}

	public static java.util.List findByItemId(long itemId, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByItemId(itemId, begin, end, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemField findByItemId_First(
		long itemId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemFieldException {
		return getPersistence().findByItemId_First(itemId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemField findByItemId_Last(
		long itemId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemFieldException {
		return getPersistence().findByItemId_Last(itemId, obc);
	}

	public static com.liferay.portlet.shopping.model.ShoppingItemField[] findByItemId_PrevAndNext(
		long itemFieldId, long itemId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.shopping.NoSuchItemFieldException {
		return getPersistence().findByItemId_PrevAndNext(itemFieldId, itemId,
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

	public static void removeByItemId(long itemId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByItemId(itemId);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByItemId(long itemId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByItemId(itemId);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static ShoppingItemFieldPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(ShoppingItemFieldPersistence persistence) {
		_persistence = persistence;
	}

	private static ShoppingItemFieldUtil _getUtil() {
		if (_util == null) {
			_util = (ShoppingItemFieldUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = ShoppingItemFieldUtil.class.getName();
	private static ShoppingItemFieldUtil _util;
	private ShoppingItemFieldPersistence _persistence;
}