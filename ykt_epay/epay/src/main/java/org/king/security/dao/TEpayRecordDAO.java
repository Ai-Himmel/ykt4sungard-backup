package org.king.security.dao;

import java.util.List;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.security.domain.TEpayActiveinfo;
import org.king.security.domain.TEpayRecord;

public interface TEpayRecordDAO extends DAO {
	public List find(MyQuery myQuery);
	public List find(String query);
	public void findByPage(DBPaginatedList page, MyQuery myQuery);
	public void save(TEpayRecord transientInstance);
	
    public void update(TEpayRecord transientInstance);
    
    public void delete(TEpayRecord persistentInstance);
	
}
