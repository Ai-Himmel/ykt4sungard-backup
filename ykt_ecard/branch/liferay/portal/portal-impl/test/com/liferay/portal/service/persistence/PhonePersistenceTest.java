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

import com.liferay.portal.NoSuchPhoneException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.Phone;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="PhonePersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PhonePersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (PhonePersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		Phone phone = _persistence.create(pk);

		assertNotNull(phone);

		assertEquals(phone.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		Phone newPhone = addPhone();

		_persistence.remove(newPhone);

		Phone existingPhone = _persistence.fetchByPrimaryKey(newPhone.getPrimaryKey());

		assertNull(existingPhone);
	}

	public void testUpdateNew() throws Exception {
		addPhone();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		Phone newPhone = _persistence.create(pk);

		newPhone.setCompanyId(nextLong());
		newPhone.setUserId(nextLong());
		newPhone.setUserName(randomString());
		newPhone.setCreateDate(nextDate());
		newPhone.setModifiedDate(nextDate());
		newPhone.setClassNameId(nextLong());
		newPhone.setClassPK(nextLong());
		newPhone.setNumber(randomString());
		newPhone.setExtension(randomString());
		newPhone.setTypeId(nextInt());
		newPhone.setPrimary(randomBoolean());

		_persistence.update(newPhone);

		Phone existingPhone = _persistence.findByPrimaryKey(newPhone.getPrimaryKey());

		assertEquals(existingPhone.getPhoneId(), newPhone.getPhoneId());
		assertEquals(existingPhone.getCompanyId(), newPhone.getCompanyId());
		assertEquals(existingPhone.getUserId(), newPhone.getUserId());
		assertEquals(existingPhone.getUserName(), newPhone.getUserName());
		assertEquals(existingPhone.getCreateDate(), newPhone.getCreateDate());
		assertEquals(existingPhone.getModifiedDate(), newPhone.getModifiedDate());
		assertEquals(existingPhone.getClassNameId(), newPhone.getClassNameId());
		assertEquals(existingPhone.getClassPK(), newPhone.getClassPK());
		assertEquals(existingPhone.getNumber(), newPhone.getNumber());
		assertEquals(existingPhone.getExtension(), newPhone.getExtension());
		assertEquals(existingPhone.getTypeId(), newPhone.getTypeId());
		assertEquals(existingPhone.getPrimary(), newPhone.getPrimary());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		Phone newPhone = addPhone();

		Phone existingPhone = _persistence.findByPrimaryKey(newPhone.getPrimaryKey());

		assertEquals(existingPhone, newPhone);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchPhoneException");
		}
		catch (NoSuchPhoneException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		Phone newPhone = addPhone();

		Phone existingPhone = _persistence.fetchByPrimaryKey(newPhone.getPrimaryKey());

		assertEquals(existingPhone, newPhone);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		Phone missingPhone = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingPhone);
	}

	protected Phone addPhone() throws Exception {
		long pk = nextLong();

		Phone phone = _persistence.create(pk);

		phone.setCompanyId(nextLong());
		phone.setUserId(nextLong());
		phone.setUserName(randomString());
		phone.setCreateDate(nextDate());
		phone.setModifiedDate(nextDate());
		phone.setClassNameId(nextLong());
		phone.setClassPK(nextLong());
		phone.setNumber(randomString());
		phone.setExtension(randomString());
		phone.setTypeId(nextInt());
		phone.setPrimary(randomBoolean());

		_persistence.update(phone);

		return phone;
	}

	private static final String _TX_IMPL = PhonePersistence.class.getName() +
		".transaction";
	private PhonePersistence _persistence;
}