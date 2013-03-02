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

package com.liferay.portlet.ratings.service.persistence;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

import com.liferay.portlet.ratings.NoSuchEntryException;
import com.liferay.portlet.ratings.model.RatingsEntry;

/**
 * <a href="RatingsEntryPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RatingsEntryPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (RatingsEntryPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		RatingsEntry ratingsEntry = _persistence.create(pk);

		assertNotNull(ratingsEntry);

		assertEquals(ratingsEntry.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		RatingsEntry newRatingsEntry = addRatingsEntry();

		_persistence.remove(newRatingsEntry);

		RatingsEntry existingRatingsEntry = _persistence.fetchByPrimaryKey(newRatingsEntry.getPrimaryKey());

		assertNull(existingRatingsEntry);
	}

	public void testUpdateNew() throws Exception {
		addRatingsEntry();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		RatingsEntry newRatingsEntry = _persistence.create(pk);

		newRatingsEntry.setCompanyId(nextLong());
		newRatingsEntry.setUserId(nextLong());
		newRatingsEntry.setUserName(randomString());
		newRatingsEntry.setCreateDate(nextDate());
		newRatingsEntry.setModifiedDate(nextDate());
		newRatingsEntry.setClassNameId(nextLong());
		newRatingsEntry.setClassPK(nextLong());
		newRatingsEntry.setScore(nextDouble());

		_persistence.update(newRatingsEntry);

		RatingsEntry existingRatingsEntry = _persistence.findByPrimaryKey(newRatingsEntry.getPrimaryKey());

		assertEquals(existingRatingsEntry.getEntryId(),
			newRatingsEntry.getEntryId());
		assertEquals(existingRatingsEntry.getCompanyId(),
			newRatingsEntry.getCompanyId());
		assertEquals(existingRatingsEntry.getUserId(),
			newRatingsEntry.getUserId());
		assertEquals(existingRatingsEntry.getUserName(),
			newRatingsEntry.getUserName());
		assertEquals(existingRatingsEntry.getCreateDate(),
			newRatingsEntry.getCreateDate());
		assertEquals(existingRatingsEntry.getModifiedDate(),
			newRatingsEntry.getModifiedDate());
		assertEquals(existingRatingsEntry.getClassNameId(),
			newRatingsEntry.getClassNameId());
		assertEquals(existingRatingsEntry.getClassPK(),
			newRatingsEntry.getClassPK());
		assertEquals(existingRatingsEntry.getScore(), newRatingsEntry.getScore());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		RatingsEntry newRatingsEntry = addRatingsEntry();

		RatingsEntry existingRatingsEntry = _persistence.findByPrimaryKey(newRatingsEntry.getPrimaryKey());

		assertEquals(existingRatingsEntry, newRatingsEntry);
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
		RatingsEntry newRatingsEntry = addRatingsEntry();

		RatingsEntry existingRatingsEntry = _persistence.fetchByPrimaryKey(newRatingsEntry.getPrimaryKey());

		assertEquals(existingRatingsEntry, newRatingsEntry);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		RatingsEntry missingRatingsEntry = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingRatingsEntry);
	}

	protected RatingsEntry addRatingsEntry() throws Exception {
		long pk = nextLong();

		RatingsEntry ratingsEntry = _persistence.create(pk);

		ratingsEntry.setCompanyId(nextLong());
		ratingsEntry.setUserId(nextLong());
		ratingsEntry.setUserName(randomString());
		ratingsEntry.setCreateDate(nextDate());
		ratingsEntry.setModifiedDate(nextDate());
		ratingsEntry.setClassNameId(nextLong());
		ratingsEntry.setClassPK(nextLong());
		ratingsEntry.setScore(nextDouble());

		_persistence.update(ratingsEntry);

		return ratingsEntry;
	}

	private static final String _TX_IMPL = RatingsEntryPersistence.class.getName() +
		".transaction";
	private RatingsEntryPersistence _persistence;
}