package org.king.hostservice.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.hostservice.dao.MonitorSrvScheduleddowntimeDAO;
import org.king.hostservice.domain.MonitorSrvScheduleddowntime;
import org.springframework.orm.ObjectRetrievalFailureException;

/**
 * Data access object (DAO) for domain model class MonitorSrvScheduleddowntime.
 * 
 * @see org.king.hostservice.dao.hibernate.MonitorSrvScheduleddowntime
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorSrvScheduleddowntimeDAOHibernate implements
		MonitorSrvScheduleddowntimeDAO {

	private static final Log log = LogFactory
			.getLog(MonitorSrvScheduleddowntimeDAOHibernate.class);

	private BaseDAO baseDAO;

	public void setBaseDAO(BaseDAO baseDAO) {
		this.baseDAO = baseDAO;
	}

	public List find(MyQuery myQuery) {
		log.debug("finding MonitorSrvScheduleddowntime instance by myQuery");
		return baseDAO.findEntity(myQuery);
	}

	public List find(String query) {
		log.debug("finding MonitorSrvScheduleddowntime instance by query");
		return baseDAO.findEntity(query);
	}

	public MonitorSrvScheduleddowntime get(Serializable id) {
		log.debug("getting MonitorSrvScheduleddowntime instance by id");
		Object temp = null;
		try {
			temp = baseDAO.getEntity(MonitorSrvScheduleddowntime.class, id);
		} catch (ObjectRetrievalFailureException e) {
			// TODO: handle exception
		}
		if (temp != null) {
			return (MonitorSrvScheduleddowntime) temp;
		}
		return null;
	}

	public List getAll() {
		log.debug("getting MonitorSrvScheduleddowntime all");
		String allHql = "from MonitorSrvScheduleddowntime";
		return baseDAO.findEntity(allHql);
	}

	public void save(MonitorSrvScheduleddowntime transientInstance) {
		log.debug("saving MonitorSrvScheduleddowntime instance");
		baseDAO.saveEntity(transientInstance);
	}

	public void update(MonitorSrvScheduleddowntime transientInstance) {
		log.debug("updating MonitorSrvScheduleddowntime instance");
		baseDAO.updateEntity(transientInstance);
	}

	public void delete(MonitorSrvScheduleddowntime persistentInstance) {
		log.debug("deleting MonitorSrvScheduleddowntime instance");
		baseDAO.removeEntity(persistentInstance);
	}

	public boolean checkSrvDowntime(Integer objectid,String nowtime){
		List list = find("from MonitorSrvScheduleddowntime a where a.serviceId="+objectid+" and a.scheduledStartTime<='"+nowtime+"' and a.scheduledEndTime>='"+nowtime+"'");
		if(list!=null&&list.size()>0){
			return true;
		}
		return false;
	}
}