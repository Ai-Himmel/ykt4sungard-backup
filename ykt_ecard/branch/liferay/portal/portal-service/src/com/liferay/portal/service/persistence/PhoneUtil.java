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
 * <a href="PhoneUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PhoneUtil {
	public static com.liferay.portal.model.Phone create(long phoneId) {
		return getPersistence().create(phoneId);
	}

	public static com.liferay.portal.model.Phone remove(long phoneId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPhoneException {
		return getPersistence().remove(phoneId);
	}

	public static com.liferay.portal.model.Phone remove(
		com.liferay.portal.model.Phone phone)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(phone);
	}

	public static com.liferay.portal.model.Phone update(
		com.liferay.portal.model.Phone phone)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(phone);
	}

	public static com.liferay.portal.model.Phone update(
		com.liferay.portal.model.Phone phone, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(phone, merge);
	}

	public static com.liferay.portal.model.Phone updateImpl(
		com.liferay.portal.model.Phone phone, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(phone, merge);
	}

	public static com.liferay.portal.model.Phone findByPrimaryKey(long phoneId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPhoneException {
		return getPersistence().findByPrimaryKey(phoneId);
	}

	public static com.liferay.portal.model.Phone fetchByPrimaryKey(long phoneId)
		throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(phoneId);
	}

	public static java.util.List findByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(long companyId, int begin,
		int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(long companyId, int begin,
		int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portal.model.Phone findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPhoneException {
		return getPersistence().findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portal.model.Phone findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPhoneException {
		return getPersistence().findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portal.model.Phone[] findByCompanyId_PrevAndNext(
		long phoneId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPhoneException {
		return getPersistence().findByCompanyId_PrevAndNext(phoneId, companyId,
			obc);
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

	public static com.liferay.portal.model.Phone findByUserId_First(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPhoneException {
		return getPersistence().findByUserId_First(userId, obc);
	}

	public static com.liferay.portal.model.Phone findByUserId_Last(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPhoneException {
		return getPersistence().findByUserId_Last(userId, obc);
	}

	public static com.liferay.portal.model.Phone[] findByUserId_PrevAndNext(
		long phoneId, long userId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPhoneException {
		return getPersistence().findByUserId_PrevAndNext(phoneId, userId, obc);
	}

	public static java.util.List findByC_C(long companyId, long classNameId)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_C(companyId, classNameId);
	}

	public static java.util.List findByC_C(long companyId, long classNameId,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findByC_C(companyId, classNameId, begin, end);
	}

	public static java.util.List findByC_C(long companyId, long classNameId,
		int begin, int end, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_C(companyId, classNameId, begin, end,
			obc);
	}

	public static com.liferay.portal.model.Phone findByC_C_First(
		long companyId, long classNameId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPhoneException {
		return getPersistence().findByC_C_First(companyId, classNameId, obc);
	}

	public static com.liferay.portal.model.Phone findByC_C_Last(
		long companyId, long classNameId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPhoneException {
		return getPersistence().findByC_C_Last(companyId, classNameId, obc);
	}

	public static com.liferay.portal.model.Phone[] findByC_C_PrevAndNext(
		long phoneId, long companyId, long classNameId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPhoneException {
		return getPersistence().findByC_C_PrevAndNext(phoneId, companyId,
			classNameId, obc);
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

	public static com.liferay.portal.model.Phone findByC_C_C_First(
		long companyId, long classNameId, long classPK,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPhoneException {
		return getPersistence().findByC_C_C_First(companyId, classNameId,
			classPK, obc);
	}

	public static com.liferay.portal.model.Phone findByC_C_C_Last(
		long companyId, long classNameId, long classPK,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPhoneException {
		return getPersistence().findByC_C_C_Last(companyId, classNameId,
			classPK, obc);
	}

	public static com.liferay.portal.model.Phone[] findByC_C_C_PrevAndNext(
		long phoneId, long companyId, long classNameId, long classPK,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPhoneException {
		return getPersistence().findByC_C_C_PrevAndNext(phoneId, companyId,
			classNameId, classPK, obc);
	}

	public static java.util.List findByC_C_C_P(long companyId,
		long classNameId, long classPK, boolean primary)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_C_C_P(companyId, classNameId, classPK,
			primary);
	}

	public static java.util.List findByC_C_C_P(long companyId,
		long classNameId, long classPK, boolean primary, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_C_C_P(companyId, classNameId, classPK,
			primary, begin, end);
	}

	public static java.util.List findByC_C_C_P(long companyId,
		long classNameId, long classPK, boolean primary, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_C_C_P(companyId, classNameId, classPK,
			primary, begin, end, obc);
	}

	public static com.liferay.portal.model.Phone findByC_C_C_P_First(
		long companyId, long classNameId, long classPK, boolean primary,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPhoneException {
		return getPersistence().findByC_C_C_P_First(companyId, classNameId,
			classPK, primary, obc);
	}

	public static com.liferay.portal.model.Phone findByC_C_C_P_Last(
		long companyId, long classNameId, long classPK, boolean primary,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPhoneException {
		return getPersistence().findByC_C_C_P_Last(companyId, classNameId,
			classPK, primary, obc);
	}

	public static com.liferay.portal.model.Phone[] findByC_C_C_P_PrevAndNext(
		long phoneId, long companyId, long classNameId, long classPK,
		boolean primary, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchPhoneException {
		return getPersistence().findByC_C_C_P_PrevAndNext(phoneId, companyId,
			classNameId, classPK, primary, obc);
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

	public static void removeByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByCompanyId(companyId);
	}

	public static void removeByUserId(long userId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByUserId(userId);
	}

	public static void removeByC_C(long companyId, long classNameId)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByC_C(companyId, classNameId);
	}

	public static void removeByC_C_C(long companyId, long classNameId,
		long classPK) throws com.liferay.portal.SystemException {
		getPersistence().removeByC_C_C(companyId, classNameId, classPK);
	}

	public static void removeByC_C_C_P(long companyId, long classNameId,
		long classPK, boolean primary)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByC_C_C_P(companyId, classNameId, classPK,
			primary);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countByCompanyId(long companyId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByCompanyId(companyId);
	}

	public static int countByUserId(long userId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByUserId(userId);
	}

	public static int countByC_C(long companyId, long classNameId)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_C(companyId, classNameId);
	}

	public static int countByC_C_C(long companyId, long classNameId,
		long classPK) throws com.liferay.portal.SystemException {
		return getPersistence().countByC_C_C(companyId, classNameId, classPK);
	}

	public static int countByC_C_C_P(long companyId, long classNameId,
		long classPK, boolean primary)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_C_C_P(companyId, classNameId, classPK,
			primary);
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static PhonePersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(PhonePersistence persistence) {
		_persistence = persistence;
	}

	private static PhoneUtil _getUtil() {
		if (_util == null) {
			_util = (PhoneUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = PhoneUtil.class.getName();
	private static PhoneUtil _util;
	private PhonePersistence _persistence;
}