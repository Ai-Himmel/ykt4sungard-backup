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

import com.liferay.portal.NoSuchActivityTrackerException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.ActivityTracker;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="ActivityTrackerPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ActivityTrackerPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (ActivityTrackerPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		ActivityTracker activityTracker = _persistence.create(pk);

		assertNotNull(activityTracker);

		assertEquals(activityTracker.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		ActivityTracker newActivityTracker = addActivityTracker();

		_persistence.remove(newActivityTracker);

		ActivityTracker existingActivityTracker = _persistence.fetchByPrimaryKey(newActivityTracker.getPrimaryKey());

		assertNull(existingActivityTracker);
	}

	public void testUpdateNew() throws Exception {
		addActivityTracker();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		ActivityTracker newActivityTracker = _persistence.create(pk);

		newActivityTracker.setGroupId(nextLong());
		newActivityTracker.setCompanyId(nextLong());
		newActivityTracker.setUserId(nextLong());
		newActivityTracker.setUserName(randomString());
		newActivityTracker.setCreateDate(nextDate());
		newActivityTracker.setClassNameId(nextLong());
		newActivityTracker.setClassPK(nextLong());
		newActivityTracker.setActivity(randomString());
		newActivityTracker.setExtraData(randomString());
		newActivityTracker.setReceiverUserId(nextLong());
		newActivityTracker.setReceiverUserName(randomString());

		_persistence.update(newActivityTracker);

		ActivityTracker existingActivityTracker = _persistence.findByPrimaryKey(newActivityTracker.getPrimaryKey());

		assertEquals(existingActivityTracker.getActivityTrackerId(),
			newActivityTracker.getActivityTrackerId());
		assertEquals(existingActivityTracker.getGroupId(),
			newActivityTracker.getGroupId());
		assertEquals(existingActivityTracker.getCompanyId(),
			newActivityTracker.getCompanyId());
		assertEquals(existingActivityTracker.getUserId(),
			newActivityTracker.getUserId());
		assertEquals(existingActivityTracker.getUserName(),
			newActivityTracker.getUserName());
		assertEquals(existingActivityTracker.getCreateDate(),
			newActivityTracker.getCreateDate());
		assertEquals(existingActivityTracker.getClassNameId(),
			newActivityTracker.getClassNameId());
		assertEquals(existingActivityTracker.getClassPK(),
			newActivityTracker.getClassPK());
		assertEquals(existingActivityTracker.getActivity(),
			newActivityTracker.getActivity());
		assertEquals(existingActivityTracker.getExtraData(),
			newActivityTracker.getExtraData());
		assertEquals(existingActivityTracker.getReceiverUserId(),
			newActivityTracker.getReceiverUserId());
		assertEquals(existingActivityTracker.getReceiverUserName(),
			newActivityTracker.getReceiverUserName());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		ActivityTracker newActivityTracker = addActivityTracker();

		ActivityTracker existingActivityTracker = _persistence.findByPrimaryKey(newActivityTracker.getPrimaryKey());

		assertEquals(existingActivityTracker, newActivityTracker);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchActivityTrackerException");
		}
		catch (NoSuchActivityTrackerException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		ActivityTracker newActivityTracker = addActivityTracker();

		ActivityTracker existingActivityTracker = _persistence.fetchByPrimaryKey(newActivityTracker.getPrimaryKey());

		assertEquals(existingActivityTracker, newActivityTracker);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		ActivityTracker missingActivityTracker = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingActivityTracker);
	}

	protected ActivityTracker addActivityTracker() throws Exception {
		long pk = nextLong();

		ActivityTracker activityTracker = _persistence.create(pk);

		activityTracker.setGroupId(nextLong());
		activityTracker.setCompanyId(nextLong());
		activityTracker.setUserId(nextLong());
		activityTracker.setUserName(randomString());
		activityTracker.setCreateDate(nextDate());
		activityTracker.setClassNameId(nextLong());
		activityTracker.setClassPK(nextLong());
		activityTracker.setActivity(randomString());
		activityTracker.setExtraData(randomString());
		activityTracker.setReceiverUserId(nextLong());
		activityTracker.setReceiverUserName(randomString());

		_persistence.update(activityTracker);

		return activityTracker;
	}

	private static final String _TX_IMPL = ActivityTrackerPersistence.class.getName() +
		".transaction";
	private ActivityTrackerPersistence _persistence;
}