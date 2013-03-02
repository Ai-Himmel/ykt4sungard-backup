package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.CheckTypeDAO;
import org.king.check.domain.TChecktype;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class DepartConf.
 * 
 * @see org.king.check.dao.hibernate.DepartConf
 * @author MyEclipse - Hibernate Tools
 */
public class CheckTypeDAOHibernate implements CheckTypeDAO {

	private static final Log log = LogFactory
			.getLog(CheckTypeDAOHibernate.class);

	protected void initDao() {
		// do nothing
	}

	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public List find(MyQuery myQuery) {
		return baseDAO.findEntity(myQuery);
	}

	public List find(String query) {
		return baseDAO.findEntity(query);
	}

	public TChecktype get(Serializable id) {
		return (TChecktype) baseDAO.getEntity(TChecktype.class, id);
	}

	public List getAll() {
		String allHql = "from Tchecktype";
		return baseDAO.findEntity(allHql);
	}

	public void save(TChecktype transientInstance) {
		baseDAO.saveEntity(transientInstance);
	}

	public void update(TChecktype transientInstance) {
		baseDAO.updateEntity(transientInstance);
	}

	public void delete(TChecktype persistentInstance) {
		log.debug("deleting checkType instance");
		baseDAO.removeEntity(persistentInstance);
	}

}