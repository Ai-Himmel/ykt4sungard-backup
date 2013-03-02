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

import com.liferay.portal.NoSuchUserGroupException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.UserGroup;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="UserGroupPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UserGroupPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (UserGroupPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		UserGroup userGroup = _persistence.create(pk);

		assertNotNull(userGroup);

		assertEquals(userGroup.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		UserGroup newUserGroup = addUserGroup();

		_persistence.remove(newUserGroup);

		UserGroup existingUserGroup = _persistence.fetchByPrimaryKey(newUserGroup.getPrimaryKey());

		assertNull(existingUserGroup);
	}

	public void testUpdateNew() throws Exception {
		addUserGroup();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		UserGroup newUserGroup = _persistence.create(pk);

		newUserGroup.setCompanyId(nextLong());
		newUserGroup.setParentUserGroupId(nextLong());
		newUserGroup.setName(randomString());
		newUserGroup.setDescription(randomString());

		_persistence.update(newUserGroup);

		UserGroup existingUserGroup = _persistence.findByPrimaryKey(newUserGroup.getPrimaryKey());

		assertEquals(existingUserGroup.getUserGroupId(),
			newUserGroup.getUserGroupId());
		assertEquals(existingUserGroup.getCompanyId(),
			newUserGroup.getCompanyId());
		assertEquals(existingUserGroup.getParentUserGroupId(),
			newUserGroup.getParentUserGroupId());
		assertEquals(existingUserGroup.getName(), newUserGroup.getName());
		assertEquals(existingUserGroup.getDescription(),
			newUserGroup.getDescription());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		UserGroup newUserGroup = addUserGroup();

		UserGroup existingUserGroup = _persistence.findByPrimaryKey(newUserGroup.getPrimaryKey());

		assertEquals(existingUserGroup, newUserGroup);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchUserGroupException");
		}
		catch (NoSuchUserGroupException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		UserGroup newUserGroup = addUserGroup();

		UserGroup existingUserGroup = _persistence.fetchByPrimaryKey(newUserGroup.getPrimaryKey());

		assertEquals(existingUserGroup, newUserGroup);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		UserGroup missingUserGroup = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingUserGroup);
	}

	protected UserGroup addUserGroup() throws Exception {
		long pk = nextLong();

		UserGroup userGroup = _persistence.create(pk);

		userGroup.setCompanyId(nextLong());
		userGroup.setParentUserGroupId(nextLong());
		userGroup.setName(randomString());
		userGroup.setDescription(randomString());

		_persistence.update(userGroup);

		return userGroup;
	}

	private static final String _TX_IMPL = UserGroupPersistence.class.getName() +
		".transaction";
	private UserGroupPersistence _persistence;
}