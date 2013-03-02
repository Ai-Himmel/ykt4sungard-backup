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

package com.liferay.counter.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.bean.BeanLocatorUtil;

import java.util.List;

/**
 * <a href="CounterUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CounterUtil {

	public static List getNames() throws SystemException {
		return getPersistence().getNames();
	}

	public static long increment() throws SystemException {
		return getPersistence().increment();
	}

	public static long increment(String name) throws SystemException {
		return getPersistence().increment(name);
	}

	public static long increment(String name, int size)
		throws SystemException {

		return getPersistence().increment(name, size);
	}

	public static void rename(String oldName, String newName)
		throws SystemException {

		getPersistence().rename(oldName, newName);
	}

	public static void reset(String name) throws SystemException {
		getPersistence().reset(name);
	}

	public static void reset(String name, long size) throws SystemException {
		getPersistence().reset(name, size);
	}

	public static CounterPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(CounterPersistence persistence) {
		_persistence = persistence;
	}

	private static CounterUtil _getUtil() {
		if (_util == null) {
			_util = (CounterUtil)BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = CounterUtil.class.getName();

	private static CounterUtil _util;

	private CounterPersistence _persistence;

}