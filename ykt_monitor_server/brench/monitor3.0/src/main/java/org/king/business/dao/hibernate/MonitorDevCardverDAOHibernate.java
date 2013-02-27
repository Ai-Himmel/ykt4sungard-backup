package org.king.business.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.king.business.dao.MonitorDevCardverDAO;
import org.king.business.domain.MonitorDevCardver;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * A data access object (DAO) providing persistence and search support for
 * MonitorDevCardver entities. Transaction control of the save(), update() and
 * delete() operations can directly support Spring container-managed
 * transactions or they can be augmented to handle user-managed Spring
 * transactions. Each of these methods provides additional information for how
 * to configure it for the desired type of transaction control.
 * 
 * @see org.king.topo.domain.MonitorDevCardver
 * @author MyEclipse Persistence Tools
 */

public class MonitorDevCardverDAOHibernate implements MonitorDevCardverDAO {
	private static final Logger log = LoggerFactory
			.getLogger(MonitorDevCardverDAOHibernate.class);

	private BaseDAO baseDAO;

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevCardverDAO#setBaseDAO(org.king.
	 * framework.dao.BaseDAO)
	 */
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevCardverDAO#find(org.king.framework
	 * .dao.MyQuery)
	 */
	public List find(MyQuery myQuery) {
		log.debug("finding MonitorDevCardver instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevCardverDAO#find(java.lang.String)
	 */
	public List find(String query) {
		log.debug("finding MonitorDevCardver instance by query");
		return baseDAO.findEntity(query);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevCardverDAO#get(java.io.Serializable
	 * )
	 */
	public MonitorDevCardver get(Serializable id) {
		log.debug("getting MonitorDevCardver instance by id");
		return (MonitorDevCardver) baseDAO.getEntity(MonitorDevCardver.class,
				id);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.topo.dao.hibernate.MonitorDevCardverDAO#getAll()
	 */
	public List getAll() {
		log.debug("getting MonitorDevCardver all");
		String allHql = "from MonitorDevCardver";
		return baseDAO.findEntity(allHql);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevCardverDAO#save(org.king.topo.domain
	 * .MonitorDevCardver)
	 */
	public void save(MonitorDevCardver transientInstance) {
		log.debug("saving MonitorDevCardver instance");
		baseDAO.saveEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevCardverDAO#update(org.king.topo
	 * .domain.MonitorDevCardver)
	 */
	public void update(MonitorDevCardver transientInstance) {
		log.debug("updating MonitorDevCardver instance");
		baseDAO.updateEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevCardverDAO#delete(org.king.topo
	 * .domain.MonitorDevCardver)
	 */
	public void delete(MonitorDevCardver persistentInstance) {
		log.debug("deleting MonitorDevCardver instance");
		baseDAO.removeEntity(persistentInstance);
	}
}