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

package com.liferay.portal.model.impl;

import com.liferay.portal.model.Address;
import com.liferay.portal.model.Country;
import com.liferay.portal.model.ListType;
import com.liferay.portal.model.Region;
import com.liferay.portal.service.CountryServiceUtil;
import com.liferay.portal.service.ListTypeServiceUtil;
import com.liferay.portal.service.RegionServiceUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="AddressImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class AddressImpl extends AddressModelImpl implements Address {

	public AddressImpl() {
	}

	public Region getRegion() {
		Region region = null;

		try {
			region = RegionServiceUtil.getRegion(getRegionId());
		}
		catch (Exception e) {
			region = new RegionImpl();

			_log.warn(e);
		}

		return region;
	}

	public Country getCountry() {
		Country country = null;

		try {
			country = CountryServiceUtil.getCountry(getCountryId());
		}
		catch (Exception e) {
			country = new CountryImpl();

			_log.warn(e);
		}

		return country;
	}

	public ListType getType() {
		ListType type = null;

		try {
			type = ListTypeServiceUtil.getListType(getTypeId());
		}
		catch (Exception e) {
			type = new ListTypeImpl();

			_log.warn(e);
		}

		return type;
	}

	private static Log _log = LogFactory.getLog(AddressImpl.class);

}