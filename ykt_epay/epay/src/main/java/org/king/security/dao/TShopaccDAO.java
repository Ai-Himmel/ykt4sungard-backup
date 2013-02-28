package org.king.security.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.security.domain.TShopacc;;

public interface TShopaccDAO extends DAO {
     public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public TShopacc get(Serializable id);
	
	public List getAll();
	
	public void save(TShopacc transientInstance);
	
    public void update(TShopacc transientInstance);
    
    public void delete(TShopacc persistentInstance);

    //通过账号获取账户信息
	public TShopacc findShopaccByAccno(String accno);
}
