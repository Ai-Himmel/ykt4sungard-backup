package com.kingstargroup.ecard.portlet.information.service;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

public class EcardInformationServiceFactory {
	public static EcardInformationService getService() {
		return _getFactory()._service;
	}

	public static EcardInformationService getImpl() {
		if (_impl == null) {
			_impl = (EcardInformationService)BeanLocatorUtil.locate(_IMPL);
		}

		return _impl;
	}

	public static EcardInformationService getTxImpl() {
		if (_txImpl == null) {
			_txImpl = (EcardInformationService)BeanLocatorUtil.locate(_TX_IMPL);
		}

		return _txImpl;
	}

	public void setService(EcardInformationService service) {
		_service = service;
	}

	private static EcardInformationServiceFactory _getFactory() {
		if (_factory == null) {
			_factory = (EcardInformationServiceFactory)BeanLocatorUtil.locate(_FACTORY);
		}

		return _factory;
	}

	private static final String _FACTORY = EcardInformationServiceFactory.class.getName();
	private static final String _IMPL = EcardInformationService.class.getName() +
		".impl";
	private static final String _TX_IMPL = EcardInformationService.class.getName() +
		".transaction";
	private static EcardInformationServiceFactory _factory;
	private static EcardInformationService _impl;
	private static EcardInformationService _txImpl;
	private EcardInformationService _service;
}
