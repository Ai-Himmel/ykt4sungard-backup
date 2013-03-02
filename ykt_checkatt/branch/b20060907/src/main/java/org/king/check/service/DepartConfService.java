package org.king.check.service;

import java.io.Serializable;
import java.util.List;
import java.util.Map;

import org.king.check.domain.Departconf;

public interface DepartConfService {
	public List find(String query);
	 
	public Departconf get(Serializable id);
	
	public List getAll();
	
	public void save(Departconf transientInstance);
	
    public void update(Departconf transientInstance);
    
    public void delete(Departconf persistentInstance);
    
    public List getDepartConfByDptId(String dptId);
    
    public List isExist(Map filter)throws Exception;
    
    public List search(Map filter)throws Exception;

}
