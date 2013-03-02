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

package com.liferay.portal.service.persistence;

import com.liferay.portal.NoSuchUserTrackerException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.UserTracker;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="UserTrackerPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UserTrackerPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (UserTrackerPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		UserTracker userTracker = _persistence.create(pk);

		assertNotNull(userTracker);

		assertEquals(userTracker.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		UserTracker newUserTracker = addUserTracker();

		_persistence.remove(newUserTracker);

		UserTracker existingUserTracker = _persistence.fetchByPrimaryKey(newUserTracker.getPrimaryKey());

		assertNull(existingUserTracker);
	}

	public void testUpdateNew() throws Exception {
		addUserTracker();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		UserTracker newUserTracker = _persistence.create(pk);

		newUserTracker.setCompanyId(nextLong());
		newUserTracker.setUserId(nextLong());
		newUserTracker.setModifiedDate(nextDate());
		newUserTracker.setSessionId(randomString());
		newUserTracker.setRemoteAddr(randomString());
		newUserTracker.setRemoteHost(randomString());
		newUserTracker.setUserAgent(randomString());

		_persistence.update(newUserTracker);

		UserTracker existingUserTracker = _persistence.findByPrimaryKey(newUserTracker.getPrimaryKey());

		assertEquals(existingUserTracker.getUserTrackerId(),
			newUserTracker.getUserTrackerId());
		assertEquals(existingUserTracker.getCompanyId(),
			newUserTracker.getCompanyId());
		assertEquals(existingUserTracker.getUserId(), newUserTracker.getUserId());
		assertEquals(existingUserTracker.getModifiedDate(),
			newUserTracker.getModifiedDate());
		assertEquals(existingUserTracker.getSessionId(),
			newUserTracker.getSessionId());
		assertEquals(existingUserTracker.getRemoteAddr(),
			newUserTracker.getRemoteAddr());
		assertEquals(existingUserTracker.getRemoteHost(),
			newUserTracker.getRemoteHost());
		assertEquals(existingUserTracker.getUserAgent(),
			newUserTracker.getUserAgent());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		UserTracker newUserTracker = addUserTracker();

		UserTracker existingUserTracker = _persistence.findByPrimaryKey(newUserTracker.getPrimaryKey());

		assertEquals(existingUserTracker, newUserTracker);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchUserTrackerException");
		}
		catch (NoSuchUserTrackerException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		UserTracker newUserTracker = addUserTracker();

		UserTracker existingUserTracker = _persistence.fetchByPrimaryKey(newUserTracker.getPrimaryKey());

		assertEquals(existingUserTracker, newUserTracker);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		UserTracker missingUserTracker = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingUserTracker);
	}

	protected UserTracker addUserTracker() throws Exception {
		long pk = nextLong();

		UserTracker userTracker = _persistence.create(pk);

		userTracker.setCompanyId(nextLong());
		userTracker.setUserId(nextLong());
		userTracker.setModifiedDate(nextDate());
		userTracker.setSessionId(randomString());
		userTracker.setRemoteAddr(randomString());
		userTracker.setRemoteHost(randomString());
		userTracker.setUserAgent(randomString());

		_persistence.update(userTracker);

		return userTracker;
	}

	private static final String _TX_IMPL = UserTrackerPersistence.class.getName() +
		".transaction";
	private UserTrackerPersistence _persistence;
}