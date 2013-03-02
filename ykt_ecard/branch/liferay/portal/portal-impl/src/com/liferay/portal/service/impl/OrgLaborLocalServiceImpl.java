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
import com.liferay.portal.model.OrgLabor;
import com.liferay.portal.model.impl.ListTypeImpl;
import com.liferay.portal.service.base.OrgLaborLocalServiceBaseImpl;

import java.rmi.RemoteException;

import java.util.List;

/**
 * <a href="OrgLaborLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class OrgLaborLocalServiceImpl extends OrgLaborLocalServiceBaseImpl {

	public OrgLabor addOrgLabor(
			long organizationId, int typeId, int sunOpen, int sunClose,
			int monOpen, int monClose, int tueOpen, int tueClose, int wedOpen,
			int wedClose, int thuOpen, int thuClose, int friOpen, int friClose,
			int satOpen, int satClose)
		throws PortalException, SystemException {

		validate(typeId);

		long orgLaborId = counterLocalService.increment();

		OrgLabor orgLabor = orgLaborPersistence.create(orgLaborId);

		orgLabor.setOrganizationId(organizationId);
		orgLabor.setTypeId(typeId);
		orgLabor.setSunOpen(sunOpen);
		orgLabor.setSunClose(sunClose);
		orgLabor.setMonOpen(monOpen);
		orgLabor.setMonClose(monClose);
		orgLabor.setTueOpen(tueOpen);
		orgLabor.setTueClose(tueClose);
		orgLabor.setWedOpen(wedOpen);
		orgLabor.setWedClose(wedClose);
		orgLabor.setThuOpen(thuOpen);
		orgLabor.setThuClose(thuClose);
		orgLabor.setFriOpen(friOpen);
		orgLabor.setFriClose(friClose);
		orgLabor.setSatOpen(satOpen);
		orgLabor.setSatClose(satClose);

		orgLaborPersistence.update(orgLabor);

		return orgLabor;
	}

	public void deleteOrgLabor(long orgLaborId)
		throws PortalException, SystemException {

		orgLaborPersistence.remove(orgLaborId);
	}

	public OrgLabor getOrgLabor(long orgLaborId)
		throws PortalException, SystemException {

		return orgLaborPersistence.findByPrimaryKey(orgLaborId);
	}

	public List getOrgLabors(long organizationId) throws SystemException {
		return orgLaborPersistence.findByOrganizationId(organizationId);
	}

	public OrgLabor updateOrgLabor(
			long orgLaborId, int sunOpen, int sunClose, int monOpen,
			int monClose, int tueOpen, int tueClose, int wedOpen, int wedClose,
			int thuOpen, int thuClose, int friOpen, int friClose, int satOpen,
			int satClose)
		throws PortalException, SystemException {

		OrgLabor orgLabor = orgLaborPersistence.findByPrimaryKey(orgLaborId);

		orgLabor.setSunOpen(sunOpen);
		orgLabor.setSunClose(sunClose);
		orgLabor.setMonOpen(monOpen);
		orgLabor.setMonClose(monClose);
		orgLabor.setTueOpen(tueOpen);
		orgLabor.setTueClose(tueClose);
		orgLabor.setWedOpen(wedOpen);
		orgLabor.setWedClose(wedClose);
		orgLabor.setThuOpen(thuOpen);
		orgLabor.setThuClose(thuClose);
		orgLabor.setFriOpen(friOpen);
		orgLabor.setFriClose(friClose);
		orgLabor.setSatOpen(satOpen);
		orgLabor.setSatClose(satClose);

		orgLaborPersistence.update(orgLabor);

		return orgLabor;
	}

	protected void validate(int typeId)
		throws PortalException, SystemException {

		try {
			listTypeService.validate(typeId, ListTypeImpl.ORGANIZATION_SERVICE);
		}
		catch (RemoteException re) {
			throw new SystemException(re);
		}
	}

}