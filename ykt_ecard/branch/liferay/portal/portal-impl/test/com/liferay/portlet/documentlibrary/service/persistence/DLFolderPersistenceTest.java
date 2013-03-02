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

import com.liferay.portlet.documentlibrary.NoSuchFolderException;
import com.liferay.portlet.documentlibrary.model.DLFolder;

/**
 * <a href="DLFolderPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DLFolderPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (DLFolderPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		DLFolder dlFolder = _persistence.create(pk);

		assertNotNull(dlFolder);

		assertEquals(dlFolder.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		DLFolder newDLFolder = addDLFolder();

		_persistence.remove(newDLFolder);

		DLFolder existingDLFolder = _persistence.fetchByPrimaryKey(newDLFolder.getPrimaryKey());

		assertNull(existingDLFolder);
	}

	public void testUpdateNew() throws Exception {
		addDLFolder();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		DLFolder newDLFolder = _persistence.create(pk);

		newDLFolder.setUuid(randomString());
		newDLFolder.setGroupId(nextLong());
		newDLFolder.setCompanyId(nextLong());
		newDLFolder.setUserId(nextLong());
		newDLFolder.setUserName(randomString());
		newDLFolder.setCreateDate(nextDate());
		newDLFolder.setModifiedDate(nextDate());
		newDLFolder.setParentFolderId(nextLong());
		newDLFolder.setName(randomString());
		newDLFolder.setDescription(randomString());
		newDLFolder.setLastPostDate(nextDate());

		_persistence.update(newDLFolder);

		DLFolder existingDLFolder = _persistence.findByPrimaryKey(newDLFolder.getPrimaryKey());

		assertEquals(existingDLFolder.getUuid(), newDLFolder.getUuid());
		assertEquals(existingDLFolder.getFolderId(), newDLFolder.getFolderId());
		assertEquals(existingDLFolder.getGroupId(), newDLFolder.getGroupId());
		assertEquals(existingDLFolder.getCompanyId(), newDLFolder.getCompanyId());
		assertEquals(existingDLFolder.getUserId(), newDLFolder.getUserId());
		assertEquals(existingDLFolder.getUserName(), newDLFolder.getUserName());
		assertEquals(existingDLFolder.getCreateDate(),
			newDLFolder.getCreateDate());
		assertEquals(existingDLFolder.getModifiedDate(),
			newDLFolder.getModifiedDate());
		assertEquals(existingDLFolder.getParentFolderId(),
			newDLFolder.getParentFolderId());
		assertEquals(existingDLFolder.getName(), newDLFolder.getName());
		assertEquals(existingDLFolder.getDescription(),
			newDLFolder.getDescription());
		assertEquals(existingDLFolder.getLastPostDate(),
			newDLFolder.getLastPostDate());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		DLFolder newDLFolder = addDLFolder();

		DLFolder existingDLFolder = _persistence.findByPrimaryKey(newDLFolder.getPrimaryKey());

		assertEquals(existingDLFolder, newDLFolder);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchFolderException");
		}
		catch (NoSuchFolderException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		DLFolder newDLFolder = addDLFolder();

		DLFolder existingDLFolder = _persistence.fetchByPrimaryKey(newDLFolder.getPrimaryKey());

		assertEquals(existingDLFolder, newDLFolder);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		DLFolder missingDLFolder = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingDLFolder);
	}

	protected DLFolder addDLFolder() throws Exception {
		long pk = nextLong();

		DLFolder dlFolder = _persistence.create(pk);

		dlFolder.setUuid(randomString());
		dlFolder.setGroupId(nextLong());
		dlFolder.setCompanyId(nextLong());
		dlFolder.setUserId(nextLong());
		dlFolder.setUserName(randomString());
		dlFolder.setCreateDate(nextDate());
		dlFolder.setModifiedDate(nextDate());
		dlFolder.setParentFolderId(nextLong());
		dlFolder.setName(randomString());
		dlFolder.setDescription(randomString());
		dlFolder.setLastPostDate(nextDate());

		_persistence.update(dlFolder);

		return dlFolder;
	}

	private static final String _TX_IMPL = DLFolderPersistence.class.getName() +
		".transaction";
	private DLFolderPersistence _persistence;
}