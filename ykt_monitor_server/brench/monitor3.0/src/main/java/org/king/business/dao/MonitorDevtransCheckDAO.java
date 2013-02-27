package org.king.business.dao;

import java.io.Serializable;
import java.util.List;

import org.king.business.domain.MonitorDevtransCheck;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

public interface MonitorDevtransCheckDAO extends DAO {

	public abstract void setBaseDAO(BaseDAO baseDAO);

	public abstract List find(MyQuery myQuery);

	public abstract List find(String query);

	public abstract MonitorDevtransCheck get(Serializable id);

	public abstract List getAll();

	public abstract void save(MonitorDevtransCheck transientInstance);

	public abstract void update(MonitorDevtransCheck transientInstance);

	public abstract void delete(MonitorDevtransCheck persistentInstance);

}