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

package com.liferay.portal.service.persistence;

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;

import java.io.Serializable;

/**
 * <a href="OrgGroupRolePK.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class OrgGroupRolePK implements Comparable, Serializable {
	public long organizationId;
	public long groupId;
	public long roleId;

	public OrgGroupRolePK() {
	}

	public OrgGroupRolePK(long organizationId, long groupId, long roleId) {
		this.organizationId = organizationId;
		this.groupId = groupId;
		this.roleId = roleId;
	}

	public long getOrganizationId() {
		return organizationId;
	}

	public void setOrganizationId(long organizationId) {
		this.organizationId = organizationId;
	}

	public long getGroupId() {
		return groupId;
	}

	public void setGroupId(long groupId) {
		this.groupId = groupId;
	}

	public long getRoleId() {
		return roleId;
	}

	public void setRoleId(long roleId) {
		this.roleId = roleId;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		OrgGroupRolePK pk = (OrgGroupRolePK)obj;

		int value = 0;

		if (organizationId < pk.organizationId) {
			value = -1;
		}
		else if (organizationId > pk.organizationId) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		if (groupId < pk.groupId) {
			value = -1;
		}
		else if (groupId > pk.groupId) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		if (roleId < pk.roleId) {
			value = -1;
		}
		else if (roleId > pk.roleId) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		OrgGroupRolePK pk = null;

		try {
			pk = (OrgGroupRolePK)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		if ((organizationId == pk.organizationId) && (groupId == pk.groupId) &&
				(roleId == pk.roleId)) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return (String.valueOf(organizationId) + String.valueOf(groupId) +
		String.valueOf(roleId)).hashCode();
	}

	public String toString() {
		StringMaker sm = new StringMaker();

		sm.append(StringPool.OPEN_CURLY_BRACE);

		sm.append("organizationId");
		sm.append(StringPool.EQUAL);
		sm.append(organizationId);

		sm.append(StringPool.COMMA);
		sm.append(StringPool.SPACE);
		sm.append("groupId");
		sm.append(StringPool.EQUAL);
		sm.append(groupId);

		sm.append(StringPool.COMMA);
		sm.append(StringPool.SPACE);
		sm.append("roleId");
		sm.append(StringPool.EQUAL);
		sm.append(roleId);

		sm.append(StringPool.CLOSE_CURLY_BRACE);

		return sm.toString();
	}
}