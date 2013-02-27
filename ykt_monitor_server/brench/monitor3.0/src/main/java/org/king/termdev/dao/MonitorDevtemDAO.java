package org.king.termdev.dao;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.termdev.domain.MonitorDevtem;

import java.io.Serializable;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-8-2
 */
public interface MonitorDevtemDAO extends DAO {
    public List find(MyQuery myQuery);

    public List find(String query);

    public MonitorDevtem get(Serializable id);

    public List getAll();

    public void save(MonitorDevtem transientInstance);

    public void update(MonitorDevtem transientInstance);

    public void delete(MonitorDevtem persistentInstance);

    public void findTDeviceByPage(DBPaginatedList page, MyQuery myQuery);

    public boolean isExistMonitorDevtem(Integer deviceid);

    public List findBySql(String sql);
}
