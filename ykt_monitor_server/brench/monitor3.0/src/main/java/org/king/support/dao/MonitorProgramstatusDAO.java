package org.king.support.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.support.domain.MonitorProgramstatus;


public interface MonitorProgramstatusDAO extends DAO{

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorProgramstatus get(Serializable id);

	public List getAll();

	public void save(MonitorProgramstatus transientInstance);

	public void update(MonitorProgramstatus transientInstance);

	public void delete(MonitorProgramstatus persistentInstance);

}