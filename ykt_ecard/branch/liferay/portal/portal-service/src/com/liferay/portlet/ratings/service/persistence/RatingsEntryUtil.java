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

package com.liferay.portlet.ratings.service.persistence;

/**
 * <a href="RatingsEntryUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RatingsEntryUtil {
	public static com.liferay.portlet.ratings.model.RatingsEntry create(
		long entryId) {
		return getPersistence().create(entryId);
	}

	public static com.liferay.portlet.ratings.model.RatingsEntry remove(
		long entryId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.ratings.NoSuchEntryException {
		return getPersistence().remove(entryId);
	}

	public static com.liferay.portlet.ratings.model.RatingsEntry remove(
		com.liferay.portlet.ratings.model.RatingsEntry ratingsEntry)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(ratingsEntry);
	}

	public static com.liferay.portlet.ratings.model.RatingsEntry update(
		com.liferay.portlet.ratings.model.RatingsEntry ratingsEntry)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(ratingsEntry);
	}

	public static com.liferay.portlet.ratings.model.RatingsEntry update(
		com.liferay.portlet.ratings.model.RatingsEntry ratingsEntry,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().update(ratingsEntry, merge);
	}

	public static com.liferay.portlet.ratings.model.RatingsEntry updateImpl(
		com.liferay.portlet.ratings.model.RatingsEntry ratingsEntry,
		boolean merge) throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(ratingsEntry, merge);
	}

	public static com.liferay.portlet.ratings.model.RatingsEntry findByPrimaryKey(
		long entryId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.ratings.NoSuchEntryException {
		return getPersistence().findByPrimaryKey(entryId);
	}

	public static com.liferay.portlet.ratings.model.RatingsEntry fetchByPrimaryKey(
		long entryId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(entryId);
	}

	public static java.util.List findByC_C(long classNameId, long classPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_C(classNameId, classPK);
	}

	public static java.util.List findByC_C(long classNameId, long classPK,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByC_C(classNameId, classPK, begin, end);
	}

	public static java.util.List findByC_C(long classNameId, long classPK,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_C(classNameId, classPK, begin, end, obc);
	}

	public static com.liferay.portlet.ratings.model.RatingsEntry findByC_C_First(
		long classNameId, long classPK,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.ratings.NoSuchEntryException {
		return getPersistence().findByC_C_First(classNameId, classPK, obc);
	}

	public static com.liferay.portlet.ratings.model.RatingsEntry findByC_C_Last(
		long classNameId, long classPK,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.ratings.NoSuchEntryException {
		return getPersistence().findByC_C_Last(classNameId, classPK, obc);
	}

	public static com.liferay.portlet.ratings.model.RatingsEntry[] findByC_C_PrevAndNext(
		long entryId, long classNameId, long classPK,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.ratings.NoSuchEntryException {
		return getPersistence().findByC_C_PrevAndNext(entryId, classNameId,
			classPK, obc);
	}

	public static com.liferay.portlet.ratings.model.RatingsEntry findByU_C_C(
		long userId, long classNameId, long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.ratings.NoSuchEntryException {
		return getPersistence().findByU_C_C(userId, classNameId, classPK);
	}

	public static com.liferay.portlet.ratings.model.RatingsEntry fetchByU_C_C(
		long userId, long classNameId, long classPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByU_C_C(userId, classNameId, classPK);
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

	public static void removeByC_C(long classNameId, long classPK)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByC_C(classNameId, classPK);
	}

	public static void removeByU_C_C(long userId, long classNameId, long classPK)
		throws com.liferay.portal.SystemException, 
			com.liferay.portlet.ratings.NoSuchEntryException {
		getPersistence().removeByU_C_C(userId, classNameId, classPK);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByC_C(long classNameId, long classPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_C(classNameId, classPK);
	}

	public static int countByU_C_C(long userId, long classNameId, long classPK)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByU_C_C(userId, classNameId, classPK);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static RatingsEntryPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(RatingsEntryPersistence persistence) {
		_persistence = persistence;
	}

	private static RatingsEntryUtil _getUtil() {
		if (_util == null) {
			_util = (RatingsEntryUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = RatingsEntryUtil.class.getName();
	private static RatingsEntryUtil _util;
	private RatingsEntryPersistence _persistence;
}