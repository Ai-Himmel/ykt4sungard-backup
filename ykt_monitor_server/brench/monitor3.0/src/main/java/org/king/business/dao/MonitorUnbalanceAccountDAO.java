package org.king.business.dao;

import java.io.Serializable;
import java.util.List;

import org.king.business.domain.MonitorUnbalanceAccount;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

public interface MonitorUnbalanceAccountDAO extends DAO {

	public abstract void setBaseDAO(BaseDAO baseDAO);

	public abstract List find(MyQuery myQuery);

	public abstract List find(String query);

	public abstract MonitorUnbalanceAccount get(Serializable id);

	public abstract List getAll();

	public abstract void save(MonitorUnbalanceAccount transientInstance);

	public abstract void update(MonitorUnbalanceAccount transientInstance);

	public abstract void delete(MonitorUnbalanceAccount persistentInstance);

}