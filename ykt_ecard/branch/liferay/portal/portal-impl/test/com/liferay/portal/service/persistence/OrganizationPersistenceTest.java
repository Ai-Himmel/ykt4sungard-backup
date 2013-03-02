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

import com.liferay.portal.NoSuchOrganizationException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.Organization;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="OrganizationPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class OrganizationPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (OrganizationPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		Organization organization = _persistence.create(pk);

		assertNotNull(organization);

		assertEquals(organization.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		Organization newOrganization = addOrganization();

		_persistence.remove(newOrganization);

		Organization existingOrganization = _persistence.fetchByPrimaryKey(newOrganization.getPrimaryKey());

		assertNull(existingOrganization);
	}

	public void testUpdateNew() throws Exception {
		addOrganization();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		Organization newOrganization = _persistence.create(pk);

		newOrganization.setCompanyId(nextLong());
		newOrganization.setParentOrganizationId(nextLong());
		newOrganization.setName(randomString());
		newOrganization.setLocation(randomBoolean());
		newOrganization.setRecursable(randomBoolean());
		newOrganization.setRegionId(nextLong());
		newOrganization.setCountryId(nextLong());
		newOrganization.setStatusId(nextInt());
		newOrganization.setComments(randomString());

		_persistence.update(newOrganization);

		Organization existingOrganization = _persistence.findByPrimaryKey(newOrganization.getPrimaryKey());

		assertEquals(existingOrganization.getOrganizationId(),
			newOrganization.getOrganizationId());
		assertEquals(existingOrganization.getCompanyId(),
			newOrganization.getCompanyId());
		assertEquals(existingOrganization.getParentOrganizationId(),
			newOrganization.getParentOrganizationId());
		assertEquals(existingOrganization.getName(), newOrganization.getName());
		assertEquals(existingOrganization.getLocation(),
			newOrganization.getLocation());
		assertEquals(existingOrganization.getRecursable(),
			newOrganization.getRecursable());
		assertEquals(existingOrganization.getRegionId(),
			newOrganization.getRegionId());
		assertEquals(existingOrganization.getCountryId(),
			newOrganization.getCountryId());
		assertEquals(existingOrganization.getStatusId(),
			newOrganization.getStatusId());
		assertEquals(existingOrganization.getComments(),
			newOrganization.getComments());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		Organization newOrganization = addOrganization();

		Organization existingOrganization = _persistence.findByPrimaryKey(newOrganization.getPrimaryKey());

		assertEquals(existingOrganization, newOrganization);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchOrganizationException");
		}
		catch (NoSuchOrganizationException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		Organization newOrganization = addOrganization();

		Organization existingOrganization = _persistence.fetchByPrimaryKey(newOrganization.getPrimaryKey());

		assertEquals(existingOrganization, newOrganization);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		Organization missingOrganization = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingOrganization);
	}

	protected Organization addOrganization() throws Exception {
		long pk = nextLong();

		Organization organization = _persistence.create(pk);

		organization.setCompanyId(nextLong());
		organization.setParentOrganizationId(nextLong());
		organization.setName(randomString());
		organization.setLocation(randomBoolean());
		organization.setRecursable(randomBoolean());
		organization.setRegionId(nextLong());
		organization.setCountryId(nextLong());
		organization.setStatusId(nextInt());
		organization.setComments(randomString());

		_persistence.update(organization);

		return organization;
	}

	private static final String _TX_IMPL = OrganizationPersistence.class.getName() +
		".transaction";
	private OrganizationPersistence _persistence;
}