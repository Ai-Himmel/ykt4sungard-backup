package org.king.business.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.king.business.dao.MonitorDevtransCheckDAO;
import org.king.business.domain.MonitorDevtransCheck;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * A data access object (DAO) providing persistence and search support for
 * MonitorDevtransCheck entities. Transaction control of the save(), update()
 * and delete() operations can directly support Spring container-managed
 * transactions or they can be augmented to handle user-managed Spring
 * transactions. Each of these methods provides additional information for how
 * to configure it for the desired type of transaction control.
 * 
 * @see org.king.topo.domain.MonitorDevtransCheck
 * @author MyEclipse Persistence Tools
 */

public class MonitorDevtransCheckDAOHibernate implements
		MonitorDevtransCheckDAO {
	private static final Logger log = LoggerFactory
			.getLogger(MonitorDevtransCheckDAOHibernate.class);

	private BaseDAO baseDAO;

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevtransCheckDAO#setBaseDAO(org.king
	 * .framework.dao.BaseDAO)
	 */
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevtransCheckDAO#find(org.king.framework
	 * .dao.MyQuery)
	 */
	public List find(MyQuery myQuery) {
		log.debug("finding MonitorDevtransCheck instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevtransCheckDAO#find(java.lang.String
	 * )
	 */
	public List find(String query) {
		log.debug("finding MonitorDevtransCheck instance by query");
		return baseDAO.findEntity(query);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevtransCheckDAO#get(java.io.Serializable
	 * )
	 */
	public MonitorDevtransCheck get(Serializable id) {
		log.debug("getting MonitorDevtransCheck instance by id");
		return (MonitorDevtransCheck) baseDAO.getEntity(
				MonitorDevtransCheck.class, id);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.topo.dao.hibernate.MonitorDevtransCheckDAO#getAll()
	 */
	public List getAll() {
		log.debug("getting MonitorDevtransCheck all");
		String allHql = "from MonitorDevtransCheck";
		return baseDAO.findEntity(allHql);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevtransCheckDAO#save(org.king.topo
	 * .domain.MonitorDevtransCheck)
	 */
	public void save(MonitorDevtransCheck transientInstance) {
		log.debug("saving MonitorDevtransCheck instance");
		baseDAO.saveEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevtransCheckDAO#update(org.king.topo
	 * .domain.MonitorDevtransCheck)
	 */
	public void update(MonitorDevtransCheck transientInstance) {
		log.debug("updating MonitorDevtransCheck instance");
		baseDAO.updateEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevtransCheckDAO#delete(org.king.topo
	 * .domain.MonitorDevtransCheck)
	 */
	public void delete(MonitorDevtransCheck persistentInstance) {
		log.debug("deleting MonitorDevtransCheck instance");
		baseDAO.removeEntity(persistentInstance);
	}
}