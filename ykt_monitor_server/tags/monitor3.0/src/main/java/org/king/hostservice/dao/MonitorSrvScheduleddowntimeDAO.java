package org.king.hostservice.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.hostservice.domain.MonitorSrvScheduleddowntime;

public interface MonitorSrvScheduleddowntimeDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorSrvScheduleddowntime get(Serializable id);

	public List getAll();

	public void save(MonitorSrvScheduleddowntime transientInstance);

	public void update(MonitorSrvScheduleddowntime transientInstance);

	public void delete(MonitorSrvScheduleddowntime persistentInstance);
	
	public boolean checkSrvDowntime(Integer objectid,String nowtime);

}