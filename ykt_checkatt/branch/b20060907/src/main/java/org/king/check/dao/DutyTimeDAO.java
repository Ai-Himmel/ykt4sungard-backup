package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.DutyTime;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

public interface DutyTimeDAO extends DAO{

    public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public DutyTime get(Serializable id);
	
	public List getAll();
	
	public void save(DutyTime transientInstance);
	
    public void update(DutyTime transientInstance);
    
    public void delete(DutyTime persistentInstance);
}
