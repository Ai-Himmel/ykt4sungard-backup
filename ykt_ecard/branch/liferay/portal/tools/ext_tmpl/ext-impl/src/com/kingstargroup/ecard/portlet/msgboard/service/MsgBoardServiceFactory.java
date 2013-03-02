package com.kingstargroup.ecard.portlet.msgboard.service;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

public class MsgBoardServiceFactory {
	public static MsgBoardService getService() {
		return _getFactory()._service;
	}

	public static MsgBoardService getImpl() {
		if (_impl == null) {
			_impl = (MsgBoardService)BeanLocatorUtil.locate(_IMPL);
		}

		return _impl;
	}

	public static MsgBoardService getTxImpl() {
		if (_txImpl == null) {
			_txImpl = (MsgBoardService)BeanLocatorUtil.locate(_TX_IMPL);
		}

		return _txImpl;
	}

	public void setService(MsgBoardService service) {
		_service = service;
	}

	private static MsgBoardServiceFactory _getFactory() {
		if (_factory == null) {
			_factory = (MsgBoardServiceFactory)BeanLocatorUtil.locate(_FACTORY);
		}

		return _factory;
	}

	private static final String _FACTORY = MsgBoardServiceFactory.class.getName();
	private static final String _IMPL = MsgBoardService.class.getName() +
		".impl";
	private static final String _TX_IMPL = MsgBoardService.class.getName() +
		".transaction";
	private static MsgBoardServiceFactory _factory;
	private static MsgBoardService _impl;
	private static MsgBoardService _txImpl;
	private MsgBoardService _service;
}
