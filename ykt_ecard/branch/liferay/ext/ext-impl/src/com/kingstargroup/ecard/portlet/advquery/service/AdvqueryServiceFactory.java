package com.kingstargroup.ecard.portlet.advquery.service;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

public class AdvqueryServiceFactory {
	public static AdvqueryService getService() {
		return _getFactory()._service;
	}

	public static AdvqueryService getImpl() {
		if (_impl == null) {
			_impl = (AdvqueryService)BeanLocatorUtil.locate(_IMPL);
		}

		return _impl;
	}

	public static AdvqueryService getTxImpl() {
		if (_txImpl == null) {
			_txImpl = (AdvqueryService)BeanLocatorUtil.locate(_TX_IMPL);
		}

		return _txImpl;
	}

	public void setService(AdvqueryService service) {
		_service = service;
	}

	private static AdvqueryServiceFactory _getFactory() {
		if (_factory == null) {
			_factory = (AdvqueryServiceFactory)BeanLocatorUtil.locate(_FACTORY);
		}

		return _factory;
	}

	private static final String _FACTORY = AdvqueryServiceFactory.class.getName();
	private static final String _IMPL = AdvqueryService.class.getName() +
		".impl";
	private static final String _TX_IMPL = AdvqueryService.class.getName() +
		".transaction";
	private static AdvqueryServiceFactory _factory;
	private static AdvqueryService _impl;
	private static AdvqueryService _txImpl;
	private AdvqueryService _service;
}
