package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.TCheckWorkconfinfo;

public interface DepartConfDAO {
	public List find(String query);
	 
	public TCheckWorkconfinfo get(Serializable id);
	
	public List getAll();
	
	public void save(TCheckWorkconfinfo transientInstance);
	
    public void update(TCheckWorkconfinfo transientInstance);
    
    public void delete(TCheckWorkconfinfo persistentInstance);
}
