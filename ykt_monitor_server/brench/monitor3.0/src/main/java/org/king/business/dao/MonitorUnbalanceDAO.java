package org.king.business.dao;

import java.io.Serializable;
import java.util.List;

import org.king.business.domain.MonitorUnbalance;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

public interface MonitorUnbalanceDAO extends DAO {

	public abstract void setBaseDAO(BaseDAO baseDAO);

	public abstract List find(MyQuery myQuery);

	public abstract List find(String query);

	public abstract MonitorUnbalance get(Serializable id);

	public abstract List getAll();

	public abstract void save(MonitorUnbalance transientInstance);

	public abstract void update(MonitorUnbalance transientInstance);

	public abstract void delete(MonitorUnbalance persistentInstance);

}