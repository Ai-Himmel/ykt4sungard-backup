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

import com.liferay.portlet.messageboards.NoSuchBanException;
import com.liferay.portlet.messageboards.model.MBBan;

/**
 * <a href="MBBanPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBBanPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (MBBanPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		MBBan mbBan = _persistence.create(pk);

		assertNotNull(mbBan);

		assertEquals(mbBan.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		MBBan newMBBan = addMBBan();

		_persistence.remove(newMBBan);

		MBBan existingMBBan = _persistence.fetchByPrimaryKey(newMBBan.getPrimaryKey());

		assertNull(existingMBBan);
	}

	public void testUpdateNew() throws Exception {
		addMBBan();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		MBBan newMBBan = _persistence.create(pk);

		newMBBan.setGroupId(nextLong());
		newMBBan.setCompanyId(nextLong());
		newMBBan.setUserId(nextLong());
		newMBBan.setUserName(randomString());
		newMBBan.setCreateDate(nextDate());
		newMBBan.setModifiedDate(nextDate());
		newMBBan.setBanUserId(nextLong());

		_persistence.update(newMBBan);

		MBBan existingMBBan = _persistence.findByPrimaryKey(newMBBan.getPrimaryKey());

		assertEquals(existingMBBan.getBanId(), newMBBan.getBanId());
		assertEquals(existingMBBan.getGroupId(), newMBBan.getGroupId());
		assertEquals(existingMBBan.getCompanyId(), newMBBan.getCompanyId());
		assertEquals(existingMBBan.getUserId(), newMBBan.getUserId());
		assertEquals(existingMBBan.getUserName(), newMBBan.getUserName());
		assertEquals(existingMBBan.getCreateDate(), newMBBan.getCreateDate());
		assertEquals(existingMBBan.getModifiedDate(), newMBBan.getModifiedDate());
		assertEquals(existingMBBan.getBanUserId(), newMBBan.getBanUserId());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		MBBan newMBBan = addMBBan();

		MBBan existingMBBan = _persistence.findByPrimaryKey(newMBBan.getPrimaryKey());

		assertEquals(existingMBBan, newMBBan);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchBanException");
		}
		catch (NoSuchBanException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		MBBan newMBBan = addMBBan();

		MBBan existingMBBan = _persistence.fetchByPrimaryKey(newMBBan.getPrimaryKey());

		assertEquals(existingMBBan, newMBBan);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		MBBan missingMBBan = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingMBBan);
	}

	protected MBBan addMBBan() throws Exception {
		long pk = nextLong();

		MBBan mbBan = _persistence.create(pk);

		mbBan.setGroupId(nextLong());
		mbBan.setCompanyId(nextLong());
		mbBan.setUserId(nextLong());
		mbBan.setUserName(randomString());
		mbBan.setCreateDate(nextDate());
		mbBan.setModifiedDate(nextDate());
		mbBan.setBanUserId(nextLong());

		_persistence.update(mbBan);

		return mbBan;
	}

	private static final String _TX_IMPL = MBBanPersistence.class.getName() +
		".transaction";
	private MBBanPersistence _persistence;
}