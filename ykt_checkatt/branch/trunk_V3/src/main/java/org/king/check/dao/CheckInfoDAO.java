package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.TCheckInfo;
import org.king.framework.dao.MyQuery;

public interface CheckInfoDAO {

	public abstract List find(MyQuery myQuery);

	public abstract List find(String query);

	public abstract TCheckInfo get(Serializable id);

	public abstract List getAll();

	public abstract void save(TCheckInfo transientInstance);

	public abstract void update(TCheckInfo transientInstance);

	public abstract void delete(TCheckInfo persistentInstance);

}