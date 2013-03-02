package com.kingstargroup.ecard.portlet.infotype.service;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

public class InfoTypeServiceFactory {
	public static InfoTypeService getService() {
		return _getFactory()._service;
	}

	public static InfoTypeService getImpl() {
		if (_impl == null) {
			_impl = (InfoTypeService)BeanLocatorUtil.locate(_IMPL);
		}

		return _impl;
	}

	public static InfoTypeService getTxImpl() {
		if (_txImpl == null) {
			_txImpl = (InfoTypeService)BeanLocatorUtil.locate(_TX_IMPL);
		}

		return _txImpl;
	}

	public void setService(InfoTypeService service) {
		_service = service;
	}

	private static InfoTypeServiceFactory _getFactory() {
		if (_factory == null) {
			_factory = (InfoTypeServiceFactory)BeanLocatorUtil.locate(_FACTORY);
		}

		return _factory;
	}

	private static final String _FACTORY = InfoTypeServiceFactory.class.getName();
	private static final String _IMPL = InfoTypeService.class.getName() +
		".impl";
	private static final String _TX_IMPL = InfoTypeService.class.getName() +
		".transaction";
	private static InfoTypeServiceFactory _factory;
	private static InfoTypeService _impl;
	private static InfoTypeService _txImpl;
	private InfoTypeService _service;
}
