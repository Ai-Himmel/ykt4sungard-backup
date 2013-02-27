package org.king.template.dao;

import java.io.Serializable;
import java.util.List;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.template.domain.MonitorTimePeriods;

public interface MonitorTimePeriodsDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorTimePeriods get(Serializable id);

	public List getAll();

	public void save(MonitorTimePeriods transientInstance);

	public void update(MonitorTimePeriods transientInstance);

	public void delete(MonitorTimePeriods persistentInstance);

    public void findMonitorTimePeriodsByPage(DBPaginatedList page, MyQuery myQuery);

    public boolean isExistMonitorTimePeriods(String alias);
}