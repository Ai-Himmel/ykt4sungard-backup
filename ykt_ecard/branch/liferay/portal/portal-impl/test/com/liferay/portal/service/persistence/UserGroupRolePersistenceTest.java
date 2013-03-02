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

import com.liferay.portal.NoSuchUserGroupRoleException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.UserGroupRole;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="UserGroupRolePersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UserGroupRolePersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (UserGroupRolePersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		UserGroupRolePK pk = new UserGroupRolePK(nextLong(), nextLong(),
				nextLong());

		UserGroupRole userGroupRole = _persistence.create(pk);

		assertNotNull(userGroupRole);

		assertEquals(userGroupRole.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		UserGroupRole newUserGroupRole = addUserGroupRole();

		_persistence.remove(newUserGroupRole);

		UserGroupRole existingUserGroupRole = _persistence.fetchByPrimaryKey(newUserGroupRole.getPrimaryKey());

		assertNull(existingUserGroupRole);
	}

	public void testUpdateNew() throws Exception {
		addUserGroupRole();
	}

	public void testUpdateExisting() throws Exception {
		UserGroupRolePK pk = new UserGroupRolePK(nextLong(), nextLong(),
				nextLong());

		UserGroupRole newUserGroupRole = _persistence.create(pk);

		_persistence.update(newUserGroupRole);

		UserGroupRole existingUserGroupRole = _persistence.findByPrimaryKey(newUserGroupRole.getPrimaryKey());

		assertEquals(existingUserGroupRole.getUserId(),
			newUserGroupRole.getUserId());
		assertEquals(existingUserGroupRole.getGroupId(),
			newUserGroupRole.getGroupId());
		assertEquals(existingUserGroupRole.getRoleId(),
			newUserGroupRole.getRoleId());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		UserGroupRole newUserGroupRole = addUserGroupRole();

		UserGroupRole existingUserGroupRole = _persistence.findByPrimaryKey(newUserGroupRole.getPrimaryKey());

		assertEquals(existingUserGroupRole, newUserGroupRole);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		UserGroupRolePK pk = new UserGroupRolePK(nextLong(), nextLong(),
				nextLong());

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchUserGroupRoleException");
		}
		catch (NoSuchUserGroupRoleException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		UserGroupRole newUserGroupRole = addUserGroupRole();

		UserGroupRole existingUserGroupRole = _persistence.fetchByPrimaryKey(newUserGroupRole.getPrimaryKey());

		assertEquals(existingUserGroupRole, newUserGroupRole);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		UserGroupRolePK pk = new UserGroupRolePK(nextLong(), nextLong(),
				nextLong());

		UserGroupRole missingUserGroupRole = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingUserGroupRole);
	}

	protected UserGroupRole addUserGroupRole() throws Exception {
		UserGroupRolePK pk = new UserGroupRolePK(nextLong(), nextLong(),
				nextLong());

		UserGroupRole userGroupRole = _persistence.create(pk);

		_persistence.update(userGroupRole);

		return userGroupRole;
	}

	private static final String _TX_IMPL = UserGroupRolePersistence.class.getName() +
		".transaction";
	private UserGroupRolePersistence _persistence;
}