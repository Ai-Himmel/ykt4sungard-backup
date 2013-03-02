package com.kingstargroup.ecard.portlet.card.service;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

public class PostponeServiceFactory {
	
	public static PostponeService getService() {
		return _getFactory()._service;
	}

	public static PostponeService getImpl() {
		if (_impl == null) {
			_impl = (PostponeService)BeanLocatorUtil.locate(_IMPL);
		}

		return _impl;
	}

	public static PostponeService getTxImpl() {
		if (_txImpl == null) {
			_txImpl = (PostponeService)BeanLocatorUtil.locate(_TX_IMPL);
		}

		return _txImpl;
	}

	public void setService(PostponeService service) {
		_service = service;
	}

	private static PostponeServiceFactory _getFactory() {
		if (_factory == null) {
			_factory = (PostponeServiceFactory)BeanLocatorUtil.locate(_FACTORY);
		}

		return _factory;
	}

	private static final String _FACTORY = PostponeServiceFactory.class.getName();
	private static final String _IMPL = PostponeService.class.getName() +
		".impl";
	private static final String _TX_IMPL = PostponeService.class.getName() +
		".transaction";
	private static PostponeServiceFactory _factory;
	private static PostponeService _impl;
	private static PostponeService _txImpl;
	private PostponeService _service;

}
