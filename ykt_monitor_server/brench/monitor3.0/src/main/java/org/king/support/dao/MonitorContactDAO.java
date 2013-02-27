package org.king.support.dao;

import java.io.Serializable;
import java.util.List;

import org.king.common.displaytag.DBPaginatedList;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.support.domain.MonitorContact;


public interface MonitorContactDAO extends DAO{

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorContact get(Serializable id);

	public List getAll();
	
	public List findContactBygroup(Integer groupid);

	public void save(MonitorContact transientInstance);

	public void update(MonitorContact transientInstance);

	public void delete(MonitorContact persistentInstance);

    public void findMonitorContactByPage(DBPaginatedList page, MyQuery myQuery);

    public boolean isExistMonitorContact(String contactName);
}