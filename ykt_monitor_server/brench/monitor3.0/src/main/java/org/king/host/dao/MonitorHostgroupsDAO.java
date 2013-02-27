package org.king.host.dao;

import java.io.Serializable;
import java.util.List;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.host.domain.MonitorHostgroups;

public interface MonitorHostgroupsDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorHostgroups get(Serializable id);

	public List getAll();

	public void save(MonitorHostgroups transientInstance);

	public void update(MonitorHostgroups transientInstance);

	public void delete(MonitorHostgroups persistentInstance);

    public void findMonitorHostgroupsByPage(DBPaginatedList page, MyQuery myQuery);

    public boolean isExistMonitorHostgroups(String groupName);

}