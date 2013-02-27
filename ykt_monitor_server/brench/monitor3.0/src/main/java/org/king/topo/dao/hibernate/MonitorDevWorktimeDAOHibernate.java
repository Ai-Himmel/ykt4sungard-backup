package org.king.topo.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.topo.dao.MonitorDevWorktimeDAO;
import org.king.topo.domain.MonitorDevWorktime;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * A data access object (DAO) providing persistence and search support for
 * MonitorDevWorktime entities. Transaction control of the save(), update() and
 * delete() operations can directly support Spring container-managed
 * transactions or they can be augmented to handle user-managed Spring
 * transactions. Each of these methods provides additional information for how
 * to configure it for the desired type of transaction control.
 * 
 * @see org.king.topo.domain.MonitorDevWorktime
 * @author MyEclipse Persistence Tools
 */

public class MonitorDevWorktimeDAOHibernate implements MonitorDevWorktimeDAO {
	private static final Logger log = LoggerFactory
			.getLogger(MonitorDevWorktimeDAOHibernate.class);

	private BaseDAO baseDAO;

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevWorktimeDAO#setBaseDAO(org.king
	 * .framework.dao.BaseDAO)
	 */
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevWorktimeDAO#find(org.king.framework
	 * .dao.MyQuery)
	 */
	public List find(MyQuery myQuery) {
		log.debug("finding MonitorDevWorktime instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevWorktimeDAO#find(java.lang.String)
	 */
	public List find(String query) {
		log.debug("finding MonitorDevWorktime instance by query");
		return baseDAO.findEntity(query);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevWorktimeDAO#get(java.io.Serializable
	 * )
	 */
	public MonitorDevWorktime get(Serializable id) {
		log.debug("getting MonitorDevWorktime instance by id");
		return (MonitorDevWorktime) baseDAO.getEntity(MonitorDevWorktime.class,
				id);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.topo.dao.hibernate.MonitorDevWorktimeDAO#getAll()
	 */
	public List getAll() {
		log.debug("getting MonitorDevWorktime all");
		String allHql = "from MonitorDevWorktime";
		return baseDAO.findEntity(allHql);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevWorktimeDAO#save(org.king.topo.
	 * domain.MonitorDevWorktime)
	 */
	public void save(MonitorDevWorktime transientInstance) {
		log.debug("saving MonitorDevWorktime instance");
		baseDAO.saveEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevWorktimeDAO#update(org.king.topo
	 * .domain.MonitorDevWorktime)
	 */
	public void update(MonitorDevWorktime transientInstance) {
		log.debug("updating MonitorDevWorktime instance");
		baseDAO.updateEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevWorktimeDAO#delete(org.king.topo
	 * .domain.MonitorDevWorktime)
	 */
	public void delete(MonitorDevWorktime persistentInstance) {
		log.debug("deleting MonitorDevWorktime instance");
		baseDAO.removeEntity(persistentInstance);
	}

}