package org.king.termdev.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.termdev.domain.MonitorDevservicecomments;

public interface MonitorDevservicecommentsDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorDevservicecomments get(Serializable id);

	public List getAll();

	public void save(MonitorDevservicecomments transientInstance);

	public void update(MonitorDevservicecomments transientInstance);

	public void delete(MonitorDevservicecomments persistentInstance);

}