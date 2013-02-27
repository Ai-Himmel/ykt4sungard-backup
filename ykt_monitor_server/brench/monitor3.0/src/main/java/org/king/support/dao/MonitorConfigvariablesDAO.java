package org.king.support.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.support.domain.MonitorConfigvariables;


public interface MonitorConfigvariablesDAO extends DAO{

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorConfigvariables get(Serializable id);

	public List getAll();

	public void save(MonitorConfigvariables transientInstance);

	public void update(MonitorConfigvariables transientInstance);

	public void delete(MonitorConfigvariables persistentInstance);

}