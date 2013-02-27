package org.king.termdev.dao;

import java.io.Serializable;
import java.util.List;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.termdev.domain.MonitorTermdevService;

public interface MonitorTermdevServiceDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorTermdevService get(Serializable id);

	public List getAll();

	public void save(MonitorTermdevService transientInstance);

	public void update(MonitorTermdevService transientInstance);

	public void delete(MonitorTermdevService persistentInstance);

    public void findMonitorTermdevServiceByPage(DBPaginatedList page, MyQuery myQuery);

    public boolean isExistMonitorTermdevService(String devserviceName);
}