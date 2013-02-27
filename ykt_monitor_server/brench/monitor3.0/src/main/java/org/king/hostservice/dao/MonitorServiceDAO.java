package org.king.hostservice.dao;

import java.io.Serializable;
import java.util.List;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.hostservice.domain.MonitorService;
import org.king.hostservice.domain.MonitorServiceAll;

public interface MonitorServiceDAO extends DAO {

    public List find(MyQuery myQuery);

    public List find(String query);

    public MonitorService get(Serializable id);
    public MonitorServiceAll getServiceAll(Serializable id);

    public List getAll();

    public void save(MonitorService transientInstance);

    public void update(MonitorService transientInstance);
    
    public void updateServiceAll(MonitorServiceAll transientInstance);

    public void delete(MonitorService persistentInstance);

    public void findMonitorServiceByPage(DBPaginatedList page, MyQuery myQuery);

    public boolean isExistMonitorService(String serviceName);
}