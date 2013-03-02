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

package com.liferay.portal.model;

import com.liferay.portal.service.persistence.OrgGroupRolePK;

import java.io.Serializable;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="OrgGroupRoleSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portal.service.http.OrgGroupRoleServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.http.OrgGroupRoleServiceSoap
 *
 */
public class OrgGroupRoleSoap implements Serializable {
	public static OrgGroupRoleSoap toSoapModel(OrgGroupRole model) {
		OrgGroupRoleSoap soapModel = new OrgGroupRoleSoap();

		soapModel.setOrganizationId(model.getOrganizationId());
		soapModel.setGroupId(model.getGroupId());
		soapModel.setRoleId(model.getRoleId());

		return soapModel;
	}

	public static OrgGroupRoleSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			OrgGroupRole model = (OrgGroupRole)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (OrgGroupRoleSoap[])soapModels.toArray(new OrgGroupRoleSoap[0]);
	}

	public OrgGroupRoleSoap() {
	}

	public OrgGroupRolePK getPrimaryKey() {
		return new OrgGroupRolePK(_organizationId, _groupId, _roleId);
	}

	public void setPrimaryKey(OrgGroupRolePK pk) {
		setOrganizationId(pk.organizationId);
		setGroupId(pk.groupId);
		setRoleId(pk.roleId);
	}

	public long getOrganizationId() {
		return _organizationId;
	}

	public void setOrganizationId(long organizationId) {
		_organizationId = organizationId;
	}

	public long getGroupId() {
		return _groupId;
	}

	public void setGroupId(long groupId) {
		_groupId = groupId;
	}

	public long getRoleId() {
		return _roleId;
	}

	public void setRoleId(long roleId) {
		_roleId = roleId;
	}

	private long _organizationId;
	private long _groupId;
	private long _roleId;
}