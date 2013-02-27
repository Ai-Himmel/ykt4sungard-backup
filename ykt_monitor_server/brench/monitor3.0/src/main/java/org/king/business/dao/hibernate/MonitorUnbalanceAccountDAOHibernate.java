package org.king.business.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.king.business.dao.MonitorUnbalanceAccountDAO;
import org.king.business.domain.MonitorUnbalanceAccount;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * A data access object (DAO) providing persistence and search support for
 * MonitorUnbalanceAccount entities. Transaction control of the save(), update()
 * and delete() operations can directly support Spring container-managed
 * transactions or they can be augmented to handle user-managed Spring
 * transactions. Each of these methods provides additional information for how
 * to configure it for the desired type of transaction control.
 * 
 * @see org.king.topo.domain.MonitorUnbalanceAccount
 * @author MyEclipse Persistence Tools
 */

public class MonitorUnbalanceAccountDAOHibernate implements
		MonitorUnbalanceAccountDAO {
	private static final Logger log = LoggerFactory
			.getLogger(MonitorUnbalanceAccountDAOHibernate.class);

	private BaseDAO baseDAO;

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorUnbalanceAccountDAO#setBaseDAO(org
	 * .king.framework.dao.BaseDAO)
	 */
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorUnbalanceAccountDAO#find(org.king.
	 * framework.dao.MyQuery)
	 */
	public List find(MyQuery myQuery) {
		log.debug("finding MonitorUnbalanceAccount instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorUnbalanceAccountDAO#find(java.lang
	 * .String)
	 */
	public List find(String query) {
		log.debug("finding MonitorUnbalanceAccount instance by query");
		return baseDAO.findEntity(query);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seeorg.king.topo.dao.hibernate.MonitorUnbalanceAccountDAO#get(java.io.
	 * Serializable)
	 */
	public MonitorUnbalanceAccount get(Serializable id) {
		log.debug("getting MonitorUnbalanceAccount instance by id");
		return (MonitorUnbalanceAccount) baseDAO.getEntity(
				MonitorUnbalanceAccount.class, id);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.topo.dao.hibernate.MonitorUnbalanceAccountDAO#getAll()
	 */
	public List getAll() {
		log.debug("getting MonitorUnbalanceAccount all");
		String allHql = "from MonitorUnbalanceAccount";
		return baseDAO.findEntity(allHql);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorUnbalanceAccountDAO#save(org.king.
	 * topo.domain.MonitorUnbalanceAccount)
	 */
	public void save(MonitorUnbalanceAccount transientInstance) {
		log.debug("saving MonitorUnbalanceAccount instance");
		baseDAO.saveEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorUnbalanceAccountDAO#update(org.king
	 * .topo.domain.MonitorUnbalanceAccount)
	 */
	public void update(MonitorUnbalanceAccount transientInstance) {
		log.debug("updating MonitorUnbalanceAccount instance");
		baseDAO.updateEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorUnbalanceAccountDAO#delete(org.king
	 * .topo.domain.MonitorUnbalanceAccount)
	 */
	public void delete(MonitorUnbalanceAccount persistentInstance) {
		log.debug("deleting MonitorUnbalanceAccount instance");
		baseDAO.removeEntity(persistentInstance);
	}
}