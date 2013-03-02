package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Workconfmap;
import org.king.framework.dao.MyQuery;


public interface WorkconfmapDao {
public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Workconfmap get(Serializable id);
	
	public List getAll();
	
	public void save(Workconfmap transientInstance);
	
    public void update(Workconfmap transientInstance);
    
    public void delete(Workconfmap persistentInstance);
}
