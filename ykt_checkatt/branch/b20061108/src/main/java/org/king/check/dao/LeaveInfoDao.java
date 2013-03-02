package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Tleaveinfo;
import org.king.framework.dao.MyQuery;

public interface LeaveInfoDao {

	public List find(MyQuery myQuery);

	public List find(String query);

	public Tleaveinfo get(Serializable id);

	public List getAll();

	public void save(Tleaveinfo transientInstance);

	public void update(Tleaveinfo transientInstance);

	public void delete(Tleaveinfo persistentInstance);
}