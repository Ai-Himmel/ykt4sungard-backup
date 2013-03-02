package com.kingstargroup.ecard.portlet.bank.service;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

public class BankServiceFactory {
	public static BankService getService() {
		return _getFactory()._service;
	}

	public static BankService getImpl() {
		if (_impl == null) {
			_impl = (BankService)BeanLocatorUtil.locate(_IMPL);
		}

		return _impl;
	}

	public static BankService getTxImpl() {
		if (_txImpl == null) {
			_txImpl = (BankService)BeanLocatorUtil.locate(_TX_IMPL);
		}

		return _txImpl;
	}

	public void setService(BankService service) {
		_service = service;
	}

	private static BankServiceFactory _getFactory() {
		if (_factory == null) {
			_factory = (BankServiceFactory)BeanLocatorUtil.locate(_FACTORY);
		}

		return _factory;
	}

	private static final String _FACTORY = BankServiceFactory.class.getName();
	private static final String _IMPL = BankService.class.getName() +
		".impl";
	private static final String _TX_IMPL = BankService.class.getName() +
		".transaction";
	private static BankServiceFactory _factory;
	private static BankService _impl;
	private static BankService _txImpl;
	private BankService _service;
}
