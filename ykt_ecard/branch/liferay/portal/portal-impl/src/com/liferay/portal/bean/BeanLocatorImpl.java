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

package com.liferay.portal.bean;

import com.liferay.portal.kernel.bean.BeanLocator;
import com.liferay.portal.kernel.bean.BeanLocatorException;
import com.liferay.portal.spring.util.SpringUtil;
import com.liferay.util.CollectionFactory;

import java.util.Set;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.springframework.context.ApplicationContext;

/**
 * <a href="BeanLocatorImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BeanLocatorImpl implements BeanLocator {

	public Object locate(String name) throws BeanLocatorException {
		return locate(name, _DEFAULT_WARN);
	}

	public Object locate(String name, boolean warn)
		throws BeanLocatorException {

		if (warn) {
			if (_beans.contains(name)) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"Cache the reference to " + name + " for better " +
							"performance");
				}
			}
		}

		ApplicationContext ctx = SpringUtil.getContext();

		if (_log.isDebugEnabled()) {
			_log.debug("Locating " + name);
		}

		Object obj = ctx.getBean(name);

		if (warn) {
			_beans.add(name);
		}

		return obj;
	}

	private static final boolean _DEFAULT_WARN = true;

	private static Log _log = LogFactory.getLog(BeanLocatorImpl.class);

	private Set _beans = CollectionFactory.getHashSet();

}