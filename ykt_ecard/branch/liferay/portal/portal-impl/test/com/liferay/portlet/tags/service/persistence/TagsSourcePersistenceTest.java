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

import com.liferay.portlet.tags.NoSuchSourceException;
import com.liferay.portlet.tags.model.TagsSource;

/**
 * <a href="TagsSourcePersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TagsSourcePersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (TagsSourcePersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		TagsSource tagsSource = _persistence.create(pk);

		assertNotNull(tagsSource);

		assertEquals(tagsSource.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		TagsSource newTagsSource = addTagsSource();

		_persistence.remove(newTagsSource);

		TagsSource existingTagsSource = _persistence.fetchByPrimaryKey(newTagsSource.getPrimaryKey());

		assertNull(existingTagsSource);
	}

	public void testUpdateNew() throws Exception {
		addTagsSource();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		TagsSource newTagsSource = _persistence.create(pk);

		newTagsSource.setParentSourceId(nextLong());
		newTagsSource.setName(randomString());
		newTagsSource.setAcronym(randomString());

		_persistence.update(newTagsSource);

		TagsSource existingTagsSource = _persistence.findByPrimaryKey(newTagsSource.getPrimaryKey());

		assertEquals(existingTagsSource.getSourceId(),
			newTagsSource.getSourceId());
		assertEquals(existingTagsSource.getParentSourceId(),
			newTagsSource.getParentSourceId());
		assertEquals(existingTagsSource.getName(), newTagsSource.getName());
		assertEquals(existingTagsSource.getAcronym(), newTagsSource.getAcronym());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		TagsSource newTagsSource = addTagsSource();

		TagsSource existingTagsSource = _persistence.findByPrimaryKey(newTagsSource.getPrimaryKey());

		assertEquals(existingTagsSource, newTagsSource);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchSourceException");
		}
		catch (NoSuchSourceException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		TagsSource newTagsSource = addTagsSource();

		TagsSource existingTagsSource = _persistence.fetchByPrimaryKey(newTagsSource.getPrimaryKey());

		assertEquals(existingTagsSource, newTagsSource);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		TagsSource missingTagsSource = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingTagsSource);
	}

	protected TagsSource addTagsSource() throws Exception {
		long pk = nextLong();

		TagsSource tagsSource = _persistence.create(pk);

		tagsSource.setParentSourceId(nextLong());
		tagsSource.setName(randomString());
		tagsSource.setAcronym(randomString());

		_persistence.update(tagsSource);

		return tagsSource;
	}

	private static final String _TX_IMPL = TagsSourcePersistence.class.getName() +
		".transaction";
	private TagsSourcePersistence _persistence;
}