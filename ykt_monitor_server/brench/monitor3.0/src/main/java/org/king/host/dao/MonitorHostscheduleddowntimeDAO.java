package org.king.host.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.host.domain.MonitorHostscheduleddowntime;

public interface MonitorHostscheduleddowntimeDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorHostscheduleddowntime get(Serializable id);

	public List getAll();

	public void save(MonitorHostscheduleddowntime transientInstance);

	public void update(MonitorHostscheduleddowntime transientInstance);

	public void delete(MonitorHostscheduleddowntime persistentInstance);
	
	public boolean checkHostDowntime(Integer objectid,String nowtime);

}