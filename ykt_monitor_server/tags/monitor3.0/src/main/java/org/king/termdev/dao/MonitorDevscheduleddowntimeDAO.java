package org.king.termdev.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.termdev.domain.MonitorDevscheduleddowntime;

public interface MonitorDevscheduleddowntimeDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorDevscheduleddowntime get(Serializable id);

	public List getAll();

	public void save(MonitorDevscheduleddowntime transientInstance);

	public void update(MonitorDevscheduleddowntime transientInstance);

	public void delete(MonitorDevscheduleddowntime persistentInstance);
	
	public boolean checkDevDowntime(Integer objectid,String nowtime);

}