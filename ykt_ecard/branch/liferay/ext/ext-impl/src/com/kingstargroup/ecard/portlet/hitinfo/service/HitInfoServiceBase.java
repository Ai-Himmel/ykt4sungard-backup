package com.kingstargroup.ecard.portlet.hitinfo.service;

import org.springframework.beans.factory.InitializingBean;

import com.kingstargroup.ecard.hibernate.hitinfo.HitInfoPersistence;
import com.kingstargroup.ecard.hibernate.infotype.InfoTypePersistence;
import com.kingstargroup.ecard.hibernate.util.HitInfoUtil;
import com.kingstargroup.ecard.hibernate.util.InfoTypeUtil;
import com.liferay.portal.service.impl.PrincipalBean;

public abstract class HitInfoServiceBase extends PrincipalBean
		implements InitializingBean, HitInfoService {
	

	public HitInfoService getHitInfoService() {
		return hitInfoService;
	}
	public void setHitInfoService(HitInfoService hitInfoService) {
		this.hitInfoService = hitInfoService;
	}
	public HitInfoPersistence getHitInfoPersistence() {
		return hitInfoPersistence;
	}
	public void setHitInfoPersistence(HitInfoPersistence hitInfoPersistence) {
		this.hitInfoPersistence = hitInfoPersistence;
	}
	public void afterPropertiesSet() throws Exception {

			if(hitInfoService == null){
				hitInfoService = HitInfoServiceFactory.getImpl();
			}
			if(hitInfoPersistence == null){
				hitInfoPersistence = HitInfoUtil.getPersistence();
			}

	}

	protected HitInfoService hitInfoService;
	protected HitInfoPersistence hitInfoPersistence;
	
	
}
