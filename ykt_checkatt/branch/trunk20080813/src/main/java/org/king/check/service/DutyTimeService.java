package org.king.check.service;

import java.util.List;
import java.util.Map;

import org.king.framework.dao.MyQuery;

public interface DutyTimeService {
    public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public List getAll();
	
    public Map searchForNewFormat(Map filter)throws Exception;
    
    public List getNoSeatList(Map filter)throws Exception;
   
}
