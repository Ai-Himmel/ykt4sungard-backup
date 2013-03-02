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

import com.liferay.portal.NoSuchPermissionException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.Permission;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="PermissionPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PermissionPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (PermissionPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		Permission permission = _persistence.create(pk);

		assertNotNull(permission);

		assertEquals(permission.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		Permission newPermission = addPermission();

		_persistence.remove(newPermission);

		Permission existingPermission = _persistence.fetchByPrimaryKey(newPermission.getPrimaryKey());

		assertNull(existingPermission);
	}

	public void testUpdateNew() throws Exception {
		addPermission();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		Permission newPermission = _persistence.create(pk);

		newPermission.setCompanyId(nextLong());
		newPermission.setActionId(randomString());
		newPermission.setResourceId(nextLong());

		_persistence.update(newPermission);

		Permission existingPermission = _persistence.findByPrimaryKey(newPermission.getPrimaryKey());

		assertEquals(existingPermission.getPermissionId(),
			newPermission.getPermissionId());
		assertEquals(existingPermission.getCompanyId(),
			newPermission.getCompanyId());
		assertEquals(existingPermission.getActionId(),
			newPermission.getActionId());
		assertEquals(existingPermission.getResourceId(),
			newPermission.getResourceId());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		Permission newPermission = addPermission();

		Permission existingPermission = _persistence.findByPrimaryKey(newPermission.getPrimaryKey());

		assertEquals(existingPermission, newPermission);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchPermissionException");
		}
		catch (NoSuchPermissionException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		Permission newPermission = addPermission();

		Permission existingPermission = _persistence.fetchByPrimaryKey(newPermission.getPrimaryKey());

		assertEquals(existingPermission, newPermission);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		Permission missingPermission = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingPermission);
	}

	protected Permission addPermission() throws Exception {
		long pk = nextLong();

		Permission permission = _persistence.create(pk);

		permission.setCompanyId(nextLong());
		permission.setActionId(randomString());
		permission.setResourceId(nextLong());

		_persistence.update(permission);

		return permission;
	}

	private static final String _TX_IMPL = PermissionPersistence.class.getName() +
		".transaction";
	private PermissionPersistence _persistence;
}