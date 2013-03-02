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

package com.kingstargroup.ecard.util;

import java.util.Iterator;
import java.util.Set;

import com.liferay.portal.kernel.util.MethodInvoker;
import com.liferay.portal.kernel.util.MethodWrapper;
import com.liferay.util.CollectionFactory;

/**
 * <a href="GlobalPool.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class GlobalPool {

	public static void clear() {
		_instance._clear();
	}

	public static void registerPool(String className) {
		_instance._registerPool(className);
	}

	private GlobalPool() {
		_registeredPools = CollectionFactory.getSyncHashSet();
	}

	private void _clear() {
		Iterator itr = _registeredPools.iterator();

		while (itr.hasNext()) {
			String className = (String)itr.next();

			MethodWrapper methodWrapper = new MethodWrapper(
				className, "clear", new Object[0]);

			try {
				MethodInvoker.invoke(methodWrapper, false);
			}
			catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

	private void _registerPool(String className) {
		_registeredPools.add(className);
	}

	private static GlobalPool _instance = new GlobalPool();

	private Set _registeredPools;

}