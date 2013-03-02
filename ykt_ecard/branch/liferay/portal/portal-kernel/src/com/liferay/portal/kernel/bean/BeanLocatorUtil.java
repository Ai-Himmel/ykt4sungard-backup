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

package com.liferay.portal.kernel.bean;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.util.PortalClassLoaderUtil;

/**
 * <a href="BeanLocatorUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BeanLocatorUtil {

	public static Object locate(String name) throws BeanLocatorException {
		if (_beanLocator == null) {
			_log.error("BeanLocator is null");

			throw new BeanLocatorException("BeanLocator has not been set");
		}
		else {
			ClassLoader contextClassLoader =
				Thread.currentThread().getContextClassLoader();

			try {
				Thread.currentThread().setContextClassLoader(
					PortalClassLoaderUtil.getClassLoader());

				return _beanLocator.locate(name);
			}
			finally {
				Thread.currentThread().setContextClassLoader(
					contextClassLoader);
			}
		}
	}

	public static Object locate(String name, boolean warn)
		throws BeanLocatorException {

		if (_beanLocator == null) {
			_log.error("BeanLocator is null");

			throw new BeanLocatorException("BeanLocator has not been set");
		}
		else {
			ClassLoader contextClassLoader =
				Thread.currentThread().getContextClassLoader();

			try {
				Thread.currentThread().setContextClassLoader(
					PortalClassLoaderUtil.getClassLoader());

				return _beanLocator.locate(name, warn);
			}
			finally {
				Thread.currentThread().setContextClassLoader(
					contextClassLoader);
			}
		}
	}

	public static void setBeanLocator(BeanLocator beanLocator) {
		if (_log.isDebugEnabled()) {
			_log.debug("Setting BeanLocator " + beanLocator.hashCode());
		}

		_beanLocator = beanLocator;
	}

	private static Log _log = LogFactoryUtil.getLog(BeanLocatorUtil.class);

	private static BeanLocator _beanLocator;

}