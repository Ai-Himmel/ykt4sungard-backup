package com.kingstargroup.ecard.portlet.card.service;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

public class CardServiceFactory {
	
	public static CardService getService() {
		return _getFactory()._service;
	}

	public static CardService getImpl() {
		if (_impl == null) {
			_impl = (CardService)BeanLocatorUtil.locate(_IMPL);
		}

		return _impl;
	}

	public static CardService getTxImpl() {
		if (_txImpl == null) {
			_txImpl = (CardService)BeanLocatorUtil.locate(_TX_IMPL);
		}

		return _txImpl;
	}

	public void setService(CardService service) {
		_service = service;
	}

	private static CardServiceFactory _getFactory() {
		if (_factory == null) {
			_factory = (CardServiceFactory)BeanLocatorUtil.locate(_FACTORY);
		}

		return _factory;
	}

	private static final String _FACTORY = CardServiceFactory.class.getName();
	private static final String _IMPL = CardService.class.getName() +
		".impl";
	private static final String _TX_IMPL = CardService.class.getName() +
		".transaction";
	private static CardServiceFactory _factory;
	private static CardService _impl;
	private static CardService _txImpl;
	private CardService _service;

}
