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

import java.io.Serializable;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="UserGroupSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portal.service.http.UserGroupServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.http.UserGroupServiceSoap
 *
 */
public class UserGroupSoap implements Serializable {
	public static UserGroupSoap toSoapModel(UserGroup model) {
		UserGroupSoap soapModel = new UserGroupSoap();

		soapModel.setUserGroupId(model.getUserGroupId());
		soapModel.setCompanyId(model.getCompanyId());
		soapModel.setParentUserGroupId(model.getParentUserGroupId());
		soapModel.setName(model.getName());
		soapModel.setDescription(model.getDescription());

		return soapModel;
	}

	public static UserGroupSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			UserGroup model = (UserGroup)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (UserGroupSoap[])soapModels.toArray(new UserGroupSoap[0]);
	}

	public UserGroupSoap() {
	}

	public long getPrimaryKey() {
		return _userGroupId;
	}

	public void setPrimaryKey(long pk) {
		setUserGroupId(pk);
	}

	public long getUserGroupId() {
		return _userGroupId;
	}

	public void setUserGroupId(long userGroupId) {
		_userGroupId = userGroupId;
	}

	public long getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(long companyId) {
		_companyId = companyId;
	}

	public long getParentUserGroupId() {
		return _parentUserGroupId;
	}

	public void setParentUserGroupId(long parentUserGroupId) {
		_parentUserGroupId = parentUserGroupId;
	}

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		_name = name;
	}

	public String getDescription() {
		return _description;
	}

	public void setDescription(String description) {
		_description = description;
	}

	private long _userGroupId;
	private long _companyId;
	private long _parentUserGroupId;
	private String _name;
	private String _description;
}