package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Irregularrest;
import org.king.framework.dao.MyQuery;


public interface IrregularrestDao {
public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Irregularrest get(Serializable id);
	
	public List getAll();
	
	public void save(Irregularrest transientInstance);
	
    public void update(Irregularrest transientInstance);
    
    public void delete(Irregularrest persistentInstance);
}
