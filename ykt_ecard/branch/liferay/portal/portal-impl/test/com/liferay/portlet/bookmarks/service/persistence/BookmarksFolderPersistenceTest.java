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

import com.liferay.portlet.bookmarks.NoSuchFolderException;
import com.liferay.portlet.bookmarks.model.BookmarksFolder;

/**
 * <a href="BookmarksFolderPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BookmarksFolderPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (BookmarksFolderPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		BookmarksFolder bookmarksFolder = _persistence.create(pk);

		assertNotNull(bookmarksFolder);

		assertEquals(bookmarksFolder.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		BookmarksFolder newBookmarksFolder = addBookmarksFolder();

		_persistence.remove(newBookmarksFolder);

		BookmarksFolder existingBookmarksFolder = _persistence.fetchByPrimaryKey(newBookmarksFolder.getPrimaryKey());

		assertNull(existingBookmarksFolder);
	}

	public void testUpdateNew() throws Exception {
		addBookmarksFolder();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		BookmarksFolder newBookmarksFolder = _persistence.create(pk);

		newBookmarksFolder.setUuid(randomString());
		newBookmarksFolder.setGroupId(nextLong());
		newBookmarksFolder.setCompanyId(nextLong());
		newBookmarksFolder.setUserId(nextLong());
		newBookmarksFolder.setCreateDate(nextDate());
		newBookmarksFolder.setModifiedDate(nextDate());
		newBookmarksFolder.setParentFolderId(nextLong());
		newBookmarksFolder.setName(randomString());
		newBookmarksFolder.setDescription(randomString());

		_persistence.update(newBookmarksFolder);

		BookmarksFolder existingBookmarksFolder = _persistence.findByPrimaryKey(newBookmarksFolder.getPrimaryKey());

		assertEquals(existingBookmarksFolder.getUuid(),
			newBookmarksFolder.getUuid());
		assertEquals(existingBookmarksFolder.getFolderId(),
			newBookmarksFolder.getFolderId());
		assertEquals(existingBookmarksFolder.getGroupId(),
			newBookmarksFolder.getGroupId());
		assertEquals(existingBookmarksFolder.getCompanyId(),
			newBookmarksFolder.getCompanyId());
		assertEquals(existingBookmarksFolder.getUserId(),
			newBookmarksFolder.getUserId());
		assertEquals(existingBookmarksFolder.getCreateDate(),
			newBookmarksFolder.getCreateDate());
		assertEquals(existingBookmarksFolder.getModifiedDate(),
			newBookmarksFolder.getModifiedDate());
		assertEquals(existingBookmarksFolder.getParentFolderId(),
			newBookmarksFolder.getParentFolderId());
		assertEquals(existingBookmarksFolder.getName(),
			newBookmarksFolder.getName());
		assertEquals(existingBookmarksFolder.getDescription(),
			newBookmarksFolder.getDescription());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		BookmarksFolder newBookmarksFolder = addBookmarksFolder();

		BookmarksFolder existingBookmarksFolder = _persistence.findByPrimaryKey(newBookmarksFolder.getPrimaryKey());

		assertEquals(existingBookmarksFolder, newBookmarksFolder);
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
		BookmarksFolder newBookmarksFolder = addBookmarksFolder();

		BookmarksFolder existingBookmarksFolder = _persistence.fetchByPrimaryKey(newBookmarksFolder.getPrimaryKey());

		assertEquals(existingBookmarksFolder, newBookmarksFolder);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		BookmarksFolder missingBookmarksFolder = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingBookmarksFolder);
	}

	protected BookmarksFolder addBookmarksFolder() throws Exception {
		long pk = nextLong();

		BookmarksFolder bookmarksFolder = _persistence.create(pk);

		bookmarksFolder.setUuid(randomString());
		bookmarksFolder.setGroupId(nextLong());
		bookmarksFolder.setCompanyId(nextLong());
		bookmarksFolder.setUserId(nextLong());
		bookmarksFolder.setCreateDate(nextDate());
		bookmarksFolder.setModifiedDate(nextDate());
		bookmarksFolder.setParentFolderId(nextLong());
		bookmarksFolder.setName(randomString());
		bookmarksFolder.setDescription(randomString());

		_persistence.update(bookmarksFolder);

		return bookmarksFolder;
	}

	private static final String _TX_IMPL = BookmarksFolderPersistence.class.getName() +
		".transaction";
	private BookmarksFolderPersistence _persistence;
}