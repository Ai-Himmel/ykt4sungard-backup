/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portal.service.impl;

import com.liferay.portal.NoSuchAccountException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Account;
import com.liferay.portal.model.User;
import com.liferay.portal.service.persistence.AccountUtil;
import com.liferay.portal.service.spring.AccountLocalService;
import com.liferay.portal.service.spring.UserLocalServiceUtil;

import java.util.Date;

/**
 * <a href="AccountLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.1 $
 *
 */
public class AccountLocalServiceImpl implements AccountLocalService {

	// Business methods

	public Account addCompany(
			String companyId, String name, String type, String size,
			String emailAddress)
		throws PortalException, SystemException {

		User user = UserLocalServiceUtil.getDefaultUser(companyId);

		String accountId = companyId;

		Account account = null;

		try {
			account = AccountUtil.findByPrimaryKey(accountId);
		}
		catch (NoSuchAccountException nsae) {
			account = AccountUtil.create(accountId);

			Date now = new Date();

			account.setCompanyId(user.getCompanyId());
			account.setUserId(user.getUserId());
			account.setUserName(user.getFullName());
			account.setCreateDate(now);
			account.setModifiedDate(now);
			account.setParentAccountId(Account.DEFAULT_PARENT_ACCOUNT_ID);
			account.setName(name);
			account.setType(type);
			account.setSize(size);
			account.setEmailAddress1(emailAddress);

			AccountUtil.update(account);
		}

		return account;
	}

}