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

package com.liferay.portal.jaas.ext.pramati;

import com.pramati.services.security.UserManagerException;
import com.pramati.services.security.spi.UserManager;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * <a href="PortalUserManager.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class PortalUserManager implements UserManager {

	public void initialize(String realmName, Map options)
		throws UserManagerException {

		_options = options;
	}

	public Map getOptions() {
		return _options;
	}

	public boolean addUser(String userName, String password)
		throws UserManagerException {

		return true;
	}

	public boolean addUser(String userName, String password, List groups)
		throws UserManagerException {

		return true;
	}

	public boolean modifyUser(String userName, List groups)
		throws UserManagerException {

		return true;
	}

	public boolean removeUser(String userName) throws UserManagerException {
		return true;
	}

	public boolean changePassword(
			String userName, String oldPassword, String newPassword)
		throws UserManagerException {

		return true;
	}

	public boolean addGroup(String groupName, List users, List groups)
		throws UserManagerException {

		return true;
	}

	public boolean modifyGroup(String groupName, List users, List groups)
		throws UserManagerException {

		return true;
	}

	public boolean removeGroup(String groupName) throws UserManagerException {
		return true;
	}

	public List getAllUsers() throws UserManagerException {
		return new ArrayList();
	}

	public List getAllGroups() throws UserManagerException {
		return new ArrayList();
	}

	public List getAllGroupsForUser(String userName)
		throws UserManagerException {

		return new ArrayList();
	}

	public List getChildGroupsForGroup(String groupName)
		throws UserManagerException {

		return new ArrayList();
	}

	public List getParentGroupsForGroup(String groupName)
		throws UserManagerException {

		return new ArrayList();
	}

	public boolean removeUsersForGroup(List users, String groupName)
		throws UserManagerException {

		return true;
	}

	public boolean removeChildGroupsForGroup(
			List childGroups, String groupName)
		throws UserManagerException {

		return true;
	}

	public List getAllUsersForGroup(String groupName)
		throws UserManagerException {

		return new ArrayList();
	}

	public boolean canEditUsers() {
		return false;
	}

	public boolean canEditGroups() {
		return false;
	}

	private Map _options;

}