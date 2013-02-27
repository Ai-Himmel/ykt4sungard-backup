package org.king.template.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.template.domain.MonitorTimeranger;

public interface MonitorTimerangerDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorTimeranger get(Serializable id);

	public List getAll();

	public void save(MonitorTimeranger transientInstance);

	public void update(MonitorTimeranger transientInstance);

	public void delete(MonitorTimeranger persistentInstance);

}