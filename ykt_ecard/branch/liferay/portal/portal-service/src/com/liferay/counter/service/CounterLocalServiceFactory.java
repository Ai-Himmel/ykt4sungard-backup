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

package com.liferay.counter.service;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

/**
 * <a href="CounterLocalServiceFactory.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CounterLocalServiceFactory {

	public static CounterLocalService getService() {
		return _getFactory()._service;
	}

	public static CounterLocalService getImpl() {
		if (_impl == null) {
			_impl = (CounterLocalService)BeanLocatorUtil.locate(_IMPL);
		}

		return _impl;
	}

	public static CounterLocalService getTxImpl() {
		if (_txImpl == null) {
			_txImpl = (CounterLocalService)BeanLocatorUtil.locate(_TX_IMPL);
		}

		return _txImpl;
	}

	public void setService(CounterLocalService service) {
		_service = service;
	}

	private static CounterLocalServiceFactory _getFactory() {
		if (_factory == null) {
			_factory = (CounterLocalServiceFactory)BeanLocatorUtil.locate(
				_FACTORY);
		}

		return _factory;
	}

	private static final String _FACTORY =
		CounterLocalServiceFactory.class.getName();

	private static final String _IMPL =
		CounterLocalService.class.getName() + ".impl";

	private static final String _TX_IMPL =
		CounterLocalService.class.getName() + ".transaction";

	private static CounterLocalServiceFactory _factory;
	private static CounterLocalService _impl;
	private static CounterLocalService _txImpl;

	private CounterLocalService _service;

}