package org.king.business.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.king.business.dao.MonitorDevCardverHisDAO;
import org.king.business.domain.MonitorDevCardverHis;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * A data access object (DAO) providing persistence and search support for
 * MonitorDevCardverHis entities. Transaction control of the save(), update()
 * and delete() operations can directly support Spring container-managed
 * transactions or they can be augmented to handle user-managed Spring
 * transactions. Each of these methods provides additional information for how
 * to configure it for the desired type of transaction control.
 * 
 * @see org.king.topo.domain.MonitorDevCardverHis
 * @author MyEclipse Persistence Tools
 */

public class MonitorDevCardverHisDAOHibernate implements
		MonitorDevCardverHisDAO {
	private static final Logger log = LoggerFactory
			.getLogger(MonitorDevCardverHisDAOHibernate.class);

	private BaseDAO baseDAO;

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevCardverHisDAO#setBaseDAO(org.king
	 * .framework.dao.BaseDAO)
	 */
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevCardverHisDAO#find(org.king.framework
	 * .dao.MyQuery)
	 */
	public List find(MyQuery myQuery) {
		log.debug("finding MonitorDevCardverHis instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevCardverHisDAO#find(java.lang.String
	 * )
	 */
	public List find(String query) {
		log.debug("finding MonitorDevCardverHis instance by query");
		return baseDAO.findEntity(query);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevCardverHisDAO#get(java.io.Serializable
	 * )
	 */
	public MonitorDevCardverHis get(Serializable id) {
		log.debug("getting MonitorDevCardverHis instance by id");
		return (MonitorDevCardverHis) baseDAO.getEntity(
				MonitorDevCardverHis.class, id);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.topo.dao.hibernate.MonitorDevCardverHisDAO#getAll()
	 */
	public List getAll() {
		log.debug("getting MonitorDevCardverHis all");
		String allHql = "from MonitorDevCardverHis";
		return baseDAO.findEntity(allHql);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevCardverHisDAO#save(org.king.topo
	 * .domain.MonitorDevCardverHis)
	 */
	public void save(MonitorDevCardverHis transientInstance) {
		log.debug("saving MonitorDevCardverHis instance");
		baseDAO.saveEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevCardverHisDAO#update(org.king.topo
	 * .domain.MonitorDevCardverHis)
	 */
	public void update(MonitorDevCardverHis transientInstance) {
		log.debug("updating MonitorDevCardverHis instance");
		baseDAO.updateEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorDevCardverHisDAO#delete(org.king.topo
	 * .domain.MonitorDevCardverHis)
	 */
	public void delete(MonitorDevCardverHis persistentInstance) {
		log.debug("deleting MonitorDevCardverHis instance");
		baseDAO.removeEntity(persistentInstance);
	}
}