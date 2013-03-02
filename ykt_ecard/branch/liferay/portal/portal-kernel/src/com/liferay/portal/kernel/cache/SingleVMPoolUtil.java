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

package com.liferay.portal.kernel.cache;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

import java.io.Serializable;

/**
 * <a href="SingleVMPoolUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Michael Young
 *
 */
public class SingleVMPoolUtil {

	public static void clear() {
		getSingleVMPool().clear();
	}

	public static void clear(String name) {
		getSingleVMPool().clear(name);
	}

	public static Object get(String name, String key) {
		return getSingleVMPool().get(name, key);
	}

	public static Object get(PortalCache portalCache, String key) {
		return getSingleVMPool().get(portalCache, key);
	}

	public static PortalCache getCache(String name) {
		return getSingleVMPool().getCache(name);
	}

	public static SingleVMPool getSingleVMPool() {
		return _getUtil()._singleVMPool;
	}

	public static void put(String name, String key, Object obj) {
		getSingleVMPool().put(name, key, obj);
	}

	public static void put(PortalCache portalCache, String key, Object obj) {
		getSingleVMPool().put(portalCache, key, obj);
	}

	public static void put(String name, String key, Serializable obj) {
		getSingleVMPool().put(name, key, obj);
	}

	public static void put(
		PortalCache portalCache, String key, Serializable obj) {

		getSingleVMPool().put(portalCache, key, obj);
	}

	public static void remove(String name, String key) {
		getSingleVMPool().remove(name, key);
	}

	public static void remove(PortalCache portalCache, String key) {
		getSingleVMPool().remove(portalCache, key);
	}

	public void setSingleVMPool(SingleVMPool singleVMPool) {
		_singleVMPool = singleVMPool;
	}

	private static SingleVMPoolUtil _getUtil() {
		if (_util == null) {
			_util = (SingleVMPoolUtil)BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = SingleVMPoolUtil.class.getName();

	private static SingleVMPoolUtil _util;

	private SingleVMPool _singleVMPool;

}