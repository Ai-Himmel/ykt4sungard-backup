package org.king.host.dao;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.host.domain.MonitorHostchecks;

import java.io.Serializable;
import java.util.List;

public interface MonitorHostchecksDAO extends DAO {

    public List find(MyQuery myQuery);

    public List find(String query);

    public MonitorHostchecks get(Serializable id);

    public List getAll();

    public void save(MonitorHostchecks transientInstance);

    public void update(MonitorHostchecks transientInstance);

    public void delete(MonitorHostchecks persistentInstance);

    public void findMonitorHostchecksByPage(DBPaginatedList page, MyQuery myQuery);

    public void execute(final String hql);
}