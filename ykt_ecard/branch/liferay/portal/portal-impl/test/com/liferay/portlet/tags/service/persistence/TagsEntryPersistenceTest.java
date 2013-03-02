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

package com.liferay.portlet.tags.service.persistence;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

import com.liferay.portlet.tags.NoSuchEntryException;
import com.liferay.portlet.tags.model.TagsEntry;

/**
 * <a href="TagsEntryPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TagsEntryPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (TagsEntryPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		TagsEntry tagsEntry = _persistence.create(pk);

		assertNotNull(tagsEntry);

		assertEquals(tagsEntry.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		TagsEntry newTagsEntry = addTagsEntry();

		_persistence.remove(newTagsEntry);

		TagsEntry existingTagsEntry = _persistence.fetchByPrimaryKey(newTagsEntry.getPrimaryKey());

		assertNull(existingTagsEntry);
	}

	public void testUpdateNew() throws Exception {
		addTagsEntry();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		TagsEntry newTagsEntry = _persistence.create(pk);

		newTagsEntry.setCompanyId(nextLong());
		newTagsEntry.setUserId(nextLong());
		newTagsEntry.setUserName(randomString());
		newTagsEntry.setCreateDate(nextDate());
		newTagsEntry.setModifiedDate(nextDate());
		newTagsEntry.setName(randomString());

		_persistence.update(newTagsEntry);

		TagsEntry existingTagsEntry = _persistence.findByPrimaryKey(newTagsEntry.getPrimaryKey());

		assertEquals(existingTagsEntry.getEntryId(), newTagsEntry.getEntryId());
		assertEquals(existingTagsEntry.getCompanyId(),
			newTagsEntry.getCompanyId());
		assertEquals(existingTagsEntry.getUserId(), newTagsEntry.getUserId());
		assertEquals(existingTagsEntry.getUserName(), newTagsEntry.getUserName());
		assertEquals(existingTagsEntry.getCreateDate(),
			newTagsEntry.getCreateDate());
		assertEquals(existingTagsEntry.getModifiedDate(),
			newTagsEntry.getModifiedDate());
		assertEquals(existingTagsEntry.getName(), newTagsEntry.getName());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		TagsEntry newTagsEntry = addTagsEntry();

		TagsEntry existingTagsEntry = _persistence.findByPrimaryKey(newTagsEntry.getPrimaryKey());

		assertEquals(existingTagsEntry, newTagsEntry);
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
		TagsEntry newTagsEntry = addTagsEntry();

		TagsEntry existingTagsEntry = _persistence.fetchByPrimaryKey(newTagsEntry.getPrimaryKey());

		assertEquals(existingTagsEntry, newTagsEntry);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		TagsEntry missingTagsEntry = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingTagsEntry);
	}

	protected TagsEntry addTagsEntry() throws Exception {
		long pk = nextLong();

		TagsEntry tagsEntry = _persistence.create(pk);

		tagsEntry.setCompanyId(nextLong());
		tagsEntry.setUserId(nextLong());
		tagsEntry.setUserName(randomString());
		tagsEntry.setCreateDate(nextDate());
		tagsEntry.setModifiedDate(nextDate());
		tagsEntry.setName(randomString());

		_persistence.update(tagsEntry);

		return tagsEntry;
	}

	private static final String _TX_IMPL = TagsEntryPersistence.class.getName() +
		".transaction";
	private TagsEntryPersistence _persistence;
}