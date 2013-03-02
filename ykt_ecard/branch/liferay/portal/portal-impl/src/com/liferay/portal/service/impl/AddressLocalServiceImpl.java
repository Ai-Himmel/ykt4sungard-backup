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

import com.liferay.portal.AddressCityException;
import com.liferay.portal.AddressStreetException;
import com.liferay.portal.AddressZipException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Address;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.ListTypeImpl;
import com.liferay.portal.service.base.AddressLocalServiceBaseImpl;
import com.liferay.portal.util.PortalUtil;

import java.rmi.RemoteException;

import java.util.Date;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="AddressLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Alexander Chow
 *
 */
public class AddressLocalServiceImpl extends AddressLocalServiceBaseImpl {

	public Address addAddress(
			long userId, String className, long classPK, String street1,
			String street2, String street3, String city, String zip,
			long regionId, long countryId, int typeId, boolean mailing,
			boolean primary)
		throws PortalException, SystemException {

		User user = userPersistence.findByPrimaryKey(userId);
		long classNameId = PortalUtil.getClassNameId(className);
		Date now = new Date();

		validate(
			0, user.getCompanyId(), classNameId, classPK, street1, city, zip,
			regionId, countryId, typeId, mailing, primary);

		long addressId = counterLocalService.increment();

		Address address = addressPersistence.create(addressId);

		address.setCompanyId(user.getCompanyId());
		address.setUserId(user.getUserId());
		address.setUserName(user.getFullName());
		address.setCreateDate(now);
		address.setModifiedDate(now);
		address.setClassNameId(classNameId);
		address.setClassPK(classPK);
		address.setStreet1(street1);
		address.setStreet2(street2);
		address.setStreet3(street3);
		address.setCity(city);
		address.setZip(zip);
		address.setRegionId(regionId);
		address.setCountryId(countryId);
		address.setTypeId(typeId);
		address.setMailing(mailing);
		address.setPrimary(primary);

		addressPersistence.update(address);

		return address;
	}

	public void deleteAddress(long addressId)
		throws PortalException, SystemException {

		addressPersistence.remove(addressId);
	}

	public void deleteAddresses(long companyId, String className, long classPK)
		throws SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		addressPersistence.removeByC_C_C(companyId, classNameId, classPK);
	}

	public Address getAddress(long addressId)
		throws PortalException, SystemException {

		return addressPersistence.findByPrimaryKey(addressId);
	}

	public List getAddresses() throws SystemException {
		return addressPersistence.findAll();
	}

	public List getAddresses(long companyId, String className, long classPK)
		throws SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		return addressPersistence.findByC_C_C(companyId, classNameId, classPK);
	}

	public Address updateAddress(
			long addressId, String street1, String street2, String street3,
			String city, String zip, long regionId, long countryId, int typeId,
			boolean mailing, boolean primary)
		throws PortalException, SystemException {

		validate(
			addressId, 0, 0, 0, street1, city, zip, regionId, countryId, typeId,
			mailing, primary);

		Address address = addressPersistence.findByPrimaryKey(addressId);

		address.setModifiedDate(new Date());
		address.setStreet1(street1);
		address.setStreet2(street2);
		address.setStreet3(street3);
		address.setCity(city);
		address.setZip(zip);
		address.setRegionId(regionId);
		address.setCountryId(countryId);
		address.setTypeId(typeId);
		address.setMailing(mailing);
		address.setPrimary(primary);

		addressPersistence.update(address);

		return address;
	}

	protected void validate(
			long addressId, long companyId, long classNameId, long classPK,
			String street1, String city, String zip, long regionId,
			long countryId, int typeId, boolean mailing, boolean primary)
		throws PortalException, SystemException {

		if (Validator.isNull(street1)) {
			throw new AddressStreetException();
		}
		else if (Validator.isNull(city)) {
			throw new AddressCityException();
		}
		else if (Validator.isNull(zip)) {
			throw new AddressZipException();
		}

		// Relax region and country requirement. See LEP-978.

		/*try {
			RegionServiceUtil.getRegion(regionId);

			CountryServiceUtil.getCountry(countryId);
		}
		catch (RemoteException re) {
			throw new SystemException(re);
		}*/

		if (addressId > 0) {
			Address address = addressPersistence.findByPrimaryKey(addressId);

			companyId = address.getCompanyId();
			classNameId = address.getClassNameId();
			classPK = address.getClassPK();
		}

		try {
			listTypeService.validate(typeId, classNameId, ListTypeImpl.ADDRESS);
		}
		catch (RemoteException re) {
			throw new SystemException(re);
		}

		validate(addressId, companyId, classNameId, classPK, mailing, primary);
	}

	protected void validate(
			long addressId, long companyId, long classNameId, long classPK,
			boolean mailing, boolean primary)
		throws PortalException, SystemException {

		// Check to make sure there isn't another address with the same company
		// id, class name, and class pk that also has mailing set to true

		if (mailing) {
			Iterator itr = addressPersistence.findByC_C_C_M(
				companyId, classNameId, classPK, mailing).iterator();

			while (itr.hasNext()) {
				Address address = (Address)itr.next();

				if ((addressId <= 0) ||
					(address.getAddressId() != addressId)) {

					address.setMailing(false);

					addressPersistence.update(address);
				}
			}
		}

		// Check to make sure there isn't another address with the same company
		// id, class name, and class pk that also has primary set to true

		if (primary) {
			Iterator itr = addressPersistence.findByC_C_C_P(
				companyId, classNameId, classPK, primary).iterator();

			while (itr.hasNext()) {
				Address address = (Address)itr.next();

				if ((addressId <= 0) ||
					(address.getAddressId() != addressId)) {

					address.setPrimary(false);

					addressPersistence.update(address);
				}
			}
		}
	}

}