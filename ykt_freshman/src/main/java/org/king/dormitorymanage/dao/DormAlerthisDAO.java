package org.king.dormitorymanage.dao;

import java.io.Serializable;
import java.util.List;

import org.king.dormitorymanage.domain.DormAlerthis;
import org.king.framework.dao.MyQuery;

public interface DormAlerthisDAO {
	public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public DormAlerthis get(Serializable id);
	
	public List getAll();
	
	public void save(DormAlerthis transientInstance);
	
    public void update(DormAlerthis transientInstance);
    
    public void delete(DormAlerthis persistentInstance);
    
}
