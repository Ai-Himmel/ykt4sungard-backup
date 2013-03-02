package com.kingstargroup.ecard.portlet.distribution.service;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

public class CustomerLocalServiceFactory {
	
	public static CustomerLocalService getService() {
		return _getFactory()._service;
	}

	public static CustomerLocalService getImpl() {
		if (_impl == null) {
			_impl = (CustomerLocalService)BeanLocatorUtil.locate(_IMPL);
		}

		return _impl;
	}

	public static CustomerLocalService getTxImpl() {
		if (_txImpl == null) {
			_txImpl = (CustomerLocalService)BeanLocatorUtil.locate(_TX_IMPL);
		}

		return _txImpl;
	}

	public void setService(CustomerLocalService service) {
		_service = service;
	}

	private static CustomerLocalServiceFactory _getFactory() {
		if (_factory == null) {
			_factory = (CustomerLocalServiceFactory)BeanLocatorUtil.locate(_FACTORY);
		}

		return _factory;
	}

	private static final String _FACTORY = CustomerLocalServiceFactory.class.getName();
	private static final String _IMPL = CustomerLocalService.class.getName() +
		".impl";
	private static final String _TX_IMPL = CustomerLocalService.class.getName() +
		".transaction";
	private static CustomerLocalServiceFactory _factory;
	private static CustomerLocalService _impl;
	private static CustomerLocalService _txImpl;
	private CustomerLocalService _service;

}
