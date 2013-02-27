package org.king.support.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.support.dao.MonitorNotificationsDAO;
import org.king.support.domain.MonitorNotifications;

/**
 * Data access object (DAO) for domain model class MonitorCommands.
 * @see org.king.support.dao.hibernate.MonitorCommands
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorNotificationsDAOHibernate implements MonitorNotificationsDAO{

    private static final Log log = LogFactory.getLog(MonitorNotificationsDAOHibernate.class);    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding MonitorNotifications instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding MonitorNotifications instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public MonitorNotifications get(Serializable id) {
				log.debug("getting MonitorNotifications instance by id");
				return (MonitorNotifications)baseDAO.getEntity(MonitorNotifications.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MonitorNotifications all");
	      String allHql = "from MonitorNotifications";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MonitorNotifications transientInstance) {
        log.debug("saving MonitorNotifications instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MonitorNotifications transientInstance){
    	log.debug("updating MonitorNotifications instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MonitorNotifications persistentInstance) {
		    log.debug("deleting MonitorNotifications instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}