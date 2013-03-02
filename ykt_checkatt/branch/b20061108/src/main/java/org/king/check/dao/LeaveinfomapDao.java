package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Leaveinfomap;
import org.king.framework.dao.MyQuery;


public interface LeaveinfomapDao {
public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Leaveinfomap get(Serializable id);
	
	public List getAll();
	
	public void save(Leaveinfomap transientInstance);
	
    public void update(Leaveinfomap transientInstance);
    
    public void delete(Leaveinfomap persistentInstance);
}
