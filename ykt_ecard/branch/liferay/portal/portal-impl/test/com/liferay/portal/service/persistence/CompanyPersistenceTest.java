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

import com.liferay.portal.NoSuchCompanyException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.Company;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="CompanyPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CompanyPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (CompanyPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		Company company = _persistence.create(pk);

		assertNotNull(company);

		assertEquals(company.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		Company newCompany = addCompany();

		_persistence.remove(newCompany);

		Company existingCompany = _persistence.fetchByPrimaryKey(newCompany.getPrimaryKey());

		assertNull(existingCompany);
	}

	public void testUpdateNew() throws Exception {
		addCompany();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		Company newCompany = _persistence.create(pk);

		newCompany.setAccountId(nextLong());
		newCompany.setWebId(randomString());
		newCompany.setKey(randomString());
		newCompany.setVirtualHost(randomString());
		newCompany.setMx(randomString());
		newCompany.setLogoId(nextLong());

		_persistence.update(newCompany);

		Company existingCompany = _persistence.findByPrimaryKey(newCompany.getPrimaryKey());

		assertEquals(existingCompany.getCompanyId(), newCompany.getCompanyId());
		assertEquals(existingCompany.getAccountId(), newCompany.getAccountId());
		assertEquals(existingCompany.getWebId(), newCompany.getWebId());
		assertEquals(existingCompany.getKey(), newCompany.getKey());
		assertEquals(existingCompany.getVirtualHost(),
			newCompany.getVirtualHost());
		assertEquals(existingCompany.getMx(), newCompany.getMx());
		assertEquals(existingCompany.getLogoId(), newCompany.getLogoId());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		Company newCompany = addCompany();

		Company existingCompany = _persistence.findByPrimaryKey(newCompany.getPrimaryKey());

		assertEquals(existingCompany, newCompany);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchCompanyException");
		}
		catch (NoSuchCompanyException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		Company newCompany = addCompany();

		Company existingCompany = _persistence.fetchByPrimaryKey(newCompany.getPrimaryKey());

		assertEquals(existingCompany, newCompany);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		Company missingCompany = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingCompany);
	}

	protected Company addCompany() throws Exception {
		long pk = nextLong();

		Company company = _persistence.create(pk);

		company.setAccountId(nextLong());
		company.setWebId(randomString());
		company.setKey(randomString());
		company.setVirtualHost(randomString());
		company.setMx(randomString());
		company.setLogoId(nextLong());

		_persistence.update(company);

		return company;
	}

	private static final String _TX_IMPL = CompanyPersistence.class.getName() +
		".transaction";
	private CompanyPersistence _persistence;
}