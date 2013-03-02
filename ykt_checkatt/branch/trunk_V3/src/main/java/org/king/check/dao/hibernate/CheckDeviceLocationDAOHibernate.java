package org.king.check.dao.hibernate;

import java.io.Serializable;
import java.util.List;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.CheckDeviceLocationDAO;
import org.king.check.domain.TCheckDeviceLocation;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;

/**
 * A data access object (DAO) providing persistence and search support for
 * TCheckDeviceLocation entities. Transaction control of the save(), update()
 * and delete() operations can directly support Spring container-managed
 * transactions or they can be augmented to handle user-managed Spring
 * transactions. Each of these methods provides additional information for how
 * to configure it for the desired type of transaction control.
 * 
 * @see org.king.check.domain.TCheckDeviceLocation
 * @author MyEclipse Persistence Tools
 */

public class CheckDeviceLocationDAOHibernate implements CheckDeviceLocationDAO {
	private static final Log log = LogFactory.getLog(CheckDeviceLocationDAOHibernate.class);

	private BaseDAO baseDAO;

	/* (non-Javadoc)
	 * @see org.test.TCheckDeviceLocationDAO#setBaseDAO(org.king.framework.dao.BaseDAO)
	 */
	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckDeviceLocationDAO#find(org.king.framework.dao.MyQuery)
	 */
	public List find(MyQuery myQuery) {
		log.debug("finding TCheckDeviceLocation instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckDeviceLocationDAO#find(java.lang.String)
	 */
	public List find(String query) {
		log.debug("finding TCheckDeviceLocation instance by query");
		return baseDAO.findEntity(query);
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckDeviceLocationDAO#get(java.io.Serializable)
	 */
	public TCheckDeviceLocation get(Serializable id) {
		log.debug("getting TCheckDeviceLocation instance by id");
		return (TCheckDeviceLocation) baseDAO.getEntity(
				TCheckDeviceLocation.class, id);
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckDeviceLocationDAO#getAll()
	 */
	public List getAll() {
		log.debug("getting TCheckDeviceLocation all");
		String allHql = "from TCheckDeviceLocation";
		return baseDAO.findEntity(allHql);
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckDeviceLocationDAO#save(org.test.TCheckDeviceLocation)
	 */
	public void save(TCheckDeviceLocation transientInstance) {
		log.debug("saving TCheckDeviceLocation instance");
		baseDAO.saveEntity(transientInstance);
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckDeviceLocationDAO#update(org.test.TCheckDeviceLocation)
	 */
	public void update(TCheckDeviceLocation transientInstance) {
		log.debug("updating TCheckDeviceLocation instance");
		baseDAO.updateEntity(transientInstance);
	}

	/* (non-Javadoc)
	 * @see org.test.TCheckDeviceLocationDAO#delete(org.test.TCheckDeviceLocation)
	 */
	public void delete(TCheckDeviceLocation persistentInstance) {
		log.debug("deleting TCheckDeviceLocation instance");
		baseDAO.removeEntity(persistentInstance);
	}

	public TCheckDeviceLocation getCheckDeviceLocation(String deviceid) {
		String hql = "from TCheckDeviceLocation t where t.id.deviceId="+deviceid;
		List result = baseDAO.findEntity(hql);
		if(result!=null && result.size()>0){
			return (TCheckDeviceLocation) result.get(0);
		}
		return null;
	}

}