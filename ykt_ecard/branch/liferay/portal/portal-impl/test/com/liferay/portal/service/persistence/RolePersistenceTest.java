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

import com.liferay.portal.NoSuchRoleException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.Role;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="RolePersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RolePersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (RolePersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		Role role = _persistence.create(pk);

		assertNotNull(role);

		assertEquals(role.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		Role newRole = addRole();

		_persistence.remove(newRole);

		Role existingRole = _persistence.fetchByPrimaryKey(newRole.getPrimaryKey());

		assertNull(existingRole);
	}

	public void testUpdateNew() throws Exception {
		addRole();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		Role newRole = _persistence.create(pk);

		newRole.setCompanyId(nextLong());
		newRole.setClassNameId(nextLong());
		newRole.setClassPK(nextLong());
		newRole.setName(randomString());
		newRole.setDescription(randomString());
		newRole.setType(nextInt());

		_persistence.update(newRole);

		Role existingRole = _persistence.findByPrimaryKey(newRole.getPrimaryKey());

		assertEquals(existingRole.getRoleId(), newRole.getRoleId());
		assertEquals(existingRole.getCompanyId(), newRole.getCompanyId());
		assertEquals(existingRole.getClassNameId(), newRole.getClassNameId());
		assertEquals(existingRole.getClassPK(), newRole.getClassPK());
		assertEquals(existingRole.getName(), newRole.getName());
		assertEquals(existingRole.getDescription(), newRole.getDescription());
		assertEquals(existingRole.getType(), newRole.getType());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		Role newRole = addRole();

		Role existingRole = _persistence.findByPrimaryKey(newRole.getPrimaryKey());

		assertEquals(existingRole, newRole);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchRoleException");
		}
		catch (NoSuchRoleException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		Role newRole = addRole();

		Role existingRole = _persistence.fetchByPrimaryKey(newRole.getPrimaryKey());

		assertEquals(existingRole, newRole);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		Role missingRole = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingRole);
	}

	protected Role addRole() throws Exception {
		long pk = nextLong();

		Role role = _persistence.create(pk);

		role.setCompanyId(nextLong());
		role.setClassNameId(nextLong());
		role.setClassPK(nextLong());
		role.setName(randomString());
		role.setDescription(randomString());
		role.setType(nextInt());

		_persistence.update(role);

		return role;
	}

	private static final String _TX_IMPL = RolePersistence.class.getName() +
		".transaction";
	private RolePersistence _persistence;
}