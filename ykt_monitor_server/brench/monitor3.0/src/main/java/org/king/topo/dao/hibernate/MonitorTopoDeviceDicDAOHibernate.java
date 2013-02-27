package org.king.topo.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.topo.dao.MonitorTopoDeviceDicDAO;
import org.king.topo.domain.MonitorTopoDeviceDic;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * A data access object (DAO) providing persistence and search support for
 * MonitorTopoDeviceDic entities. Transaction control of the save(), update()
 * and delete() operations can directly support Spring container-managed
 * transactions or they can be augmented to handle user-managed Spring
 * transactions. Each of these methods provides additional information for how
 * to configure it for the desired type of transaction control.
 * 
 * @see org.king.topo.domain.MonitorTopoDeviceDic
 * @author MyEclipse Persistence Tools
 */

public class MonitorTopoDeviceDicDAOHibernate implements
		MonitorTopoDeviceDicDAO {
	private static final Logger log = LoggerFactory
			.getLogger(MonitorTopoDeviceDicDAOHibernate.class);

	private BaseDAO baseDAO;

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoDeviceDicDAO#setBaseDAO(org.king
	 * .framework.dao.BaseDAO)
	 */
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoDeviceDicDAO#find(org.king.framework
	 * .dao.MyQuery)
	 */
	public List find(MyQuery myQuery) {
		log.debug("finding MonitorTopoDeviceDic instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoDeviceDicDAO#find(java.lang.String
	 * )
	 */
	public List find(String query) {
		log.debug("finding MonitorTopoDeviceDic instance by query");
		return baseDAO.findEntity(query);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoDeviceDicDAO#get(java.io.Serializable
	 * )
	 */
	public MonitorTopoDeviceDic get(Serializable id) {
		log.debug("getting MonitorTopoDeviceDic instance by id");
		return (MonitorTopoDeviceDic) baseDAO.getEntity(
				MonitorTopoDeviceDic.class, id);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see org.king.topo.dao.hibernate.MonitorTopoDeviceDicDAO#getAll()
	 */
	public List getAll() {
		log.debug("getting MonitorTopoDeviceDic all");
		String allHql = "from MonitorTopoDeviceDic";
		return baseDAO.findEntity(allHql);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoDeviceDicDAO#save(org.king.topo
	 * .domain.MonitorTopoDeviceDic)
	 */
	public void save(MonitorTopoDeviceDic transientInstance) {
		log.debug("saving MonitorTopoDeviceDic instance");
		baseDAO.saveEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoDeviceDicDAO#update(org.king.topo
	 * .domain.MonitorTopoDeviceDic)
	 */
	public void update(MonitorTopoDeviceDic transientInstance) {
		log.debug("updating MonitorTopoDeviceDic instance");
		baseDAO.updateEntity(transientInstance);
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see
	 * org.king.topo.dao.hibernate.MonitorTopoDeviceDicDAO#delete(org.king.topo
	 * .domain.MonitorTopoDeviceDic)
	 */
	public void delete(MonitorTopoDeviceDic persistentInstance) {
		log.debug("deleting MonitorTopoDeviceDic instance");
		baseDAO.removeEntity(persistentInstance);
	}

	public MonitorTopoDeviceDic findDictByTypecode(Integer devphytype,
			String devtypecode) {
		String oneHql = "from MonitorTopoDeviceDic where devphytype="+devphytype+" and devtypecode='"+devtypecode+"'";
		List list = baseDAO.findEntity(oneHql);
		if(list!=null&&list.size()>0){
			return (MonitorTopoDeviceDic)list.get(0);
		}
		return null;
	}
}