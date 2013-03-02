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

package com.liferay.portlet.softwarecatalog.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portlet.softwarecatalog.LicenseNameException;
import com.liferay.portlet.softwarecatalog.model.SCLicense;
import com.liferay.portlet.softwarecatalog.service.base.SCLicenseLocalServiceBaseImpl;

import java.util.List;

/**
 * <a href="SCLicenseLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 * @author Brian Wing Shun Chan
 *
 */
public class SCLicenseLocalServiceImpl extends SCLicenseLocalServiceBaseImpl {

	public SCLicense addLicense(
			String name, String url, boolean openSource, boolean active,
			boolean recommended)
		throws PortalException, SystemException {

		validate(name);

		long licenseId = counterLocalService.increment();

		SCLicense license = scLicensePersistence.create(licenseId);

		license.setName(name);
		license.setUrl(url);
		license.setOpenSource(openSource);
		license.setActive(active);
		license.setRecommended(recommended);

		scLicensePersistence.update(license);

		return license;
	}

	public void deleteLicense(long licenseId)
		throws PortalException, SystemException {

		scLicensePersistence.remove(licenseId);
	}

	public SCLicense getLicense(long licenseId)
		throws PortalException, SystemException {

		return scLicensePersistence.findByPrimaryKey(licenseId);
	}

	public List getLicenses() throws SystemException {
		return scLicensePersistence.findAll();
	}

	public List getLicenses(int begin, int end) throws SystemException {
		return scLicensePersistence.findAll(begin, end);
	}

	public List getLicenses(boolean active, boolean recommended)
		throws SystemException {

		return scLicensePersistence.findByA_R(active, recommended);
	}

	public List getLicenses(
			boolean active, boolean recommended, int begin, int end)
		throws SystemException {

		return scLicensePersistence.findByA_R(active, recommended, begin, end);
	}

	public int getLicensesCount() throws SystemException {
		return scLicensePersistence.countAll();
	}

	public int getLicensesCount(boolean active, boolean recommended)
		throws SystemException {

		return scLicensePersistence.countByA_R(active, recommended);
	}

	public List getProductEntryLicenses(long productEntryId)
		throws PortalException, SystemException {

		return scProductEntryPersistence.getSCLicenses(productEntryId);
	}

	public SCLicense updateLicense(
			long licenseId, String name, String url, boolean openSource,
			boolean active, boolean recommended)
		throws PortalException, SystemException {

		validate(name);

		SCLicense license = scLicensePersistence.findByPrimaryKey(licenseId);

		license.setName(name);
		license.setUrl(url);
		license.setOpenSource(openSource);
		license.setActive(active);
		license.setRecommended(recommended);

		scLicensePersistence.update(license);

		return license;
	}

	protected void validate(String name) throws PortalException {
		if (Validator.isNull(name)) {
			throw new LicenseNameException();
		}
	}

}