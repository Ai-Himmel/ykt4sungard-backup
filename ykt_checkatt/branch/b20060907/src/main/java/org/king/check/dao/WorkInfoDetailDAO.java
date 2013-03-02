package org.king.check.dao;

import java.io.Serializable;
import java.util.List;


import org.king.check.domain.Workinfodetail;

public interface WorkInfoDetailDAO {
	public List find(String query);
	 
	public Workinfodetail get(Serializable id);
	
	public List getAll();
  public void save(Workinfodetail workInfo);

  public void update(Workinfodetail workInfo);
  
  public void delete(Workinfodetail workInfo);
}
