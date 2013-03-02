package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Departconf;

public interface DepartConfDAO {
	public List find(String query);
	 
	public Departconf get(Serializable id);
	
	public List getAll();
	
	public void save(Departconf transientInstance);
	
    public void update(Departconf transientInstance);
    
    public void delete(Departconf persistentInstance);
}
