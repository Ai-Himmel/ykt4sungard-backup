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

import com.liferay.portal.NoSuchPasswordPolicyException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.PasswordPolicy;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="PasswordPolicyPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PasswordPolicyPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (PasswordPolicyPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		PasswordPolicy passwordPolicy = _persistence.create(pk);

		assertNotNull(passwordPolicy);

		assertEquals(passwordPolicy.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		PasswordPolicy newPasswordPolicy = addPasswordPolicy();

		_persistence.remove(newPasswordPolicy);

		PasswordPolicy existingPasswordPolicy = _persistence.fetchByPrimaryKey(newPasswordPolicy.getPrimaryKey());

		assertNull(existingPasswordPolicy);
	}

	public void testUpdateNew() throws Exception {
		addPasswordPolicy();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		PasswordPolicy newPasswordPolicy = _persistence.create(pk);

		newPasswordPolicy.setCompanyId(nextLong());
		newPasswordPolicy.setUserId(nextLong());
		newPasswordPolicy.setUserName(randomString());
		newPasswordPolicy.setCreateDate(nextDate());
		newPasswordPolicy.setModifiedDate(nextDate());
		newPasswordPolicy.setDefaultPolicy(randomBoolean());
		newPasswordPolicy.setName(randomString());
		newPasswordPolicy.setDescription(randomString());
		newPasswordPolicy.setChangeable(randomBoolean());
		newPasswordPolicy.setChangeRequired(randomBoolean());
		newPasswordPolicy.setMinAge(nextLong());
		newPasswordPolicy.setCheckSyntax(randomBoolean());
		newPasswordPolicy.setAllowDictionaryWords(randomBoolean());
		newPasswordPolicy.setMinLength(nextInt());
		newPasswordPolicy.setHistory(randomBoolean());
		newPasswordPolicy.setHistoryCount(nextInt());
		newPasswordPolicy.setExpireable(randomBoolean());
		newPasswordPolicy.setMaxAge(nextLong());
		newPasswordPolicy.setWarningTime(nextLong());
		newPasswordPolicy.setGraceLimit(nextInt());
		newPasswordPolicy.setLockout(randomBoolean());
		newPasswordPolicy.setMaxFailure(nextInt());
		newPasswordPolicy.setLockoutDuration(nextLong());
		newPasswordPolicy.setRequireUnlock(randomBoolean());
		newPasswordPolicy.setResetFailureCount(nextLong());

		_persistence.update(newPasswordPolicy);

		PasswordPolicy existingPasswordPolicy = _persistence.findByPrimaryKey(newPasswordPolicy.getPrimaryKey());

		assertEquals(existingPasswordPolicy.getPasswordPolicyId(),
			newPasswordPolicy.getPasswordPolicyId());
		assertEquals(existingPasswordPolicy.getCompanyId(),
			newPasswordPolicy.getCompanyId());
		assertEquals(existingPasswordPolicy.getUserId(),
			newPasswordPolicy.getUserId());
		assertEquals(existingPasswordPolicy.getUserName(),
			newPasswordPolicy.getUserName());
		assertEquals(existingPasswordPolicy.getCreateDate(),
			newPasswordPolicy.getCreateDate());
		assertEquals(existingPasswordPolicy.getModifiedDate(),
			newPasswordPolicy.getModifiedDate());
		assertEquals(existingPasswordPolicy.getDefaultPolicy(),
			newPasswordPolicy.getDefaultPolicy());
		assertEquals(existingPasswordPolicy.getName(),
			newPasswordPolicy.getName());
		assertEquals(existingPasswordPolicy.getDescription(),
			newPasswordPolicy.getDescription());
		assertEquals(existingPasswordPolicy.getChangeable(),
			newPasswordPolicy.getChangeable());
		assertEquals(existingPasswordPolicy.getChangeRequired(),
			newPasswordPolicy.getChangeRequired());
		assertEquals(existingPasswordPolicy.getMinAge(),
			newPasswordPolicy.getMinAge());
		assertEquals(existingPasswordPolicy.getCheckSyntax(),
			newPasswordPolicy.getCheckSyntax());
		assertEquals(existingPasswordPolicy.getAllowDictionaryWords(),
			newPasswordPolicy.getAllowDictionaryWords());
		assertEquals(existingPasswordPolicy.getMinLength(),
			newPasswordPolicy.getMinLength());
		assertEquals(existingPasswordPolicy.getHistory(),
			newPasswordPolicy.getHistory());
		assertEquals(existingPasswordPolicy.getHistoryCount(),
			newPasswordPolicy.getHistoryCount());
		assertEquals(existingPasswordPolicy.getExpireable(),
			newPasswordPolicy.getExpireable());
		assertEquals(existingPasswordPolicy.getMaxAge(),
			newPasswordPolicy.getMaxAge());
		assertEquals(existingPasswordPolicy.getWarningTime(),
			newPasswordPolicy.getWarningTime());
		assertEquals(existingPasswordPolicy.getGraceLimit(),
			newPasswordPolicy.getGraceLimit());
		assertEquals(existingPasswordPolicy.getLockout(),
			newPasswordPolicy.getLockout());
		assertEquals(existingPasswordPolicy.getMaxFailure(),
			newPasswordPolicy.getMaxFailure());
		assertEquals(existingPasswordPolicy.getLockoutDuration(),
			newPasswordPolicy.getLockoutDuration());
		assertEquals(existingPasswordPolicy.getRequireUnlock(),
			newPasswordPolicy.getRequireUnlock());
		assertEquals(existingPasswordPolicy.getResetFailureCount(),
			newPasswordPolicy.getResetFailureCount());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		PasswordPolicy newPasswordPolicy = addPasswordPolicy();

		PasswordPolicy existingPasswordPolicy = _persistence.findByPrimaryKey(newPasswordPolicy.getPrimaryKey());

		assertEquals(existingPasswordPolicy, newPasswordPolicy);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchPasswordPolicyException");
		}
		catch (NoSuchPasswordPolicyException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		PasswordPolicy newPasswordPolicy = addPasswordPolicy();

		PasswordPolicy existingPasswordPolicy = _persistence.fetchByPrimaryKey(newPasswordPolicy.getPrimaryKey());

		assertEquals(existingPasswordPolicy, newPasswordPolicy);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		PasswordPolicy missingPasswordPolicy = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingPasswordPolicy);
	}

	protected PasswordPolicy addPasswordPolicy() throws Exception {
		long pk = nextLong();

		PasswordPolicy passwordPolicy = _persistence.create(pk);

		passwordPolicy.setCompanyId(nextLong());
		passwordPolicy.setUserId(nextLong());
		passwordPolicy.setUserName(randomString());
		passwordPolicy.setCreateDate(nextDate());
		passwordPolicy.setModifiedDate(nextDate());
		passwordPolicy.setDefaultPolicy(randomBoolean());
		passwordPolicy.setName(randomString());
		passwordPolicy.setDescription(randomString());
		passwordPolicy.setChangeable(randomBoolean());
		passwordPolicy.setChangeRequired(randomBoolean());
		passwordPolicy.setMinAge(nextLong());
		passwordPolicy.setCheckSyntax(randomBoolean());
		passwordPolicy.setAllowDictionaryWords(randomBoolean());
		passwordPolicy.setMinLength(nextInt());
		passwordPolicy.setHistory(randomBoolean());
		passwordPolicy.setHistoryCount(nextInt());
		passwordPolicy.setExpireable(randomBoolean());
		passwordPolicy.setMaxAge(nextLong());
		passwordPolicy.setWarningTime(nextLong());
		passwordPolicy.setGraceLimit(nextInt());
		passwordPolicy.setLockout(randomBoolean());
		passwordPolicy.setMaxFailure(nextInt());
		passwordPolicy.setLockoutDuration(nextLong());
		passwordPolicy.setRequireUnlock(randomBoolean());
		passwordPolicy.setResetFailureCount(nextLong());

		_persistence.update(passwordPolicy);

		return passwordPolicy;
	}

	private static final String _TX_IMPL = PasswordPolicyPersistence.class.getName() +
		".transaction";
	private PasswordPolicyPersistence _persistence;
}