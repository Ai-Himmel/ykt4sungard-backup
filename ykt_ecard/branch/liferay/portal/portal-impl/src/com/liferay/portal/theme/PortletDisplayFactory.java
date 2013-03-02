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

package com.liferay.portal.theme;

import com.liferay.portal.util.PropsValues;

import org.apache.commons.pool.BasePoolableObjectFactory;
import org.apache.commons.pool.ObjectPool;
import org.apache.commons.pool.impl.StackObjectPool;

/**
 * <a href="PortletDisplayFactory.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletDisplayFactory {

	public static PortletDisplay create() throws Exception {
		if (PropsValues.COMMONS_POOL_ENABLED) {
			return (PortletDisplay)_instance._pool.borrowObject();
		}
		else {
			return new PortletDisplay();
		}
	}

	public static void recycle(PortletDisplay portletDisplay) throws Exception {
		if (PropsValues.COMMONS_POOL_ENABLED) {
			_instance._pool.returnObject(portletDisplay);
		}
		else if (portletDisplay != null) {
			portletDisplay.recycle();
		}
	}

	private PortletDisplayFactory() {
		_pool = new StackObjectPool(new Factory());
	}

	private static PortletDisplayFactory _instance =
		new PortletDisplayFactory();

	private ObjectPool _pool;

	private class Factory extends BasePoolableObjectFactory {

		public Object makeObject() {
			return new PortletDisplay();
		}

		public void passivateObject(Object obj) {
			PortletDisplay portletDisplay = (PortletDisplay)obj;

			portletDisplay.recycle();
		}

	}

}