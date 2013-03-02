package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.CheckInfoDAO;
import org.king.check.domain.TCheckInfo;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * A data access object (DAO) providing persistence and search support for
 * TCheckInfo entities. Transaction control of the save(), update() and delete()
 * operations can directly support Spring container-managed transactions or they
 * can be augmented to handle user-managed Spring transactions. Each of these
 * methods provides additional information for how to configure it for the
 * desired type of transaction control.
 * 
 * @see org.king.check.domain.TCheckInfo
 * @author MyEclipse Persistence Tools
 */

public class CheckInfoDAOHibernate implements CheckInfoDAO {
	private static final Log log = LogFactory.getLog(CheckInfoDAOHibernate.class);

	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckInfoDAO#find(org.king.framework.dao.MyQuery)
	 */
	public List find(MyQuery myQuery) {
		log.debug("finding TCheckInfo instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckInfoDAO#find(java.lang.String)
	 */
	public List find(String query) {
		log.debug("finding TCheckInfo instance by query");
		return baseDAO.findEntity(query);
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckInfoDAO#get(java.io.Serializable)
	 */
	public TCheckInfo get(Serializable id) {
		log.debug("getting TCheckInfo instance by id");
		return (TCheckInfo) baseDAO.getEntity(TCheckInfo.class, id);
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckInfoDAO#getAll()
	 */
	public List getAll() {
		log.debug("getting TCheckInfo all");
		String allHql = "from TCheckInfo";
		return baseDAO.findEntity(allHql);
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckInfoDAO#save(org.test.TCheckInfo)
	 */
	public void save(TCheckInfo transientInstance) {
		log.debug("saving TCheckInfo instance");
		baseDAO.saveEntity(transientInstance);
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckInfoDAO#update(org.test.TCheckInfo)
	 */
	public void update(TCheckInfo transientInstance) {
		log.debug("updating TCheckInfo instance");
		baseDAO.updateEntity(transientInstance);
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckInfoDAO#delete(org.test.TCheckInfo)
	 */
	public void delete(TCheckInfo persistentInstance) {
		log.debug("deleting TCheckInfo instance");
		baseDAO.removeEntity(persistentInstance);
	}

}