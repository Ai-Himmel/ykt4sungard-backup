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

import com.liferay.portal.NoSuchOrgGroupRoleException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.OrgGroupRole;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="OrgGroupRolePersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class OrgGroupRolePersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (OrgGroupRolePersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		OrgGroupRolePK pk = new OrgGroupRolePK(nextLong(), nextLong(),
				nextLong());

		OrgGroupRole orgGroupRole = _persistence.create(pk);

		assertNotNull(orgGroupRole);

		assertEquals(orgGroupRole.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		OrgGroupRole newOrgGroupRole = addOrgGroupRole();

		_persistence.remove(newOrgGroupRole);

		OrgGroupRole existingOrgGroupRole = _persistence.fetchByPrimaryKey(newOrgGroupRole.getPrimaryKey());

		assertNull(existingOrgGroupRole);
	}

	public void testUpdateNew() throws Exception {
		addOrgGroupRole();
	}

	public void testUpdateExisting() throws Exception {
		OrgGroupRolePK pk = new OrgGroupRolePK(nextLong(), nextLong(),
				nextLong());

		OrgGroupRole newOrgGroupRole = _persistence.create(pk);

		_persistence.update(newOrgGroupRole);

		OrgGroupRole existingOrgGroupRole = _persistence.findByPrimaryKey(newOrgGroupRole.getPrimaryKey());

		assertEquals(existingOrgGroupRole.getOrganizationId(),
			newOrgGroupRole.getOrganizationId());
		assertEquals(existingOrgGroupRole.getGroupId(),
			newOrgGroupRole.getGroupId());
		assertEquals(existingOrgGroupRole.getRoleId(),
			newOrgGroupRole.getRoleId());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		OrgGroupRole newOrgGroupRole = addOrgGroupRole();

		OrgGroupRole existingOrgGroupRole = _persistence.findByPrimaryKey(newOrgGroupRole.getPrimaryKey());

		assertEquals(existingOrgGroupRole, newOrgGroupRole);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		OrgGroupRolePK pk = new OrgGroupRolePK(nextLong(), nextLong(),
				nextLong());

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchOrgGroupRoleException");
		}
		catch (NoSuchOrgGroupRoleException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		OrgGroupRole newOrgGroupRole = addOrgGroupRole();

		OrgGroupRole existingOrgGroupRole = _persistence.fetchByPrimaryKey(newOrgGroupRole.getPrimaryKey());

		assertEquals(existingOrgGroupRole, newOrgGroupRole);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		OrgGroupRolePK pk = new OrgGroupRolePK(nextLong(), nextLong(),
				nextLong());

		OrgGroupRole missingOrgGroupRole = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingOrgGroupRole);
	}

	protected OrgGroupRole addOrgGroupRole() throws Exception {
		OrgGroupRolePK pk = new OrgGroupRolePK(nextLong(), nextLong(),
				nextLong());

		OrgGroupRole orgGroupRole = _persistence.create(pk);

		_persistence.update(orgGroupRole);

		return orgGroupRole;
	}

	private static final String _TX_IMPL = OrgGroupRolePersistence.class.getName() +
		".transaction";
	private OrgGroupRolePersistence _persistence;
}