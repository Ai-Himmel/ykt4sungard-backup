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

package com.liferay.portal.jaas;

import java.io.Serializable;

import java.security.Principal;
import java.security.acl.Group;

import java.util.Collections;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

/**
 * <a href="PortalGroup.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class PortalGroup
	extends PortalPrincipal implements Group, Serializable {

	public PortalGroup(String groupName) {
		super(groupName);
	}

	public boolean addMember(Principal user) {
		if (!_members.containsKey(user)) {
			_members.put(user, user);

			return true;
		}
		else {
			return false;
		}
	}

	public boolean isMember(Principal member) {
		boolean isMember = _members.containsKey(member);

		if (!isMember) {
			Iterator itr = _members.values().iterator();

			while (!isMember && itr.hasNext()) {
				Object obj = itr.next();

				if (obj instanceof Group) {
					Group group = (Group)obj;

					isMember = group.isMember(member);
				}
			}
		}

		return isMember;
	}

	public Enumeration members() {
		return Collections.enumeration(_members.values());
	}

	public boolean removeMember(Principal user) {
		Object obj = _members.remove(user);

		if (obj != null) {
			return true;
		}
		else {
			return false;
		}
	}

	private Map _members = new HashMap();

}