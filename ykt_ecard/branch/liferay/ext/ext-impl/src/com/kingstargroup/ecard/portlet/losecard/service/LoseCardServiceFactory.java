package com.kingstargroup.ecard.portlet.losecard.service;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

public class LoseCardServiceFactory {
	public static LoseCardService getService() {
		return _getFactory()._service;
	}

	public static LoseCardService getImpl() {
		if (_impl == null) {
			_impl = (LoseCardService)BeanLocatorUtil.locate(_IMPL);
		}

		return _impl;
	}

	public static LoseCardService getTxImpl() {
		if (_txImpl == null) {
			_txImpl = (LoseCardService)BeanLocatorUtil.locate(_TX_IMPL);
		}

		return _txImpl;
	}

	public void setService(LoseCardService service) {
		_service = service;
	}

	private static LoseCardServiceFactory _getFactory() {
		if (_factory == null) {
			_factory = (LoseCardServiceFactory)BeanLocatorUtil.locate(_FACTORY);
		}

		return _factory;
	}

	private static final String _FACTORY = LoseCardServiceFactory.class.getName();
	private static final String _IMPL = LoseCardService.class.getName() +
		".impl";
	private static final String _TX_IMPL = LoseCardService.class.getName() +
		".transaction";
	private static LoseCardServiceFactory _factory;
	private static LoseCardService _impl;
	private static LoseCardService _txImpl;
	private LoseCardService _service;
}
