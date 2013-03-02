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

package com.liferay.portlet.shopping.service;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

/**
 * <a href="ShoppingCouponServiceFactory.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is responsible for the lookup of the implementation for
 * <code>com.liferay.portlet.shopping.service.ShoppingCouponService</code>.
 * Spring manages the lookup and lifecycle of the beans. This means you can
 * modify the Spring configuration files to return a different implementation or
 * to inject additional behavior.
 * </p>
 *
 * <p>
 * See the <code>spring.configs</code> property in portal.properties for
 * additional information on how to customize the Spring XML files.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.ShoppingCouponService
 * @see com.liferay.portlet.shopping.service.ShoppingCouponServiceUtil
 *
 */
public class ShoppingCouponServiceFactory {
	public static ShoppingCouponService getService() {
		return _getFactory()._service;
	}

	public static ShoppingCouponService getImpl() {
		if (_impl == null) {
			_impl = (ShoppingCouponService)BeanLocatorUtil.locate(_IMPL);
		}

		return _impl;
	}

	public static ShoppingCouponService getTxImpl() {
		if (_txImpl == null) {
			_txImpl = (ShoppingCouponService)BeanLocatorUtil.locate(_TX_IMPL);
		}

		return _txImpl;
	}

	public void setService(ShoppingCouponService service) {
		_service = service;
	}

	private static ShoppingCouponServiceFactory _getFactory() {
		if (_factory == null) {
			_factory = (ShoppingCouponServiceFactory)BeanLocatorUtil.locate(_FACTORY);
		}

		return _factory;
	}

	private static final String _FACTORY = ShoppingCouponServiceFactory.class.getName();
	private static final String _IMPL = ShoppingCouponService.class.getName() +
		".impl";
	private static final String _TX_IMPL = ShoppingCouponService.class.getName() +
		".transaction";
	private static ShoppingCouponServiceFactory _factory;
	private static ShoppingCouponService _impl;
	private static ShoppingCouponService _txImpl;
	private ShoppingCouponService _service;
}