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

package com.liferay.mail.service.persistence;

import com.liferay.mail.NoSuchCyrusVirtualException;
import com.liferay.mail.model.CyrusVirtual;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;

import java.util.List;

/**
 * <a href="CyrusVirtualUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CyrusVirtualUtil {

	public static void remove(String emailAddress)
		throws NoSuchCyrusVirtualException, SystemException {

		getPersistence().remove(emailAddress);
	}

	public static void update(CyrusVirtual user) throws SystemException {
		getPersistence().update(user);
	}

	public static CyrusVirtual findByPrimaryKey(String emailAddress)
		throws NoSuchCyrusVirtualException, SystemException {

		return getPersistence().findByPrimaryKey(emailAddress);
	}

	public static List findByUserId(long userId) throws SystemException {
		return getPersistence().findByUserId(userId);
	}

	public static void removeByUserId(long userId) throws SystemException {
		getPersistence().removeByUserId(userId);
	}

	public static CyrusVirtualPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(CyrusVirtualPersistence persistence) {
		_persistence = persistence;
	}

	private static CyrusVirtualUtil _getUtil() {
		if (_util == null) {
			_util = (CyrusVirtualUtil)BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = CyrusVirtualUtil.class.getName();

	private static CyrusVirtualUtil _util;

	private CyrusVirtualPersistence _persistence;

}