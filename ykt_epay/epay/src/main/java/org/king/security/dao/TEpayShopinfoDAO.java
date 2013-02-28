package org.king.security.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.MyQuery;
import org.king.security.domain.TEpayShopinfo;

public interface TEpayShopinfoDAO {
	public List find(MyQuery myQuery);

	public List find(String query);

	public TEpayShopinfo get(Serializable id);

	public List getAll();

	public void save(TEpayShopinfo transientInstance);

	public void update(TEpayShopinfo transientInstance);

	public void delete(TEpayShopinfo persistentInstance);

	public TEpayShopinfo getShopinfoByid(Long shopId);

	public boolean isExistShopinfoByid(Long shopId);
}
