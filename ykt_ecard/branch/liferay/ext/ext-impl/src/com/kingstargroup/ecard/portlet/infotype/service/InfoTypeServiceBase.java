package com.kingstargroup.ecard.portlet.infotype.service;

import org.springframework.beans.factory.InitializingBean;

import com.kingstargroup.ecard.hibernate.infotype.InfoTypePersistence;
import com.kingstargroup.ecard.hibernate.util.InfoTypeUtil;
import com.liferay.portal.service.impl.PrincipalBean;

public abstract class InfoTypeServiceBase extends PrincipalBean
		implements InitializingBean, InfoTypeService {
	
	

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
	public void afterPropertiesSet() throws Exception {

			if(infoTypeService == null){
				infoTypeService = InfoTypeServiceFactory.getImpl();
			}
			if(infoTypePersistence == null){
				 infoTypePersistence = InfoTypeUtil.getPersistence();
			}

	}

	protected InfoTypeService infoTypeService;
	protected InfoTypePersistence infoTypePersistence;
	
	
}
