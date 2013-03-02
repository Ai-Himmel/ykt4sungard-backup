package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Tworktimeinfo;
import org.king.framework.dao.MyQuery;



public interface WorkTimeConfDao {

	public void save( Tworktimeinfo workTimeConf);

	public void update( Tworktimeinfo workTimeConf);

	public void delete(Tworktimeinfo workTimeConf);

	public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Tworktimeinfo get(Serializable id);

	public List getAll();

}