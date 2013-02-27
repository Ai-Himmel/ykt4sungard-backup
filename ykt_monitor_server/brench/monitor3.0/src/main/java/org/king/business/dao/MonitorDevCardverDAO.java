package org.king.business.dao;

import java.io.Serializable;
import java.util.List;

import org.king.business.domain.MonitorDevCardver;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

public interface MonitorDevCardverDAO extends DAO {

	public abstract void setBaseDAO(BaseDAO baseDAO);

	public abstract List find(MyQuery myQuery);

	public abstract List find(String query);

	public abstract MonitorDevCardver get(Serializable id);

	public abstract List getAll();

	public abstract void save(MonitorDevCardver transientInstance);

	public abstract void update(MonitorDevCardver transientInstance);

	public abstract void delete(MonitorDevCardver persistentInstance);

}