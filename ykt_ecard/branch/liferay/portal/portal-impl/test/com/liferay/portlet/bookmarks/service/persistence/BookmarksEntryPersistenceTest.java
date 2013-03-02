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

package com.liferay.portlet.bookmarks.service.persistence;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

import com.liferay.portlet.bookmarks.NoSuchEntryException;
import com.liferay.portlet.bookmarks.model.BookmarksEntry;

/**
 * <a href="BookmarksEntryPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BookmarksEntryPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (BookmarksEntryPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		BookmarksEntry bookmarksEntry = _persistence.create(pk);

		assertNotNull(bookmarksEntry);

		assertEquals(bookmarksEntry.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		BookmarksEntry newBookmarksEntry = addBookmarksEntry();

		_persistence.remove(newBookmarksEntry);

		BookmarksEntry existingBookmarksEntry = _persistence.fetchByPrimaryKey(newBookmarksEntry.getPrimaryKey());

		assertNull(existingBookmarksEntry);
	}

	public void testUpdateNew() throws Exception {
		addBookmarksEntry();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		BookmarksEntry newBookmarksEntry = _persistence.create(pk);

		newBookmarksEntry.setUuid(randomString());
		newBookmarksEntry.setCompanyId(nextLong());
		newBookmarksEntry.setUserId(nextLong());
		newBookmarksEntry.setCreateDate(nextDate());
		newBookmarksEntry.setModifiedDate(nextDate());
		newBookmarksEntry.setFolderId(nextLong());
		newBookmarksEntry.setName(randomString());
		newBookmarksEntry.setUrl(randomString());
		newBookmarksEntry.setComments(randomString());
		newBookmarksEntry.setVisits(nextInt());
		newBookmarksEntry.setPriority(nextInt());

		_persistence.update(newBookmarksEntry);

		BookmarksEntry existingBookmarksEntry = _persistence.findByPrimaryKey(newBookmarksEntry.getPrimaryKey());

		assertEquals(existingBookmarksEntry.getUuid(),
			newBookmarksEntry.getUuid());
		assertEquals(existingBookmarksEntry.getEntryId(),
			newBookmarksEntry.getEntryId());
		assertEquals(existingBookmarksEntry.getCompanyId(),
			newBookmarksEntry.getCompanyId());
		assertEquals(existingBookmarksEntry.getUserId(),
			newBookmarksEntry.getUserId());
		assertEquals(existingBookmarksEntry.getCreateDate(),
			newBookmarksEntry.getCreateDate());
		assertEquals(existingBookmarksEntry.getModifiedDate(),
			newBookmarksEntry.getModifiedDate());
		assertEquals(existingBookmarksEntry.getFolderId(),
			newBookmarksEntry.getFolderId());
		assertEquals(existingBookmarksEntry.getName(),
			newBookmarksEntry.getName());
		assertEquals(existingBookmarksEntry.getUrl(), newBookmarksEntry.getUrl());
		assertEquals(existingBookmarksEntry.getComments(),
			newBookmarksEntry.getComments());
		assertEquals(existingBookmarksEntry.getVisits(),
			newBookmarksEntry.getVisits());
		assertEquals(existingBookmarksEntry.getPriority(),
			newBookmarksEntry.getPriority());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		BookmarksEntry newBookmarksEntry = addBookmarksEntry();

		BookmarksEntry existingBookmarksEntry = _persistence.findByPrimaryKey(newBookmarksEntry.getPrimaryKey());

		assertEquals(existingBookmarksEntry, newBookmarksEntry);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchEntryException");
		}
		catch (NoSuchEntryException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		BookmarksEntry newBookmarksEntry = addBookmarksEntry();

		BookmarksEntry existingBookmarksEntry = _persistence.fetchByPrimaryKey(newBookmarksEntry.getPrimaryKey());

		assertEquals(existingBookmarksEntry, newBookmarksEntry);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		BookmarksEntry missingBookmarksEntry = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingBookmarksEntry);
	}

	protected BookmarksEntry addBookmarksEntry() throws Exception {
		long pk = nextLong();

		BookmarksEntry bookmarksEntry = _persistence.create(pk);

		bookmarksEntry.setUuid(randomString());
		bookmarksEntry.setCompanyId(nextLong());
		bookmarksEntry.setUserId(nextLong());
		bookmarksEntry.setCreateDate(nextDate());
		bookmarksEntry.setModifiedDate(nextDate());
		bookmarksEntry.setFolderId(nextLong());
		bookmarksEntry.setName(randomString());
		bookmarksEntry.setUrl(randomString());
		bookmarksEntry.setComments(randomString());
		bookmarksEntry.setVisits(nextInt());
		bookmarksEntry.setPriority(nextInt());

		_persistence.update(bookmarksEntry);

		return bookmarksEntry;
	}

	private static final String _TX_IMPL = BookmarksEntryPersistence.class.getName() +
		".transaction";
	private BookmarksEntryPersistence _persistence;
}