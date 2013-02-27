package org.king.host.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.host.domain.MonitorHostcomments;

public interface MonitorHostcommentsDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorHostcomments get(Serializable id);

	public List getAll();

	public void save(MonitorHostcomments transientInstance);

	public void update(MonitorHostcomments transientInstance);

	public void delete(MonitorHostcomments persistentInstance);

}