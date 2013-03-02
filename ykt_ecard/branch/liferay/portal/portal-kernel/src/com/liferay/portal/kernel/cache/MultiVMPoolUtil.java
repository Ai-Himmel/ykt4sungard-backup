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

import java.util.Map;

/**
 * <a href="MultiVMPoolUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Michael Young
 *
 */
public class MultiVMPoolUtil {

	public static void clear() {
		getMultiVMPool().clear();
	}

	public static void clear(String name) {
		getMultiVMPool().clear(name);
	}

	public static void clearGroup(
		Map groups, String groupKey, PortalCache portalCache) {

		getMultiVMPool().clearGroup(groups, groupKey, portalCache);
	}

	public static Object get(String name, String key) {
		return getMultiVMPool().get(name, key);
	}

	public static Object get(PortalCache portalCache, String key) {
		return getMultiVMPool().get(portalCache, key);
	}

	public static MultiVMPool getMultiVMPool() {
		return _getUtil()._multiVMPool;
	}

	public static PortalCache getCache(String name) {
		return getMultiVMPool().getCache(name);
	}

	public static void put(String name, String key, Object obj) {
		getMultiVMPool().put(name, key, obj);
	}

	public static void put(PortalCache portalCache, String key, Object obj) {
		getMultiVMPool().put(portalCache, key, obj);
	}

	public static void put(
		PortalCache portalCache, String key, Map groups, String groupKey,
		Object obj) {

		getMultiVMPool().put(portalCache, key, groups, groupKey, obj);
	}

	public static void put(String name, String key, Serializable obj) {
		getMultiVMPool().put(name, key, obj);
	}

	public static void put(
		PortalCache portalCache, String key, Serializable obj) {

		getMultiVMPool().put(portalCache, key, obj);
	}

	public static void put(
		PortalCache portalCache, String key, Map groups, String groupKey,
		Serializable obj) {

		getMultiVMPool().put(portalCache, key, groups, groupKey, obj);
	}

	public static void remove(String name, String key) {
		getMultiVMPool().remove(name, key);
	}

	public static void remove(PortalCache portalCache, String key) {
		getMultiVMPool().remove(portalCache, key);
	}

	public static void updateGroup(Map groups, String groupKey, String key) {
		getMultiVMPool().updateGroup(groups, groupKey, key);
	}

	public void setMultiVMPool(MultiVMPool multiVMPool) {
		_multiVMPool = multiVMPool;
	}

	private static MultiVMPoolUtil _getUtil() {
		if (_util == null) {
			_util = (MultiVMPoolUtil)BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = MultiVMPoolUtil.class.getName();

	private static MultiVMPoolUtil _util;

	private MultiVMPool _multiVMPool;

}