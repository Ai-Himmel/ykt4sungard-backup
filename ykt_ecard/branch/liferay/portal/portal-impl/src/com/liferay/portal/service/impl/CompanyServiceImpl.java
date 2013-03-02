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
import com.liferay.portal.model.Company;
import com.liferay.portal.model.impl.RoleImpl;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.base.CompanyServiceBaseImpl;

import java.io.File;

/**
 * <a href="CompanyServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CompanyServiceImpl extends CompanyServiceBaseImpl {

	public Company addCompany(String webId, String virtualHost, String mx)
		throws PortalException, SystemException {

		if (!getPermissionChecker().isOmniadmin()) {
			throw new PrincipalException();
		}

		return companyLocalService.addCompany(webId, virtualHost, mx);
	}

	public Company updateCompany(long companyId, String virtualHost, String mx)
		throws PortalException, SystemException {

		if (!getPermissionChecker().isOmniadmin()) {
			throw new PrincipalException();
		}

		return companyLocalService.updateCompany(companyId, virtualHost, mx);
	}

	public Company updateCompany(
			long companyId, String virtualHost, String mx, String name,
			String legalName, String legalId, String legalType, String sicCode,
			String tickerSymbol, String industry, String type, String size)
		throws PortalException, SystemException {

		if (!roleLocalService.hasUserRole(
				getUserId(), companyId, RoleImpl.ADMINISTRATOR, true)) {

			throw new PrincipalException();
		}

		return companyLocalService.updateCompany(
			companyId, virtualHost, mx, name, legalName, legalId, legalType,
			sicCode, tickerSymbol, industry, type, size);
	}

	public void updateDisplay(
			long companyId, String languageId, String timeZoneId)
		throws PortalException, SystemException {

		if (!roleLocalService.hasUserRole(
				getUserId(), companyId, RoleImpl.ADMINISTRATOR, true)) {

			throw new PrincipalException();
		}

		companyLocalService.updateDisplay(companyId, languageId, timeZoneId);
	}

	public void updateLogo(long companyId, File file)
		throws PortalException, SystemException {

		if (!roleLocalService.hasUserRole(
				getUserId(), companyId, RoleImpl.ADMINISTRATOR, true)) {

			throw new PrincipalException();
		}

		companyLocalService.updateLogo(companyId, file);
	}

	public void updateSecurity(
			long companyId, String authType, boolean autoLogin,
			boolean sendPassword, boolean strangers, boolean strangersWithMx,
			boolean strangersVerify, boolean communityLogo)
		throws PortalException, SystemException {

		if (!roleLocalService.hasUserRole(
				getUserId(), companyId, RoleImpl.ADMINISTRATOR, true)) {

			throw new PrincipalException();
		}

		companyLocalService.updateSecurity(
			companyId, authType, autoLogin, sendPassword, strangers,
			strangersWithMx, strangersVerify, communityLogo);
	}

}