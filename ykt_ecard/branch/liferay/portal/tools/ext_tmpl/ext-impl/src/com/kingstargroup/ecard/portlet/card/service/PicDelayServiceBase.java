package com.kingstargroup.ecard.portlet.card.service;

import org.springframework.beans.factory.InitializingBean;

import com.kingstargroup.ecard.hibernate.picdelay.PicDelayPersistence;
import com.kingstargroup.ecard.hibernate.util.PicDelayUtil;
import com.liferay.portal.service.impl.PrincipalBean;

public abstract class PicDelayServiceBase extends PrincipalBean implements
		PicDelayService, InitializingBean {

	public PicDelayService getPicDelayService() {
		return picDelayService;
	}
	public void setPicDelayService(PicDelayService picDelayService) {
		this.picDelayService = picDelayService;
	}
	public PicDelayPersistence getPicDelayPersistence() {
		return picDelayPersistence;
	}
	public void setPicDelayPersistence(PicDelayPersistence picDelayPersistence) {
		this.picDelayPersistence = picDelayPersistence;
	}
	public void afterPropertiesSet() throws Exception {
		// TODO Auto-generated method stub
		if(picDelayService==null){
			picDelayService = PicDelayServiceFactory.getImpl();
		}
		if(picDelayPersistence == null){
			picDelayPersistence = PicDelayUtil.getPersistence();
		}
	}
	
	
	protected PicDelayService picDelayService;
	protected PicDelayPersistence picDelayPersistence;
	

}
