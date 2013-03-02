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
 * <a href="GroupHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class GroupHBM {
	protected GroupHBM() {
	}

	protected GroupHBM(String groupId) {
		_groupId = groupId;
	}

	protected GroupHBM(String groupId, String companyId, String parentGroupId,
		String name, String friendlyURL, String themeId, String colorSchemeId) {
		_groupId = groupId;
		_companyId = companyId;
		_parentGroupId = parentGroupId;
		_name = name;
		_friendlyURL = friendlyURL;
		_themeId = themeId;
		_colorSchemeId = colorSchemeId;
	}

	public String getPrimaryKey() {
		return _groupId;
	}

	protected void setPrimaryKey(String pk) {
		_groupId = pk;
	}

	protected String getGroupId() {
		return _groupId;
	}

	protected void setGroupId(String groupId) {
		_groupId = groupId;
	}

	protected String getCompanyId() {
		return _companyId;
	}

	protected void setCompanyId(String companyId) {
		_companyId = companyId;
	}

	protected String getParentGroupId() {
		return _parentGroupId;
	}

	protected void setParentGroupId(String parentGroupId) {
		_parentGroupId = parentGroupId;
	}

	protected String getName() {
		return _name;
	}

	protected void setName(String name) {
		_name = name;
	}

	protected String getFriendlyURL() {
		return _friendlyURL;
	}

	protected void setFriendlyURL(String friendlyURL) {
		_friendlyURL = friendlyURL;
	}

	protected String getThemeId() {
		return _themeId;
	}

	protected void setThemeId(String themeId) {
		_themeId = themeId;
	}

	protected String getColorSchemeId() {
		return _colorSchemeId;
	}

	protected void setColorSchemeId(String colorSchemeId) {
		_colorSchemeId = colorSchemeId;
	}

	protected Set getRoles() {
		return _roles;
	}

	protected void setRoles(Set roles) {
		_roles = roles;
	}

	protected Set getUsers() {
		return _users;
	}

	protected void setUsers(Set users) {
		_users = users;
	}

	private String _groupId;
	private String _companyId;
	private String _parentGroupId;
	private String _name;
	private String _friendlyURL;
	private String _themeId;
	private String _colorSchemeId;
	private Set _roles;
	private Set _users;
}