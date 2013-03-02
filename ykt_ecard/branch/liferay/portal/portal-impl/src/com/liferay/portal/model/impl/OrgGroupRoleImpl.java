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

import com.liferay.portal.model.Group;
import com.liferay.portal.model.OrgGroupRole;
import com.liferay.portal.model.Organization;

import java.util.Iterator;
import java.util.List;

/**
 * <a href="OrgGroupRoleImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class OrgGroupRoleImpl
	extends OrgGroupRoleModelImpl implements OrgGroupRole {

	public OrgGroupRoleImpl() {
	}

	public boolean containsOrganization(List organizations) {
		if (organizations == null) {
			return false;
		}
		else {
			Iterator itr = organizations.iterator();

			while (itr.hasNext()) {
				Organization organization = (Organization)itr.next();

				if (organization.getOrganizationId() == getOrganizationId()) {
					return true;
				}
			}
		}

		return false;
	}

	public boolean containsGroup(List groups) {
		if (groups == null) {
			return false;
		}
		else {
			Iterator itr = groups.iterator();

			while (itr.hasNext()) {
				Group group = (Group)itr.next();

				if (group.getGroupId() == getGroupId()) {
					return true;
				}
			}
		}

		return false;
	}

}