package org.king.host.dao;

import java.io.Serializable;
import java.util.List;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.host.domain.MonitorHost;
import org.king.host.domain.MonitorHostAll;

public interface MonitorHostDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorHost get(Serializable id);
	public MonitorHostAll getHostAll(Serializable id);

	public List getAll();

	public void save(MonitorHost transientInstance);

	public void update(MonitorHost transientInstance);
	public void updateHostAll(MonitorHostAll transientInstance);

	public void delete(MonitorHost persistentInstance);

    public void findMonitorHostByPage(DBPaginatedList page, MyQuery myQuery);

    public boolean isExistMonitorHost(String hostAddress);
}