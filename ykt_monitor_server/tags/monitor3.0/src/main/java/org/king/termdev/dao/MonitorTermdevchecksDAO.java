package org.king.termdev.dao;

import org.king.common.displaytag.DBPaginatedList;
import org.king.common.query.QueryTranslate;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.termdev.domain.MonitorTermdevchecks;

import java.io.Serializable;
import java.util.List;

public interface MonitorTermdevchecksDAO extends DAO {

    public List find(MyQuery myQuery);

    public List find(String query);

    public MonitorTermdevchecks get(Serializable id);

    public List getAll();

    public void save(MonitorTermdevchecks transientInstance);

    public void update(MonitorTermdevchecks transientInstance);

    public void delete(MonitorTermdevchecks persistentInstance);

    public void findMonitorTermdevchecksByPage(DBPaginatedList page, MyQuery myQuery);
}