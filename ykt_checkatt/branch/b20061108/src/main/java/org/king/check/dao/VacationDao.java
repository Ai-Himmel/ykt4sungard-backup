package org.king.check.dao;

import java.io.Serializable;
import java.util.List;


import org.king.check.domain.Vacation;

public interface VacationDao {
	public List find(String query);
	 
	public Vacation get(Serializable id);
	
	public List getAll();
	
    public void save(Vacation transientInstance);
	
    public void update(Vacation transientInstance);
    
    public void delete(Vacation persistentInstance);

}
