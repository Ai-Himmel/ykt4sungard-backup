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

package com.liferay.portal.jaas.ext.sun7;

import com.iplanet.ias.security.auth.realm.IASRealm;

import com.liferay.portal.util.Constants;

import com.sun.enterprise.security.acl.RoleMapper;
import com.sun.enterprise.security.auth.realm.BadRealmException;
import com.sun.enterprise.security.auth.realm.InvalidOperationException;
import com.sun.enterprise.security.auth.realm.NoSuchRealmException;
import com.sun.enterprise.security.auth.realm.NoSuchUserException;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Properties;

/**
 * <a href="PortalRealm.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class PortalRealm extends IASRealm {

	public PortalRealm() {
		_anyone = RoleMapper.getDefaultRole().getName();
		_groups = new HashMap();
	}

	protected void init(Properties props)
		throws BadRealmException, NoSuchRealmException {

		setProperty(
			IASRealm.JAAS_CONTEXT_PARAM,
			props.getProperty(IASRealm.JAAS_CONTEXT_PARAM));
	}

	public String getAuthType() {
		return Constants.REALM_NAME;
	}

	public Enumeration getGroupNames(String userId)
		throws InvalidOperationException, NoSuchUserException {

		List list = (List)_groups.get(userId);

		if (list == null) {
			return Collections.enumeration(new ArrayList());
		}
		else {
			return Collections.enumeration(list);
		}
	}

	public void setGroupNames(String userId, String[] groups) {
		List list = new ArrayList(groups.length + 1);

		for (int i = 0; i < groups.length; i++) {
			list.add(groups[i]);
		}

		list.add(_anyone);

		_groups.put(userId, list);
	}

	private String _anyone;
	private Map _groups;

}