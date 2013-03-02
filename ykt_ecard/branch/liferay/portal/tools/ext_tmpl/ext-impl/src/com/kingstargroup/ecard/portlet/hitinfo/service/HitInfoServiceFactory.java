package com.kingstargroup.ecard.portlet.hitinfo.service;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

public class HitInfoServiceFactory {
	public static HitInfoService getService() {
		return _getFactory()._service;
	}

	public static HitInfoService getImpl() {
		if (_impl == null) {
			_impl = (HitInfoService)BeanLocatorUtil.locate(_IMPL);
		}

		return _impl;
	}

	public static HitInfoService getTxImpl() {
		if (_txImpl == null) {
			_txImpl = (HitInfoService)BeanLocatorUtil.locate(_TX_IMPL);
		}

		return _txImpl;
	}

	public void setService(HitInfoService service) {
		_service = service;
	}

	private static HitInfoServiceFactory _getFactory() {
		if (_factory == null) {
			_factory = (HitInfoServiceFactory)BeanLocatorUtil.locate(_FACTORY);
		}

		return _factory;
	}

	private static final String _FACTORY = HitInfoServiceFactory.class.getName();
	private static final String _IMPL = HitInfoService.class.getName() +
		".impl";
	private static final String _TX_IMPL = HitInfoService.class.getName() +
		".transaction";
	private static HitInfoServiceFactory _factory;
	private static HitInfoService _impl;
	private static HitInfoService _txImpl;
	private HitInfoService _service;
}
