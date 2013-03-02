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

import com.liferay.portal.util.WebKeys;
import com.liferay.util.CollectionFactory;

import java.util.Collection;
import java.util.Iterator;
import java.util.Map;

import javax.mail.MessagingException;
import javax.mail.Store;

import javax.servlet.http.HttpSession;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="MailCache.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class MailCache {

	public static Store getStore(HttpSession ses, String accountPrefix) {
		return (Store)ses.getAttribute(WebKeys.MAIL_STORE + accountPrefix);
	}

	public static void putStore(
		HttpSession ses, String accountPrefix, Store store) {

		ses.setAttribute(WebKeys.MAIL_STORE + accountPrefix, store);
	}

	public static void removeStore(HttpSession ses, String accountPrefix) {
		ses.removeAttribute(WebKeys.MAIL_STORE + accountPrefix);
	}

	public static Collection getUserAccounts(long userId) {
		return (Collection)_accountsPool.get(new Long(userId));
	}

	public static void putUserAccounts(long userId, Collection accounts) {
		_accountsPool.put(new Long(userId), accounts);
	}

	public static void removeUserAccounts(long userId) {
		_accountsPool.remove(new Long(userId));
	}

	public static void clearCache(HttpSession ses) throws MessagingException {
		Long userIdObj = (Long)ses.getAttribute(WebKeys.USER_ID);

		if (_log.isDebugEnabled()) {
			_log.debug("Clearing the mail cache for user " + userIdObj);
		}

		Collection accounts = getUserAccounts(userIdObj.longValue());

		if (accounts != null) {
			if (_log.isDebugEnabled()) {
				_log.debug(
					"User has " + accounts.size() + " accounts that might " +
						"need to be closed");
			}

			Iterator itr = accounts.iterator();

			while (itr.hasNext()) {
				MailAccount account = (MailAccount)itr.next();

				String accountPrefix = account.getName();

				Store store = getStore(ses, accountPrefix);

				if (store != null) {
					store.close();
				}

				removeStore(ses, accountPrefix);
			}

			removeUserAccounts(userIdObj.longValue());
		}
	}

	private static Log _log = LogFactory.getLog(MailCache.class);

	private static Map _accountsPool = CollectionFactory.getSyncHashMap();

}