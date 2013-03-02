package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.king.check.dao.AreaDAO;
import org.king.check.domain.TArea;
import org.king.framework.dao.BaseDAO;

public class AreaDAOHibernate implements AreaDAO{
	
	private BaseDAO baseDAO;

	public List findArea(String query) {
	    return 	baseDAO.findEntity(query);
	}

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public TArea get(Serializable id) {
		return (TArea)baseDAO.getEntity(TArea.class, id);
	}

}
