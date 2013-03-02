package org.king.classmanage.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.classmanage.dao.StuAdddelhisDAO;
import org.king.classmanage.domain.StuAdddelhis;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class StuAdddelhis.
 * 
 * @see org.king.classmanage.dao.hibernate.StuAdddelhis
 * @author MyEclipse - Hibernate Tools
 */
public class StuAdddelhisDAOHibernate implements StuAdddelhisDAO {

	private static final Log log = LogFactory
			.getLog(StuAdddelhisDAOHibernate.class);

	protected void initDao() {
		// do nothing
	}

	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public List find(MyQuery myQuery) {
		log.debug("finding StuAdddelhis instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	public List find(String query) {
		log.debug("finding StuAdddelhis instance by query");
		return baseDAO.findEntity(query);
	}

	public StuAdddelhis get(Serializable id) {
		log.debug("getting StuAdddelhis instance by id");
		return (StuAdddelhis) baseDAO.getEntity(StuAdddelhis.class, id);
	}

	public List getAll() {
		log.debug("getting StuAdddelhis all");
		String allHql = "from StuAdddelhis";
		return baseDAO.findEntity(allHql);
	}

	public void save(StuAdddelhis transientInstance) {
		log.debug("saving StuAdddelhis instance");
		baseDAO.saveEntity(transientInstance);
	}

	public void update(StuAdddelhis transientInstance) {
		log.debug("updating StuAdddelhis instance");
		baseDAO.updateEntity(transientInstance);
	}

	public void delete(StuAdddelhis persistentInstance) {
		log.debug("deleting StuAdddelhis instance");
		baseDAO.removeEntity(persistentInstance);
	}

}