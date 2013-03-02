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

import com.liferay.portal.NoSuchResourceCodeException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.ResourceCode;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="ResourceCodePersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ResourceCodePersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (ResourceCodePersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		ResourceCode resourceCode = _persistence.create(pk);

		assertNotNull(resourceCode);

		assertEquals(resourceCode.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		ResourceCode newResourceCode = addResourceCode();

		_persistence.remove(newResourceCode);

		ResourceCode existingResourceCode = _persistence.fetchByPrimaryKey(newResourceCode.getPrimaryKey());

		assertNull(existingResourceCode);
	}

	public void testUpdateNew() throws Exception {
		addResourceCode();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		ResourceCode newResourceCode = _persistence.create(pk);

		newResourceCode.setCompanyId(nextLong());
		newResourceCode.setName(randomString());
		newResourceCode.setScope(nextInt());

		_persistence.update(newResourceCode);

		ResourceCode existingResourceCode = _persistence.findByPrimaryKey(newResourceCode.getPrimaryKey());

		assertEquals(existingResourceCode.getCodeId(),
			newResourceCode.getCodeId());
		assertEquals(existingResourceCode.getCompanyId(),
			newResourceCode.getCompanyId());
		assertEquals(existingResourceCode.getName(), newResourceCode.getName());
		assertEquals(existingResourceCode.getScope(), newResourceCode.getScope());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		ResourceCode newResourceCode = addResourceCode();

		ResourceCode existingResourceCode = _persistence.findByPrimaryKey(newResourceCode.getPrimaryKey());

		assertEquals(existingResourceCode, newResourceCode);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchResourceCodeException");
		}
		catch (NoSuchResourceCodeException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		ResourceCode newResourceCode = addResourceCode();

		ResourceCode existingResourceCode = _persistence.fetchByPrimaryKey(newResourceCode.getPrimaryKey());

		assertEquals(existingResourceCode, newResourceCode);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		ResourceCode missingResourceCode = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingResourceCode);
	}

	protected ResourceCode addResourceCode() throws Exception {
		long pk = nextLong();

		ResourceCode resourceCode = _persistence.create(pk);

		resourceCode.setCompanyId(nextLong());
		resourceCode.setName(randomString());
		resourceCode.setScope(nextInt());

		_persistence.update(resourceCode);

		return resourceCode;
	}

	private static final String _TX_IMPL = ResourceCodePersistence.class.getName() +
		".transaction";
	private ResourceCodePersistence _persistence;
}