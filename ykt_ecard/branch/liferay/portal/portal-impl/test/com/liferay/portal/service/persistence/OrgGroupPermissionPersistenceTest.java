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

import com.liferay.portal.NoSuchOrgGroupPermissionException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.OrgGroupPermission;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="OrgGroupPermissionPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class OrgGroupPermissionPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (OrgGroupPermissionPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		OrgGroupPermissionPK pk = new OrgGroupPermissionPK(nextLong(),
				nextLong(), nextLong());

		OrgGroupPermission orgGroupPermission = _persistence.create(pk);

		assertNotNull(orgGroupPermission);

		assertEquals(orgGroupPermission.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		OrgGroupPermission newOrgGroupPermission = addOrgGroupPermission();

		_persistence.remove(newOrgGroupPermission);

		OrgGroupPermission existingOrgGroupPermission = _persistence.fetchByPrimaryKey(newOrgGroupPermission.getPrimaryKey());

		assertNull(existingOrgGroupPermission);
	}

	public void testUpdateNew() throws Exception {
		addOrgGroupPermission();
	}

	public void testUpdateExisting() throws Exception {
		OrgGroupPermissionPK pk = new OrgGroupPermissionPK(nextLong(),
				nextLong(), nextLong());

		OrgGroupPermission newOrgGroupPermission = _persistence.create(pk);

		_persistence.update(newOrgGroupPermission);

		OrgGroupPermission existingOrgGroupPermission = _persistence.findByPrimaryKey(newOrgGroupPermission.getPrimaryKey());

		assertEquals(existingOrgGroupPermission.getOrganizationId(),
			newOrgGroupPermission.getOrganizationId());
		assertEquals(existingOrgGroupPermission.getGroupId(),
			newOrgGroupPermission.getGroupId());
		assertEquals(existingOrgGroupPermission.getPermissionId(),
			newOrgGroupPermission.getPermissionId());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		OrgGroupPermission newOrgGroupPermission = addOrgGroupPermission();

		OrgGroupPermission existingOrgGroupPermission = _persistence.findByPrimaryKey(newOrgGroupPermission.getPrimaryKey());

		assertEquals(existingOrgGroupPermission, newOrgGroupPermission);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		OrgGroupPermissionPK pk = new OrgGroupPermissionPK(nextLong(),
				nextLong(), nextLong());

		try {
			_persistence.findByPrimaryKey(pk);

			fail(
				"Missing entity did not throw NoSuchOrgGroupPermissionException");
		}
		catch (NoSuchOrgGroupPermissionException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		OrgGroupPermission newOrgGroupPermission = addOrgGroupPermission();

		OrgGroupPermission existingOrgGroupPermission = _persistence.fetchByPrimaryKey(newOrgGroupPermission.getPrimaryKey());

		assertEquals(existingOrgGroupPermission, newOrgGroupPermission);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		OrgGroupPermissionPK pk = new OrgGroupPermissionPK(nextLong(),
				nextLong(), nextLong());

		OrgGroupPermission missingOrgGroupPermission = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingOrgGroupPermission);
	}

	protected OrgGroupPermission addOrgGroupPermission()
		throws Exception {
		OrgGroupPermissionPK pk = new OrgGroupPermissionPK(nextLong(),
				nextLong(), nextLong());

		OrgGroupPermission orgGroupPermission = _persistence.create(pk);

		_persistence.update(orgGroupPermission);

		return orgGroupPermission;
	}

	private static final String _TX_IMPL = OrgGroupPermissionPersistence.class.getName() +
		".transaction";
	private OrgGroupPermissionPersistence _persistence;
}