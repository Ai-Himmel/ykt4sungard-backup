package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.WorkInfoDao;
import org.king.check.domain.Tattserialrecord;
import org.king.check.domain.Tcheckattreport;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * Data access object (DAO) for domain model class Workinfo.
 * 
 * @see org.king.check.dao.hibernate.Workinfo
 * @author MyEclipse - Hibernate Tools
 */
public class WorkinfoDAOHibernate implements WorkInfoDao {

	private static final Log log = LogFactory
			.getLog(WorkinfoDAOHibernate.class);

	protected void initDao() {
		// do nothing
	}

	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public List find(MyQuery myQuery) {
		return baseDAO.findEntity(myQuery);
	}

	public List find(String query) {
		return baseDAO.findEntity(query);
	}

	public Tattserialrecord get(Serializable id) {
		return (Tattserialrecord) baseDAO.getEntity(Tattserialrecord.class, id);
	}

	public List getAll() {
		String allHql = "from Workinfo";
		return baseDAO.findEntity(allHql);
	}

	public void save(Tattserialrecord transientInstance) {
		baseDAO.saveEntity(transientInstance);
	}

	public void update(Tattserialrecord transientInstance) {
		baseDAO.updateEntity(transientInstance);
	}

	public void delete(Tattserialrecord persistentInstance) {
		log.debug("deleting Workinfo instance");
		baseDAO.removeEntity(persistentInstance);
	}

	public void delete(Tcheckattreport workInfo) {
		baseDAO.removeEntity(workInfo);
		
	}

	public void save(Tcheckattreport workInfo) {
		baseDAO.saveEntity(workInfo);
		
	}

	public void update(Tcheckattreport workInfo) {
		baseDAO.updateEntity(workInfo);
		
	}

}