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
 * <a href="ShoppingItemFinderUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingItemFinderUtil {
	public static int countByCategoryIds(java.util.List categoryIds)
		throws com.liferay.portal.SystemException {
		return getFinder().countByCategoryIds(categoryIds);
	}

	public static int countByFeatured(long groupId, long[] categoryIds)
		throws com.liferay.portal.SystemException {
		return getFinder().countByFeatured(groupId, categoryIds);
	}

	public static int countByKeywords(long groupId, long[] categoryIds,
		java.lang.String keywords) throws com.liferay.portal.SystemException {
		return getFinder().countByKeywords(groupId, categoryIds, keywords);
	}

	public static int countBySale(long groupId, long[] categoryIds)
		throws com.liferay.portal.SystemException {
		return getFinder().countBySale(groupId, categoryIds);
	}

	public static java.util.List findByFeatured(long groupId,
		long[] categoryIds, int numOfItems)
		throws com.liferay.portal.SystemException {
		return getFinder().findByFeatured(groupId, categoryIds, numOfItems);
	}

	public static java.util.List findByKeywords(long groupId,
		long[] categoryIds, java.lang.String keywords, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getFinder().findByKeywords(groupId, categoryIds, keywords,
			begin, end);
	}

	public static java.util.List findBySale(long groupId, long[] categoryIds,
		int numOfItems) throws com.liferay.portal.SystemException {
		return getFinder().findBySale(groupId, categoryIds, numOfItems);
	}

	public static ShoppingItemFinder getFinder() {
		return _getUtil()._finder;
	}

	public void setFinder(ShoppingItemFinder finder) {
		_finder = finder;
	}

	private static ShoppingItemFinderUtil _getUtil() {
		if (_util == null) {
			_util = (ShoppingItemFinderUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = ShoppingItemFinderUtil.class.getName();
	private static ShoppingItemFinderUtil _util;
	private ShoppingItemFinder _finder;
}