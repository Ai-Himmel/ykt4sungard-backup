package org.king.check.service;

import java.io.Serializable;
import java.util.List;
import java.util.Map;

import org.king.check.domain.Tdeptworkconfinfo;

public interface DepartConfService {
	public List find(String query);
	 
	public Tdeptworkconfinfo get(Serializable id);
	
	public List getAll();
	
	public void save(Tdeptworkconfinfo transientInstance);
	
    public void update(Tdeptworkconfinfo transientInstance);
    
    public void delete(Tdeptworkconfinfo persistentInstance);
    
    public List getDepartConfByDptId(String dptId);
    
    public List isExist(Map filter)throws Exception;
    
    public List search(Map filter)throws Exception;
    
    public Map getConfAndTimeId(String deptId,String confDate);
    
    public boolean ifExistDeptConf(String deptId,String workDate);

}
