package org.king.check.dao;
import java.io.Serializable;
import java.util.List;

import org.king.check.domain.TArea;
import org.king.framework.dao.DAO;
public  interface AreaDAO extends DAO{
	
	public List findArea(String  query);
	
	public TArea get(Serializable id);

}
