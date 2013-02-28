package org.king.security.service;

import org.king.framework.service.Service;
import org.king.security.domain.TEpayShopinfo;

public interface ShopService extends Service{

	public TEpayShopinfo gettShopinfoByid(Long shopId);

	public void saveOrUpdateShopinfo(TEpayShopinfo tShopinfo,String type);

}
