package org.king.termdev.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.termdev.domain.MonitorDsrvscheduleddowntime;

public interface MonitorDsrvscheduleddowntimeDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorDsrvscheduleddowntime get(Serializable id);

	public List getAll();

	public void save(MonitorDsrvscheduleddowntime transientInstance);

	public void update(MonitorDsrvscheduleddowntime transientInstance);

	public void delete(MonitorDsrvscheduleddowntime persistentInstance);
	
	public boolean checkDsrvDowntime(Integer objectid,String nowtime);

}