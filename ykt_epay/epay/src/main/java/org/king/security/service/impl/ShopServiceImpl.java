package org.king.security.service.impl;

import org.king.framework.service.impl.BaseService;
import org.king.security.dao.TEpayShopinfoDAO;
import org.king.security.domain.TEpayShopinfo;
import org.king.security.service.ShopService;
import org.springframework.jdbc.core.JdbcTemplate;

public class ShopServiceImpl extends BaseService implements ShopService {

	private TEpayShopinfoDAO tShopinfoDAO;
	
	 private JdbcTemplate jdbcTemplate;
	
	
	public void settShopinfoDAO(TEpayShopinfoDAO tShopinfoDAO) {
		this.tShopinfoDAO = tShopinfoDAO;
	}
	
	 public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
	    this.jdbcTemplate = jdbcTemplate;
	  }


	public TEpayShopinfo gettShopinfoByid(Long shopId) {
		return tShopinfoDAO.getShopinfoByid(shopId);
	}

	public void saveOrUpdateShopinfo(TEpayShopinfo tShopinfo,String type) {
		if(type.equals("update")){
			tShopinfoDAO.update(tShopinfo);
		}else{
			tShopinfoDAO.save(tShopinfo);
		}
		
	}

}
