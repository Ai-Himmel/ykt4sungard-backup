package com.kingstargroup.ecard.portlet.card.service;

import org.springframework.beans.factory.InitializingBean;

import com.kingstargroup.ecard.hibernate.postpone.PostponePersistence;
import com.kingstargroup.ecard.hibernate.util.PostponeUtil;
import com.liferay.portal.service.impl.PrincipalBean;

public abstract class PostponeServiceBase extends PrincipalBean implements
		PostponeService, InitializingBean {
	

	public PostponeService getPostponeService() {
		return postponeService;
	}
	public void setPostponeService(PostponeService postponeService) {
		this.postponeService = postponeService;
	}
	public PostponePersistence getPostponePersistence() {
		return postponePersistence;
	}
	public void setPostponePersistence(PostponePersistence postponePersistence) {
		this.postponePersistence = postponePersistence;
	}
	public void afterPropertiesSet() throws Exception {
		// TODO Auto-generated method stub
		if(postponeService==null){
			postponeService = PostponeServiceFactory.getImpl();
		}
		if(postponePersistence == null){
			postponePersistence = PostponeUtil.getPersistence();
		}
	}
	
	
	protected PostponeService postponeService;
	protected PostponePersistence postponePersistence;
	

}
