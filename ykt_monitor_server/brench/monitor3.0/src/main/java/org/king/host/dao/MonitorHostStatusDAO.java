package org.king.host.dao;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.host.domain.MonitorHostStatus;

import java.io.Serializable;
import java.util.List;

public interface MonitorHostStatusDAO extends DAO {

    public List find(MyQuery myQuery);

    public List find(String query);

    public MonitorHostStatus get(Serializable id);

    public List getAll();

    public void save(MonitorHostStatus transientInstance);

    public void update(MonitorHostStatus transientInstance);

    public void delete(MonitorHostStatus persistentInstance);

    public void findMonitorHostStatusByPage(DBPaginatedList page, MyQuery myQuery);

    public void execute(final String hql);

}