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

import com.liferay.portal.NoSuchAccountException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;
import com.liferay.portal.model.Account;
import com.liferay.portal.service.persistence.BasePersistenceTestCase;

/**
 * <a href="AccountPersistenceTest.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class AccountPersistenceTest extends BasePersistenceTestCase {
	protected void setUp() throws Exception {
		super.setUp();

		_persistence = (AccountPersistence)BeanLocatorUtil.locate(_TX_IMPL);
	}

	public void testCreate() throws Exception {
		long pk = nextLong();

		Account account = _persistence.create(pk);

		assertNotNull(account);

		assertEquals(account.getPrimaryKey(), pk);
	}

	public void testRemove() throws Exception {
		Account newAccount = addAccount();

		_persistence.remove(newAccount);

		Account existingAccount = _persistence.fetchByPrimaryKey(newAccount.getPrimaryKey());

		assertNull(existingAccount);
	}

	public void testUpdateNew() throws Exception {
		addAccount();
	}

	public void testUpdateExisting() throws Exception {
		long pk = nextLong();

		Account newAccount = _persistence.create(pk);

		newAccount.setCompanyId(nextLong());
		newAccount.setUserId(nextLong());
		newAccount.setUserName(randomString());
		newAccount.setCreateDate(nextDate());
		newAccount.setModifiedDate(nextDate());
		newAccount.setParentAccountId(nextLong());
		newAccount.setName(randomString());
		newAccount.setLegalName(randomString());
		newAccount.setLegalId(randomString());
		newAccount.setLegalType(randomString());
		newAccount.setSicCode(randomString());
		newAccount.setTickerSymbol(randomString());
		newAccount.setIndustry(randomString());
		newAccount.setType(randomString());
		newAccount.setSize(randomString());

		_persistence.update(newAccount);

		Account existingAccount = _persistence.findByPrimaryKey(newAccount.getPrimaryKey());

		assertEquals(existingAccount.getAccountId(), newAccount.getAccountId());
		assertEquals(existingAccount.getCompanyId(), newAccount.getCompanyId());
		assertEquals(existingAccount.getUserId(), newAccount.getUserId());
		assertEquals(existingAccount.getUserName(), newAccount.getUserName());
		assertEquals(existingAccount.getCreateDate(), newAccount.getCreateDate());
		assertEquals(existingAccount.getModifiedDate(),
			newAccount.getModifiedDate());
		assertEquals(existingAccount.getParentAccountId(),
			newAccount.getParentAccountId());
		assertEquals(existingAccount.getName(), newAccount.getName());
		assertEquals(existingAccount.getLegalName(), newAccount.getLegalName());
		assertEquals(existingAccount.getLegalId(), newAccount.getLegalId());
		assertEquals(existingAccount.getLegalType(), newAccount.getLegalType());
		assertEquals(existingAccount.getSicCode(), newAccount.getSicCode());
		assertEquals(existingAccount.getTickerSymbol(),
			newAccount.getTickerSymbol());
		assertEquals(existingAccount.getIndustry(), newAccount.getIndustry());
		assertEquals(existingAccount.getType(), newAccount.getType());
		assertEquals(existingAccount.getSize(), newAccount.getSize());
	}

	public void testFindByPrimaryKeyExisting() throws Exception {
		Account newAccount = addAccount();

		Account existingAccount = _persistence.findByPrimaryKey(newAccount.getPrimaryKey());

		assertEquals(existingAccount, newAccount);
	}

	public void testFindByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		try {
			_persistence.findByPrimaryKey(pk);

			fail("Missing entity did not throw NoSuchAccountException");
		}
		catch (NoSuchAccountException nsee) {
		}
	}

	public void testFetchByPrimaryKeyExisting() throws Exception {
		Account newAccount = addAccount();

		Account existingAccount = _persistence.fetchByPrimaryKey(newAccount.getPrimaryKey());

		assertEquals(existingAccount, newAccount);
	}

	public void testFetchByPrimaryKeyMissing() throws Exception {
		long pk = nextLong();

		Account missingAccount = _persistence.fetchByPrimaryKey(pk);

		assertNull(missingAccount);
	}

	protected Account addAccount() throws Exception {
		long pk = nextLong();

		Account account = _persistence.create(pk);

		account.setCompanyId(nextLong());
		account.setUserId(nextLong());
		account.setUserName(randomString());
		account.setCreateDate(nextDate());
		account.setModifiedDate(nextDate());
		account.setParentAccountId(nextLong());
		account.setName(randomString());
		account.setLegalName(randomString());
		account.setLegalId(randomString());
		account.setLegalType(randomString());
		account.setSicCode(randomString());
		account.setTickerSymbol(randomString());
		account.setIndustry(randomString());
		account.setType(randomString());
		account.setSize(randomString());

		_persistence.update(account);

		return account;
	}

	private static final String _TX_IMPL = AccountPersistence.class.getName() +
		".transaction";
	private AccountPersistence _persistence;
}