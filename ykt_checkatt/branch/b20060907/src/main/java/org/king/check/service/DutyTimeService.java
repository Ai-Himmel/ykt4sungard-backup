package org.king.check.service;

import java.io.Serializable;
import java.util.List;
import java.util.Map;

import org.king.check.domain.Clerk;
import org.king.check.domain.DutyTime;
import org.king.framework.dao.MyQuery;

public interface DutyTimeService {
    public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public DutyTime get(Serializable id);
	
	public List getAll();
	
	public void save(DutyTime transientInstance);
	
    public void update(DutyTime transientInstance);
    
    public void delete(DutyTime persistentInstance);
    
    public List searchInfo(Map filter)throws Exception;
    
    public Integer getRecordCount(Map filter) throws Exception;
    
    public Map searchForNewFormat(Map filter)throws Exception;
   
}
