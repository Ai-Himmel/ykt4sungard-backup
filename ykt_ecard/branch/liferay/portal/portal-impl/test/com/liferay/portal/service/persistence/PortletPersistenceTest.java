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

import com.liferay.portal.NoSuchPortletException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="PortletPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (PortletPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		Portlet portlet = _persistence.create(pk);

		assertNotNull(portlet);

		assertEquals(portlet.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		Portlet newPortlet = addPortlet();

		_persistence.remove(newPortlet);

		Portlet existingPortlet = _persistence.fetchByPrimaryKey(newPortlet.getPrimaryKey());

		assertNull(existingPortlet);
	}

	public void testUpdateNew() throws Exception {
		addPortlet();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		Portlet newPortlet = _persistence.create(pk);

		newPortlet.setCompanyId(nextLong());
		newPortlet.setPortletId(randomString());
		newPortlet.setRoles(randomString());
		newPortlet.setActive(randomBoolean());

		_persistence.update(newPortlet);

		Portlet existingPortlet = _persistence.findByPrimaryKey(newPortlet.getPrimaryKey());

		assertEquals(existingPortlet.getId(), newPortlet.getId());
		assertEquals(existingPortlet.getCompanyId(), newPortlet.getCompanyId());
		assertEquals(existingPortlet.getPortletId(), newPortlet.getPortletId());
		assertEquals(existingPortlet.getRoles(), newPortlet.getRoles());
		assertEquals(existingPortlet.getActive(), newPortlet.getActive());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		Portlet newPortlet = addPortlet();

		Portlet existingPortlet = _persistence.findByPrimaryKey(newPortlet.getPrimaryKey());

		assertEquals(existingPortlet, newPortlet);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchPortletException");
		}
		catch (NoSuchPortletException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		Portlet newPortlet = addPortlet();

		Portlet existingPortlet = _persistence.fetchByPrimaryKey(newPortlet.getPrimaryKey());

		assertEquals(existingPortlet, newPortlet);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		Portlet missingPortlet = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingPortlet);
	}

	protected Portlet addPortlet() throws Exception {
		long pk = nextLong();

		Portlet portlet = _persistence.create(pk);

		portlet.setCompanyId(nextLong());
		portlet.setPortletId(randomString());
		portlet.setRoles(randomString());
		portlet.setActive(randomBoolean());

		_persistence.update(portlet);

		return portlet;
	}

	private static final String _TX_IMPL = PortletPersistence.class.getName() +
		".transaction";
	private PortletPersistence _persistence;
}