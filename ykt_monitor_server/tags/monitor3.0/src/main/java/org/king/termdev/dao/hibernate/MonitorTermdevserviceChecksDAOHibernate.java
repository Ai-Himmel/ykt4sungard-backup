package org.king.termdev.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.termdev.dao.MonitorTermdevserviceChecksDAO;
import org.king.termdev.domain.MonitorTermdevserviceChecks;

/**
 * Data access object (DAO) for domain model class MonitorTermdevserviceChecks.
 * @see org.king.termdev.dao.hibernate.MonitorTermdevserviceChecks
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorTermdevserviceChecksDAOHibernate implements MonitorTermdevserviceChecksDAO{

    private static final Log log = LogFactory.getLog(MonitorTermdevserviceChecksDAOHibernate.class);

    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding MonitorTermdevserviceChecks instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding MonitorTermdevserviceChecks instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public MonitorTermdevserviceChecks get(Serializable id) {
				log.debug("getting MonitorTermdevserviceChecks instance by id");
				return (MonitorTermdevserviceChecks)baseDAO.getEntity(MonitorTermdevserviceChecks.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MonitorTermdevserviceChecks all");
	      String allHql = "from MonitorTermdevserviceChecks";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MonitorTermdevserviceChecks transientInstance) {
        log.debug("saving MonitorTermdevserviceChecks instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MonitorTermdevserviceChecks transientInstance){
    	log.debug("updating MonitorTermdevserviceChecks instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MonitorTermdevserviceChecks persistentInstance) {
		    log.debug("deleting MonitorTermdevserviceChecks instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}