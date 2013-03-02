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

import com.liferay.portal.NoSuchOrgLaborException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.OrgLabor;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="OrgLaborPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class OrgLaborPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (OrgLaborPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		OrgLabor orgLabor = _persistence.create(pk);

		assertNotNull(orgLabor);

		assertEquals(orgLabor.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		OrgLabor newOrgLabor = addOrgLabor();

		_persistence.remove(newOrgLabor);

		OrgLabor existingOrgLabor = _persistence.fetchByPrimaryKey(newOrgLabor.getPrimaryKey());

		assertNull(existingOrgLabor);
	}

	public void testUpdateNew() throws Exception {
		addOrgLabor();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		OrgLabor newOrgLabor = _persistence.create(pk);

		newOrgLabor.setOrganizationId(nextLong());
		newOrgLabor.setTypeId(nextInt());
		newOrgLabor.setSunOpen(nextInt());
		newOrgLabor.setSunClose(nextInt());
		newOrgLabor.setMonOpen(nextInt());
		newOrgLabor.setMonClose(nextInt());
		newOrgLabor.setTueOpen(nextInt());
		newOrgLabor.setTueClose(nextInt());
		newOrgLabor.setWedOpen(nextInt());
		newOrgLabor.setWedClose(nextInt());
		newOrgLabor.setThuOpen(nextInt());
		newOrgLabor.setThuClose(nextInt());
		newOrgLabor.setFriOpen(nextInt());
		newOrgLabor.setFriClose(nextInt());
		newOrgLabor.setSatOpen(nextInt());
		newOrgLabor.setSatClose(nextInt());

		_persistence.update(newOrgLabor);

		OrgLabor existingOrgLabor = _persistence.findByPrimaryKey(newOrgLabor.getPrimaryKey());

		assertEquals(existingOrgLabor.getOrgLaborId(),
			newOrgLabor.getOrgLaborId());
		assertEquals(existingOrgLabor.getOrganizationId(),
			newOrgLabor.getOrganizationId());
		assertEquals(existingOrgLabor.getTypeId(), newOrgLabor.getTypeId());
		assertEquals(existingOrgLabor.getSunOpen(), newOrgLabor.getSunOpen());
		assertEquals(existingOrgLabor.getSunClose(), newOrgLabor.getSunClose());
		assertEquals(existingOrgLabor.getMonOpen(), newOrgLabor.getMonOpen());
		assertEquals(existingOrgLabor.getMonClose(), newOrgLabor.getMonClose());
		assertEquals(existingOrgLabor.getTueOpen(), newOrgLabor.getTueOpen());
		assertEquals(existingOrgLabor.getTueClose(), newOrgLabor.getTueClose());
		assertEquals(existingOrgLabor.getWedOpen(), newOrgLabor.getWedOpen());
		assertEquals(existingOrgLabor.getWedClose(), newOrgLabor.getWedClose());
		assertEquals(existingOrgLabor.getThuOpen(), newOrgLabor.getThuOpen());
		assertEquals(existingOrgLabor.getThuClose(), newOrgLabor.getThuClose());
		assertEquals(existingOrgLabor.getFriOpen(), newOrgLabor.getFriOpen());
		assertEquals(existingOrgLabor.getFriClose(), newOrgLabor.getFriClose());
		assertEquals(existingOrgLabor.getSatOpen(), newOrgLabor.getSatOpen());
		assertEquals(existingOrgLabor.getSatClose(), newOrgLabor.getSatClose());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		OrgLabor newOrgLabor = addOrgLabor();

		OrgLabor existingOrgLabor = _persistence.findByPrimaryKey(newOrgLabor.getPrimaryKey());

		assertEquals(existingOrgLabor, newOrgLabor);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchOrgLaborException");
		}
		catch (NoSuchOrgLaborException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		OrgLabor newOrgLabor = addOrgLabor();

		OrgLabor existingOrgLabor = _persistence.fetchByPrimaryKey(newOrgLabor.getPrimaryKey());

		assertEquals(existingOrgLabor, newOrgLabor);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		OrgLabor missingOrgLabor = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingOrgLabor);
	}

	protected OrgLabor addOrgLabor() throws Exception {
		long pk = nextLong();

		OrgLabor orgLabor = _persistence.create(pk);

		orgLabor.setOrganizationId(nextLong());
		orgLabor.setTypeId(nextInt());
		orgLabor.setSunOpen(nextInt());
		orgLabor.setSunClose(nextInt());
		orgLabor.setMonOpen(nextInt());
		orgLabor.setMonClose(nextInt());
		orgLabor.setTueOpen(nextInt());
		orgLabor.setTueClose(nextInt());
		orgLabor.setWedOpen(nextInt());
		orgLabor.setWedClose(nextInt());
		orgLabor.setThuOpen(nextInt());
		orgLabor.setThuClose(nextInt());
		orgLabor.setFriOpen(nextInt());
		orgLabor.setFriClose(nextInt());
		orgLabor.setSatOpen(nextInt());
		orgLabor.setSatClose(nextInt());

		_persistence.update(orgLabor);

		return orgLabor;
	}

	private static final String _TX_IMPL = OrgLaborPersistence.class.getName() +
		".transaction";
	private OrgLaborPersistence _persistence;
}