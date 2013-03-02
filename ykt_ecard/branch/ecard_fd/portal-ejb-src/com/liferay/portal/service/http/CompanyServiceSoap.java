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

import com.liferay.portal.service.spring.CompanyServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="CompanyServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class CompanyServiceSoap {
	public static com.liferay.portal.model.CompanyModel getCompany()
		throws RemoteException {
		try {
			com.liferay.portal.model.Company returnValue = CompanyServiceUtil.getCompany();

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.CompanyModel getCompany(
		java.lang.String companyId) throws RemoteException {
		try {
			com.liferay.portal.model.Company returnValue = CompanyServiceUtil.getCompany(companyId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.CompanyModel[] getGroups()
		throws RemoteException {
		try {
			java.util.List returnValue = CompanyServiceUtil.getGroups();

			return (com.liferay.portal.model.Company[])returnValue.toArray(new com.liferay.portal.model.Company[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.CompanyModel[] getRoles()
		throws RemoteException {
		try {
			java.util.List returnValue = CompanyServiceUtil.getRoles();

			return (com.liferay.portal.model.Company[])returnValue.toArray(new com.liferay.portal.model.Company[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.CompanyModel[] getUsers()
		throws RemoteException {
		try {
			java.util.List returnValue = CompanyServiceUtil.getUsers();

			return (com.liferay.portal.model.Company[])returnValue.toArray(new com.liferay.portal.model.Company[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.util.lucene.Hits search(
		java.lang.String companyId, java.lang.String keywords)
		throws RemoteException {
		try {
			com.liferay.util.lucene.Hits returnValue = CompanyServiceUtil.search(companyId,
					keywords);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.util.lucene.Hits search(
		java.lang.String companyId, java.lang.String groupId,
		java.lang.String keywords) throws RemoteException {
		try {
			com.liferay.util.lucene.Hits returnValue = CompanyServiceUtil.search(companyId,
					groupId, keywords);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portal.model.CompanyModel updateCompany(
		java.lang.String portalURL, java.lang.String homeURL,
		java.lang.String mx, java.lang.String name, java.lang.String shortName,
		java.lang.String type, java.lang.String size, java.lang.String street,
		java.lang.String city, java.lang.String state, java.lang.String zip,
		java.lang.String phone, java.lang.String fax,
		java.lang.String emailAddress) throws RemoteException {
		try {
			com.liferay.portal.model.Company returnValue = CompanyServiceUtil.updateCompany(portalURL,
					homeURL, mx, name, shortName, type, size, street, city,
					state, zip, phone, fax, emailAddress);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void updateDefaultUser(java.lang.String languageId,
		java.lang.String timeZoneId, java.lang.String themeId,
		java.lang.String colorSchemeId, java.lang.String resolution)
		throws RemoteException {
		try {
			CompanyServiceUtil.updateDefaultUser(languageId, timeZoneId,
				themeId, colorSchemeId, resolution);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}