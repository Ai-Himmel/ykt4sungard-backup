package com.kingstargroup.ecard.portlet.advquery.service;

import org.springframework.beans.factory.InitializingBean;

import com.kingstargroup.ecard.hibernate.advquery.AdvqueryPersistence;
import com.kingstargroup.ecard.hibernate.util.AdvqueryUtil;
import com.liferay.portal.service.impl.PrincipalBean;

public abstract class AdvqueryServiceBase extends PrincipalBean
		implements InitializingBean, AdvqueryService {	
	
	/**
	 * @return the advqueryService
	 */
	public AdvqueryService getAdvqueryService() {
		return advqueryService;
	}
	/**
	 * @param advqueryService the advqueryService to set
	 */
	public void setAdvqueryService(AdvqueryService advqueryService) {
		this.advqueryService = advqueryService;
	}
	/**
	 * @return the advqueryPersistence
	 */
	public AdvqueryPersistence getAdvqueryPersistence() {
		return advqueryPersistence;
	}
	/**
	 * @param advqueryPersistence the advqueryPersistence to set
	 */
	public void setAdvqueryPersistence(AdvqueryPersistence advqueryPersistence) {
		this.advqueryPersistence = advqueryPersistence;
	}
	public void afterPropertiesSet() throws Exception {

			if(advqueryService == null){
				advqueryService = AdvqueryServiceFactory.getImpl();
			}
			
			if(advqueryPersistence ==null){
				advqueryPersistence = AdvqueryUtil.getPersistence();
			}

	}

	protected AdvqueryService advqueryService;
	protected AdvqueryPersistence advqueryPersistence;
	
}
