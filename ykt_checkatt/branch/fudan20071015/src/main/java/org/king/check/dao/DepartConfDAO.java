package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Tdeptworkconfinfo;

public interface DepartConfDAO {
	public List find(String query);
	 
	public Tdeptworkconfinfo get(Serializable id);
	
	public List getAll();
	
	public void save(Tdeptworkconfinfo transientInstance);
	
    public void update(Tdeptworkconfinfo transientInstance);
    
    public void delete(Tdeptworkconfinfo persistentInstance);
}
