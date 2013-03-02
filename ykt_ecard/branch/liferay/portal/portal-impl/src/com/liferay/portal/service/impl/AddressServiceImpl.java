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

package com.liferay.portal.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.model.Address;
import com.liferay.portal.service.base.AddressServiceBaseImpl;
import com.liferay.portal.service.permission.CommonPermissionUtil;

import java.util.List;

/**
 * <a href="AddressServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Alexander Chow
 *
 */
public class AddressServiceImpl extends AddressServiceBaseImpl {

	public Address addAddress(
			String className, long classPK, String street1, String street2,
			String street3, String city, String zip, long regionId,
			long countryId, int typeId, boolean mailing, boolean primary)
		throws PortalException, SystemException {

		CommonPermissionUtil.check(
			getPermissionChecker(), className, classPK, ActionKeys.UPDATE);

		return addressLocalService.addAddress(
			getUserId(), className, classPK, street1, street2, street3, city,
			zip, regionId, countryId, typeId, mailing, primary);
	}

	public void deleteAddress(long addressId)
		throws PortalException, SystemException {

		Address address = addressPersistence.findByPrimaryKey(addressId);

		CommonPermissionUtil.check(
			getPermissionChecker(), address.getClassNameId(),
			address.getClassPK(), ActionKeys.UPDATE);

		addressLocalService.deleteAddress(addressId);
	}

	public Address getAddress(long addressId)
		throws PortalException, SystemException {

		Address address = addressPersistence.findByPrimaryKey(addressId);

		CommonPermissionUtil.check(
			getPermissionChecker(), address.getClassNameId(),
			address.getClassPK(), ActionKeys.VIEW);

		return address;
	}

	public List getAddresses(String className, long classPK)
		throws PortalException, SystemException {

		CommonPermissionUtil.check(
			getPermissionChecker(), className, classPK, ActionKeys.VIEW);

		return addressLocalService.getAddresses(
			getUser().getCompanyId(), className, classPK);
	}

	public Address updateAddress(
			long addressId, String street1, String street2, String street3,
			String city, String zip, long regionId, long countryId, int typeId,
			boolean mailing, boolean primary)
		throws PortalException, SystemException {

		Address address = addressPersistence.findByPrimaryKey(addressId);

		CommonPermissionUtil.check(
			getPermissionChecker(), address.getClassNameId(),
			address.getClassPK(), ActionKeys.UPDATE);

		return addressLocalService.updateAddress(
			addressId, street1, street2, street3, city, zip, regionId,
			countryId, typeId, mailing, primary);
	}

}