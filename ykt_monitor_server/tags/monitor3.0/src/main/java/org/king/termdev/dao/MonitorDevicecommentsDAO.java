package org.king.termdev.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.termdev.domain.MonitorDevicecomments;

public interface MonitorDevicecommentsDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorDevicecomments get(Serializable id);

	public List getAll();

	public void save(MonitorDevicecomments transientInstance);

	public void update(MonitorDevicecomments transientInstance);

	public void delete(MonitorDevicecomments persistentInstance);

}