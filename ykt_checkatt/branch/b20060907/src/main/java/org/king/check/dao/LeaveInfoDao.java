package org.king.check.dao;


import java.io.Serializable;
import java.util.Date;
import java.util.List;

import org.king.check.domain.Leaveinfo;
import org.king.framework.dao.MyQuery;


public interface LeaveInfoDao {

public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Leaveinfo get(Serializable id);
	
	public List getAll();
	
	public void save(Leaveinfo transientInstance);
	
    public void update(Leaveinfo transientInstance);
    
    public void delete(Leaveinfo persistentInstance);
    
 /* public void saveLeaveInfo(Leaveinfo leaveInfo);

  public Leaveinfo getLeaveInfoByLeaveInfoId();

  public List getLeaveInfosByUserId(String userId);

  public List getLeaveInfosByTime(Date startDate, Date endDate);*/
}