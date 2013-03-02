package org.king.check.service;

import java.io.Serializable;
import java.util.List;
import java.util.Map;

import org.king.check.domain.Extraworkinfo;
import org.king.framework.dao.MyQuery;

public interface ExtraWorkService {

    public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Extraworkinfo get(Serializable id);
	
	public List getAll();
	
	public void save(Extraworkinfo transientInstance);
	
    public void update(Extraworkinfo transientInstance);
    
    public void delete(Extraworkinfo persistentInstance);
    
    public List addExtraWork(Map filter)throws Exception;
    
    public List searchExtraWork(Map filter)throws Exception;
    
    public void updateExtraInfo(Map filter)throws Exception;
    
    public void deleteExtraInfo(String ids[])throws Exception;
    
    public List staticExtraInfo(Map filter)throws Exception;
    
    public Integer getExtraDays(Map filter)throws Exception;
    
    public List getExtraWorkDetail(Map filter)throws Exception;
    
    
}
