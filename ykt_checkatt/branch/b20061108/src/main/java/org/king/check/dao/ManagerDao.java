package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Manager;
import org.king.framework.dao.MyQuery;

public interface ManagerDao {
public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Manager get(Serializable id);
	
	public List getAll();
	
	
  public void save(Manager manager);

  public void delete(Manager manager);

  public void update(Manager manager);

  //public Manager getManagerByManagerId(String managerId);
}