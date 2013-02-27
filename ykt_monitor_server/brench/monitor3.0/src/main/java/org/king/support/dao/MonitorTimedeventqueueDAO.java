package org.king.support.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.support.domain.MonitorTimedeventqueue;


public interface MonitorTimedeventqueueDAO extends DAO{

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorTimedeventqueue get(Serializable id);

	public List getAll();

	public void save(MonitorTimedeventqueue transientInstance);

	public void update(MonitorTimedeventqueue transientInstance);

	public void delete(MonitorTimedeventqueue persistentInstance);
	
	public MonitorTimedeventqueue findMonitorTimedeventqueueByObjectAndType(Integer objectId,Integer eventType);

}