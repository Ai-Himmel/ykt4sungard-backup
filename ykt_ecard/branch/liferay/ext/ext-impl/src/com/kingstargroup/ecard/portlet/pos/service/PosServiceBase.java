package com.kingstargroup.ecard.portlet.pos.service;

import org.springframework.beans.factory.InitializingBean;

import com.kingstargroup.ecard.hibernate.pos.PosPersistence;
import com.kingstargroup.ecard.hibernate.util.PosUtil;
import com.liferay.portal.service.impl.PrincipalBean;

public abstract class PosServiceBase extends PrincipalBean implements
		InitializingBean, PosService {

	public PosService getPosService() {
		return posService;
	}

	public void setPosService(PosService posService) {
		this.posService = posService;
	}

	public void afterPropertiesSet() throws Exception {
		if (posService == null) {
			posService = PosServiceFactory.getImpl();
		}
		if(posPersistence == null){
			posPersistence = PosUtil.getPersistence();
		}
	}

	protected PosPersistence posPersistence;
	protected PosService posService;
}
