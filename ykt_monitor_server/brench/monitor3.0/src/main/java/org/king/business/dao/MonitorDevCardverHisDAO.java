package org.king.business.dao;

import java.io.Serializable;
import java.util.List;

import org.king.business.domain.MonitorDevCardverHis;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

public interface MonitorDevCardverHisDAO extends DAO {

	public abstract void setBaseDAO(BaseDAO baseDAO);

	public abstract List find(MyQuery myQuery);

	public abstract List find(String query);

	public abstract MonitorDevCardverHis get(Serializable id);

	public abstract List getAll();

	public abstract void save(MonitorDevCardverHis transientInstance);

	public abstract void update(MonitorDevCardverHis transientInstance);

	public abstract void delete(MonitorDevCardverHis persistentInstance);

}