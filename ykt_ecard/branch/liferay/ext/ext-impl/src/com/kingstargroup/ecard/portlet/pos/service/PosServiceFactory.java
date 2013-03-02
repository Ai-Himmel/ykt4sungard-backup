package com.kingstargroup.ecard.portlet.pos.service;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

public class PosServiceFactory {
	public static PosService getService() {
		return _getFactory()._service;
	}

	public static PosService getImpl() {
		if (_impl == null) {
			_impl = (PosService)BeanLocatorUtil.locate(_IMPL);
		}

		return _impl;
	}

	public static PosService getTxImpl() {
		if (_txImpl == null) {
			_txImpl = (PosService)BeanLocatorUtil.locate(_TX_IMPL);
		}

		return _txImpl;
	}

	public void setService(PosService service) {
		_service = service;
	}

	private static PosServiceFactory _getFactory() {
		if (_factory == null) {
			_factory = (PosServiceFactory)BeanLocatorUtil.locate(_FACTORY);
		}

		return _factory;
	}

	private static final String _FACTORY = PosServiceFactory.class.getName();
	private static final String _IMPL = PosService.class.getName() +
		".impl";
	private static final String _TX_IMPL = PosService.class.getName() +
		".transaction";
	private static PosServiceFactory _factory;
	private static PosService _impl;
	private static PosService _txImpl;
	private PosService _service;

}
