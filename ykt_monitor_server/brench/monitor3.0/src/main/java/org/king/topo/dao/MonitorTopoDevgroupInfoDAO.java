package org.king.topo.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.topo.domain.MonitorTopoDevgroupInfo;

public interface MonitorTopoDevgroupInfoDAO extends DAO {

	public abstract List find(MyQuery myQuery);

	public abstract List find(String query);

	public abstract MonitorTopoDevgroupInfo get(Serializable id);

	public abstract List getAll();
	
	public List getDevgroupInfoByGroupid(Integer groupid);

	public abstract void save(MonitorTopoDevgroupInfo transientInstance);

	public abstract void update(MonitorTopoDevgroupInfo transientInstance);

	public abstract void delete(MonitorTopoDevgroupInfo persistentInstance);

}