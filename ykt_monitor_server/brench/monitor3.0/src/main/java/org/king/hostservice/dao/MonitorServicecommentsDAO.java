package org.king.hostservice.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.hostservice.domain.MonitorServicecoments;

public interface MonitorServicecommentsDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorServicecoments get(Serializable id);

	public List getAll();

	public void save(MonitorServicecoments transientInstance);

	public void update(MonitorServicecoments transientInstance);

	public void delete(MonitorServicecoments persistentInstance);

}