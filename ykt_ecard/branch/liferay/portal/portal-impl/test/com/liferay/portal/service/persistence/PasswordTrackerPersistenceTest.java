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

import com.liferay.portal.NoSuchPasswordTrackerException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.PasswordTracker;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="PasswordTrackerPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PasswordTrackerPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (PasswordTrackerPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		PasswordTracker passwordTracker = _persistence.create(pk);

		assertNotNull(passwordTracker);

		assertEquals(passwordTracker.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		PasswordTracker newPasswordTracker = addPasswordTracker();

		_persistence.remove(newPasswordTracker);

		PasswordTracker existingPasswordTracker = _persistence.fetchByPrimaryKey(newPasswordTracker.getPrimaryKey());

		assertNull(existingPasswordTracker);
	}

	public void testUpdateNew() throws Exception {
		addPasswordTracker();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		PasswordTracker newPasswordTracker = _persistence.create(pk);

		newPasswordTracker.setUserId(nextLong());
		newPasswordTracker.setCreateDate(nextDate());
		newPasswordTracker.setPassword(randomString());

		_persistence.update(newPasswordTracker);

		PasswordTracker existingPasswordTracker = _persistence.findByPrimaryKey(newPasswordTracker.getPrimaryKey());

		assertEquals(existingPasswordTracker.getPasswordTrackerId(),
			newPasswordTracker.getPasswordTrackerId());
		assertEquals(existingPasswordTracker.getUserId(),
			newPasswordTracker.getUserId());
		assertEquals(existingPasswordTracker.getCreateDate(),
			newPasswordTracker.getCreateDate());
		assertEquals(existingPasswordTracker.getPassword(),
			newPasswordTracker.getPassword());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		PasswordTracker newPasswordTracker = addPasswordTracker();

		PasswordTracker existingPasswordTracker = _persistence.findByPrimaryKey(newPasswordTracker.getPrimaryKey());

		assertEquals(existingPasswordTracker, newPasswordTracker);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchPasswordTrackerException");
		}
		catch (NoSuchPasswordTrackerException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		PasswordTracker newPasswordTracker = addPasswordTracker();

		PasswordTracker existingPasswordTracker = _persistence.fetchByPrimaryKey(newPasswordTracker.getPrimaryKey());

		assertEquals(existingPasswordTracker, newPasswordTracker);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		PasswordTracker missingPasswordTracker = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingPasswordTracker);
	}

	protected PasswordTracker addPasswordTracker() throws Exception {
		long pk = nextLong();

		PasswordTracker passwordTracker = _persistence.create(pk);

		passwordTracker.setUserId(nextLong());
		passwordTracker.setCreateDate(nextDate());
		passwordTracker.setPassword(randomString());

		_persistence.update(passwordTracker);

		return passwordTracker;
	}

	private static final String _TX_IMPL = PasswordTrackerPersistence.class.getName() +
		".transaction";
	private PasswordTrackerPersistence _persistence;
}