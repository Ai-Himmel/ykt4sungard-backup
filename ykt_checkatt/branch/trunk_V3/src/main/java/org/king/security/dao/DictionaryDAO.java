package org.king.security.dao;

import java.io.Serializable;
import java.util.List;

import org.king.security.domain.Dictionary;
import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;

public interface DictionaryDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public Dictionary get(Serializable id);

	public List getAll();

	public void save(Dictionary transientInstance);

	public void update(Dictionary transientInstance);

	public void delete(Dictionary persistentInstance);

}
