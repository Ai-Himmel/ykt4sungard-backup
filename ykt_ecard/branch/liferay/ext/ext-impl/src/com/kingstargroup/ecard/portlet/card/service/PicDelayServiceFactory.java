package com.kingstargroup.ecard.portlet.card.service;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

public class PicDelayServiceFactory {
	
	public static PicDelayService getService() {
		return _getFactory()._service;
	}

	public static PicDelayService getImpl() {
		if (_impl == null) {
			_impl = (PicDelayService)BeanLocatorUtil.locate(_IMPL);
		}

		return _impl;
	}

	public static PicDelayService getTxImpl() {
		if (_txImpl == null) {
			_txImpl = (PicDelayService)BeanLocatorUtil.locate(_TX_IMPL);
		}

		return _txImpl;
	}

	public void setService(PicDelayService service) {
		_service = service;
	}

	private static PicDelayServiceFactory _getFactory() {
		if (_factory == null) {
			_factory = (PicDelayServiceFactory)BeanLocatorUtil.locate(_FACTORY);
		}

		return _factory;
	}

	private static final String _FACTORY = PicDelayServiceFactory.class.getName();
	private static final String _IMPL = PicDelayService.class.getName() +
		".impl";
	private static final String _TX_IMPL = PicDelayService.class.getName() +
		".transaction";
	private static PicDelayServiceFactory _factory;
	private static PicDelayService _impl;
	private static PicDelayService _txImpl;
	private PicDelayService _service;

}
