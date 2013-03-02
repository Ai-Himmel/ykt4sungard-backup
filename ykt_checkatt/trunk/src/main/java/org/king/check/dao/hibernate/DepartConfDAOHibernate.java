package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.DepartConfDAO;
import org.king.check.domain.Tdeptworkconfinfo;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class DepartConf.
 * 
 * @see org.king.check.dao.hibernate.DepartConf
 * @author MyEclipse - Hibernate Tools
 */
public class DepartConfDAOHibernate implements DepartConfDAO {

	private static final Log log = LogFactory
			.getLog(DepartConfDAOHibernate.class);

	protected void initDao() {
		// do nothing
	}

	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public List find(MyQuery myQuery) {
		// log.debug("finding DepartConf instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	public List find(String query) {
		// log.debug("finding DepartConf instance by query");
		return baseDAO.findEntity(query);
	}

	public Tdeptworkconfinfo get(Serializable id) {
		//log.debug("getting DepartConf instance by id");
		return (Tdeptworkconfinfo) baseDAO.getEntity(Tdeptworkconfinfo.class, id);
	}

	public List getAll() {
		//log.debug("getting DepartConf all");
		String allHql = "from Tdeptworkconfinfo";
		return baseDAO.findEntity(allHql);
	}

	public void save(Tdeptworkconfinfo transientInstance) {
		//log.debug("saving DepartConf instance");
		baseDAO.saveEntity(transientInstance);
	}

	public void update(Tdeptworkconfinfo transientInstance) {
		//log.debug("updating DepartConf instance");
		baseDAO.updateEntity(transientInstance);
	}

	public void delete(Tdeptworkconfinfo persistentInstance) {
		log.debug("deleting DepartConf instance");
		baseDAO.removeEntity(persistentInstance);
	}

}