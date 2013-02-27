package org.king.topo.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.topo.dao.MonitorParameterDAO;
import org.king.topo.domain.MonitorParameter;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * A data access object (DAO) providing persistence and search support for
 * MonitorParameter entities. Transaction control of the save(), update() and
 * delete() operations can directly support Spring container-managed
 * transactions or they can be augmented to handle user-managed Spring
 * transactions. Each of these methods provides additional information for how
 * to configure it for the desired type of transaction control.
 * 
 * @see org.king.topo.domain.MonitorParameter
 * @author MyEclipse Persistence Tools
 */

public class MonitorParameterDAOHibernate implements MonitorParameterDAO {
	private static final Logger log = LoggerFactory
			.getLogger(MonitorParameterDAOHibernate.class);

	private BaseDAO baseDAO;

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorParameterDAO#setBaseDAO(org.king.framework
	 * .dao.BaseDAO)
	 */
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorParameterDAO#find(org.king.framework
	 * .dao.MyQuery)
	 */
	public List find(MyQuery myQuery) {
		log.debug("finding MonitorParameter instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorParameterDAO#find(java.lang.String)
	 */
	public List find(String query) {
		log.debug("finding MonitorParameter instance by query");
		return baseDAO.findEntity(query);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorParameterDAO#get(java.io.Serializable)
	 */
	public MonitorParameter get(Serializable id) {
		log.debug("getting MonitorParameter instance by id");
		return (MonitorParameter) baseDAO.getEntity(MonitorParameter.class, id);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.topo.dao.hibernate.MonitorParameterDAO#getAll()
	 */
	public List getAll() {
		log.debug("getting MonitorParameter all");
		String allHql = "from MonitorParameter";
		return baseDAO.findEntity(allHql);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorParameterDAO#save(org.king.topo.domain
	 * .MonitorParameter)
	 */
	public void save(MonitorParameter transientInstance) {
		log.debug("saving MonitorParameter instance");
		baseDAO.saveEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorParameterDAO#update(org.king.topo.
	 * domain.MonitorParameter)
	 */
	public void update(MonitorParameter transientInstance) {
		log.debug("updating MonitorParameter instance");
		baseDAO.updateEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorParameterDAO#delete(org.king.topo.
	 * domain.MonitorParameter)
	 */
	public void delete(MonitorParameter persistentInstance) {
		log.debug("deleting MonitorParameter instance");
		baseDAO.removeEntity(persistentInstance);
	}
}