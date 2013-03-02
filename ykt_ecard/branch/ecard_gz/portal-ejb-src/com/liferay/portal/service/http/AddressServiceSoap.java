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

package com.liferay.portal.service.http;

import com.liferay.portal.service.spring.AddressServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="AddressServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class AddressServiceSoap {
	public static com.liferay.portal.model.AddressModel addAddress(
		java.lang.String userId, java.lang.String className,
		java.lang.String classPK, java.lang.String description,
		java.lang.String street1, java.lang.String street2,
		java.lang.String city, java.lang.String state, java.lang.String zip,
		java.lang.String country, java.lang.String phone, java.lang.String fax,
		java.lang.String cell, java.lang.String pager, java.lang.String tollFree)
		throws RemoteException {
		try {
			com.liferay.portal.model.Address returnValue = AddressServiceUtil.addAddress(userId,
					className, classPK, description, street1, street2, city,
					state, zip, country, phone, fax, cell, pager, tollFree);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteAddress(java.lang.String addressId)
		throws RemoteException {
		try {
			AddressServiceUtil.deleteAddress(addressId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.AddressModel getAddress(
		java.lang.String addressId) throws RemoteException {
		try {
			com.liferay.portal.model.Address returnValue = AddressServiceUtil.getAddress(addressId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.AddressModel[] getAddresses(
		java.lang.String className, java.lang.String classPK)
		throws RemoteException {
		try {
			java.util.List returnValue = AddressServiceUtil.getAddresses(className,
					classPK);

			return (com.liferay.portal.model.Address[])returnValue.toArray(new com.liferay.portal.model.Address[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.AddressModel getPrimaryAddress(
		java.lang.String className, java.lang.String classPK)
		throws RemoteException {
		try {
			com.liferay.portal.model.Address returnValue = AddressServiceUtil.getPrimaryAddress(className,
					classPK);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.AddressModel updateAddress(
		java.lang.String addressId, java.lang.String description,
		java.lang.String street1, java.lang.String street2,
		java.lang.String city, java.lang.String state, java.lang.String zip,
		java.lang.String country, java.lang.String phone, java.lang.String fax,
		java.lang.String cell, java.lang.String pager, java.lang.String tollFree)
		throws RemoteException {
		try {
			com.liferay.portal.model.Address returnValue = AddressServiceUtil.updateAddress(addressId,
					description, street1, street2, city, state, zip, country,
					phone, fax, cell, pager, tollFree);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void updateAddresses(java.lang.String className,
		java.lang.String classPK, java.lang.String[] addressIds)
		throws RemoteException {
		try {
			AddressServiceUtil.updateAddresses(className, classPK, addressIds);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void updateAddressPriority(java.lang.String className,
		java.lang.String classPK, java.lang.String addressId, boolean priority)
		throws RemoteException {
		try {
			AddressServiceUtil.updateAddressPriority(className, classPK,
				addressId, priority);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasWrite(java.lang.String addressId)
		throws RemoteException {
		try {
			boolean returnValue = AddressServiceUtil.hasWrite(addressId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}