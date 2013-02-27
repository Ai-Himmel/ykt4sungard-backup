package org.king.support.dao;

import java.io.Serializable;
import java.util.List;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.support.domain.MonitorContactgroups;


public interface MonitorContactgroupsDAO extends DAO{

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorContactgroups get(Serializable id);

	public List getAll();

	public void save(MonitorContactgroups transientInstance);

	public void update(MonitorContactgroups transientInstance);

	public void delete(MonitorContactgroups persistentInstance);

    public void findMonitorContactgroupsByPage(DBPaginatedList page, MyQuery myQuery);

    public boolean isExistMonitorContactgroups(String groupName);

}