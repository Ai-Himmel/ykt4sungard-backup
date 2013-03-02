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

import java.io.Serializable;

import java.util.Map;

/**
 * <a href="MultiVMPool.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Michael Young
 *
 */
public interface MultiVMPool {

	public void clear();

	public void clear(String name);

	public void clearGroup(
		Map groups, String groupKey, PortalCache portalCache);

	public Object get(String name, String key);

	public Object get(PortalCache portalCache, String key);

	public PortalCache getCache(String name);

	public void put(String name, String key, Object obj);

	public void put(PortalCache portalCache, String key, Object obj);

	public void put(
		PortalCache portalCache, String key, Map groups, String groupKey,
		Object obj);

	public void put(String name, String key, Serializable obj);

	public void put(PortalCache portalCache, String key, Serializable obj);

	public void put(
		PortalCache portalCache, String key, Map groups, String groupKey,
		Serializable obj);

	public void remove(String name, String key);

	public void remove(PortalCache portalCache, String key);

	public void updateGroup(Map groups, String groupKey, String key);

}