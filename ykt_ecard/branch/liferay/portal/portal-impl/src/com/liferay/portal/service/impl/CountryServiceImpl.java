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

import com.liferay.portal.CountryA2Exception;
import com.liferay.portal.CountryA3Exception;
import com.liferay.portal.CountryIddException;
import com.liferay.portal.CountryNameException;
import com.liferay.portal.CountryNumberException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Country;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.base.CountryServiceBaseImpl;

import java.util.List;

/**
 * <a href="CountryServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CountryServiceImpl extends CountryServiceBaseImpl {

	public Country addCountry(
			String name, String a2, String a3, String number, String idd,
			boolean active)
		throws PortalException, SystemException {

		if (!getPermissionChecker().isOmniadmin()) {
			throw new PrincipalException();
		}

		if (Validator.isNull(name)) {
			throw new CountryNameException();
		}

		if (Validator.isNull(a2)) {
			throw new CountryA2Exception();
		}

		if (Validator.isNull(a3)) {
			throw new CountryA3Exception();
		}

		if (Validator.isNull(number)) {
			throw new CountryNumberException();
		}

		if (Validator.isNull(idd)) {
			throw new CountryIddException();
		}

		long countryId = counterLocalService.increment();

		Country country = countryPersistence.create(countryId);

		country.setName(name);
		country.setA2(a2);
		country.setA3(a3);
		country.setNumber(number);
		country.setIdd(idd);
		country.setActive(active);

		countryPersistence.update(country);

		return country;
	}

	public List getCountries() throws SystemException {
		return countryPersistence.findAll();
	}

	public List getCountries(boolean active) throws SystemException {
		return countryPersistence.findByActive(active);
	}

	public Country getCountry(long countryId)
		throws PortalException, SystemException {

		return countryPersistence.findByPrimaryKey(countryId);
	}

}