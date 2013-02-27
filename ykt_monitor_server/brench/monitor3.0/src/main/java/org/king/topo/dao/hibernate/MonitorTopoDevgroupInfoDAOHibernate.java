package org.king.topo.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.topo.dao.MonitorTopoDevgroupInfoDAO;
import org.king.topo.domain.MonitorTopoDevgroupInfo;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * A data access object (DAO) providing persistence and search support for
 * MonitorTopoDevgroupInfo entities. Transaction control of the save(), update()
 * and delete() operations can directly support Spring container-managed
 * transactions or they can be augmented to handle user-managed Spring
 * transactions. Each of these methods provides additional information for how
 * to configure it for the desired type of transaction control.
 * 
 * @see org.king.topo.domain.MonitorTopoDevgroupInfo
 * @author MyEclipse Persistence Tools
 */

public class MonitorTopoDevgroupInfoDAOHibernate implements
		MonitorTopoDevgroupInfoDAO {
	private static final Logger log = LoggerFactory
			.getLogger(MonitorTopoDevgroupInfoDAOHibernate.class);

	private BaseDAO baseDAO;

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoDevgroupInfoDAO#setBaseDAO(org
	 * .king.framework.dao.BaseDAO)
	 */
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoDevgroupInfoDAO#find(org.king.
	 * framework.dao.MyQuery)
	 */
	public List find(MyQuery myQuery) {
		log.debug("finding MonitorTopoDevgroupInfo instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoDevgroupInfoDAO#find(java.lang
	 * .String)
	 */
	public List find(String query) {
		log.debug("finding MonitorTopoDevgroupInfo instance by query");
		return baseDAO.findEntity(query);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @seeorg.king.topo.dao.hibernate.MonitorTopoDevgroupInfoDAO#get(java.io.
	 * Serializable)
	 */
	public MonitorTopoDevgroupInfo get(Serializable id) {
		log.debug("getting MonitorTopoDevgroupInfo instance by id");
		return (MonitorTopoDevgroupInfo) baseDAO.getEntity(
				MonitorTopoDevgroupInfo.class, id);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.topo.dao.hibernate.MonitorTopoDevgroupInfoDAO#getAll()
	 */
	public List getAll() {
		log.debug("getting MonitorTopoDevgroupInfo all");
		String allHql = "from MonitorTopoDevgroupInfo";
		return baseDAO.findEntity(allHql);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoDevgroupInfoDAO#save(org.king.
	 * topo.domain.MonitorTopoDevgroupInfo)
	 */
	public void save(MonitorTopoDevgroupInfo transientInstance) {
		log.debug("saving MonitorTopoDevgroupInfo instance");
		baseDAO.saveEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoDevgroupInfoDAO#update(org.king
	 * .topo.domain.MonitorTopoDevgroupInfo)
	 */
	public void update(MonitorTopoDevgroupInfo transientInstance) {
		log.debug("updating MonitorTopoDevgroupInfo instance");
		baseDAO.updateEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoDevgroupInfoDAO#delete(org.king
	 * .topo.domain.MonitorTopoDevgroupInfo)
	 */
	public void delete(MonitorTopoDevgroupInfo persistentInstance) {
		log.debug("deleting MonitorTopoDevgroupInfo instance");
		baseDAO.removeEntity(persistentInstance);
	}

	public List getDevgroupInfoByGroupid(Integer groupid) {
		String allHql = "from MonitorTopoDevgroupInfo where devicegroupid="+groupid;
		return baseDAO.findEntity(allHql);
	}
}