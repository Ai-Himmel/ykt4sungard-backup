package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.TCheckLocation;
import org.king.framework.dao.MyQuery;

public interface CheckLocationDAO {

	public abstract List find(MyQuery myQuery);

	public abstract List find(String query);

	public abstract TCheckLocation get(Serializable id);

	public abstract List getAll();

	public abstract void save(TCheckLocation transientInstance);

	public abstract void update(TCheckLocation transientInstance);

	public abstract void delete(TCheckLocation persistentInstance);

}