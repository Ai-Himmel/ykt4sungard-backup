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

import com.liferay.portal.NoSuchContactException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.Contact;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="ContactPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ContactPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (ContactPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		Contact contact = _persistence.create(pk);

		assertNotNull(contact);

		assertEquals(contact.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		Contact newContact = addContact();

		_persistence.remove(newContact);

		Contact existingContact = _persistence.fetchByPrimaryKey(newContact.getPrimaryKey());

		assertNull(existingContact);
	}

	public void testUpdateNew() throws Exception {
		addContact();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		Contact newContact = _persistence.create(pk);

		newContact.setCompanyId(nextLong());
		newContact.setUserId(nextLong());
		newContact.setUserName(randomString());
		newContact.setCreateDate(nextDate());
		newContact.setModifiedDate(nextDate());
		newContact.setAccountId(nextLong());
		newContact.setParentContactId(nextLong());
		newContact.setFirstName(randomString());
		newContact.setMiddleName(randomString());
		newContact.setLastName(randomString());
		newContact.setPrefixId(nextInt());
		newContact.setSuffixId(nextInt());
		newContact.setMale(randomBoolean());
		newContact.setBirthday(nextDate());
		newContact.setSmsSn(randomString());
		newContact.setAimSn(randomString());
		newContact.setIcqSn(randomString());
		newContact.setJabberSn(randomString());
		newContact.setMsnSn(randomString());
		newContact.setSkypeSn(randomString());
		newContact.setYmSn(randomString());
		newContact.setEmployeeStatusId(randomString());
		newContact.setEmployeeNumber(randomString());
		newContact.setJobTitle(randomString());
		newContact.setJobClass(randomString());
		newContact.setHoursOfOperation(randomString());

		_persistence.update(newContact);

		Contact existingContact = _persistence.findByPrimaryKey(newContact.getPrimaryKey());

		assertEquals(existingContact.getContactId(), newContact.getContactId());
		assertEquals(existingContact.getCompanyId(), newContact.getCompanyId());
		assertEquals(existingContact.getUserId(), newContact.getUserId());
		assertEquals(existingContact.getUserName(), newContact.getUserName());
		assertEquals(existingContact.getCreateDate(), newContact.getCreateDate());
		assertEquals(existingContact.getModifiedDate(),
			newContact.getModifiedDate());
		assertEquals(existingContact.getAccountId(), newContact.getAccountId());
		assertEquals(existingContact.getParentContactId(),
			newContact.getParentContactId());
		assertEquals(existingContact.getFirstName(), newContact.getFirstName());
		assertEquals(existingContact.getMiddleName(), newContact.getMiddleName());
		assertEquals(existingContact.getLastName(), newContact.getLastName());
		assertEquals(existingContact.getPrefixId(), newContact.getPrefixId());
		assertEquals(existingContact.getSuffixId(), newContact.getSuffixId());
		assertEquals(existingContact.getMale(), newContact.getMale());
		assertEquals(existingContact.getBirthday(), newContact.getBirthday());
		assertEquals(existingContact.getSmsSn(), newContact.getSmsSn());
		assertEquals(existingContact.getAimSn(), newContact.getAimSn());
		assertEquals(existingContact.getIcqSn(), newContact.getIcqSn());
		assertEquals(existingContact.getJabberSn(), newContact.getJabberSn());
		assertEquals(existingContact.getMsnSn(), newContact.getMsnSn());
		assertEquals(existingContact.getSkypeSn(), newContact.getSkypeSn());
		assertEquals(existingContact.getYmSn(), newContact.getYmSn());
		assertEquals(existingContact.getEmployeeStatusId(),
			newContact.getEmployeeStatusId());
		assertEquals(existingContact.getEmployeeNumber(),
			newContact.getEmployeeNumber());
		assertEquals(existingContact.getJobTitle(), newContact.getJobTitle());
		assertEquals(existingContact.getJobClass(), newContact.getJobClass());
		assertEquals(existingContact.getHoursOfOperation(),
			newContact.getHoursOfOperation());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		Contact newContact = addContact();

		Contact existingContact = _persistence.findByPrimaryKey(newContact.getPrimaryKey());

		assertEquals(existingContact, newContact);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchContactException");
		}
		catch (NoSuchContactException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		Contact newContact = addContact();

		Contact existingContact = _persistence.fetchByPrimaryKey(newContact.getPrimaryKey());

		assertEquals(existingContact, newContact);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		Contact missingContact = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingContact);
	}

	protected Contact addContact() throws Exception {
		long pk = nextLong();

		Contact contact = _persistence.create(pk);

		contact.setCompanyId(nextLong());
		contact.setUserId(nextLong());
		contact.setUserName(randomString());
		contact.setCreateDate(nextDate());
		contact.setModifiedDate(nextDate());
		contact.setAccountId(nextLong());
		contact.setParentContactId(nextLong());
		contact.setFirstName(randomString());
		contact.setMiddleName(randomString());
		contact.setLastName(randomString());
		contact.setPrefixId(nextInt());
		contact.setSuffixId(nextInt());
		contact.setMale(randomBoolean());
		contact.setBirthday(nextDate());
		contact.setSmsSn(randomString());
		contact.setAimSn(randomString());
		contact.setIcqSn(randomString());
		contact.setJabberSn(randomString());
		contact.setMsnSn(randomString());
		contact.setSkypeSn(randomString());
		contact.setYmSn(randomString());
		contact.setEmployeeStatusId(randomString());
		contact.setEmployeeNumber(randomString());
		contact.setJobTitle(randomString());
		contact.setJobClass(randomString());
		contact.setHoursOfOperation(randomString());

		_persistence.update(contact);

		return contact;
	}

	private static final String _TX_IMPL = ContactPersistence.class.getName() +
		".transaction";
	private ContactPersistence _persistence;
}