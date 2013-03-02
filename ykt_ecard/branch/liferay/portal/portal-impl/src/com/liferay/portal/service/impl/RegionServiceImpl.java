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
import com.liferay.portal.RegionCodeException;
import com.liferay.portal.RegionNameException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Country;
import com.liferay.portal.model.Region;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.base.RegionServiceBaseImpl;

import java.util.List;

/**
 * <a href="RegionServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RegionServiceImpl extends RegionServiceBaseImpl {

	public Region addRegion(
			long countryId, String regionCode, String name, boolean active)
		throws PortalException, SystemException {

		if (!getPermissionChecker().isOmniadmin()) {
			throw new PrincipalException();
		}

		Country country = countryPersistence.findByPrimaryKey(countryId);

		if (Validator.isNull(regionCode)) {
			throw new RegionCodeException();
		}

		if (Validator.isNull(name)) {
			throw new RegionNameException();
		}

		long regionId = counterLocalService.increment();

		Region region = regionPersistence.create(regionId);

		region.setCountryId(countryId);
		region.setRegionCode(regionCode);
		region.setName(name);
		region.setActive(active);

		regionPersistence.update(region);

		return region;
	}

	public List getRegions() throws SystemException {
		return regionPersistence.findAll();
	}

	public List getRegions(long countryId) throws SystemException {
		return regionPersistence.findByCountryId(countryId);
	}

	public List getRegions(boolean active) throws SystemException {
		return regionPersistence.findByActive(active);
	}

	public List getRegions(long countryId, boolean active)
		throws SystemException {

		return regionPersistence.findByC_A(countryId, active);
	}

	public Region getRegion(long regionId)
		throws PortalException, SystemException {

		return regionPersistence.findByPrimaryKey(regionId);
	}

}