package com.kingstargroup.ecard.portlet.uploadfile.service;

import org.springframework.beans.factory.InitializingBean;

import com.kingstargroup.ecard.hibernate.upload.UploadFilePersistence;
import com.kingstargroup.ecard.hibernate.util.UploadFileUtil;
import com.liferay.portal.service.impl.PrincipalBean;

public abstract class UploadFileServiceBase extends PrincipalBean
		implements InitializingBean, UploadFileService {
	
	public UploadFileService getUploadFileService() {
		return uploadFileService;
	}
	public void setUploadFileService(UploadFileService uploadFileService) {
		this.uploadFileService = uploadFileService;
	}
	public UploadFilePersistence getUploadFilePersistence() {
		return uploadFilePersistence;
	}
	public void setUploadFilePersistence(UploadFilePersistence uploadFilePersistence) {
		this.uploadFilePersistence = uploadFilePersistence;
	}
	
	public void afterPropertiesSet() throws Exception {

			if(uploadFileService == null){
				uploadFileService = UploadFileServiceFactory.getImpl();
			}
			if(uploadFilePersistence == null){
				uploadFilePersistence = UploadFileUtil.getPersistence();
			}

	}

	protected UploadFileService uploadFileService;
	protected UploadFilePersistence uploadFilePersistence;
	
	
}
