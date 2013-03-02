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

package com.liferay.portlet.mail.util.multiaccount;

import com.liferay.portal.model.User;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.ActionRequestImpl;
import com.liferay.portlet.mail.AccountNotFoundException;
import com.liferay.portlet.mail.MailAccountsException;
import com.liferay.util.Validator;

import java.util.ArrayList;
import java.util.Collection;

import javax.portlet.ActionRequest;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * MailAccounts handles all the mail accounts of a user
 *
 * <a href="MailAccounts.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Jorge Ferrer
 * @version $Revision: 1.2 $
 *
 */
public class MailAccounts {

	public static MailAccount getCurrentAccount(HttpServletRequest req)
		throws MailAccountsException {

		HttpSession ses = req.getSession();

		String accountName = req.getParameter("mail_account");

		if (Validator.isNull(accountName)) {
			return _previousAccount(req);
		}

		MailAccount account = _getAccount(req, accountName);

		_log.info("Current account " + account);

		ses.setAttribute(WebKeys.MAIL_CURRENT_ACCOUNT, account);

		return account;
	}

	public static MailAccount getCurrentAccount(ActionRequest req)
		throws MailAccountsException {

		ActionRequestImpl reqImpl = (ActionRequestImpl)req;

		return getCurrentAccount(reqImpl.getHttpServletRequest());
	}

	public static Collection findAllAccounts(User user, String password) {
		Collection cachedAccounts =
			MailCache.getUserAccounts(user.getUserId());

		if (cachedAccounts != null) {
			return cachedAccounts;
		}

		try {
			AccountFinder accountFinder =
				AccountFinderLocator.getAccountFinderInstance();

			Collection accounts = accountFinder.findAllAccounts(user, password);

			MailCache.putUserAcounts(user.getUserId(), accounts);

			return accounts;
		}
		catch (MailAccountsException mae) {
			_log.error(
				"Error trying to get all accounts for user " + user.getUserId(),
				mae);

			return new ArrayList();
		}
	}

	public static String getDefaultAccountName() {
		AccountFinder accountFinder =
			AccountFinderLocator.getAccountFinderInstance();

		return accountFinder.getDefaultAccountName();
	}

	public static MailAccount findAccount(
		User user, String password, String accountName) {

		try {
			AccountFinder accountFinder =
				AccountFinderLocator.getAccountFinderInstance();

			return accountFinder.findAccount(user, password, accountName);
		}
		catch (Exception e) {
			_log.error(
				"Error obtaining the account for user " + user.getUserId() +
					" with prefix " + accountName +
						". The default will be used. ",
				e);

			return new MailAccount(
				"Default", user.getUserId(), password, user.getEmailAddress());
		}
	}

	private static MailAccount _getAccount(
			HttpServletRequest req, String accountName)
		throws MailAccountsException {

		MailAccount account = null;

		AccountFinder accountFinder =
			AccountFinderLocator.getAccountFinderInstance();

		User user = null;
		String password = null;

		try {
			user = PortalUtil.getUser(req);
			password = PortalUtil.getUserPassword(req);

			account = accountFinder.findAccount(user, password, accountName);
		}
		catch (AccountNotFoundException anfe) {
			try {
				account = accountFinder.findAccount(
					user, password, accountFinder.getDefaultAccountName());
			}
			catch (Exception e1) {
				throw new MailAccountsException(
					"Could not read the default account", e1);
			}
		}
		catch (Exception e2) {
			throw new MailAccountsException(
				"Could not read the account " + accountName, e2);
		}

		// Call find all accounts to cache the list of accounts associated with
		// a user. If this method is not called, then when a user logs off,
		// there will not be any accounts associated with that user, and so it
		// becomes impossible to close the stores associated with the accounts
		// that are associated with that user. Closing the stores dramatically
		// improves performance because it closes all associated JavaMail
		// connections to the IMAP server.

		findAllAccounts(user, password);

		return account;
	}

	private static MailAccount _previousAccount(HttpServletRequest req)
		throws MailAccountsException {

		HttpSession ses = req.getSession();

		MailAccount previousAccount =
			(MailAccount)ses.getAttribute(WebKeys.MAIL_CURRENT_ACCOUNT);

		if (previousAccount == null) {
			MailAccount defaultAccount =
				_getAccount(req, getDefaultAccountName());

			ses.setAttribute(WebKeys.MAIL_CURRENT_ACCOUNT, defaultAccount);

			previousAccount = defaultAccount;
		}

		return previousAccount;
	}

	private static final Log _log = LogFactory.getLog(MailAccounts.class);

}