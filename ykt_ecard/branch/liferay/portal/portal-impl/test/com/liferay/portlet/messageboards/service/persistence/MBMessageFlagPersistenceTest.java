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

import com.liferay.portlet.messageboards.NoSuchMessageFlagException;
import com.liferay.portlet.messageboards.model.MBMessageFlag;

/**
 * <a href="MBMessageFlagPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBMessageFlagPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (MBMessageFlagPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		MBMessageFlag mbMessageFlag = _persistence.create(pk);

		assertNotNull(mbMessageFlag);

		assertEquals(mbMessageFlag.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		MBMessageFlag newMBMessageFlag = addMBMessageFlag();

		_persistence.remove(newMBMessageFlag);

		MBMessageFlag existingMBMessageFlag = _persistence.fetchByPrimaryKey(newMBMessageFlag.getPrimaryKey());

		assertNull(existingMBMessageFlag);
	}

	public void testUpdateNew() throws Exception {
		addMBMessageFlag();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		MBMessageFlag newMBMessageFlag = _persistence.create(pk);

		newMBMessageFlag.setUserId(nextLong());
		newMBMessageFlag.setMessageId(nextLong());
		newMBMessageFlag.setFlag(nextInt());

		_persistence.update(newMBMessageFlag);

		MBMessageFlag existingMBMessageFlag = _persistence.findByPrimaryKey(newMBMessageFlag.getPrimaryKey());

		assertEquals(existingMBMessageFlag.getMessageFlagId(),
			newMBMessageFlag.getMessageFlagId());
		assertEquals(existingMBMessageFlag.getUserId(),
			newMBMessageFlag.getUserId());
		assertEquals(existingMBMessageFlag.getMessageId(),
			newMBMessageFlag.getMessageId());
		assertEquals(existingMBMessageFlag.getFlag(), newMBMessageFlag.getFlag());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		MBMessageFlag newMBMessageFlag = addMBMessageFlag();

		MBMessageFlag existingMBMessageFlag = _persistence.findByPrimaryKey(newMBMessageFlag.getPrimaryKey());

		assertEquals(existingMBMessageFlag, newMBMessageFlag);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchMessageFlagException");
		}
		catch (NoSuchMessageFlagException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		MBMessageFlag newMBMessageFlag = addMBMessageFlag();

		MBMessageFlag existingMBMessageFlag = _persistence.fetchByPrimaryKey(newMBMessageFlag.getPrimaryKey());

		assertEquals(existingMBMessageFlag, newMBMessageFlag);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		MBMessageFlag missingMBMessageFlag = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingMBMessageFlag);
	}

	protected MBMessageFlag addMBMessageFlag() throws Exception {
		long pk = nextLong();

		MBMessageFlag mbMessageFlag = _persistence.create(pk);

		mbMessageFlag.setUserId(nextLong());
		mbMessageFlag.setMessageId(nextLong());
		mbMessageFlag.setFlag(nextInt());

		_persistence.update(mbMessageFlag);

		return mbMessageFlag;
	}

	private static final String _TX_IMPL = MBMessageFlagPersistence.class.getName() +
		".transaction";
	private MBMessageFlagPersistence _persistence;
}