package org.king.support.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.support.domain.MonitorCommands;


public interface MonitorCommandsDAO extends DAO{

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorCommands get(Serializable id);

	public List getAll();

	public void save(MonitorCommands transientInstance);

	public void update(MonitorCommands transientInstance);

	public void delete(MonitorCommands persistentInstance);

}