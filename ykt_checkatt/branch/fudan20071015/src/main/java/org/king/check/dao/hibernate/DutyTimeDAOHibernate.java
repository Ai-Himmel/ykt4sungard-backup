package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.DutyTimeDAO;
import org.king.check.domain.Tcheckattinfo;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class DutyTimeDAO.
 * 
 * @see org.king.check.dao.hibernate.DutyTimeDAO
 * @author MyEclipse - Hibernate Tools
 */
public class DutyTimeDAOHibernate implements DutyTimeDAO {

	private static final Log log = LogFactory
			.getLog(DutyTimeDAOHibernate.class);

	protected void initDao() {
		// do nothing
	}

	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public List find(MyQuery myQuery) {
		// log.debug("finding DutyTimeDAO instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	public List find(String query) {
		// log.debug("finding DutyTimeDAO instance by query");
		return baseDAO.findEntity(query);
	}

	public Tcheckattinfo get(Serializable id) {
		// log.debug("getting DutyTimeDAO instance by id");
		return (Tcheckattinfo) baseDAO.getEntity(Tcheckattinfo.class, id);
	}

	public List getAll() {
		// log.debug("getting DutyTimeDAO all");
		String allHql = "from Tcheckattinfo";
		return baseDAO.findEntity(allHql);
	}

	public void save(Tcheckattinfo transientInstance) {
		// log.debug("saving DutyTimeDAO instance");
		baseDAO.saveEntity(transientInstance);
	}

	public void update(Tcheckattinfo transientInstance) {
		// log.debug("updating DutyTimeDAO instance");
		baseDAO.updateEntity(transientInstance);
	}

	public void delete(Tcheckattinfo persistentInstance) {
		// log.debug("deleting DutyTimeDAO instance");
		baseDAO.removeEntity(persistentInstance);
	}

}