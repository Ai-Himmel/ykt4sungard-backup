package org.king.check.dao;


import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Attserial;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

public interface AttserialDAO extends DAO {

	public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Attserial get(Serializable id);
	
	public List getAll();
	

}