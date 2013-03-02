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

import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.User;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="UserPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class UserPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (UserPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		User user = _persistence.create(pk);

		assertNotNull(user);

		assertEquals(user.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		User newUser = addUser();

		_persistence.remove(newUser);

		User existingUser = _persistence.fetchByPrimaryKey(newUser.getPrimaryKey());

		assertNull(existingUser);
	}

	public void testUpdateNew() throws Exception {
		addUser();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		User newUser = _persistence.create(pk);

		newUser.setUuid(randomString());
		newUser.setCompanyId(nextLong());
		newUser.setCreateDate(nextDate());
		newUser.setModifiedDate(nextDate());
		newUser.setDefaultUser(randomBoolean());
		newUser.setContactId(nextLong());
		newUser.setPassword(randomString());
		newUser.setPasswordEncrypted(randomBoolean());
		newUser.setPasswordReset(randomBoolean());
		newUser.setPasswordModifiedDate(nextDate());
		newUser.setGraceLoginCount(nextInt());
		newUser.setScreenName(randomString());
		newUser.setEmailAddress(randomString());
		newUser.setPortraitId(nextLong());
		newUser.setLanguageId(randomString());
		newUser.setTimeZoneId(randomString());
		newUser.setGreeting(randomString());
		newUser.setComments(randomString());
		newUser.setLoginDate(nextDate());
		newUser.setLoginIP(randomString());
		newUser.setLastLoginDate(nextDate());
		newUser.setLastLoginIP(randomString());
		newUser.setLastFailedLoginDate(nextDate());
		newUser.setFailedLoginAttempts(nextInt());
		newUser.setLockout(randomBoolean());
		newUser.setLockoutDate(nextDate());
		newUser.setAgreedToTermsOfUse(randomBoolean());
		newUser.setActive(randomBoolean());

		_persistence.update(newUser);

		User existingUser = _persistence.findByPrimaryKey(newUser.getPrimaryKey());

		assertEquals(existingUser.getUuid(), newUser.getUuid());
		assertEquals(existingUser.getUserId(), newUser.getUserId());
		assertEquals(existingUser.getCompanyId(), newUser.getCompanyId());
		assertEquals(existingUser.getCreateDate(), newUser.getCreateDate());
		assertEquals(existingUser.getModifiedDate(), newUser.getModifiedDate());
		assertEquals(existingUser.getDefaultUser(), newUser.getDefaultUser());
		assertEquals(existingUser.getContactId(), newUser.getContactId());
		assertEquals(existingUser.getPassword(), newUser.getPassword());
		assertEquals(existingUser.getPasswordEncrypted(),
			newUser.getPasswordEncrypted());
		assertEquals(existingUser.getPasswordReset(), newUser.getPasswordReset());
		assertEquals(existingUser.getPasswordModifiedDate(),
			newUser.getPasswordModifiedDate());
		assertEquals(existingUser.getGraceLoginCount(),
			newUser.getGraceLoginCount());
		assertEquals(existingUser.getScreenName(), newUser.getScreenName());
		assertEquals(existingUser.getEmailAddress(), newUser.getEmailAddress());
		assertEquals(existingUser.getPortraitId(), newUser.getPortraitId());
		assertEquals(existingUser.getLanguageId(), newUser.getLanguageId());
		assertEquals(existingUser.getTimeZoneId(), newUser.getTimeZoneId());
		assertEquals(existingUser.getGreeting(), newUser.getGreeting());
		assertEquals(existingUser.getComments(), newUser.getComments());
		assertEquals(existingUser.getLoginDate(), newUser.getLoginDate());
		assertEquals(existingUser.getLoginIP(), newUser.getLoginIP());
		assertEquals(existingUser.getLastLoginDate(), newUser.getLastLoginDate());
		assertEquals(existingUser.getLastLoginIP(), newUser.getLastLoginIP());
		assertEquals(existingUser.getLastFailedLoginDate(),
			newUser.getLastFailedLoginDate());
		assertEquals(existingUser.getFailedLoginAttempts(),
			newUser.getFailedLoginAttempts());
		assertEquals(existingUser.getLockout(), newUser.getLockout());
		assertEquals(existingUser.getLockoutDate(), newUser.getLockoutDate());
		assertEquals(existingUser.getAgreedToTermsOfUse(),
			newUser.getAgreedToTermsOfUse());
		assertEquals(existingUser.getActive(), newUser.getActive());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		User newUser = addUser();

		User existingUser = _persistence.findByPrimaryKey(newUser.getPrimaryKey());

		assertEquals(existingUser, newUser);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchUserException");
		}
		catch (NoSuchUserException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		User newUser = addUser();

		User existingUser = _persistence.fetchByPrimaryKey(newUser.getPrimaryKey());

		assertEquals(existingUser, newUser);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		User missingUser = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingUser);
	}

	protected User addUser() throws Exception {
		long pk = nextLong();

		User user = _persistence.create(pk);

		user.setUuid(randomString());
		user.setCompanyId(nextLong());
		user.setCreateDate(nextDate());
		user.setModifiedDate(nextDate());
		user.setDefaultUser(randomBoolean());
		user.setContactId(nextLong());
		user.setPassword(randomString());
		user.setPasswordEncrypted(randomBoolean());
		user.setPasswordReset(randomBoolean());
		user.setPasswordModifiedDate(nextDate());
		user.setGraceLoginCount(nextInt());
		user.setScreenName(randomString());
		user.setEmailAddress(randomString());
		user.setPortraitId(nextLong());
		user.setLanguageId(randomString());
		user.setTimeZoneId(randomString());
		user.setGreeting(randomString());
		user.setComments(randomString());
		user.setLoginDate(nextDate());
		user.setLoginIP(randomString());
		user.setLastLoginDate(nextDate());
		user.setLastLoginIP(randomString());
		user.setLastFailedLoginDate(nextDate());
		user.setFailedLoginAttempts(nextInt());
		user.setLockout(randomBoolean());
		user.setLockoutDate(nextDate());
		user.setAgreedToTermsOfUse(randomBoolean());
		user.setActive(randomBoolean());

		_persistence.update(user);

		return user;
	}

	private static final String _TX_IMPL = UserPersistence.class.getName() +
		".transaction";
	private UserPersistence _persistence;
}