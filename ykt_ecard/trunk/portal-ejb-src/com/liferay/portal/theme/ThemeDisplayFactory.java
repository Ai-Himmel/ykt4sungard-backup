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

package com.liferay.portal.theme;

import org.apache.commons.pool.BasePoolableObjectFactory;
import org.apache.commons.pool.ObjectPool;
import org.apache.commons.pool.impl.StackObjectPool;

/**
 * <a href="ThemeDisplayFactory.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.38 $
 *
 */
public class ThemeDisplayFactory {

	public static ThemeDisplay create() throws Exception {
		return (ThemeDisplay)_instance._pool.borrowObject();
	}

	public static void recycle(ThemeDisplay themeDisplay) throws Exception {
		_instance._pool.returnObject(themeDisplay);
	}

	private ThemeDisplayFactory() {
		_pool = new StackObjectPool(new Factory());
	}

	private static ThemeDisplayFactory _instance = new ThemeDisplayFactory();

	private ObjectPool _pool;

	private class Factory extends BasePoolableObjectFactory {

		public Object makeObject() {
			return new ThemeDisplay();
		}

		public void passivateObject(Object obj) {
			ThemeDisplay themeDisplay = (ThemeDisplay)obj;

			themeDisplay.recycle();
		}

	}

}