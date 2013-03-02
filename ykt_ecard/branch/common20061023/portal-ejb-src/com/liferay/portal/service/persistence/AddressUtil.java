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
 * <a href="AddressUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class AddressUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portal.model.Address"),
			"com.liferay.portal.service.persistence.AddressPersistence2");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portal.model.Address"));

	public static com.liferay.portal.model.Address create(
		java.lang.String addressId) {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(addressId);
	}

	public static com.liferay.portal.model.Address remove(
		java.lang.String addressId)
		throws com.liferay.portal.NoSuchAddressException, 
			com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);
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
			listener.onBeforeRemove(findByPrimaryKey(addressId));
		}

		com.liferay.portal.model.Address address = persistence.remove(addressId);

		if (listener != null) {
			listener.onAfterRemove(address);
		}

		return address;
	}

	public static com.liferay.portal.model.Address update(
		com.liferay.portal.model.Address address)
		throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = address.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(address);
			}
			else {
				listener.onBeforeUpdate(address);
			}
		}

		address = persistence.update(address);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(address);
			}
			else {
				listener.onAfterUpdate(address);
			}
		}

		return address;
	}

	public static com.liferay.portal.model.Address findByPrimaryKey(
		java.lang.String addressId)
		throws com.liferay.portal.NoSuchAddressException, 
			com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(addressId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end) throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end);
	}

	public static java.util.List findByCompanyId(java.lang.String companyId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId(companyId, begin, end, obc);
	}

	public static com.liferay.portal.model.Address findByCompanyId_First(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchAddressException, 
			com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_First(companyId, obc);
	}

	public static com.liferay.portal.model.Address findByCompanyId_Last(
		java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchAddressException, 
			com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_Last(companyId, obc);
	}

	public static com.liferay.portal.model.Address[] findByCompanyId_PrevAndNext(
		java.lang.String addressId, java.lang.String companyId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchAddressException, 
			com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByCompanyId_PrevAndNext(addressId, companyId, obc);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portal.model.Address findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchAddressException, 
			com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portal.model.Address findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchAddressException, 
			com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portal.model.Address[] findByUserId_PrevAndNext(
		java.lang.String addressId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchAddressException, 
			com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(addressId, userId, obc);
	}

	public static java.util.List findByC_C(java.lang.String companyId,
		java.lang.String className) throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_C(companyId, className);
	}

	public static java.util.List findByC_C(java.lang.String companyId,
		java.lang.String className, int begin, int end)
		throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_C(companyId, className, begin, end);
	}

	public static java.util.List findByC_C(java.lang.String companyId,
		java.lang.String className, int begin, int end,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_C(companyId, className, begin, end, obc);
	}

	public static com.liferay.portal.model.Address findByC_C_First(
		java.lang.String companyId, java.lang.String className,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchAddressException, 
			com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_C_First(companyId, className, obc);
	}

	public static com.liferay.portal.model.Address findByC_C_Last(
		java.lang.String companyId, java.lang.String className,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchAddressException, 
			com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_C_Last(companyId, className, obc);
	}

	public static com.liferay.portal.model.Address[] findByC_C_PrevAndNext(
		java.lang.String addressId, java.lang.String companyId,
		java.lang.String className,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchAddressException, 
			com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_C_PrevAndNext(addressId, companyId,
			className, obc);
	}

	public static java.util.List findByC_C_C(java.lang.String companyId,
		java.lang.String className, java.lang.String classPK)
		throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_C_C(companyId, className, classPK);
	}

	public static java.util.List findByC_C_C(java.lang.String companyId,
		java.lang.String className, java.lang.String classPK, int begin, int end)
		throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_C_C(companyId, className, classPK, begin, end);
	}

	public static java.util.List findByC_C_C(java.lang.String companyId,
		java.lang.String className, java.lang.String classPK, int begin,
		int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_C_C(companyId, className, classPK, begin,
			end, obc);
	}

	public static com.liferay.portal.model.Address findByC_C_C_First(
		java.lang.String companyId, java.lang.String className,
		java.lang.String classPK,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchAddressException, 
			com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_C_C_First(companyId, className, classPK, obc);
	}

	public static com.liferay.portal.model.Address findByC_C_C_Last(
		java.lang.String companyId, java.lang.String className,
		java.lang.String classPK,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchAddressException, 
			com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_C_C_Last(companyId, className, classPK, obc);
	}

	public static com.liferay.portal.model.Address[] findByC_C_C_PrevAndNext(
		java.lang.String addressId, java.lang.String companyId,
		java.lang.String className, java.lang.String classPK,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.NoSuchAddressException, 
			com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByC_C_C_PrevAndNext(addressId, companyId,
			className, classPK, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByCompanyId(companyId);
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static void removeByC_C(java.lang.String companyId,
		java.lang.String className) throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByC_C(companyId, className);
	}

	public static void removeByC_C_C(java.lang.String companyId,
		java.lang.String className, java.lang.String classPK)
		throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByC_C_C(companyId, className, classPK);
	}

	public static int countByCompanyId(java.lang.String companyId)
		throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByCompanyId(companyId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	public static int countByC_C(java.lang.String companyId,
		java.lang.String className) throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByC_C(companyId, className);
	}

	public static int countByC_C_C(java.lang.String companyId,
		java.lang.String className, java.lang.String classPK)
		throws com.liferay.portal.SystemException {
		AddressPersistence persistence = (AddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByC_C_C(companyId, className, classPK);
	}

	private static final Log _log = LogFactory.getLog(AddressUtil.class);
}