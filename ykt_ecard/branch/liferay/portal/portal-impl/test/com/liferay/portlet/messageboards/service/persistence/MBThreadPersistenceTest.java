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

import com.liferay.portlet.messageboards.NoSuchThreadException;
import com.liferay.portlet.messageboards.model.MBThread;

/**
 * <a href="MBThreadPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBThreadPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (MBThreadPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		MBThread mbThread = _persistence.create(pk);

		assertNotNull(mbThread);

		assertEquals(mbThread.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		MBThread newMBThread = addMBThread();

		_persistence.remove(newMBThread);

		MBThread existingMBThread = _persistence.fetchByPrimaryKey(newMBThread.getPrimaryKey());

		assertNull(existingMBThread);
	}

	public void testUpdateNew() throws Exception {
		addMBThread();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		MBThread newMBThread = _persistence.create(pk);

		newMBThread.setCategoryId(nextLong());
		newMBThread.setRootMessageId(nextLong());
		newMBThread.setMessageCount(nextInt());
		newMBThread.setViewCount(nextInt());
		newMBThread.setLastPostByUserId(nextLong());
		newMBThread.setLastPostDate(nextDate());
		newMBThread.setPriority(nextDouble());

		_persistence.update(newMBThread);

		MBThread existingMBThread = _persistence.findByPrimaryKey(newMBThread.getPrimaryKey());

		assertEquals(existingMBThread.getThreadId(), newMBThread.getThreadId());
		assertEquals(existingMBThread.getCategoryId(),
			newMBThread.getCategoryId());
		assertEquals(existingMBThread.getRootMessageId(),
			newMBThread.getRootMessageId());
		assertEquals(existingMBThread.getMessageCount(),
			newMBThread.getMessageCount());
		assertEquals(existingMBThread.getViewCount(), newMBThread.getViewCount());
		assertEquals(existingMBThread.getLastPostByUserId(),
			newMBThread.getLastPostByUserId());
		assertEquals(existingMBThread.getLastPostDate(),
			newMBThread.getLastPostDate());
		assertEquals(existingMBThread.getPriority(), newMBThread.getPriority());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		MBThread newMBThread = addMBThread();

		MBThread existingMBThread = _persistence.findByPrimaryKey(newMBThread.getPrimaryKey());

		assertEquals(existingMBThread, newMBThread);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchThreadException");
		}
		catch (NoSuchThreadException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		MBThread newMBThread = addMBThread();

		MBThread existingMBThread = _persistence.fetchByPrimaryKey(newMBThread.getPrimaryKey());

		assertEquals(existingMBThread, newMBThread);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		MBThread missingMBThread = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingMBThread);
	}

	protected MBThread addMBThread() throws Exception {
		long pk = nextLong();

		MBThread mbThread = _persistence.create(pk);

		mbThread.setCategoryId(nextLong());
		mbThread.setRootMessageId(nextLong());
		mbThread.setMessageCount(nextInt());
		mbThread.setViewCount(nextInt());
		mbThread.setLastPostByUserId(nextLong());
		mbThread.setLastPostDate(nextDate());
		mbThread.setPriority(nextDouble());

		_persistence.update(mbThread);

		return mbThread;
	}

	private static final String _TX_IMPL = MBThreadPersistence.class.getName() +
		".transaction";
	private MBThreadPersistence _persistence;
}