package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.TChecktype;

public interface CheckTypeDAO {
	public List find(String query);
	 
	public TChecktype get(Serializable id);
	
	public List getAll();
	
	public void save(TChecktype transientInstance);
	
    public void update(TChecktype transientInstance);
    
    public void delete(TChecktype persistentInstance);
}
