package org.king.support.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.support.dao.MonitorCommandsDAO;
import org.king.support.domain.MonitorCommands;

/**
 * Data access object (DAO) for domain model class MonitorCommands.
 * @see org.king.support.dao.hibernate.MonitorCommands
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorCommandsDAOHibernate implements MonitorCommandsDAO{

    private static final Log log = LogFactory.getLog(MonitorNotificationsDAOHibernate.class);    
    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding MonitorCommands instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding MonitorCommands instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public MonitorCommands get(Serializable id) {
				log.debug("getting MonitorCommands instance by id");
				return (MonitorCommands)baseDAO.getEntity(MonitorCommands.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MonitorCommands all");
	      String allHql = "from MonitorCommands";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MonitorCommands transientInstance) {
        log.debug("saving MonitorCommands instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MonitorCommands transientInstance){
    	log.debug("updating MonitorCommands instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MonitorCommands persistentInstance) {
		    log.debug("deleting MonitorCommands instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}