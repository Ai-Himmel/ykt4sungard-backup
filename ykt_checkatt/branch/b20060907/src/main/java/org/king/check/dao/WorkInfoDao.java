package org.king.check.dao;

import java.io.Serializable;
import java.util.Date;

import java.util.List;

import org.king.check.domain.Workinfo;
import org.king.framework.dao.MyQuery;


public interface WorkInfoDao {

public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Workinfo get(Serializable id);
	
	public List getAll();
  public void save(Workinfo workInfo);

  public void update(Workinfo workInfo);
  
  public void delete(Workinfo workInfo);

  /*public Workinfo getWorkInfoByWorkInfoId(String workInfoId);

  public Workinfo getWorkInfoBySerialId(String serialId);

  public List getWorkInfosByCardNumber(String CardNumber);

  public List getClerkWorkInfosByDate(Date startDate, Date endDate, String userId);

  public List getDepartWorkInfosByDate(Date startDate, Date endDate, String departId);*/
}