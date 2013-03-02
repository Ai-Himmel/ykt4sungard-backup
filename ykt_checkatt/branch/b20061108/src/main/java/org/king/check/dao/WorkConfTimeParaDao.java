package org.king.check.dao;


import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Worktimepara;
import org.king.framework.dao.MyQuery;


public interface WorkConfTimeParaDao {

public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Worktimepara get(Serializable id);
  public void save(Worktimepara workTimePara);

  public void update(Worktimepara workTimePara);

  public void delete(Worktimepara workTimepara);

  //public Worktimepara getWorkTimePara(String workTimeParaId);

  public List getAll();

  //public void saveMap(String workTimeConfParaId, String workTimeConf);
}