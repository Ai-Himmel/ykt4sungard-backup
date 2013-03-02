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

import com.liferay.portlet.documentlibrary.NoSuchFileRankException;
import com.liferay.portlet.documentlibrary.model.DLFileRank;

/**
 * <a href="DLFileRankPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DLFileRankPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (DLFileRankPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		DLFileRank dlFileRank = _persistence.create(pk);

		assertNotNull(dlFileRank);

		assertEquals(dlFileRank.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		DLFileRank newDLFileRank = addDLFileRank();

		_persistence.remove(newDLFileRank);

		DLFileRank existingDLFileRank = _persistence.fetchByPrimaryKey(newDLFileRank.getPrimaryKey());

		assertNull(existingDLFileRank);
	}

	public void testUpdateNew() throws Exception {
		addDLFileRank();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		DLFileRank newDLFileRank = _persistence.create(pk);

		newDLFileRank.setCompanyId(nextLong());
		newDLFileRank.setUserId(nextLong());
		newDLFileRank.setCreateDate(nextDate());
		newDLFileRank.setFolderId(nextLong());
		newDLFileRank.setName(randomString());

		_persistence.update(newDLFileRank);

		DLFileRank existingDLFileRank = _persistence.findByPrimaryKey(newDLFileRank.getPrimaryKey());

		assertEquals(existingDLFileRank.getFileRankId(),
			newDLFileRank.getFileRankId());
		assertEquals(existingDLFileRank.getCompanyId(),
			newDLFileRank.getCompanyId());
		assertEquals(existingDLFileRank.getUserId(), newDLFileRank.getUserId());
		assertEquals(existingDLFileRank.getCreateDate(),
			newDLFileRank.getCreateDate());
		assertEquals(existingDLFileRank.getFolderId(),
			newDLFileRank.getFolderId());
		assertEquals(existingDLFileRank.getName(), newDLFileRank.getName());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		DLFileRank newDLFileRank = addDLFileRank();

		DLFileRank existingDLFileRank = _persistence.findByPrimaryKey(newDLFileRank.getPrimaryKey());

		assertEquals(existingDLFileRank, newDLFileRank);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchFileRankException");
		}
		catch (NoSuchFileRankException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		DLFileRank newDLFileRank = addDLFileRank();

		DLFileRank existingDLFileRank = _persistence.fetchByPrimaryKey(newDLFileRank.getPrimaryKey());

		assertEquals(existingDLFileRank, newDLFileRank);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		DLFileRank missingDLFileRank = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingDLFileRank);
	}

	protected DLFileRank addDLFileRank() throws Exception {
		long pk = nextLong();

		DLFileRank dlFileRank = _persistence.create(pk);

		dlFileRank.setCompanyId(nextLong());
		dlFileRank.setUserId(nextLong());
		dlFileRank.setCreateDate(nextDate());
		dlFileRank.setFolderId(nextLong());
		dlFileRank.setName(randomString());

		_persistence.update(dlFileRank);

		return dlFileRank;
	}

	private static final String _TX_IMPL = DLFileRankPersistence.class.getName() +
		".transaction";
	private DLFileRankPersistence _persistence;
}