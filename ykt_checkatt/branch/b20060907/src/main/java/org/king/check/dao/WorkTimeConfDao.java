package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Worktimeconf;
import org.king.framework.dao.MyQuery;



public interface WorkTimeConfDao {

  public void save( Worktimeconf workTimeConf);

  public void update( Worktimeconf workTimeConf);

  public void delete(Worktimeconf workTimeConf);

  public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Worktimeconf get(Serializable id);
  //public Worktimeconf getWorkTimeConfByWorkConfTimeId(String workConfTimeId);

  public List getAll();

 // public Worktimeconf getWorkTimeConfByWorkConfTimeName(String workConfTimeName);
}