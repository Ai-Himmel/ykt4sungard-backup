package org.king.check.service;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Workconfmap;
import org.king.framework.dao.MyQuery;

public interface WorkConfMapService {
public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Workconfmap get(Serializable id);
	
	public Workconfmap getWorkconfmapByClerkId(Integer clerkId);
	
	public List getAll();
	
	public void save(Workconfmap transientInstance);
	
    public void update(Workconfmap transientInstance);
    
    public void delete(Workconfmap persistentInstance);
}
