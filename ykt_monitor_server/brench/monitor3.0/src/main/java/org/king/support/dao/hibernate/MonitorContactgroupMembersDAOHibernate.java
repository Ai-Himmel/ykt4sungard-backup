package org.king.support.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.support.dao.MonitorContactgroupMembersDAO;
import org.king.support.domain.MonitorContactgroupMembers;

/**
 * Data access object (DAO) for domain model class MonitorContactgroupMembers.
 * 
 * @see org.king.support.dao.hibernate.MonitorContactgroupMembers
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorContactgroupMembersDAOHibernate implements
		MonitorContactgroupMembersDAO {
	private static final Log log = LogFactory
			.getLog(MonitorContactgroupMembersDAOHibernate.class);
	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public List find(MyQuery myQuery) {
		log.debug("finding MonitorContactgroupMembers instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	public List find(String query) {
		log.debug("finding MonitorContactgroupMembers instance by query");
		return baseDAO.findEntity(query);
	}

	public MonitorContactgroupMembers get(Serializable id) {
		log.debug("getting MonitorContactgroupMembers instance by id");
		return (MonitorContactgroupMembers) baseDAO.getEntity(
				MonitorContactgroupMembers.class, id);
	}

	public List getAll() {
		log.debug("getting MonitorContactgroupMembers all");
		String allHql = "from MonitorContactgroupMembers";
		return baseDAO.findEntity(allHql);
	}

	public void save(MonitorContactgroupMembers transientInstance) {
		log.debug("saving MonitorContactgroupMembers instance");
		baseDAO.saveEntity(transientInstance);
	}

	public void update(MonitorContactgroupMembers transientInstance) {
		log.debug("updating MonitorContactgroupMembers instance");
		baseDAO.updateEntity(transientInstance);
	}

	public void delete(MonitorContactgroupMembers persistentInstance) {
		log.debug("deleting MonitorContactgroupMembers instance");
		baseDAO.removeEntity(persistentInstance);
	}

}