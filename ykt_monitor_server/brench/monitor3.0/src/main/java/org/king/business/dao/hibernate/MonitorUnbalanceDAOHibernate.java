package org.king.business.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.king.business.dao.MonitorUnbalanceDAO;
import org.king.business.domain.MonitorUnbalance;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * A data access object (DAO) providing persistence and search support for
 * MonitorUnbalance entities. Transaction control of the save(), update() and
 * delete() operations can directly support Spring container-managed
 * transactions or they can be augmented to handle user-managed Spring
 * transactions. Each of these methods provides additional information for how
 * to configure it for the desired type of transaction control.
 * 
 * @see org.king.topo.domain.MonitorUnbalance
 * @author MyEclipse Persistence Tools
 */

public class MonitorUnbalanceDAOHibernate implements MonitorUnbalanceDAO {
	private static final Logger log = LoggerFactory
			.getLogger(MonitorUnbalanceDAOHibernate.class);

	private BaseDAO baseDAO;

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorUnbalanceDAO#setBaseDAO(org.king.framework
	 * .dao.BaseDAO)
	 */
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorUnbalanceDAO#find(org.king.framework
	 * .dao.MyQuery)
	 */
	public List find(MyQuery myQuery) {
		log.debug("finding MonitorUnbalance instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorUnbalanceDAO#find(java.lang.String)
	 */
	public List find(String query) {
		log.debug("finding MonitorUnbalance instance by query");
		return baseDAO.findEntity(query);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorUnbalanceDAO#get(java.io.Serializable)
	 */
	public MonitorUnbalance get(Serializable id) {
		log.debug("getting MonitorUnbalance instance by id");
		return (MonitorUnbalance) baseDAO.getEntity(MonitorUnbalance.class, id);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.topo.dao.hibernate.MonitorUnbalanceDAO#getAll()
	 */
	public List getAll() {
		log.debug("getting MonitorUnbalance all");
		String allHql = "from MonitorUnbalance";
		return baseDAO.findEntity(allHql);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorUnbalanceDAO#save(org.king.topo.domain
	 * .MonitorUnbalance)
	 */
	public void save(MonitorUnbalance transientInstance) {
		log.debug("saving MonitorUnbalance instance");
		baseDAO.saveEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorUnbalanceDAO#update(org.king.topo.
	 * domain.MonitorUnbalance)
	 */
	public void update(MonitorUnbalance transientInstance) {
		log.debug("updating MonitorUnbalance instance");
		baseDAO.updateEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorUnbalanceDAO#delete(org.king.topo.
	 * domain.MonitorUnbalance)
	 */
	public void delete(MonitorUnbalance persistentInstance) {
		log.debug("deleting MonitorUnbalance instance");
		baseDAO.removeEntity(persistentInstance);
	}
}