package com.kingstargroup.ecard.portlet.losecard.service;

import org.springframework.beans.factory.InitializingBean;

import com.kingstargroup.ecard.hibernate.losecard.LoseCardPersistence;
import com.kingstargroup.ecard.hibernate.util.LoseCardUtil;
import com.liferay.portal.service.impl.PrincipalBean;

public abstract class LoseCardServiceBase extends PrincipalBean
		implements InitializingBean,LoseCardService{

	public LoseCardService getLoseCardService() {
		return loseCardService;
	}
	public void setMsgBoardService(LoseCardService loseCardService) {
		this.loseCardService = loseCardService;
	}
	public LoseCardPersistence getLoseCardPersistence() {
		return loseCardPersistence;
	}
	public void setLoseCardPersistence(LoseCardPersistence loseCardPersistence) {
		this.loseCardPersistence = loseCardPersistence;
	}
	public void afterPropertiesSet() throws Exception {

			if(loseCardService == null){
				loseCardService = LoseCardServiceFactory.getImpl();
			}
			if(loseCardPersistence == null){
				loseCardPersistence = LoseCardUtil.getPersistence();
			}

	}

	protected LoseCardService loseCardService;
	protected LoseCardPersistence loseCardPersistence;

}
