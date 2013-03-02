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

import com.liferay.portlet.tags.NoSuchPropertyException;
import com.liferay.portlet.tags.model.TagsProperty;

/**
 * <a href="TagsPropertyPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TagsPropertyPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (TagsPropertyPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		TagsProperty tagsProperty = _persistence.create(pk);

		assertNotNull(tagsProperty);

		assertEquals(tagsProperty.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		TagsProperty newTagsProperty = addTagsProperty();

		_persistence.remove(newTagsProperty);

		TagsProperty existingTagsProperty = _persistence.fetchByPrimaryKey(newTagsProperty.getPrimaryKey());

		assertNull(existingTagsProperty);
	}

	public void testUpdateNew() throws Exception {
		addTagsProperty();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		TagsProperty newTagsProperty = _persistence.create(pk);

		newTagsProperty.setCompanyId(nextLong());
		newTagsProperty.setUserId(nextLong());
		newTagsProperty.setUserName(randomString());
		newTagsProperty.setCreateDate(nextDate());
		newTagsProperty.setModifiedDate(nextDate());
		newTagsProperty.setEntryId(nextLong());
		newTagsProperty.setKey(randomString());
		newTagsProperty.setValue(randomString());

		_persistence.update(newTagsProperty);

		TagsProperty existingTagsProperty = _persistence.findByPrimaryKey(newTagsProperty.getPrimaryKey());

		assertEquals(existingTagsProperty.getPropertyId(),
			newTagsProperty.getPropertyId());
		assertEquals(existingTagsProperty.getCompanyId(),
			newTagsProperty.getCompanyId());
		assertEquals(existingTagsProperty.getUserId(),
			newTagsProperty.getUserId());
		assertEquals(existingTagsProperty.getUserName(),
			newTagsProperty.getUserName());
		assertEquals(existingTagsProperty.getCreateDate(),
			newTagsProperty.getCreateDate());
		assertEquals(existingTagsProperty.getModifiedDate(),
			newTagsProperty.getModifiedDate());
		assertEquals(existingTagsProperty.getEntryId(),
			newTagsProperty.getEntryId());
		assertEquals(existingTagsProperty.getKey(), newTagsProperty.getKey());
		assertEquals(existingTagsProperty.getValue(), newTagsProperty.getValue());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		TagsProperty newTagsProperty = addTagsProperty();

		TagsProperty existingTagsProperty = _persistence.findByPrimaryKey(newTagsProperty.getPrimaryKey());

		assertEquals(existingTagsProperty, newTagsProperty);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchPropertyException");
		}
		catch (NoSuchPropertyException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		TagsProperty newTagsProperty = addTagsProperty();

		TagsProperty existingTagsProperty = _persistence.fetchByPrimaryKey(newTagsProperty.getPrimaryKey());

		assertEquals(existingTagsProperty, newTagsProperty);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		TagsProperty missingTagsProperty = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingTagsProperty);
	}

	protected TagsProperty addTagsProperty() throws Exception {
		long pk = nextLong();

		TagsProperty tagsProperty = _persistence.create(pk);

		tagsProperty.setCompanyId(nextLong());
		tagsProperty.setUserId(nextLong());
		tagsProperty.setUserName(randomString());
		tagsProperty.setCreateDate(nextDate());
		tagsProperty.setModifiedDate(nextDate());
		tagsProperty.setEntryId(nextLong());
		tagsProperty.setKey(randomString());
		tagsProperty.setValue(randomString());

		_persistence.update(tagsProperty);

		return tagsProperty;
	}

	private static final String _TX_IMPL = TagsPropertyPersistence.class.getName() +
		".transaction";
	private TagsPropertyPersistence _persistence;
}