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

import com.liferay.portlet.tags.NoSuchAssetException;
import com.liferay.portlet.tags.model.TagsAsset;

/**
 * <a href="TagsAssetPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TagsAssetPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (TagsAssetPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		TagsAsset tagsAsset = _persistence.create(pk);

		assertNotNull(tagsAsset);

		assertEquals(tagsAsset.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		TagsAsset newTagsAsset = addTagsAsset();

		_persistence.remove(newTagsAsset);

		TagsAsset existingTagsAsset = _persistence.fetchByPrimaryKey(newTagsAsset.getPrimaryKey());

		assertNull(existingTagsAsset);
	}

	public void testUpdateNew() throws Exception {
		addTagsAsset();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		TagsAsset newTagsAsset = _persistence.create(pk);

		newTagsAsset.setGroupId(nextLong());
		newTagsAsset.setCompanyId(nextLong());
		newTagsAsset.setUserId(nextLong());
		newTagsAsset.setUserName(randomString());
		newTagsAsset.setCreateDate(nextDate());
		newTagsAsset.setModifiedDate(nextDate());
		newTagsAsset.setClassNameId(nextLong());
		newTagsAsset.setClassPK(nextLong());
		newTagsAsset.setStartDate(nextDate());
		newTagsAsset.setEndDate(nextDate());
		newTagsAsset.setPublishDate(nextDate());
		newTagsAsset.setExpirationDate(nextDate());
		newTagsAsset.setMimeType(randomString());
		newTagsAsset.setTitle(randomString());
		newTagsAsset.setDescription(randomString());
		newTagsAsset.setSummary(randomString());
		newTagsAsset.setUrl(randomString());
		newTagsAsset.setHeight(nextInt());
		newTagsAsset.setWidth(nextInt());
		newTagsAsset.setPriority(nextDouble());
		newTagsAsset.setViewCount(nextInt());

		_persistence.update(newTagsAsset);

		TagsAsset existingTagsAsset = _persistence.findByPrimaryKey(newTagsAsset.getPrimaryKey());

		assertEquals(existingTagsAsset.getAssetId(), newTagsAsset.getAssetId());
		assertEquals(existingTagsAsset.getGroupId(), newTagsAsset.getGroupId());
		assertEquals(existingTagsAsset.getCompanyId(),
			newTagsAsset.getCompanyId());
		assertEquals(existingTagsAsset.getUserId(), newTagsAsset.getUserId());
		assertEquals(existingTagsAsset.getUserName(), newTagsAsset.getUserName());
		assertEquals(existingTagsAsset.getCreateDate(),
			newTagsAsset.getCreateDate());
		assertEquals(existingTagsAsset.getModifiedDate(),
			newTagsAsset.getModifiedDate());
		assertEquals(existingTagsAsset.getClassNameId(),
			newTagsAsset.getClassNameId());
		assertEquals(existingTagsAsset.getClassPK(), newTagsAsset.getClassPK());
		assertEquals(existingTagsAsset.getStartDate(),
			newTagsAsset.getStartDate());
		assertEquals(existingTagsAsset.getEndDate(), newTagsAsset.getEndDate());
		assertEquals(existingTagsAsset.getPublishDate(),
			newTagsAsset.getPublishDate());
		assertEquals(existingTagsAsset.getExpirationDate(),
			newTagsAsset.getExpirationDate());
		assertEquals(existingTagsAsset.getMimeType(), newTagsAsset.getMimeType());
		assertEquals(existingTagsAsset.getTitle(), newTagsAsset.getTitle());
		assertEquals(existingTagsAsset.getDescription(),
			newTagsAsset.getDescription());
		assertEquals(existingTagsAsset.getSummary(), newTagsAsset.getSummary());
		assertEquals(existingTagsAsset.getUrl(), newTagsAsset.getUrl());
		assertEquals(existingTagsAsset.getHeight(), newTagsAsset.getHeight());
		assertEquals(existingTagsAsset.getWidth(), newTagsAsset.getWidth());
		assertEquals(existingTagsAsset.getPriority(), newTagsAsset.getPriority());
		assertEquals(existingTagsAsset.getViewCount(),
			newTagsAsset.getViewCount());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		TagsAsset newTagsAsset = addTagsAsset();

		TagsAsset existingTagsAsset = _persistence.findByPrimaryKey(newTagsAsset.getPrimaryKey());

		assertEquals(existingTagsAsset, newTagsAsset);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchAssetException");
		}
		catch (NoSuchAssetException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		TagsAsset newTagsAsset = addTagsAsset();

		TagsAsset existingTagsAsset = _persistence.fetchByPrimaryKey(newTagsAsset.getPrimaryKey());

		assertEquals(existingTagsAsset, newTagsAsset);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		TagsAsset missingTagsAsset = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingTagsAsset);
	}

	protected TagsAsset addTagsAsset() throws Exception {
		long pk = nextLong();

		TagsAsset tagsAsset = _persistence.create(pk);

		tagsAsset.setGroupId(nextLong());
		tagsAsset.setCompanyId(nextLong());
		tagsAsset.setUserId(nextLong());
		tagsAsset.setUserName(randomString());
		tagsAsset.setCreateDate(nextDate());
		tagsAsset.setModifiedDate(nextDate());
		tagsAsset.setClassNameId(nextLong());
		tagsAsset.setClassPK(nextLong());
		tagsAsset.setStartDate(nextDate());
		tagsAsset.setEndDate(nextDate());
		tagsAsset.setPublishDate(nextDate());
		tagsAsset.setExpirationDate(nextDate());
		tagsAsset.setMimeType(randomString());
		tagsAsset.setTitle(randomString());
		tagsAsset.setDescription(randomString());
		tagsAsset.setSummary(randomString());
		tagsAsset.setUrl(randomString());
		tagsAsset.setHeight(nextInt());
		tagsAsset.setWidth(nextInt());
		tagsAsset.setPriority(nextDouble());
		tagsAsset.setViewCount(nextInt());

		_persistence.update(tagsAsset);

		return tagsAsset;
	}

	private static final String _TX_IMPL = TagsAssetPersistence.class.getName() +
		".transaction";
	private TagsAssetPersistence _persistence;
}