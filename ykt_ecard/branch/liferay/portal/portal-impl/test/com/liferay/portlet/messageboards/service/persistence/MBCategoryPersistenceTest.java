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

package com.liferay.portlet.messageboards.service.persistence;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

import com.liferay.portlet.messageboards.NoSuchCategoryException;
import com.liferay.portlet.messageboards.model.MBCategory;

/**
 * <a href="MBCategoryPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBCategoryPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (MBCategoryPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		MBCategory mbCategory = _persistence.create(pk);

		assertNotNull(mbCategory);

		assertEquals(mbCategory.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		MBCategory newMBCategory = addMBCategory();

		_persistence.remove(newMBCategory);

		MBCategory existingMBCategory = _persistence.fetchByPrimaryKey(newMBCategory.getPrimaryKey());

		assertNull(existingMBCategory);
	}

	public void testUpdateNew() throws Exception {
		addMBCategory();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		MBCategory newMBCategory = _persistence.create(pk);

		newMBCategory.setUuid(randomString());
		newMBCategory.setGroupId(nextLong());
		newMBCategory.setCompanyId(nextLong());
		newMBCategory.setUserId(nextLong());
		newMBCategory.setUserName(randomString());
		newMBCategory.setCreateDate(nextDate());
		newMBCategory.setModifiedDate(nextDate());
		newMBCategory.setParentCategoryId(nextLong());
		newMBCategory.setName(randomString());
		newMBCategory.setDescription(randomString());
		newMBCategory.setLastPostDate(nextDate());

		_persistence.update(newMBCategory);

		MBCategory existingMBCategory = _persistence.findByPrimaryKey(newMBCategory.getPrimaryKey());

		assertEquals(existingMBCategory.getUuid(), newMBCategory.getUuid());
		assertEquals(existingMBCategory.getCategoryId(),
			newMBCategory.getCategoryId());
		assertEquals(existingMBCategory.getGroupId(), newMBCategory.getGroupId());
		assertEquals(existingMBCategory.getCompanyId(),
			newMBCategory.getCompanyId());
		assertEquals(existingMBCategory.getUserId(), newMBCategory.getUserId());
		assertEquals(existingMBCategory.getUserName(),
			newMBCategory.getUserName());
		assertEquals(existingMBCategory.getCreateDate(),
			newMBCategory.getCreateDate());
		assertEquals(existingMBCategory.getModifiedDate(),
			newMBCategory.getModifiedDate());
		assertEquals(existingMBCategory.getParentCategoryId(),
			newMBCategory.getParentCategoryId());
		assertEquals(existingMBCategory.getName(), newMBCategory.getName());
		assertEquals(existingMBCategory.getDescription(),
			newMBCategory.getDescription());
		assertEquals(existingMBCategory.getLastPostDate(),
			newMBCategory.getLastPostDate());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		MBCategory newMBCategory = addMBCategory();

		MBCategory existingMBCategory = _persistence.findByPrimaryKey(newMBCategory.getPrimaryKey());

		assertEquals(existingMBCategory, newMBCategory);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchCategoryException");
		}
		catch (NoSuchCategoryException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		MBCategory newMBCategory = addMBCategory();

		MBCategory existingMBCategory = _persistence.fetchByPrimaryKey(newMBCategory.getPrimaryKey());

		assertEquals(existingMBCategory, newMBCategory);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		MBCategory missingMBCategory = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingMBCategory);
	}

	protected MBCategory addMBCategory() throws Exception {
		long pk = nextLong();

		MBCategory mbCategory = _persistence.create(pk);

		mbCategory.setUuid(randomString());
		mbCategory.setGroupId(nextLong());
		mbCategory.setCompanyId(nextLong());
		mbCategory.setUserId(nextLong());
		mbCategory.setUserName(randomString());
		mbCategory.setCreateDate(nextDate());
		mbCategory.setModifiedDate(nextDate());
		mbCategory.setParentCategoryId(nextLong());
		mbCategory.setName(randomString());
		mbCategory.setDescription(randomString());
		mbCategory.setLastPostDate(nextDate());

		_persistence.update(mbCategory);

		return mbCategory;
	}

	private static final String _TX_IMPL = MBCategoryPersistence.class.getName() +
		".transaction";
	private MBCategoryPersistence _persistence;
}