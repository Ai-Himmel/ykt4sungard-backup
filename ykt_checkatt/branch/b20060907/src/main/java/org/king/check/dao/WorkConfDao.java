package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Workconf;
import org.king.framework.dao.MyQuery;




public interface WorkConfDao {
	
public List find(MyQuery myQuery);
	
public List find(String query);
	 
	public Workconf get(Serializable id);
	
	public List getAll();
  public void save(Workconf workConf);

  public void update(Workconf workConf);

  public void delete(Workconf persistentInstance);

/*  public Workconf getWorkConf(String workConfId);

  public void saveUserAndWorkConfMap(String userId, String workConfId);*/
}