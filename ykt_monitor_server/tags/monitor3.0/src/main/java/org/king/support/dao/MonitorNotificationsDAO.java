package org.king.support.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.support.domain.MonitorCommands;
import org.king.support.domain.MonitorNotifications;


public interface MonitorNotificationsDAO extends DAO{

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorNotifications get(Serializable id);

	public List getAll();

	public void save(MonitorNotifications transientInstance);

	public void update(MonitorNotifications transientInstance);

	public void delete(MonitorNotifications persistentInstance);

}