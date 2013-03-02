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

import com.liferay.portlet.messageboards.NoSuchMessageException;
import com.liferay.portlet.messageboards.model.MBMessage;

/**
 * <a href="MBMessagePersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBMessagePersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (MBMessagePersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		MBMessage mbMessage = _persistence.create(pk);

		assertNotNull(mbMessage);

		assertEquals(mbMessage.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		MBMessage newMBMessage = addMBMessage();

		_persistence.remove(newMBMessage);

		MBMessage existingMBMessage = _persistence.fetchByPrimaryKey(newMBMessage.getPrimaryKey());

		assertNull(existingMBMessage);
	}

	public void testUpdateNew() throws Exception {
		addMBMessage();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		MBMessage newMBMessage = _persistence.create(pk);

		newMBMessage.setUuid(randomString());
		newMBMessage.setCompanyId(nextLong());
		newMBMessage.setUserId(nextLong());
		newMBMessage.setUserName(randomString());
		newMBMessage.setCreateDate(nextDate());
		newMBMessage.setModifiedDate(nextDate());
		newMBMessage.setCategoryId(nextLong());
		newMBMessage.setThreadId(nextLong());
		newMBMessage.setParentMessageId(nextLong());
		newMBMessage.setSubject(randomString());
		newMBMessage.setBody(randomString());
		newMBMessage.setAttachments(randomBoolean());
		newMBMessage.setAnonymous(randomBoolean());

		_persistence.update(newMBMessage);

		MBMessage existingMBMessage = _persistence.findByPrimaryKey(newMBMessage.getPrimaryKey());

		assertEquals(existingMBMessage.getUuid(), newMBMessage.getUuid());
		assertEquals(existingMBMessage.getMessageId(),
			newMBMessage.getMessageId());
		assertEquals(existingMBMessage.getCompanyId(),
			newMBMessage.getCompanyId());
		assertEquals(existingMBMessage.getUserId(), newMBMessage.getUserId());
		assertEquals(existingMBMessage.getUserName(), newMBMessage.getUserName());
		assertEquals(existingMBMessage.getCreateDate(),
			newMBMessage.getCreateDate());
		assertEquals(existingMBMessage.getModifiedDate(),
			newMBMessage.getModifiedDate());
		assertEquals(existingMBMessage.getCategoryId(),
			newMBMessage.getCategoryId());
		assertEquals(existingMBMessage.getThreadId(), newMBMessage.getThreadId());
		assertEquals(existingMBMessage.getParentMessageId(),
			newMBMessage.getParentMessageId());
		assertEquals(existingMBMessage.getSubject(), newMBMessage.getSubject());
		assertEquals(existingMBMessage.getBody(), newMBMessage.getBody());
		assertEquals(existingMBMessage.getAttachments(),
			newMBMessage.getAttachments());
		assertEquals(existingMBMessage.getAnonymous(),
			newMBMessage.getAnonymous());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		MBMessage newMBMessage = addMBMessage();

		MBMessage existingMBMessage = _persistence.findByPrimaryKey(newMBMessage.getPrimaryKey());

		assertEquals(existingMBMessage, newMBMessage);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchMessageException");
		}
		catch (NoSuchMessageException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		MBMessage newMBMessage = addMBMessage();

		MBMessage existingMBMessage = _persistence.fetchByPrimaryKey(newMBMessage.getPrimaryKey());

		assertEquals(existingMBMessage, newMBMessage);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		MBMessage missingMBMessage = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingMBMessage);
	}

	protected MBMessage addMBMessage() throws Exception {
		long pk = nextLong();

		MBMessage mbMessage = _persistence.create(pk);

		mbMessage.setUuid(randomString());
		mbMessage.setCompanyId(nextLong());
		mbMessage.setUserId(nextLong());
		mbMessage.setUserName(randomString());
		mbMessage.setCreateDate(nextDate());
		mbMessage.setModifiedDate(nextDate());
		mbMessage.setCategoryId(nextLong());
		mbMessage.setThreadId(nextLong());
		mbMessage.setParentMessageId(nextLong());
		mbMessage.setSubject(randomString());
		mbMessage.setBody(randomString());
		mbMessage.setAttachments(randomBoolean());
		mbMessage.setAnonymous(randomBoolean());

		_persistence.update(mbMessage);

		return mbMessage;
	}

	private static final String _TX_IMPL = MBMessagePersistence.class.getName() +
		".transaction";
	private MBMessagePersistence _persistence;
}