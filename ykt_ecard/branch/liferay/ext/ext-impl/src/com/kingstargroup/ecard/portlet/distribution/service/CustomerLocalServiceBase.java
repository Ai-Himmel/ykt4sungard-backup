package com.kingstargroup.ecard.portlet.distribution.service;

import org.springframework.beans.factory.InitializingBean;

import com.kingstargroup.ecard.hibernate.customer.CustomerPersistence;
import com.kingstargroup.ecard.hibernate.util.CustomerUtil;
import com.liferay.portal.service.impl.PrincipalBean;

public abstract class CustomerLocalServiceBase extends PrincipalBean implements
		CustomerLocalService, InitializingBean {

	public CustomerLocalService getCustomerLocalService() {
		return customerLocalService;
	}

	public void setCustomerLocalService(
			CustomerLocalService customerLocalService) {
		this.customerLocalService = customerLocalService;
	}

	public CustomerPersistence getCustomerPersistence() {
		return customerPersistence;
	}

	public void setCustomerPersistence(CustomerPersistence customerPersistence) {
		this.customerPersistence = customerPersistence;
	}

	public void afterPropertiesSet() throws Exception {
		// TODO Auto-generated method stub
		if (customerLocalService == null) {
			customerLocalService = CustomerLocalServiceFactory.getService();
		}
		if (customerPersistence == null) {
			customerPersistence = CustomerUtil.getPersistence();
		}

	}

	protected CustomerLocalService customerLocalService;
	protected CustomerPersistence customerPersistence;

}
