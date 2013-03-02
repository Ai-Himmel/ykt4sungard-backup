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
 * <a href="AddressUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class AddressUtil {
	public static com.liferay.portal.model.Address create(long addressId) {
		return getPersistence().create(addressId);
	}

	public static com.liferay.portal.model.Address remove(long addressId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAddressException {
		return getPersistence().remove(addressId);
	}

	public static com.liferay.portal.model.Address remove(
		com.liferay.portal.model.Address address)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(address);
	}

	public static com.liferay.portal.model.Address update(
		com.liferay.portal.model.Address address)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(address);
	}

	public static com.liferay.portal.model.Address update(
		com.liferay.portal.model.Address address, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(address, merge);
	}

	public static com.liferay.portal.model.Address updateImpl(
		com.liferay.portal.model.Address address, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(address, merge);
	}

	public static com.liferay.portal.model.Address findByPrimaryKey(
		long addressId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAddressException {
		return getPersistence().findByPrimaryKey(addressId);
	}

	public static com.liferay.portal.model.Address fetchByPrimaryKey(
		long addressId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(addressId);
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

	public static com.liferay.portal.model.Address findByCompanyId_First(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAddressException {
		return getPersistence().findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portal.model.Address findByCompanyId_Last(
		long companyId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAddressException {
		return getPersistence().findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portal.model.Address[] findByCompanyId_PrevAndNext(
		long addressId, long companyId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAddressException {
		return getPersistence().findByCompanyId_PrevAndNext(addressId,
			companyId, obc);
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

	public static com.liferay.portal.model.Address findByUserId_First(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAddressException {
		return getPersistence().findByUserId_First(userId, obc);
	}

	public static com.liferay.portal.model.Address findByUserId_Last(
		long userId, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAddressException {
		return getPersistence().findByUserId_Last(userId, obc);
	}

	public static com.liferay.portal.model.Address[] findByUserId_PrevAndNext(
		long addressId, long userId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAddressException {
		return getPersistence().findByUserId_PrevAndNext(addressId, userId, obc);
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

	public static com.liferay.portal.model.Address findByC_C_First(
		long companyId, long classNameId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAddressException {
		return getPersistence().findByC_C_First(companyId, classNameId, obc);
	}

	public static com.liferay.portal.model.Address findByC_C_Last(
		long companyId, long classNameId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAddressException {
		return getPersistence().findByC_C_Last(companyId, classNameId, obc);
	}

	public static com.liferay.portal.model.Address[] findByC_C_PrevAndNext(
		long addressId, long companyId, long classNameId,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAddressException {
		return getPersistence().findByC_C_PrevAndNext(addressId, companyId,
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

	public static com.liferay.portal.model.Address findByC_C_C_First(
		long companyId, long classNameId, long classPK,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAddressException {
		return getPersistence().findByC_C_C_First(companyId, classNameId,
			classPK, obc);
	}

	public static com.liferay.portal.model.Address findByC_C_C_Last(
		long companyId, long classNameId, long classPK,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAddressException {
		return getPersistence().findByC_C_C_Last(companyId, classNameId,
			classPK, obc);
	}

	public static com.liferay.portal.model.Address[] findByC_C_C_PrevAndNext(
		long addressId, long companyId, long classNameId, long classPK,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAddressException {
		return getPersistence().findByC_C_C_PrevAndNext(addressId, companyId,
			classNameId, classPK, obc);
	}

	public static java.util.List findByC_C_C_M(long companyId,
		long classNameId, long classPK, boolean mailing)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_C_C_M(companyId, classNameId, classPK,
			mailing);
	}

	public static java.util.List findByC_C_C_M(long companyId,
		long classNameId, long classPK, boolean mailing, int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_C_C_M(companyId, classNameId, classPK,
			mailing, begin, end);
	}

	public static java.util.List findByC_C_C_M(long companyId,
		long classNameId, long classPK, boolean mailing, int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findByC_C_C_M(companyId, classNameId, classPK,
			mailing, begin, end, obc);
	}

	public static com.liferay.portal.model.Address findByC_C_C_M_First(
		long companyId, long classNameId, long classPK, boolean mailing,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAddressException {
		return getPersistence().findByC_C_C_M_First(companyId, classNameId,
			classPK, mailing, obc);
	}

	public static com.liferay.portal.model.Address findByC_C_C_M_Last(
		long companyId, long classNameId, long classPK, boolean mailing,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAddressException {
		return getPersistence().findByC_C_C_M_Last(companyId, classNameId,
			classPK, mailing, obc);
	}

	public static com.liferay.portal.model.Address[] findByC_C_C_M_PrevAndNext(
		long addressId, long companyId, long classNameId, long classPK,
		boolean mailing, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAddressException {
		return getPersistence().findByC_C_C_M_PrevAndNext(addressId, companyId,
			classNameId, classPK, mailing, obc);
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

	public static com.liferay.portal.model.Address findByC_C_C_P_First(
		long companyId, long classNameId, long classPK, boolean primary,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAddressException {
		return getPersistence().findByC_C_C_P_First(companyId, classNameId,
			classPK, primary, obc);
	}

	public static com.liferay.portal.model.Address findByC_C_C_P_Last(
		long companyId, long classNameId, long classPK, boolean primary,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAddressException {
		return getPersistence().findByC_C_C_P_Last(companyId, classNameId,
			classPK, primary, obc);
	}

	public static com.liferay.portal.model.Address[] findByC_C_C_P_PrevAndNext(
		long addressId, long companyId, long classNameId, long classPK,
		boolean primary, com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAddressException {
		return getPersistence().findByC_C_C_P_PrevAndNext(addressId, companyId,
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

	public static void removeByC_C_C_M(long companyId, long classNameId,
		long classPK, boolean mailing)
		throws com.liferay.portal.SystemException {
		getPersistence().removeByC_C_C_M(companyId, classNameId, classPK,
			mailing);
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

	public static int countByC_C_C_M(long companyId, long classNameId,
		long classPK, boolean mailing)
		throws com.liferay.portal.SystemException {
		return getPersistence().countByC_C_C_M(companyId, classNameId, classPK,
			mailing);
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

	public static AddressPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(AddressPersistence persistence) {
		_persistence = persistence;
	}

	private static AddressUtil _getUtil() {
		if (_util == null) {
			_util = (AddressUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = AddressUtil.class.getName();
	private static AddressUtil _util;
	private AddressPersistence _persistence;
}