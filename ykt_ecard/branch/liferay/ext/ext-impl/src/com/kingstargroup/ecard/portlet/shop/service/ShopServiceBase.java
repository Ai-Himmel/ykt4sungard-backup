package com.kingstargroup.ecard.portlet.shop.service;

import org.springframework.beans.factory.InitializingBean;

import com.kingstargroup.ecard.hibernate.customer.CustomerPersistence;
import com.kingstargroup.ecard.hibernate.device.DevicePersistence;
import com.kingstargroup.ecard.hibernate.shop.ShopPersistence;
import com.kingstargroup.ecard.hibernate.util.CustomerUtil;
import com.kingstargroup.ecard.hibernate.util.DeviceUtil;
import com.kingstargroup.ecard.hibernate.util.ShopUtil;
import com.liferay.portal.service.impl.PrincipalBean;

public abstract class ShopServiceBase extends PrincipalBean
		implements InitializingBean, ShopService {	
	

	public ShopService getShopService() {
		return shopService;
	}
	public void setShopService(ShopService shopService) {
		this.shopService = shopService;
	}
	public ShopPersistence getShopPersistence() {
		return shopPersistence;
	}
	public void setShopPersistence(ShopPersistence shopPersistence) {
		this.shopPersistence = shopPersistence;
	}
	public DevicePersistence getDevicePersistence() {
		return devicePersistence;
	}
	public void setDevicePersistence(DevicePersistence devicePersistence) {
		this.devicePersistence = devicePersistence;
	}
	
	public CustomerPersistence getCustomerPersistence() {
		return customerPersistence;
	}
	public void setCustomerPersistence(CustomerPersistence customerPersistence) {
		this.customerPersistence = customerPersistence;
	}
	public void afterPropertiesSet() throws Exception {

			if(shopService == null){
				shopService = ShopServiceFactory.getImpl();
			}
			if(shopPersistence == null){
				shopPersistence = ShopUtil.getPersistence();
			}
			if(devicePersistence ==null){
				devicePersistence = DeviceUtil.getPersistence();
			}			
			if(customerPersistence ==null){
				customerPersistence = CustomerUtil.getPersistence();
			}
	}

	protected ShopService shopService;
	protected ShopPersistence shopPersistence;
	protected DevicePersistence devicePersistence;
	protected CustomerPersistence customerPersistence;
	
	
}
