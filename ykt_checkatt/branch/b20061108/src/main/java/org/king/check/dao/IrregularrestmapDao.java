package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Irregularrestmap;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;


public interface IrregularrestmapDao extends DAO {
public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Irregularrestmap get(Serializable id);
	
	public List getAll();
	
	public void save(Irregularrestmap transientInstance);
	
    public void update(Irregularrestmap transientInstance);
    
    public void delete(Irregularrestmap persistentInstance);
}
