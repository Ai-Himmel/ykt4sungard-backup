package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Tcheckattinfo;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

public interface DutyTimeDAO extends DAO{

    public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Tcheckattinfo get(Serializable id);
	
	public List getAll();
	
	public void save(Tcheckattinfo transientInstance);
	
    public void update(Tcheckattinfo transientInstance);
    
    public void delete(Tcheckattinfo persistentInstance);
}
