package org.king.hostservice.dao;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.hostservice.domain.MonitorServiceCheck;

import java.io.Serializable;
import java.util.List;

public interface MonitorServiceCheckDAO extends DAO {

    public List find(MyQuery myQuery);

    public List find(String query);

    public MonitorServiceCheck get(Serializable id);

    public List getAll();

    public void save(MonitorServiceCheck transientInstance);

    public void update(MonitorServiceCheck transientInstance);

    public void delete(MonitorServiceCheck persistentInstance);

    public void findMonitorServiceCheckByPage(DBPaginatedList page, MyQuery myQuery);

    public void execute(final String hql);
}