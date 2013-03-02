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

import com.liferay.portal.NoSuchUserTrackerPathException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.UserTrackerPath;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="UserTrackerPathPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UserTrackerPathPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (UserTrackerPathPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		UserTrackerPath userTrackerPath = _persistence.create(pk);

		assertNotNull(userTrackerPath);

		assertEquals(userTrackerPath.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		UserTrackerPath newUserTrackerPath = addUserTrackerPath();

		_persistence.remove(newUserTrackerPath);

		UserTrackerPath existingUserTrackerPath = _persistence.fetchByPrimaryKey(newUserTrackerPath.getPrimaryKey());

		assertNull(existingUserTrackerPath);
	}

	public void testUpdateNew() throws Exception {
		addUserTrackerPath();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		UserTrackerPath newUserTrackerPath = _persistence.create(pk);

		newUserTrackerPath.setUserTrackerId(nextLong());
		newUserTrackerPath.setPath(randomString());
		newUserTrackerPath.setPathDate(nextDate());

		_persistence.update(newUserTrackerPath);

		UserTrackerPath existingUserTrackerPath = _persistence.findByPrimaryKey(newUserTrackerPath.getPrimaryKey());

		assertEquals(existingUserTrackerPath.getUserTrackerPathId(),
			newUserTrackerPath.getUserTrackerPathId());
		assertEquals(existingUserTrackerPath.getUserTrackerId(),
			newUserTrackerPath.getUserTrackerId());
		assertEquals(existingUserTrackerPath.getPath(),
			newUserTrackerPath.getPath());
		assertEquals(existingUserTrackerPath.getPathDate(),
			newUserTrackerPath.getPathDate());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		UserTrackerPath newUserTrackerPath = addUserTrackerPath();

		UserTrackerPath existingUserTrackerPath = _persistence.findByPrimaryKey(newUserTrackerPath.getPrimaryKey());

		assertEquals(existingUserTrackerPath, newUserTrackerPath);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchUserTrackerPathException");
		}
		catch (NoSuchUserTrackerPathException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		UserTrackerPath newUserTrackerPath = addUserTrackerPath();

		UserTrackerPath existingUserTrackerPath = _persistence.fetchByPrimaryKey(newUserTrackerPath.getPrimaryKey());

		assertEquals(existingUserTrackerPath, newUserTrackerPath);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		UserTrackerPath missingUserTrackerPath = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingUserTrackerPath);
	}

	protected UserTrackerPath addUserTrackerPath() throws Exception {
		long pk = nextLong();

		UserTrackerPath userTrackerPath = _persistence.create(pk);

		userTrackerPath.setUserTrackerId(nextLong());
		userTrackerPath.setPath(randomString());
		userTrackerPath.setPathDate(nextDate());

		_persistence.update(userTrackerPath);

		return userTrackerPath;
	}

	private static final String _TX_IMPL = UserTrackerPathPersistence.class.getName() +
		".transaction";
	private UserTrackerPathPersistence _persistence;
}