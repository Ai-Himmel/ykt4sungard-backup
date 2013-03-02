package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.king.check.dao.TermDAO;
import org.king.check.domain.TTerm;
import org.king.framework.dao.BaseDAO;

public class TermDAOHibernate implements TermDAO{

	private BaseDAO baseDAO;
	
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}


	public List find(String query) {
		return baseDAO.findEntity(query);
	}

	
	public void save(TTerm term) {
		baseDAO.saveEntity(term);
	}
	
	public TTerm get(Serializable id){
		return (TTerm)baseDAO.getEntity(TTerm.class, id);
	}
	
	public void update(TTerm term){
		baseDAO.updateEntity(term);
	}

}
