package org.king.business.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.king.business.dao.MonitorUnbalanceAccountHisDAO;
import org.king.business.domain.MonitorUnbalanceAccountHis;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * A data access object (DAO) providing persistence and search support for
 * MonitorUnbalanceAccountHis entities. Transaction control of the save(),
 * update() and delete() operations can directly support Spring
 * container-managed transactions or they can be augmented to handle
 * user-managed Spring transactions. Each of these methods provides additional
 * information for how to configure it for the desired type of transaction
 * control.
 * 
 * @see org.king.topo.domain.MonitorUnbalanceAccountHis
 * @author MyEclipse Persistence Tools
 */

public class MonitorUnbalanceAccountHisDAOHibernate implements
		MonitorUnbalanceAccountHisDAO {
	private static final Logger log = LoggerFactory
			.getLogger(MonitorUnbalanceAccountHisDAOHibernate.class);

	private BaseDAO baseDAO;

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorUnbalanceAccountHisDAO#setBaseDAO(
	 * org.king.framework.dao.BaseDAO)
	 */
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorUnbalanceAccountHisDAO#find(org.king
	 * .framework.dao.MyQuery)
	 */
	public List find(MyQuery myQuery) {
		log.debug("finding MonitorUnbalanceAccountHis instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorUnbalanceAccountHisDAO#find(java.lang
	 * .String)
	 */
	public List find(String query) {
		log.debug("finding MonitorUnbalanceAccountHis instance by query");
		return baseDAO.findEntity(query);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorUnbalanceAccountHisDAO#get(java.io
	 * .Serializable)
	 */
	public MonitorUnbalanceAccountHis get(Serializable id) {
		log.debug("getting MonitorUnbalanceAccountHis instance by id");
		return (MonitorUnbalanceAccountHis) baseDAO.getEntity(
				MonitorUnbalanceAccountHis.class, id);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.topo.dao.hibernate.MonitorUnbalanceAccountHisDAO#getAll()
	 */
	public List getAll() {
		log.debug("getting MonitorUnbalanceAccountHis all");
		String allHql = "from MonitorUnbalanceAccountHis";
		return baseDAO.findEntity(allHql);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorUnbalanceAccountHisDAO#save(org.king
	 * .topo.domain.MonitorUnbalanceAccountHis)
	 */
	public void save(MonitorUnbalanceAccountHis transientInstance) {
		log.debug("saving MonitorUnbalanceAccountHis instance");
		baseDAO.saveEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorUnbalanceAccountHisDAO#update(org.
	 * king.topo.domain.MonitorUnbalanceAccountHis)
	 */
	public void update(MonitorUnbalanceAccountHis transientInstance) {
		log.debug("updating MonitorUnbalanceAccountHis instance");
		baseDAO.updateEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorUnbalanceAccountHisDAO#delete(org.
	 * king.topo.domain.MonitorUnbalanceAccountHis)
	 */
	public void delete(MonitorUnbalanceAccountHis persistentInstance) {
		log.debug("deleting MonitorUnbalanceAccountHis instance");
		baseDAO.removeEntity(persistentInstance);
	}
}