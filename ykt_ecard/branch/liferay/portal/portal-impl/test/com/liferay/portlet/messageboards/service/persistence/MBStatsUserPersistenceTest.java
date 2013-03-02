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

import com.liferay.portlet.messageboards.NoSuchStatsUserException;
import com.liferay.portlet.messageboards.model.MBStatsUser;

/**
 * <a href="MBStatsUserPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBStatsUserPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (MBStatsUserPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		MBStatsUser mbStatsUser = _persistence.create(pk);

		assertNotNull(mbStatsUser);

		assertEquals(mbStatsUser.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		MBStatsUser newMBStatsUser = addMBStatsUser();

		_persistence.remove(newMBStatsUser);

		MBStatsUser existingMBStatsUser = _persistence.fetchByPrimaryKey(newMBStatsUser.getPrimaryKey());

		assertNull(existingMBStatsUser);
	}

	public void testUpdateNew() throws Exception {
		addMBStatsUser();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		MBStatsUser newMBStatsUser = _persistence.create(pk);

		newMBStatsUser.setGroupId(nextLong());
		newMBStatsUser.setUserId(nextLong());
		newMBStatsUser.setMessageCount(nextInt());
		newMBStatsUser.setLastPostDate(nextDate());

		_persistence.update(newMBStatsUser);

		MBStatsUser existingMBStatsUser = _persistence.findByPrimaryKey(newMBStatsUser.getPrimaryKey());

		assertEquals(existingMBStatsUser.getStatsUserId(),
			newMBStatsUser.getStatsUserId());
		assertEquals(existingMBStatsUser.getGroupId(),
			newMBStatsUser.getGroupId());
		assertEquals(existingMBStatsUser.getUserId(), newMBStatsUser.getUserId());
		assertEquals(existingMBStatsUser.getMessageCount(),
			newMBStatsUser.getMessageCount());
		assertEquals(existingMBStatsUser.getLastPostDate(),
			newMBStatsUser.getLastPostDate());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		MBStatsUser newMBStatsUser = addMBStatsUser();

		MBStatsUser existingMBStatsUser = _persistence.findByPrimaryKey(newMBStatsUser.getPrimaryKey());

		assertEquals(existingMBStatsUser, newMBStatsUser);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchStatsUserException");
		}
		catch (NoSuchStatsUserException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		MBStatsUser newMBStatsUser = addMBStatsUser();

		MBStatsUser existingMBStatsUser = _persistence.fetchByPrimaryKey(newMBStatsUser.getPrimaryKey());

		assertEquals(existingMBStatsUser, newMBStatsUser);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		MBStatsUser missingMBStatsUser = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingMBStatsUser);
	}

	protected MBStatsUser addMBStatsUser() throws Exception {
		long pk = nextLong();

		MBStatsUser mbStatsUser = _persistence.create(pk);

		mbStatsUser.setGroupId(nextLong());
		mbStatsUser.setUserId(nextLong());
		mbStatsUser.setMessageCount(nextInt());
		mbStatsUser.setLastPostDate(nextDate());

		_persistence.update(mbStatsUser);

		return mbStatsUser;
	}

	private static final String _TX_IMPL = MBStatsUserPersistence.class.getName() +
		".transaction";
	private MBStatsUserPersistence _persistence;
}