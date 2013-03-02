package com.kingstargroup.ecard.portlet.cardlist.service;

import org.springframework.beans.factory.InitializingBean;

import com.kingstargroup.ecard.hibernate.information.InformationPersistence;
import com.kingstargroup.ecard.hibernate.util.InformationUtil;
import com.liferay.portal.service.impl.PrincipalBean;

public abstract class CardListServiceBase extends PrincipalBean implements
		CardListService, InitializingBean {
	public CardListService getCardListservice() {
		return cardListservice;
	}
	public void setCardListservice(CardListService cardListservice) {
		this.cardListservice = cardListservice;
	}
	public InformationPersistence getInformationPersistence() {
		return informationPersistence;
	}
	public void setInformationPersistence(
			InformationPersistence informationPersistence) {
		this.informationPersistence = informationPersistence;
	}
	public void afterPropertiesSet() throws Exception {
		// TODO Auto-generated method stub
		if(cardListservice==null){
			cardListservice = CardListServiceFactory.getImpl();
		}
		if(informationPersistence == null){
			informationPersistence = InformationUtil.getPersistence();
		}
	}
	
	
	protected CardListService cardListservice;
	protected InformationPersistence informationPersistence;
	

}
