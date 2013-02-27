package org.king.hostservice.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.hostservice.dao.MonitorServicecommentsDAO;
import org.king.hostservice.domain.MonitorServicecoments;
import org.springframework.orm.ObjectRetrievalFailureException;

/**
 * Data access object (DAO) for domain model class MonitorServicecoments.
 * 
 * @see org.king.hostservice.dao.hibernate.MonitorServicecoments
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorServicecommentsDAOHibernate implements
		MonitorServicecommentsDAO {

	private static final Log log = LogFactory
			.getLog(MonitorServicecommentsDAOHibernate.class);

	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public List find(MyQuery myQuery) {
		log.debug("finding MonitorServicecoments instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	public List find(String query) {
		log.debug("finding MonitorServicecoments instance by query");
		return baseDAO.findEntity(query);
	}

	public MonitorServicecoments get(Serializable id) {
		log.debug("getting MonitorServicecoments instance by id");
		Object temp = null;
		try {
			temp = baseDAO.getEntity(MonitorServicecoments.class, id);
		} catch (ObjectRetrievalFailureException e) {
			// TODO: handle exception
		}
		if (temp != null) {
			return (MonitorServicecoments) temp;
		}
		return null;
	}

	public List getAll() {
		log.debug("getting MonitorServicecoments all");
		String allHql = "from MonitorServicecoments";
		return baseDAO.findEntity(allHql);
	}

	public void save(MonitorServicecoments transientInstance) {
		log.debug("saving MonitorServicecoments instance");
		baseDAO.saveEntity(transientInstance);
	}

	public void update(MonitorServicecoments transientInstance) {
		log.debug("updating MonitorServicecoments instance");
		baseDAO.updateEntity(transientInstance);
	}

	public void delete(MonitorServicecoments persistentInstance) {
		log.debug("deleting MonitorServicecoments instance");
		baseDAO.removeEntity(persistentInstance);
	}

}