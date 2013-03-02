package com.kingstargroup.ecard.portlet.cardlist.service;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

public class CardListServiceFactory {
	
	public static CardListService getService() {
		return _getFactory()._service;
	}

	public static CardListService getImpl() {
		if (_impl == null) {
			_impl = (CardListService)BeanLocatorUtil.locate(_IMPL);
		}

		return _impl;
	}

	public static CardListService getTxImpl() {
		if (_txImpl == null) {
			_txImpl = (CardListService)BeanLocatorUtil.locate(_TX_IMPL);
		}

		return _txImpl;
	}

	public void setService(CardListService service) {
		_service = service;
	}

	private static CardListServiceFactory _getFactory() {
		if (_factory == null) {
			_factory = (CardListServiceFactory)BeanLocatorUtil.locate(_FACTORY);
		}

		return _factory;
	}

	private static final String _FACTORY = CardListServiceFactory.class.getName();
	private static final String _IMPL = CardListService.class.getName() +
		".impl";
	private static final String _TX_IMPL = CardListService.class.getName() +
		".transaction";
	private static CardListServiceFactory _factory;
	private static CardListService _impl;
	private static CardListService _txImpl;
	private CardListService _service;

}
