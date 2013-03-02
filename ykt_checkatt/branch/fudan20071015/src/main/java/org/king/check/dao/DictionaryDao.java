package org.king.check.dao;


import org.king.check.domain.WebDictionary;
import org.king.framework.dao.DAO;

public interface DictionaryDao extends DAO {

	public void update(WebDictionary dic);
	
	public void delete(WebDictionary dic);
	
	public void save(WebDictionary dic);

}
