package org.king.topo.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.topo.domain.MonitorDevWorktime;

public interface MonitorDevWorktimeDAO extends DAO {
	
	public abstract List find(MyQuery myQuery);

	public abstract List find(String query);

	public abstract MonitorDevWorktime get(Serializable id);

	public abstract List getAll();

	public abstract void save(MonitorDevWorktime transientInstance);

	public abstract void update(MonitorDevWorktime transientInstance);

	public abstract void delete(MonitorDevWorktime persistentInstance);

}