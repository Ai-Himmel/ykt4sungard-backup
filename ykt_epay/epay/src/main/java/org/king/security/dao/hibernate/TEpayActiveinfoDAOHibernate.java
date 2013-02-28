package org.king.security.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.security.dao.TEpayActiveinfoDAO;
import org.king.security.domain.TEpayActiveinfo;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class TEpayActiveinfoDAOHibernate implements TEpayActiveinfoDAO{

	private static final Logger log = LoggerFactory
	.getLogger(TEpayActiveinfoDAOHibernate.class);
	private BaseDAO baseDAO;
	
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public void delete(TEpayActiveinfo persistentInstance) {
		baseDAO.removeEntity(persistentInstance);
		
	}

	public List find(MyQuery myQuery) {
		// TODO Auto-generated method stub
		return baseDAO.findEntity(myQuery);
	}

	public List find(String query) {
		// TODO Auto-generated method stub
		return baseDAO.findEntity(query);
	}

	public TEpayActiveinfo get(Serializable id) {
		// TODO Auto-generated method stub
		return (TEpayActiveinfo)baseDAO.getEntity(TEpayActiveinfo.class, id);
	}

	public List getAll() {
		// TODO Auto-generated method stub
		return baseDAO.findEntity("from TEpayActiveinfo");
	}

	public void save(TEpayActiveinfo transientInstance) {
		baseDAO.saveEntity(transientInstance);
	}

	public void update(TEpayActiveinfo transientInstance) {
		baseDAO.updateEntity(transientInstance);
		
	}

}
