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

import com.liferay.portlet.messageboards.NoSuchDiscussionException;
import com.liferay.portlet.messageboards.model.MBDiscussion;

/**
 * <a href="MBDiscussionPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBDiscussionPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (MBDiscussionPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		MBDiscussion mbDiscussion = _persistence.create(pk);

		assertNotNull(mbDiscussion);

		assertEquals(mbDiscussion.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		MBDiscussion newMBDiscussion = addMBDiscussion();

		_persistence.remove(newMBDiscussion);

		MBDiscussion existingMBDiscussion = _persistence.fetchByPrimaryKey(newMBDiscussion.getPrimaryKey());

		assertNull(existingMBDiscussion);
	}

	public void testUpdateNew() throws Exception {
		addMBDiscussion();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		MBDiscussion newMBDiscussion = _persistence.create(pk);

		newMBDiscussion.setClassNameId(nextLong());
		newMBDiscussion.setClassPK(nextLong());
		newMBDiscussion.setThreadId(nextLong());

		_persistence.update(newMBDiscussion);

		MBDiscussion existingMBDiscussion = _persistence.findByPrimaryKey(newMBDiscussion.getPrimaryKey());

		assertEquals(existingMBDiscussion.getDiscussionId(),
			newMBDiscussion.getDiscussionId());
		assertEquals(existingMBDiscussion.getClassNameId(),
			newMBDiscussion.getClassNameId());
		assertEquals(existingMBDiscussion.getClassPK(),
			newMBDiscussion.getClassPK());
		assertEquals(existingMBDiscussion.getThreadId(),
			newMBDiscussion.getThreadId());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		MBDiscussion newMBDiscussion = addMBDiscussion();

		MBDiscussion existingMBDiscussion = _persistence.findByPrimaryKey(newMBDiscussion.getPrimaryKey());

		assertEquals(existingMBDiscussion, newMBDiscussion);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchDiscussionException");
		}
		catch (NoSuchDiscussionException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		MBDiscussion newMBDiscussion = addMBDiscussion();

		MBDiscussion existingMBDiscussion = _persistence.fetchByPrimaryKey(newMBDiscussion.getPrimaryKey());

		assertEquals(existingMBDiscussion, newMBDiscussion);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		MBDiscussion missingMBDiscussion = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingMBDiscussion);
	}

	protected MBDiscussion addMBDiscussion() throws Exception {
		long pk = nextLong();

		MBDiscussion mbDiscussion = _persistence.create(pk);

		mbDiscussion.setClassNameId(nextLong());
		mbDiscussion.setClassPK(nextLong());
		mbDiscussion.setThreadId(nextLong());

		_persistence.update(mbDiscussion);

		return mbDiscussion;
	}

	private static final String _TX_IMPL = MBDiscussionPersistence.class.getName() +
		".transaction";
	private MBDiscussionPersistence _persistence;
}