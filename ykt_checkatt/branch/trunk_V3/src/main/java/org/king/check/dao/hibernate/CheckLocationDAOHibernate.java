package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.CheckLocationDAO;
import org.king.check.domain.TCheckLocation;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * A data access object (DAO) providing persistence and search support for
 * TCheckLocation entities. Transaction control of the save(), update() and
 * delete() operations can directly support Spring container-managed
 * transactions or they can be augmented to handle user-managed Spring
 * transactions. Each of these methods provides additional information for how
 * to configure it for the desired type of transaction control.
 * 
 * @see org.king.check.domain.TCheckLocation
 * @author MyEclipse Persistence Tools
 */

public class CheckLocationDAOHibernate implements CheckLocationDAO {
	private static final Log log = LogFactory.getLog(CheckLocationDAOHibernate.class);

	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckLocationDAO#find(org.king.framework.dao.MyQuery)
	 */
	public List find(MyQuery myQuery) {
		log.debug("finding TCheckLocation instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckLocationDAO#find(java.lang.String)
	 */
	public List find(String query) {
		log.debug("finding TCheckLocation instance by query");
		return baseDAO.findEntity(query);
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckLocationDAO#get(java.io.Serializable)
	 */
	public TCheckLocation get(Serializable id) {
		log.debug("getting TCheckLocation instance by id");
		return (TCheckLocation) baseDAO.getEntity(TCheckLocation.class, id);
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckLocationDAO#getAll()
	 */
	public List getAll() {
		log.debug("getting TCheckLocation all");
		String allHql = "from TCheckLocation";
		return baseDAO.findEntity(allHql);
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckLocationDAO#save(org.test.TCheckLocation)
	 */
	public void save(TCheckLocation transientInstance) {
		log.debug("saving TCheckLocation instance");
		baseDAO.saveEntity(transientInstance);
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckLocationDAO#update(org.test.TCheckLocation)
	 */
	public void update(TCheckLocation transientInstance) {
		log.debug("updating TCheckLocation instance");
		baseDAO.updateEntity(transientInstance);
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckLocationDAO#delete(org.test.TCheckLocation)
	 */
	public void delete(TCheckLocation persistentInstance) {
		log.debug("deleting TCheckLocation instance");
		baseDAO.removeEntity(persistentInstance);
	}
}