package org.king.check.service;

import java.io.Serializable;
import java.util.List;
import java.util.Map;

import org.king.check.domain.Irregularrest;
import org.king.framework.dao.MyQuery;

public interface IrregularRestService {
    public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Irregularrest get(Serializable id);
	
	public List getAll();
	
	public void save(Irregularrest transientInstance);
	
    public void update(Irregularrest transientInstance);
    
    public void delete(Irregularrest persistentInstance);
    
    public List register(Map filter)throws Exception;
    
    public List searchIrregular(Map filter)throws Exception;
    
    public void updateIrregular(Map filter)throws Exception;
    
    public void deleteIrregular(String ids[])throws Exception;

}
