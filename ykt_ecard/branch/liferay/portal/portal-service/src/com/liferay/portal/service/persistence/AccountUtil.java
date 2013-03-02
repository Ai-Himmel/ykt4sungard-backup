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

/**
 * <a href="AccountUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class AccountUtil {
	public static com.liferay.portal.model.Account create(long accountId) {
		return getPersistence().create(accountId);
	}

	public static com.liferay.portal.model.Account remove(long accountId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAccountException {
		return getPersistence().remove(accountId);
	}

	public static com.liferay.portal.model.Account remove(
		com.liferay.portal.model.Account account)
		throws com.liferay.portal.SystemException {
		return getPersistence().remove(account);
	}

	public static com.liferay.portal.model.Account update(
		com.liferay.portal.model.Account account)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(account);
	}

	public static com.liferay.portal.model.Account update(
		com.liferay.portal.model.Account account, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().update(account, merge);
	}

	public static com.liferay.portal.model.Account updateImpl(
		com.liferay.portal.model.Account account, boolean merge)
		throws com.liferay.portal.SystemException {
		return getPersistence().updateImpl(account, merge);
	}

	public static com.liferay.portal.model.Account findByPrimaryKey(
		long accountId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.NoSuchAccountException {
		return getPersistence().findByPrimaryKey(accountId);
	}

	public static com.liferay.portal.model.Account fetchByPrimaryKey(
		long accountId) throws com.liferay.portal.SystemException {
		return getPersistence().fetchByPrimaryKey(accountId);
	}

	public static java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		return getPersistence().findWithDynamicQuery(queryInitializer);
	}

	public static java.util.List findWithDynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		return getPersistence().findWithDynamicQuery(queryInitializer, begin,
			end);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll();
	}

	public static java.util.List findAll(int begin, int end)
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll(begin, end);
	}

	public static java.util.List findAll(int begin, int end,
		com.liferay.portal.kernel.util.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		return getPersistence().findAll(begin, end, obc);
	}

	public static void removeAll() throws com.liferay.portal.SystemException {
		getPersistence().removeAll();
	}

	public static int countAll() throws com.liferay.portal.SystemException {
		return getPersistence().countAll();
	}

	public static AccountPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(AccountPersistence persistence) {
		_persistence = persistence;
	}

	private static AccountUtil _getUtil() {
		if (_util == null) {
			_util = (AccountUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = AccountUtil.class.getName();
	private static AccountUtil _util;
	private AccountPersistence _persistence;
}