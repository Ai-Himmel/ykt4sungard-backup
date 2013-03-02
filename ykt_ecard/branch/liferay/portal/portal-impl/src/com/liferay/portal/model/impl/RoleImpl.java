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

import com.liferay.portal.model.Role;
import com.liferay.portal.util.RoleNames;

/**
 * <a href="RoleImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RoleImpl extends RoleModelImpl implements Role {

	public static final String ADMINISTRATOR = RoleNames.ADMINISTRATOR;

	public static final String GUEST = RoleNames.GUEST;

	public static final String POWER_USER = RoleNames.POWER_USER;

	public static final String USER = RoleNames.USER;

	public static final String[] SYSTEM_ROLES = RoleNames.SYSTEM_ROLES;

	public static final String COMMUNITY_ADMINISTRATOR =
		RoleNames.COMMUNITY_ADMINISTRATOR;

	public static final String COMMUNITY_MEMBER = RoleNames.COMMUNITY_MEMBER;

	public static final String COMMUNITY_OWNER = RoleNames.COMMUNITY_OWNER;

	public static final String[] SYSTEM_COMMUNITY_ROLES =
		RoleNames.SYSTEM_COMMUNITY_ROLES;

	public static final String ORGANIZATION_ADMINISTRATOR =
		RoleNames.ORGANIZATION_ADMINISTRATOR;

	public static final String ORGANIZATION_MEMBER =
		RoleNames.ORGANIZATION_MEMBER;

	public static final String ORGANIZATION_OWNER =
		RoleNames.ORGANIZATION_OWNER;

	public static final String[] SYSTEM_ORGANIZATION_ROLES =
		RoleNames.SYSTEM_ORGANIZATION_ROLES;

	public static final int TYPE_COMMUNITY = 2;

	public static final String TYPE_COMMUNITY_LABEL = "community";

	public static final int TYPE_ORGANIZATION = 3;

	public static final String TYPE_ORGANIZATION_LABEL = "organization";

	public static final int TYPE_REGULAR = 1;

	public static final String TYPE_REGULAR_LABEL = "regular";

	public static String getTypeLabel(int type) {
		if (type == TYPE_COMMUNITY) {
			return TYPE_COMMUNITY_LABEL;
		}
		else if (type == TYPE_ORGANIZATION) {
			return TYPE_ORGANIZATION_LABEL;
		}
		else {
			return TYPE_REGULAR_LABEL;
		}
	}

	public RoleImpl() {
	}

	public String getTypeLabel() {
		return getTypeLabel(getType());
	}

}