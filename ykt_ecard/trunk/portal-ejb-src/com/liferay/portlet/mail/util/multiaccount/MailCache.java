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

import com.liferay.portlet.mail.util.MailUtil;
import com.liferay.util.SimpleCachePool;

import java.util.Collection;
import java.util.Iterator;

import javax.mail.Store;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="MailCache.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Jorge Ferrer
 * @version $Revision: 1.2 $
 *
 */
public class MailCache {

	// Stores

	public static Store getStore(String userId, String accountPrefix) {
		String storeId = getStoreId(userId, accountPrefix);

		_log.debug("Get store " + storeId);

		return (Store)SimpleCachePool.get(storeId);
	}

	public static void removeStore(String userId, String accountPrefix) {
		String storeId = getStoreId(userId, accountPrefix);

		_log.debug("Remove store " + storeId);

		SimpleCachePool.remove(storeId);
	}

	public static void putStore(
		String userId, String accountPrefix, Store store) {

		String storeId = getStoreId(userId, accountPrefix);

		_log.debug("Put store " + storeId);

		SimpleCachePool.put(storeId, store);
	}

	private static String getStoreId(String userId, String accountPrefix) {
		return MailUtil.SCP_STORE_ID + userId + accountPrefix;
	}

	// Clean up

	public static void clearCache(String userId) {
		_log.debug("Clearing the mail cache for user " + userId);

		Collection accounts = getUserAccounts(userId);

		if (accounts != null) {
			_log.debug("User has " + accounts.size() + " cached accounts");

			Iterator itr = accounts.iterator();

			while (itr.hasNext()) {
				MailAccount account = (MailAccount)itr.next();

				removeAndCloseStore(userId, account.getName());
			}

			removeUserAccounts(userId);
		}
	}

	private static void removeAndCloseStore(
		String userId, String accountPrefix) {

		Store store = getStore(userId, accountPrefix);

		try {
			if (store != null) {
				store.close();
			}
		}
		catch (Exception e) {
			_log.error(e);
		}

		removeStore(userId, accountPrefix);

		SimpleCachePool.remove(getFolderPoolId(userId));
	}

	// Folders

	public static String getFolderPoolId(String userId) {
		return MailUtil.SCP_FOLDER_POOL_ID + userId;
	}

	public static String getFolderCacheId(String folderName, Store store) {
		return folderName + store.hashCode();
	}

	// Mail accounts

	public static Collection getUserAccounts(String userId) {
		String userAccountsId = getUserAccountsId(userId);

		_log.debug("Get user accounts " + userId);

		return (Collection)SimpleCachePool.get(userAccountsId);
	}

	public static void putUserAcounts(String userId, Collection accounts) {
		String userAccountsId = getUserAccountsId(userId);

		_log.debug("Put all user accounts " + userId);

		SimpleCachePool.put(userAccountsId, accounts);
	}

	private static void removeUserAccounts(String userId) {
		String userAccountsId = getUserAccountsId(userId);

		_log.debug("Remove user accounts " + userId);

		SimpleCachePool.remove(userAccountsId);
	}

	private static String getUserAccountsId(String userId) {
		return MailUtil.SCP_STORE_ID + ".MAIL_ACCOUNTS." + userId;
	}

	private static final Log _log = LogFactory.getLog(MailCache.class);

}