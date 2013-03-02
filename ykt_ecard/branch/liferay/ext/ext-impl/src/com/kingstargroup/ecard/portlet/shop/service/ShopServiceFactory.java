package com.kingstargroup.ecard.portlet.shop.service;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

public class ShopServiceFactory {
	public static ShopService getService() {
		return _getFactory()._service;
	}

	public static ShopService getImpl() {
		if (_impl == null) {
			_impl = (ShopService)BeanLocatorUtil.locate(_IMPL);
		}

		return _impl;
	}

	public static ShopService getTxImpl() {
		if (_txImpl == null) {
			_txImpl = (ShopService)BeanLocatorUtil.locate(_TX_IMPL);
		}

		return _txImpl;
	}

	public void setService(ShopService service) {
		_service = service;
	}

	private static ShopServiceFactory _getFactory() {
		if (_factory == null) {
			_factory = (ShopServiceFactory)BeanLocatorUtil.locate(_FACTORY);
		}

		return _factory;
	}

	private static final String _FACTORY = ShopServiceFactory.class.getName();
	private static final String _IMPL = ShopService.class.getName() +
		".impl";
	private static final String _TX_IMPL = ShopService.class.getName() +
		".transaction";
	private static ShopServiceFactory _factory;
	private static ShopService _impl;
	private static ShopService _txImpl;
	private ShopService _service;
}
