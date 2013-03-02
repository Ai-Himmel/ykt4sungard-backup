package org.king.check.dao.hibernate;

import org.king.check.dao.DictionaryDao;
import org.king.check.domain.WebDictionary;
import org.king.framework.dao.BaseDAO;

public class DictionaryHibernate implements DictionaryDao {

	protected void initDao() {
		// do nothing
	}

	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}
	
	public void update(WebDictionary dic){
		baseDAO.updateEntity(dic);
	}
	
	public void delete(WebDictionary dic){
		baseDAO.removeEntity(dic);
	
	}
	public void save(WebDictionary dic){
		baseDAO.saveEntity(dic);
	}
	

}
