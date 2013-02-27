package org.king.support.dao;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.support.domain.MonitorRuntimevariables;

import java.io.Serializable;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-9
 */
public interface MonitorRuntimevariablesDAO extends DAO {
    public List find(MyQuery myQuery);

    public List find(String query);

    public MonitorRuntimevariables get(Serializable id);

    public List getAll();

    public void save(MonitorRuntimevariables transientInstance);

    public void update(MonitorRuntimevariables transientInstance);

    public void delete(MonitorRuntimevariables persistentInstance);

    public void findMonitorRuntimevariablesByPage(DBPaginatedList page, MyQuery myQuery);

    public boolean isExistMonitorRuntimevariables(String varName);
}
