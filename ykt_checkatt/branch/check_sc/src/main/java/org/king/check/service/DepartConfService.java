package org.king.check.service;

import java.io.Serializable;
import java.util.List;
import java.util.Map;

import org.king.check.domain.TCheckWorkconfinfo;

public interface DepartConfService {
	public List find(String query);
	 
	public TCheckWorkconfinfo get(Serializable id);
	
	public List getAll();
	
	public void save(TCheckWorkconfinfo transientInstance);
	
    public void update(TCheckWorkconfinfo transientInstance);
    
    public void delete(TCheckWorkconfinfo persistentInstance);
    
    public List getDepartConfByDptId(String dptId);
    
    public List isExist(Map filter)throws Exception;
    
    public List search(Map filter)throws Exception;
    
    public Map getConfAndTimeId(String deptId,String confDate);
    
    public boolean ifExistDeptConf(String deptId,String workDate);

}
