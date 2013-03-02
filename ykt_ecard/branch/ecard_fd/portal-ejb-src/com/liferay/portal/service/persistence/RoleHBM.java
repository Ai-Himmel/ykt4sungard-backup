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

package com.liferay.portal.service.persistence;

import java.util.Set;

/**
 * <a href="RoleHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class RoleHBM {
	protected RoleHBM() {
	}

	protected RoleHBM(String roleId) {
		_roleId = roleId;
	}

	protected RoleHBM(String roleId, String companyId, String name) {
		_roleId = roleId;
		_companyId = companyId;
		_name = name;
	}

	public String getPrimaryKey() {
		return _roleId;
	}

	protected void setPrimaryKey(String pk) {
		_roleId = pk;
	}

	protected String getRoleId() {
		return _roleId;
	}

	protected void setRoleId(String roleId) {
		_roleId = roleId;
	}

	protected String getCompanyId() {
		return _companyId;
	}

	protected void setCompanyId(String companyId) {
		_companyId = companyId;
	}

	protected String getName() {
		return _name;
	}

	protected void setName(String name) {
		_name = name;
	}

	protected Set getGroups() {
		return _groups;
	}

	protected void setGroups(Set groups) {
		_groups = groups;
	}

	protected Set getUsers() {
		return _users;
	}

	protected void setUsers(Set users) {
		_users = users;
	}

	private String _roleId;
	private String _companyId;
	private String _name;
	private Set _groups;
	private Set _users;
}