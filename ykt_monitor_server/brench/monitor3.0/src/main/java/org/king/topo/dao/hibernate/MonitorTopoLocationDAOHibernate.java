package org.king.topo.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.topo.dao.MonitorTopoLocationDAO;
import org.king.topo.domain.MonitorTopoLocation;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * A data access object (DAO) providing persistence and search support for
 * MonitorTopoLocation entities. Transaction control of the save(), update() and
 * delete() operations can directly support Spring container-managed
 * transactions or they can be augmented to handle user-managed Spring
 * transactions. Each of these methods provides additional information for how
 * to configure it for the desired type of transaction control.
 * 
 * @see org.king.topo.domain.MonitorTopoLocation
 * @author MyEclipse Persistence Tools
 */

public class MonitorTopoLocationDAOHibernate implements MonitorTopoLocationDAO {
	private static final Logger log = LoggerFactory
			.getLogger(MonitorTopoLocationDAOHibernate.class);

	private BaseDAO baseDAO;

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoLocationDAO#setBaseDAO(org.king
	 * .framework.dao.BaseDAO)
	 */
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoLocationDAO#find(org.king.framework
	 * .dao.MyQuery)
	 */
	public List find(MyQuery myQuery) {
		log.debug("finding MonitorTopoLocation instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoLocationDAO#find(java.lang.String)
	 */
	public List find(String query) {
		log.debug("finding MonitorTopoLocation instance by query");
		return baseDAO.findEntity(query);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoLocationDAO#get(java.io.Serializable
	 * )
	 */
	public MonitorTopoLocation get(Serializable id) {
		log.debug("getting MonitorTopoLocation instance by id");
		return (MonitorTopoLocation) baseDAO.getEntity(
				MonitorTopoLocation.class, id);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.topo.dao.hibernate.MonitorTopoLocationDAO#getAll()
	 */
	public List getAll() {
		log.debug("getting MonitorTopoLocation all");
		String allHql = "from MonitorTopoLocation";
		return baseDAO.findEntity(allHql);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoLocationDAO#save(org.king.topo
	 * .domain.MonitorTopoLocation)
	 */
	public void save(MonitorTopoLocation transientInstance) {
		log.debug("saving MonitorTopoLocation instance");
		baseDAO.saveEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoLocationDAO#update(org.king.topo
	 * .domain.MonitorTopoLocation)
	 */
	public void update(MonitorTopoLocation transientInstance) {
		log.debug("updating MonitorTopoLocation instance");
		baseDAO.updateEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoLocationDAO#delete(org.king.topo
	 * .domain.MonitorTopoLocation)
	 */
	public void delete(MonitorTopoLocation persistentInstance) {
		log.debug("deleting MonitorTopoLocation instance");
		baseDAO.removeEntity(persistentInstance);
	}
}