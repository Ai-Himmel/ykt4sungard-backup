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

package com.liferay.portlet.mail.util.multiaccount;

import com.liferay.portal.model.User;
import com.liferay.portlet.mail.MailAccountsException;

import java.util.ArrayList;
import java.util.Collection;

/**
 * <a href="SingleAccountFinder.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class SingleAccountFinder implements AccountFinder {

	public String getDefaultAccountName() {
		return _IGNORE;
	}

	public String getMailUserId(User user) {
		return String.valueOf(user.getUserId());
	}

	public MailAccount findAccount(
			User user, String password, String accountName)
		throws MailAccountsException {

		return new MailAccount(
			accountName, getMailUserId(user), password, user.getEmailAddress());
	}

	public Collection findAllAccounts(User user, String password)
		throws MailAccountsException {

		Collection result = new ArrayList();

		result.add(findAccount(user, password, getDefaultAccountName()));

		return result;
	}

	private static final String _IGNORE = ".IGNORE";

}