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

package com.liferay.portlet.documentlibrary.service.persistence;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

import com.liferay.portlet.documentlibrary.NoSuchFileVersionException;
import com.liferay.portlet.documentlibrary.model.DLFileVersion;

/**
 * <a href="DLFileVersionPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DLFileVersionPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (DLFileVersionPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		DLFileVersion dlFileVersion = _persistence.create(pk);

		assertNotNull(dlFileVersion);

		assertEquals(dlFileVersion.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		DLFileVersion newDLFileVersion = addDLFileVersion();

		_persistence.remove(newDLFileVersion);

		DLFileVersion existingDLFileVersion = _persistence.fetchByPrimaryKey(newDLFileVersion.getPrimaryKey());

		assertNull(existingDLFileVersion);
	}

	public void testUpdateNew() throws Exception {
		addDLFileVersion();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		DLFileVersion newDLFileVersion = _persistence.create(pk);

		newDLFileVersion.setCompanyId(nextLong());
		newDLFileVersion.setUserId(nextLong());
		newDLFileVersion.setUserName(randomString());
		newDLFileVersion.setCreateDate(nextDate());
		newDLFileVersion.setFolderId(nextLong());
		newDLFileVersion.setName(randomString());
		newDLFileVersion.setVersion(nextDouble());
		newDLFileVersion.setSize(nextInt());

		_persistence.update(newDLFileVersion);

		DLFileVersion existingDLFileVersion = _persistence.findByPrimaryKey(newDLFileVersion.getPrimaryKey());

		assertEquals(existingDLFileVersion.getFileVersionId(),
			newDLFileVersion.getFileVersionId());
		assertEquals(existingDLFileVersion.getCompanyId(),
			newDLFileVersion.getCompanyId());
		assertEquals(existingDLFileVersion.getUserId(),
			newDLFileVersion.getUserId());
		assertEquals(existingDLFileVersion.getUserName(),
			newDLFileVersion.getUserName());
		assertEquals(existingDLFileVersion.getCreateDate(),
			newDLFileVersion.getCreateDate());
		assertEquals(existingDLFileVersion.getFolderId(),
			newDLFileVersion.getFolderId());
		assertEquals(existingDLFileVersion.getName(), newDLFileVersion.getName());
		assertEquals(existingDLFileVersion.getVersion(),
			newDLFileVersion.getVersion());
		assertEquals(existingDLFileVersion.getSize(), newDLFileVersion.getSize());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		DLFileVersion newDLFileVersion = addDLFileVersion();

		DLFileVersion existingDLFileVersion = _persistence.findByPrimaryKey(newDLFileVersion.getPrimaryKey());

		assertEquals(existingDLFileVersion, newDLFileVersion);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchFileVersionException");
		}
		catch (NoSuchFileVersionException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		DLFileVersion newDLFileVersion = addDLFileVersion();

		DLFileVersion existingDLFileVersion = _persistence.fetchByPrimaryKey(newDLFileVersion.getPrimaryKey());

		assertEquals(existingDLFileVersion, newDLFileVersion);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		DLFileVersion missingDLFileVersion = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingDLFileVersion);
	}

	protected DLFileVersion addDLFileVersion() throws Exception {
		long pk = nextLong();

		DLFileVersion dlFileVersion = _persistence.create(pk);

		dlFileVersion.setCompanyId(nextLong());
		dlFileVersion.setUserId(nextLong());
		dlFileVersion.setUserName(randomString());
		dlFileVersion.setCreateDate(nextDate());
		dlFileVersion.setFolderId(nextLong());
		dlFileVersion.setName(randomString());
		dlFileVersion.setVersion(nextDouble());
		dlFileVersion.setSize(nextInt());

		_persistence.update(dlFileVersion);

		return dlFileVersion;
	}

	private static final String _TX_IMPL = DLFileVersionPersistence.class.getName() +
		".transaction";
	private DLFileVersionPersistence _persistence;
}