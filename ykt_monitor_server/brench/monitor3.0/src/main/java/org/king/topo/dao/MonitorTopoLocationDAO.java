package org.king.topo.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.topo.domain.MonitorTopoLocation;

public interface MonitorTopoLocationDAO extends DAO {
	
	public abstract List find(MyQuery myQuery);

	public abstract List find(String query);

	public abstract MonitorTopoLocation get(Serializable id);

	public abstract List getAll();

	public abstract void save(MonitorTopoLocation transientInstance);

	public abstract void update(MonitorTopoLocation transientInstance);

	public abstract void delete(MonitorTopoLocation persistentInstance);

}