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

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Address;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Organization;
import com.liferay.portal.service.AddressLocalServiceUtil;
import com.liferay.portal.service.GroupLocalServiceUtil;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="OrganizationImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class OrganizationImpl
	extends OrganizationModelImpl implements Organization {

	public static final int DEFAULT_PARENT_ORGANIZATION_ID = 0;

	public static final int ANY_PARENT_ORGANIZATION_ID = -1;

	public static final int ANY_TYPE = -1;

	public static final int TYPE_REGULAR = 1;

	public static final String TYPE_REGULAR_LABEL = "regular";

	public static final int TYPE_LOCATION = 2;

	public static final String TYPE_LOCATION_LABEL = "location";

	public static int getType(boolean location) {
		int type = OrganizationImpl.TYPE_REGULAR;

		if (location) {
			type = OrganizationImpl.TYPE_LOCATION;
		}

		return type;
	}

	public static String getTypeLabel(int type) {
		if (type == TYPE_LOCATION) {
			return TYPE_LOCATION_LABEL;
		}
		else {
			return TYPE_REGULAR_LABEL;
		}
	}

	public OrganizationImpl() {
	}

	public boolean isRoot() {
		if (getParentOrganizationId() == DEFAULT_PARENT_ORGANIZATION_ID) {
			return true;
		}
		else {
			return false;
		}
	}

	public boolean isRegular() {
		return !isLocation();
	}

	public int getType() {
		if (isLocation()) {
			return TYPE_LOCATION;
		}
		else {
			return TYPE_REGULAR;
		}
	}

	public String getTypeLabel() {
		return getTypeLabel(getType());
	}

	public Group getGroup() {
		if (getOrganizationId() > 0) {
			try {
				return GroupLocalServiceUtil.getOrganizationGroup(
					getCompanyId(), getOrganizationId());
			}
			catch (Exception e) {
				_log.error(e);
			}
		}

		return new GroupImpl();
	}

	public Address getAddress() {
		Address address = null;

		try {
			List addresses = getAddresses();

			if (addresses.size() > 0) {
				address = (Address)addresses.get(0);
			}
		}
		catch (Exception e) {
			_log.error(e);
		}

		if (address == null) {
			address = new AddressImpl();
		}

		return address;
	}

	public List getAddresses() throws PortalException, SystemException {
		return AddressLocalServiceUtil.getAddresses(
			getCompanyId(), Organization.class.getName(), getOrganizationId());
	}

	private static Log _log = LogFactory.getLog(Organization.class);

}