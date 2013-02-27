package org.king.support.dao.hibernate;

import java.io.Serializable;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.framework.dao.BaseDAO;
import org.king.framework.dao.MyQuery;
import org.king.support.dao.MonitorConfigvariablesDAO;
import org.king.support.domain.MonitorConfigvariables;

/**
 * Data access object (DAO) for domain model class MonitorConfigvariables.
 * @see org.king.support.dao.hibernate.MonitorConfigvariables
 * @author MyEclipse - Hibernate Tools
 */
public class MonitorConfigvariablesDAOHibernate implements MonitorConfigvariablesDAO{

    private static final Log log = LogFactory.getLog(MonitorConfigvariablesDAOHibernate.class);

    private BaseDAO baseDAO;
    
    public void setBaseDAO(BaseDAO baseDAO) {
		    this.baseDAO = baseDAO;
	  }
	
    public List find(MyQuery myQuery) {
        log.debug("finding MonitorConfigvariables instance by myQuery");
        return baseDAO.findEntity(myQuery);
    }
    
    public List find(String query) {
				log.debug("finding MonitorConfigvariables instance by query");
				return baseDAO.findEntity(query);
	  }
	  
	  public MonitorConfigvariables get(Serializable id) {
				log.debug("getting MonitorConfigvariables instance by id");
				return (MonitorConfigvariables)baseDAO.getEntity(MonitorConfigvariables.class,id);
	  }
	
	  public List getAll() {
	      log.debug("getting MonitorConfigvariables all");
	      String allHql = "from MonitorConfigvariables";
	      return baseDAO.findEntity(allHql);
	  }
	  
    public void save(MonitorConfigvariables transientInstance) {
        log.debug("saving MonitorConfigvariables instance");
        baseDAO.saveEntity(transientInstance);
    }
    
    public void update(MonitorConfigvariables transientInstance){
    	log.debug("updating MonitorConfigvariables instance");
    	baseDAO.updateEntity(transientInstance);
    }
    
    
	  public void delete(MonitorConfigvariables persistentInstance) {
		    log.debug("deleting MonitorConfigvariables instance");
        baseDAO.removeEntity(persistentInstance);
    }
    
	

    

    


}