package com.kingstargroup.ecard.portlet.information.service;

import org.springframework.beans.factory.InitializingBean;

import com.kingstargroup.ecard.hibernate.information.InformationPersistence;
import com.kingstargroup.ecard.hibernate.infotype.InfoTypePersistence;
import com.kingstargroup.ecard.hibernate.upload.UploadFilePersistence;
import com.kingstargroup.ecard.hibernate.util.InfoTypeUtil;
import com.kingstargroup.ecard.hibernate.util.InformationUtil;
import com.kingstargroup.ecard.hibernate.util.UploadFileUtil;
import com.kingstargroup.ecard.portlet.infotype.service.InfoTypeService;
import com.kingstargroup.ecard.portlet.infotype.service.InfoTypeServiceFactory;
import com.kingstargroup.ecard.portlet.uploadfile.service.UploadFileService;
import com.kingstargroup.ecard.portlet.uploadfile.service.UploadFileServiceFactory;
import com.liferay.portal.service.impl.PrincipalBean;

public abstract class EcardInformationServiceBase extends PrincipalBean
		implements InitializingBean, EcardInformationService {

	public EcardInformationService getEcardInformationService() {
		return ecardInformationService;
	}

	public void setEcardInformationService(
			EcardInformationService ecardInformationService) {
		this.ecardInformationService = ecardInformationService;
	}

	public InformationPersistence getInformationPersistence() {
		return informationPersistence;
	}

	public void setInformationPersistence(
			InformationPersistence informationPersistence) {
		this.informationPersistence = informationPersistence;
	}

	public InfoTypeService getInfoTypeService() {
		return infoTypeService;
	}

	public void setInfoTypeService(InfoTypeService infoTypeService) {
		this.infoTypeService = infoTypeService;
	}

	public InfoTypePersistence getInfoTypePersistence() {
		return infoTypePersistence;
	}

	public void setInfoTypePersistence(InfoTypePersistence infoTypePersistence) {
		this.infoTypePersistence = infoTypePersistence;
	}

	public UploadFileService getUploadFileService() {
		return uploadFileService;
	}

	public void setUploadFileService(UploadFileService uploadFileService) {
		this.uploadFileService = uploadFileService;
	}

	public UploadFilePersistence getUploadFilePersistence() {
		return uploadFilePersistence;
	}

	public void setUploadFilePersistence(
			UploadFilePersistence uploadFilePersistence) {
		this.uploadFilePersistence = uploadFilePersistence;
	}

	public void afterPropertiesSet() throws Exception {
		// TODO Auto-generated method stub
		if (ecardInformationService == null) {
			ecardInformationService = EcardInformationServiceFactory.getImpl();
		}

		if (informationPersistence == null) {
			informationPersistence = InformationUtil.getPersistence();
		}

		if (infoTypeService == null) {
			infoTypeService = InfoTypeServiceFactory.getImpl();
		}

		if (infoTypePersistence == null) {
			infoTypePersistence = InfoTypeUtil.getPersistence();
		}

		if (uploadFileService == null) {
			uploadFileService = UploadFileServiceFactory.getImpl();
		}

		if (uploadFilePersistence == null) {
			uploadFilePersistence = UploadFileUtil.getPersistence();
		}

	}

	protected EcardInformationService ecardInformationService;
	protected InformationPersistence informationPersistence;
	protected InfoTypeService infoTypeService;
	protected InfoTypePersistence infoTypePersistence;
	protected UploadFileService uploadFileService;
	protected UploadFilePersistence uploadFilePersistence;

}
