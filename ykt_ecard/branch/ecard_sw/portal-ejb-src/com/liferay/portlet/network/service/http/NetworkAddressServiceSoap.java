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

package com.liferay.portlet.network.service.http;

import com.liferay.portlet.network.service.spring.NetworkAddressServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="NetworkAddressServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class NetworkAddressServiceSoap {
	public static com.liferay.portlet.network.model.NetworkAddressModel addAddress(
		java.lang.String name, java.lang.String url, java.lang.String comments,
		java.lang.String notifyBy, long interval, boolean active)
		throws RemoteException {
		try {
			com.liferay.portlet.network.model.NetworkAddress returnValue = NetworkAddressServiceUtil.addAddress(name,
					url, comments, notifyBy, interval, active);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void checkAddress(
		com.liferay.portlet.network.model.NetworkAddress address)
		throws RemoteException {
		try {
			NetworkAddressServiceUtil.checkAddress(address);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void checkAddresses(long interval) throws RemoteException {
		try {
			NetworkAddressServiceUtil.checkAddresses(interval);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteAddress(java.lang.String addressId)
		throws RemoteException {
		try {
			NetworkAddressServiceUtil.deleteAddress(addressId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.network.model.NetworkAddressModel getAddress(
		java.lang.String addressId) throws RemoteException {
		try {
			com.liferay.portlet.network.model.NetworkAddress returnValue = NetworkAddressServiceUtil.getAddress(addressId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.network.model.NetworkAddressModel[] getAddresses()
		throws RemoteException {
		try {
			java.util.List returnValue = NetworkAddressServiceUtil.getAddresses();

			return (com.liferay.portlet.network.model.NetworkAddress[])returnValue.toArray(new com.liferay.portlet.network.model.NetworkAddress[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.network.model.NetworkAddressModel[] getAddresses(
		long interval) throws RemoteException {
		try {
			java.util.List returnValue = NetworkAddressServiceUtil.getAddresses(interval);

			return (com.liferay.portlet.network.model.NetworkAddress[])returnValue.toArray(new com.liferay.portlet.network.model.NetworkAddress[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.network.model.NetworkAddressModel[] getAddresses(
		long interval, boolean active) throws RemoteException {
		try {
			java.util.List returnValue = NetworkAddressServiceUtil.getAddresses(interval,
					active);

			return (com.liferay.portlet.network.model.NetworkAddress[])returnValue.toArray(new com.liferay.portlet.network.model.NetworkAddress[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getAddressesSize() throws RemoteException {
		try {
			int returnValue = NetworkAddressServiceUtil.getAddressesSize();

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.network.model.NetworkAddressModel updateAddress(
		java.lang.String addressId, java.lang.String name,
		java.lang.String url, java.lang.String comments,
		java.lang.String notifyBy, long interval, boolean active)
		throws RemoteException {
		try {
			com.liferay.portlet.network.model.NetworkAddress returnValue = NetworkAddressServiceUtil.updateAddress(addressId,
					name, url, comments, notifyBy, interval, active);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}