package org.king.topo.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.topo.domain.MonitorTopoDeviceGroup;

public interface MonitorTopoDeviceGroupDAO extends DAO {
	
	public abstract List find(MyQuery myQuery);

	public abstract List find(String query);

	public abstract MonitorTopoDeviceGroup get(Serializable id);

	public abstract List getAll();

	public abstract void save(MonitorTopoDeviceGroup transientInstance);

	public abstract void update(MonitorTopoDeviceGroup transientInstance);

	public abstract void delete(MonitorTopoDeviceGroup persistentInstance);

    public List findBySql(String sql);
}