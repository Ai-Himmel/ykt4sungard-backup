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

import com.liferay.portal.NoSuchServiceComponentException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.ServiceComponent;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="ServiceComponentPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ServiceComponentPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (ServiceComponentPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		ServiceComponent serviceComponent = _persistence.create(pk);

		assertNotNull(serviceComponent);

		assertEquals(serviceComponent.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		ServiceComponent newServiceComponent = addServiceComponent();

		_persistence.remove(newServiceComponent);

		ServiceComponent existingServiceComponent = _persistence.fetchByPrimaryKey(newServiceComponent.getPrimaryKey());

		assertNull(existingServiceComponent);
	}

	public void testUpdateNew() throws Exception {
		addServiceComponent();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		ServiceComponent newServiceComponent = _persistence.create(pk);

		newServiceComponent.setBuildNamespace(randomString());
		newServiceComponent.setBuildNumber(nextLong());
		newServiceComponent.setBuildDate(nextLong());
		newServiceComponent.setData(randomString());

		_persistence.update(newServiceComponent);

		ServiceComponent existingServiceComponent = _persistence.findByPrimaryKey(newServiceComponent.getPrimaryKey());

		assertEquals(existingServiceComponent.getServiceComponentId(),
			newServiceComponent.getServiceComponentId());
		assertEquals(existingServiceComponent.getBuildNamespace(),
			newServiceComponent.getBuildNamespace());
		assertEquals(existingServiceComponent.getBuildNumber(),
			newServiceComponent.getBuildNumber());
		assertEquals(existingServiceComponent.getBuildDate(),
			newServiceComponent.getBuildDate());
		assertEquals(existingServiceComponent.getData(),
			newServiceComponent.getData());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		ServiceComponent newServiceComponent = addServiceComponent();

		ServiceComponent existingServiceComponent = _persistence.findByPrimaryKey(newServiceComponent.getPrimaryKey());

		assertEquals(existingServiceComponent, newServiceComponent);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchServiceComponentException");
		}
		catch (NoSuchServiceComponentException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		ServiceComponent newServiceComponent = addServiceComponent();

		ServiceComponent existingServiceComponent = _persistence.fetchByPrimaryKey(newServiceComponent.getPrimaryKey());

		assertEquals(existingServiceComponent, newServiceComponent);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		ServiceComponent missingServiceComponent = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingServiceComponent);
	}

	protected ServiceComponent addServiceComponent() throws Exception {
		long pk = nextLong();

		ServiceComponent serviceComponent = _persistence.create(pk);

		serviceComponent.setBuildNamespace(randomString());
		serviceComponent.setBuildNumber(nextLong());
		serviceComponent.setBuildDate(nextLong());
		serviceComponent.setData(randomString());

		_persistence.update(serviceComponent);

		return serviceComponent;
	}

	private static final String _TX_IMPL = ServiceComponentPersistence.class.getName() +
		".transaction";
	private ServiceComponentPersistence _persistence;
}