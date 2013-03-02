package com.kingstargroup.ecard.portlet.bank.service;

import org.springframework.beans.factory.InitializingBean;

import com.kingstargroup.ecard.hibernate.bank.BankPersistence;
import com.kingstargroup.ecard.hibernate.util.BankUtil;
import com.liferay.portal.service.impl.PrincipalBean;

public abstract class BankServiceBase extends PrincipalBean
		implements InitializingBean, BankService {	
	

	public BankService getBankService() {
		return bankService;
	}

	public void setBankService(BankService bankService) {
		this.bankService = bankService;
	}
	

	public BankPersistence getBankPersistence() {
		return bankPersistence;
	}

	public void setBankPersistence(BankPersistence bankPersistence) {
		this.bankPersistence = bankPersistence;
	}

	public void afterPropertiesSet() throws Exception {

			if(bankService == null){
				bankService = BankServiceFactory.getImpl();
			}
			
			if(bankPersistence ==null){
				bankPersistence = BankUtil.getPersistence();
			}

	}

	protected BankService bankService;
	protected BankPersistence bankPersistence;
	
}
