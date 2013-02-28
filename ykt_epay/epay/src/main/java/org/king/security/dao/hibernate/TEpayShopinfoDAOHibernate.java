package org.king.security.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.framework.util.MyUtils;
import org.king.security.dao.TEpayShopinfoDAO;
import org.king.security.domain.TEpayShopinfo;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class TEpayShopinfoDAOHibernate implements TEpayShopinfoDAO {

	private static final Logger log = LoggerFactory.getLogger(TEpayShopinfoDAOHibernate.class);
	private BaseDAO baseDAO;
	
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}
	
	public void delete(TEpayShopinfo persistentInstance) {
		baseDAO.removeEntity(persistentInstance);

	}

	public List find(MyQuery myQuery) {
		return baseDAO.findEntity(myQuery);
	}

	public List find(String query) {
		return baseDAO.findEntity(query);
	}

	public TEpayShopinfo get(Serializable id) {
		return (TEpayShopinfo)baseDAO.getEntity(TEpayShopinfo.class, id);
	}

	public List getAll() {
		return baseDAO.findEntity("from TEpayShopinfo");
	}

	public void save(TEpayShopinfo transientInstance) {
		baseDAO.saveEntity(transientInstance);
	}

	public void update(TEpayShopinfo transientInstance) {
		baseDAO.updateEntity(transientInstance);
	}

	public TEpayShopinfo getShopinfoByid(Long shopId) {
		if (MyUtils.isBlank(shopId)) {
			return null;
		}
		
		TEpayShopinfo epayShopinfo = null;
		try {
			epayShopinfo = (TEpayShopinfo)baseDAO.getEntity(TEpayShopinfo.class, shopId);
		} catch (Exception e) {
			return null;
		}
		
		return epayShopinfo;
	}

	public boolean isExistShopinfoByid(Long shopId) {
		TEpayShopinfo epayShopinfo = null;
		try {
			epayShopinfo = (TEpayShopinfo)baseDAO.getEntity(TEpayShopinfo.class, shopId);
		} catch (Exception e) {
			return false;
		}
		if(epayShopinfo!=null){
			return true;
		}else{
			 return false;
		}
		}
	
}
