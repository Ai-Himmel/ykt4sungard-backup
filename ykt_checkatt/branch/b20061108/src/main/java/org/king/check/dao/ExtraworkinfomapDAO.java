package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Extraworkinfomap;
import org.king.framework.dao.MyQuery;

public interface ExtraworkinfomapDAO {
	
public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Extraworkinfomap get(Serializable id);
	
	public List getAll();
	
	public void save(Extraworkinfomap transientInstance);
	
    public void update(Extraworkinfomap transientInstance);
    
    public void delete(Extraworkinfomap persistentInstance);
}
