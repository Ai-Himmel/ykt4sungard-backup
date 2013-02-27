package org.king.termdev.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.termdev.domain.MonitorTermdevserviceChecks;

public interface MonitorTermdevserviceChecksDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public MonitorTermdevserviceChecks get(Serializable id);

	public List getAll();

	public void save(MonitorTermdevserviceChecks transientInstance);

	public void update(MonitorTermdevserviceChecks transientInstance);

	public void delete(MonitorTermdevserviceChecks persistentInstance);

}