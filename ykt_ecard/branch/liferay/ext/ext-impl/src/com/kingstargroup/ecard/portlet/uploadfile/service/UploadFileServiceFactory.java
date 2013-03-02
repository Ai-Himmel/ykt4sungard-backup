package com.kingstargroup.ecard.portlet.uploadfile.service;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

public class UploadFileServiceFactory {
	public static UploadFileService getService() {
		return _getFactory()._service;
	}

	public static UploadFileService getImpl() {
		if (_impl == null) {
			_impl = (UploadFileService)BeanLocatorUtil.locate(_IMPL);
		}

		return _impl;
	}

	public static UploadFileService getTxImpl() {
		if (_txImpl == null) {
			_txImpl = (UploadFileService)BeanLocatorUtil.locate(_TX_IMPL);
		}

		return _txImpl;
	}

	public void setService(UploadFileService service) {
		_service = service;
	}

	private static UploadFileServiceFactory _getFactory() {
		if (_factory == null) {
			_factory = (UploadFileServiceFactory)BeanLocatorUtil.locate(_FACTORY);
		}

		return _factory;
	}

	private static final String _FACTORY = UploadFileServiceFactory.class.getName();
	private static final String _IMPL = UploadFileService.class.getName() +
		".impl";
	private static final String _TX_IMPL = UploadFileService.class.getName() +
		".transaction";
	private static UploadFileServiceFactory _factory;
	private static UploadFileService _impl;
	private static UploadFileService _txImpl;
	private UploadFileService _service;
}
