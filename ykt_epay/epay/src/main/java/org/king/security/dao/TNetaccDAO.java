package org.king.security.dao;

import java.io.Serializable;
import java.util.List;

import org.king.common.displaytag.DBPaginatedList;
import org.king.common.query.QueryTranslate;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.security.domain.TNetacc;

public interface TNetaccDAO extends DAO {

	public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public TNetacc get(Serializable id);
	
	public List getAll();
	
	public void save(TNetacc transientInstance);
	
    public void update(TNetacc transientInstance);
    
    public void delete(TNetacc persistentInstance);

    //通过账号获取账户信息
	public TNetacc findNetaccByAccno(String accno);

	public void findByPage(DBPaginatedList page, QueryTranslate queryTranslate);

}
