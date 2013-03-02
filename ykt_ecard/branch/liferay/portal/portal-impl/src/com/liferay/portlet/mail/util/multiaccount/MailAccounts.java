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

import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.User;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.mail.AccountNotFoundException;
import com.liferay.portlet.mail.MailAccountsException;

import java.util.ArrayList;
import java.util.Collection;

import javax.portlet.ActionRequest;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="MailAccounts.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * Handles all the mail accounts that belong to the current user.
 * </p>
 *
 * @author Jorge Ferrer
 *
 */
public class MailAccounts {

	public static final String ACCOUNT_FINDER_PASSWORD = PropsUtil.get(
		PropsUtil.MAIL_ACCOUNT_FINDER_PASSWORD);

	public static MailAccount getCurrentAccount(HttpServletRequest req)
		throws MailAccountsException {

		HttpSession ses = req.getSession();

		MailAccount previousAccount =
			(MailAccount)ses.getAttribute(WebKeys.MAIL_CURRENT_ACCOUNT);

		if (previousAccount == null) {
			MailAccount defaultAccount =
				_getAccount(req, _getDefaultAccountName());

			ses.setAttribute(WebKeys.MAIL_CURRENT_ACCOUNT, defaultAccount);

			previousAccount = defaultAccount;
		}

		return previousAccount;
	}

	public static MailAccount getCurrentAccount(ActionRequest req)
		throws MailAccountsException {

		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);

		return getCurrentAccount(httpReq);
	}

	public static void setAccount(HttpServletRequest req, String accountName)
		throws MailAccountsException {

		HttpSession ses = req.getSession();

		MailAccount account = _getAccount(req, accountName);

		if (_log.isInfoEnabled()) {
			_log.info("Switched to account " + account);
		}

		ses.setAttribute(WebKeys.MAIL_CURRENT_ACCOUNT, account);
	}

	private static MailAccount _getAccount(
			HttpServletRequest req, String accountName)
		throws MailAccountsException {

		HttpSession ses = req.getSession();

		MailAccount account = null;

		AccountFinder accountFinder =
			AccountFinderLocator.getAccountFinderInstance();

		User user = null;
		String password = null;

		try {
			user = PortalUtil.getUser(req);

			if (Validator.isNull(ACCOUNT_FINDER_PASSWORD)) {
				password = PortalUtil.getUserPassword(ses);

				if (password == null) {
					password = user.getPassword();
				}
			}
			else {
				password = ACCOUNT_FINDER_PASSWORD;
			}

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

		_findAllAccounts(user, password);

		return account;
	}

	private static String _getDefaultAccountName() {
		AccountFinder accountFinder =
			AccountFinderLocator.getAccountFinderInstance();

		return accountFinder.getDefaultAccountName();
	}

	private static Collection _findAllAccounts(User user, String password) {
		Collection cachedAccounts = MailCache.getUserAccounts(user.getUserId());

		if (cachedAccounts != null) {
			return cachedAccounts;
		}

		try {
			AccountFinder accountFinder =
				AccountFinderLocator.getAccountFinderInstance();

			Collection accounts = accountFinder.findAllAccounts(user, password);

			MailCache.putUserAccounts(user.getUserId(), accounts);

			return accounts;
		}
		catch (MailAccountsException mae) {
			_log.error(
				"Error trying to get all accounts for user " + user.getUserId(),
				mae);

			return new ArrayList();
		}
	}

	private static Log _log = LogFactory.getLog(MailAccounts.class);

}