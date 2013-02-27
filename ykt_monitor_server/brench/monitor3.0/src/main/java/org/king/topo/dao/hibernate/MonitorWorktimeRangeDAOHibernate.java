package org.king.topo.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.topo.dao.MonitorWorktimeRangeDAO;
import org.king.topo.domain.MonitorWorktimeRange;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * A data access object (DAO) providing persistence and search support for
 * MonitorWorktimeRange entities. Transaction control of the save(), update()
 * and delete() operations can directly support Spring container-managed
 * transactions or they can be augmented to handle user-managed Spring
 * transactions. Each of these methods provides additional information for how
 * to configure it for the desired type of transaction control.
 * 
 * @see org.king.topo.domain.MonitorWorktimeRange
 * @author MyEclipse Persistence Tools
 */

public class MonitorWorktimeRangeDAOHibernate implements
		MonitorWorktimeRangeDAO {
	private static final Logger log = LoggerFactory
			.getLogger(MonitorWorktimeRangeDAOHibernate.class);

	private BaseDAO baseDAO;

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorWorktimeRangeDAO#setBaseDAO(org.king
	 * .framework.dao.BaseDAO)
	 */
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorWorktimeRangeDAO#find(org.king.framework
	 * .dao.MyQuery)
	 */
	public List find(MyQuery myQuery) {
		log.debug("finding MonitorWorktimeRange instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorWorktimeRangeDAO#find(java.lang.String
	 * )
	 */
	public List find(String query) {
		log.debug("finding MonitorWorktimeRange instance by query");
		return baseDAO.findEntity(query);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorWorktimeRangeDAO#get(java.io.Serializable
	 * )
	 */
	public MonitorWorktimeRange get(Serializable id) {
		log.debug("getting MonitorWorktimeRange instance by id");
		return (MonitorWorktimeRange) baseDAO.getEntity(
				MonitorWorktimeRange.class, id);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.topo.dao.hibernate.MonitorWorktimeRangeDAO#getAll()
	 */
	public List getAll() {
		log.debug("getting MonitorWorktimeRange all");
		String allHql = "from MonitorWorktimeRange";
		return baseDAO.findEntity(allHql);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorWorktimeRangeDAO#save(org.king.topo
	 * .domain.MonitorWorktimeRange)
	 */
	public void save(MonitorWorktimeRange transientInstance) {
		log.debug("saving MonitorWorktimeRange instance");
		baseDAO.saveEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorWorktimeRangeDAO#update(org.king.topo
	 * .domain.MonitorWorktimeRange)
	 */
	public void update(MonitorWorktimeRange transientInstance) {
		log.debug("updating MonitorWorktimeRange instance");
		baseDAO.updateEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorWorktimeRangeDAO#delete(org.king.topo
	 * .domain.MonitorWorktimeRange)
	 */
	public void delete(MonitorWorktimeRange persistentInstance) {
		log.debug("deleting MonitorWorktimeRange instance");
		baseDAO.removeEntity(persistentInstance);
	}
}