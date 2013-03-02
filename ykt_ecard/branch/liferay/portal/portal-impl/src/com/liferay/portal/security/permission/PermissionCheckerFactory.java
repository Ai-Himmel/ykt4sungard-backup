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

package com.liferay.portal.security.permission;

import com.liferay.portal.model.User;
import com.liferay.portal.util.PropsValues;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.commons.pool.BasePoolableObjectFactory;
import org.apache.commons.pool.ObjectPool;
import org.apache.commons.pool.impl.StackObjectPool;

/**
 * <a href="PermissionCheckerFactory.java.html"><b><i>View Source</i></b></a>
 *
 * @author Charles May
 * @author Brian Wing Shun Chan
 *
 */
public class PermissionCheckerFactory {

	public static PermissionCheckerImpl create(User user, boolean checkGuest)
		throws Exception {

		if (PropsValues.COMMONS_POOL_ENABLED) {
			if (_log.isDebugEnabled()) {
				_log.debug(
					"Borrowing:\t" + _instance._pool.getNumIdle() + "\t" +
						_instance._pool.getNumActive());
			}
		}

		PermissionCheckerImpl permissionChecker = null;

		if (PropsValues.COMMONS_POOL_ENABLED) {
			permissionChecker =
				(PermissionCheckerImpl)_instance._pool.borrowObject();
		}
		else {
			permissionChecker = (PermissionCheckerImpl)Class.forName(
				PropsValues.PERMISSIONS_CHECKER).newInstance();
		}

		permissionChecker.init(user, checkGuest);

		return permissionChecker;
	}

	public static void recycle(PermissionCheckerImpl permissionChecker)
		throws Exception {

		if (PropsValues.COMMONS_POOL_ENABLED) {
			if (permissionChecker == null) {
				return;
			}

			if (_log.isDebugEnabled()) {
				_log.debug(
					"Recycling:\t" + _instance._pool.getNumIdle() + "\t" +
						_instance._pool.getNumActive());
			}

			_instance._pool.returnObject(permissionChecker);
		}
		else if (permissionChecker != null) {
			permissionChecker.recycle();
		}
	}

	private PermissionCheckerFactory() {
		_pool = new StackObjectPool(new Factory());
	}

	private static Log _log = LogFactory.getLog(PermissionCheckerFactory.class);

	private static PermissionCheckerFactory _instance =
		new PermissionCheckerFactory();

	private ObjectPool _pool;

	private class Factory extends BasePoolableObjectFactory {

		public Object makeObject() {
			try {
				return Class.forName(
					PropsValues.PERMISSIONS_CHECKER).newInstance();
			}
			catch (Exception e) {
				_log.error(e);

				return null;
			}
		}

		public void passivateObject(Object obj) {
			PermissionCheckerImpl permissionChecker =
				(PermissionCheckerImpl)obj;

			permissionChecker.recycle();
		}

	}

}