package org.king.hostservice.dao;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.hostservice.domain.MonitorServiceStatus;

import java.io.Serializable;
import java.util.List;

public interface MonitorServiceStatusDAO extends DAO {

    public List find(MyQuery myQuery);

    public List find(String query);

    public MonitorServiceStatus get(Serializable id);

    public List getAll();

    public void save(MonitorServiceStatus transientInstance);

    public void update(MonitorServiceStatus transientInstance);

    public void delete(MonitorServiceStatus persistentInstance);

    public void findMonitorServiceStatusByPage(DBPaginatedList page, MyQuery myQuery);

    public void execute(final String hql);
}