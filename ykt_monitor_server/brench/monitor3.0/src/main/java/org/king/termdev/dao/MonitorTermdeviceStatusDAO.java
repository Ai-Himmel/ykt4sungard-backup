package org.king.termdev.dao;

import java.io.Serializable;
import java.util.List;

import org.king.common.displaytag.DBPaginatedList;
import org.king.common.query.QueryTranslate;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.termdev.domain.MonitorTermdeviceStatus;

public interface MonitorTermdeviceStatusDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorTermdeviceStatus get(Serializable id);

	public List getAll();

	public void save(MonitorTermdeviceStatus transientInstance);

	public void update(MonitorTermdeviceStatus transientInstance);

	public void delete(MonitorTermdeviceStatus persistentInstance);

    public void findMonitorTermdeviceStatusByPage(DBPaginatedList page, MyQuery myQuery);
}