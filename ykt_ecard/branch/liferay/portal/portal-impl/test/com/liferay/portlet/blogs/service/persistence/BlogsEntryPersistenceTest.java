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

package com.liferay.portlet.blogs.service.persistence;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

import com.liferay.portlet.blogs.NoSuchEntryException;
import com.liferay.portlet.blogs.model.BlogsEntry;

/**
 * <a href="BlogsEntryPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BlogsEntryPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (BlogsEntryPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		BlogsEntry blogsEntry = _persistence.create(pk);

		assertNotNull(blogsEntry);

		assertEquals(blogsEntry.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		BlogsEntry newBlogsEntry = addBlogsEntry();

		_persistence.remove(newBlogsEntry);

		BlogsEntry existingBlogsEntry = _persistence.fetchByPrimaryKey(newBlogsEntry.getPrimaryKey());

		assertNull(existingBlogsEntry);
	}

	public void testUpdateNew() throws Exception {
		addBlogsEntry();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		BlogsEntry newBlogsEntry = _persistence.create(pk);

		newBlogsEntry.setUuid(randomString());
		newBlogsEntry.setGroupId(nextLong());
		newBlogsEntry.setCompanyId(nextLong());
		newBlogsEntry.setUserId(nextLong());
		newBlogsEntry.setUserName(randomString());
		newBlogsEntry.setCreateDate(nextDate());
		newBlogsEntry.setModifiedDate(nextDate());
		newBlogsEntry.setTitle(randomString());
		newBlogsEntry.setUrlTitle(randomString());
		newBlogsEntry.setContent(randomString());
		newBlogsEntry.setDisplayDate(nextDate());

		_persistence.update(newBlogsEntry);

		BlogsEntry existingBlogsEntry = _persistence.findByPrimaryKey(newBlogsEntry.getPrimaryKey());

		assertEquals(existingBlogsEntry.getUuid(), newBlogsEntry.getUuid());
		assertEquals(existingBlogsEntry.getEntryId(), newBlogsEntry.getEntryId());
		assertEquals(existingBlogsEntry.getGroupId(), newBlogsEntry.getGroupId());
		assertEquals(existingBlogsEntry.getCompanyId(),
			newBlogsEntry.getCompanyId());
		assertEquals(existingBlogsEntry.getUserId(), newBlogsEntry.getUserId());
		assertEquals(existingBlogsEntry.getUserName(),
			newBlogsEntry.getUserName());
		assertEquals(existingBlogsEntry.getCreateDate(),
			newBlogsEntry.getCreateDate());
		assertEquals(existingBlogsEntry.getModifiedDate(),
			newBlogsEntry.getModifiedDate());
		assertEquals(existingBlogsEntry.getTitle(), newBlogsEntry.getTitle());
		assertEquals(existingBlogsEntry.getUrlTitle(),
			newBlogsEntry.getUrlTitle());
		assertEquals(existingBlogsEntry.getContent(), newBlogsEntry.getContent());
		assertEquals(existingBlogsEntry.getDisplayDate(),
			newBlogsEntry.getDisplayDate());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		BlogsEntry newBlogsEntry = addBlogsEntry();

		BlogsEntry existingBlogsEntry = _persistence.findByPrimaryKey(newBlogsEntry.getPrimaryKey());

		assertEquals(existingBlogsEntry, newBlogsEntry);
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
		BlogsEntry newBlogsEntry = addBlogsEntry();

		BlogsEntry existingBlogsEntry = _persistence.fetchByPrimaryKey(newBlogsEntry.getPrimaryKey());

		assertEquals(existingBlogsEntry, newBlogsEntry);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		BlogsEntry missingBlogsEntry = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingBlogsEntry);
	}

	protected BlogsEntry addBlogsEntry() throws Exception {
		long pk = nextLong();

		BlogsEntry blogsEntry = _persistence.create(pk);

		blogsEntry.setUuid(randomString());
		blogsEntry.setGroupId(nextLong());
		blogsEntry.setCompanyId(nextLong());
		blogsEntry.setUserId(nextLong());
		blogsEntry.setUserName(randomString());
		blogsEntry.setCreateDate(nextDate());
		blogsEntry.setModifiedDate(nextDate());
		blogsEntry.setTitle(randomString());
		blogsEntry.setUrlTitle(randomString());
		blogsEntry.setContent(randomString());
		blogsEntry.setDisplayDate(nextDate());

		_persistence.update(blogsEntry);

		return blogsEntry;
	}

	private static final String _TX_IMPL = BlogsEntryPersistence.class.getName() +
		".transaction";
	private BlogsEntryPersistence _persistence;
}