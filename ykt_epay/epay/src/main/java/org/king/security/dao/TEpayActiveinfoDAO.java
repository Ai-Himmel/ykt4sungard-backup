package org.king.security.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.MyQuery;
import org.king.security.domain.TEpayActiveinfo;

public interface TEpayActiveinfoDAO {
public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public TEpayActiveinfo get(Serializable id);
	
	public List getAll();
	
	public void save(TEpayActiveinfo transientInstance);
	
    public void update(TEpayActiveinfo transientInstance);
    
    public void delete(TEpayActiveinfo persistentInstance);
}
