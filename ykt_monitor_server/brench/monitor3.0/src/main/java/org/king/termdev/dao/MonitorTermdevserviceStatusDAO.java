package org.king.termdev.dao;

import java.io.Serializable;
import java.util.List;

import org.king.common.displaytag.DBPaginatedList;
import org.king.common.query.QueryTranslate;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.termdev.domain.MonitorTermdevserviceStatus;

public interface MonitorTermdevserviceStatusDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorTermdevserviceStatus get(Serializable id);

	public List getAll();

	public void save(MonitorTermdevserviceStatus transientInstance);

	public void update(MonitorTermdevserviceStatus transientInstance);

	public void delete(MonitorTermdevserviceStatus persistentInstance);

    public void findMonitorTermdevserviceStatusByPage(DBPaginatedList page, MyQuery myQuery);
}