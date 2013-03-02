package org.king.check.dao;

import java.io.Serializable;
import java.util.List;

import org.king.check.domain.Tworkconfinfo;
import org.king.framework.dao.MyQuery;

public interface WorkConfDao {

	public List find(MyQuery myQuery);

	public List find(String query);

	public Tworkconfinfo get(Serializable id);

	public List getAll();

	public void save(Tworkconfinfo workConf);

	public void update(Tworkconfinfo workConf);

	public void delete(Tworkconfinfo persistentInstance);

}